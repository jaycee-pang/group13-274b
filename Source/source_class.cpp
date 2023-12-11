#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <fstream>

enum class BoundaryType
{
    Periodic,
    Fixed,
    Cutoff
};

enum class NeighborhoodType
{
    Moore,
    VonNeumann
};

class CellularAutomata
{
private:
    std::vector<std::vector<int>> grid;
    int gridWidth;
    int gridHeight;
    BoundaryType boundaryType;
    NeighborhoodType neighborhoodType;
    std::function<int(int, int)> initFunc;
    std::function<int(int, int, const std::vector<std::vector<int>> &)> ruleFunc;
    int time_step; // add parameter to keep time (used for running automata)

    // Utility function to get the state of a neighbor cell considering boundary conditions
    int getNeighborState(int x, int y)
    {
        // Implement logic based on boundaryType and neighborhoodType
        // ...
    }

public:
    // Constructor
    CellularAutomata(int width, int height, int time_step,
                     BoundaryType bType, NeighborhoodType nType,
                     std::function<int(int, int)> initFunction,
                     std::function<int(int, int, const std::vector<std::vector<int>> &)> ruleFunction)
        : gridWidth(width), gridHeight(height), boundaryType(bType), neighborhoodType(nType),
          initFunc(initFunction), ruleFunc(ruleFunction), time_step(time_step)
    {
        initializeGrid();
    }

    // Initialize the grid
    void initializeGrid()
    {
        grid.resize(gridHeight, std::vector<int>(gridWidth));
        for (int i = 0; i < gridHeight; ++i)
        {
            for (int j = 0; j < gridWidth; ++j)
            {
                grid[i][j] = initFunc(i, j);
            }
        }
    }

    // Apply rules to the grid
    void applyRules()
    {
        std::vector<std::vector<int>> newGrid(gridHeight, std::vector<int>(gridWidth));
        for (int i = 0; i < gridHeight; ++i)
        {
            for (int j = 0; j < gridWidth; ++j)
            {
                newGrid[i][j] = ruleFunc(i, j, grid);
            }
        }
        grid = newGrid;
    }

    // Getter for the grid
    const std::vector<std::vector<int>> &getGrid() const
    {
        return grid;
    }

    // Display the grid
    void displayGrid() const
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

    // Save the grid
    void saveGrid(std::string file_path)
    {
        std::ofstream out(file_path, std::ios::app);
        if (!out.is_open())
        {
            out << "time_step, x, y, value" << std::endl;
        }
        else
        {
            for (int i = 0; i < gridHeight; ++i)
            {
                for (int j = 0; j < gridWidth; ++j)
                {
                    out << time_step << ", " << j << ", " << i << ", " << grid[i][j] << std::endl;
                }
            }
        }
    }

    // Additional methods and functionalities...

    // Run simulation on initialized Grid and save per-step grid to file
    void runSimlulation(int n_steps, std::string file_path)
    {
        for (int i = 0; i < n_steps; ++i)
        {
            saveGrid(file_path);
            // perhaps other things here? however we're specifically calling our automata
            applyRules();
            time_step += 1;
        }
    }
};
