#include "neighborhoods.h"
// std::pairs/mapping for states ex. 
int moore(const std::vector<std::vector<int>>& grid, int row, int col, int boundary_type) {
    int sum; 
    if (boundary_type == 1) {
        sum = 0; 
        for (int i = row - 1; i <= row + 1; i++) {
            for (int j = col - 1; j <= col + 1; j++) {
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
    if (boundary_type ==2) {
        int m = grid.size();    // rows 
        int n = grid[0].size();  // cols 
        for (int i = row - 1; i <= row + 1; i++) {
            for (int j = col - 1; j <= col + 1; j++) {
                // skip the central cell
                if (i == row && j == col) {
                    continue;
                }
                int wrappedRow = (i + m) % m;   // wrap indices when they go out of the boundary
                int wrappedCol = (j + n) % n;
                sum += grid[wrappedRow][wrappedCol];

            }
        }
        return sum;
    }
}