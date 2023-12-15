// Chem 274B: Software Engineering Fundataions for
//            Molecular Sciences 
// Group 13 
// 
// Directory Path: final/Source/ 
//
// Date Created: December 10, 2023
// Date Updated: December 14, 2023 
// 
// C++ implementation of a cellular automata class's rule functions
// Contains functions for required rule functions: 
//      - Majority Rule: new cell state is what the majority of neighbors are 
//      - Straight Rule: new cell state is the next cell state 
//      - Neighbor Rule: based on neighbors
// All of the rule functions take in the current cell state, the maximum cell states, 
// and a vector of the states of its neighbors (specific to object's neighborhood and boundary and radius),
// and updates the cell state based on those neighbors. 
//  
// The API (include) file is source_automata_compiled.h, which includes prototypes
// of the functions defined in this file.

#include <vector>
#include <map>
#include <algorithm>

#include "source_automata_compiled.h"


// Turn to what the majority of the neighbors are 
int MajorityRule(int current_state, int num_states, std::vector<int> neighborhood_states)
{
    std::map<int, int> state_counts;
    for (int state : neighborhood_states) 
    {
        int count = std::count(neighborhood_states.begin(), neighborhood_states.end(), state);
        state_counts[state] = count; 
    }
    int max_count = 0;
    int max_state = 0;
    bool tie = false; 
    for (const auto &it : state_counts)
    {
        if (it.second > max_count)
        {
            max_count = it.second;
            max_state = it.first;
            tie = false; 
        }
        else if (it.second == max_count ) {
            tie = true; 
        }
    }
    if (!tie && max_count > neighborhood_states.size())
    {
        return max_state;
    }
    else
    {
        return current_state;
    }
}

// turn to the next state, if at the max number of states, stay the same 
int StraightRule(int current_state, int num_states, std::vector<int> neighborhood_states)
{
    if (current_state == num_states)
    {
        return num_states;
    }
    else
    {
        return current_state + 1;
    }
}

// if any of the neighbors are at a higher state, turn to that state. else, stay the same 
int NeighborRule(int current_state, int num_states, std::vector<int> neighborhood_states)
{
    if (current_state == num_states)
    {
        return num_states;
    }
    else
    {
        for (const auto &it : neighborhood_states)
        {
            if (it == current_state + 1)
            {
                return it;
            }
            
        }
        return current_state;
    }
}