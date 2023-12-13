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

CPP_LIBFLAGS=	-O3 -c

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
AUTOMATA_OBJS = automata_class_functions.o Source.o moore.o
AUTOMATA_OBJS_TEST = source_automata_compiled_class.o rules.o
AUTOMATA_LIB = libautomata.a
AUTOMATA_LIB_TEST = test_libautomata.a


#temporary testing makefile for disease application of cellular automata
test_disease_auto:	$(INC_DIR)/myclass.h $(INC_DIR)/Source.h
	$(CPP) $(ERRORFLAG) $(CPPFLAGS) automata automata_class.cpp \
	-I$(INC_DIR) $(LIB_DIR)/libautomata.a
	mv automata $(BIN_DIR)
	cd $(BIN_DIR); ./automata

#create class functions object file
automata_class_functions.o:
	$(CPP) $(CPP_LIBFLAGS) automata_class_functions.cpp -I$(INC_DIR)

#grid initialization functions
Source.o:
	$(CPP) $(CPP_LIBFLAGS) Source.cpp -I$(INC_DIR)

moore.o:
	$(CPP) $(CPP_LIBFLAGS) moore.cpp -I$(INC_DIR)

source_automata_compiled_class.o: 
	$(CPP) $(CPP_LIBFLAGS) source_automata_compiled_class.cpp -I$(INC_DIR)

rules.o:
	$(CPP) $(CPP_LIBFLAGS) rules.cpp -I$(INC_DIR)

test_libautomata.a: $(AUTOMATA_OBJS_TEST)
	ar -ru $(AUTOMATA_LIB_TEST) $(AUTOMATA_OBJS_TEST)
	mv $(AUTOMATA_LIB_TEST) $(LIB_DIR)
	rm $(AUTOMATA_OBJS_TEST)



#create+update automata class library. Move to /Lib
libautomata.a: $(AUTOMATA_OBJS)
	ar -ru $(AUTOMATA_LIB) $(AUTOMATA_OBJS)
	mv $(AUTOMATA_LIB) $(LIB_DIR)
	rm $(AUTOMATA_OBJS)

all:
	make automata_class_functions.o
	make libautomata.a
	make test_disease_auto

cleanall:
	cd $(BIN_DIR); rm $(AUTOMATA_EXECUTABLES) 

