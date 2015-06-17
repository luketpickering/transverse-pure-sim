# first source a newer version of gcc
source /cvmfs/cms.cern.ch/slc5_amd64_gcc481/external/gcc/4.8.1/etc/profile.d/init.sh
export GENERATORS=$HOME/software/generators

# CERNLIB (T.Y. installed 3/5/13)
echo "Setting up CERNLIB"
export CERN=$HOME/software/CERNLIB
export CERN_LEVEL=2005
export CERN_ROOT=$CERN/$CERN_LEVEL
export CERNLIB=$CERN_ROOT/lib
export CERNLIBDIR=$CERNLIB
export CERNPATH=$CERNLIB
export PATH=${CERN_ROOT}/bin:${PATH}
export LD_LIBRARY_PATH=${CERNLIB}:${LD_LIBRARY_PATH}

echo "Setting up pythia6"
export PYTHIA6=$GENERATORS/ext/pythia6/v6_428/lib/
export LD_LIBRARY_PATH=${PYTHIA6}:${LD_LIBRARY_PATH}
echo "Setting up libxml"
export LIBXML2_LIB=$GENERATORS/ext/libxml2-2.9.0/install/lib/
export LIBXML2_INC=$GENERATORS/ext/libxml2-2.9.0/install/include/libxml2
export LD_LIBRARY_PATH=$GENERATORS/ext/libxml2-2.9.0/install/lib:${LD_LIBRARY_PATH}
echo "Setting up log4cpp"
export LOG4CPP_INC=$GENERATORS/ext/log4cpp/install/include/
export LOG4CPP_LIB=$GENERATORS/ext/log4cpp/install/lib/
export LD_LIBRARY_PATH=$GENERATORS/ext/log4cpp/install/lib:${LD_LIBRARY_PATH}
echo "Setting up lhapdf"
export LHAPDF_LIB=$GENERATORS/ext/lhapdf-5.9.1/install/lib/
export LHAPDF_INC=$GENERATORS/ext/lhapdf-5.9.1/install/include/
export LHAPATH=$GENERATORS/ext/lhapdf-5.9.1/install/bin/
export LD_LIBRARY_PATH=$GENERATORS/ext/lhapdf-5.9.1/install/lib:${LD_LIBRARY_PATH}
echo "Setting up ROOT"
export ROOTSYS=$GENERATORS/ext/root-5.30.06/root/
export PATH=$GENERATORS/ext/root-5.30.06/root/bin/:${PATH}
export LD_LIBRARY_PATH=$GENERATORS/ext/root-5.30.06/root/lib/:${LD_LIBRARY_PATH}
cd $ROOTSYS/bin/
source thisroot.sh
cd - > /dev/null

echo "Setting up NEUT"
export NEUT_ROOT=$GENERATORS/neut_5.3.3_v1r21
export PATH=${NEUT_ROOT}/src/neutsmpl/bin:${PATH}
# for getting luke's neut2rootracker converter to work
export NEUTCLASSLOC=$NEUT_ROOT/src/neutclass

echo "Setting up GENIE"
export GENIE=$GENERATORS/genie_2_8_6
export LD_LIBRARY_PATH=$GENIE/lib/:${LD_LIBRARY_PATH}
export PATH=$GENIE/bin:${PATH}

echo "Setting up NUWRO"
export NUWRO=$GENERATORS/nuwro
export PATH=$NUWRO/bin:${PATH}

echo "Setting up GIBUU"
export GIBUU=$GENERATORS/GiBUU_1.6
export PATH=$GIBUU/objects:${PATH}
