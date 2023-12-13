#include <vector> 

int custom_rule1(int current_state, int num_states, std::vector<int> neighborhood_states) {
    
    if (current_state > num_states-2) {
        return num_states; 
    }
    else {
        return current_state+2; 
    }
}