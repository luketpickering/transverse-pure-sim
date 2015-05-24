CXX := g++

LDIR :=lib

CXXFLAGS := -fPIC $(ROOTCFLAGS) -g -std=c++11
LDFLAGS := $(ROOTLDFLAGS) -Wl,-rpath=.

TOBJS := CLITools.cxx PureGenUtils.cxx
TOBJH := $(TOBJS:.cxx=.hxx)

TARGET := libPureGenUtils.so

.PHONEY: all clean

all: tests
	./UtilsTests.exe
	@echo ""
	@echo "*********************************************************************"
	@echo "Success. Built Utils."
	@echo "*********************************************************************"
	mkdir -p $(LDIR)
	mv $(TARGET) $(LDIR)

tests: UtilsTests.cxx $(TOBJH) $(TOBJS) $(TARGET)
	$(CXX) -o UtilsTests.exe $(CXXFLAGS) $(LDFLAGS) $(TARGET) UtilsTests.cxx

$(TARGET): $(TOBJS) $(TOBJH)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -shared $(TOBJS) -o $@

clean:
	rm -rf $(TARGET) UtilsTests.exe $(LDIR)
