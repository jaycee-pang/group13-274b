#include <iostream> 
#include <vector> 
#include <tuple> 
std::vector<int> getNeighborState(int x, int y){
    // Implement logic based on boundaryType and neighborhoodType
    if (neighborhood_type_ == NeighborhoodType::Moore) {
        std::vector<std::tuple<int ,int>>  neighborOffsets = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
        std::vector<int> neighborhood_states;  
        // loop through offsets and get neighborhood states according to boundary condition
        for (const auto& offset: neighborOffsets) { 
            int offset_x, offset_y; 
            int neighbor_x = x+offset_x; 
            int neighbor_y = y+offset_y; 
            int state; 
            if (boundary_type_ == BoundaryType::Fixed) { 
                if (neighbor_x >= 0 && neighbor_x < grid.size() && neighbor_y >= 0 && neighbor_y < grid[0].size()) {
                    state = grid[neighbor_x][neighbor_y];
                    neighborhood_states.push_back(state);
                }
            }
            else if (boundary_type_ == BoundaryType::Periodic) {
                // wrapping around 
                neighbor_x = (neighbor_x + grid.size()) % grid.size();
                neighbor_y = (neighbor_y + grid[0].size()) % grid[0].size();
                state = graid[neighbor_x][neighbor_y];
                neighborhood_states.push_back(state); 
            }
            else if (boundary_type_ == BoundaryType::Cutoff) {
                if (neighbor_x >= 0 && neighbor_x < grid.size() && neighbor_y >= 0 && neighbor_y < grid[0].size()) {
                    state = grid[neighbor_x][neighbor_y];
                    neighborhood_states.push_back(state);
                }
            }

            
        }
        return neighborhoodStates; 
    } 

   
}
