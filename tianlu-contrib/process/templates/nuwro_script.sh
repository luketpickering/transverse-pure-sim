#!/bin/env bash
# Template script for running nuwro
RUNNUM=ZRUNNUMZ
OUTNAME="nwr.${RUNNUM}.out.root"
ROUTNAME="nwr.${RUNNUM}.ntrac.root"

cd $TMPDIR

# run nuwro
nuwro -i ZCARDFILEZ -o $OUTNAME

# convert output to rootracker
nuwro2rootracker ${OUTNAME} ${ROUTNAME}

CUStageOut ${ROUTNAME} ZOUTDIRZ
