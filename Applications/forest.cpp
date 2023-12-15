// MSSE Berkeley
// CHEM 274B: Group 13, Final Project

// Cellular Automata Application: model a forest environment 
// Directory path: final/Applications
// Uses cellular automata to model the evolution of a forest organism. 
// There are 6 states re

#include "neighborhoods.h"
#include <iostream>
#include <vector>
#include <random>
#include <cstdlib>
#include <algorithm>
#include <functional>
#include <string> 
#include <map> 
#include "source_automata_compiled.h"  

const int Empty = 0; 
const int Soil = 1; 
const int Seed = 2; 
const int Sprout = 3; 
const int Leaves = 4; 
const int Flower = 5; 

// auto init_forest_with_prob(double fertilityProb) {
//     return [=](int x, int y, int max_states) -> int {
//         // put seeds
//         double prob = static_cast<double>(rand()) / RAND_MAX;
//         if (prob < fertilityProb / 2) {
//             return Seed;
//         } else if (prob < fertilityProb) {
//             return Soil;
//         } else {
//             return Empty;
//         }
//     };
// }

std::function<int(int, int, int, double)> init_forest = [](int x, int y, int max_states, double fertilityProb) -> int
{   
    // put seeds 
    double prob = static_cast<double>(rand()) / RAND_MAX; 
    if (prob < fertilityProb/2) {
        return Seed;
    }
    else if (prob < fertilityProb) {
        return Soil; 
    }
    else { return Empty; }
};
int forest_rules(int current_state, int num_states, std::vector<int> neighborhood_states) {
    
    if (current_state == 0) {
        
        int soilCount=std::count(neighborhood_states.begin(), neighborhood_states.end(), Soil);
        if (soilCount >= 2) {
            std::cout << "Seeded!" <<std::endl;
            return Seed; 
        }
    }
    else if (current_state == Seed) {

        int soilCount = std::count(neighborhood_states.begin(), neighborhood_states.end(), Soil);
        int flowerCount = std::count(neighborhood_states.begin(), neighborhood_states.end(), Flower);
        if (soilCount >=1 || flowerCount >=1 ) {
            std::cout << "Seed sprouted!" << std::endl;
            return Sprout; 
        }
    }
    // else if (current_state == Sprout) {
    //     int soilCount = std::count(neighborhood_states.begin(), neighborhood_states.end(), Soil);
    //     if (soilCount >=2) {
    //         return Leaves; 
    //     }
    // }
    else if (current_state == Sprout) {
        int soilCount = std::count(neighborhood_states.begin(), neighborhood_states.end(), Soil);
        int emptyCount = std::count(neighborhood_states.begin(), neighborhood_states.end(), Empty);
        int sproutCount = std::count(neighborhood_states.begin(), neighborhood_states.end(), Sprout);
        int leafCount = std::count(neighborhood_states.begin(), neighborhood_states.end(), Leaves);
        if (emptyCount >=1 || soilCount >=2 || leafCount >=1 ) {
            std::cout << "Space for leaves to grow!" <<std::endl;
            return Leaves; 
        }
    }
    else if (current_state == Leaves) {
        std::cout << "Flowers bloomed!" <<std::endl;
        return Flower; 
    }
    else if (current_state == Flower) {
        int soilCount = std::count(neighborhood_states.begin(), neighborhood_states.end(), Soil);
        int emptyCount = std::count(neighborhood_states.begin(), neighborhood_states.end(), Empty);
        int flowerCount = std::count(neighborhood_states.begin(), neighborhood_states.end(), Flower);
        int leafCount = std::count(neighborhood_states.begin(), neighborhood_states.end(), Leaves);
        if (emptyCount <= 1 || soilCount <= 1 || flowerCount >=4 || leafCount >= 6) { // if it's too crowded, 
            std::cout << "Flower still in bloom" <<std::endl;
            return Flower;
        } 
        else { 
            std::cout << "Flower was too croweded. Back to soil" <<std::endl;
            return Soil;
        }
        
    }
    else { return current_state; }
}; 
int main(void) {
    int width = 15;
    int height = 15;
    int num_states = 6;
    int radius = 1;
    std::string file = "forest_input.txt";
    std::string outfile = "forest_simulation";
    int num_steps = 10;

    CellularAutomata forest(
        width,
        height,
        num_states,
        radius,
        BoundaryType::Fixed,        
        NeighborhoodType::Moore,  
        std::bind(init_forest, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, 0.5),
        std::bind(forest_rules, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3),
        outfile
    );
    forest.setRuleFunction(std::bind(forest_rules, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    std::cout << "States:" << std::endl; 
    std::cout << "|| Empty || Soil || Seed || Sprout || Leaves || Flower ||" <<std::endl;
    std::cout <<"Starting simulation"<<std::endl;
    forest.displayGrid(); 
    for (int i = 0; i < num_steps; i++ ) {
        forest.step(); 
        forest.displayGrid(); 
    }
    std::cout << "Simulation complete!"<< endl << "Results: " << std::endl;
    std::map < int, std::string> state_map = {{0, "Empty"}, {1, "Soil"}, 
                                                {2, "Seed"}, {3,"Sprout"},
                                                {4:"Leaves"}, {5, "Flower"} };
    int state_count; 
    for (const auto & pair: state_map){
        state_count = forest.countCellState(pair.first);
        std::cout << pair.second << " count: " << state_count << std::endl;
    }
    

    return 0;
}