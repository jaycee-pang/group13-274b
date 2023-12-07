# MSSE Berkeley
# CHEM 274B: Software Engineering Foundations for Molecular Sciences
## November 2023

## USAGE
Create and run disease_automata_executable
<pre> make test_disease_automata</pre>

## UPDATES

11.26.2023
- Laura added Makefile, README to /Source
    - Note: Makefile doesn't really do anything yet lol
- Added `disease_automata.cpp` to /Source
    -  Began adding cpp implementation of disease automata using `Source.cpp`

12.2.2023
- Moved `disease_automata.cpp` somewhere else to create a general purpose library in /Source 
- Added `automata_class.cpp` to /Source 

12.4.2023
- Added `myclass.h` in /Include for prototypes to `automata_class_functions.cpp`
- Added `automata_class_functions.cpp` in /Source to hold rule functions
- Added `user_input.txt` to hold user input to be read from `automata_class.cpp`
- Updated `automata_class.cpp`:
    - apply_rules() accepts rules from myclass.h
    - Constructor updated to initialize
    - created run_simulation() function to run steps the number of inputted time steps