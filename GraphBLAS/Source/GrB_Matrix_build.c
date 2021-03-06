//------------------------------------------------------------------------------
// GrB_Matrix_build: build a sparse GraphBLAS matrix
//------------------------------------------------------------------------------

// SuiteSparse:GraphBLAS, Timothy A. Davis, (c) 2017-2021, All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

//------------------------------------------------------------------------------

#include "GB_build.h"

#define GB_MATRIX_BUILD(prefix,type,T)                                        \
GrB_Info GB_EVAL3 (prefix, _Matrix_build_, T) /* build a matrix from tuples */\
(                                                                             \
    GrB_Matrix C,                   /* matrix to build                    */  \
    const GrB_Index *I,             /* array of row indices of tuples     */  \
    const GrB_Index *J,             /* array of column indices of tuples  */  \
    const type *X,                  /* array of values of tuples          */  \
    GrB_Index nvals,                /* number of tuples                   */  \
    const GrB_BinaryOp dup          /* binary op to assemble duplicates   */  \
)                                                                             \
{                                                                             \
    GB_WHERE (C, "GrB_Matrix_build_" GB_STR(T) " (C, I, J, X, nvals, dup)") ; \
    GB_BURBLE_START ("GrB_Matrix_build") ;                                    \
    GB_RETURN_IF_NULL_OR_FAULTY (C) ;                                         \
    GrB_Info info = GB_matvec_build (C, I, J, X, nvals, dup,                  \
        GB_ ## T ## _code, true, Context) ;                                   \
    GB_BURBLE_END ;                                                           \
    return (info) ;                                                           \
}

GB_MATRIX_BUILD (GrB, bool      , BOOL   )
GB_MATRIX_BUILD (GrB, int8_t    , INT8   )
GB_MATRIX_BUILD (GrB, uint8_t   , UINT8  )
GB_MATRIX_BUILD (GrB, int16_t   , INT16  )
GB_MATRIX_BUILD (GrB, uint16_t  , UINT16 )
GB_MATRIX_BUILD (GrB, int32_t   , INT32  )
GB_MATRIX_BUILD (GrB, uint32_t  , UINT32 )
GB_MATRIX_BUILD (GrB, int64_t   , INT64  )
GB_MATRIX_BUILD (GrB, uint64_t  , UINT64 )
GB_MATRIX_BUILD (GrB, float     , FP32   )
GB_MATRIX_BUILD (GrB, double    , FP64   )
GB_MATRIX_BUILD (GxB, GxB_FC32_t, FC32   )
GB_MATRIX_BUILD (GxB, GxB_FC64_t, FC64   )
GB_MATRIX_BUILD (GrB, void      , UDT    )

