#include "neighborhoods.h"
// std::pairs/mapping for states ex. 
int moore(const std::vector<std::vector<int>>& grid, int row, int col) {
    int sum = 0; 
    for (int i = row - 1; i <= row + 1; ++i) {
        for (int j = col - 1; j <= col + 1; ++j) {
            // skip the central cell
            if (i == row && j == col) {
                continue;
            }
            if (i >= 0 && i < grid.size() && j >= 0 && j < grid[0].size()) {
                sum += grid[i][j];
            }
        }
    }

    return sum; 
}