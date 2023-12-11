# MSSE Berkeley
# CHEM 274B: Software Engineering Foundations for Molecular Sciences
## December 2023

## USAGE
Create and run automata_class executable
<pre> make test_disease_auto</pre>

Create automata static library
<pre> make libautomata.a </pre>

## UPDATES

11.26.2023 - Laura
- added Makefile, README to /Source
    - Note: Makefile doesn't really do anything yet lol
- Added `disease_automata.cpp` to /Source
    -  Began adding cpp implementation of disease automata using `Source.cpp`

12.2.2023 - Laura
- Moved `disease_automata.cpp` somewhere else to create a general purpose library in /Source 
- Added `automata_class.cpp` to /Source 

12.4.2023 - Laura
- Added `myclass.h` in /Include for prototypes to `automata_class_functions.cpp`
- Added `automata_class_functions.cpp` in /Source to hold rule functions
- Added `user_input.txt` to hold user input to be read from `automata_class.cpp`
- Updated `automata_class.cpp`:
    - apply_rules() accepts rules from myclass.h
    - Constructor updated to initialize
    - created run_simulation() function to run steps the number of inputted time steps

12.6.2023 - Laura
- implemented source.cpp functions into automata class (`automata_class.cpp`)
- began implementing von neumann function into automata class
    - TODO: ran into problem on line 51 of automata class, generating a weird compiler error
    - try running to see error with:
<pre> make test_disease_auto </pre>

12.10.2023 - Laura
- Solved weird compiler error. I just hadn't included the `automata_class_functions.cpp` in a library and had it included yet
- Updated Makefile to be able to generate static library for Source

12.11.2023 - Laura
- fixed von_neumann_rules to allow for boundary conditions
- __Jaycee, jw what the 'return sum' lines are for in your moore function?__
- __can I add moore.cpp to the automata_class_functions.cpp file?__
- __??? Is it ok that I just placed all your initialization functions in automata_class???__
### TODO
- [``] fix von neumann function so it's actually... von neumann
- [``] allow input for up to 5 states
- [`w`] allow for function decision between moore or von_neumann
- [`c`] allow for specification of x and y dimensions of graph
- [``] implement reading from `user_input.txt`