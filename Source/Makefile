# Chem 274B: Software Engineering Fundataions for
#            Molecular Sciences 
# University of California, Berkeley
#
# Last modified December 14th, 2023
#
# This makefile can be used to create the object files and static
#			libraries needed to operate the cellular automata
#
# GNU C++ Compiler
CPP         = g++      
CPP_LIBFLAGS=	-O3 -c

# The directory where assn 4's main library include files are stored.
INC_DIR = ../Include

# The directory where assn 4's main library object files are stored
LIB_DIR     = ../Lib

# The object files and libraries generated from the makefile

AUTOMATA_OBJS = cp_source_automata_compiled_class.o rules.o
AUTOMATA_OBJS_TEST = source_automata_compiled_class.o rules.o run_sim.o
AUTOMATA_LIB = 
AUTOMATA_LIB_TEST = test_libautomata.a

# create automata class object file
source_automata_compiled_class.o: 
	$(CPP) $(CPP_LIBFLAGS) source_automata_compiled_class.cpp -I$(INC_DIR)

cp_source_automata_compiled_class.o: 
	$(CPP) $(CPP_LIBFLAGS) cp_source_automata_compiled_class.cpp -I$(INC_DIR)

# majority, straight, neighbor rule functions
rules.o:
	$(CPP) $(CPP_LIBFLAGS) rules.cpp -I$(INC_DIR)

run_sim.o:
	$(CPP) $(CPP_LIBFLAGS) run_sim.cpp -I$(INC_DIR)

#create+update automata class library. Move to /Lib
test_libautomata.a: $(AUTOMATA_OBJS_TEST)
	ar -ru $(AUTOMATA_LIB_TEST) $(AUTOMATA_OBJS_TEST)
	mv $(AUTOMATA_LIB_TEST) $(LIB_DIR)
	rm $(AUTOMATA_OBJS_TEST)

cp_libautomata.a: $(AUTOMATA_OBJS)
	ar -ru cp_libautomata.a $(AUTOMATA_OBJS)
	mv cp_libautomata.a $(LIB_DIR)
	rm $(AUTOMATA_OBJS)

all:
	make source_automata_compiled_class.o
	make rules.o
	make test_libautomata.a
	make run_sim.o



