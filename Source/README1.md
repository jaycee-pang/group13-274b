# MSSE Berkeley
# CHEM 274B: Software Engineering Foundations for Molecular Sciences
## December 2023

## USAGE
Create automata static library
<pre> make test_libautomata.a </pre>

## Applications
`disease_simulation.cpp` - simulates influenza virus spread in a 10x10 area
[mortality rate data](https://wonder.cdc.gov/controller/datarequest/D158;jsessionid=EDF51154784AE93C2EB5E7BA5C8F)
[infectivity rate data](https://www.cdc.gov/mmwr/volumes/72/wr/mm7208a1.htm#:~:text=Among%2015%2C678%20unvaccinated%20person%2Ddays,A%20virus%20infection%20was%2071%25.)
[rate of flu vaccination USA](https://grady.uga.edu/news/more-adults-likely-to-get-a-flu-vaccination-than-receive-an-updated-covid-19-vaccine/#:~:text=According%20to%20the%20Centers%20for,2022%2D23%20was%2049%25.)

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

### TODO
###### Laura

###### Jaycee
- [``] complete 'forest_simulation' script in /Applications

###### Shirley
Place in separate .cpp file in Source:
- [``] complete graphing utils
- [``] read simulation vector and timesteps from .txt file, output to graph, create gif

###### Jeffrey
