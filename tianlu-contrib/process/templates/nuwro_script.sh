#!/bin/env bash
# Template script for running nuwro
RUNNUM=ZRUNNUMZ
OUTNAME="nwr.${RUNNUM}.out.root"
ROUTNAME="nwr.${RUNNUM}.ntrac.root"

cd $TMPDIR

# run nuwro and silence stdout because sometimes it can get caught in
# infinite loop and bloat the logs
nuwro -i ZCARDFILEZ -o $OUTNAME > /dev/null

# convert output to rootracker
nuwro2rootracker ${OUTNAME} ${ROUTNAME}

CUStageOut ${ROUTNAME} ZOUTDIRZ
