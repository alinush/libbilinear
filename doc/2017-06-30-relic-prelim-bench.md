## BLS numbers (RELIC library) on Macbook Air

All of these builds were dynamic libraries built using `TIMER=HREAL` (this 
measures context-switches and kernel time too, though there shouldn't be many.
However, Nadav warned me that on OS X there might be!)

### 112 (or 128 bits): FP_PRIME = 254, BN_P254, type = EP_DTYPE, degree = 2

All numbers agree:

 - 160 microsecs to generate keys
 - 130 microsecs to sign (includes hashing
 - 1.2 millisecs to verify (includes hashing and two pairings)

Built using a slightly modified [./preset/x64-pbc-112.sh](2017-06-30-relic-builds/x64-pbc-112.sh)
(however, the original 128 script was the same as the 112 one, so these numbers are the same, and thus unreported)

 > -- Curve BN-P254:
 > FP_PRIME: 254
 > Security level: 112

Compiled with `HREAL`:

 > HREAL: Realtime high-resolution timer.
 >
 > BENCH: cp_bls_gen                       = 160570 nanosec  (160 microsec)
 > BENCH: cp_bls_sign                      = 128888 nanosec  (128 microsec)
 > BENCH: cp_bls_ver                       = 1167607 nanosec (1.1 millisec)

Compiled with `ANSI`:

 > ANSI: ANSI-compatible timer.
 > 
 > BENCH: cp_bls_gen                       = 159 microsec
 > BENCH: cp_bls_sign                      = 121 microsec
 > BENCH: cp_bls_ver                       = 1147 microsec 

Compiled with `CYCLE`:

 > CYCLE: Cycle-counting timer.
 > 
 > BENCH: cp_bls_gen                       = 314252 cycles
 > BENCH: cp_bls_sign                      = 239328 cycles
 > BENCH: cp_bls_ver                       = 2280485 cycles

Compiled with `HPROC`:

 > HPROC: Per-process high-resolution timer.
 > 
 > BENCH: cp_bls_gen                       = 159716 nanosec
 > BENCH: cp_bls_sign                      = 123382 nanosec
 > BENCH: cp_bls_ver                       = 1142707 nanosec

Compiled with `HTHRD`:

 > HTHRD: Per-thread high-resolution timer.
 > 
 > BENCH: cp_bls_gen                       = 151342 nanosec
 > BENCH: cp_bls_sign                      = 127157 nanosec
 > BENCH: cp_bls_ver                       = 1161873 nanosec

Compiled with `POSIX`:

 > POSIX: POSIX-compatible timer.
 > 
 > BENCH: cp_bls_gen                       = 162 microsec
 > BENCH: cp_bls_sign                      = 125 microsec
 > BENCH: cp_bls_ver                       = 1177 microsec

### 128 bits: FP_PRIME == 381, B12_P381, type = EP_MTYPE, degree = 2

### 128 bits: FP_PRIME == 382, BN_P382, type = EP_DTYPE, degree = 2

### 140 bits: FP_PRIME == 455, B12_P455, type = EP_DTYPE, degree = 2

**Warning:** This was run on dvorak.

 > -- Curve B12-P455:
 > FP_PRIME: 455
 > Security level: 140
 > Benchmark iterations: 10000
 > 
 > HREAL: Realtime high-resolution timer.
 > 
 > BENCH: cp_bls_gen                       = 634278 nanosec
 > BENCH: cp_bls_sign                      = 898353 nanosec
 > BENCH: cp_bls_ver                       = 5963122 nanosec

### 160 bits: FP_PRIME == 638, B12_P638, type = EP_MTYPE, degree = 2

### ???-bits: FP_PRIME = 256, BN_P256, type = EP_DTYPE, degree = 2 

```
BENCH: cp_bls_gen                       = 1675 microsec
BENCH: cp_bls_sign                      = 1905 microsec
BENCH: cp_bls_ver                       = 19982 microsec
```
