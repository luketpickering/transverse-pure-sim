#!/bin/env bash

# Converts rootracker output to transverse variable output with Luke's
# ProcessRooTrackerToTransversityVariables.exe


generators=( 'neut' 'genie' )
categories=( 'targets/C' 'targets/O' 'targets/Ar' 'targets/Fe' 'targets/Cu' 'targets/Zn' 'targets/Pb' )

for generator in "${generators[@]}"
do
    for category in "${categories[@]}"
    do
        ProcessRooTrackerToTransversityVariables.exe -i "${HOME}/store/other/generators/${generator}/${category}/*.root" -o ${HOME}/store/other/generators/${generator}/${category}/TransverseVars.root -g ${generator}
    done
done
