# Chem 274B: Software Engineering Fundataions for
#            Molecular Sciences 
# University of California, Berkeley
#
# Last modified November 26, 2023
# Laura Jones

# GNU C++ Compiler
CPP         = g++      

# compiler flags -O3 optimized version
CPPFLAGS    = -O3 -o

# The directory where assn 4's main library include files are stored.
INC_DIR = ../Include

# The directory where the include files for utilities are stored
UINC_DIR = ../Utils/Include

# The directory where assn 4's main library object files are stored
LIB_DIR     = ../Lib

# The directory where the library object files for utilities are stored
ULIB_DIR     = ../Utils/Lib

# Executable programs
BIN_DIR     = ../Bin

# The next line contains a list of executable object files 
# created by this Makefile.
AUTOMATA_EXECUTABLES = 

#temporary testing makefile for disease application of cellular automata
test_disease_auto:	$(INC_DIR)/Source.h
	$(CPP) $(CPPFLAGS) disease_auto disease_automata.cpp \
	-I$(INC_DIR)
	mv disease_auto $(BIN_DIR)
	cd $(BIN_DIR); ./disease_auto

all: $(AUTOMATA_EXECUTABLES)

cleanall:
	cd $(BIN_DIR); rm $(AUTOMATA_EXECUTABLES) 

