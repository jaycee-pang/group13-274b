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

// Default initialization function
extern std::function<int(int, int, int)> defaultInitFunc;

// Default rule function
extern std::function<int(int, int, const std::vector<int> &)> defaultRuleFunc;

class CellularAutomata
{
private:
    std::vector<std::vector<int>> grid;
    int gridWidth;
    int gridHeight;
    int num_states;
    int radius;
    int num_steps;
    BoundaryType boundaryType;
    NeighborhoodType neighborhoodType;
    std::function<int(int, int, int)> initFunc;
    std::function<int(int, int, const std::vector<int> &)> ruleFunc;

    std::string file_path;

    std::vector<int> getNeighborState(int x, int y);

public:
    CellularAutomata(int width, int height, int num_states = 2, int radius = 1,
                     BoundaryType bType = BoundaryType::Cutoff,
                     NeighborhoodType nType = NeighborhoodType::Moore,
                     std::function<int(int, int, int)> customInitFunc = defaultInitFunc,
                     std::function<int(int, int, const std::vector<int> &)> customRuleFunc = defaultRuleFunc,
                     std::string file_path = "automata_output.txt");

    CellularAutomata(const std::string &file_path, int time_step, std::string new_path = "loaded_automata_output.txt");

    ~CellularAutomata();

    void initializeGrid();

    void loadGrid(std::ifstream &in_stream, int target_time);

    void applyRules();

    void step();

    void setInitFunction(std::function<int(int, int, int)> newInitFunc);

    void setRuleFunction(std::function<int(int, int, const std::vector<int> &)> newRuleFunc);

    const std::vector<std::vector<int>> &getGrid() const;

    void displayGrid() const;

    int countCellState(int state_val) const;

    void save_grid();

    void save_params();
};

int MajorityRule(int current_state, int num_states, std::vector<int> neighborhood_states);
int StraightRule(int current_state, int num_states, std::vector<int> neighborhood_states);
int NeighborRule(int current_state, int num_states, std::vector<int> neighborhood_states);
