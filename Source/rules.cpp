#include <vector>
#include <map>
#include <algorithm>

#include <source_automata_compiled.h>

int MajorityRule(int current_state, int num_states, std::vector<int> neighborhood_states)
{
    std::map<int, int> state_counts;
    for (int state : neighborhood_states)
    {
        int count = std::count(neighborhood_states.begin(), neighborhood_states.end(), state);
        state_counts[state] = count;
    }
    int max_count = 0;
    int max_state = 0;
    for (const auto &it : state_counts)
    {
        if (it.second > max_count)
        {
            max_count = it.second;
            max_state = it.first;
        }
    }
    if (max_count > neighborhood_states.size() / 2)
    {
        return max_state;
    }
    else
    {
        return current_state;
    }
}

int StraightRule(int current_state, int num_states, std::vector<int> neighborhood_states)
{
    if (current_state == num_states)
    {
        return num_states;
    }
    else
    {
        return current_state + 1;
    }
}

int NeighborRule(int current_state, int num_states, std::vector<int> neighborhood_states)
{
    if (current_state == num_states)
    {
        return num_states;
    }
    else
    {
        for (const auto &it : neighborhood_states)
        {
            if (it == current_state + 1)
            {
                return it;
            }
            else
            {
                return current_state;
            }
        }
    }
}