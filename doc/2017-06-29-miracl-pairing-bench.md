## Curves

See [curves here](2017-06-28-miracl-curves.html), or:

 > AES-128 security uses a BN k=12 curve
 > (implementation in bn_pair.cpp)
 > 
 > AES-192 security uses a KSS k=18 curve
 > (implementation in kss_pair.cpp)
 > 
 > AES-256 security uses a BLS k=24 curve
 > (implementation in bls_pair.cpp)

## On Macbook Air

### Performance summary for 128 bits
Average time to hash: 221 microseconds (32 iter)  
Average time to sign: 829 microseconds (16 iter)  
Average time to pair twice (w/ precomp): 17219 microseconds (512 iter)  

### Performance summary for 192 bits
Average time to hash: 2816 microseconds (32 iter)  
Average time to sign: 2638 microseconds (16 iter)  
Average time to pair twice (w/ precomp): 112493 microseconds (512 iter)

### Performance summary for 256
Average time to hash: 3442 microseconds (32 iter)  
Average time to sign: 5520 microseconds (16 iter)  
Average time to pair twice (w/ precomp): 188990 microseconds (512 iter)

## On Macbook Pro

### Performance summary for 128 bits
Average time to hash: 122 microseconds (32 iter)  
Average time to sign: 467 microseconds (16 iter)  
Average time to pair: 9731 microseconds (160 iter)

### Performance summary for 192 bits
Average time to hash: 1726 microseconds (32 iter)  
Average time to sign: 1710 microseconds (16 iter)  
Average time to pair: 63250 microseconds (160 iter)

### Performance summary for 256 bits
Average time to hash: 1467 microseconds (32 iter)  
Average time to sign: 3009 microseconds (16 iter)  
Average time to pair: 103414 microseconds (160 iter)
