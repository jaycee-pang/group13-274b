// Chem 274B: Software Engineering Fundamentals for
//            Molecular Sciences  
// Group 13
//
//  Directory path: final/Include 
//  
//  Include file for C++ implementations of a cellular automata library 
//  Includes enums for set boundary types: periodic, fixed, cutoff 
//  enum class for set neighborhood types: Moore, VonNeumann 
//  C++ cellular automata class that generates a grid with statesand applies rules and updates 
//  cell states based on states and the CA's boundary types and neighborhood types and 
//  the specified rule applied. 
//  Rule functions are alos included in this library: majority, straight, neighbor conditional
#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <fstream>
#include <algorithm>
#include <map> 
// enum class for selecting boundary type: 
//      Periodic: boundaries wrap around 
//      Fixed: fixed boundaries surrounding cells of interest 
//      Cutoff: no boundaries 
enum class BoundaryType
{
    Periodic,
    Fixed,
    Cutoff
};
// enum class for neighborhood: 
//      Moore: all cells based on radius that surround the cell are neighbors 
//      Von Neumann: all cells based on radius on East, West, North, adn South are neighbors 
enum class NeighborhoodType
{
    Moore,
    VonNeumann
};

// Default initialization function
extern std::function<int(int, int, int)> defaultInitFunc;

// Default rule function
extern std::function<int(int, int, const std::vector<int> &)> defaultRuleFunc;

class CellularAutomata
{
private:
    std::vector<std::vector<int>> grid;         // vector to hold cells 
    int gridWidth;      // width of grid 
    int gridHeight;     // height of grid 
    int num_states;     // how many states can the grid take on 
    int radius;         // radius: defines how far enighborhood extends 
    int num_steps;      // num steps in teh simulation taken
    BoundaryType boundaryType;          // select from enum class 
    NeighborhoodType neighborhoodType;      // select from enum class 
    std::function<int(int, int, int)> initFunc;         // function to initialize grid with states 
    std::function<int(int, int, const std::vector<int> &)> ruleFunc;        //rule function 

    std::string file_path;

    std::vector<int> getNeighborState(int x, int y);

public:
    CellularAutomata(int width, int height, int num_states = 2, int radius = 1,
                     BoundaryType bType = BoundaryType::Cutoff,
                     NeighborhoodType nType = NeighborhoodType::Moore,
                     std::function<int(int, int, int)> customInitFunc = defaultInitFunc,
                     std::function<int(int, int, const std::vector<int> &)> customRuleFunc = defaultRuleFunc,
                     std::string file_path = "automata_output.txt");

    CellularAutomata(const std::string &file_path, int time_step, std::string new_path = "loaded_automata_output.txt");

    ~CellularAutomata();

    void initializeGrid();

    void loadGrid(std::ifstream &in_stream, int target_time);

    void applyRules();

    void step();

    void setInitFunction(std::function<int(int, int, int)> newInitFunc);

    void setRuleFunction(std::function<int(int, int, const std::vector<int> &)> newRuleFunc);

    const std::vector<std::vector<int>> &getGrid() const;

    void displayGrid() const;

    int countCellState(int state_val) const;

    void save_grid();

    void save_params();
};


// Rule Functions 
//      Take in current state of cell, number of states possible, and states of neighbors 
//      Returns the state to transition to 

// Majority Rule: cell's new state is the state of the majority of its neighbors 
int MajorityRule(int current_state, int num_states, std::vector<int> neighborhood_states);
// Stright Rule: transition to the next state, if at the maximum number of states, stay the same 
int StraightRule(int current_state, int num_states, std::vector<int> neighborhood_states);
// get the neighbor states, if any neighbor is at the next state, turn to that state, else stay the same 
int NeighborRule(int current_state, int num_states, std::vector<int> neighborhood_states);
