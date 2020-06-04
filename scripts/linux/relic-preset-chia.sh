cmake \
-DARITH=gmp \
-DWSIZE=64  \
-DTIMER=CYCLE   \
-DCHECK=off \
-DVERBS=off \
-DALLOC=AUTO    \
-DSHLIB=OFF \
-DMULTI=PTHREAD \
-DFP_PRIME=381  \
-DSTBIN=OFF \
-DFP_PMERS="off"    \
-DFPX_METHD="INTEG;INTEG;LAZYR" \
-DEP_PLAIN="off"    \
-DEP_SUPER="off"    \
-DQUIET=1   \
-DPP_EXT="LAZYR"    \
-DPP_METHD="LAZYR;OATEP"    \
-DTESTS=1   \
-DBENCH=1   \
-DSEED=UDEV \
-DFP_QNRES=off  \
-DFP_METHD="INTEG;INTEG;INTEG;MONTY;LOWER;SLIDE"    \
-DCOMP="-O2 -funroll-loops -fomit-frame-pointer"    \
$1

#
# In addition to extra params, differs from gmp-pbc-bls381.sh on the following.
#
#-DFP_QNRES=on \
#-DFP_METHD="BASIC;COMBA;COMBA;MONTY;LOWER;SLIDE" \
#-DCOMP="-O3 -funroll-loops -fomit-frame-pointer"    \
