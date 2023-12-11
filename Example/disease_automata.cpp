// MSSE Berkeley
// CHEM 274B: Group 13, Final Project

// Cellular Automata Application: Disease Spreading Simulation

// This script determines the step-wise interactions of our cellular automata grid
// with regards to the following user inputs:
//      - Type of disease (covid, strep throat, zombie virus)
//      - Size of population
//      - Percent of population wearing masks daily
//      - Hand washing frequency

// Questions: 
//  - we don't need to make each time step a global variabel, right?

#include <iostream> 
#include <vector>   //allows for 2d grid
#include <random>   //allows for random number generator in init function

#include "Source.h"

int temp_init_function(int j, int k)
//function that will set initial state of each cell on graph
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    //define states: healthy(0), infected(1), empty cell(0)
    const double infection_rate = 0.2;
    const double density = 0.4;    //probability of disease spreading, density of humans on graph

    if(dis(gen) < infection_rate)
    {
        return 2;   //cell is an infected person
    }
    else if (dis(gen) < density)
    {
        return 1;   //cell is a person
    }
    else{
        return 0;   //cell empty
    }

}

void step(std::vector<std::vector<int>>& grid)
{
    std::vector<std::vector<int>>new_grid;  //new grid, has changes from time step
    //TODO: determine what occurs at each time step to see if disease spreads
    
    update_grid(grid, new_grid);
}


int main(void)
{
    //set default rules and size for graph
    int size = 10;
    int i, j = 0;   //just to fill the space for the temp init function
    std::vector<std::vector<int>> grid;
    
    //set graph and initial conditions
    grid = initialize_grid(size, int(temp_init_function)(int, int)); //
    //create a graph, ask user for rules and apply rules
    grid = apply_rules(grid, int(rule_function) (int, int));  //goes into square, check if anything 
    //around it is diseased, then sets that thing as a 
    for(int i = 0; i < 100; i++)    //100 time steps
    {
        step(grid);    
    }
    
    //TODO: print output of a few timesteps for graph
    return 0;
}

/*
    Python Implementation of the step function for forest fire automata:

    def step():
    global time, config, nextConfig

    time += 1

    for x in range(width):
        for y in range(height):
            state = config[y, x]
            if state == fire:
                # cf. Sayama, "the burning tree is completely charred after one time step"
                state = char
            elif state == tree:
                for dx in range(-1, 2):
                    for dy in range(-1, 2):
                        if config[(y+dy)%height, (x+dx)%width] == fire:
                            state = fire
            nextConfig[y, x] = state

    config, nextConfig = nextConfig, config
*/

//setup function will call jupyternotebook thing to accept text-file settings