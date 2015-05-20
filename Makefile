#Compiler and various flags
CXX= g++
CXXFLAGS= -c -Wall -g
LFLAGS= -Wall -g
UTFLAGS= -pthread

#Various directory names
SOURCE_DIR= src
TEST_DIR= test
LIB_INSTALL_DIR= /usr/local/lib
HEADER_INSTALL_DIR= /usr/local/include

#Various groups of source files
TESTS= $(patsubst %.cpp, %, $(wildcard $(TEST_DIR)/*_test.cpp))
HEADERS= $(wildcard $(SOURCE_DIR)/*.hpp)
OBJECTS= $(patsubst $(SOURCE_DIR)/%.cpp, %.o, $(wildcard $(SOURCE_DIR)/*.cpp))

#Various information about our library
VERSION= 0.1
LIB= lib/libenigma.a
LIB_SO= $(patsubst %.a, %.so.$(VERSION), $(LIB))

.PHONY: clean test all

all: lib test

###################################
#Source object files and executable
###################################

#Interactive executable
enigma: wheel.o ref.o stecker.o eint.o
	$(CXX) $(LFLAGS) -o $@ $^

#Object file specifically for exectuable
eint.o: $(SOURCE_DIR)/enigma.cpp
	$(CXX) $(CXXFLAGS) -D INTERACTIVE -o $@ $^

enigma.o: $(SOURCE_DIR)/enigma.cpp
	$(CXX) $(CXXFLAGS) $^

ref.o: $(SOURCE_DIR)/ref.cpp
	$(CXX) $(CXXFLAGS) $^

wheel.o: $(SOURCE_DIR)/wheel.cpp
	$(CXX) $(CXXFLAGS) $^

stecker.o: $(SOURCE_DIR)/stecker.cpp
	$(CXX) $(CXXFLAGS) $^

###########################
#Build the library archives
###########################

lib: CXXFLAGS += -D TESTING -fPIC
lib: $(OBJECTS)
	ar -crs $(LIB) $^
	$(CXX) -shared -o $(LIB_SO) $^

######################################
#Tests and Unit Test Framework targets
######################################

test: $(TESTS)

UTFramework.o: $(TEST_DIR)/UTFramework.cpp
	$(CXX) $(UTFLAGS) $(CXXFLAGS) $^

$(TEST_DIR)/ref_test: UTFramework.o ref.o $(TEST_DIR)/ref_test.cpp
	$(CXX) $(LFLAGS) $(UTFLAGS) -o $@ $^

$(TEST_DIR)/wheel_test: UTFramework.o wheel.o $(TEST_DIR)/wheel_test.cpp
	$(CXX) $(LFLAGS) $(UTFLAGS) -o $@ $^

$(TEST_DIR)/stecker_test: UTFramework.o stecker.o $(TEST_DIR)/stecker_test.cpp
	$(CXX) $(LFLAGS) $(UTFLAGS) -o $@ $^

#Object file specifically for enigma_test
etest.o: $(SOURCE_DIR)/enigma.cpp
	$(CXX) $(CXXFLAGS) -D TESTING -D INTERACTIVE -o $@ $^

$(TEST_DIR)/enigma_test: UTFramework.o ref.o wheel.o stecker.o etest.o $(TEST_DIR)/enigma_test.cpp
	$(CXX) $(LFLAGS) $(UTFLAGS) -o $@ $^

####################################################
#(Un)/Install the library to/from the system folders
####################################################

install: all
	install -t $(LIB_INSTALL_DIR) $(LIB) $(LIB_SO)
	install -t $(HEADER_INSTALL_DIR) $(HEADERS)

uninstall:
	rm -f $(LIB_INSTALL_DIR)/$(notdir $(LIB)) $(LIB_INSTALL_DIR)/$(notdir $(LIB_SO))
	rm -f $(foreach file, $(notdir $(HEADERS)), $(HEADER_INSTALL_DIR)/$(file))

#############################
#The destroyer of rouge files
#############################

clean:
	rm -f *.o
	rm -f *~
	rm -f ./*/*~
	rm -f lib/*
	rm -f enigma
	rm -f $(TEST_DIR)/*_test
