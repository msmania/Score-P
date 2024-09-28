#include <mpi.h>
#include <cmath>
#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include "jacobi.h"
#include <stddef.h>

#include <scorep/SCOREP_User.h>

#if !defined ( __offsetof__ ) && !defined ( offsetof )
#define offsetof( TYPE, MEMBER ) ( ( size_t )&( ( TYPE* )0 )->MEMBER )
#endif

#define U( j, i ) data.afU[ ( ( j ) - data.iRowFirst ) * data.iCols + ( i ) ]
#define F( j, i ) data.afF[ ( ( j ) - data.iRowFirst ) * data.iCols + ( i ) ]

using namespace std;

// setting values, init mpi, omp etc
void
Init( JacobiData& data, int& argc, char** argv )
{
    /* MPI Initialization */
    MPI_Init( &argc, &argv );
    MPI_Comm_rank( MPI_COMM_WORLD, &data.iMyRank );
    MPI_Comm_size( MPI_COMM_WORLD, &data.iNumProcs );

    /*user topology test*/
    SCOREP_USER_CARTESIAN_TOPOLOGY_CREATE( mytopo, "My own Topology", 2 );
    SCOREP_USER_CARTESIAN_TOPOLOGY_ADD_DIM( mytopo, 2, 1, "dim1_2" );
    SCOREP_USER_CARTESIAN_TOPOLOGY_ADD_DIM( mytopo, ( data.iNumProcs + 1 ) / 2, 1, "dim2_4" );
    SCOREP_USER_CARTESIAN_TOPOLOGY_INIT( mytopo );
    SCOREP_USER_CARTESIAN_TOPOLOGY_SET_COORDS( mytopo, 2, data.iMyRank % 2, data.iMyRank / 2 );

    /*mpi topology test*/
    int      dim[ 2 ], period[ 2 ], reorder;
    MPI_Comm comm;
    dim[ 0 ]    = 1;
    dim[ 1 ]    = data.iNumProcs;
    period[ 0 ] = 1;
    period[ 1 ] = 0;
    reorder     = 1;
    MPI_Cart_create( MPI_COMM_WORLD, 2, dim, period, reorder, &comm );

    if ( data.iMyRank == 0 )
    {
        int   version, subversion;
        int   ITERATIONS = 1000;
        char* env        = getenv( "ITERATIONS" );

        MPI_Get_version( &version, &subversion );
        printf( "Jacobi %d MPI-%d.%d process(es)\n", data.iNumProcs,
                version, subversion );

        if ( env )
        {
            int iterations = atoi( env );
            if ( iterations > 0 )
            {
                ITERATIONS = iterations;
            }
            else
            {
                printf( "Ignoring invalid ITERATIONS=%s!\n", env );
            }
        }

// default medium
        data.iCols      = 2000;
        data.iRows      = 2000;
        data.fAlpha     = 0.8;
        data.fRelax     = 1.0;
        data.fTolerance = 1e-10;
        data.iIterMax   = ITERATIONS;
        cout << "\n-> matrix size: " << data.iCols << "x" << data.iRows
             << "\n-> alpha: " << data.fAlpha
             << "\n-> relax: " << data.fRelax
             << "\n-> tolerance: " << data.fTolerance
             << "\n-> iterations: " << data.iIterMax << endl << endl;
    }
    /* Build MPI Datastructure */
    MPI_Datatype typelist[ 8 ] =
    { MPI_INT,    MPI_INT,    MPI_INT,    MPI_INT,    MPI_INT,
      MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE };

    int block_lengths[ 8 ];
    for ( int i = 0; i < 8; i++ )
    {
        block_lengths[ i ] = 1;
    }
    MPI_Aint displacements[ 8 ] =
    { ( MPI_Aint )offsetof( struct JacobiData, iRows ),
      ( MPI_Aint )offsetof( struct JacobiData, iCols ),
      ( MPI_Aint )offsetof( struct JacobiData, iRowFirst ),
      ( MPI_Aint )offsetof( struct JacobiData, iRowLast ),
      ( MPI_Aint )offsetof( struct JacobiData, iIterMax ),
      ( MPI_Aint )offsetof( struct JacobiData, fAlpha ),
      ( MPI_Aint )offsetof( struct JacobiData, fRelax ),
      ( MPI_Aint )offsetof( struct JacobiData, fTolerance ) };

    MPI_Datatype MPI_JacobiData;
#if ( MPI_VERSION >= 2 )
    MPI_Type_create_struct( 8, block_lengths, displacements, typelist, &MPI_JacobiData );
#else
    MPI_Type_struct( 8, block_lengths, displacements, typelist, &MPI_JacobiData );
#endif
    MPI_Type_commit( &MPI_JacobiData );

    /* Send input parameters to all procs */
    MPI_Bcast( &data, 1, MPI_JacobiData, 0, MPI_COMM_WORLD );

    /* calculate bounds for the task working area */
    data.iRowFirst = data.iMyRank * ( data.iRows - 2 ) / data.iNumProcs;
    if ( data.iMyRank == data.iNumProcs - 1 )
    {
        data.iRowLast = data.iRows - 1;
    }
    else
    {
        data.iRowLast = ( data.iMyRank + 1 ) * ( data.iRows - 2 ) / data.iNumProcs + 1;
    }

    data.afU = new double[ ( data.iRowLast - data.iRowFirst + 1 ) * data.iCols ];
    data.afF = new double[ ( data.iRowLast - data.iRowFirst + 1 ) * data.iCols ];

    // calculate dx and dy
    data.fDx = 2.0 / ( data.iCols - 1 );
    data.fDy = 2.0 / ( data.iRows - 1 );

    data.iIterCount = 0;

    return;
}

// final cleanup routines
void
Finish( JacobiData& data )
{
    delete[] data.afU;
    delete[] data.afF;

    MPI_Finalize();
    return;
}

// print result summary
void
PrintResults( const JacobiData& data )
{
    if ( data.iMyRank == 0 )
    {
        cout << " Number of iterations : " << data.iIterCount << endl;
        cout << " Residual             : " << data.fResidual << endl;
        cout << " Solution Error       : " << data.fError << endl;
        cout << " Elapsed Time         : " << data.fTimeStop - data.fTimeStart << endl;
        cout << " MFlops               : " << 0.000013 * data.iIterCount
            * ( data.iCols - 2 ) * ( data.iRows - 2 )
            / ( data.fTimeStop - data.fTimeStart ) << endl;
    }
    return;
}

// Initializes matrix
// Assumes exact solution is u(x,y) = (1-x^2)*(1-y^2)
void
InitializeMatrix( JacobiData& data )
{
    /* Initialize initial condition and RHS */
    for ( int j = data.iRowFirst; j <= data.iRowLast; j++ )
    {
        for ( int i = 0; i < data.iCols; i++ )
        {
            // TODO: check if this values have to be ints or doubles
            int xx = ( int )( -1.0 + data.fDx * i );
            int yy = ( int )( -1.0 + data.fDy * j );

            int xx2 = xx * xx;
            int yy2 = yy * yy;

            U( j, i ) = 0.0;
            F( j, i ) = -data.fAlpha * ( 1.0 - xx2 ) * ( 1.0 - yy2 )
                        + 2.0 * ( -2.0 + xx2 + yy2 );
        }
    }
}

// Checks error between numerical and exact solution
void
CheckError( JacobiData& data )
{
    double error = 0.0;

    for ( int j = data.iRowFirst; j <= data.iRowLast; j++ )
    {
        if ( ( data.iMyRank != 0 && j == data.iRowFirst ) ||
             ( data.iMyRank != data.iNumProcs - 1 && j == data.iRowLast ) )
        {
            continue;
        }

        for ( int i = 0; i < data.iCols; i++ )
        {
            double xx   = -1.0 + data.fDx * i;
            double yy   = -1.0 + data.fDy * j;
            double temp = U( j, i ) - ( 1.0 - xx * xx ) * ( 1.0 - yy * yy );
            error += temp * temp;
        }
    }

    data.fError = error;
    MPI_Reduce( &data.fError, &error, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD );
    data.fError = sqrt( error ) / ( data.iCols * data.iRows );
}


int
main( int argc, char** argv )
{
    SCOREP_USER_REGION( "main_user_instrumented", SCOREP_USER_REGION_TYPE_FUNCTION );
    int retVal = 0;    // return value

    JacobiData myData;


    // sets default values or reads from stdin
    // inits MPI and OpenMP if needed
    // distribute MPI data, calculate MPI bounds
    Init( myData, argc, argv );

    if ( myData.afU && myData.afF )
    {
        // matrix init
        InitializeMatrix( myData );

        // starting timer
        myData.fTimeStart = MPI_Wtime();

        // running calculations
        Jacobi( myData );

        // stopping timer
        myData.fTimeStop = MPI_Wtime();

        // error checking
        CheckError( myData );

        // print result summary
        PrintResults( myData );
    }
    else
    {
        cout << " Memory allocation failed ...\n";
        retVal = -1;
    }

    // cleanup
    Finish( myData );
    return retVal;
}
