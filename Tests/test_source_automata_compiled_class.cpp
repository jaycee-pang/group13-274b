#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <fstream>

#include "source_automata_compiled.h"

int main(void)
{
    std::string file = "user_input.txt";
    std::string upload = "user_upload.txt";

    int test_width = 5;
    int test_height = 6;

    BoundaryType bType = BoundaryType::Periodic;
    NeighborhoodType nType = NeighborhoodType::VonNeumann;

    CellularAutomata basic_automata(test_width, test_height);
    basic_automata.step();

    CellularAutomata test_automata(test_width, test_height, 2, 2, bType, nType, defaultInitFunc, MajorityRule, file);
    test_automata.step();
    test_automata.displayGrid();
    std::cout << std::endl;
    test_automata.step();
    test_automata.displayGrid();
    std::cout << std::endl;

    CellularAutomata upload_automata(file, 1, upload);
    upload_automata.displayGrid();
    std::cout << std::endl;

    upload_automata.step();
    upload_automata.displayGrid();
    std::cout << std::endl;

    return 0;
}