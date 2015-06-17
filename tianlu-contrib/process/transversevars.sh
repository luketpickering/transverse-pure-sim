#!/bin/env bash

# Converts rootracker output to transverse variable output with Luke's
# ProcessRooTrackerToTransversityVariables.exe

##### user options ####
generators=( 'neut' 'genie' 'nuwro')
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
        -h|--help)
            echo "Usage: $0 [-f <force removal>] [-h <help>]"
            echo "[-f|--force <force removing previous outputs to prevent collision>]"
            echo "[-h|--help <show this help message>]"
            exit 0
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
        inputdir="${HOME}/store/other/generators/${generator}/${category}"
        input="${inputdir}/*.root"
        output="${inputdir}/TransverseVars.root"

        if [ "${force}" = true ]; then
            test -f  ${output} && echo "Removing ${output} to allow overwrite!" && rm -f ${output}
        fi

        ProcessRooTrackerToTransversityVariables.exe -i "${input}" -o ${output}  -g ${generator}

    done
done

echo "All done!" && exit 0
