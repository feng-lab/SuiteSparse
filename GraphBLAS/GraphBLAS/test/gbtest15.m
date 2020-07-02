function gbtest15
%GBTEST15 list all unary operators

% SuiteSparse:GraphBLAS, Timothy A. Davis, (c) 2017-2020, All Rights
% Reserved. http://suitesparse.com.  See GraphBLAS/Doc/License.txt.

types = gbtest_types ;
ops = { 'identity', '~', '-', '1', 'minv', 'abs',  'sqrt', 'log', ...
    'exp', 'sin', 'cos', 'tan', 'asin', 'acos', 'atan', ...
    'sinh', 'cosh', 'tanh', 'asinh', 'acosh', 'atanh', ...
    'signum', 'ceil', 'floor', 'round', 'trunc', 'pow2', ...
    'expm1', 'log10', 'log1p', 'log2', 'lgamma', 'tgamma', 'erf', ...
    'erfc', 'conj', 'creal', 'cimag', 'carg', 'isinf', 'isnan', ...
    'isinfinite', 'frexpx', 'frexpe' } ;

nops = 0 ;
for k1 = 1:length (ops)
    for k2 = 1:length (types)
        op = [ops{k1} '.' types{k2}] ;
        fprintf ('\nop: [%s]\n', op) ;
        try
            GrB.unopinfo (op) ;
            GrB.unopinfo (ops {k1}, types {k2}) ;
            nops = nops + 1 ;
        catch
        end
    end
end

fprintf ('\nhelp GrB.unopinfo:\n') ;
GrB.unopinfo ;

fprintf ('number of unary ops: %d\n', nops) ;
assert (nops == 204) ;

fprintf ('gbtest15: all tests passed\n') ;


