/*
 * This file is part of the Score-P software (http://www.score-p.org)
 *
 * Copyright (c) 2009-2012,
 * RWTH Aachen University, Germany
 *
 * Copyright (c) 2009-2012,
 * Gesellschaft fuer numerische Simulation mbH Braunschweig, Germany
 *
 * Copyright (c) 2009-2012, 2014,
 * Technische Universitaet Dresden, Germany
 *
 * Copyright (c) 2009-2012,
 * University of Oregon, Eugene, USA
 *
 * Copyright (c) 2009-2012, 2017, 2021
 * Forschungszentrum Juelich GmbH, Germany
 *
 * Copyright (c) 2009-2012,
 * German Research School for Simulation Sciences GmbH, Juelich/Aachen, Germany
 *
 * Copyright (c) 2009-2012,
 * Technische Universitaet Muenchen, Germany
 *
 * This software may be modified and distributed under the terms of
 * a BSD-style license.  See the COPYING file in the package base
 * directory for details.
 *
 */

#ifndef CUBELIB_ERROR_CODES_H
#define CUBELIB_ERROR_CODES_H


/**
 * @file            CUBELIB_ErrorCodes.h
 * @ingroup         CUBELIB_Exception_module
 *
 * @brief           Error codes and error handling.
 *
 */

#include <errno.h>
#include <stdint.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This is the list of error codes for CUBELIB.
 */
typedef enum
{
    /** Special marker for error messages which indicates a deprecation. */
    CUBELIB_DEPRECATED    = -3,

    /** Special marker when the application will be aborted. */
    CUBELIB_ABORT         = -2,

    /** Special marker for error messages which are only warnings. */
    CUBELIB_WARNING       = -1,

    /** Operation successful */
    CUBELIB_SUCCESS       = 0,

    /** Invalid error code
     *
     * Should only be used internally and not as an actual error code.
     */
    CUBELIB_ERROR_INVALID = 1,

    /* These are the internal implementation of POSIX error codes. */
    /** The list of arguments is too long */
    CUBELIB_ERROR_E2BIG,
    /** Not enough rights */
    CUBELIB_ERROR_EACCES,
    /** Address is not available */
    CUBELIB_ERROR_EADDRNOTAVAIL,
    /** Address family is not supported */
    CUBELIB_ERROR_EAFNOSUPPORT,
    /** Resource temporarily not available */
    CUBELIB_ERROR_EAGAIN,
    /** Connection is already processed */
    CUBELIB_ERROR_EALREADY,
    /** Invalid file pointer */
    CUBELIB_ERROR_EBADF,
    /** Invalid message */
    CUBELIB_ERROR_EBADMSG,
    /** Resource or device is busy */
    CUBELIB_ERROR_EBUSY,
    /** Operation was aborted */
    CUBELIB_ERROR_ECANCELED,
    /** No child process available */
    CUBELIB_ERROR_ECHILD,
    /** Connection was refused */
    CUBELIB_ERROR_ECONNREFUSED,
    /** Connection was reset */
    CUBELIB_ERROR_ECONNRESET,
    /** Resolved deadlock */
    CUBELIB_ERROR_EDEADLK,
    /** Destination address was expected */
    CUBELIB_ERROR_EDESTADDRREQ,
    /** Domain error */
    CUBELIB_ERROR_EDOM,
    /** Reserved */
    CUBELIB_ERROR_EDQUOT,
    /** File does already exist */
    CUBELIB_ERROR_EEXIST,
    /** Invalid address */
    CUBELIB_ERROR_EFAULT,
    /** File is too large */
    CUBELIB_ERROR_EFBIG,
    /** Operation is work in progress */
    CUBELIB_ERROR_EINPROGRESS,
    /** Interruption of an operating system call */
    CUBELIB_ERROR_EINTR,
    /** Invalid argument */
    CUBELIB_ERROR_EINVAL,
    /** Generic I/O error */
    CUBELIB_ERROR_EIO,
    /** Socket is already connected */
    CUBELIB_ERROR_EISCONN,
    /** Target is a directory */
    CUBELIB_ERROR_EISDIR,
    /** Too many layers of symbolic links */
    CUBELIB_ERROR_ELOOP,
    /** Too many opened files */
    CUBELIB_ERROR_EMFILE,
    /** Too many links */
    CUBELIB_ERROR_EMLINK,
    /** Message buffer is too small */
    CUBELIB_ERROR_EMSGSIZE,
    /** Reserved */
    CUBELIB_ERROR_EMULTIHOP,
    /** Filename is too long */
    CUBELIB_ERROR_ENAMETOOLONG,
    /** Network is down */
    CUBELIB_ERROR_ENETDOWN,
    /** Connection was reset from the network */
    CUBELIB_ERROR_ENETRESET,
    /** Network is not reachable */
    CUBELIB_ERROR_ENETUNREACH,
    /** Too many opened files */
    CUBELIB_ERROR_ENFILE,
    /** No buffer space available */
    CUBELIB_ERROR_ENOBUFS,
    /** No more data left in the queue */
    CUBELIB_ERROR_ENODATA,
    /** This device does not support this function */
    CUBELIB_ERROR_ENODEV,
    /** File or directory does not exist */
    CUBELIB_ERROR_ENOENT,
    /** Cannot execute binary */
    CUBELIB_ERROR_ENOEXEC,
    /** Locking failed */
    CUBELIB_ERROR_ENOLCK,
    /** Reserved */
    CUBELIB_ERROR_ENOLINK,
    /** Not enough main memory available */
    CUBELIB_ERROR_ENOMEM,
    /** Message has not the expected type */
    CUBELIB_ERROR_ENOMSG,
    /** This protocol is not available */
    CUBELIB_ERROR_ENOPROTOOPT,
    /** No space left on device */
    CUBELIB_ERROR_ENOSPC,
    /** No stream available */
    CUBELIB_ERROR_ENOSR,
    /** This is not a stream */
    CUBELIB_ERROR_ENOSTR,
    /** Requested function is not implemented */
    CUBELIB_ERROR_ENOSYS,
    /** Socket is not connected */
    CUBELIB_ERROR_ENOTCONN,
    /** This is not a directory */
    CUBELIB_ERROR_ENOTDIR,
    /** This directory is not empty */
    CUBELIB_ERROR_ENOTEMPTY,
    /** No socket */
    CUBELIB_ERROR_ENOTSOCK,
    /** This operation is not supported */
    CUBELIB_ERROR_ENOTSUP,
    /** This IOCTL is not supported by the device */
    CUBELIB_ERROR_ENOTTY,
    /** Device is not yet configured */
    CUBELIB_ERROR_ENXIO,
    /** Operation is not supported by this socket */
    CUBELIB_ERROR_EOPNOTSUPP,
    /** Value is to long for the datatype */
    CUBELIB_ERROR_EOVERFLOW,
    /** Operation is not permitted */
    CUBELIB_ERROR_EPERM,
    /** Broken pipe */
    CUBELIB_ERROR_EPIPE,
    /** Protocol error */
    CUBELIB_ERROR_EPROTO,
    /** Protocol is not supported */
    CUBELIB_ERROR_EPROTONOSUPPORT,
    /** Wrong protocol type for this socket */
    CUBELIB_ERROR_EPROTOTYPE,
    /** Value is out of range */
    CUBELIB_ERROR_ERANGE,
    /** Filesystem is read only */
    CUBELIB_ERROR_EROFS,
    /** This seek is not allowed */
    CUBELIB_ERROR_ESPIPE,
    /** No matching process found */
    CUBELIB_ERROR_ESRCH,
    /** Reserved */
    CUBELIB_ERROR_ESTALE,
    /** Timeout in file stream or IOCTL */
    CUBELIB_ERROR_ETIME,
    /** Connection timed out */
    CUBELIB_ERROR_ETIMEDOUT,
    /** File could not be executed while it is opened */
    CUBELIB_ERROR_ETXTBSY,
    /** Operation would be blocking */
    CUBELIB_ERROR_EWOULDBLOCK,
    /** Invalid link between devices */
    CUBELIB_ERROR_EXDEV,

    /* These are the error codes specific to the CubeLib package */

    /** Function call not allowed in current state */
    CUBELIB_ERROR_INVALID_CALL,
    /** Parameter value out of range */
    CUBELIB_ERROR_INVALID_ARGUMENT,
    /** Invalid or inconsistent record data */
    CUBELIB_ERROR_INVALID_DATA,
    /** The given size cannot be used */
    CUBELIB_ERROR_INVALID_SIZE_GIVEN,
    /** The given type is not known */
    CUBELIB_ERROR_UNKNOWN_TYPE,
    /** This could not be done with the given memory */
    CUBELIB_ERROR_MEM_FAULT,
    /** Memory allocation failed */
    CUBELIB_ERROR_MEM_ALLOC_FAILED,
    /** Index out of bounds */
    CUBELIB_ERROR_INDEX_OUT_OF_BOUNDS,
    /** Invalid source code line number */
    CUBELIB_ERROR_INVALID_LINENO,
    /** End of buffer/file reached */
    CUBELIB_ERROR_END_OF_BUFFER,
    /** Unable to open file */
    CUBELIB_ERROR_FILE_CAN_NOT_OPEN,
    /** Missing library support for requested compression mode */
    CUBELIB_ERROR_FILE_COMPRESSION_NOT_SUPPORTED,
    /** Invalid file operation */
    CUBELIB_ERROR_FILE_INTERACTION
} CUBELIB_ErrorCode;


/**
 * Returns the name of an error code.
 *
 * @param errorCode : Error Code
 *
 * @returns Returns the name of a known error code, and "INVALID_ERROR" for
 *          invalid or unknown error IDs.
 * @ingroup CUBELIB_Exception_module
 */
const char*
CUBELIB_Error_GetName( CUBELIB_ErrorCode errorCode );


/**
 * Returns the description of an error code.
 *
 * @param errorCode : Error Code
 *
 * @returns Returns the description of a known error code.
 * @ingroup CUBELIB_Exception_module
 */
const char*
CUBELIB_Error_GetDescription( CUBELIB_ErrorCode errorCode );


/**
 * Signature of error handler callback functions. The error handler can be set
 * with @ref CUBELIB_Error_RegisterCallback.
 *
 * @param userData        : Data passed to this function as given by the registration call.
 * @param file            : Name of the source-code file where the error appeared
 * @param line            : Line number in the source code where the error appeared
 * @param function        : Name of the function where the error appeared
 * @param errorCode       : Error code
 * @param msgFormatString : Format string like it is used for the printf family.
 * @param va              : Variable argument list
 *
 * @returns Should return the errorCode
 */
typedef CUBELIB_ErrorCode
( * CUBELIB_ErrorCallback )( void*             userData,
                             const char*       file,
                             uint64_t          line,
                             const char*       function,
                             CUBELIB_ErrorCode errorCode,
                             const char*       msgFormatString,
                             va_list           va );


/**
 * Register a programmers callback function for error handling.
 *
 * @param errorCallbackIn : Function which will be called instead of printing a
 *                          default message to standard error.
 * @param userData :        Data pointer passed to the callback.
 *
 * @returns Function pointer to the former error handling function.
 * @ingroup CUBELIB_Exception_module
 *
 */
CUBELIB_ErrorCallback
CUBELIB_Error_RegisterCallback( CUBELIB_ErrorCallback errorCallbackIn,
                                void*                 userData );


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* CUBELIB_ERROR_CODES_H */
