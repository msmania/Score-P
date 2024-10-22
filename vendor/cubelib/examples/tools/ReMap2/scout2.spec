<metrics>
    <metric>
        <!-- This metric is copied from the trace analysis -->
        <disp_name>Time</disp_name>
        <uniq_name>time</uniq_name>
        <dtype>FLOAT</dtype>
        <uom>sec</uom>
        <url>@mirror@scalasca_patterns-2.2.html#time</url>
        <descr>Total CPU allocation time (includes time allocated for idle threads)</descr>
        <metric type="PREDERIVED_EXCLUSIVE">
            <disp_name>Execution</disp_name>
            <uniq_name>execution</uniq_name>
            <dtype>FLOAT</dtype>
            <uom>sec</uom>
            <url>@mirror@scalasca_patterns-2.2.html#execution</url>
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
                        if ( not
                            (
                                ( ${cube::region::name}[${regionid}] eq "TRACE BUFFER FLUSH" )
                                or
                                ( ${cube::region::name}[${regionid}] eq "TRACING" )
                            )
                        )
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
                <url>@mirror@scalasca_patterns-2.2.html#mpi</url>
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
                    <url>@mirror@scalasca_patterns-2.2.html#mpi_synchronization</url>
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
                        <url>@mirror@scalasca_patterns-2.2.html#mpi_sync_collective</url>
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
                        <metric>
                            <!-- This metric is copied from the trace analysis -->
                            <disp_name>Wait at Barrier</disp_name>
                            <uniq_name>mpi_barrier_wait</uniq_name>
                            <dtype>FLOAT</dtype>
                            <uom>sec</uom>
                            <url>@mirror@scalasca_patterns-2.2.html#mpi_barrier_wait</url>
                            <descr>Waiting time in front of MPI barriers</descr>
                        </metric>
                        <metric>
                            <!-- This metric is copied from the trace analysis -->
                            <disp_name>Barrier Completion</disp_name>
                            <uniq_name>mpi_barrier_completion</uniq_name>
                            <dtype>FLOAT</dtype>
                            <uom>sec</uom>
                            <url>@mirror@scalasca_patterns-2.2.html#mpi_barrier_completion</url>
                            <descr>Time needed to finish an MPI barrier</descr>
                        </metric>
                    </metric>
                    <metric type="PREDERIVED_EXCLUSIVE">
                        <disp_name>Remote Memory Access</disp_name>
                        <uniq_name>mpi_rma_synchronization</uniq_name>
                        <dtype>FLOAT</dtype>
                        <uom>sec</uom>
                        <url>@mirror@scalasca_patterns-2.2.html#mpi_rma_synchronization</url>
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
                            <url>@mirror@scalasca_patterns-2.2.html#mpi_rma_sync_active</url>
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
                            <metric>
                                <!-- This metric is copied from the trace analysis -->
                                <disp_name>Late Post</disp_name>
                                <uniq_name>mpi_rma_sync_late_post</uniq_name>
                                <dtype>FLOAT</dtype>
                                <uom>sec</uom>
                                <url>@mirror@scalasca_patterns-2.2.html#mpi_rma_sync_late_post</url>
                                <descr>Time spent in MPI RMA Late Post inefficiency pattern during RMA operations</descr>
                            </metric>
                            <metric>
                                <!-- This metric is copied from the trace analysis -->
                                <disp_name>Wait at Fence</disp_name>
                                <uniq_name>mpi_rma_wait_at_fence</uniq_name>
                                <dtype>FLOAT</dtype>
                                <uom>sec</uom>
                                <url>@mirror@scalasca_patterns-2.2.html#mpi_rma_wait_at_fence</url>
                                <descr>Waiting time in MPI RMA due to inherent synchronization in MPI_Win_fence</descr>
                                <metric>
                                    <!-- This metric is copied from the trace analysis -->
                                    <disp_name>Early Fence</disp_name>
                                    <uniq_name>mpi_rma_early_fence</uniq_name>
                                    <dtype>FLOAT</dtype>
                                    <uom>sec</uom>
                                    <url>@mirror@scalasca_patterns-2.2.html#mpi_rma_early_fence</url>
                                    <descr>Waiting time in MPI RMA synchronization due to pending RMA ops</descr>
                                </metric>
                            </metric>
                            <metric>
                                <!-- This metric is copied from the trace analysis -->
                                <disp_name>Early Wait</disp_name>
                                <uniq_name>mpi_rma_early_wait</uniq_name>
                                <dtype>FLOAT</dtype>
                                <uom>sec</uom>
                                <url>@mirror@scalasca_patterns-2.2.html#mpi_rma_early_wait</url>
                                <descr>Waiting time in MPI RMA general active target synchronization due to an early wait call</descr>
                                <metric>
                                    <!-- This metric is copied from the trace analysis -->
                                    <disp_name>Late Complete</disp_name>
                                    <uniq_name>mpi_rma_late_complete</uniq_name>
                                    <dtype>FLOAT</dtype>
                                    <uom>sec</uom>
                                    <url>@mirror@scalasca_patterns-2.2.html#mpi_rma_late_complete</url>
                                    <descr>Waiting time in MPI RMA general active target synchronization due to unnecessary time between last RMA op and synchronization call</descr>
                                </metric>
                            </metric>
                        </metric>
                        <metric type="PREDERIVED_EXCLUSIVE">
                            <disp_name>Passive Target</disp_name>
                            <uniq_name>mpi_rma_sync_passive</uniq_name>
                            <dtype>FLOAT</dtype>
                            <uom>sec</uom>
                            <url>@mirror@scalasca_patterns-2.2.html#mpi_rma_sync_passive</url>
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
                            <metric>
                                <!-- This metric is copied from the trace analysis -->
                                <disp_name>Lock Contention</disp_name>
                                <uniq_name>mpi_rma_sync_lock_competition</uniq_name>
                                <dtype>FLOAT</dtype>
                                <uom>sec</uom>
                                <url>@mirror@scalasca_patterns-2.2.html#mpi_rma_sync_lock_competition</url>
                                <descr>Time spent in MPI_Win_lock/MPI_Win_unlock acquiring a lock for a window</descr>
                            </metric>
                        </metric>
                        <metric>
                            <!-- This metric is copied from the trace analysis -->
                            <disp_name>Wait for Progress</disp_name>
                            <uniq_name>mpi_rma_sync_wait_for_progress</uniq_name>
                            <dtype>FLOAT</dtype>
                            <uom>sec</uom>
                            <url>@mirror@scalasca_patterns-2.2.html#mpi_rma_wait_at_create</url>
                            <descr>Time spent in MPI_Win_create, waiting for the last process to enter the call</descr>
                        </metric>
                        <metric>
                            <!-- This metric is copied from the trace analysis -->
                            <disp_name>Wait at Create</disp_name>
                            <uniq_name>mpi_rma_wait_at_create</uniq_name>
                            <dtype>FLOAT</dtype>
                            <uom>sec</uom>
                            <url>@mirror@scalasca_patterns-2.2.html#mpi_rma_sync_wait_for_progress</url>
                            <descr>Time spent waiting in MPI_Win_lock/MPI_Win_unlock waiting for progress on the target</descr>
                        </metric>
                        <metric>
                            <!-- This metric is copied from the trace analysis -->
                            <disp_name>Wait at Free</disp_name>
                            <uniq_name>mpi_rma_wait_at_free</uniq_name>
                            <dtype>FLOAT</dtype>
                            <uom>sec</uom>
                            <url>@mirror@scalasca_patterns-2.2.html#mpi_rma_wait_at_free</url>
                            <descr>Time spent in MPI_Win_free, waiting for the last process to enter the call</descr>
                        </metric>
                    </metric>
                </metric>
                <metric type="POSTDERIVED">
                    <disp_name>Communication</disp_name>
                    <uniq_name>mpi_communication</uniq_name>
                    <dtype>FLOAT</dtype>
                    <uom>sec</uom>
                    <url>@mirror@scalasca_patterns-2.2.html#mpi_communication</url>
                    <descr>Time spent in MPI communication calls</descr>
                    <cubepl>
                        metric::mpi_point2point() + metric::mpi_collective() + metric::mpi_rma_communication()
                    </cubepl>
                    <metric type="PREDERIVED_EXCLUSIVE">
                        <disp_name>Point-to-point</disp_name>
                        <uniq_name>mpi_point2point</uniq_name>
                        <dtype>FLOAT</dtype>
                        <uom>sec</uom>
                        <url>@mirror@scalasca_patterns-2.2.html#mpi_point2point</url>
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
                        <metric>
                            <!-- This metric is copied from the trace analysis -->
                            <disp_name>Late Sender</disp_name>
                            <uniq_name>mpi_latesender</uniq_name>
                            <dtype>FLOAT</dtype>
                            <uom>sec</uom>
                            <url>@mirror@scalasca_patterns-2.2.html#mpi_latesender</url>
                            <descr>Time a receiving process is waiting for a message</descr>
                            <metric>
                                <!-- This metric is copied from the trace analysis -->
                                <disp_name>Messages in Wrong Order</disp_name>
                                <uniq_name>mpi_latesender_wo</uniq_name>
                                <dtype>FLOAT</dtype>
                                <uom>sec</uom>
                                <url>@mirror@scalasca_patterns-2.2.html#mpi_latesender_wo</url>
                                <descr>Late Sender situation due to messages received in the wrong order</descr>
                                <metric>
                                    <!-- This metric is copied from the trace analysis -->
                                    <disp_name>From different sources</disp_name>
                                    <uniq_name>mpi_lswo_different</uniq_name>
                                    <dtype>FLOAT</dtype>
                                    <uom>sec</uom>
                                    <url>@mirror@scalasca_patterns-2.2.html#mpi_lswo_different</url>
                                    <descr>Wrong order situation due to messages received from different sources</descr>
                                </metric>
                                <metric>
                                    <!-- This metric is copied from the trace analysis -->
                                    <disp_name>From same source</disp_name>
                                    <uniq_name>mpi_lswo_same</uniq_name>
                                    <dtype>FLOAT</dtype>
                                    <uom>sec</uom>
                                    <url>@mirror@scalasca_patterns-2.2.html#mpi_lswo_same</url>
                                    <descr>Wrong order situation due to messages received from the same source</descr>
                                </metric>
                            </metric>
                        </metric>
                        <metric>
                            <!-- This metric is copied from the trace analysis -->
                            <disp_name>Late Receiver</disp_name>
                            <uniq_name>mpi_latereceiver</uniq_name>
                            <dtype>FLOAT</dtype>
                            <uom>sec</uom>
                            <url>@mirror@scalasca_patterns-2.2.html#mpi_latereceiver</url>
                            <descr>Time a receiving process is waiting for a message</descr>
                        </metric>
                    </metric>
                    <metric type="PREDERIVED_EXCLUSIVE">
                        <disp_name>Collective</disp_name>
                        <uniq_name>mpi_collective</uniq_name>
                        <dtype>FLOAT</dtype>
                        <uom>sec</uom>
                        <url>@mirror@scalasca_patterns-2.2.html#mpi_collective</url>
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
                        <metric>
                            <!-- This metric is copied from the trace analysis -->
                            <disp_name>Early Reduce</disp_name>
                            <uniq_name>mpi_earlyreduce</uniq_name>
                            <dtype>FLOAT</dtype>
                            <uom>sec</uom>
                            <url>@mirror@scalasca_patterns-2.2.html#mpi_earlyreduce</url>
                            <descr>Waiting time due to an early receiver in MPI n-to-1 operations</descr>
                        </metric>
                        <metric>
                            <!-- This metric is copied from the trace analysis -->
                            <disp_name>Early Scan</disp_name>
                            <uniq_name>mpi_earlyscan</uniq_name>
                            <dtype>FLOAT</dtype>
                            <uom>sec</uom>
                            <url>@mirror@scalasca_patterns-2.2.html#mpi_earlyscan</url>
                            <descr>Waiting time due to an early receiver in an MPI scan operation</descr>
                        </metric>
                        <metric>
                            <!-- This metric is copied from the trace analysis -->
                            <disp_name>Late Broadcast</disp_name>
                            <uniq_name>mpi_latebroadcast</uniq_name>
                            <dtype>FLOAT</dtype>
                            <uom>sec</uom>
                            <url>@mirror@scalasca_patterns-2.2.html#mpi_latebroadcast</url>
                            <descr>Waiting time due to a late sender in MPI 1-to-n operations</descr>
                        </metric>
                        <metric>
                            <!-- This metric is copied from the trace analysis -->
                            <disp_name>Wait at N x N</disp_name>
                            <uniq_name>mpi_wait_nxn</uniq_name>
                            <dtype>FLOAT</dtype>
                            <uom>sec</uom>
                            <url>@mirror@scalasca_patterns-2.2.html#mpi_wait_nxn</url>
                            <descr>Waiting time due to inherent synchronization in MPI n-to-n operations</descr>
                        </metric>
                        <metric>
                            <!-- This metric is copied from the trace analysis -->
                            <disp_name>N x N Completion</disp_name>
                            <uniq_name>mpi_nxn_completion</uniq_name>
                            <dtype>FLOAT</dtype>
                            <uom>sec</uom>
                            <url>@mirror@scalasca_patterns-2.2.html#mpi_nxn_completion</url>
                            <descr>Time needed to finish a N-to-N collective operation</descr>
                        </metric>
                    </metric>
                    <metric type="PREDERIVED_EXCLUSIVE">
                        <disp_name>Remote Memory Access</disp_name>
                        <uniq_name>mpi_rma_communication</uniq_name>
                        <dtype>FLOAT</dtype>
                        <uom>sec</uom>
                        <url>@mirror@scalasca_patterns-2.2.html#mpi_rma_communication</url>
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
                        <metric>
                            <!-- This metric is copied from the trace analysis -->
                            <disp_name>Late Post</disp_name>
                            <uniq_name>mpi_rma_comm_late_post</uniq_name>
                            <dtype>FLOAT</dtype>
                            <uom>sec</uom>
                            <url>@mirror@scalasca_patterns-2.2.html#mpi_rma_comm_late_post</url>
                            <descr>Time spent in MPI RMA Late Post inefficiency pattern during epoch synchronization.</descr>
                        </metric>
                        <metric>
                            <!-- This metric is copied from the trace analysis -->
                            <disp_name>Lock Contention</disp_name>
                            <uniq_name>mpi_rma_comm_lock_competition</uniq_name>
                            <dtype>FLOAT</dtype>
                            <uom>sec</uom>
                            <url>@mirror@scalasca_patterns-2.2.html#mpi_rma_comm_lock_competition</url>
                            <descr>Time spent waiting in RMA operations waiting to acquire a lock for a window in passive target synchronization</descr>
                        </metric>
                        <metric>
                            <!-- This metric is copied from the trace analysis -->
                            <disp_name>Wait for Progress</disp_name>
                            <uniq_name>mpi_rma_comm_wait_for_progress</uniq_name>
                            <dtype>FLOAT</dtype>
                            <uom>sec</uom>
                            <url>@mirror@scalasca_patterns-2.2.html#mpi_rma_comm_wait_for_progress</url>
                            <descr>Time spent waiting in MPI_Win_lock/MPI_Win_unlock waiting for progress on the target</descr>
                        </metric>
                    </metric>
                </metric>
                <metric type="PREDERIVED_EXCLUSIVE">
                    <disp_name>File I/O</disp_name>
                    <uniq_name>mpi_io</uniq_name>
                    <dtype>FLOAT</dtype>
                    <uom>sec</uom>
                    <url>@mirror@scalasca_patterns-2.2.html#mpi_io</url>
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
                        <url>@mirror@scalasca_patterns-2.2.html#mpi_io_collective</url>
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
                    <url>@mirror@scalasca_patterns-2.2.html#mpi_init_exit</url>
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
                    <metric>
                        <!-- This metric is copied from the trace analysis -->
                        <disp_name>Initialization Completion</disp_name>
                        <uniq_name>mpi_init_completion</uniq_name>
                        <dtype>FLOAT</dtype>
                        <uom>sec</uom>
                        <url>@mirror@scalasca_patterns-2.2.html#mpi_init_completion</url>
                        <descr>Time needed to finish MPI initialization</descr>
                    </metric>
                    <metric>
                        <!-- This metric is copied from the trace analysis -->
                        <disp_name>Wait at Finalize</disp_name>
                        <uniq_name>mpi_finalize_wait</uniq_name>
                        <dtype>FLOAT</dtype>
                        <uom>sec</uom>
                        <url>@mirror@scalasca_patterns-2.2.html#mpi_finalize_wait</url>
                        <descr>Waiting time in front of MPI_Finalize</descr>
                    </metric>
                </metric>
            </metric>
            <metric type="POSTDERIVED">
                <disp_name>OMP</disp_name>
                <uniq_name>omp_time</uniq_name>
                <dtype>FLOAT</dtype>
                <uom>sec</uom>
                <url>@mirror@scalasca_patterns-2.2.html#omp_time</url>
                <descr>Time spent in the OpenMP run-time system and API</descr>
                <cubepl>
                    metric::omp_flush() + metric::omp_management() + metric::omp_synchronization()
                </cubepl>
                <metric type="PREDERIVED_EXCLUSIVE">
                    <disp_name>Flush</disp_name>
                    <uniq_name>omp_flush</uniq_name>
                    <dtype>FLOAT</dtype>
                    <uom>sec</uom>
                    <url>@mirror@scalasca_patterns-2.2.html#omp_flush</url>
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
                                if ( lowercase(${cube::region::name}[${regionid}]) =~ /^!\$omp flush/ )
                                {
                                    ${omp_flush}[${i}] = 1;
                                };
                                ${i} = ${i} + 1;
                            };
                            return 0;
                        }
                    </cubeplinit>
                </metric>
                <metric>
                    <!-- This metric is copied from the trace analysis -->
                    <disp_name>Management</disp_name>
                    <uniq_name>omp_management</uniq_name>
                    <dtype>FLOAT</dtype>
                    <uom>sec</uom>
                    <url>@mirror@scalasca_patterns-2.2.html#omp_management</url>
                    <descr>Time needed to start up and shut down team of threads</descr>
                    <metric>
                        <!-- This metric is copied from the trace analysis -->
                        <disp_name>Fork</disp_name>
                        <uniq_name>omp_fork</uniq_name>
                        <dtype>FLOAT</dtype>
                        <uom>sec</uom>
                        <url>@mirror@scalasca_patterns-2.2.html#omp_fork</url>
                        <descr>Time needed to create team of threads</descr>
                    </metric>
                </metric>
                <metric type="POSTDERIVED">
                    <disp_name>Synchronization</disp_name>
                    <uniq_name>omp_synchronization</uniq_name>
                    <dtype>FLOAT</dtype>
                    <uom>sec</uom>
                    <url>@mirror@scalasca_patterns-2.2.html#omp_synchronization</url>
                    <descr>Time spent on OpenMP synchronization</descr>
                    <cubepl>
                        metric::omp_barrier() + metric::omp_critical() + metric::omp_lock_api() + metric::omp_ordered()
                    </cubepl>
                    <metric type="POSTDERIVED">
                        <disp_name>Barrier</disp_name>
                        <uniq_name>omp_barrier</uniq_name>
                        <dtype>FLOAT</dtype>
                        <uom>sec</uom>
                        <url>@mirror@scalasca_patterns-2.2.html#omp_barrier</url>
                        <descr>OpenMP barrier synchronization</descr>
                        <cubepl>
                            metric::omp_ebarrier() + metric::omp_ibarrier()
                        </cubepl>
                        <metric type="PREDERIVED_EXCLUSIVE">
                            <disp_name>Explicit</disp_name>
                            <uniq_name>omp_ebarrier</uniq_name>
                            <dtype>FLOAT</dtype>
                            <uom>sec</uom>
                            <url>@mirror@scalasca_patterns-2.2.html#omp_ebarrier</url>
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
                                        if ( lowercase(${cube::region::name}[${regionid}]) =~ /^!\$omp barrier/ )
                                        {
                                            ${omp_ebarrier}[${i}] = 1;
                                        };
                                        ${i} = ${i} + 1;
                                    };
                                    return 0;
                                }
                            </cubeplinit>
                            <metric>
                                <!-- This metric is copied from the trace analysis -->
                                <disp_name>Wait at Barrier</disp_name>
                                <uniq_name>omp_ebarrier_wait</uniq_name>
                                <dtype>FLOAT</dtype>
                                <uom>sec</uom>
                                <url>@mirror@scalasca_patterns-2.2.html#omp_ebarrier_wait</url>
                                <descr>Waiting time in front of explicit OpenMP barriers</descr>
                            </metric>
                        </metric>
                        <metric type="PREDERIVED_EXCLUSIVE">
                            <disp_name>Implicit</disp_name>
                            <uniq_name>omp_ibarrier</uniq_name>
                            <dtype>FLOAT</dtype>
                            <uom>sec</uom>
                            <url>@mirror@scalasca_patterns-2.2.html#omp_ibarrier</url>
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
                                            ( lowercase(${cube::region::name}[${regionid}]) =~ /^!\$omp implicit barrier/ )
                                            or
                                            ( lowercase(${cube::region::name}[${regionid}]) =~ /^!\$omp ibarrier/ )
                                        )
                                        {
                                            ${omp_ibarrier}[${i}] = 1;
                                        };
                                        ${i} = ${i} + 1;
                                    };
                                    return 0;
                                }
                            </cubeplinit>
                            <metric>
                                <!-- This metric is copied from the trace analysis -->
                                <disp_name>Wait at Barrier</disp_name>
                                <uniq_name>omp_ibarrier_wait</uniq_name>
                                <dtype>FLOAT</dtype>
                                <uom>sec</uom>
                                <url>@mirror@scalasca_patterns-2.2.html#omp_ibarrier_wait</url>
                                <descr>Time spent in explicit OpenMP barriers</descr>
                            </metric>
                        </metric>
                    </metric>
                    <metric type="PREDERIVED_EXCLUSIVE">
                        <disp_name>Critical</disp_name>
                        <uniq_name>omp_critical</uniq_name>
                        <dtype>FLOAT</dtype>
                        <uom>sec</uom>
                        <url>@mirror@scalasca_patterns-2.2.html#omp_critical</url>
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
                                        ( lowercase(${cube::region::name}[${regionid}]) =~ /^!\$omp atomic/ )
                                        or
                                        (
                                            ( lowercase(${cube::region::name}[${regionid}]) =~ /^!\$omp critical/ )
                                            and
                                            not ( lowercase(${cube::region::name}[${regionid}]) =~ /^!\$omp critical sblock/ )
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
                        <url>@mirror@scalasca_patterns-2.2.html#omp_lock_api</url>
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
                                        ( lowercase(${cube::region::name}[${regionid}]) =~ /^omp_/ )
                                        and
                                        ( lowercase(${cube::region::name}[${regionid}]) =~ /_lock$/ )
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
                        <url>@mirror@scalasca_patterns-2.2.html#omp_ordered</url>
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
                                    if ( lowercase(${cube::region::name}[${regionid}]) =~ /^!\$omp ordered\s@/ )
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
            <url>@mirror@scalasca_patterns-2.2.html#overhead</url>
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
                        if (
                            ( ${cube::region::name}[${regionid}] eq "TRACE BUFFER FLUSH" )
                            or
                            ( ${cube::region::name}[${regionid}] eq "TRACING" )
                        )
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
            <url>@mirror@scalasca_patterns-2.2.html#omp_idle_threads</url>
            <descr>Unused CPU reservation time</descr>
            <metric>
                <!-- This metric is still hard-coded in the Cube remapper -->
                <disp_name>Limited parallelism</disp_name>
                <uniq_name>omp_limited_parallelism</uniq_name>
                <dtype>FLOAT</dtype>
                <uom>sec</uom>
                <url>@mirror@scalasca_patterns-2.2.html#omp_limited_parallelism</url>
                <descr>Unused CPU reservation time in parallel regions due to limited parallelism</descr>
            </metric>
        </metric>
    </metric>
    <metric>
        <!-- This metric is copied from the trace analysis -->
        <disp_name>Visits</disp_name>
        <uniq_name>visits</uniq_name>
        <dtype>INTEGER</dtype>
        <uom>occ</uom>
        <url>@mirror@scalasca_patterns-2.2.html#visits</url>
        <descr>Number of visits</descr>
    </metric>
    <metric type="POSTDERIVED">
        <disp_name>Synchronizations</disp_name>
        <uniq_name>syncs</uniq_name>
        <dtype>INTEGER</dtype>
        <uom>occ</uom>
        <url>@mirror@scalasca_patterns-2.2.html#syncs</url>
        <descr>Number of synchronization operations</descr>
        <cubepl>
            metric::syncs_p2p() + metric::syncs_coll()  + metric::syncs_rma()
        </cubepl>
        <metric type="POSTDERIVED">
            <disp_name>Point-to-point</disp_name>
            <uniq_name>syncs_p2p</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>occ</uom>
            <url>@mirror@scalasca_patterns-2.2.html#syncs_p2p</url>
            <descr>Number of point-to-point synchronization operations</descr>
            <cubepl>
                metric::syncs_send() + metric::syncs_recv()
            </cubepl>
            <metric>
                <!-- This metric is copied from the trace analysis -->
                <disp_name>Sends</disp_name>
                <uniq_name>syncs_send</uniq_name>
                <dtype>INTEGER</dtype>
                <uom>occ</uom>
                <url>@mirror@scalasca_patterns-2.2.html#syncs_send</url>
                <descr>Number of point-to-point send synchronization operations</descr>
                <metric>
                    <!-- This metric is copied from the trace analysis -->
                    <disp_name>Late Receivers</disp_name>
                    <uniq_name>mpi_slr_count</uniq_name>
                    <dtype>INTEGER</dtype>
                    <uom>occ</uom>
                    <url>@mirror@scalasca_patterns-2.2.html#mpi_slr_count</url>
                    <descr>Number of Late Receiver instances in synchronizations</descr>
                </metric>
            </metric>
            <metric>
                <!-- This metric is copied from the trace analysis -->
                <disp_name>Receives</disp_name>
                <uniq_name>syncs_recv</uniq_name>
                <dtype>INTEGER</dtype>
                <uom>occ</uom>
                <url>@mirror@scalasca_patterns-2.2.html#syncs_recv</url>
                <descr>Number of point-to-point receive synchronization operations</descr>
                <metric>
                    <!-- This metric is copied from the trace analysis -->
                    <disp_name>Late Senders</disp_name>
                    <uniq_name>mpi_sls_count</uniq_name>
                    <dtype>INTEGER</dtype>
                    <uom>occ</uom>
                    <url>@mirror@scalasca_patterns-2.2.html#mpi_sls_count</url>
                    <descr>Number of Late Sender instances in synchronizations</descr>
                    <metric>
                        <!-- This metric is copied from the trace analysis -->
                        <disp_name>Messages in Wrong Order</disp_name>
                        <uniq_name>mpi_slswo_count</uniq_name>
                        <dtype>INTEGER</dtype>
                        <uom>occ</uom>
                        <url>@mirror@scalasca_patterns-2.2.html#mpi_slswo_count</url>
                        <descr>Number of Late Sender instances in synchronizations were messages are received in wrong order</descr>
                    </metric>
                </metric>
            </metric>
        </metric>
        <metric>
            <!-- This metric is copied from the trace analysis -->
            <disp_name>Collective</disp_name>
            <uniq_name>syncs_coll</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>occ</uom>
            <url>@mirror@scalasca_patterns-2.2.html#syncs_coll</url>
            <descr>Number of collective synchronization operations</descr>
        </metric>
        <metric type="POSTDERIVED">
            <disp_name>Remote Memory Access</disp_name>
            <uniq_name>syncs_rma</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>occ</uom>
            <url>@mirror@scalasca_patterns-2.2.html#syncs_rma</url>
            <descr>Number of Remote Memory Access synchronizations</descr>
            <cubepl>
                metric::syncs_fence() + metric::syncs_gats()  + metric::syncs_locks()
            </cubepl>
            <metric type="PREDERIVED_EXCLUSIVE">
                <disp_name>Fences</disp_name>
                <uniq_name>syncs_fence</uniq_name>
                <dtype>INTEGER</dtype>
                <uom>occ</uom>
                <url>@mirror@scalasca_patterns-2.2.html#syncs_fence</url>
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
                <url>@mirror@scalasca_patterns-2.2.html#syncs_gats</url>
                <descr>Number of GATS epochs</descr>
                <cubepl>
                    metric::syncs_gats_access() + metric::syncs_gats_exposure()
                </cubepl>
                <metric type="PREDERIVED_EXCLUSIVE">
                    <disp_name>Access Epochs</disp_name>
                    <uniq_name>syncs_gats_access</uniq_name>
                    <dtype>INTEGER</dtype>
                    <uom>occ</uom>
                    <url>@mirror@scalasca_patterns-2.2.html#syncs_gats_access</url>
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
                    <url>@mirror@scalasca_patterns-2.2.html#syncs_gats_exposure</url>
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
                <url>@mirror@scalasca_patterns-2.2.html#syncs_locks</url>
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
    <metric>
        <!-- This metric is copied from the trace analysis -->
        <disp_name>Pairwise synchronizations for RMA</disp_name>
        <uniq_name>mpi_rma_pairsync_count</uniq_name>
        <dtype>INTEGER</dtype>
        <uom>occ</uom>
        <url>@mirror@scalasca_patterns-2.2.html#pwsyncs</url>
        <descr>Number of pairwise synchronizations using MPI RMA</descr>
        <metric>
            <!-- This metric is copied from the trace analysis -->
            <disp_name>Unneeded synchronizations</disp_name>
            <uniq_name>mpi_rma_pairsync_unneeded_count</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>occ</uom>
            <url>@mirror@scalasca_patterns-2.2.html#pwsyncs_unneeded</url>
            <descr>Number of unneeded pairwise synchronizations using MPI RMA</descr>
        </metric>
    </metric>
    <metric type="POSTDERIVED">
        <disp_name>Communications</disp_name>
        <uniq_name>comms</uniq_name>
        <dtype>INTEGER</dtype>
        <uom>occ</uom>
        <url>@mirror@scalasca_patterns-2.2.html#comms</url>
        <descr>Number of communication operations</descr>
        <cubepl>
            metric::comms_p2p() + metric::comms_coll() + metric::comms_rma()
        </cubepl>
        <metric type="POSTDERIVED">
            <disp_name>Point-to-point</disp_name>
            <uniq_name>comms_p2p</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>occ</uom>
            <url>@mirror@scalasca_patterns-2.2.html#comms_p2p</url>
            <descr>Number of point-to-point communication operations</descr>
            <cubepl>
                metric::comms_send() + metric::comms_recv()
            </cubepl>
            <metric>
                <!-- This metric is copied from the trace analysis -->
                <disp_name>Sends</disp_name>
                <uniq_name>comms_send</uniq_name>
                <dtype>INTEGER</dtype>
                <uom>occ</uom>
                <url>@mirror@scalasca_patterns-2.2.html#comms_send</url>
                <descr>Number of point-to-point send communication operations</descr>
                <metric>
                    <!-- This metric is copied from the trace analysis -->
                    <disp_name>Late Receivers</disp_name>
                    <uniq_name>mpi_clr_count</uniq_name>
                    <dtype>INTEGER</dtype>
                    <uom>occ</uom>
                    <url>@mirror@scalasca_patterns-2.2.html#mpi_clr_count</url>
                    <descr>Number of Late Receiver instances in communications</descr>
                </metric>
            </metric>
            <metric>
                <!-- This metric is copied from the trace analysis -->
                <disp_name>Receives</disp_name>
                <uniq_name>comms_recv</uniq_name>
                <dtype>INTEGER</dtype>
                <uom>occ</uom>
                <url>@mirror@scalasca_patterns-2.2.html#comms_recv</url>
                <descr>Number of point-to-point receive communication operations</descr>
                <metric>
                    <!-- This metric is copied from the trace analysis -->
                    <disp_name>Late Senders</disp_name>
                    <uniq_name>mpi_cls_count</uniq_name>
                    <dtype>INTEGER</dtype>
                    <uom>occ</uom>
                    <url>@mirror@scalasca_patterns-2.2.html#mpi_cls_count</url>
                    <descr>Number of Late Sender instances in communications</descr>
                    <metric>
                        <!-- This metric is copied from the trace analysis -->
                        <disp_name>Messages in Wrong Order</disp_name>
                        <uniq_name>mpi_clswo_count</uniq_name>
                        <dtype>INTEGER</dtype>
                        <uom>occ</uom>
                        <url>@mirror@scalasca_patterns-2.2.html#mpi_clswo_count</url>
                        <descr>Number of Late Sender instances in communications were messages are received in wrong order</descr>
                    </metric>
                </metric>
            </metric>
        </metric>
        <metric type="POSTDERIVED">
            <disp_name>Collective</disp_name>
            <uniq_name>comms_coll</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>occ</uom>
            <url>@mirror@scalasca_patterns-2.2.html#comms_coll</url>
            <descr>Number of collective communication operations</descr>
            <cubepl>
                metric::comms_cxch() + metric::comms_csrc() + metric::comms_cdst()
            </cubepl>
            <metric>
                <!-- This metric is copied from the trace analysis -->
                <disp_name>Exchange</disp_name>
                <uniq_name>comms_cxch</uniq_name>
                <dtype>INTEGER</dtype>
                <uom>occ</uom>
                <url>@mirror@scalasca_patterns-2.2.html#comms_cxch</url>
                <descr>Number of collective communications as source and destination</descr>
            </metric>
            <metric>
                <!-- This metric is copied from the trace analysis -->
                <disp_name>As source</disp_name>
                <uniq_name>comms_csrc</uniq_name>
                <dtype>INTEGER</dtype>
                <uom>occ</uom>
                <url>@mirror@scalasca_patterns-2.2.html#comms_csrc</url>
                <descr>Number of collective communications as source</descr>
            </metric>
            <metric>
                <!-- This metric is copied from the trace analysis -->
                <disp_name>As destination</disp_name>
                <uniq_name>comms_cdst</uniq_name>
                <dtype>INTEGER</dtype>
                <uom>occ</uom>
                <url>@mirror@scalasca_patterns-2.2.html#comms_cdst</url>
                <descr>Number of collective communications as destination</descr>
            </metric>
        </metric>
        <metric type="POSTDERIVED">
            <disp_name>Remote Memory Access</disp_name>
            <uniq_name>comms_rma</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>occ</uom>
            <url>@mirror@scalasca_patterns-2.2.html#comms_rma</url>
            <descr>Number of remote memory access operations</descr>
            <cubepl>
                metric::comms_rma_gets() + metric::comms_rma_puts()
            </cubepl>
            <metric type="PREDERIVED_EXCLUSIVE">
                <disp_name>Puts</disp_name>
                <uniq_name>comms_rma_puts</uniq_name>
                <dtype>INTEGER</dtype>
                <uom>occ</uom>
                <url>@mirror@scalasca_patterns-2.2.html#comms_rma_puts</url>
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
                <url>@mirror@scalasca_patterns-2.2.html#comms_rma_gets</url>
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
        <url>@mirror@scalasca_patterns-2.2.html#bytes</url>
        <descr>Number of bytes transferred</descr>
        <cubepl>
            metric::bytes_p2p() + metric::bytes_coll() + metric::bytes_rma()
        </cubepl>
        <metric type="POSTDERIVED">
            <disp_name>Point-to-point</disp_name>
            <uniq_name>bytes_p2p</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>bytes</uom>
            <url>@mirror@scalasca_patterns-2.2.html#bytes_p2p</url>
            <descr>Number of bytes transferred in point-to-point communication operations</descr>
            <cubepl>
                metric::bytes_sent() + metric::bytes_rcvd()
            </cubepl>
            <metric>
                <!-- This metric is copied from the trace analysis -->
                <disp_name>Sent</disp_name>
                <uniq_name>bytes_sent</uniq_name>
                <dtype>INTEGER</dtype>
                <uom>bytes</uom>
                <url>@mirror@scalasca_patterns-2.2.html#bytes_sent</url>
                <descr>Number of bytes sent in point-to-point communication operations</descr>
            </metric>
            <metric>
                <!-- This metric is copied from the trace analysis -->
                <disp_name>Received</disp_name>
                <uniq_name>bytes_rcvd</uniq_name>
                <dtype>INTEGER</dtype>
                <uom>bytes</uom>
                <url>@mirror@scalasca_patterns-2.2.html#bytes_rcvd</url>
                <descr>Number of bytes received in point-to-point communication operations</descr>
            </metric>
        </metric>
        <metric type="POSTDERIVED">
            <disp_name>Collective</disp_name>
            <uniq_name>bytes_coll</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>bytes</uom>
            <url>@mirror@scalasca_patterns-2.2.html#bytes_coll</url>
            <descr>Number of bytes transferred in collective communication operations</descr>
            <cubepl>
                metric::bytes_cout() + metric::bytes_cin()
            </cubepl>
            <metric>
                <!-- This metric is copied from the trace analysis -->
                <disp_name>Outgoing</disp_name>
                <uniq_name>bytes_cout</uniq_name>
                <dtype>INTEGER</dtype>
                <uom>bytes</uom>
                <url>@mirror@scalasca_patterns-2.2.html#bytes_cout</url>
                <descr>Number of bytes outgoing in collective communication operations</descr>
            </metric>
            <metric>
                <!-- This metric is copied from the trace analysis -->
                <disp_name>Incoming</disp_name>
                <uniq_name>bytes_cin</uniq_name>
                <dtype>INTEGER</dtype>
                <uom>bytes</uom>
                <url>@mirror@scalasca_patterns-2.2.html#bytes_cin</url>
                <descr>Number of bytes incoming in collective communication operations</descr>
            </metric>
        </metric>
        <metric type="POSTDERIVED">
            <disp_name>Remote Memory Access</disp_name>
            <uniq_name>bytes_rma</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>bytes</uom>
            <url>@mirror@scalasca_patterns-2.2.html#bytes_rma</url>
            <descr>Number of bytes transferred in remote memory access operations</descr>
            <cubepl>
                metric::bytes_put() + metric::bytes_get()
            </cubepl>
            <metric>
                <!-- This metric is copied from the trace analysis -->
                <disp_name>Sent</disp_name>
                <uniq_name>bytes_put</uniq_name>
                <dtype>INTEGER</dtype>
                <uom>bytes</uom>
                <url>@mirror@scalasca_patterns-2.2.html#bytes_put</url>
                <descr>Number of bytes sent in remote memory access operations</descr>
            </metric>
            <metric>
                <!-- This metric is copied from the trace analysis -->
                <disp_name>Received</disp_name>
                <uniq_name>bytes_get</uniq_name>
                <dtype>INTEGER</dtype>
                <uom>bytes</uom>
                <url>@mirror@scalasca_patterns-2.2.html#bytes_get</url>
                <descr>Number of bytes received in remote memory access operations</descr>
            </metric>
        </metric>
    </metric>
    <metric type="PREDERIVED_EXCLUSIVE">
        <disp_name>MPI file operations</disp_name>
        <uniq_name>mpi_file_ops</uniq_name>
        <dtype>INTEGER</dtype>
        <uom>occ</uom>
        <url>@mirror@scalasca_patterns-2.2.html#mpi_file_ops</url>
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
            <url>@mirror@scalasca_patterns-2.2.html#mpi_file_iops</url>
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
                <url>@mirror@scalasca_patterns-2.2.html#mpi_file_irops</url>
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
                <url>@mirror@scalasca_patterns-2.2.html#mpi_file_iwops</url>
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
            <url>@mirror@scalasca_patterns-2.2.html#mpi_file_cops</url>
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
                <url>@mirror@scalasca_patterns-2.2.html#mpi_file_crops</url>
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
                <url>@mirror@scalasca_patterns-2.2.html#mpi_file_cwops</url>
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
        <!-- This metric is copied from the trace analysis -->
        <disp_name>Critical path</disp_name>
        <uniq_name>critical_path</uniq_name>
        <dtype>FLOAT</dtype>
        <uom>sec</uom>
        <descr>Critical-path profile</descr>
        <url>@mirror@scalasca_patterns-2.2.html#critical_path</url>
        <metric type="PREDERIVED_EXCLUSIVE">
            <disp_name>Imbalance</disp_name>
            <uniq_name>critical_path_imbalance</uniq_name>
            <dtype>FLOAT</dtype>
            <uom>sec</uom>
            <descr>Imbalanced critical-path routines</descr>
            <url>@mirror@scalasca_patterns-2.2.html#critical_path_imbalance</url>
            <cubepl>
                {
                    ${a} = 0;
                    if ( metric::critical_path(i) > 0 )
                    {
                        ${a} = max(0,
                                    ( metric::fixed::critical_path(i)-
                                        (
                                            (
                                            metric::fixed::time(i)
                                            - metric::fixed::mpi_barrier_wait(i)
                                            - metric::fixed::mpi_rma_sync_late_post(i)
                                            - metric::fixed::mpi_rma_wait_at_fence(i)
                                            - metric::fixed::mpi_rma_early_wait(i)
                                            - metric::fixed::mpi_rma_sync_wait_for_progress(i)
                                            - metric::fixed::mpi_rma_wait_at_create(i)
                                            - metric::fixed::mpi_rma_wait_at_free(i)
                                            - metric::fixed::mpi_rma_sync_lock_competition(i)
                                            - metric::fixed::mpi_latesender(i)
                                            - metric::fixed::mpi_latereceiver(i)
                                            - metric::fixed::mpi_earlyreduce(i)
                                            - metric::fixed::mpi_earlyscan(i)
                                            - metric::fixed::mpi_latebroadcast(i)
                                            - metric::fixed::mpi_wait_nxn(i)
                                            - metric::fixed::mpi_rma_comm_late_post(i)
                                            - metric::fixed::mpi_rma_comm_lock_competition(i)
                                            - metric::fixed::mpi_rma_comm_wait_for_progress(i)
                                            - metric::fixed::mpi_finalize_wait(i)
                                            - metric::fixed::omp_management(i)
                                            - metric::fixed::omp_ebarrier_wait(i)
                                            - metric::fixed::omp_ibarrier_wait(i)
                                            - metric::fixed::omp_critical(i)
                                            - metric::fixed::omp_ordered(i)
                                            - metric::fixed::omp_idle_threads(i)
                                            )
                                            / ${cube::#locations}
                                        )
                                    )
                                    / metric::fixed::critical_path(i)
                                )
                                * metric::critical_path(e);
                    };
                    return ${a};
                }
            </cubepl>
        </metric>
    </metric>
    <metric>
        <!-- This metric is still hard-coded in the Cube remapper -->
        <disp_name>Computational imbalance</disp_name>
        <uniq_name>imbalance</uniq_name>
        <dtype>FLOAT</dtype>
        <uom>sec</uom>
        <url>@mirror@scalasca_patterns-2.2.html#imbalance</url>
        <descr>Computational load imbalance heuristic (see Online Description for details)</descr>
        <metric>
            <!-- This metric is still hard-coded in the Cube remapper -->
            <disp_name>Overload</disp_name>
            <uniq_name>imbalance_above</uniq_name>
            <dtype>FLOAT</dtype>
            <uom>sec</uom>
            <url>@mirror@scalasca_patterns-2.2.html#imbalance_above</url>
            <descr>Computational load imbalance heuristic (overload)</descr>
            <metric>
                <!-- This metric is still hard-coded in the Cube remapper -->
                <disp_name>Single participant</disp_name>
                <uniq_name>imbalance_above_single</uniq_name>
                <dtype>FLOAT</dtype>
                <uom>sec</uom>
                <url>@mirror@scalasca_patterns-2.2.html#imbalance_above_single</url>
                <descr>Computational load imbalance heuristic (single participant)</descr>
            </metric>
        </metric>
        <metric>
            <!-- This metric is still hard-coded in the Cube remapper -->
            <disp_name>Underload</disp_name>
            <uniq_name>imbalance_below</uniq_name>
            <dtype>FLOAT</dtype>
            <uom>sec</uom>
            <url>@mirror@scalasca_patterns-2.2.html#imbalance_below</url>
            <descr>Computational load imbalance heuristic (underload)</descr>
            <metric>
                <!-- This metric is still hard-coded in the Cube remapper -->
                <disp_name>Non-participation</disp_name>
                <uniq_name>imbalance_below_bypass</uniq_name>
                <dtype>FLOAT</dtype>
                <uom>sec</uom>
                <url>@mirror@scalasca_patterns-2.2.html#imbalance_below_bypass</url>
                <descr>Computational load imbalance heuristic (non-participation)</descr>
                <metric>
                    <!-- This metric is still hard-coded in the Cube remapper -->
                    <disp_name>Singularity</disp_name>
                    <uniq_name>imbalance_below_singularity</uniq_name>
                    <dtype>FLOAT</dtype>
                    <uom>sec</uom>
                    <url>@mirror@scalasca_patterns-2.2.html#imbalance_below_singularity</url>
                    <descr>Computational load imbalance heuristic (non-participation in singularity)</descr>
                </metric>
            </metric>
        </metric>
    </metric>
</metrics>
