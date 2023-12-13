// Chem 274B: Software Engineering Fundamentals for
//            Molecular Sciences  
// Creator: Laura Jones
// Date Created: 12/4/2023
// Last revisited: 12/11/2023
//
//  This functions file contains any necessary external functions for the
//          cellular automata class, compiled in static libraries
//
//          Input : indeces for position on grid, grid itself
//          Output: integer value for new state of position on grid

#include <vector>   //allow for grid
#include <iostream> //allow for deubugging
#include "myclass.h"

    //rule function - takes into account 4 adjacent cells to set state of cell in question
    int von_neumann_rules(int i, int j, const std::vector<std::vector<int>>& grid, 
                            int boundary_type, int neighborhood_type)   //pass indexes, grid by ref
    {                                               
        int state;  //saves the int value of the state that the cell is in
        int row;    //used to ensure fixed/periodic boundaries followed
        int col;
        int row_size = (int)grid.size();    //length of grid
        int col_size = (int)grid[0].size(); //height of grid
        state = grid[i][j]; //state of focused cell
          
        if(state == 2) //if the cell affected in the previous timestep
        {
            state = 3;  //now that cell will be dead
        }
        else if(state == 1 && boundary_type == 1) //if cell is unaffected and boundary type is fixed
        {
            //get_neighbors(boundary_type, grid)
            for(int dx = -1; dx < 1; dx++)
            {
                for(int dy = -1; dy < 1; dy++)
                {
                    if(dx == 0 && dy == 0){ //skip central cell
                        continue;
                    }
                    row = (i+dx)%row_size;  //x deviation around central cell
                    col = (j+dy)%col_size;  //y deviation around central cell

                    if(row <= 0 || row > row_size || col <= 0 || col > col_size)   //if out of fixed boundary
                    {
                        break;   //skip this out-of-bounds cell
                    }
                    else if(grid[row][col] == 2)    // if the adjacent cell has its state being 'infectious'...
                    {
                        state = 2;  //cell will now be in state 2, infected
                    }  
                }
            }
        }
        else if (state == 1 && boundary_type == 2) //if cell is unaffected and boundary type is periodic
        {
             for(int dx = -1; dx < 1; dx++)
            {
                for(int dy = -1; dy < 1; dy++)
                {
                    if(dx == 0 && dy == 0){ //skip central cell
                        continue;
                    }
                    row = (i+dx)%row_size;  //x deviation around central cell
                    col = (j+dy)%col_size;  //y deviation around central cell
                     
                    if(row <= 0 || row > row_size || col <= 0 || col > col_size)   //if out of fixed boundary
                    {
                        row = (i+dx+row_size)%row_size;  //wrapped x deviation
                        col = (j+dy+col_size)%col_size;  //wrapped y deviation
                    }
                    if(grid[row][col] == 2)    // if the adjacent cell has its state being 'infectious'...
                        state = 2;  //cell will now be in state 2, infected
                    }   
                }
            } 
        return state;
    }