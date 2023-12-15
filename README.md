# Chem 274B: Software Engineering Fundamentals for
#            Molecular Sciences 
# University of California, Berkeley
# December 2023

# 
# Group 13
# Date Created: December 2023
#
# Directory Path: Final3/

This is the main directory for Group 13's final project. 
This is our implementation of a general purpose library of a cellular automata
that can be used in a variety of applications to model different phenomena. 

The directory structure is as follows:

LIST OF SUBDIRECTORIES IN THIS DIRECTORY:
- Bin/ : This subdirectory contains all the executable program (test program)
	
- Lib/ : This subdirectory contains all library object files compiled from 
        the functionalities used by the cellular automata. (.a)
		
- Include/: This directory contains all the APIs in the form of  
        function prototypes stored in .h include files
		
- Source/ : This directory contains all the source code with the
        functionality implemented in C++. This includes the Cellular Automata class and its initialization steps, update steps, and outputs as well as its rule functions. 
		
- Tests: Test programs used to test the functionalities of our cellular automata by running simulations of various parameters. 
		
- Utils: Contains all the source files that implement utilities
        like timing, I/O, and random array generation, other performance metric tools. 

LIST OF FILES IN THIS DIRECTORY:
- README:(is this file) 

- Makefile: Makefile with global make command. See the Makefile
        for possible 'make commands' from this directory level.

- .gitignore: For GitHub repository commits, currently preventing
        pushing object files (e.g., static libraries, linkable 
        object files, and some executables under Bin/)
- Answers-Assignment3: answers, algorithmic analysis, plots 
