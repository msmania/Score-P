/*
 * This file is part of the Score-P software (http://www.score-p.org)
 *
 * Copyright (c) 2009-2011,
 * RWTH Aachen University, Germany
 *
 * Copyright (c) 2009-2011,
 * Gesellschaft fuer numerische Simulation mbH Braunschweig, Germany
 *
 * Copyright (c) 2009-2011,
 * Technische Universitaet Dresden, Germany
 *
 * Copyright (c) 2009-2011,
 * University of Oregon, Eugene, USA
 *
 * Copyright (c) 2009-2011, 2014, 2018,
 * Forschungszentrum Juelich GmbH, Germany
 *
 * Copyright (c) 2009-2011,
 * German Research School for Simulation Sciences GmbH, Juelich/Aachen, Germany
 *
 * Copyright (c) 2009-2011,
 * Technische Universitaet Muenchen, Germany
 *
 * This software may be modified and distributed under the terms of
 * a BSD-style license. See the COPYING file in the package base
 * directory for details.
 *
 */

#ifndef SCOREP_POMP2_OPENMP_FORTRAN_H
#define SCOREP_POMP2_OPENMP_FORTRAN_H

/**
 * @file
 *
 * @ingroup OPARI2
 *
 * @brief Provides defines for function name decoration for POMP2 Fortran wrappers.
 */

#include <opari2/pomp2_lib.h>

#include "SCOREP_Fortran_Wrapper.h"

/* Fortran types */
typedef uint64_t POMP2_Region_handle_fortran;
typedef int64_t  POMP2_Task_handle_fortran;

#define SCOREP_POMP_F2C_REGION( handle ) ( ( POMP2_Region_handle* )handle )
#define SCOREP_POMP_F2C_TASK( handle ) ( ( POMP2_Task_handle* )handle )

/*
 * Fortan subroutine external name setup
 */

#define POMP2_Atomic_enter_U             POMP2_ATOMIC_ENTER
#define POMP2_Atomic_exit_U              POMP2_ATOMIC_EXIT
#define POMP2_Barrier_enter_U            POMP2_BARRIER_ENTER
#define POMP2_Barrier_exit_U             POMP2_BARRIER_EXIT
#define POMP2_Implicit_barrier_enter_U   POMP2_IMPLICIT_BARRIER_ENTER
#define POMP2_Implicit_barrier_exit_U    POMP2_IMPLICIT_BARRIER_EXIT
#define POMP2_Flush_enter_U              POMP2_FLUSH_ENTER
#define POMP2_Flush_exit_U               POMP2_FLUSH_EXIT
#define POMP2_Critical_begin_U           POMP2_CRITICAL_BEGIN
#define POMP2_Critical_end_U             POMP2_CRITICAL_END
#define POMP2_Critical_enter_U           POMP2_CRITICAL_ENTER
#define POMP2_Critical_exit_U            POMP2_CRITICAL_EXIT
#define POMP2_Do_enter_U                 POMP2_DO_ENTER
#define POMP2_Do_exit_U                  POMP2_DO_EXIT
#define POMP2_Master_begin_U             POMP2_MASTER_BEGIN
#define POMP2_Master_end_U               POMP2_MASTER_END
#define POMP2_Ordered_enter_U            POMP2_ORDERED_ENTER
#define POMP2_Ordered_exit_U             POMP2_ORDERED_EXIT
#define POMP2_Ordered_begin_U            POMP2_ORDERED_BEGIN
#define POMP2_Ordered_end_U              POMP2_ORDERED_END
#define POMP2_Parallel_begin_U           POMP2_PARALLEL_BEGIN
#define POMP2_Parallel_end_U             POMP2_PARALLEL_END
#define POMP2_Parallel_fork_U            POMP2_PARALLEL_FORK
#define POMP2_Parallel_join_U            POMP2_PARALLEL_JOIN
#define POMP2_Section_begin_U            POMP2_SECTION_BEGIN
#define POMP2_Section_end_U              POMP2_SECTION_END
#define POMP2_Sections_enter_U           POMP2_SECTIONS_ENTER
#define POMP2_Sections_exit_U            POMP2_SECTIONS_EXIT
#define POMP2_Single_begin_U             POMP2_SINGLE_BEGIN
#define POMP2_Single_end_U               POMP2_SINGLE_END
#define POMP2_Single_enter_U             POMP2_SINGLE_ENTER
#define POMP2_Single_exit_U              POMP2_SINGLE_EXIT
#define POMP2_Task_create_begin_U        POMP2_TASK_CREATE_BEGIN
#define POMP2_Task_create_end_U          POMP2_TASK_CREATE_END
#define POMP2_Task_begin_U               POMP2_TASK_BEGIN
#define POMP2_Task_end_U                 POMP2_TASK_END
#define POMP2_Untied_task_create_begin_U POMP2_UNTIED_TASK_CREATE_BEGIN
#define POMP2_Untied_task_create_end_U   POMP2_UNTIED_TASK_CREATE_END
#define POMP2_Untied_task_begin_U        POMP2_UNTIED_TASK_BEGIN
#define POMP2_Untied_task_end_U          POMP2_UNTIED_TASK_END
#define POMP2_Taskwait_begin_U           POMP2_TASKWAIT_BEGIN
#define POMP2_Taskwait_end_U             POMP2_TASKWAIT_END
#define POMP2_Workshare_enter_U          POMP2_WORKSHARE_ENTER
#define POMP2_Workshare_exit_U           POMP2_WORKSHARE_EXIT
#define POMP2_Lib_get_max_threads_U      POMP2_LIB_GET_MAX_THREADS
#define POMP2_Init_lock_U                POMP2_INIT_LOCK
#define POMP2_Destroy_lock_U             POMP2_DESTROY_LOCK
#define POMP2_Set_lock_U                 POMP2_SET_LOCK
#define POMP2_Unset_lock_U               POMP2_UNSET_LOCK
#define POMP2_Test_lock_U                POMP2_TEST_LOCK
#define POMP2_Init_nest_lock_U           POMP2_INIT_NEST_LOCK
#define POMP2_Destroy_nest_lock_U        POMP2_DESTROY_NEST_LOCK
#define POMP2_Set_nest_lock_U            POMP2_SET_NEST_LOCK
#define POMP2_Unset_nest_lock_U          POMP2_UNSET_NEST_LOCK
#define POMP2_Test_nest_lock_U           POMP2_TEST_NEST_LOCK
#define POMP2_Assign_handle_U            POMP2_ASSIGN_HANDLE

#define omp_init_lock_U         OMP_INIT_LOCK
#define omp_destroy_lock_U      OMP_DESTROY_LOCK
#define omp_set_lock_U          OMP_SET_LOCK
#define omp_unset_lock_U        OMP_UNSET_LOCK
#define omp_test_lock_U         OMP_TEST_LOCK
#define omp_init_nest_lock_U    OMP_INIT_NEST_LOCK
#define omp_destroy_nest_lock_U OMP_DESTROY_NEST_LOCK
#define omp_set_nest_lock_U     OMP_SET_NEST_LOCK
#define omp_unset_nest_lock_U   OMP_UNSET_NEST_LOCK
#define omp_test_nest_lock_U    OMP_TEST_NEST_LOCK

#define POMP2_Atomic_enter_L             pomp2_atomic_enter
#define POMP2_Atomic_exit_L              pomp2_atomic_exit
#define POMP2_Barrier_enter_L            pomp2_barrier_enter
#define POMP2_Barrier_exit_L             pomp2_barrier_exit
#define POMP2_Implicit_barrier_enter_L   pomp2_implicit_barrier_enter
#define POMP2_Implicit_barrier_exit_L    pomp2_implicit_barrier_exit
#define POMP2_Flush_enter_L              pomp2_flush_enter
#define POMP2_Flush_exit_L               pomp2_flush_exit
#define POMP2_Critical_begin_L           pomp2_critical_begin
#define POMP2_Critical_end_L             pomp2_critical_end
#define POMP2_Critical_enter_L           pomp2_critical_enter
#define POMP2_Critical_exit_L            pomp2_critical_exit
#define POMP2_Do_enter_L                 pomp2_do_enter
#define POMP2_Do_exit_L                  pomp2_do_exit
#define POMP2_Master_begin_L             pomp2_master_begin
#define POMP2_Master_end_L               pomp2_master_end
#define POMP2_Ordered_enter_L            pomp2_ordered_enter
#define POMP2_Ordered_exit_L             pomp2_ordered_exit
#define POMP2_Ordered_begin_L            pomp2_ordered_begin
#define POMP2_Ordered_end_L              pomp2_ordered_end
#define POMP2_Parallel_begin_L           pomp2_parallel_begin
#define POMP2_Parallel_end_L             pomp2_parallel_end
#define POMP2_Parallel_fork_L            pomp2_parallel_fork
#define POMP2_Parallel_join_L            pomp2_parallel_join
#define POMP2_Section_begin_L            pomp2_section_begin
#define POMP2_Section_end_L              pomp2_section_end
#define POMP2_Sections_enter_L           pomp2_sections_enter
#define POMP2_Sections_exit_L            pomp2_sections_exit
#define POMP2_Single_begin_L             pomp2_single_begin
#define POMP2_Single_end_L               pomp2_single_end
#define POMP2_Single_enter_L             pomp2_single_enter
#define POMP2_Single_exit_L              pomp2_single_exit
#define POMP2_Task_create_begin_L        pomp2_task_create_begin
#define POMP2_Task_create_end_L          pomp2_task_create_end
#define POMP2_Task_begin_L               pomp2_task_begin
#define POMP2_Task_end_L                 pomp2_task_end
#define POMP2_Untied_task_create_begin_L pomp2_untied_task_create_begin
#define POMP2_Untied_task_create_end_L   pomp2_untied_task_create_end
#define POMP2_Untied_task_begin_L        pomp2_untied_task_begin
#define POMP2_Untied_task_end_L          pomp2_untied_task_end
#define POMP2_Taskwait_begin_L           pomp2_taskwait_begin
#define POMP2_Taskwait_end_L             pomp2_taskwait_end
#define POMP2_Workshare_enter_L          pomp2_workshare_enter
#define POMP2_Workshare_exit_L           pomp2_workshare_exit
#define POMP2_Lib_get_max_threads_L      pomp2_lib_get_max_threads
#define POMP2_Init_lock_L                pomp2_init_lock
#define POMP2_Destroy_lock_L             pomp2_destroy_lock
#define POMP2_Set_lock_L                 pomp2_set_lock
#define POMP2_Unset_lock_L               pomp2_unset_lock
#define POMP2_Test_lock_L                pomp2_test_lock
#define POMP2_Init_nest_lock_L           pomp2_init_nest_lock
#define POMP2_Destroy_nest_lock_L        pomp2_destroy_nest_lock
#define POMP2_Set_nest_lock_L            pomp2_set_nest_lock
#define POMP2_Unset_nest_lock_L          pomp2_unset_nest_lock
#define POMP2_Test_nest_lock_L           pomp2_test_nest_lock
#define POMP2_Assign_handle_L            pomp2_assign_handle

#define omp_init_lock_L         omp_init_lock
#define omp_destroy_lock_L      omp_destroy_lock
#define omp_set_lock_L          omp_set_lock
#define omp_unset_lock_L        omp_unset_lock
#define omp_test_lock_L         omp_test_lock
#define omp_init_nest_lock_L    omp_init_nest_lock
#define omp_destroy_nest_lock_L omp_destroy_nest_lock
#define omp_set_nest_lock_L     omp_set_nest_lock
#define omp_unset_nest_lock_L   omp_unset_nest_lock
#define omp_test_nest_lock_L    omp_test_nest_lock

#endif /* SCOREP_POMP2_OPENMP_FORTRAN_H */
