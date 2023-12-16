// Chem 274B: Software Engineering Fundataions for
//            Molecular Sciences 
// Group 13 
// 
// Directory Path: final/Source/ 
//
// Date Created: December 10, 2023
// Date Updated: December 14, 2023 
// 
// function to run the simulation with CA input parameters. 
#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <fstream>

#include "source_automata_compiled.h" 

// CellularAutomata::CellularAutomata(int width, int height, int num_states, int radius,
//                                    BoundaryType bType,
//                                    NeighborhoodType nType,
//                                    std::function<int(int, int, int)> customInitFunc,
//                                    std::function<int(int, int, const std::vector<int> &)> customRuleFunc,
//                                    std::string file_path)
int input_simulation(int width, int height, int num_states, int radius, BoundaryType btype, 
                        NeighborhoodType ntype, std::function<int(int, int, int)> customInitFunc, 
                        std::function<int(int, int, const std::vector<int> &)> customRuleFunc, 
                        std::string file_path,
                        int sim_steps) {
    CellularAutomata CA(width, height, num_states, radius, btype, ntype, 
                        customInitFunc, 
                        customRuleFunc, 
                        file_path);
    std::cout <<"Starting simulation."<<std::endl;
    CA.displayGrid(); 
    for (int i = 0; i < sim_steps; i++ ) {
        CA.step(); 
        CA.displayGrid(); 
    }
    std::cout <<"Simulation complete." <<std::endl;
    // successful run 

    std::cout << "Results:"<<std::endl;
    for (int i = 0; i < num_states; i ++) {
        int count = CA.countCellState(i); 
        std::cout << "State [" << i << "]: "<<count<<std::endl;
    }
    return 0; 
  

}
