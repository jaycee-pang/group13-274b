# Chem 274B: Software Engineering Fundataions for
#            Molecular Sciences 
# University of California, Berkeley
#
# Last modified December 13th, 2023
# Laura Jones

# This makefile demonstrates functionality of the automata class
# library

# GNU C++ Compiler
CPP         = g++      

# compiler flags -O3 optimized version
CPPFLAGS    = -O3 -o

# allows for compiler warning messages
ERRORFLAG 	= -Wall

# The directory where group-13's main library include files are stored.
INC_DIR = ../Include

# The directory where group-13's main library object files are stored
LIB_DIR     = ../Lib

# Executable programs
BIN_DIR     = ../Bin

# List of executables generated
EXECUTABLES	= disease_automata forest 

disease_automata:$(LIB_DIR)/test_libautomata.a
	$(CPP) $(CPPFLAGS) disease_automata disease_simulation.cpp \
	-I$(INC_DIR) $(LIB_DIR)/test_libautomata.a
	mv disease_automata $(BIN_DIR)
	cd $(BIN_DIR); ./disease_automata

 forest: $(LIB_DIR)/test_libautomata.a
	$(CPP) $(CPPFLAGS) forest forest.cpp \
	-I$(INC_DIR) $(LIB_DIR)/test_libautomata.a
	mv forest $(BIN_DIR)
	cd $(BIN_DIR); ./forest