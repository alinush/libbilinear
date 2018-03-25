 > alinush@macbook [~/repos/MIRACL/osx-build] (master \*%) $ ./bmark
 > MIRACL - 64 bit version
 > Little Endian processor
 > Using some assembly language
 > No special optimizations
 > Precomputation uses fixed Window size = 8
 > So 256 values are precomputed and stored
 > NOTE: No optimizations/assembly language apply to GF(2^m) Elliptic Curves
 > NOTE: times are elapsed real-times - so make sure nothing else is running!
 > 
 > Modular exponentiation benchmarks - calculating g^e mod p
 > From these figures it should be possible to roughly estimate the time
 > required for your favourite PK algorithm, RSA, DSA, DH, etc.
 > Key R - random base bits/random exponent bits
 >     V - random base bits/(small exponent e)
 >     S - (small base g)  /random exponent bits
 >     P - exponentiation with precomputation (fixed base g)
 >     D - double exponentiation g^e.a^b mod p
 > F3 = 257, F4 = 65537
 > RSA - Rivest-Shamir-Adleman
 > DH  - Diffie Hellman Key exchange
 > DSA - Digital Signature Algorithm
 > 
 > 512 bit prime....
 > R -    52864 iterations of  512/ 160      0.19 ms per iteration
 > D -    45461 iterations of  512/ 160      0.22 ms per iteration
 > R -    17841 iterations of  512/ 512      0.56 ms per iteration
 > S -    63285 iterations of  g=3/ 160      0.16 ms per iteration
 > P -   238407 iterations of  512/ 160      0.04 ms per iteration
 > 
 > 1024 bit RSA decryption                   1.12 ms
 >  512 bit DH 160 bit exponent:-
 >          offline, no precomputation       0.19 ms
 >          offline, small base              0.16 ms
 >          offline, w. precomputation       0.04 ms
 >          online                           0.19 ms
 >  512 bit DSA 160 bit exponent:-
 >          signature no precomputation      0.19 ms
 >          signature w. precomputation      0.04 ms
 >          verification                     0.22 ms
 > 
 > 1024 bit prime....
 > R -    17002 iterations of 1024/ 160      0.59 ms per iteration
 > D -    13664 iterations of 1024/ 160      0.73 ms per iteration
 > R -     2874 iterations of 1024/1024      3.48 ms per iteration
 > V -  1106436 iterations of 1024/e= 3      0.01 ms per iteration
 > V -   151121 iterations of 1024/e=F4      0.07 ms per iteration
 > S -    22649 iterations of  g=3/ 160      0.44 ms per iteration
 > P -    86334 iterations of 1024/ 160      0.12 ms per iteration
 > 
 > 2048 bit RSA decryption                   6.96 ms
 > 1024 bit RSA encryption e=3               0.01 ms
 > 1024 bit RSA encryption e=65537           0.07 ms
 > 1024 bit DH 160 bit exponent:-
 >          offline, no precomputation       0.59 ms
 >          offline, small base              0.44 ms
 >          offline, w. precomputation       0.12 ms
 >          online                           0.59 ms
 > 1024 bit DSA 160 bit exponent:-
 >          signature no precomputation      0.59 ms
 >          signature w. precomputation      0.12 ms
 >          verification                     0.73 ms
 > 
 > 2048 bit prime....
 > R -     3066 iterations of 2048/ 256      3.26 ms per iteration
 > D -     2529 iterations of 2048/ 256      3.95 ms per iteration
 > R -      413 iterations of 2048/2048     24.27 ms per iteration
 > V -   342609 iterations of 2048/e= 3      0.03 ms per iteration
 > V -    46438 iterations of 2048/e=F4      0.22 ms per iteration
 > S -     3883 iterations of  g=3/ 256      2.58 ms per iteration
 > P -    14134 iterations of 2048/ 256      0.71 ms per iteration
 > 
 > 2048 bit RSA encryption e=3               0.03 ms
 > 2048 bit RSA encryption e=65537           0.22 ms
 > 2048 bit DH 256 bit exponent:-
 >          offline, no precomputation       3.26 ms
 >          offline, small base              2.58 ms
 >          offline, w. precomputation       0.71 ms
 >          online                           3.26 ms
 > 2048 bit DSA 256 bit exponent:-
 >          signature no precomputation      3.26 ms
 >          signature w. precomputation      0.71 ms
 >          verification                     3.95 ms
 > 
 > Elliptic Curve point multiplication benchmarks - calculating r.P
 > From these figures it should be possible to roughly estimate the time
 > required for your favourite EC PK algorithm, ECDSA, ECDH, etc.
 > Key - ER - Elliptic Curve point multiplication r.P
 >       ED - Elliptic Curve double multiplication r.P + s.Q
 >       EP - Elliptic Curve multiplication with precomputation
 > EC    - Elliptic curve GF(p) - p of no special form
 > ECDH  - Diffie Hellman Key exchange
 > ECDSA - Digital Signature Algorithm
 > 
 > 160 bit GF(p) Elliptic Curve....
 > ER -    17658 iterations                  0.57 ms per iteration
 > ED -    13914 iterations                  0.72 ms per iteration
 > EP -    83197 iterations                  0.12 ms per iteration
 > 
 >  160 bit ECDH :-
 >          offline, no precomputation       0.57 ms
 >          offline, w. precomputation       0.12 ms
 >          online                           0.57 ms
 >  160 bit ECDSA :-
 >          signature no precomputation      0.57 ms
 >          signature w. precomputation      0.12 ms
 >          verification                     0.72 ms
 > 
 > 192 bit GF(p) Elliptic Curve....
 > ER -    14494 iterations                  0.69 ms per iteration
 > ED -    10983 iterations                  0.91 ms per iteration
 > EP -    64541 iterations                  0.15 ms per iteration
 > 
 >  192 bit ECDH :-
 >          offline, no precomputation       0.69 ms
 >          offline, w. precomputation       0.15 ms
 >          online                           0.69 ms
 >  192 bit ECDSA :-
 >          signature no precomputation      0.69 ms
 >          signature w. precomputation      0.15 ms
 >          verification                     0.91 ms
 > 
 > 224 bit GF(p) Elliptic Curve....
 > ER -     9817 iterations                  1.02 ms per iteration
 > ED -     7595 iterations                  1.32 ms per iteration
 > EP -    45401 iterations                  0.22 ms per iteration
 > 
 >  224 bit ECDH :-
 >          offline, no precomputation       1.02 ms
 >          offline, w. precomputation       0.22 ms
 >          online                           1.02 ms
 >  224 bit ECDSA :-
 >          signature no precomputation      1.02 ms
 >          signature w. precomputation      0.22 ms
 >          verification                     1.32 ms
 > 
 > 256 bit GF(p) Elliptic Curve....
 > ER -     8347 iterations                  1.20 ms per iteration
 > ED -     6537 iterations                  1.53 ms per iteration
 > EP -    37093 iterations                  0.27 ms per iteration
 > 
 >  256 bit ECDH :-
 >          offline, no precomputation       1.20 ms
 >          offline, w. precomputation       0.27 ms
 >          online                           1.20 ms
 >  256 bit ECDSA :-
 >          signature no precomputation      1.20 ms
 >          signature w. precomputation      0.27 ms
 >          verification                     1.53 ms
 > 
 > 163 bit GF(2^m) Elliptic Curve....
 > ER -    25847 iterations                  0.39 ms per iteration
 > ED -    19273 iterations                  0.52 ms per iteration
 > EP -    99693 iterations                  0.10 ms per iteration
 > 
 >  163 bit ECDH :-
 >          offline, no precomputation       0.39 ms
 >          offline, w. precomputation       0.10 ms
 >          online                           0.39 ms
 >  163 bit ECDSA :-
 >          signature no precomputation      0.39 ms
 >          signature w. precomputation      0.10 ms
 >          verification                     0.52 ms
 > 
 > 163 bit GF(2^m) Koblitz Elliptic Curve....
 > ER -    36531 iterations                  0.27 ms per iteration
 > ED -    19187 iterations                  0.52 ms per iteration
 > EP -   100134 iterations                  0.10 ms per iteration
 > 
 >  163 bit ECDH :-
 >          offline, no precomputation       0.27 ms
 >          offline, w. precomputation       0.10 ms
 >          online                           0.27 ms
 >  163 bit ECDSA :-
 >          signature no precomputation      0.27 ms
 >          signature w. precomputation      0.10 ms
 >          verification                     0.52 ms
 > 
 > 233 bit GF(2^m) Elliptic Curve....
 > ER -    15406 iterations                  0.65 ms per iteration
 > ED -    11003 iterations                  0.91 ms per iteration
 > EP -    58690 iterations                  0.17 ms per iteration
 > 
 >  233 bit ECDH :-
 >          offline, no precomputation       0.65 ms
 >          offline, w. precomputation       0.17 ms
 >          online                           0.65 ms
 >  233 bit ECDSA :-
 >          signature no precomputation      0.65 ms
 >          signature w. precomputation      0.17 ms
 >          verification                     0.91 ms
 > 
 > 233 bit GF(2^m) Koblitz Elliptic Curve....
 > ER -    25924 iterations                  0.39 ms per iteration
 > ED -    12571 iterations                  0.80 ms per iteration
 > EP -    59874 iterations                  0.17 ms per iteration
 > 
 >  233 bit ECDH :-
 >          offline, no precomputation       0.39 ms
 >          offline, w. precomputation       0.17 ms
 >          online                           0.39 ms
 >  233 bit ECDSA :-
 >          signature no precomputation      0.39 ms
 >          signature w. precomputation      0.17 ms
 >          verification                     0.80 ms
 > 
 > 283 bit GF(2^m) Elliptic Curve....
 > ER -     9342 iterations                  1.07 ms per iteration
 > ED -     6527 iterations                  1.53 ms per iteration
 > EP -    35157 iterations                  0.28 ms per iteration
 > 
 >  283 bit ECDH :-
 >          offline, no precomputation       1.07 ms
 >          offline, w. precomputation       0.28 ms
 >          online                           1.07 ms
 >  283 bit ECDSA :-
 >          signature no precomputation      1.07 ms
 >          signature w. precomputation      0.28 ms
 >          verification                     1.53 ms
 > 
 > 283 bit GF(2^m) Koblitz Elliptic Curve....
 > ER -    16773 iterations                  0.60 ms per iteration
 > ED -     8483 iterations                  1.18 ms per iteration
 > EP -    35783 iterations                  0.28 ms per iteration
 > 
 >  283 bit ECDH :-
 >          offline, no precomputation       0.60 ms
 >          offline, w. precomputation       0.28 ms
 >          online                           0.60 ms
 >  283 bit ECDSA :-
 >          signature no precomputation      0.60 ms
 >          signature w. precomputation      0.28 ms
 >          verification                     1.18 ms
 > 
 > 571 bit GF(2^m) Elliptic Curve....
 > ER -     2051 iterations                  4.88 ms per iteration
 > ED -     1448 iterations                  6.91 ms per iteration
 > EP -     7496 iterations                  1.33 ms per iteration
 > 
 >  571 bit ECDH :-
 >          offline, no precomputation       4.88 ms
 >          offline, w. precomputation       1.33 ms
 >          online                           4.88 ms
 >  571 bit ECDSA :-
 >          signature no precomputation      4.88 ms
 >          signature w. precomputation      1.33 ms
 >          verification                     6.91 ms
 > 
 > 571 bit GF(2^m) Koblitz Elliptic Curve....
 > ER -     4643 iterations                  2.15 ms per iteration
 > ED -     2041 iterations                  4.90 ms per iteration
 > EP -     7897 iterations                  1.27 ms per iteration
 > 
 >  571 bit ECDH :-
 >          offline, no precomputation       2.15 ms
 >          offline, w. precomputation       1.27 ms
 >          online                           2.15 ms
 >  571 bit ECDSA :-
 >          signature no precomputation      2.15 ms
 >          signature w. precomputation      1.27 ms
 >          verification                     4.90 ms
