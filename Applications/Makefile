# Chem 274B: Software Engineering Fundataions for
#            Molecular Sciences 
# University of California, Berkeley
#
# Last modified December 15th, 2023
# Laura Jones

# This makefile demonstrates functionality of the automata class
# library using two applications: an evolving forest and the spread of the flu

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

# utils Directory
UTILS_VISUAL= ../Utils/Visualizers

# Executable programs
BIN_DIR     = ../Bin

# List of executables generated
EXECUTABLES	= disease_automata forest
TXT_FILES	= disease_simulation.txt forest_simulation

general_sim:$(LIB_DIR)/test_libautomata.a
	$(CPP) $(CPPFLAGS) general_sim general_sim.cpp \
	-I$(INC_DIR) $(LIB_DIR)/test_libautomata.a
	mv general_sim $(BIN_DIR)
	cd $(BIN_DIR); ./general_sim

disease_automata:$(LIB_DIR)/test_libautomata.a
	$(CPP) $(CPPFLAGS) disease_automata disease_simulation.cpp \
	-I$(INC_DIR) $(LIB_DIR)/test_libautomata.a
	mv disease_automata $(BIN_DIR)
	cd $(BIN_DIR); ./disease_automata

visual_disease_automata:
	make disease_automata
	cd $(UTILS_VISUAL); python visualize_automata.py ../../Bin/disease_simulation.txt -o ../../Bin
	
forest: $(LIB_DIR)/test_libautomata.a
	$(CPP) $(CPPFLAGS) forest forest.cpp \
	-I$(INC_DIR) $(LIB_DIR)/test_libautomata.a
	mv forest $(BIN_DIR)
	cd $(BIN_DIR); ./forest

visual_forest:
	make forest
	cd $(UTILS_VISUAL); python visualize_automata.py ../../Bin/forest_simulation -o ../../Bin

cleanall:
	cd $(BIN_DIR); rm $(EXECUTABLES)
	cd $(BIN_DIR); rm $(TXT_FILES)
	cd $(BIN_DIR); Cellular_Automata.gif
