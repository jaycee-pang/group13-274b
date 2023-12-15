// MSSE Berkeley
// CHEM 274B: Group 13, Final Project

// Group 13
// Date Created: 12/14/2023 
// Date Updated: 12/14/2023
// Directory path: final/Tests
// 
// Cellular Automata 
// Test the fixed rules function with cellular automata with: 
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
    std::string file01 = "straight_periodic_vn.txt";
    int test01 = input_simulation(width, height, num_states, radius, btype, 
                        ntype, defaultInitFunc, 
                        StraightRule, 
                        file01,
                        sim_steps) ;


    // Test02: Periodic, Moore 
    std::string file02 = "straight_periodic_moore.txt";
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
    std::string file03 = "straight_cutoff_vn.txt";
    int test03 = input_simulation(width, height, num_states, radius, btype, 
                        ntype, defaultInitFunc, 
                        StraightRule, 
                        file03,
                        sim_steps) ;
    // Test04: Cutoff, Moore
    btype = BoundaryType::Cutoff; 
    ntype = NeighborhoodType::Moore; 
    std::string file04 = "straight_cutoff_moore.txt";
    int test04 = input_simulation(width, height, num_states, radius, btype, 
                        ntype, defaultInitFunc, 
                        StraightRule, 
                        file04,
                        sim_steps) ;
    
    // Test05: Fixed, VN
    btype = BoundaryType::Fixed; 
    ntype = NeighborhoodType::VonNeumann; 
    std::string file05 = "straight_fixed_vn.txt";
    int test05 = input_simulation(width, height, num_states, radius, btype, 
                        ntype, defaultInitFunc, 
                        StraightRule, 
                        file05,
                        sim_steps) ;
    
    // Test06: Fixed, Moore
    btype = BoundaryType::Fixed; 
    ntype = NeighborhoodType::Moore; 
    std::string file06 = "straight_fixed_moore.txt";
    int test06 = input_simulation(width, height, num_states, radius, btype, 
                        ntype, defaultInitFunc, 
                        StraightRule, 
                        file06,
                        sim_steps) ;
    return 0;


}