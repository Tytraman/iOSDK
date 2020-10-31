/*  Copyright (c) 2014 Apple Inc.  All rights reserved.                       */

#ifndef __LA_BASE_HEADER__
#define __LA_BASE_HEADER__

#include <os/object.h>
#include <os/availability.h>
#include <stddef.h>

/*  Define abstractions for a number of attributes that we wish to be able to
    consisely attach to functions in the LinearAlgebra library.             */
#define LA_AVAILABILITY  API_AVAILABLE(macos(10.10), ios(8.0))
#define LA_NONNULL1      OS_NONNULL1
#define LA_NONNULL       OS_NONNULL_ALL
#define LA_EXPORT        OS_EXPORT
#define LA_NOTHROW       OS_NOTHROW
#define LA_FUNCTION      OS_EXPORT OS_NOTHROW
#define LA_CONST         OS_CONST

/*!
 @typedef la_attribute_t

 @abstract
 Attributes to control the behavior of operations in the LinearAlgebra library.

 @discussion
 These attributes are "sticky"; created objects inherit the inclusive-or of
 the attributes set on their parents at the point that they are created.

 @constant LA_ENABLE_LOGGING
 Computations performed using objects with this attribute print debugging
 information to stderr.
 */
#define LA_DEFAULT_ATTRIBUTES           (0)
#define LA_ATTRIBUTE_ENABLE_LOGGING     (1U << 0)
typedef unsigned long la_attribute_t;

/*!
 @typedef la_status_t

 @abstract
 Status codes for la_object_t objects.

 @discussion
 Every la_object_t object has a status.  If everything has gone well in a
 computation, the status will be LA_STATUS_SUCCESS, which is defined to
 be zero.  Status codes greater than zero indicate warnings, and codes less
 than zero indicate errors.

 Errors and warnings propagate with a computation to all descendants of the
 la_object_t object that produced them.  If a la_object_t object receives an 
 error or warning from both parents, one of them will take precedence over the
 other.  The exact precedence ranking is not defined, but errors always
 supercede warnings.

 @constant LA_SUCCESS
 There are no errors or warnings associated with the la_object_t object.

 @constant LA_WARNING_POORLY_CONDITIONED
 One or more parts of the computation was poorly conditioned numerically, and
 the results are signficantly less accurate than might otherwise expected.

 @constant LA_INTERNAL_ERROR
 An error was encountered internal to the LinearAlgebra library.  For example, 
 an allocation failed, or memory was corrupted.

 @constant LA_INVALID_PARAMETER_ERROR
 An invalid parameter was passed to the function that created this object or
 one of it's ancestors.

 @constant LA_DIMENSION_MISMATCH_ERROR
 The function that created this object or one of its ancestors was passed
 arguments whose dimensions were not compatibile.  For example, this error
 might be generated by attempting to add a 63-element vector to a 135-element
 vector, or to multiply a 10x4 matrix by a 7x128 matrix.

 @constant LA_PRECISION_MISMATCH_ERROR
 The function that created this object or one of its ancestors was passed
 arguments whose underlying scalar types did not match.

 @constant LA_SINGULAR_ERROR
 One or more parts of the computation attempted to solve a singular system,
 and no correct result is possible.
 */
#define LA_SUCCESS                       (0)
#define LA_WARNING_POORLY_CONDITIONED    (1000)
#define LA_INTERNAL_ERROR                (-1000)
#define LA_INVALID_PARAMETER_ERROR       (-1001)
#define LA_DIMENSION_MISMATCH_ERROR      (-1002)
#define LA_PRECISION_MISMATCH_ERROR      (-1003)
#define LA_SINGULAR_ERROR                (-1004)
#define LA_SLICE_OUT_OF_BOUNDS_ERROR     (-1005)
typedef long la_status_t;

#define LA_SCALAR_TYPE_FLOAT  (0x8000)
#define LA_SCALAR_TYPE_DOUBLE (0x4000)
typedef unsigned int la_scalar_type_t;

typedef unsigned long la_count_t;
typedef long la_index_t;

typedef void (*la_deallocator_t)(void *ptr);

#endif // defined __LA_BASE_HEADER__
