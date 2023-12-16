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

Users can select the parameters to use for their cellular automata specifying: 
    - initialization of the gird 
    - rule functions 
    - number of states 
    - width and height of the grid 
    - specify rule function at a certain time step 
Cellular Automata can be constructed by specifying the parameters directly as arguments, or can be loaded in from a txt file. 
Users can choose from the default rule function, the provided rule functions (majority, straight, or neighbor), or set their own. They can also set a custom initialization function or use the default. 

Running a simulation after the cellular automata has been set up requires calling the `step` function. If you would like a different rule for a different step, call `setRuleFunction`.

Alternatively, the `input_simulation` function to input all of the parameters for the cellular automata, and run a simulation for the specified number of time steps. 

Visualization is done by running the python script found in Utils/ with the output text file for the simulation. It produces a gif showing the grid for all of the steps of the simulation. 

Two applications of our cellular automata are found in Applications/. One models disease spreading with set infection rate and other parameters pertaining to a disease simulation such as vaccination rate. The other application models the evolution of a plant based on a set fertility rate and rule function determining growth conditions. 

The directory structure is as follows:

LIST OF SUBDIRECTORIES IN THIS DIRECTORY:
- Bin/ : This subdirectory contains all the executable program (test program)
	
- Lib/ : This subdirectory contains all library object files compiled from 
        the functionalities used by the cellular automata. (.a)
		
- Include/: This directory contains all the APIs in the form of  
        function prototypes stored in .h include files
		
- Source/ : This directory contains all the source code with the
        functionality implemented in C++. This includes the Cellular Automata class and its initialization steps, update steps, and outputs as well as its rule functions. 
		
- Tests/: Test programs used to test the functionalities of our cellular automata by running simulations of various parameters. 
		
- Utils: Contains all the source files that implement utilities
        for grid visualization. 

LIST OF FILES IN THIS DIRECTORY:
- README:(is this file) 

- Makefile: Makefile with global make command. See the Makefile
        for possible 'make commands' from this directory level.
- reflections: individual reflections on this project
