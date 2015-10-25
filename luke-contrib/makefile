
.PHONY: cpp11test.exe utils Neut2RooTracker\
 plotting NuTRAPAnalysis\
 GiBUUToStdHep

all: cpp11test.exe Neut2RooTracker\
	NuTRAPAnalysis\
	GiBUUToStdHep\
	plotting
	@echo ""
	@echo "*********************************************************************"
	@echo "Success. Built all of Lukes PureGen code."
	@echo "Now source setup.sh to add relevant directories to your PATH and"
	@echo "LD_LIBRARY_PATH"
	@echo "*********************************************************************"

clean: Neut2RooTracker_clean\
 NuTRAPAnalysis_clean\
 GiBUUToStdHep_clean\
 plotting_clean

cpp11test.exe:
	echo "int main(){}" > cpp11test.cxx
	$(CXX) -std=c++11 cpp11test.cxx -o $@
	rm cpp11test.{cxx,exe}

Neut2RooTracker:
	cd neut/neut2rootracker && $(MAKE)
plotting:
	cd plotting/ROOTXMLPlot && $(MAKE)
NuTRAPAnalysis:
	cd NuTRAPAnalysis/NuTRAPAnalysis && $(MAKE)
GiBUUToStdHep:
	cd gibuu/GiBUUToStdHep && $(MAKE)

Neut2RooTracker_clean:
	cd neut/neut2rootracker && $(MAKE) clean
plotting_clean:
	cd plotting/ROOTXMLPlot && $(MAKE) clean
NuTRAPAnalysis_clean:
	cd NuTRAPAnalysis/NuTRAPAnalysis && $(MAKE) clean
GiBUUToStdHep_clean:
	cd gibuu/GiBUUToStdHep && $(MAKE) clean
