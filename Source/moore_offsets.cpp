#include <iostream> 
#include <vector> 
#include <tuple> 
#include <algorithm> 
#include <map> 

enum class RuleType {
    Majority, 
    Straight, 
    NeighborConditional
};
std::vector<int> getNeighborState(int x, int y){
    // Implement logic based on boundaryType and neighborhoodType
    if (neighborhood_type_ == NeighborhoodType::Moore) {
        std::vector<std::tuple<int ,int>>  neighborOffsets = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
        std::vector<int> neighborhood_states;  
        // loop through offsets and get neighborhood states according to boundary condition
        for (const auto& offset: neighborOffsets) { 
            int offset_x = std::get<0>(offset); 
            int offset_y = std::get<1>(offset);

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
        return neighborhood_states; 
    } 

   
}

int MajorityRules(int i, int j) {
    std::vector neighborhood_states = getNeighborState(i, j); 
    std::map<int, int> state_counts; 
    for (int state : states) {
        int count = std::count(neighborhood_states.begin(), neighborhood_states.end(), state); 

        state_counts[state] = count; 
    }
    int max_count = 0; 
    int max_state = 0; 
    for (const auto& it: state_counts) {
        if (it.second > max_count) {
            max_count = it.second;
            max_state = it.first; 
        }
    }
    return max_state; 
    // actually max state/num neighbors ; 
}

int StraightRules(int i, int j) {
    return states[next state];

}
int ConditionalRules(int i, int j) {
    std::vector<int> neighborhood_states = getNeighborState(i, j); 
    
}


