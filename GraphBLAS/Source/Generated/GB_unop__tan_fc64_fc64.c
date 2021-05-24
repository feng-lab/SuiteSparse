//------------------------------------------------------------------------------
// GB_unop:  hard-coded functions for each built-in unary operator
//------------------------------------------------------------------------------

// SuiteSparse:GraphBLAS, Timothy A. Davis, (c) 2017-2021, All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

//------------------------------------------------------------------------------

// If this file is in the Generated/ folder, do not edit it (auto-generated).

#include "GB.h"
#ifndef GBCOMPACT
#include "GB_control.h"
#include "GB_atomics.h"
#include "GB_unop__include.h"

// C=unop(A) is defined by the following types and operators:

// op(A)  function:  GB (_unop_apply__tan_fc64_fc64)
// op(A') function:  GB (_unop_tran__tan_fc64_fc64)

// C type:   GxB_FC64_t
// A type:   GxB_FC64_t
// cast:     GxB_FC64_t cij = aij
// unaryop:  cij = ctan (aij)

#define GB_ATYPE \
    GxB_FC64_t

#define GB_CTYPE \
    GxB_FC64_t

// aij = Ax [pA]
#define GB_GETA(aij,Ax,pA) \
    GxB_FC64_t aij = Ax [pA]

#define GB_CX(p) Cx [p]

// unary operator
#define GB_OP(z, x) \
    z = ctan (x) ;

// casting
#define GB_CAST(z, aij) \
    GxB_FC64_t z = aij ;

// cij = op (aij)
#define GB_CAST_OP(pC,pA)           \
{                                   \
    /* aij = Ax [pA] */             \
    GxB_FC64_t aij = Ax [pA] ;          \
    /* Cx [pC] = op (cast (aij)) */ \
    GxB_FC64_t z = aij ;               \
    Cx [pC] = ctan (z) ;        \
}

// true if operator is the identity op with no typecasting
#define GB_OP_IS_IDENTITY_WITH_NO_TYPECAST \
    0

// disable this operator and use the generic case if these conditions hold
#define GB_DISABLE \
    (GxB_NO_TAN || GxB_NO_FC64)

//------------------------------------------------------------------------------
// Cx = op (cast (Ax)): apply a unary operator
//------------------------------------------------------------------------------

GrB_Info GB (_unop_apply__tan_fc64_fc64)
(
    GxB_FC64_t *Cx,       // Cx and Ax may be aliased
    const GxB_FC64_t *Ax,
    const int8_t *restrict Ab,   // A->b if A is bitmap
    int64_t anz,
    int nthreads
)
{
    #if GB_DISABLE
    return (GrB_NO_VALUE) ;
    #else
    int64_t p ;

    // TODO: if OP is ONE and uniform-valued matrices are exploited, then
    // do this in O(1) time

    if (Ab == NULL)
    { 
        #if ( GB_OP_IS_IDENTITY_WITH_NO_TYPECAST )
            GB_memcpy (Cx, Ax, anz * sizeof (GxB_FC64_t), nthreads) ;
        #else
            #pragma omp parallel for num_threads(nthreads) schedule(static)
            for (p = 0 ; p < anz ; p++)
            {
                GxB_FC64_t aij = Ax [p] ;
                GxB_FC64_t z = aij ;
                Cx [p] = ctan (z) ;
            }
        #endif
    }
    else
    { 
        // bitmap case, no transpose; A->b already memcpy'd into C->b
        #pragma omp parallel for num_threads(nthreads) schedule(static)
        for (p = 0 ; p < anz ; p++)
        {
            if (!Ab [p]) continue ;
            GxB_FC64_t aij = Ax [p] ;
            GxB_FC64_t z = aij ;
            Cx [p] = ctan (z) ;
        }
    }
    return (GrB_SUCCESS) ;
    #endif
}

//------------------------------------------------------------------------------
// C = op (cast (A')): transpose, typecast, and apply a unary operator
//------------------------------------------------------------------------------

GrB_Info GB (_unop_tran__tan_fc64_fc64)
(
    GrB_Matrix C,
    const GrB_Matrix A,
    int64_t *restrict *Workspaces,
    const int64_t *restrict A_slice,
    int nworkspaces,
    int nthreads
)
{ 
    #if GB_DISABLE
    return (GrB_NO_VALUE) ;
    #else
    #include "GB_unop_transpose.c"
    return (GrB_SUCCESS) ;
    #endif
}

#endif

