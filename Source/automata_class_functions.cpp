// Chem 274B: Software Engineering Fundamentals for
//            Molecular Sciences  
// Creator: Laura Jones
// Date Created: 12/4/2023
// Last revisited: 12/4/2023
//
//  This functions file contains any necessary external functions for the
//          cellular automata class, compiled in static libraries
//
#pragma once    // Ensures that this file is only included once
                // during compilation
#include <vector>   //allow for grid

        //rule function
        int von_neumann_rules(int i, int j, std::vector<std::vector<int>> grid) //what's configuring around the index. The 4 directly-adjacent cells
        {
            int state;  //saves the int value of the state that the cell is in
            int size = grid.size();
            for(int x = 0; x < size; x++)
            {
                for(int y = 0; y < grid.size(); y++)
                {
                    state = grid[x][y];
                    if(state == 2) //if the cell affected in the previous timestep
                    {
                        state = 3;  //now that cell will be dead TODO: implement recovery chance?
                    }
                    else if(state == 1) //if cell is unaffected
                    {
                        for(int dx = -1; dx < 1; dx++)
                        {
                            for(int dy = -1; dy < 1; dy++)
                            {
                                if(grid[(y+dy)%size][(x+dx)%size] == 2)  //if anything in a moore neighborhood
                                {                                           // is on infectious...
                                    state = 2;
                                }
                            }
                        }
                    }
                    //grid_[x][y] == state;
                }
            }
            //periodic() or fixed()
            return state;
        }