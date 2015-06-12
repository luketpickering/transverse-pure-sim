#!/bin/env bash
# Template script for running neut
RUNNUM=ZRUNNUMZ
OUTNAME="nt.${RUNNUM}.neut.root"
ROUTNAME="nt.${RUNNUM}.ntrac.root"

cd $TMPDIR
cp -a $NEUT_ROOT ./

cd neut*/src/neutsmpl

# run neut
./neutroot2 ZCARDFILEZ $OUTNAME

# convert output to rootracker
NeutToRooTracker.exe -i ${OUTNAME} -o ${ROUTNAME} -s -G

CUStageOut ${ROUTNAME} ZOUTDIRZ
