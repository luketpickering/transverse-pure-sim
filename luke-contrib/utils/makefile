CXX := g++

LDIR :=lib

CXXFLAGS := -fPIC $(ROOTCFLAGS) -g -std=c++11 -Wall
LDFLAGS := $(ROOTLDFLAGS) -Wl,-rpath=.

TOBJS := CLITools.cxx PureGenUtils.cxx
TOBJH := $(TOBJS:.cxx=.hxx)

TARGET := libPureGenUtils.so

.PHONEY: all clean

all: tests
	./UtilsTests.exe
	mkdir -p $(LDIR)
	mv $(TARGET) $(LDIR)
	@echo ""
	@echo "*********************************************************************"
	@echo "Success. Built Utils."
	@echo "*********************************************************************"

tests: UtilsTests.cxx $(TOBJH) $(TOBJS) $(TARGET)
	$(CXX) -o UtilsTests.exe $(CXXFLAGS) $(LDFLAGS) $(TARGET) UtilsTests.cxx

$(TARGET): $(TOBJS) $(TOBJH)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -shared $(TOBJS) -o $@

clean:
	rm -rf $(TARGET) UtilsTests.exe $(LDIR)
