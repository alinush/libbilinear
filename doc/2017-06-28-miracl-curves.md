From [pairings.txt](https://github.com/miracl/MIRACL/blob/master/source/curve/pairing/pairings.txt)

 > For Type-3 pairings, the ate pairing is always used. Curves are chosen
 > for optimal match to the required security level.
 > 
 > AES-80 security uses an MNT k=6 curve
 > (implementation in mnt_pair.cpp)
 > 
 > AES-128 security uses a BN k=12 curve
 > (implementation in bn_pair.cpp)
 > 
 > AES-192 security uses a KSS k=18 curve
 > (implementation in kss_pair.cpp)
 > 
 > AES-256 security uses a BLS k=24 curve
 > (implementation in bls_pair.cpp)

This might be outdated:

 > For higher levels of security it is recommended to increase the embedding 
 > degree and use non-supersingular curves - see ake4cpt.cpp and ake8cpt.cpp for 
 > examples. We use a "tower of extensions" to build an Fp^4 class on top of an 
 > Fp^2 class - see zzn2.h and zzn4.h
 >
 > Recommendations: 
 > 
 > For AES-80  security see ake6mntx.cpp
 >
 > For AES-128 security see ake12bnx.cpp
 >
 > For AES-192 security see ake18kssx.cpp
 >
 > For AES-256 security see ake24blsa.cpp
