// MSSE Berkeley
// CHEM 274B: Group 13, Final Project

// Group 13
// Date Created: 12/14/2023 
// Date Updated: 12/14/2023
// Directory path: final/Tests
// 
// Cellular Automata 
// Test the neighbor conditional rules function with cellular automata with: 
//      neighborhood types: Von Neumman, Moore 
//      boundary types: Periodic, cutoff, fixed 

#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <fstream>

#include "source_automata_compiled.h"

int main(void)
{ 
    int width = 5; 
    int height = 5; 
    int num_states = 3; 
    int radius = 1; 
    int sim_steps = 6; 

    // Test01: Periodic, VonNeumann 
    BoundaryType btype = BoundaryType::Periodic; 
    NeighborhoodType ntype = NeighborhoodType::VonNeumann; 
    std::string file01 = "neighbor_periodic_vn.txt";
    int test01 = input_simulation(width, height, num_states, radius, btype, 
                        ntype, defaultInitFunc, 
                        NeighborRule, 
                        file01,
                        sim_steps) ;


    // Test02: Periodic, Moore 
    std::string file02 = "neighbor_periodic_moore.txt";
    btype = BoundaryType::Periodic; 
    ntype = NeighborhoodType::Moore; 
    int test = input_simulation(width, height, num_states, radius, btype, 
                        ntype, defaultInitFunc, 
                        StraightRule, 
                        file02,
                        sim_steps) ;

    // Test03: Cutoff, VN
    btype = BoundaryType::Cutoff; 
    ntype = NeighborhoodType::VonNeumann; 
    std::string file03 = "neighbor_cutoff_vn.txt";
    int test03 = input_simulation(width, height, num_states, radius, btype, 
                        ntype, defaultInitFunc, 
                        NeighborRule, 
                        file03,
                        sim_steps) ;
    // Test04: Cutoff, Moore
    btype = BoundaryType::Cutoff; 
    ntype = NeighborhoodType::Moore; 
    std::string file04 = "neighbor_cutoff_moore.txt";
    int test04 = input_simulation(width, height, num_states, radius, btype, 
                        ntype, defaultInitFunc, 
                        NeighborRule, 
                        file04,
                        sim_steps) ;
    
    // Test05: Fixed, VN
    btype = BoundaryType::Fixed; 
    ntype = NeighborhoodType::VonNeumann; 
    std::string file05 = "neighbor_fixed_vn.txt";
    int test05 = input_simulation(width, height, num_states, radius, btype, 
                        ntype, defaultInitFunc, 
                        NeighborRule, 
                        file05,
                        sim_steps) ;
    
    // Test06: Fixed, Moore
    btype = BoundaryType::Fixed; 
    ntype = NeighborhoodType::Moore; 
    std::string file06 = "neighbor_fixed_moore.txt";
    int test06 = input_simulation(width, height, num_states, radius, btype, 
                        ntype, defaultInitFunc, 
                        NeighborRule, 
                        file06,
                        sim_steps) ;
    return 0;


}