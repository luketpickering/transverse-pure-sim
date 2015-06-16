
.PHONY: cpp11test.exe utils Neut2RooTracker GiBUUToStdHep\
 plotting ProcessRooTrackerToTransversityVariables

all: cpp11test.exe utils Neut2RooTracker GiBUUToStdHep\
	ProcessRooTrackerToTransversityVariables
	@echo ""
	@echo "*********************************************************************"
	@echo "Success. Built all of Lukes PureGen code."
	@echo "Now source setup.sh to add relevant directories to your PATH and"
	@echo "LD_LIBRARY_PATH"
	@echo "*********************************************************************"

clean: utils_clean Neut2RooTracker_clean GiBUUToStdHep_clean\
 ProcessRooTrackerToTransversityVariables_clean

cpp11test.exe:
	echo "int main(){}" > cpp11test.cxx
	$(CXX) -std=c++11 cpp11test.cxx -o $@
	rm cpp11test.{cxx,exe}

utils:
	cd utils && $(MAKE)
Neut2RooTracker: utils
	cd generators/neut/neut2rootracker && $(MAKE)
GiBUUToStdHep: utils
	cd generators/GiBUU/GiBUUToStdHep && $(MAKE)
plotting:
	cd plotting && $(MAKE)
ProcessRooTrackerToTransversityVariables: utils
	cd transverse-variable-tree-generation/all && $(MAKE)

utils_clean:
	cd utils && $(MAKE) clean
Neut2RooTracker_clean:
	cd generators/neut/neut2rootracker && $(MAKE) clean
GiBUUToStdHep_clean:
	cd generators/GiBUU/GiBUUToStdHep && $(MAKE) clean
plotting_clean:
	cd plotting && $(MAKE) clean
ProcessRooTrackerToTransversityVariables_clean:
	cd transverse-variable-tree-generation/all && $(MAKE) clean
