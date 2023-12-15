
#include <iostream> //allow for debugging
#include <string>   //allow for string of filepath

#include "source_automata_compiled.h"

int main(void)
{
    //Test that object can be generated from file-path
    std::string file_path_in = "../Bin/disease_simulation.txt";
    std::string file_path_out = "output_disease_sim.txt";
    CellularAutomata test_file_input(file_path_in, 6, file_path_out);

    
    return 0;
}