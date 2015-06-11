# first source a newer version of gcc
source /cvmfs/cms.cern.ch/slc5_amd64_gcc481/external/gcc/4.8.1/etc/profile.d/init.sh
setenv GENERATORS $HOME/software/generators

# CERNLIB (T.Y. installed 3/5/13)
echo "Setting up CERNLIB"
setenv CERN $HOME/software/CERNLIB
setenv CERN_LEVEL 2005
setenv CERN_ROOT $CERN/$CERN_LEVEL
setenv CERNLIB $CERN_ROOT/lib
setenv CERNLIBDIR $CERNLIB
setenv CERNPATH $CERNLIB
setenv PATH ${CERN_ROOT}/bin:${PATH}
setenv LD_LIBRARY_PATH ${CERNLIB}:${LD_LIBRARY_PATH}

echo "Setting up pythia6, libxml, log4cpp, lhapdf, and ROOT"
setenv PYTHIA6 $GENERATORS/ext/pythia6/v6_428/lib/
setenv LD_LIBRARY_PATH ${PYTHIA6}:${LD_LIBRARY_PATH}
setenv LIBXML2_LIB $GENERATORS/ext/libxml2-2.9.0/install/lib/
setenv LIBXML2_INC $GENERATORS/ext/libxml2-2.9.0/install/include/libxml2
setenv LD_LIBRARY_PATH $GENERATORS/ext/libxml2-2.9.0/install/lib:${LD_LIBRARY_PATH}
setenv LOG4CPP_INC $GENERATORS/ext/log4cpp/install/include/
setenv LOG4CPP_LIB $GENERATORS/ext/log4cpp/install/lib/
setenv LD_LIBRARY_PATH $GENERATORS/ext/log4cpp/install/lib:${LD_LIBRARY_PATH}
setenv LHAPDF_LIB $GENERATORS/ext/lhapdf-5.9.1/install/lib/
setenv LHAPDF_INC $GENERATORS/ext/lhapdf-5.9.1/install/include/
setenv LHAPATH $GENERATORS/ext/lhapdf-5.9.1/install/bin/
setenv LD_LIBRARY_PATH $GENERATORS/ext/lhapdf-5.9.1/install/lib:${LD_LIBRARY_PATH}
setenv ROOTSYS $GENERATORS/ext/root-5.30.06/root/
setenv PATH $GENERATORS/ext/root-5.30.06/root/bin/:${PATH}
setenv LD_LIBRARY_PATH $GENERATORS/ext/root-5.30.06/root/lib/:${LD_LIBRARY_PATH}
cd $ROOTSYS/bin/
source thisroot.csh
cd -

echo "Setting up NEUT"
setenv NEUT_ROOT $GENERATORS/neut_*
setenv PATH ${NEUT_ROOT}/src/neutsmpl/bin:${PATH}
# for getting luke's neut2rootracker converter to work
setenv NEUTCLASSLOC $NEUT_ROOT/src/neutclass

echo "Setting up GENIE"
setenv GENIE $GENERATORS/genie_*
setenv LD_LIBRARY_PATH $GENIE/lib/:${LD_LIBRARY_PATH}
setenv PATH $GENIE/bin/:${PATH}
