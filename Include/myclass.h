// Chem 274B: Software Engineering Fundamentals for
//            Molecular Sciences  
// Creator: Laura Jones, Group 13
// Date Created: 12/4/2022
//
//  myclass.h contains all necessary information about the classes
//              created in /Source to be linked to their static libraries
//
#pragma once    // Ensures that this file is only included once
                // during compilation
#include <vector>   //allow for grid 

int von_neumann_rules(int, int, const std::vector<std::vector<int>>&);