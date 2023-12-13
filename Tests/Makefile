# Chem 274B: Software Engineering Fundataions for
#            Molecular Sciences 
# University of California, Berkeley
#
# Last modified December 12th, 2023
# SHirley Li

# GNU C++ Compiler
CPP         = g++      

# compiler flags -O3 optimized version
CPPFLAGS    = -O3 -o

CPP_LIBFLAGS=	-O3 -c

# allows for compiler warning messages
ERRORFLAG 	= -Wall

# The directory where assn 4's main library include files are stored.
INC_DIR = ../Include

# The directory where assn 4's main library object files are stored
LIB_DIR     = ../Lib

# Executable programs
BIN_DIR     = ../Bin


test_source_automata_compiled_class: $(INC_DIR)/source_automata_compiled.h
	$(CPP) $(CPPFLAGS) test_source_automata_compiled_class test_source_automata_compiled_class.cpp \
	-I$(INC_DIR) $(LIB_DIR)/test_libautomata.a
	mv test_source_automata_compiled_class $(BIN_DIR)