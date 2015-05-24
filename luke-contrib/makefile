
.PHONY: utils Neut2RooTracker GiBUUToStdHep\
 plotting ProcessRooTrackerToTransversityVariables

all: utils Neut2RooTracker GiBUUToStdHep\
	plotting ProcessRooTrackerToTransversityVariables
	@echo ""
	@echo "*********************************************************************"
	@echo "Success. Built all of Lukes PureGen code."
	@echo "Now source setup.sh to add relevant directories to your PATH and"
	@echo "LD_LIBRARY_PATH"
	@echo "*********************************************************************"

clean: utils_clean Neut2RooTracker_clean GiBUUToStdHep_clean\
 plotting_clean ProcessRooTrackerToTransversityVariables_clean

utils:
	cd utils && $(MAKE)
Neut2RooTracker: utils
	cd generators/neut/neut2rootracker && $(MAKE)
GiBUUToStdHep: utils
	cd generators/GiBUU && $(MAKE)
plotting:
	cd plotting && $(MAKE)
ProcessRooTrackerToTransversityVariables: utils
	cd transverse-variable-tree-generation/all && $(MAKE)

utils_clean:
	cd utils && $(MAKE) clean
Neut2RooTracker_clean:
	cd generators/neut/neut2rootracker && $(MAKE) clean
GiBUUToStdHep_clean:
	cd generators/GiBUU && $(MAKE) clean
plotting_clean:
	cd plotting && $(MAKE) clean
ProcessRooTrackerToTransversityVariables_clean:
	cd transverse-variable-tree-generation/all && $(MAKE) clean
