// MSSE Berkeley
// CHEM 274B: Group 13, Final Project

// This class allows a user to generate a cellular automaton with the
//          following parameters:
//          Inputs:
//              file_ : string
//              num_steps :  
//              dim_0_ : 
//              y dimension : 
//              num_states_ :
//              states_ :  
//              neighbors_ :
//              boundaries_ : 
//
//          Outputs : step-wise changes in automaton simulation          

#include <iostream> 
#include <vector>   //allows for 2d grid
#include <random>   //allows for random number generator in init function
#include <string>   
#include <fstream>  //allow for input from .txt file]
#include <functional> //allow for std::function
#include <tuple> //allow for offsets

#include "myclass.h"    //allow for von neumann rule functions
#include "neighborhoods.h"    //allow for moore rule function

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

enum class RuleType {
    Straight,
    Majority,
    Neighbor
};

class Automata
{
    private:
        std::string file_;  //.txt input file
        std::vector<std::vector<int>> grid_;
        int num_steps_; //num of steps the simulation will take
        int dim_0_;  //width of grid
        int dim_1_; //height of grid
        double rate_ = .2;   //rate of spread TODO: must be passed into user_input.txt
        double density_ = .5;    //chance that a cell will be active TODO: must be passed into user_input.txt
        int num_states_;    //number of states a cell can be (not including "empty")
        std::vector<std::string> states_;   //states in the following order: unaffected, affected, destroyed
        NeighborhoodType neighborhood_type_; //Von Neumann or Moore
        BoundaryType boundary_type_;  //periodic, fixed, or cutoff
        std::function<int(int, int)> init_func_; //user passed. otherwise, set to default
        std::function<int(int, int, const std::vector<std::vector<int>>&)> rule_func; //user passed. otherwise, set to default
        int time_step_;
        std::string output_file= "automata_output.txt";
        
        std::vector<int> getNeighborState(int x, int y){
        // Implement logic based on boundaryType and neighborhoodType
        if (neighborhood_type_ == NeighborhoodType::Moore) {
            std::vector<std::tuple<int ,int>>  neighborOffsets = {{-1, -1}, {-1, 0}, {-1, 1}, 
                                                                    {0, -1}, {0, 1}, {1, -1},
                                                                    {1, 0}, {1, 1}};
            std::vector<int> neighborhood_states;  
            // loop through offsets and get neighborhood states according to boundary condition
            for (const auto& offset: neighborOffsets) { 
                int offset_x = std::get<0>(offset); 
                int offset_y = std::get<1>(offset);

                int neighbor_x = x+offset_x; 
                int neighbor_y = y+offset_y; 
                int state; 
                if (boundary_type_ == BoundaryType::Fixed) { 
                    if (neighbor_x >= 0 && neighbor_x < grid_.size() && neighbor_y >= 0
                        && neighbor_y < grid_[0].size()) {
                        state = grid_[neighbor_x][neighbor_y];
                        neighborhood_states.push_back(state);
                    }
                }
                else if (boundary_type_ == BoundaryType::Periodic) {
                    // wrapping around 
                    neighbor_x = (neighbor_x + grid_.size()) % grid_.size();
                    neighbor_y = (neighbor_y + grid_[0].size()) % grid_[0].size();
                    state = grid_[neighbor_x][neighbor_y];
                    neighborhood_states.push_back(state); 
                }
                else if (boundary_type_ == BoundaryType::Cutoff) {
                    if (neighbor_x >= 0 && neighbor_x < grid_.size() && neighbor_y >= 0
                        && neighbor_y < grid_[0].size()) {
                        state = grid_[neighbor_x][neighbor_y];
                        neighborhood_states.push_back(state);
                    }
                }
            }
            return neighborhood_states; 
        }
        }
    public:
        Automata(std::string file, int num_steps, int dim_0, int dim_1,
                int num_states, std::vector<std::string> states, 
                NeighborhoodType neighbors, BoundaryType boundary_type)  //probably will delete this constructor
            : file_(file), num_steps_(num_steps), dim_0_(dim_0), dim_1_(dim_1), 
              num_states_(num_states), states_(states), neighborhood_type_(neighbors), boundary_type_(boundary_type)
        {
            //setup from .txt file
            //SET init function as default
            initialize_grid();
            //set default rule function
            std::cout << "Time step 0 " << std::endl;
            print();
            //run_simulation();   //performs number of steps that user passes in
        }
        ~Automata()//deconstructor
        {}
        void setup()
        {
            //read from .txt file
            //save into private members
        }
        /*void step()
        {
            //new grid, has changes from time step
            std::vector<std::vector<int>> new_grid(dim_0_, std::vector<int>(dim_1_));

            if(neighborhood_type_ == NeighborhoodType::Moore)
            {
                //new_grid = apply_rules(grid_, &moore);
            }
            else{
                apply_rules();
            }
        }
        */
        void run_simulation()   //TODO: remove and replace in main
        {
            for(int t = 1; t < num_steps_; t++) //t represents time
            {
                std::cout << "Time step: " << t << std::endl;
                apply_rules();
                save_grid(output_file);
            }
        }

        void initialize_grid() {
            std::vector<std::vector<int>> grid(dim_0_, std::vector<int>(dim_1_));
            grid_ = grid;
            for (int i = 0; i < dim_0_; ++i) {
                for (int j = 0; j < dim_1_; ++j) {
                    grid_[i][j] = start_grid();
                }
            }
        }
        void apply_rules() {
            std::vector<std::vector<int>> new_grid(dim_0_, std::vector<int>(dim_1_));
            std::vector<int> n_states;
            for (int i = 0; i < dim_0_; ++i) {
                for (int j = 0; j < dim_1_; ++j) {
                    n_states = getNeighborState(i, j);
                //TODO: correct inputs to rule function 
                    //new_grid[i][j] = rule_func(i, j, );
                    //pass in grid[i][j], n_states, neighbors
                }
            }
            grid_ = new_grid;

    //rules=straight: all cells on grid(if 0, go to 1; if 1, go to 2. Go up to num states)
            //neighbor: if 0, if any neighbor is 1, then turn to next 1
            //majority: if most of neighbor are a certain type, then change
            //custom: user inputs rule function. All the user needs to do is input custom
            //      rule function that just returns an int
        }
        int default_rules(int i, int j)
        {
            //return state of the cell depending on the other 
        }
        int start_grid()
        //function that will set initial state of each cell on graph
            // must be dependent on the number of user-inputted states
        {
            std::random_device rd;
            std::mt19937 gen(rd()); //generate random value
            std::uniform_real_distribution<> dis(0.0, 1.0);
            if(dis(gen) < rate_)    //0.2
            {
                return 2;   //state 2, affected
            }
            else if (dis(gen) < density_)   //0.5
            {
                return 1;   //state 1, unaffected
            }
            else {
                return 0;   //empty cell
            }
        }
        void print()
        {
             for (int i = 0; i < dim_0_; ++i) {
                for (int j = 0; j < dim_1_; ++j) {
                    if(grid_[i][j] == 3)   {
                        std::cout << " ";
                        continue; //empty if deceased
                    }
                    std::cout << grid_[i][j] << " ";
                }
                std::cout << std::endl;
            }
        }
        void save_grid(std::string file_path)   //output filepath
        {
            std::ofstream out(file_path, std::ios::app);
            if (!out.is_open()) //if file is closed
            {
                out << "time_step, x, y, value" << std::endl;
            }
            else
            {
                for (int i = 0; i < dim_1_; ++i)    //print out indeces and graph
                {
                    for (int j = 0; j < dim_0_; ++j)
                    {
                        out << time_step_ << ", " << j << ", ";
                        out << i << ", " << grid_[i][j] << std::endl;
                    }
                }
            }
        }
        int n_steps()
        {
            return num_steps_;
        }
        void set_output_file(std::string n_file)
        {
            output_file = n_file;
        }
};

int main(void)
{
    std::string file = "user_input.txt";
    std::vector<std::string> states;
    states.push_back("healthy");
    states.push_back("infected");
    states.push_back("dead");

    Automata disease_simulation(file, 10, 10, 10, 3, states, 
                                NeighborhoodType::VonNeumann, BoundaryType::Fixed);

    //rule function calls neighborhood states, outputs states of neighbors into a vector
        //takinging into account neighbor states
    return 0;
}