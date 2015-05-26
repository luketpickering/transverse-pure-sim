CXX := g++
RCINT := rootcint
RC := root-config

BDIR :=bin
LDIR :=lib

TARGET := GiBUUToStdHep.exe
TARGETSRC := $(TARGET:.exe=.cxx)

TOBJS := GiRooTracker.cxx
TOBJH := $(TOBJS:.cxx=.hxx)

ROOTCFLAGS := `$(RC) --cflags`
ROOTLDFLAGS := `$(RC) --libs --glibs`

CXXFLAGS := -fPIC $(ROOTCFLAGS) -g -std=c++11 -Wall
LDFLAGS := $(ROOTLDFLAGS) -Wl,-rpath=.

UTILSLOC :=../../utils
UTILSDEPSO :=libPureGenUtils.so

.PHONY: all clean

all: $(TARGET)
	@echo ""
	@echo "*********************************************************************"
	@echo "Success. Built GiBUUToStdHep."
	@echo "*********************************************************************"
	mkdir -p $(BDIR) $(LDIR)
	mv $(TARGET) $(BDIR)/
	mv $(UTILSDEPSO) GiRooTracker.so $(LDIR)/

$(UTILSDEPSO):
	ln -s `readlink -f $(UTILSLOC)/lib/$@` $@

$(TARGET): $(TARGETSRC) $(UTILSDEPSO) GiRooTracker.so
	$(CXX) -o $@ $(CXXFLAGS) $(LDFLAGS) -I$(UTILSLOC) $^

GiRooTracker.so: GiRooTracker.hxx GiRooTracker.cxx
	$(CXX) $(CXXFLAGS) -shared -I$(UTILSLOC) -o $@ GiRooTracker.cxx

clean:
	rm -rf $(TARGET) $(UTILSDEPSO) GiRooTracker.so $(LDIR) $(BDIR)
