#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <fstream>

#include "source_automata_compiled.h"

// Default initialization function
std::function<int(int, int, int)> defaultInitFunc = [](int x, int y, int max_states) -> int
{
    return rand() % max_states;
};

// Default rule function
std::function<int(int, int, const std::vector<int> &)> defaultRuleFunc = [](int cell_val, int max_states, const std::vector<int> &neighbor_vals) -> int
{
    return cell_val;
};

// Utility function to get all of the neighbor states for a given cell
std::vector<int> CellularAutomata::getNeighborState(int x, int y)
{
    std::vector<int> neighbors;
    for (int i = -radius; i <= radius; ++i)
    {
        for (int j = -radius; j <= radius; ++j)
        {
            if (i == 0 && j == 0) // if center coord
            {
                continue;
            }
            // account for von neumann boundaries
            if ((neighborhoodType != NeighborhoodType::VonNeumann) || (neighborhoodType == NeighborhoodType::VonNeumann && abs(i) + abs(j) <= radius))
            {
                int x_n = x + i;
                int y_n = y + j;

                if (x_n < 0 || x_n >= gridHeight || y_n < 0 || y_n >= gridWidth) // out of bounds
                {
                    if (boundaryType == BoundaryType::Cutoff)
                    {
                        continue;
                    }
                    else if (boundaryType == BoundaryType::Fixed)
                    {
                        neighbors.push_back(0);
                    }
                    else // if periodic
                    {
                        // make sure modulos are always positive
                        x_n = ((x_n % gridHeight) + gridHeight) % gridHeight;
                        y_n = ((y_n % gridWidth) + gridWidth) % gridWidth;
                        neighbors.push_back(grid[x_n][y_n]);
                    }
                }
                else // in bounds
                {
                    neighbors.push_back(grid[x_n][y_n]);
                }
            }
        }
    }
    return neighbors;
};

// Constructor
CellularAutomata::CellularAutomata(int width, int height, int num_states, int radius,
                                   BoundaryType bType,
                                   NeighborhoodType nType,
                                   std::function<int(int, int, int)> customInitFunc,
                                   std::function<int(int, int, const std::vector<int> &)> customRuleFunc,
                                   std::string file_path)
    : gridWidth(width), gridHeight(height), num_states(num_states), radius(radius), num_steps(0),
      boundaryType(bType), neighborhoodType(nType),
      initFunc(customInitFunc), ruleFunc(customRuleFunc),
      file_path(file_path)
{
    if (gridWidth <= 0 || gridHeight <= 0)
    {
        throw std::invalid_argument("Width and height must be positive.");
    }
    initializeGrid();
}

// Alternate Constructor: load params in from .txt file from specific time step instance
CellularAutomata::CellularAutomata(const std::string &file_path, int time_step, std::string new_path)
    : num_steps(time_step), file_path(new_path)
{
    std::ifstream in(file_path);
    if (!in.is_open())
    {
        throw std::runtime_error("Error opening file: " + file_path);
    }
    initFunc = defaultInitFunc;
    ruleFunc = defaultRuleFunc;

    std::string bTypeStr, nTypeStr;
    int end_steps;

    in >> gridWidth >> gridHeight >> num_states >> radius >> end_steps >> bTypeStr >> nTypeStr;
    //end steps == num steps... Where the simulation starts
    if (bTypeStr == "Periodic")
    {
        boundaryType = BoundaryType::Periodic;
    }
    else if (bTypeStr == "Fixed")
    {
        boundaryType = BoundaryType::Fixed;
    }
    else
    {
        boundaryType = BoundaryType::Cutoff;
    }

    if (nTypeStr == "VonNeumann")
    {
        neighborhoodType = NeighborhoodType::VonNeumann;
    }
    else
    {
        neighborhoodType = NeighborhoodType::Moore;
    }
    loadGrid(in, time_step);    //pass in input file, num steps to complete
}

// Destructor
CellularAutomata::~CellularAutomata() {}

// Initialize the grid
void CellularAutomata::initializeGrid()
{
    grid.resize(gridHeight, std::vector<int>(gridWidth));
    for (int i = 0; i < gridHeight; ++i)
    {
        for (int j = 0; j < gridWidth; ++j)
        {
            grid[i][j] = initFunc(i, j, num_states);
        }
    }
}

// TO DO: IS BUGGY, NEEDS TO BE FIXED
// load cell values from input text stream (from alternate constructor)
void CellularAutomata::loadGrid(std::ifstream &in_stream, int target_time)
{
    grid.resize(gridHeight, std::vector<int>(gridWidth));
    std::string header;
    bool reach_time = false;

    std::getline(in_stream, header);
    std::cout << header << std::endl;
    int step, x, y, value;

    while (in_stream >> step >> x >> y >> value)
    {
        if (step == target_time)
        {
            reach_time = true;
            grid[x][y] = value;
        }
    }
    in_stream.close();
    if (!reach_time) // if never reached desired target time
    {
        std::cout << "Input txt file does not contain cell values for time: ";
        std::cout << target_time << ", using defaultinitFunc..." << std::endl;
        initializeGrid();
    }
}

// Apply rules to the grid
void CellularAutomata::applyRules()
{
    std::vector<std::vector<int>> newGrid(gridHeight, std::vector<int>(gridWidth));
    for (int i = 0; i < gridHeight; ++i)
    {
        for (int j = 0; j < gridWidth; ++j)
        {
            std::vector<int> neighbor_vals = getNeighborState(i, j);
            newGrid[i][j] = ruleFunc(grid[i][j], num_states, neighbor_vals);
        }
    }
    grid = newGrid;
}

// take one time step
void CellularAutomata::step()
{
    if (num_steps == 0) // record original start
    {
        save_params();
        save_grid();
    }
    applyRules();
    num_steps += 1;
    save_grid();
}

// Setter for initFunc
void CellularAutomata::setInitFunction(std::function<int(int, int, int)> newInitFunc)
{
    initFunc = newInitFunc;
}

// Setter for ruleFunc
void CellularAutomata::setRuleFunction(std::function<int(int, int, const std::vector<int> &)> newRuleFunc)
{
    ruleFunc = newRuleFunc;
}

// Getter for the grid
const std::vector<std::vector<int>> &CellularAutomata::getGrid() const
{
    return grid;
}

// Display the grid
void CellularAutomata::displayGrid() const
{
    for (const auto &row : grid)
    {
        for (int cell : row)
        {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
}

// count number of cells that have a specific state
int CellularAutomata::countCellState(int state_val) const
{
    int count = 0;
    for (int i = 0; i < gridHeight; ++i)
    {
        for (int j = 0; j < gridWidth; ++j)
        {
            if (grid[i][j] == state_val)
            {
                count += 1;
            }
        }
    }
    return count;
}

// save cell values
void CellularAutomata::save_grid()
{
    std::ofstream out(file_path, std::ios::app);
    if (out.is_open()) // if file is closed
    {
        for (int i = 0; i < gridHeight; ++i) // print out indeces and graph
        {
            for (int j = 0; j < gridWidth; ++j)
            {
                out << num_steps << ", " << j << ", ";
                out << i << ", " << grid[i][j];
            }
            out << std::endl;
        }
        out.close();
    }
    else
    {
        throw std::runtime_error("Error saving to file: " + file_path);
    }
}

// save grid parameters
void CellularAutomata::save_params()
{
    std::ofstream out(file_path, std::ios::app);
    if (out.is_open())
    {
        out << gridWidth << std::endl;
        out << gridHeight << std::endl;
        out << num_states << std::endl;
        out << radius << std::endl;
        out << num_steps << std::endl;
        if (boundaryType == BoundaryType::Periodic)
        {
            out << "Periodic" << std::endl;
        }
        else if (boundaryType == BoundaryType::Fixed)
        {
            out << "Fixed" << std::endl;
        }
        else // cutoff
        {
            out << "Cutoff" << std::endl;
        }

        if (neighborhoodType == NeighborhoodType::VonNeumann)
        {
            out << "VonNeumann" << std::endl;
        }
        else // moore
        {
            out << "Moore" << std::endl;
        }
        out << "time_step, x, y, value" << std::endl;
        out.close();
    }
    else
    {
        throw std::runtime_error("Error saving to file: " + file_path);
    }
}

// original class declaration commented below

// class CellularAutomata
// {
// private:
//     std::vector<std::vector<int>> grid;
//     int gridWidth;
//     int gridHeight;
//     int num_states;
//     int radius;
//     int num_steps;
//     BoundaryType boundaryType;
//     NeighborhoodType neighborhoodType;
//     std::function<int(int, int, int)> initFunc;
//     std::function<int(int, int, const std::vector<int> &)> ruleFunc;

//     std::string file_path;

//     // Utility function to get all of the neighbor states for a given cell
//     std::vector<int> getNeighborState(int x, int y)
//     {
//         std::vector<int> neighbors;
//         for (int i = -radius; i <= radius; ++i)
//         {
//             for (int j = -radius; j <= radius; ++j)
//             {
//                 if (i == 0 && j == 0) // if center coord
//                 {
//                     continue;
//                 }
//                 // account for von neumann boundaries
//                 if ((neighborhoodType != NeighborhoodType::VonNeumann) || (neighborhoodType == NeighborhoodType::VonNeumann && abs(i) + abs(j) <= radius))
//                 {
//                     int x_n = x + i;
//                     int y_n = y + j;

//                     if (x_n < 0 || x_n >= gridHeight || y_n < 0 || y_n >= gridWidth) // out of bounds
//                     {
//                         if (boundaryType == BoundaryType::Cutoff)
//                         {
//                             continue;
//                         }
//                         else if (boundaryType == BoundaryType::Fixed)
//                         {
//                             neighbors.push_back(0);
//                         }
//                         else // if periodic
//                         {
//                             neighbors.push_back(grid[x_n % gridHeight][y_n % gridWidth]);
//                         }
//                     }
//                     else // in bounds
//                     {
//                         neighbors.push_back(grid[x_n][y_n]);
//                     }
//                 }
//             }
//         }
//         return neighbors;
//     }

// public:
//     // Constructor
//     CellularAutomata(int width, int height, int num_states = 2, int radius = 1,
//                      BoundaryType bType = BoundaryType::Cutoff,
//                      NeighborhoodType nType = NeighborhoodType::Moore,
//                      std::function<int(int, int, int)> customInitFunc = defaultInitFunc,
//                      std::function<int(int, int, const std::vector<int> &)> customRuleFunc = defaultRuleFunc,
//                      std::string file_path = "automata_output.txt")
//         : gridWidth(width), gridHeight(height), num_states(num_states), radius(radius), num_steps(0),
//           boundaryType(bType), neighborhoodType(nType),
//           initFunc(customInitFunc), ruleFunc(customRuleFunc),
//           file_path(file_path)
//     {
//         if (gridWidth <= 0 || gridHeight <= 0)
//         {
//             throw std::invalid_argument("Width and height must be positive.");
//         }
//         initializeGrid();
//     }

//     // Alternate Constructor: load params in from .txt file from specific time step instance
//     CellularAutomata(const std::string &file_path, int time_step, std::string new_path = "loaded_automata_output.txt")
//         : num_steps(time_step), file_path(new_path)
//     {
//         std::ifstream in(file_path);
//         if (!in.is_open())
//         {
//             throw std::runtime_error("Error opening file: " + file_path);
//         }
//         initFunc = defaultInitFunc;
//         ruleFunc = defaultRuleFunc;

//         std::string bTypeStr, nTypeStr;
//         int end_steps;

//         in >> gridWidth >> gridHeight >> num_states >> radius >> end_steps >> bTypeStr >> nTypeStr;

//         if (end_steps < time_step)
//         {
//             throw std::invalid_argument("Provided input txt file does not contain cell values for time: " + time_step);
//         }

//         if (bTypeStr == "Periodic")
//         {
//             boundaryType = BoundaryType::Periodic;
//         }
//         else if (bTypeStr == "Fixed")
//         {
//             boundaryType = BoundaryType::Fixed;
//         }
//         else
//         {
//             boundaryType = BoundaryType::Cutoff;
//         }

//         if (nTypeStr == "VonNeumann")
//         {
//             neighborhoodType = NeighborhoodType::VonNeumann;
//         }
//         else
//         {
//             neighborhoodType = NeighborhoodType::Moore;
//         }

//         loadGrid(in, time_step);
//     }

//     // Deconstructor
//     ~CellularAutomata() {}

//     // Initialize the grid
//     void initializeGrid()
//     {
//         grid.resize(gridHeight, std::vector<int>(gridWidth));
//         for (int i = 0; i < gridHeight; ++i)
//         {
//             for (int j = 0; j < gridWidth; ++j)
//             {
//                 grid[i][j] = initFunc(i, j, num_states);
//             }
//         }
//     }

//     // load cell values from input text stream (from alternate constructor)
//     void loadGrid(std::ifstream &in_stream, int target_time)
//     {
//         grid.resize(gridHeight, std::vector<int>(gridWidth));
//         std::string header;

//         std::getline(in_stream, header);

//         while (!in_stream.eof())
//         {
//             int step, x, y, value;
//             in_stream >> step >> x >> y >> value;
//             if (step == target_time)
//             {
//                 grid[x][y] = value;
//             }
//         }
//     }

//     // Apply rules to the grid
//     void applyRules()
//     {
//         std::vector<std::vector<int>> newGrid(gridHeight, std::vector<int>(gridWidth));
//         for (int i = 0; i < gridHeight; ++i)
//         {
//             for (int j = 0; j < gridWidth; ++j)
//             {
//                 std::vector<int> neighbor_vals = getNeighborState(i, j);
//                 newGrid[i][j] = ruleFunc(grid[i][j], num_states, neighbor_vals);
//             }
//         }
//         grid = newGrid;
//     }

//     // take one time step
//     void step()
//     {
//         if (num_steps == 0) // record original start
//         {
//             save_grid();
//         }
//         applyRules();
//         num_steps += 1;
//         save_grid();
//     }

//     // Setter for initFunc
//     void setInitFunction(std::function<int(int, int, int)> newInitFunc)
//     {
//         initFunc = newInitFunc;
//     }

//     // Setter for ruleFunc
//     void setRuleFunction(std::function<int(int, int, const std::vector<int> &)> newRuleFunc)
//     {
//         ruleFunc = newRuleFunc;
//     }

//     // Getter for the grid
//     const std::vector<std::vector<int>> &getGrid() const
//     {
//         return grid;
//     }

//     // Display the grid
//     void displayGrid() const
//     {
//         for (const auto &row : grid)
//         {
//             for (int cell : row)
//             {
//                 std::cout << cell << " ";
//             }
//             std::cout << std::endl;
//         }
//     }

//     // count number of cells that have a specific state
//     int countCellState(int state_val) const
//     {
//         int count = 0;
//         for (int i = 0; i < gridHeight; ++i)
//         {
//             for (int j = 0; j < gridWidth; ++j)
//             {
//                 if (grid[i][j] == state_val)
//                 {
//                     count += 1;
//                 }
//             }
//         }
//         return count;
//     }

//     // save grid parameters and cell values
//     void save_grid()
//     {
//         std::ofstream out(file_path, std::ios::app);
//         if (!out.is_open()) // if file is closed
//         {
//             out << gridWidth << std::endl;
//             out << gridHeight << std::endl;
//             out << num_states << std::endl;
//             out << radius << std::endl;
//             out << num_steps << std::endl;
//             if (boundaryType == BoundaryType::Periodic)
//             {
//                 out << "Periodic" << std::endl;
//             }
//             else if (boundaryType == BoundaryType::Fixed)
//             {
//                 out << "Fixed" << std::endl;
//             }
//             else // cutoff
//             {
//                 out << "Cutoff" << std::endl;
//             }

//             if (neighborhoodType == NeighborhoodType::VonNeumann)
//             {
//                 out << "VonNeumann" << std::endl;
//             }
//             else // moore
//             {
//                 out << "Moore" << std::endl;
//             }
//             out << "time_step, x, y, value" << std::endl;
//         }
//         else
//         {
//             for (int i = 0; i < gridHeight; ++i) // print out indeces and graph
//             {
//                 for (int j = 0; j < gridWidth; ++j)
//                 {
//                     out << num_steps << ", " << j << ", ";
//                     out << i << ", " << grid[i][j] << std::endl;
//                 }
//             }
//         }
//     }
// };