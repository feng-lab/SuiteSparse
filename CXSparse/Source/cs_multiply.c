#include "cs.h"
/* C = A*B */
cs *cs_multiply (const cs *A, const cs *B)
{
    CS_INT p, j, nz = 0, anz, *Cp, *Ci, *Bp, m, n, bnz, *w, values, *Bi ;
    CS_ENTRY *x, *Bx, *Cx ;
    cs *C ;
    if (!CS_CSC (A) || !CS_CSC (B)) return (NULL) ;      /* check inputs */
    if (A->n != B->m) return (NULL) ;
    m = A->m ; anz = A->p [A->n] ;
    n = B->n ; Bp = B->p ; Bi = B->i ; Bx = B->x ; bnz = Bp [n] ;
#ifdef _MSC_VER
    w = (CS_INT*)cs_calloc (m, sizeof (CS_INT)) ;                    /* get workspace */
#else
    w = cs_calloc (m, sizeof (CS_INT)) ;                    /* get workspace */
#endif
    values = (A->x != NULL) && (Bx != NULL) ;
#ifdef _MSC_VER
    x = values ? (CS_ENTRY*)cs_malloc (m, sizeof (CS_ENTRY)) : NULL ; /* get workspace */
#else
    x = values ? cs_malloc (m, sizeof (CS_ENTRY)) : NULL ; /* get workspace */
#endif
    C = cs_spalloc (m, n, anz + bnz, values, 0) ;        /* allocate result */
    if (!C || !w || (values && !x)) return (cs_done (C, w, x, 0)) ;
    Cp = C->p ;
    for (j = 0 ; j < n ; j++)
    {
        if (nz + m > C->nzmax && !cs_sprealloc (C, 2*(C->nzmax)+m))
        {
            return (cs_done (C, w, x, 0)) ;             /* out of memory */
        } 
        Ci = C->i ; Cx = C->x ;         /* C->i and C->x may be reallocated */
        Cp [j] = nz ;                   /* column j of C starts here */
        for (p = Bp [j] ; p < Bp [j+1] ; p++)
        {
            nz = cs_scatter (A, Bi [p], Bx ? Bx [p] : 1, w, x, j+1, C, nz) ;
        }
        if (values) for (p = Cp [j] ; p < nz ; p++) Cx [p] = x [Ci [p]] ;
    }
    Cp [n] = nz ;                       /* finalize the last column of C */
    cs_sprealloc (C, 0) ;               /* remove extra space from C */
    return (cs_done (C, w, x, 1)) ;     /* success; free workspace, return C */
}
