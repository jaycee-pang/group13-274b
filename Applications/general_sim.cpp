// MSSE Berkeley
// CHEM 274B: Group 13, Final Project

// Cellular Automata Application: model a forest environment 
// Directory path: final/Applications
// Uses cellular automata to model a forest. 
#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <fstream>
#include <limits> 
#include <string> 
#include "source_automata_compiled.h"
std::vector<int> CA_arguments() {
    std::vector<int> userInput(6); 
    std::cout << "Please enter the conditions for the cellular automata"<<std::endl;
    std::vector<std::string> messages= {
        "Enter the width of the grid: ",
        "Enter the height of the grid: ",
        "Enter the number of states: ",
        "Enter the neighborhood type (0 for VonNeuman, 1 for Moore): ",
        "Enter the boundary condition (0 for periodic, 1 for fixed, 2 for cutoff): "
    };

    for (int i = 0; i < messages.size(); ++i) {
        do {
  
            std::cout << messages[i];
            std::cin >> userInput[i];
            if (std::cin.fail()) {
                std::cin.clear();  
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  
                std::cout << "Invalid input. Please enter a valid integer.\n";
            } else {
                switch (i) {
                    case 0:
                        if (userInput[i] <= 0) {
                            std::cout << "Invalid input. Please enter a positive integer.\n";
                            continue; 
                        }
                        break;
                    case 1:
                        if (userInput[i] <= 0) {
                            std::cout << "Invalid input. Please enter a positive integer.\n";
                            continue;  
                        }
                        break;
                    case 2:
                        if (userInput[i] > userInput[0]*userInput[1]/2) {
                            int max_states = userInput[0]*userInput[1]/2; 
                            std::cout << "Too many states. Please enter an integer less than " << max_states <<".\n";
                            continue;  
                        }
                        break;
                    case 3:
                        if (userInput[i] > 1) {
                            std::cout << "Invalid input. Please enter 0 or 1.\n";
                            continue; 
                        }
                        break;
                    case 4:
                        if (userInput[i] > 2) {
                            std::cout << "Invalid input. Please enter 0, 1, or 2.\n";
                            continue;  
                        }
                        break;
                    default:
                        break;
                }
                break;
            }
        } while (true);  
    }
    return userInput; 

}

int main(void) {

    std::vector<int> userInput = CA_arguments(); 
    int height = userInput[0];
    int width = userInput[1]; 
    int num_states = userInput[2]; 
    int neighborhood = userInput[3]; 
    NeighborhoodType ntype; 
    if (neighborhood == 0) {
        ntype = NeighborhoodType::VonNeumann;
    }
    else if (neighborhood ==1) {
        ntype = NeighborhoodType::Moore; 
    }
    else {ntype = NeighborhoodType::VonNeumann; } 
    int boundary = userInput[4]; 
    BoundaryType btype; 
    if (boundary == 0) {
        btype = BoundaryType::Periodic; 
    }
    else if (boundary == 1) {
        btype = BoundaryType::Fixed; 
    }
    else if (boundary == 2) {
        btype = BoundaryType::Cutoff; 
    }
    else {btype = BoundaryType::Fixed; }
    int rule = userInput[5]; 
    int radius = 1; 
    std::string outfile = "output_user_choice.txt";
    CellularAutomata CA(
        width,
        height,
        num_states,
        radius,
        btype,
        ntype,
        outfile);
    int num_steps; 
    do {
        std::cout << "Enter the number of steps for the simulation: ";
        cin >> num_steps; 
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid integer."<<std::endl;
        }
    } while (true);
    // "Enter the rule function to use: (0 for default, 1 for majority, 2 for straight, 3 for conditional neighbor): 
    std::cout << "Starting simulation" << std::endl;
    CA.displayGrid();
    do {
        std::cout <<"Enter the number of steps for the simulation:"
    
    for (int i = 0; i< num_steps; i++) {
        std::cout << "0: Majority \n1: Straight \n2: Conditional neigbor " <<std::endl;
        std::cout << "Enter rule to apply for step " << i + 1 <<": ";
        int userRule; 
        std::cin >> userRule;
        switch (userRule)
        {
        case 0:
            CA.setRuleFunction(MajorityRule);
            break;
        case 2:
            CA.setRuleFunction(StraightRule);
            break;
        case 3:
            CA.setRuleFunction(NeighborRule);
            break;
        default:
            CA.setRuleFunction(defaultRuleFunc);
            break;
        }
        CA.step(); 
        CA.displayGrid(); 
    }
    std::cout<<"Simulation complete!"<<std::endl;

     
    

    // "Enter the width of the grid: ",
    //     "Enter the height of the grid: ",
    //     "Enter the number of states: ",
    //     "Enter the neighborhood type (0 for VonNeuman, 1 for Moore): ",
    //     "Enter the boundary condition (0 for periodic, 1 for fixed, 2 for cutoff): ",
    //     "Enter the rule function to use: (0 for default, 1 for majority, 2 for straight, 3 for conditional neighbor):  "
  
    return 0;
}