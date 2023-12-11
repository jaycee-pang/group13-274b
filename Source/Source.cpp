#include <iostream>
#include <vector>
#include <functional>
#include <random>
// initialize grid from a init func
std::vector<std::vector<int>> initialize_grid(int size, std::function<int(int, int)> init_func) {
    std::vector<std::vector<int>> grid(size, std::vector<int>(size));

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            grid[i][j] = init_func(i, j);
        }
    }
    return grid;
}
<<<<<<< HEAD
// apply a rule function
std::vector<std::vector<int>> apply_rules(const std::vector<std::vector<int>>& grid, std::function<int(int, int, const std::vector<std::vector<int>>&)> rule_func) {
=======

std::vector<std::vector<int>> apply_rules(const std::vector<std::vector<int>>& grid,
                                         std::function<int(int, int, const std::vector<std::vector<int>>&)> rule_func) {
>>>>>>> 128092a26aef49983787d1156c99f03301b17c47
    int size = grid.size();
    std::vector<std::vector<int>> new_grid(size, std::vector<int>(size));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            new_grid[i][j] = rule_func(i, j, grid);
        }
    }
    return new_grid;
}
// update the grid
void update_grid(std::vector<std::vector<int>>& grid, const std::vector<std::vector<int>>& new_grid) {
    grid = new_grid;
}

<<<<<<< HEAD

// example init func for forest fire, input to initialize_grid
=======
// example init func for forest fire
>>>>>>> 128092a26aef49983787d1156c99f03301b17c47

// Function to initialize the grid for forest fire simulation

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dis(0.0, 1.0);
int forest_fire_init(int i, int j) {
    const double initial_burning_ratio = 0.02;  // Probability of a cell initially being burning
    const double tree_probability = 0.6;        // Probability of a cell being a tree

    if (dis(gen) < initial_burning_ratio) {
        return 2;  // Burning
    } else if (dis(gen) < tree_probability) {
        return 1;  // Tree
    } else {
        return 0;  // Empty
    }
}

//add init function and rule function here