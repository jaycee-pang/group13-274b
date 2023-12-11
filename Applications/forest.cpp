// MSSE Berkeley
// CHEM 274B: Group 13, Final Project

// Cellular Automata Application: model a forest environment 
// Directory path: final/Applications
// Uses cellular automata to model a forest. 
// with regards to the following user inputs:
//      - Events: draught, fire, famine, flood, rain

#include <iostream> 
#include <vector>  
#include <cstdlib> 
#include <ctime>  
#include <random>  
#include <algorithm> 
#include "Source.h"
#include "neighborhoods.h"
const int EMPTY = 0;
const int FLORA = 1;
const int TREE = 3; 
const int SPROUT = 5; 
const int FAUNA = 2;
const int BABY = 4; 
const int ADULT = 6; 

enum State {
    EMPTY, FLORA, TREE, SPROUT, FAUNA, BABY, ADULT
}; 

struct Cell {
    State state; 
    Cell(State s) : state(s) {}
};
std::vector<std::vector<Cell>> grid;
// in moore: sum += static_cast<int>(grid[i][j].state); 

// user should specify probabilities? 
// test function takes input from user (or generate txt file )
// user inputs size, 
std::vector<std::pair<int, std::string>> states; 
// do we need state information (neighbor's states) 
// does this ^ need to go in neighborhood function 
// make a class for cellular automata, need to acces 
int init_forest(int i, int j, double emptyProb, double floraProb, double faunaProb) {
    double randValue = static_cast<double>(rand()) / RAND_MAX; 
    if (randValue < emptyProb) {
        return EMPTY;
    } 
    else if (randValue < emptyProb + floraProb) {
        return FLORA;
    } 
    else {
        return FAUNA;
    }
}
void step(std::vector<std::vector<int>>& grid, int row, int col)
{

}



int forest_rules(const std::vector<std::vector<int>>& grid, int row, int col) {
    int sum = moore(grid, row, col, PERIODIC);
    if (grid[row][col] == EMPTY) {
        if (sum == 1) {         // if one neighbor
            return FLORA;   // if empty cell has one neighbor, become flora
        }
    } 
    else if (grid[row][col] == SPROUT) {
        if (sum > 1 && sum < 5) {         
            return FLORA; 
        }
    }
    else if (grid[row][col] == FLORA && ) {         // maybe if all of these conditions + an empty cell nearby becomes a sprout
        if (sum >= 4 && sum < 7) {         // if 4 or more neighbors and less than 7
            return TREE; // if a flora cell has 4-7 neighbors, become tree
        }
    } 
    else if (grid[row][col] == FLORA) {     // possible to change other neighbor cells? 
        if (sum >= 7) {  // if 7 or more neighbors
            return SPROUT; // flora cell has 7 or more neighbors, become sprout
        }
    }

    else if (grid[row][col] == BABY) { 
        if (sum > 1 && sum < 4) {               // if it's a baby and 1<sum<4, become fauna  
            return FAUNA; 
        }
    } 
    else if (grid[row][col] == FAUNA) {
        if (sum >= 4 && sum < 7) {         // if 4 or more neighbors and less than 7
            return ADULT; // if a fauna cell has 4-7 neighbors, become big_fauna
        }
    } 
    else if (grid[row][col] == ADULT) {     // possible to change other neighbor cells? 
        if (sum >= 7) {  // if 7 or more neighbors
            return BABY; // flora cell has 7 or more neighbors, become sprout
        }
    }
     
    
}

int neighbor_states(const std::vector<std::vector<int>>& grid, int row, int col, int STATE, int boundary_type, int radius) {
    int count = 0; 
    for (int i = row - radius; i <= row + radius; i++) {
        for (int j = col - radius; j <= col + radius; j++) {
            if (i == row && j == col) {
                continue; 
            }
            if (grid[i][j] == STATE) {
                count++;
            }
        }
    }
    return count; 
}

int forest_rules2(const std::vector<std::vector<int>>& grid, int row, int col) {
    int sum = moore(grid, row, col, PERIODIC);
    if (grid[row][col] == EMPTY) {
        if (sum == 1) {         // if one neighbor
            return FLORA;   // if empty cell has one neighbor, become flora
        }
    } 
    else if (grid[row][col] == SPROUT && neighbor_states(grid, row, col, SPROUT,)) {
        if (sum > 1 && sum < 4) {         
            return FLORA; 
        }
    }
    else if (grid[row][col] == FLORA) {         // maybe if all of these conditions + an empty cell nearby becomes a sprout
        if (sum >= 4 && sum < 7) {         // if 4 or more neighbors and less than 7
            return TREE; // if a flora cell has 4-7 neighbors, become big_flora
        }
    } 
    else if (grid[row][col] == FLORA) {     // possible to change other neighbor cells? 
        if (sum >= 7) {  // if 7 or more neighbors
            return SPROUT; // flora cell has 7 or more neighbors, become sprout
        }
    }

    else if (grid[row][col] == BABY) { 
        if (sum > 1 && sum < 4) {               // if it's a baby and 1<sum<4, become fauna  
            return FAUNA; 
        }
    } 
    else if (grid[row][col] == FAUNA) {
        if (sum >= 4 && sum < 7) {         // if 4 or more neighbors and less than 7
            return ADULT; // if a fauna cell has 4-7 neighbors, become adult
        }
    } 
    else if (grid[row][col] == ADULT) {     // possible to change other neighbor cells? 
        if (sum >= 7) {  // if 7 or more neighbors
            return BABY; // flora cell has 7 or more neighbors, become sprout
        }
    }
     
     


}

