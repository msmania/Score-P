<doc>
    <mirrors>
        <murl>http://vi-hps.com/path/to/documentation</murl>
        <murl>http://vi-hps.com/path/to/documentation2</murl>
        <murl>http://vi-hps.com/path/to/documentation3</murl>
    </mirrors>
</doc>
<metrics>
    <metric>
        <!-- This metric is copied from the summary profile -->
        <disp_name>Time</disp_name>
        <uniq_name>time</uniq_name>
        <dtype>FLOAT</dtype>
        <uom>sec</uom>
        <url>@mirror@scorep_metrics-1.3-trunk.html#time</url>
        <descr>Total CPU allocation time (includes time allocated for idle threads)</descr>
        <metric type="PREDERIVED_EXCLUSIVE">
            <disp_name>Execution</disp_name>
            <uniq_name>execution</uniq_name>
            <dtype>FLOAT</dtype>
            <uom>sec</uom>
            <url>@mirror@scorep_metrics-1.3-trunk.html#execution</url>
            <descr>Execution time (does not include time allocated for idle threads)</descr>
            <cubepl>
                {
                    ${a} = 0;
                    if ( ${execution}[${calculation::callpath::id}] == 1 )
                    {
                        ${a} = metric::time(e) - metric::omp_idle_threads(e);
                    };
                    return ${a};
                }
            </cubepl>
            <cubeplinit>
                {
                    global(execution);
                    ${i} = 0;
                    while( ${i} < ${cube::#callpaths} )
                    {
                        ${execution}[${i}] = 0;
                        ${regionid} = ${cube::callpath::calleeid}[${i}] ;
                        if ( not ( ${cube::region::name}[${regionid}] eq "TRACE BUFFER FLUSH" ) )
                        {
                            ${execution}[${i}] = 1;
                        };
                        ${i} = ${i} + 1;
                    };
                    return 0;
                }
            </cubeplinit>
            <metric type="PREDERIVED_EXCLUSIVE">
                <disp_name>MPI</disp_name>
                <uniq_name>mpi</uniq_name>
                <dtype>FLOAT</dtype>
                <uom>sec</uom>
                <url>@mirror@scorep_metrics-1.3-trunk.html#mpi</url>
                <descr>Time spent in MPI calls</descr>
                <cubepl>
                    {
                        ${a} = 0;
                        if ( ${mpi}[${calculation::callpath::id}] == 1 )
                        {
                            ${a} = metric::time(e) - metric::omp_idle_threads(e);
                        };
                        return ${a};
                    }
                </cubepl>
                <cubeplinit>
                    {
                        global(mpi);
                        ${i} = 0;
                        while( ${i} < ${cube::#callpaths} )
                        {
                            ${mpi}[${i}] = 0;
                            if ( ${cube::region::mod}[${cube::callpath::calleeid}[${i}]] eq "MPI" )
                            {
                                ${mpi}[${i}] = 1;
                            };
                            ${i} = ${i} + 1;
                        };
                        return 0;
                    }
                </cubeplinit>
                <metric type="PREDERIVED_EXCLUSIVE">
                    <disp_name>Synchronization</disp_name>
                    <uniq_name>mpi_synchronization</uniq_name>
                    <dtype>FLOAT</dtype>
                    <uom>sec</uom>
                    <url>@mirror@scorep_metrics-1.3-trunk.html#mpi_synchronization</url>
                    <descr>Time spent in MPI synchronization calls</descr>
                    <cubepl>
                        {
                            ${a} = 0;
                                if ( ${mpi_synchronization}[${calculation::callpath::id}] == 1 )
                            {
                            ${a} = metric::time(e) - metric::omp_idle_threads(e);
                            };
                            return ${a};
                        }
                    </cubepl>
                    <cubeplinit>
                        {
                            global(mpi_synchronization);
                            ${i} = 0;
                            while( ${i} < ${cube::#callpaths} )
                            {
                                ${mpi_synchronization}[${i}] = 0;
                                ${regionid} = ${cube::callpath::calleeid}[${i}];
                                if (
                                    ( ${cube::region::mod}[${regionid}] eq "MPI" )
                                    and
                                    (
                                        ( ${cube::region::name}[${regionid}] seq "mpi_barrier" )
                                        or
                                        ( ${cube::region::name}[${regionid}] seq "mpi_win_post" )
                                        or
                                        ( ${cube::region::name}[${regionid}] seq "mpi_win_wait" )
                                        or
                                        ( ${cube::region::name}[${regionid}] seq "mpi_win_start" )
                                        or
                                        ( ${cube::region::name}[${regionid}] seq "mpi_win_complete" )
                                        or
                                        ( ${cube::region::name}[${regionid}] seq "mpi_win_fence" )
                                        or
                                        ( ${cube::region::name}[${regionid}] seq "mpi_win_lock" )
                                        or
                                        ( ${cube::region::name}[${regionid}] seq "mpi_win_unlock" )
                                    )
                                )
                                {
                                    ${mpi_synchronization}[${i}] = 1;
                                };
                                ${i} = ${i} + 1;
                            };
                            return 0;
                        }
                    </cubeplinit>
                    <metric type="PREDERIVED_EXCLUSIVE">
                        <disp_name>Collective</disp_name>
                        <uniq_name>mpi_sync_collective</uniq_name>
                        <dtype>FLOAT</dtype>
                        <uom>sec</uom>
                        <url>@mirror@scorep_metrics-1.3-trunk.html#mpi_sync_collective</url>
                        <descr>Time spent in MPI barriers</descr>
                        <cubepl>
                            {
                                ${a} = 0;
                                if ( ${mpi_sync_collective}[${calculation::callpath::id}] == 1 )
                                {
                                    ${a} = metric::time(e) - metric::omp_idle_threads(e);
                                };
                                return ${a};
                            }
                        </cubepl>
                        <cubeplinit>
                            {
                                global(mpi_sync_collective);
                                ${i} = 0;
                                while( ${i} < ${cube::#callpaths} )
                                {
                                    ${mpi_sync_collective}[${i}] = 0;
                                    ${regionid} = ${cube::callpath::calleeid}[${i}];
                                    if (
                                        ( ${cube::region::mod}[${regionid}] eq "MPI" )
                                        and
                                        ( ${cube::region::name}[${regionid}] seq "mpi_barrier" )
                                    )
                                    {
                                    ${mpi_sync_collective}[${i}] = 1;
                                    };
                                    ${i} = ${i} + 1;
                                };
                                return 0;
                            }
                        </cubeplinit>
                    </metric>
                    <metric type="PREDERIVED_EXCLUSIVE">
                        <disp_name>Remote Memory Access</disp_name>
                        <uniq_name>mpi_rma_synchronization</uniq_name>
                        <dtype>FLOAT</dtype>
                        <uom>sec</uom>
                        <url>@mirror@scorep_metrics-1.3-trunk.html#mpi_rma_synchronization</url>
                        <descr>Time spent in MPI RMA synchronization calls</descr>
                        <cubepl>
                            {
                                ${a} = 0;
                                if ( ${mpi_rma_synchronization}[${calculation::callpath::id}] == 1 )
                                {
                                    ${a} = metric::time(e) - metric::omp_idle_threads(e);
                                };
                                return ${a};
                            }
                        </cubepl>
                        <cubeplinit>
                            {
                                global(mpi_rma_synchronization);
                                ${i} = 0;
                                while( ${i} < ${cube::#callpaths} )
                                {
                                    ${mpi_rma_synchronization}[${i}] = 0;
                                    ${regionid} = ${cube::callpath::calleeid}[${i}];
                                    if (
                                        ( ${cube::region::mod}[${regionid}] eq "MPI" )
                                        and
                                        (
                                            ( ${cube::region::name}[${regionid}] seq "mpi_win_post" )
                                            or
                                            ( ${cube::region::name}[${regionid}] seq "mpi_win_wait" )
                                            or
                                            ( ${cube::region::name}[${regionid}] seq "mpi_win_start" )
                                            or
                                            ( ${cube::region::name}[${regionid}] seq "mpi_win_complete" )
                                            or
                                            ( ${cube::region::name}[${regionid}] seq "mpi_win_fence" )
                                            or
                                            ( ${cube::region::name}[${regionid}] seq "mpi_win_lock" )
                                            or
                                            ( ${cube::region::name}[${regionid}] seq "mpi_win_unlock" )
                                        )
                                    )
                                    {
                                        ${mpi_rma_synchronization}[${i}] = 1;
                                    };
                                    ${i} = ${i} + 1;
                                };
                                return 0;
                            }
                        </cubeplinit>
                        <metric type="PREDERIVED_EXCLUSIVE">
                            <disp_name>Active Target</disp_name>
                            <uniq_name>mpi_rma_sync_active</uniq_name>
                            <dtype>FLOAT</dtype>
                            <uom>sec</uom>
                            <url>@mirror@scorep_metrics-1.3-trunk.html#mpi_rma_sync_active</url>
                            <descr>Time spent in MPI RMA active target synchronization calls</descr>
                            <cubepl>
                                {
                                ${a} = 0;
                                if ( ${mpi_rma_sync_active}[${calculation::callpath::id}] == 1 )
                                {
                                ${a} = metric::time(e) - metric::omp_idle_threads(e);
                                };
                                return ${a};
                                }
                            </cubepl>
                            <cubeplinit>
                                {
                                    global(mpi_rma_sync_active);
                                    ${i} = 0;
                                    while( ${i} < ${cube::#callpaths} )
                                    {
                                        ${mpi_rma_sync_active}[${i}] = 0;
                                        ${regionid} = ${cube::callpath::calleeid}[${i}];
                                        if (
                                            ( ${cube::region::mod}[${regionid}] eq "MPI" )
                                            and
                                            (
                                                ( ${cube::region::name}[${regionid}] seq "mpi_win_post" )
                                                or
                                                ( ${cube::region::name}[${regionid}] seq "mpi_win_wait" )
                                                or
                                                ( ${cube::region::name}[${regionid}] seq "mpi_win_start" )
                                                or
                                                ( ${cube::region::name}[${regionid}] seq "mpi_win_complete" )
                                                or
                                                ( ${cube::region::name}[${regionid}] seq "mpi_win_fence" )
                                            )
                                        )
                                        {
                                            ${mpi_rma_sync_active}[${i}] = 1;
                                        };
                                        ${i} = ${i} + 1;
                                    };
                                    return 0;
                                }
                            </cubeplinit>
                        </metric>
                        <metric type="PREDERIVED_EXCLUSIVE">
                            <disp_name>Passive Target</disp_name>
                            <uniq_name>mpi_rma_sync_passive</uniq_name>
                            <dtype>FLOAT</dtype>
                            <uom>sec</uom>
                            <url>@mirror@scorep_metrics-1.3-trunk.html#mpi_rma_sync_passive</url>
                            <descr>Time spent in MPI RMA passive target synchronization calls</descr>
                            <cubepl>
                                {
                                    ${a} = 0;
                                    if ( ${mpi_rma_sync_passive}[${calculation::callpath::id}] == 1 )
                                    {
                                        ${a} = metric::time(e) - metric::omp_idle_threads(e);
                                    };
                                    return ${a};
                                }
                            </cubepl>
                            <cubeplinit>
                                {
                                    global(mpi_rma_sync_passive);
                                    ${i} = 0;
                                    while( ${i} < ${cube::#callpaths} )
                                    {
                                        ${mpi_rma_sync_passive}[${i}] = 0;
                                        ${regionid} = ${cube::callpath::calleeid}[${i}];
                                        if (
                                            ( ${cube::region::mod}[${regionid}] eq "MPI" )
                                            and
                                            (
                                                ( ${cube::region::name}[${regionid}] seq "mpi_win_lock" )
                                                or
                                                ( ${cube::region::name}[${regionid}] seq "mpi_win_unlock" )
                                            )
                                        )
                                        {
                                            ${mpi_rma_sync_passive}[${i}] = 1;
                                        };
                                        ${i} = ${i} + 1;
                                    };
                                    return 0;
                                }
                            </cubeplinit>
                        </metric>
                    </metric>
                </metric>
                <metric type="POSTDERIVED">
                    <disp_name>Communication</disp_name>
                    <uniq_name>mpi_communication</uniq_name>
                    <dtype>FLOAT</dtype>
                    <uom>sec</uom>
                    <url>@mirror@scorep_metrics-1.3-trunk.html#mpi_communication</url>
                    <descr>Time spent in MPI communication calls</descr>
                    <cubepl>
                        metric::mpi_point2point() + metric::mpi_collective() + metric::mpi_rma_communication()
                    </cubepl>
                    <metric type="PREDERIVED_EXCLUSIVE">
                        <disp_name>Point-to-point</disp_name>
                        <uniq_name>mpi_point2point</uniq_name>
                        <dtype>FLOAT</dtype>
                        <uom>sec</uom>
                        <url>@mirror@scorep_metrics-1.3-trunk.html#mpi_point2point</url>
                        <descr>MPI point-to-point communication</descr>
                        <cubepl>
                            {
                                ${a} = 0;
                                if ( ${mpi_point2point}[${calculation::callpath::id}] == 1 )
                                {
                                    ${a} = metric::time(e) - metric::omp_idle_threads(e);
                                };
                                return ${a};
                            }
                        </cubepl>
                        <cubeplinit>
                            {
                                global(mpi_point2point);
                                ${i} = 0;
                                while( ${i} < ${cube::#callpaths} )
                                {
                                    ${mpi_point2point}[${i}] = 0;
                                    ${regionid} = ${cube::callpath::calleeid}[${i}];
                                    if (
                                        ( ${cube::region::mod}[${regionid}] eq "MPI" )
                                        and
                                        (
                                            ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_.*buffer/ )
                                            or
                                            ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_.*cancel/ )
                                            or
                                            ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_.*get_count/ )
                                            or
                                            ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_.*probe/ )
                                            or
                                            ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_.*recv/ )
                                            or
                                            ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_.*request/ )
                                            or
                                            ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_.*send/ )
                                            or
                                            ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_test/ )
                                            or
                                            ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_wait/ )
                                            or
                                            (
                                                not ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_win/ )
                                                and
                                                ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_.*start/ )
                                            )
                                        )
                                    )
                                    {
                                    ${mpi_point2point}[${i}] = 1;
                                };
                                    ${i} = ${i} + 1;
                                };
                                return 0;
                            }
                        </cubeplinit>
                    </metric>
                    <metric type="PREDERIVED_EXCLUSIVE">
                        <disp_name>Collective</disp_name>
                        <uniq_name>mpi_collective</uniq_name>
                        <dtype>FLOAT</dtype>
                        <uom>sec</uom>
                        <url>@mirror@scorep_metrics-1.3-trunk.html#mpi_collective</url>
                        <descr>MPI collective communication</descr>
                        <cubepl>
                            {
                                ${a} = 0;
                                if ( ${mpi_collective}[${calculation::callpath::id}] == 1 )
                                {
                                    ${a} = metric::time(e) - metric::omp_idle_threads(e);
                                };
                                return ${a};
                            }
                        </cubepl>
                        <cubeplinit>
                            {
                                global(mpi_collective);
                                ${i} = 0;
                                while( ${i} < ${cube::#callpaths} )
                                {
                                    ${mpi_collective}[${i}] = 0;
                                    ${regionid} = ${cube::callpath::calleeid}[${i}];
                                    if (
                                        ( ${cube::region::mod}[${regionid}] eq "MPI" )
                                        and
                                        (
                                            ( ${cube::region::name}[${regionid}] seq "mpi_allgather" )
                                            or
                                            ( ${cube::region::name}[${regionid}] seq "mpi_allgatherv" )
                                            or
                                            ( ${cube::region::name}[${regionid}] seq "mpi_allreduce" )
                                            or
                                            ( ${cube::region::name}[${regionid}] seq "mpi_alltoall" )
                                            or
                                            ( ${cube::region::name}[${regionid}] seq "mpi_alltoallv" )
                                            or
                                            ( ${cube::region::name}[${regionid}] seq "mpi_alltoallw" )
                                            or
                                            ( ${cube::region::name}[${regionid}] seq "mpi_bcast" )
                                            or
                                            ( ${cube::region::name}[${regionid}] seq "mpi_exscan" )
                                            or
                                            ( ${cube::region::name}[${regionid}] seq "mpi_gather" )
                                            or
                                            ( ${cube::region::name}[${regionid}] seq "mpi_gatherv" )
                                            or
                                            ( ${cube::region::name}[${regionid}] seq "mpi_reduce" )
                                            or
                                            ( ${cube::region::name}[${regionid}] seq "mpi_reduce_scatter" )
                                            or
                                            ( ${cube::region::name}[${regionid}] seq "mpi_reduce_scatter_block" )
                                            or
                                            ( ${cube::region::name}[${regionid}] seq "mpi_scan" )
                                            or
                                            ( ${cube::region::name}[${regionid}] seq "mpi_scatter" )
                                            or
                                            ( ${cube::region::name}[${regionid}] seq "mpi_scatterv" )
                                        )
                                    )
                                    {
                                        ${mpi_collective}[${i}] = 1;
                                    };
                                    ${i} = ${i} + 1;
                                };
                                return 0;
                            }
                        </cubeplinit>
                    </metric>
                    <metric type="PREDERIVED_EXCLUSIVE">
                        <disp_name>Remote Memory Access</disp_name>
                        <uniq_name>mpi_rma_communication</uniq_name>
                        <dtype>FLOAT</dtype>
                        <uom>sec</uom>
                        <url>@mirror@scorep_metrics-1.3-trunk.html#mpi_rma_communication</url>
                        <descr>MPI remote memory access communication</descr>
                        <cubepl>
                            {
                                ${a} = 0;
                                if ( ${mpi_rma_communication}[${calculation::callpath::id}] == 1 )
                                {
                                    ${a} = metric::time(e) - metric::omp_idle_threads(e);
                                };
                                return ${a};
                            }
                        </cubepl>
                        <cubeplinit>
                            {
                                global(mpi_rma_communication);
                                ${i} = 0;
                                while( ${i} < ${cube::#callpaths} )
                                {
                                    ${mpi_rma_communication}[${i}] = 0;
                                    ${regionid} = ${cube::callpath::calleeid}[${i}];
                                    if (
                                        ( ${cube::region::mod}[${regionid}] eq "MPI" )
                                        and
                                        (
                                            ( ${cube::region::name}[${regionid}] seq "mpi_get" )
                                            or
                                            ( ${cube::region::name}[${regionid}] seq "mpi_put" )
                                            or
                                            ( ${cube::region::name}[${regionid}] seq "mpi_accumulate" )
                                        )
                                    )
                                    {
                                        ${mpi_rma_communication}[${i}] = 1;
                                    };
                                    ${i} = ${i} + 1;
                                };
                                return 0;
                            }
                        </cubeplinit>
                    </metric>
                </metric>
                <metric type="PREDERIVED_EXCLUSIVE">
                    <disp_name>File I/O</disp_name>
                    <uniq_name>mpi_io</uniq_name>
                    <dtype>FLOAT</dtype>
                    <uom>sec</uom>
                    <url>@mirror@scorep_metrics-1.3-trunk.html#mpi_io</url>
                    <descr>Time spent in MPI file I/O calls</descr>
                    <cubepl>
                        {
                            ${a} = 0;
                            if ( ${mpi_io}[${calculation::callpath::id}] == 1 )
                            {
                                ${a} = metric::time(e) - metric::omp_idle_threads(e);
                            };
                            return ${a};
                        }
                    </cubepl>
                    <cubeplinit>
                        {
                            global(mpi_io);
                            ${i} = 0;
                            while( ${i} < ${cube::#callpaths} )
                            {
                                ${mpi_io}[${i}] = 0;
                                ${regionid} = ${cube::callpath::calleeid}[${i}];
                                if (
                                    ( ${cube::region::mod}[${regionid}] eq "MPI" )
                                    and
                                    ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_file/ )
                                )
                                {
                                    ${mpi_io}[${i}] = 1;
                                };
                                ${i} = ${i} + 1;
                            };
                            return 0;
                        }
                    </cubeplinit>
                    <metric type="PREDERIVED_EXCLUSIVE">
                        <disp_name>Collective</disp_name>
                        <uniq_name>mpi_io_collective</uniq_name>
                        <dtype>FLOAT</dtype>
                        <uom>sec</uom>
                        <url>@mirror@scorep_metrics-1.3-trunk.html#mpi_io_collective</url>
                        <descr>Time spent in collective MPI file I/O calls</descr>
                        <cubepl>
                            {
                                ${a} = 0;
                                if ( ${mpi_io_collective}[${calculation::callpath::id}] == 1 )
                                {
                                    ${a} = metric::time(e) - metric::omp_idle_threads(e);
                                };
                                return ${a};
                            }
                        </cubepl>
                        <cubeplinit>
                            {
                                global(mpi_io_collective);
                                ${i} = 0;
                                while( ${i} < ${cube::#callpaths} )
                                {
                                    ${mpi_io_collective}[${i}] = 0;
                                    ${regionid} = ${cube::callpath::calleeid}[${i}];
                                    if (
                                        ( ${cube::region::mod}[${regionid}] eq "MPI" )
                                        and
                                        (
                                            ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_file/ )
                                            and
                                            not ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_file_set_err/ )
                                            and
                                            (
                                                ( ${cube::region::name}[${regionid}] seq "mpi_file_open" )
                                                or
                                                ( ${cube::region::name}[${regionid}] seq "mpi_file_close" )
                                                or
                                                ( ${cube::region::name}[${regionid}] seq "mpi_file_preallocate" )
                                                or
                                                ( ${cube::region::name}[${regionid}] seq "mpi_file_seek_shared" )
                                                or
                                                ( ${cube::region::name}[${regionid}] seq "mpi_file_sync" )
                                                or
                                                ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_file.*_all/ )
                                                or
                                                ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_file.*_ordered/ )
                                                or
                                                ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_file.*_set/ )
                                            )
                                        )
                                    )
                                    {
                                        ${mpi_io_collective}[${i}] = 1;
                                    };
                                    ${i} = ${i} + 1;
                                };
                                return 0;
                            }
                        </cubeplinit>
                    </metric>
                </metric>
                <metric type="PREDERIVED_EXCLUSIVE">
                    <disp_name>Init/Exit</disp_name>
                    <uniq_name>mpi_init_exit</uniq_name>
                    <dtype>FLOAT</dtype>
                    <uom>sec</uom>
                    <url>@mirror@scorep_metrics-1.3-trunk.html#mpi_init_exit</url>
                    <descr>Time spent in MPI initialization calls</descr>
                    <cubepl>
                        {
                            ${a} = 0;
                            if ( ${mpi_init_exit}[${calculation::callpath::id}] == 1 )
                            {
                                ${a} = metric::time(e) - metric::omp_idle_threads(e);
                            };
                            return ${a};
                        }
                    </cubepl>
                    <cubeplinit>
                        {
                            global(mpi_init_exit);
                            ${i} = 0;
                            while( ${i} < ${cube::#callpaths} )
                            {
                                ${mpi_init_exit}[${i}] = 0;
                                ${regionid} = ${cube::callpath::calleeid}[${i}];
                                if (
                                    ( ${cube::region::mod}[${regionid}] eq "MPI" )
                                    and
                                    (
                                        ( ${cube::region::name}[${regionid}] seq "mpi_init" )
                                        or
                                        ( ${cube::region::name}[${regionid}] seq "mpi_init_thread" )
                                        or
                                        ( ${cube::region::name}[${regionid}] seq "mpi_finalize" )
                                    )
                                )
                                {
                                    ${mpi_init_exit}[${i}] = 1;
                                };
                                ${i} = ${i} + 1;
                            };
                            return 0;
                        }
                    </cubeplinit>
                </metric>
            </metric>
            <metric type="POSTDERIVED">
                <disp_name>OMP</disp_name>
                <uniq_name>omp_time</uniq_name>
                <dtype>FLOAT</dtype>
                <uom>sec</uom>
                <url>@mirror@scorep_metrics-1.3-trunk.html#omp_time</url>
                <descr>Time spent in the OpenMP run-time system and API</descr>
                <cubepl>
                    metric::omp_flush() + metric::omp_management() + metric::omp_synchronization()
                </cubepl>
                <metric type="PREDERIVED_EXCLUSIVE">
                    <disp_name>Flush</disp_name>
                    <uniq_name>omp_flush</uniq_name>
                    <dtype>FLOAT</dtype>
                    <uom>sec</uom>
                    <url>@mirror@scorep_metrics-1.3-trunk.html#omp_flush</url>
                    <descr>Time spent in the OpenMP flush directives</descr>
                    <cubepl>
                        {
                            ${a} = 0;
                            if ( ${omp_flush}[${calculation::callpath::id}] == 1 )
                            {
                                ${a} = metric::time(e) - metric::omp_idle_threads(e);
                            };
                            return ${a};
                        }
                    </cubepl>
                    <cubeplinit>
                        {
                            global(omp_flush);
                            ${i} = 0;
                            while( ${i} < ${cube::#callpaths} )
                            {
                                ${omp_flush}[${i}] = 0;
                                ${regionid} = ${cube::callpath::calleeid}[${i}];
                                if (
                                    ( ${cube::region::description}[${regionid}] seq "openmp" )
                                    and
                                    ( lowercase(${cube::region::name}[${regionid}]) =~ /^!\$omp flush/ )
                                )
                                {
                                    ${omp_flush}[${i}] = 1;
                                };
                                ${i} = ${i} + 1;
                            };
                            return 0;
                        }
                    </cubeplinit>
                </metric>
                <metric type="PREDERIVED_EXCLUSIVE">
                    <disp_name>Management</disp_name>
                    <uniq_name>omp_management</uniq_name>
                    <dtype>FLOAT</dtype>
                    <uom>sec</uom>
                    <url>@mirror@scorep_metrics-1.3-trunk.html#omp_management</url>
                    <descr>Time needed to start up and shut down team of threads</descr>
                    <cubepl>
                        {
                            ${a} = 0;
                            if ( ${omp_management}[${calculation::callpath::id}] == 1 )
                            {
                                ${a} = metric::time(e) - metric::omp_idle_threads(e);
                            };
                            return ${a};
                        }
                    </cubepl>
                    <cubeplinit>
                        {
                            global(omp_management);
                            ${i} = 0;
                            while( ${i} < ${cube::#callpaths} )
                            {
                                ${omp_management}[${i}] = 0;
                                ${regionid} = ${cube::callpath::calleeid}[${i}];
                                if (
                                    ( ${cube::region::description}[${regionid}] seq "openmp" )
                                    and
                                    ( lowercase(${cube::region::name}[${regionid}]) =~ /^!\$omp parallel\s@/ )
                                )
                                {
                                    ${omp_management}[${i}] = 1;
                                };
                                ${i} = ${i} + 1;
                            };
                            return 0;
                        }
                    </cubeplinit>
                </metric>
                <metric type="POSTDERIVED">
                    <disp_name>Synchronization</disp_name>
                    <uniq_name>omp_synchronization</uniq_name>
                    <dtype>FLOAT</dtype>
                    <uom>sec</uom>
                    <url>@mirror@scorep_metrics-1.3-trunk.html#omp_synchronization</url>
                    <descr>Time spent on OpenMP synchronization</descr>
                    <cubepl>
                        metric::omp_barrier() + metric::omp_critical() + metric::omp_lock_api() + metric::omp_ordered()
                    </cubepl>
                    <metric type="POSTDERIVED">
                        <disp_name>Barrier</disp_name>
                        <uniq_name>omp_barrier</uniq_name>
                        <dtype>FLOAT</dtype>
                        <uom>sec</uom>
                        <url>@mirror@scorep_metrics-1.3-trunk.html#omp_barrier</url>
                        <descr>OpenMP barrier synchronization</descr>
                        <cubepl>
                            metric::omp_ebarrier() + metric::omp_ibarrier()
                        </cubepl>
                        <metric type="PREDERIVED_EXCLUSIVE">
                            <disp_name>Explicit</disp_name>
                            <uniq_name>omp_ebarrier</uniq_name>
                            <dtype>FLOAT</dtype>
                            <uom>sec</uom>
                            <url>@mirror@scorep_metrics-1.3-trunk.html#omp_ebarrier</url>
                            <descr>Time spent in explicit OpenMP barriers</descr>
                            <cubepl>
                                {
                                    ${a} = 0;
                                    if ( ${omp_ebarrier}[${calculation::callpath::id}] == 1 )
                                    {
                                        ${a} = metric::time(e) - metric::omp_idle_threads(e);
                                    };
                                    return ${a};
                                }
                            </cubepl>
                            <cubeplinit>
                                {
                                    global(omp_ebarrier);
                                    ${i} = 0;
                                    while( ${i} < ${cube::#callpaths} )
                                    {
                                        ${omp_ebarrier}[${i}] = 0;
                                        ${regionid} = ${cube::callpath::calleeid}[${i}];
                                        if (
                                            ( ${cube::region::description}[${regionid}] seq "openmp" )
                                            and
                                            ( lowercase(${cube::region::name}[${regionid}]) =~ /^!\$omp barrier/ )
                                        )
                                        {
                                            ${omp_ebarrier}[${i}] = 1;
                                        };
                                        ${i} = ${i} + 1;
                                    };
                                    return 0;
                                }
                            </cubeplinit>
                        </metric>
                        <metric type="PREDERIVED_EXCLUSIVE">
                            <disp_name>Implicit</disp_name>
                            <uniq_name>omp_ibarrier</uniq_name>
                            <dtype>FLOAT</dtype>
                            <uom>sec</uom>
                            <url>@mirror@scorep_metrics-1.3-trunk.html#omp_ibarrier</url>
                            <descr>Time spent in implicit OpenMP barriers</descr>
                            <cubepl>
                                {
                                    ${a} = 0;
                                    if ( ${omp_ibarrier}[${calculation::callpath::id}] == 1 )
                                    {
                                        ${a} = metric::time(e) - metric::omp_idle_threads(e);
                                    };
                                    return ${a};
                                }
                            </cubepl>
                            <cubeplinit>
                                {
                                    global(omp_ibarrier);
                                    ${i} = 0;
                                    while( ${i} < ${cube::#callpaths} )
                                    {
                                        ${omp_ibarrier}[${i}] = 0;
                                        ${regionid} = ${cube::callpath::calleeid}[${i}];
                                        if (
                                            ( ${cube::region::description}[${regionid}] seq "openmp" )
                                            and
                                            ( lowercase(${cube::region::name}[${regionid}]) =~ /^!\$omp implicit barrier/ )
                                        )
                                        {
                                            ${omp_ibarrier}[${i}] = 1;
                                        };
                                        ${i} = ${i} + 1;
                                    };
                                    return 0;
                                }
                            </cubeplinit>
                        </metric>
                    </metric>
                    <metric type="PREDERIVED_EXCLUSIVE">
                        <disp_name>Critical</disp_name>
                        <uniq_name>omp_critical</uniq_name>
                        <dtype>FLOAT</dtype>
                        <uom>sec</uom>
                        <url>@mirror@scorep_metrics-1.3-trunk.html#omp_critical</url>
                        <descr>Time spent in front of a critical section</descr>
                        <cubepl>
                            {
                                ${a} = 0;
                                if ( ${omp_critical}[${calculation::callpath::id}] == 1 )
                                {
                                    ${a} = metric::time(e) - metric::omp_idle_threads(e);
                                };
                                return ${a};
                            }
                        </cubepl>
                        <cubeplinit>
                            {
                                global(omp_critical);
                                ${i} = 0;
                                while( ${i} < ${cube::#callpaths} )
                                {
                                    ${omp_critical}[${i}] = 0;
                                    ${regionid} = ${cube::callpath::calleeid}[${i}];
                                    if (
                                        ( ${cube::region::description}[${regionid}] seq "openmp" )
                                        and
                                        (
                                            ( lowercase(${cube::region::name}[${regionid}]) =~ /^!\$omp atomic/ )
                                            or
                                            (
                                                ( lowercase(${cube::region::name}[${regionid}]) =~ /^!\$omp critical/ )
                                                and
                                                not ( lowercase(${cube::region::name}[${regionid}]) =~ /^!\$omp critical sblock/ )
                                            )
                                        )
                                    )
                                    {
                                        ${omp_critical}[${i}] = 1;
                                    };
                                    ${i} = ${i} + 1;
                                };
                                return 0;
                            }
                        </cubeplinit>
                    </metric>
                    <metric type="PREDERIVED_EXCLUSIVE">
                        <disp_name>Lock API</disp_name>
                        <uniq_name>omp_lock_api</uniq_name>
                        <dtype>FLOAT</dtype>
                        <uom>sec</uom>
                        <url>@mirror@scorep_metrics-1.3-trunk.html#omp_lock_api</url>
                        <descr>Time spent in OpenMP API calls dealing with locks</descr>
                        <cubepl>
                            {
                                ${a} = 0;
                                if ( ${omp_lock_api}[${calculation::callpath::id}] == 1 )
                                {
                                    ${a} = metric::time(e) - metric::omp_idle_threads(e);
                                };
                                return ${a};
                            }
                        </cubepl>
                        <cubeplinit>
                            {
                                global(omp_lock_api);
                                ${i} = 0;
                                while( ${i} < ${cube::#callpaths} )
                                {
                                    ${omp_lock_api}[${i}] = 0;
                                    ${regionid} = ${cube::callpath::calleeid}[${i}];
                                    if (
                                        ( ${cube::region::description}[${regionid}] seq "openmp" )
                                        and
                                        (
                                            ( lowercase(${cube::region::name}[${regionid}]) =~ /^omp_/ )
                                            and
                                            ( lowercase(${cube::region::name}[${regionid}]) =~ /_lock$/ )
                                        )
                                    )
                                    {
                                        ${omp_lock_api}[${i}] = 1;
                                    };
                                    ${i} = ${i} + 1;
                                };
                                return 0;
                            }
                        </cubeplinit>
                    </metric>
                    <metric type="PREDERIVED_EXCLUSIVE">
                        <disp_name>Ordered</disp_name>
                        <uniq_name>omp_ordered</uniq_name>
                        <dtype>FLOAT</dtype>
                        <uom>sec</uom>
                        <url>@mirror@scorep_metrics-1.3-trunk.html#omp_ordered</url>
                        <descr>Time spent in front of an ordered region</descr>
                        <cubepl>
                            {
                                ${a} = 0;
                                if ( ${omp_ordered}[${calculation::callpath::id}] == 1 )
                                {
                                    ${a} = metric::time(e) - metric::omp_idle_threads(e);
                                };
                                return ${a};
                            }
                        </cubepl>
                        <cubeplinit>
                            {
                                global(omp_ordered);
                                ${i} = 0;
                                while( ${i} < ${cube::#callpaths} )
                                {
                                    ${omp_ordered}[${i}] = 0;
                                    ${regionid} = ${cube::callpath::calleeid}[${i}];
                                    if (
                                        ( ${cube::region::description}[${regionid}] seq "openmp" )
                                        and
                                        ( lowercase(${cube::region::name}[${regionid}]) =~ /^!\$omp ordered\s@/ )
                                    )
                                    {
                                        ${omp_ordered}[${i}] = 1;
                                    };
                                    ${i} = ${i} + 1;
                                };
                                return 0;
                            }
                        </cubeplinit>
                    </metric>
                </metric>
            </metric>
        </metric>
        <metric type="PREDERIVED_EXCLUSIVE">
            <disp_name>Overhead</disp_name>
            <uniq_name>overhead</uniq_name>
            <dtype>FLOAT</dtype>
            <uom>sec</uom>
            <url>@mirror@scorep_metrics-1.3-trunk.html#overhead</url>
            <descr>Time spent performing tasks related to trace generation</descr>
            <cubepl>
                {
                    ${a} = 0;
                    if ( ${overhead}[${calculation::callpath::id}] == 1 )
                    {
                        ${a} = metric::time(e) - metric::omp_idle_threads(e);
                    };
                    return ${a};
                }
            </cubepl>
            <cubeplinit>
                {
                    global(overhead);
                    ${i} = 0;
                    while( ${i} < ${cube::#callpaths} )
                    {
                        ${overhead}[${i}] = 0;
                        ${regionid} = ${cube::callpath::calleeid}[${i}];
                        if ( ${cube::region::name}[${regionid}] eq "TRACE BUFFER FLUSH" )
                        {
                            ${overhead}[${i}] = 1;
                        };
                        ${i} = ${i} + 1;
                    };
                    return 0;
                }
            </cubeplinit>
        </metric>
        <metric>
            <!-- This metric is still hard-coded in the Cube remapper -->
            <disp_name>Idle threads</disp_name>
            <uniq_name>omp_idle_threads</uniq_name>
            <dtype>FLOAT</dtype>
            <uom>sec</uom>
            <url>@mirror@scorep_metrics-1.3-trunk.html#omp_idle_threads</url>
            <descr>Unused CPU reservation time</descr>
            <metric>
                <!-- This metric is still hard-coded in the Cube remapper -->
                <disp_name>Limited parallelism</disp_name>
                <uniq_name>omp_limited_parallelism</uniq_name>
                <dtype>FLOAT</dtype>
                <uom>sec</uom>
                <url>@mirror@scorep_metrics-1.3-trunk.html#omp_limited_parallelism</url>
                <descr>Unused CPU reservation time in parallel regions due to limited parallelism</descr>
            </metric>
        </metric>
    </metric>
    <metric>
        <!-- This metric is copied from the summary profile -->
        <disp_name>Visits</disp_name>
        <uniq_name>visits</uniq_name>
        <dtype>INTEGER</dtype>
        <uom>occ</uom>
        <url>@mirror@scorep_metrics-1.3-trunk.html#visits</url>
        <descr>Number of visits</descr>
    </metric>
    <metric type="POSTDERIVED">
        <disp_name>Synchronizations</disp_name>
        <uniq_name>syncs</uniq_name>
        <dtype>INTEGER</dtype>
        <uom>occ</uom>
        <url>@mirror@scorep_metrics-1.3-trunk.html#syncs</url>
        <descr>Number of synchronization operations</descr>
        <cubepl>
            metric::syncs_rma()
        </cubepl>
        <metric type="POSTDERIVED">
            <disp_name>Remote Memory Access</disp_name>
            <uniq_name>syncs_rma</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>occ</uom>
            <url>@mirror@scorep_metrics-1.3-trunk.html#syncs_rma</url>
            <descr>Number of Remote Memory Access synchronizations</descr>
            <cubepl>
                metric::syncs_fence() + metric::syncs_gats()  + metric::syncs_locks()
            </cubepl>
            <metric type="PREDERIVED_EXCLUSIVE">
                <disp_name>Fences</disp_name>
                <uniq_name>syncs_fence</uniq_name>
                <dtype>INTEGER</dtype>
                <uom>occ</uom>
                <url>@mirror@scorep_metrics-1.3-trunk.html#syncs_fence</url>
                <descr>Number of fence synchronizations</descr>
                <cubepl>
                    {
                        ${a} = 0;
                        if ( ${syncs_fence}[${calculation::callpath::id}] == 1 )
                        {
                            ${a} = metric::visits(e);
                        };
                        return ${a};
                    }
                </cubepl>
                <cubeplinit>
                    {
                        global(syncs_fence);
                        ${i} = 0;
                        while( ${i} < ${cube::#callpaths} )
                        {
                            ${syncs_fence}[${i}] = 0;
                            ${regionid} = ${cube::callpath::calleeid}[${i}];
                            if (
                                ( ${cube::region::mod}[${regionid}] eq "MPI" )
                                and
                                ( ${cube::region::name}[${regionid}] seq "mpi_win_fence" )
                            )
                            {
                                ${syncs_fence}[${i}] = 1;
                            };
                            ${i} = ${i} + 1;
                        };
                        return 0;
                    }
                </cubeplinit>
            </metric>
            <metric type="POSTDERIVED">
                <disp_name>GATS Epochs</disp_name>
                <uniq_name>syncs_gats</uniq_name>
                <dtype>INTEGER</dtype>
                <uom>occ</uom>
                <url>@mirror@scorep_metrics-1.3-trunk.html#syncs_gats</url>
                <descr>Number of GATS epochs</descr>
                <cubepl>
                    metric::syncs_gats_access() + metric::syncs_gats_exposure()
                </cubepl>
                <metric type="PREDERIVED_EXCLUSIVE">
                    <disp_name>Access Epochs</disp_name>
                    <uniq_name>syncs_gats_access</uniq_name>
                    <dtype>INTEGER</dtype>
                    <uom>occ</uom>
                    <url>@mirror@scorep_metrics-1.3-trunk.html#syncs_gats_access</url>
                    <descr>Number of access epochs</descr>
                    <cubepl>
                        {
                            ${a} = 0;
                            if ( ${syncs_gats_access}[${calculation::callpath::id}] == 1 )
                            {
                                ${a} = metric::visits(e);
                            };
                            return ${a};
                        }
                    </cubepl>
                    <cubeplinit>
                        {
                            global(syncs_gats_access);
                            ${i} = 0;
                            while( ${i} < ${cube::#callpaths} )
                            {
                                ${syncs_gats_access}[${i}] = 0;
                                ${regionid} = ${cube::callpath::calleeid}[${i}];
                                if (
                                    ( ${cube::region::mod}[${regionid}] eq "MPI" )
                                    and
                                    ( ${cube::region::name}[${regionid}] seq "mpi_win_start" )
                                )
                                {
                                    ${syncs_gats_access}[${i}] = 1;
                                };
                                ${i} = ${i} + 1;
                            };
                            return 0;
                        }
                    </cubeplinit>
                </metric>
                <metric type="PREDERIVED_EXCLUSIVE">
                    <disp_name>Exposure Epochs</disp_name>
                    <uniq_name>syncs_gats_exposure</uniq_name>
                    <dtype>INTEGER</dtype>
                    <uom>occ</uom>
                    <url>@mirror@scorep_metrics-1.3-trunk.html#syncs_gats_exposure</url>
                    <descr>Number of exposure epochs</descr>
                    <cubepl>
                        {
                            ${a} = 0;
                            if ( ${syncs_gats_exposure}[${calculation::callpath::id}] == 1 )
                            {
                                ${a} = metric::visits(e);
                            };
                            return ${a};
                        }
                    </cubepl>
                    <cubeplinit>
                        {
                            global(syncs_gats_exposure);
                            ${i} = 0;
                            while( ${i} < ${cube::#callpaths} )
                            {
                                ${syncs_gats_exposure}[${i}] = 0;
                                ${regionid} = ${cube::callpath::calleeid}[${i}];
                                if (
                                    ( ${cube::region::mod}[${regionid}] eq "MPI" )
                                    and
                                    ( ${cube::region::name}[${regionid}] seq "mpi_win_post" )
                                )
                                {
                                    ${syncs_gats_exposure}[${i}] = 1;
                                };
                                ${i} = ${i} + 1;
                            };
                            return 0;
                        }
                    </cubeplinit>
                </metric>
            </metric>
            <metric type="PREDERIVED_EXCLUSIVE">
                <disp_name>Lock Epochs</disp_name>
                <uniq_name>syncs_locks</uniq_name>
                <dtype>INTEGER</dtype>
                <uom>occ</uom>
                <url>@mirror@scorep_metrics-1.3-trunk.html#syncs_locks</url>
                <descr>Number of lock epochs</descr>
                <cubepl>
                    {
                        ${a} = 0;
                        if ( ${syncs_locks}[${calculation::callpath::id}] == 1 )
                        {
                            ${a} = metric::visits(e);
                        };
                        return ${a};
                    }
                </cubepl>
                <cubeplinit>
                    {
                        global(syncs_locks);
                        ${i} = 0;
                        while( ${i} < ${cube::#callpaths} )
                        {
                            ${syncs_locks}[${i}] = 0;
                            ${regionid} = ${cube::callpath::calleeid}[${i}];
                            if (
                                ( ${cube::region::mod}[${regionid}] eq "MPI" )
                                and
                                ( ${cube::region::name}[${regionid}] seq "mpi_win_lock" )
                            )
                            {
                                ${syncs_locks}[${i}] = 1;
                            };
                            ${i} = ${i} + 1;
                        };
                        return 0;
                    }
                </cubeplinit>
            </metric>
        </metric>
    </metric>
    <metric type="POSTDERIVED">
        <disp_name>Communications</disp_name>
        <uniq_name>comms</uniq_name>
        <dtype>INTEGER</dtype>
        <uom>occ</uom>
        <url>@mirror@scorep_metrics-1.3-trunk.html#comms</url>
        <descr>Number of communication operations</descr>
        <cubepl>
            metric::comms_rma()
        </cubepl>
        <metric type="POSTDERIVED">
            <disp_name>Remote Memory Access</disp_name>
            <uniq_name>comms_rma</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>occ</uom>
            <url>@mirror@scorep_metrics-1.3-trunk.html#comms_rma</url>
            <descr>Number of remote memory access operations</descr>
            <cubepl>
                metric::comms_rma_gets() + metric::comms_rma_puts()
            </cubepl>
            <metric type="PREDERIVED_EXCLUSIVE">
                <disp_name>Puts</disp_name>
                <uniq_name>comms_rma_puts</uniq_name>
                <dtype>INTEGER</dtype>
                <uom>occ</uom>
                <url>@mirror@scorep_metrics-1.3-trunk.html#comms_rma_puts</url>
                <descr>Number of RMA put and accumulate operations</descr>
                <cubepl>
                    {
                        ${a} = 0;
                        if ( ${comms_rma_puts}[${calculation::callpath::id}] == 1 )
                        {
                            ${a} = metric::visits(e);
                        };
                        return ${a};
                    }
                </cubepl>
                <cubeplinit>
                    {
                        global(comms_rma_puts);
                        ${i} = 0;
                        while( ${i} < ${cube::#callpaths} )
                        {
                            ${comms_rma_puts}[${i}] = 0;
                            ${regionid} = ${cube::callpath::calleeid}[${i}];
                            if (
                                ( ${cube::region::mod}[${regionid}] eq "MPI" )
                                and
                                (
                                    ( ${cube::region::name}[${regionid}] seq "mpi_put" )
                                    or
                                    ( ${cube::region::name}[${regionid}] seq "mpi_accumulate" )
                                )
                            )
                            {
                                ${comms_rma_puts}[${i}] = 1;
                            };
                            ${i} = ${i} + 1;
                        };
                        return 0;
                    }
                </cubeplinit>
            </metric>
            <metric type="PREDERIVED_EXCLUSIVE">
                <disp_name>Gets</disp_name>
                <uniq_name>comms_rma_gets</uniq_name>
                <dtype>INTEGER</dtype>
                <uom>occ</uom>
                <url>@mirror@scorep_metrics-1.3-trunk.html#comms_rma_gets</url>
                <descr>Number of RMA get operations</descr>
                <cubepl>
                    {
                        ${a} = 0;
                        if ( ${comms_rma_gets}[${calculation::callpath::id}] == 1 )
                        {
                            ${a} = metric::visits(e);
                        };
                        return ${a};
                    }
                </cubepl>
                <cubeplinit>
                    {
                        global(comms_rma_gets);
                        ${i} = 0;
                        while( ${i} < ${cube::#callpaths} )
                        {
                            ${comms_rma_gets}[${i}] = 0;
                            ${regionid} = ${cube::callpath::calleeid}[${i}];
                            if (
                                ( ${cube::region::mod}[${regionid}] eq "MPI" )
                                and
                                ( ${cube::region::name}[${regionid}] seq "mpi_get" )
                            )
                            {
                                ${comms_rma_gets}[${i}] = 1;
                            };
                            ${i} = ${i} + 1;
                        };
                        return 0;
                    }
                </cubeplinit>
            </metric>
        </metric>
    </metric>
    <metric type="POSTDERIVED">
        <disp_name>Bytes transferred</disp_name>
        <uniq_name>bytes</uniq_name>
        <dtype>INTEGER</dtype>
        <uom>bytes</uom>
        <url>@mirror@scorep_metrics-1.3-trunk.html#bytes</url>
        <descr>Number of bytes transferred</descr>
        <cubepl>
            metric::bytes_sent() + metric::bytes_received()
        </cubepl>
        <metric>
            <disp_name>Sent</disp_name>
            <uniq_name>bytes_sent</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>bytes</uom>
            <url>@mirror@scorep_metrics-1.3-trunk.html#bytes_sent</url>
            <descr>Number of bytes sent in point-to-point communication operations</descr>
            <metric type="PREDERIVED_EXCLUSIVE">
                <disp_name>Point-to-point</disp_name>
                <uniq_name>bytes_sent_p2p</uniq_name>
                <dtype>INTEGER</dtype>
                <uom>bytes</uom>
                <url>@mirror@scorep_metrics-1.3-trunk.html#bytes_sent_p2p</url>
                <descr>Number of bytes sent in point-to-point communication operations</descr>
                <cubepl>
                    {
                        ${a} = 0;
                        if ( ${bytes_sent_p2p}[${calculation::callpath::id}] == 1 )
                        {
                            ${a} = metric::bytes_sent(e);
                        };
                        return ${a};
                    }
                </cubepl>
                <cubeplinit>
                    {
                        global(bytes_sent_p2p);
                        ${i} = 0;
                        while( ${i} < ${cube::#callpaths} )
                        {
                            ${bytes_sent_p2p}[${i}] = 0;
                            ${regionid} = ${cube::callpath::calleeid}[${i}];
                            if (
                                ( ${cube::region::mod}[${regionid}] eq "MPI" )
                                and
                                (
                                    ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_.*buffer/ )
                                    or
                                    ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_.*cancel/ )
                                    or
                                    ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_.*get_count/ )
                                    or
                                    ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_.*probe/ )
                                    or
                                    ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_.*recv/ )
                                    or
                                    ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_.*request/ )
                                    or
                                    ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_.*send/ )
                                    or
                                    ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_test/ )
                                    or
                                    ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_wait/ )
                                    or
                                    (
                                        not ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_win/ )
                                        and
                                        ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_.*start/ )
                                    )
                                )
                            )
                            {
                                ${bytes_sent_p2p}[${i}] = 1;
                            };
                            ${i} = ${i} + 1;
                        };
                        return 0;
                    }
                </cubeplinit>
            </metric>
            <metric type="PREDERIVED_EXCLUSIVE">
                <disp_name>Collective</disp_name>
                <uniq_name>bytes_sent_coll</uniq_name>
                <dtype>INTEGER</dtype>
                <uom>bytes</uom>
                <url>@mirror@scorep_metrics-1.3-trunk.html#bytes_sent_coll</url>
                <descr>Number of bytes sent in collective communication operations</descr>
                <cubepl>
                    {
                        ${a} = 0;
                        if ( ${bytes_sent_coll}[${calculation::callpath::id}] == 1 )
                        {
                            ${a} = metric::bytes_sent(e);
                        };
                        return ${a};
                    }
                </cubepl>
                <cubeplinit>
                    {
                        global(bytes_sent_coll);
                        ${i} = 0;
                        while( ${i} < ${cube::#callpaths} )
                        {
                            ${bytes_sent_coll}[${i}] = 0;
                            ${regionid} = ${cube::callpath::calleeid}[${i}];
                            if (
                                ( ${cube::region::mod}[${regionid}] eq "MPI" )
                                and
                                (
                                    ( ${cube::region::name}[${regionid}] seq "mpi_allgather" )
                                    or
                                    ( ${cube::region::name}[${regionid}] seq "mpi_allgatherv" )
                                    or
                                    ( ${cube::region::name}[${regionid}] seq "mpi_allreduce" )
                                    or
                                    ( ${cube::region::name}[${regionid}] seq "mpi_alltoall" )
                                    or
                                    ( ${cube::region::name}[${regionid}] seq "mpi_alltoallv" )
                                    or
                                    ( ${cube::region::name}[${regionid}] seq "mpi_alltoallw" )
                                    or
                                    ( ${cube::region::name}[${regionid}] seq "mpi_bcast" )
                                    or
                                    ( ${cube::region::name}[${regionid}] seq "mpi_exscan" )
                                    or
                                    ( ${cube::region::name}[${regionid}] seq "mpi_gather" )
                                    or
                                    ( ${cube::region::name}[${regionid}] seq "mpi_gatherv" )
                                    or
                                    ( ${cube::region::name}[${regionid}] seq "mpi_reduce" )
                                    or
                                    ( ${cube::region::name}[${regionid}] seq "mpi_reduce_scatter" )
                                    or
                                    ( ${cube::region::name}[${regionid}] seq "mpi_reduce_scatter_block" )
                                    or
                                    ( ${cube::region::name}[${regionid}] seq "mpi_scan" )
                                    or
                                    ( ${cube::region::name}[${regionid}] seq "mpi_scatter" )
                                    or
                                    ( ${cube::region::name}[${regionid}] seq "mpi_scatterv" )
                                )
                            )
                            {
                                ${bytes_sent_coll}[${i}] = 1;
                            };
                            ${i} = ${i} + 1;
                        };
                        return 0;
                    }
                </cubeplinit>
            </metric>
        </metric>
        <metric>
            <disp_name>Received</disp_name>
            <uniq_name>bytes_received</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>bytes</uom>
            <url>@mirror@scorep_metrics-1.3-trunk.html#bytes_rcvd</url>
            <descr>Number of bytes received in point-to-point communication operations</descr>
            <metric type="PREDERIVED_EXCLUSIVE">
                <disp_name>Point-to-point</disp_name>
                <uniq_name>bytes_received_p2p</uniq_name>
                <dtype>INTEGER</dtype>
                <uom>bytes</uom>
                <url>@mirror@scorep_metrics-1.3-trunk.html#bytes_received_p2p</url>
                <descr>Number of bytes received in point-to-point communication operations</descr>
                <cubepl>
                    {
                        ${a} = 0;
                        if ( ${bytes_received_p2p}[${calculation::callpath::id}] == 1 )
                        {
                            ${a} = metric::bytes_received(e);
                        };
                        return ${a};
                    }
                </cubepl>
                <cubeplinit>
                    {
                        global(bytes_received_p2p);
                        ${i} = 0;
                        while( ${i} < ${cube::#callpaths} )
                        {
                            ${bytes_received_p2p}[${i}] = 0;
                            ${regionid} = ${cube::callpath::calleeid}[${i}];
                            if (
                                ( ${cube::region::mod}[${regionid}] eq "MPI" )
                                and
                                (
                                    ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_.*buffer/ )
                                    or
                                    ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_.*cancel/ )
                                    or
                                    ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_.*get_count/ )
                                    or
                                    ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_.*probe/ )
                                    or
                                    ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_.*recv/ )
                                    or
                                    ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_.*request/ )
                                    or
                                    ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_.*send/ )
                                    or
                                    ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_test/ )
                                    or
                                    ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_wait/ )
                                    or
                                    (
                                        not ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_win/ )
                                        and
                                        ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_.*start/ )
                                    )
                                )
                            )
                            {
                                ${bytes_received_p2p}[${i}] = 1;
                            };
                            ${i} = ${i} + 1;
                        };
                        return 0;
                    }
                </cubeplinit>
            </metric>
            <metric type="PREDERIVED_EXCLUSIVE">
                <disp_name>Collective</disp_name>
                <uniq_name>bytes_received_coll</uniq_name>
                <dtype>INTEGER</dtype>
                <uom>bytes</uom>
                <url>@mirror@scorep_metrics-1.3-trunk.html#bytes_received_coll</url>
                <descr>Number of bytes received in collective communication operations</descr>
                <cubepl>
                    {
                        ${a} = 0;
                        if ( ${bytes_received_coll}[${calculation::callpath::id}] == 1 )
                        {
                            ${a} = metric::bytes_received(e);
                        };
                        return ${a};
                    }
                </cubepl>
                <cubeplinit>
                    {
                        global(bytes_received_coll);
                        ${i} = 0;
                        while( ${i} < ${cube::#callpaths} )
                        {
                            ${bytes_received_coll}[${i}] = 0;
                            ${regionid} = ${cube::callpath::calleeid}[${i}];
                            if (
                                ( ${cube::region::mod}[${regionid}] eq "MPI" )
                                and
                                (
                                    ( ${cube::region::name}[${regionid}] seq "mpi_allgather" )
                                    or
                                    ( ${cube::region::name}[${regionid}] seq "mpi_allgatherv" )
                                    or
                                    ( ${cube::region::name}[${regionid}] seq "mpi_allreduce" )
                                    or
                                    ( ${cube::region::name}[${regionid}] seq "mpi_alltoall" )
                                    or
                                    ( ${cube::region::name}[${regionid}] seq "mpi_alltoallv" )
                                    or
                                    ( ${cube::region::name}[${regionid}] seq "mpi_alltoallw" )
                                    or
                                    ( ${cube::region::name}[${regionid}] seq "mpi_bcast" )
                                    or
                                    ( ${cube::region::name}[${regionid}] seq "mpi_exscan" )
                                    or
                                    ( ${cube::region::name}[${regionid}] seq "mpi_gather" )
                                    or
                                    ( ${cube::region::name}[${regionid}] seq "mpi_gatherv" )
                                    or
                                    ( ${cube::region::name}[${regionid}] seq "mpi_reduce" )
                                    or
                                    ( ${cube::region::name}[${regionid}] seq "mpi_reduce_scatter" )
                                    or
                                    ( ${cube::region::name}[${regionid}] seq "mpi_reduce_scatter_block" )
                                    or
                                    ( ${cube::region::name}[${regionid}] seq "mpi_scan" )
                                    or
                                    ( ${cube::region::name}[${regionid}] seq "mpi_scatter" )
                                    or
                                    ( ${cube::region::name}[${regionid}] seq "mpi_scatterv" )
                                )
                            )
                            {
                                ${bytes_received_coll}[${i}] = 1;
                            };
                            ${i} = ${i} + 1;
                        };
                        return 0;
                    }
                </cubeplinit>
            </metric>
        </metric>
    </metric>
    <metric type="PREDERIVED_EXCLUSIVE">
        <disp_name>MPI file operations</disp_name>
        <uniq_name>mpi_file_ops</uniq_name>
        <dtype>INTEGER</dtype>
        <uom>occ</uom>
        <url>@mirror@scorep_metrics-1.3-trunk.html#mpi_file_ops</url>
        <descr>Number of MPI file operations</descr>
        <cubepl>
            {
                ${a} = 0;
                if ( ${mpi_file_ops}[${calculation::callpath::id}] == 1 )
                {
                    ${a} = metric::visits(e);
                };
                return ${a};
            }
        </cubepl>
        <cubeplinit>
            {
                global(mpi_file_ops);
                ${i} = 0;
                while( ${i} < ${cube::#callpaths} )
                {
                    ${mpi_file_ops}[${i}] = 0;
                    ${regionid} = ${cube::callpath::calleeid}[${i}];
                    if (
                        ( ${cube::region::mod}[${regionid}] eq "MPI" )
                        and
                        ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_file/ )
                    )
                    {
                        ${mpi_file_ops}[${i}] = 1;
                    };
                    ${i} = ${i} + 1;
                };
                return 0;
            }
        </cubeplinit>
        <metric type="PREDERIVED_EXCLUSIVE">
            <disp_name>Individual</disp_name>
            <uniq_name>mpi_file_iops</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>occ</uom>
            <url>@mirror@scorep_metrics-1.3-trunk.html#mpi_file_iops</url>
            <descr>Number of individual MPI file operations</descr>
            <cubepl>
                {
                    ${a} = 0;
                    if ( ${mpi_file_iops}[${calculation::callpath::id}] == 1 )
                    {
                        ${a} = metric::visits(e);
                    };
                    return ${a};
                }
            </cubepl>
            <cubeplinit>
                {
                    global(mpi_file_iops);
                    ${i} = 0;
                    while( ${i} < ${cube::#callpaths} )
                    {
                        ${mpi_file_iops}[${i}] = 0;
                        ${regionid} = ${cube::callpath::calleeid}[${i}];
                        if (
                            ( ${cube::region::mod}[${regionid}] eq "MPI" )
                            and
                            (
                                ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_file/ )
                                and
                                not (
                                    not ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_file_set_err/ )
                                    and
                                    (
                                        ( ${cube::region::name}[${regionid}] seq "mpi_file_open" )
                                        or
                                        ( ${cube::region::name}[${regionid}] seq "mpi_file_close" )
                                        or
                                        ( ${cube::region::name}[${regionid}] seq "mpi_file_preallocate" )
                                        or
                                        ( ${cube::region::name}[${regionid}] seq "mpi_file_seek_shared" )
                                        or
                                        ( ${cube::region::name}[${regionid}] seq "mpi_file_sync" )
                                        or
                                        ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_file.*_all/ )
                                        or
                                        ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_file.*_ordered/ )
                                        or
                                        ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_file.*_set/ )
                                    )
                                )
                            )
                        )
                        {
                            ${mpi_file_iops}[${i}] = 1;
                        };
                        ${i} = ${i} + 1;
                    };
                    return 0;
                }
            </cubeplinit>
            <metric type="PREDERIVED_EXCLUSIVE">
                <disp_name>Reads</disp_name>
                <uniq_name>mpi_file_irops</uniq_name>
                <dtype>INTEGER</dtype>
                <uom>occ</uom>
                <url>@mirror@scorep_metrics-1.3-trunk.html#mpi_file_irops</url>
                <descr>Number of individual MPI file read operations</descr>
                <cubepl>
                    {
                        ${a} = 0;
                        if ( ${mpi_file_irops}[${calculation::callpath::id}] == 1 )
                        {
                            ${a} = metric::visits(e);
                        };
                        return ${a};
                    }
                </cubepl>
                <cubeplinit>
                    {
                        global(mpi_file_irops);
                        ${i} = 0;
                        while( ${i} < ${cube::#callpaths} )
                        {
                            ${mpi_file_irops}[${i}] = 0;
                            ${regionid} = ${cube::callpath::calleeid}[${i}];
                            if (
                                ( ${cube::region::mod}[${regionid}] eq "MPI" )
                                and
                                ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_file/ )
                                and
                                (
                                    ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_file.*read$/ )
                                    or
                                    ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_file.*read_at$/ )
                                    or
                                    ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_file.*read_shared$/ )
                                )
                            )
                            {
                                ${mpi_file_irops}[${i}] = 1;
                            };
                            ${i} = ${i} + 1;
                        };
                        return 0;
                    }
                </cubeplinit>
            </metric>
            <metric type="PREDERIVED_EXCLUSIVE">
                <disp_name>Writes</disp_name>
                <uniq_name>mpi_file_iwops</uniq_name>
                <dtype>INTEGER</dtype>
                <uom>occ</uom>
                <url>@mirror@scorep_metrics-1.3-trunk.html#mpi_file_iwops</url>
                <descr>Number of individual MPI file write operations</descr>
                <cubepl>
                    {
                        ${a} = 0;
                        if ( ${mpi_file_iwops}[${calculation::callpath::id}] == 1 )
                        {
                            ${a} = metric::visits(e);
                        };
                        return ${a};
                    }
                </cubepl>
                <cubeplinit>
                    {
                        global(mpi_file_iwops);
                        ${i} = 0;
                        while( ${i} < ${cube::#callpaths} )
                        {
                            ${mpi_file_iwops}[${i}] = 0;
                            ${regionid} = ${cube::callpath::calleeid}[${i}];
                            if (
                                ( ${cube::region::mod}[${regionid}] eq "MPI" )
                                and
                                ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_file/ )
                                and
                                (
                                    ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_file.*write$/ )
                                    or
                                    ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_file.*write_at$/ )
                                    or
                                    ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_file.*write_shared$/ )
                                )
                            )
                            {
                                ${mpi_file_iwops}[${i}] = 1;
                            };
                            ${i} = ${i} + 1;
                        };
                        return 0;
                    }
                </cubeplinit>
            </metric>
        </metric>
        <metric type="PREDERIVED_EXCLUSIVE">
            <disp_name>Collective</disp_name>
            <uniq_name>mpi_file_cops</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>occ</uom>
            <url>@mirror@scorep_metrics-1.3-trunk.html#mpi_file_cops</url>
            <descr>Number of collective MPI file operations</descr>
            <cubepl>
                {
                    ${a} = 0;
                    if ( ${mpi_file_cops}[${calculation::callpath::id}] == 1 )
                    {
                        ${a} = metric::visits(e);
                    };
                    return ${a};
                }
            </cubepl>
            <cubeplinit>
                {
                    global(mpi_file_cops);
                    ${i} = 0;
                    while( ${i} < ${cube::#callpaths} )
                    {
                        ${mpi_file_cops}[${i}] = 0;
                        ${regionid} = ${cube::callpath::calleeid}[${i}];
                        if (
                            ( ${cube::region::mod}[${regionid}] eq "MPI" )
                            and
                            (
                                ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_file/ )
                                and
                                not ( lowercase(${cube::region::name}[${regionid}]) =~  /^mpi_file_set_err/  )
                                and
                                (
                                    ( ${cube::region::name}[${regionid}] seq "mpi_file_open" )
                                    or
                                    ( ${cube::region::name}[${regionid}] seq "mpi_file_close" )
                                    or
                                    ( ${cube::region::name}[${regionid}] seq "mpi_file_preallocate" )
                                    or
                                    ( ${cube::region::name}[${regionid}] seq "mpi_file_seek_shared" )
                                    or
                                    ( ${cube::region::name}[${regionid}] seq "mpi_file_sync" )
                                    or
                                    ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_file.*_all/ )
                                    or
                                    ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_file.*_ordered/ )
                                    or
                                    ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_file.*_set/ )
                                )
                            )
                        )
                        {
                            ${mpi_file_cops}[${i}] = 1;
                        };
                        ${i} = ${i} + 1;
                    };
                    return 0;
                }
            </cubeplinit>
            <metric type="PREDERIVED_EXCLUSIVE">
                <disp_name>Reads</disp_name>
                <uniq_name>mpi_file_crops</uniq_name>
                <dtype>INTEGER</dtype>
                <uom>occ</uom>
                <url>@mirror@scorep_metrics-1.3-trunk.html#mpi_file_crops</url>
                <descr>Number of collective MPI file read operations</descr>
                <cubepl>
                    {
                        ${a} = 0;
                        if ( ${mpi_file_crops}[${calculation::callpath::id}] == 1 )
                        {
                            ${a} = metric::visits(e);
                        };
                        return ${a};
                    }
                </cubepl>
                <cubeplinit>
                    {
                        global(mpi_file_crops);
                        ${i} = 0;
                        while( ${i} < ${cube::#callpaths} )
                        {
                            ${mpi_file_crops}[${i}] = 0;
                            ${regionid} = ${cube::callpath::calleeid}[${i}];
                            if (
                                ( ${cube::region::mod}[${regionid}] eq "MPI" )
                                and
                                (
                                    ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_file_read.*_all/ )
                                    or
                                    ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_file_read.*_ordered/ )
                                )
                            )
                            {
                                ${mpi_file_crops}[${i}] = 1;
                            };
                            ${i} = ${i} + 1;
                        };
                        return 0;
                    }
                </cubeplinit>
            </metric>
            <metric type="PREDERIVED_EXCLUSIVE">
                <disp_name>Writes</disp_name>
                <uniq_name>mpi_file_cwops</uniq_name>
                <dtype>INTEGER</dtype>
                <uom>occ</uom>
                <url>@mirror@scorep_metrics-1.3-trunk.html#mpi_file_cwops</url>
                <descr>Number of collective MPI file write operations</descr>
                <cubepl>
                    {
                        ${a} = 0;
                        if ( ${mpi_file_cwops}[${calculation::callpath::id}] == 1 )
                        {
                            ${a} = metric::visits(e);
                        };
                        return ${a};
                    }
                </cubepl>
                <cubeplinit>
                    {
                        global(mpi_file_cwops);
                        ${i} = 0;
                        while( ${i} < ${cube::#callpaths} )
                        {
                            ${mpi_file_cwops}[${i}] = 0;
                            ${regionid} = ${cube::callpath::calleeid}[${i}];
                            if (
                                ( ${cube::region::mod}[${regionid}] eq "MPI" )
                                and
                                (
                                    ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_file_write.*_all/ )
                                    or
                                    ( lowercase(${cube::region::name}[${regionid}]) =~ /^mpi_file_write.*_ordered/ )
                                )
                            )
                            {
                                ${mpi_file_cwops}[${i}] = 1;
                            };
                            ${i} = ${i} + 1;
                        };
                        return 0;
                    }
                </cubeplinit>
            </metric>
        </metric>
    </metric>
    <metric>
        <disp_name>Computational imbalance</disp_name>
        <uniq_name>imbalance</uniq_name>
        <dtype>FLOAT</dtype>
        <uom>sec</uom>
        <url>@mirror@scorep_metrics-1.3-trunk.html#imbalance</url>
        <descr>Computational load imbalance heuristic (see Online Description for details)</descr>
        <metric>
            <!-- This metric is still hard-coded in the Cube remapper -->
            <disp_name>Overload</disp_name>
            <uniq_name>imbalance_above</uniq_name>
            <dtype>FLOAT</dtype>
            <uom>sec</uom>
            <url>@mirror@scorep_metrics-1.3-trunk.html#imbalance_above</url>
            <descr>Computational load imbalance heuristic (overload)</descr>
            <metric>
                <!-- This metric is still hard-coded in the Cube remapper -->
                <disp_name>Single participant</disp_name>
                <uniq_name>imbalance_above_single</uniq_name>
                <dtype>FLOAT</dtype>
                <uom>sec</uom>
                <url>@mirror@scorep_metrics-1.3-trunk.html#imbalance_above_single</url>
                <descr>Computational load imbalance heuristic (single participant)</descr>
            </metric>
        </metric>
        <metric>
            <!-- This metric is still hard-coded in the Cube remapper -->
            <disp_name>Underload</disp_name>
            <uniq_name>imbalance_below</uniq_name>
            <dtype>FLOAT</dtype>
            <uom>sec</uom>
            <url>@mirror@scorep_metrics-1.3-trunk.html#imbalance_below</url>
            <descr>Computational load imbalance heuristic (underload)</descr>
            <metric>
                <!-- This metric is still hard-coded in the Cube remapper -->
                <disp_name>Non-participation</disp_name>
                <uniq_name>imbalance_below_bypass</uniq_name>
                <dtype>FLOAT</dtype>
                <uom>sec</uom>
                <url>@mirror@scorep_metrics-1.3-trunk.html#imbalance_below_bypass</url>
                <descr>Computational load imbalance heuristic (non-participation)</descr>
                <metric>
                    <!-- This metric is still hard-coded in the Cube remapper -->
                    <disp_name>Singularity</disp_name>
                    <uniq_name>imbalance_below_singularity</uniq_name>
                    <dtype>FLOAT</dtype>
                    <uom>sec</uom>
                    <url>@mirror@scorep_metrics-1.3-trunk.html#imbalance_below_singularity</url>
                    <descr>Computational load imbalance heuristic (non-participation in singularity)</descr>
                </metric>
            </metric>
        </metric>
    </metric>
</metrics>
