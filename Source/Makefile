# Chem 274B: Software Engineering Fundataions for
#            Molecular Sciences 
# University of California, Berkeley
#
# Last modified December 6th, 2023
# Laura Jones

# GNU C++ Compiler
CPP         = g++      

# compiler flags -O3 optimized version
CPPFLAGS    = -O0 -o

# allows for compiler warning messages
ERRORFLAG 	= -Wall

# The directory where assn 4's main library include files are stored.
INC_DIR = ../Include

# The directory where assn 4's main library object files are stored
LIB_DIR     = ../Lib

# Executable programs
BIN_DIR     = ../Bin

# The next line contains a list of executable object files 
# created by this Makefile.
AUTOMATA_EXECUTABLES = automata

#temporary testing makefile for disease application of cellular automata
test_disease_auto:	$(INC_DIR)/myclass.h
	$(CPP) $(ERRORFLAG) $(CPPFLAGS) automata automata_class.cpp \
	-I$(INC_DIR)
	mv automata $(BIN_DIR)
	cd $(BIN_DIR); ./automata

all: $(AUTOMATA_EXECUTABLES)

cleanall:
	cd $(BIN_DIR); rm $(AUTOMATA_EXECUTABLES) 

