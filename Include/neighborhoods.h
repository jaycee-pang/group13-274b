#include <vector>
// define boundary types 
#define STATIC 1; 
#define PERIODIC 2; 
int moore(const std::vector<std::vector<int>>& grid, int row, int col, int boundary_type);