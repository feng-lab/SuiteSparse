#include "cs.h"
/* pinv = p', or p = pinv' */
CS_INT *cs_pinv (CS_INT const *p, CS_INT n)
{
    CS_INT k, *pinv ;
    if (!p) return (NULL) ;                     /* p = NULL denotes identity */
#ifdef _MSC_VER
    pinv = (CS_INT*)cs_malloc (n, sizeof (CS_INT)) ;        /* allocate result */
#else
    pinv = cs_malloc (n, sizeof (CS_INT)) ;        /* allocate result */
#endif
    if (!pinv) return (NULL) ;                  /* out of memory */
    for (k = 0 ; k < n ; k++) pinv [p [k]] = k ;/* invert the permutation */
    return (pinv) ;                             /* return result */
}
