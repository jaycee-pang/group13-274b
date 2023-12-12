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
        std::function<int(int, int)> init_func; //user passed. otherwise, set to default
        std::function<int(int, int, const std::vector<std::vector<int>>&)> rule_func; //user passed. otherwise, set to default
        int time_step_;
        // Utility function to get the state of a neighbor cell considering boundary conditions
        int getNeighborState(int x, int y)
        {
            // Implement logic based on boundaryType and neighborhoodType
            if (neighborhood_type_ == NeighborhoodType::Moore) {
                int neighborOffsets = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
            } else if (neighborhood_type_ == NeighborhoodType::VonNeumann) {
                int neighborOffsets = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
            }
            // ...
        }
    public:
        Automata(std::string file, int num_steps, int dim_0, int dim_1,
                int num_states, std::vector<std::string> states, 
                NeighborhoodType neighbors, BoundaryType boundary_type,
                std::function<int()> init_func = &start_grid,
                std::function<int(int, int, const std::vector<std::vector<int>>&)> rule_func)  //probably will delete this constructor
            : file_(file), num_steps_(num_steps), dim_0_(dim_0), dim_1_(dim_1), 
              num_states_(num_states), states_(states), neighborhood_type_(neighbors), boundary_type_(boundary_type)
        {
            //setup from .txt file
            grid_ = initialize_grid();
            std::cout << "Time step 0 " << std::endl;
            print();
            run_simulation();   //performs number of steps that user passes in
        }
        ~Automata()//deconstructor
        {}
        void setup()
        {
            //read from .txt file
            //save into private members
        }
        void step()
        {
            //new grid, has changes from time step
            std::vector<std::vector<int>> new_grid(dim_0_, std::vector<int>(dim_1_));

            if(neighborhood_type_ == NeighborhoodType::Moore)
            {
                //new_grid = apply_rules(grid_, &moore);
            }
            else{
                new_grid = apply_rules(grid_, &von_neumann_rules);
            }
            update_grid(grid_, new_grid);
        }
        void run_simulation()   //TODO: remove and replace in main
        {
            for(int t = 1; t < num_steps_; t++) //t represents time
            {
                std::cout << "Time step: " << t << std::endl;
                step();
                print();
            }
        }
        std::vector<std::vector<int>> initialize_grid() {
    std::vector<std::vector<int>> grid(dim_0_, std::vector<int>(dim_1_));
        for (int i = 0; i < dim_0_; ++i) {
            for (int j = 0; j < dim_1_; ++j) {
                grid[i][j] = start_grid();
            }
        }
        return grid;
        }
        std::vector<std::vector<int>> apply_rules(const std::vector<std::vector<int>>& grid,
                                        int (rule_func) (int, int, const std::vector<std::vector<int>>&, int)) {
            std::vector<std::vector<int>> new_grid(dim_0_, std::vector<int>(dim_1_));
            for (int i = 0; i < dim_0_; ++i) {
                for (int j = 0; j < dim_1_; ++j) {
                    new_grid[i][j] = rule_func(i, j, grid, 1);
                }
            }
            return new_grid;
        }
    
        void update_grid(std::vector<std::vector<int>>& grid,
        const std::vector<std::vector<int>>& new_grid) {
            grid = new_grid;
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
        // Save the grid
        void saveGrid(std::string file_path)
        {
            std::ofstream out(file_path, std::ios::app);
            if (!out.is_open())
            {
                out << "time_step, x, y, value" << std::endl;
            }
            else
            {
                for (int i = 0; i < dim_1_; ++i)
                {
                    for (int j = 0; j < dim_0_; ++j)
                    {
                        out << time_step_ << ", " << j << ", " << i << ", " << grid_[i][j] << std::endl;
                    }
                }
            }
        }
};

int main(void)
{
    std::string file = "user_input.txt";

    std::vector<std::string> states;
    states.push_back("healthy");
    states.push_back("infected");
    states.push_back("dead");

    Automata disease_simulation(file, 10, 10, 10, 3, states, "VonNeumann", "Fixed");
    return 0;
}