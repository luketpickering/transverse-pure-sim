#!/bin/env bash
# Template script for running genie
RUNNUM=ZRUNNUMZ
OUTNAME="gntp.${RUNNUM}.ghep.root"
ROUTNAME="gntp.${RUNNUM}.gtrac.root"

cd $TMPDIR
cp -a $GENIE ./

cd genie*

# run genie
gevgen -n ZNEVENTSZ -p ZNUPDGZ -t ZTGTPDGZ -e ZNUPGEVZ -r $RUNNUM --seed ${RANDOM} --cross-sections $GENERATORS/data/geniesplines/gxspl-small-2.8.4.xml

# convert output to rootracker
gntpc -i ${OUTNAME} -f t2k_rootracker -o ${ROUTNAME}

CUStageOut ${ROUTNAME} ZOUTDIRZ

