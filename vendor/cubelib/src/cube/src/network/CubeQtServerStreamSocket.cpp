/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2020-2022                                                **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


/*-------------------------------------------------------------------------*/
/**
 *  @file
 *  @ingroup CUBE_gui.network
 *  @brief   Definition of the class cube::QtServerStreamSocket.
 **/
/*-------------------------------------------------------------------------*/


#include <config.h>

#include "CubeQtServerStreamSocket.h"

#include <QEventLoop>
#include <QMetaType>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include <QtGlobal>
#include <QDebug>
#include <unistd.h>

#include "CubeError.h"
#include "CubeNetworkProxy.h"

using namespace std;
using namespace cube;

#if QT_VERSION < 0x050000 // already implemented in Qt5
Q_DECLARE_METATYPE( QAbstractSocket::SocketError );
Q_DECLARE_METATYPE( QAbstractSocket::SocketState );
#endif

#define ASSERT_STATE_OF( socket, socket_state )                     \
    if ( socket->state() != socket_state )                          \
    {                                                             \
        throw UnrecoverableNetworkError( QObject::tr( "Connection timed out." ).toUtf8().data() ); \
    }

namespace
{
// default socket timeout of 1 second
int DEFAULT_TIMEOUT = 10000;
}

SocketPtr
QtServerStreamSocket::create()
{
    qRegisterMetaType< QAbstractSocket::SocketError >(
        "QAbstractSocket::SocketError" );
    qRegisterMetaType< QAbstractSocket::SocketState >(
        "QAbstractSocket::SocketState" );

    CubeNetworkProxy::exceptionPtr = nullptr;
    /*
     * A QTcpSocket cannot be accessed from different threads. When QtServerStreamSocket is created, a new thread (socketIOThread) is created
     * and it's thread affinity moved to the new thread. All read/write operations will be processed in socketIOThread.
     * If methods of CubeProxy are called from other threads, signals are used to replace direct calls.
     */
    QtServerStreamSocket* qss = new QtServerStreamSocket();
    return SocketPtr( qss  );
}


void
QtServerStreamSocket::connect( const std::string& address,
                               int                port )
{
    // calls socketConnect() in main thread, waits for slot to be finished (Qt::DirectConnection)
    socketConnect( address.c_str(), port );
}

void
QtServerStreamSocket::socketConnect( const QString& address,
                                     int            port )
{
    if ( mSocket )
    {
        if ( mSocket->isOpen() )
        {
            disconnect();
        }
    }
    else
    {
        mSocket = new QTcpSocket();
    }

    if ( !mSocket )
    {
        throw UnrecoverableNetworkError( QObject::tr( "Cannot connect on invalid socket." ).toUtf8().data() );
    }

    mSocket->connectToHost( address, port );
    mSocket->waitForConnected( 1000 );

    try
    {
        if ( mSocket->state() != QAbstractSocket::ConnectedState )
        {
            throw UnrecoverableNetworkError( QObject::tr( "Connection timed out." ).toUtf8().data() );
        }
        if ( !mSocket->isValid() )
        {
            throw UnrecoverableNetworkError( mSocket->errorString().toStdString() );
        }
    }
    catch ( const NetworkError& )
    {
        // exceptions have to be handled in a different thread
        CubeNetworkProxy::exceptionPtr = std::current_exception();
    }
}


void
QtServerStreamSocket::disconnect()
{
    disconnectSlot();
}


void
QtServerStreamSocket::disconnectSlot()
{
    if ( !mSocket || !mSocket->isValid() || !mSocket->isOpen() )
    {
        throw UnrecoverableNetworkError(
                  QObject::tr( "Attempting to disconnect invalid socket." ).toUtf8().data() );
    }

    mSocket->disconnectFromHost();
}

void
QtServerStreamSocket::listen( int port )
{
    if ( mServer )
    {
        shutdown();
    }
    else
    {
        mServer = new QTcpServer();
    }

    if ( !mServer )
    {
        throw UnrecoverableNetworkError( QObject::tr( "Cannot listen on invalid socket." ).toUtf8().data() );
    }

    mServer->listen( QHostAddress::Any, port );

    if ( !mServer->isListening() )
    {
        throw UnrecoverableNetworkError( mServer->errorString().toStdString() );
    }
}


void
QtServerStreamSocket::accept()
{
    if ( !mServer )
    {
        throw UnrecoverableNetworkError(
                  QObject::tr( "Cannot accept connections on invalid socket." ).toUtf8().data() );
    }
    do
    {
        if ( mServer->hasPendingConnections() )
        {
            break;
        }
    }
    while ( !mServer->waitForNewConnection( 100 ) );

    mSocket = mServer->nextPendingConnection();

    if ( !mSocket->isOpen() )
    {
        throw UnrecoverableNetworkError( mSocket->errorString().toStdString() );
    }
}


void
QtServerStreamSocket::shutdown()
{
    if ( !mServer )
    {
        throw UnrecoverableNetworkError( QObject::tr( "Cannot shutdown invalid socket." ).toUtf8().data() );
    }
    mServer->close();
}


/**
   QtServerStreamSocket::send() blocks calling thread and processes socketSend() in the thread socketIOThread.
 */
size_t
QtServerStreamSocket::send( const void* buffer,
                            size_t      num_bytes )
{
    socketSend( buffer, num_bytes );

    if ( cube::CubeNetworkProxy::exceptionPtr != nullptr )
    {
        std::rethrow_exception( cube::CubeNetworkProxy::exceptionPtr );
    }
    return num_bytes;
}

/**
   QtServerStreamSocket::receive() blocks calling thread and processes socketReceive() in the thread socketIOThread.
 */
size_t
QtServerStreamSocket::receive( void*  buffer,
                               size_t num_bytes )
{
    socketReceive( buffer, num_bytes );
    return num_bytes;
}


void
QtServerStreamSocket::socketSend( const void* buffer,
                                  size_t      num_bytes )
{
    if ( !mSocket || !mSocket->isValid() || !mSocket->isOpen() )
    {
        throw UnrecoverableNetworkError( QObject::tr( "Unable to write to invalid socket." ).toUtf8().data() );
    }

    qint64 bytesSent  = 0;
    qint64 totalBytes = num_bytes;

    try
    {
        while ( bytesSent < totalBytes )
        {
            qint64 res =
                mSocket->write( &static_cast< const char* >( buffer )[ bytesSent ],
                                totalBytes - bytesSent );
            mSocket->flush();

            if ( res < 0 )
            {
                throw UnrecoverableNetworkError( mSocket->errorString().toStdString() );
            }
            else
            {
                bytesSent += res;
            }

            while ( mSocket->bytesToWrite() > 0 )
            {
                ASSERT_STATE_OF( mSocket, QAbstractSocket::ConnectedState );

                if ( !mSocket->isWritable() )
                {
                    throw UnrecoverableNetworkError(
                              mSocket->errorString().toStdString() );
                }
            }
        }
    }
    catch ( const NetworkError& )
    {
        // exception has to be handled in a different thread
        CubeNetworkProxy::exceptionPtr = std::current_exception();
    }
}

void
QtServerStreamSocket::socketReceive( void*  buffer,
                                     size_t num_bytes )
{
    if ( !mSocket || !mSocket->isValid() || !mSocket->isOpen() )
    {
        throw UnrecoverableNetworkError( QObject::tr( "Unable to read from invalid socket." ).toUtf8().data() );
    }

    try
    {
        qint64 bytesRead  = 0;
        qint64 totalBytes = num_bytes;

        while ( ( bytesRead < totalBytes ) && ( mSocket->state() != QAbstractSocket::UnconnectedState ) )
        {
            while ( mSocket->waitForReadyRead( 1 ) )
            {
            }
            if ( mSocket->bytesAvailable() > 0 )
            {
                qint64 res =
                    mSocket->read( &static_cast< char* >( buffer )[ bytesRead ],
                                   qMin( totalBytes - bytesRead,
                                         mSocket->bytesAvailable() ) );
                if ( res < 0 )
                {
                    throw UnrecoverableNetworkError(
                              mSocket->errorString().toStdString() );
                }
                else
                {
                    bytesRead += res;
                }
            }
            else
            {
                ASSERT_STATE_OF( mSocket, QAbstractSocket::ConnectedState );

                if ( !mSocket->isReadable() )
                {
                    throw UnrecoverableNetworkError(
                              mSocket->errorString().toStdString() );
                }
            }
        }
    }
    catch ( const std::exception& e )
    {
        CubeNetworkProxy::exceptionPtr = std::current_exception();
    }
}


bool
QtServerStreamSocket::isConnected()
{
    if ( !mSocket )
    {
        throw UnrecoverableNetworkError( QObject::tr( "Invalid socket." ).toUtf8().data() );
    }
    bool r = mSocket->isOpen();
    return r;
}


bool
QtServerStreamSocket::isListening()
{
    if ( !mServer )
    {
        throw UnrecoverableNetworkError( QObject::tr( "Invalid socket." ).toUtf8().data() );
    }

    return mServer->isListening();
}


std::string
QtServerStreamSocket::getHostname()
{
    return QObject::tr( "Unknown host" ).toUtf8().data();
}


std::string
QtServerStreamSocket::getInfoString()
{
    return "QtServerStreamSocket";
}


QtServerStreamSocket::QtServerStreamSocket()
    : mSocket( nullptr ),
    mServer( nullptr )
{
}


QtServerStreamSocket::~QtServerStreamSocket()
{
    if ( mSocket )
    {
        if ( isConnected() )
        {
            disconnect();
        }
        delete mSocket;
    }
    if ( mServer )
    {
        if ( isListening() )
        {
            shutdown();
        }
        delete mServer;
    }
}


SocketPtr
QtServerStreamSocket::copy()
{
    QtServerStreamSocket* s = new QtServerStreamSocket();
    s->mSocket = mSocket;
    s->mServer = nullptr;
    return SocketPtr( s );
}
