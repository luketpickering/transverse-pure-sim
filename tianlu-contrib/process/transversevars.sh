#!/bin/env bash

# Converts rootracker output to transverse variable output with Luke's
# ProcessRooTrackerToTransversityVariables.exe

##### user options ####
generators=( 'neut' 'genie' )
categories=( 'targets/C' 'targets/O' 'targets/Ar' 'targets/Fe' 'targets/Cu' 'targets/Zn' 'targets/Pb' )
### end user options ###

# Parse command line options
force=false
while [[ $# > 0 ]]
do
    key="$1"

    case $key in
        -f|--force)
            force=true
            ;;
        *)
            ;;
    esac
    shift
done

for generator in "${generators[@]}"
do
    for category in "${categories[@]}"
    do
        output="${HOME}/store/other/generators/${generator}/${category}/TransverseVars.root"
        if [ "${force}" = true ]; then
            test -f  ${output} && echo "Removing ${output} to allow overwrite!" && rm -f ${output}
        fi

        ProcessRooTrackerToTransversityVariables.exe -i "${HOME}/store/other/generators/${generator}/${category}/*.root" -o ${output}  -g ${generator}

    done
done
