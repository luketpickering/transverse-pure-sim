Author: Tianlu Yuan
Date: June 6 2015
Email: tianlu.yuan [at] colorado.edu

# Instructions for NEUT installation
Probably outdated instructions [here](http://www.t2k.org/asg/xsec/niwgdocs/neut/install_neut). General guideline, need CERNLIB, need to set up paths to CERNLIB and modify script `NEUT_ROOT/src/neutsmpl/EnvMakeneutsmpl` before sourcing and running the corresponding make script. See [NEUT notes](http://www.t2k.org/asg/xsec/niwgdocs/neut/NeutDoc) and [setup script](setup.sh).

# Instructions for GENIE installation
Tom Dealtry has written a nice python script that installs all prereqs for GENIE and GENIE itself.  It is located in the `nd280Computing` directory in the T2K Repository under `GENIE_install_scripts`.

The command to run `installGENIE.py` is:
```
./installGENIE.py -g 2.8.0 -l 5.9.1 -p 6_428 -r 5.30.06 -x 2.9.0 -m 'Make.include' -u 'UserPhysicsOptions.xml' -d /nfs/hepcode/t2k/ -o
```
For an explanation of the options do `./installGENIE.py -h`.

Compiling ROOT can be problematic due to `/usr/local/lib/libfftw3.a` on being a statically linked library instead of a dynamically linked lib.  Options seem to be either recompile fftw3 library with `-fPIC` option, or disable fftw3 in ROOT when configuring via `./configure --disable-fftw3`.  Have chosen the second option when installing GENIE 2.8.0.

[GENIE manual](http://genie.hepforge.org/manuals/GENIE_PhysicsAndUserManual_v2.10.00a.pdf)

The script above no longer seems to work due to new server permission restrictions. GENIE requires a few external libraries. log4cpp, pythia6, libxml, lhapdf. These are all stored (copied from earlier GENIE install) in `$GENERATORS/ext/`.

To configure, must specify location of some include and libs from the external packages. `./configure --with-libxml2-inc=$LIBXML2_INC --with-libxml2-lib=$LIBXML2_LIB --with-log4cpp-inc=$LOG4CPP_INC --with-log4cpp-lib=$LOG4CPP_LIB`.

When running GENIE, gevgen may complain about a missing file in LHAPATH. From the website: "We removed the restriction on $LHAPATH. We now supply, in $GENIE/data/evgen/pdfs, the patched PDF. Please copy this to your $LHAPATH area."

# Instructions for NuWro installation
`git clone http://borg.ift.uni.wroc.pl/nuwro.git`
`cd nuwro && make`

Should make sure to checkout the necessary tagged version.

Also requires pythia6 enabled ROOT with libPythia6.so in `root/lib/`, and then root must be configured as `./configure --with-pythia6-libdir=$PWD/lib`.

## Word of warning about gfortran
It seems that nuwro requires a libPythia6.so that is linked to libgfortran.so.1 which is bundled with gcc-4.1.2 (default in SL5). However, GiBUU requires a more up-to-date version of gcc, and Luke's utilities packages also require gcc-4.7+ since they have C++11 specs. These have replaced libgfortran.so.1 with libgfortran.so.3 and any attempts to compile nuwro with a pythia6 library linked to this version of libgfortran will result in `undefined symbol: _gfortran_...` errors (pythia6 itself will still compile fine though). The current workaround is to compile pythia6 with gcc-4.1.2 so that it links to the older version of libgfortran. Then use gcc-4.7+ to compile the generators themselves.

I've also noticed that this occurs with some of the external packages (e.g. lhapdf) will fail similarly when compiled with gcc-4.8.1. May be related to this NASA [issue](http://heasarc.gsfc.nasa.gov/lheasoft/linux.html)?

# Instructions for GiBUU installation
GiBUU is probably the simplest to build. [Directions](https://gibuu.hepforge.org/trac/wiki/svn) for getting the src are online. Then just do `make` and it should work if you have an updated version of gcc. I know gcc-4.1.2 doesn't work. To clean you have to do `make renew` instead of `make clean`.

# Analyzing outputs
The GENIE output is by default in a GHEP format which requires a lot of native GENIE classes in order to be able to read it. There is a utility that ships with GENIE `gntpc` that can convert the native GENIE into a rooTracker or other summary format. Usage is as `gntpc -i ghep.file.root -f output.format (gst, rootracker, etc)`.

NEUT doesn't have converter.
