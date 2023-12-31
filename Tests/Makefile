# Chem 274B: Software Engineering Fundataions for
#            Molecular Sciences 
# University of California, Berkeley
#
# Last modified December 15th, 2023
# Shirley Li
# Creates executables for tests for our Cellular Automata class 
# GNU C++ Compiler
CPP         = g++      

# compiler flags -O3 optimized version
CPPFLAGS    = -O3 -o

CPP_LIBFLAGS=	-O3 -c

# allows for compiler warning messages
ERRORFLAG 	= -Wall

# The directory where library include files are stored.
INC_DIR = ../Include

# The directory where library object files are stored
LIB_DIR     = ../Lib

# Executable programs
BIN_DIR     = ../Bin

# Generate executables to test functionalities 
EXECUTABLES = test_source_automata_compiled_class test_majority test_straight test_neighbor

test_source_automata_compiled_class: $(INC_DIR)/source_automata_compiled.h
	$(CPP) $(CPPFLAGS) test_source_automata_compiled_class test_source_automata_compiled_class.cpp \
	-I$(INC_DIR) $(LIB_DIR)/test_libautomata.a
	mv test_source_automata_compiled_class $(BIN_DIR)
	cd $(BIN_DIR); ./test_source_automata_compiled_class
  
test_majority: $(INC_DIR)/source_automata_compiled.h
	$(CPP) $(CPPFLAGS) test_majority test_majority.cpp \
	-I$(INC_DIR) $(LIB_DIR)/test_libautomata.a
	mv test_majority $(BIN_DIR)

test_straight: $(INC_DIR)/source_automata_compiled.h
	$(CPP) $(CPPFLAGS) test_straight test_straight.cpp \
	-I$(INC_DIR) $(LIB_DIR)/test_libautomata.a
	mv test_straight $(BIN_DIR)

test_neighbor: $(INC_DIR)/source_automata_compiled.h
	$(CPP) $(CPPFLAGS) test_neighbor test_neighbor.cpp \
	-I$(INC_DIR) $(LIB_DIR)/test_libautomata.a
	mv test_neighbor $(BIN_DIR)

