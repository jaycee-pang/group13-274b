#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <random>


std::vector<std::vector<int>> initialize_grid(int size, std::function<int(int, int)> init_func);

std::vector<std::vector<int>> apply_rules(const std::vector<std::vector<int>>& grid,
    std::function<int(int, int, const std::vector<std::vector<int>>&)> rule_func);


void update_grid(std::vector<std::vector<int>>& grid, const std::vector<std::vector<int>>& new_grid);