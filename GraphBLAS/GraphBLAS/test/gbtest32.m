function gbtest32
%GBTEST32 test nonzeros

% SuiteSparse:GraphBLAS, Timothy A. Davis, (c) 2017-2020, All Rights
% Reserved. http://suitesparse.com.  See GraphBLAS/Doc/License.txt.

rng ('default') ;

for d = 0:.1:1
    for n = 0:10
        A = sprandn (n, n, d) ;
        X = nonzeros (A) ;
        G = GrB (A) ;
        Y = nonzeros (G) ;
        assert (isequal (X, Y)) ;
    end
end

fprintf ('gbtest32: all tests passed\n') ;

