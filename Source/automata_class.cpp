// MSSE Berkeley
// CHEM 274B: Group 13, Final Project


#include <iostream> 
#include <vector>   //allows for 2d grid
#include <random>   //allows for random number generator in init function
#include <string>   
#include <fstream>  //allow for input from .txt file

#include "myclass.h"    //allow for rule functions

class Automata
{
    private:
        std::string file_;  //.txt input file
        std::vector<std::vector<int>> grid_;
        int num_steps_; //num of steps the simulation will take
        int size_;  //length of one side of the grid
        double rate_;   //rate of spread
        double density_;    //chance that a cell will be active
        int num_states_;    //number of states a cell can be (not including "empty")
        std::vector<std::string> states_;   //states in the following order: unaffected, affected, destroyed 
        std::string neighbors_; //Von Neumann or Moore
        std::string boundary_;  //periodic or fixed
    public:
        Automata(std::string file, int num_steps, int size,
                int num_states, std::vector<std::string> states, 
                std::string neighbors, std::string boundary_type)  //probably will delete this constructor
            : file_(file), num_steps_(num_steps), size_(size), 
              num_states_(num_states), states_(states), neighbors_(neighbors), boundary_(boundary_type)
        {
            //setup from .txt file
            grid_ = initialize_grid(size_);
            std::cout << "Time step 0 " << std::endl;
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
            std::vector<std::vector<int>> new_grid;  //new grid, has changes from time step
            const std::vector<std::vector<int>> setting_grid = grid_;
            //TODO: determine what occurs at each time step to see if disease spreads
            new_grid = apply_rules(setting_grid, &von_neumann_rules);
            //new_grid = apply_rules(grid_, &von_neumann_rules);
            update_grid(grid_, new_grid);
        }
        void run_simulation()
        {
            for(int t = 1; t < num_steps_; t++) //t represents time
            {
                std::cout << "Time step: " << t << std::endl;
                step();
            }
        }
        
        std::vector<std::vector<int>> initialize_grid(int size)
        {
        std::vector<std::vector<int>> grid(size, std::vector<int>(size));

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                grid[i][j] = init_function();
            }
        }
        return grid;
        }
        std::vector<std::vector<int>> apply_rules(const std::vector<std::vector<int>>& grid,
                                        int (*rule_func) (int, int, const std::vector<std::vector<int>>&)) {
            int size = grid.size();
            std::vector<std::vector<int>> new_grid(size, std::vector<int>(size));
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    new_grid[i][j] = rule_func(i, j, grid);
                }
            }
            return new_grid;
        }
    
        void update_grid(std::vector<std::vector<int>>& grid,
        const std::vector<std::vector<int>>& new_grid) {
            grid = new_grid;
        }

        int init_function()
        //function that will set initial state of each cell on graph
        {
            std::random_device rd;
            std::mt19937 gen(rd()); //generate random value
            std::uniform_real_distribution<> dis(0.0, 1.0);

            if(dis(gen) < rate_)    //0.3
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
};

int main(void)
{
    std::string file = "user_input.txt";

    std::vector<std::string> states;
    states.push_back("healthy");
    states.push_back("infected");
    states.push_back("dead");

    Automata disease_simulation(file, 10, 10, 3, states, "Von Neumann", "Fixed");
    return 0;
}

/*
    Python Implementation of the step function for forest fire automata:

    def step():
    global time, config, nextConfig

    time += 1

    for x in range(width):
        for y in range(height):
            state = config[y, x]
            if state == fire:
                # cf. Sayama, "the burning tree is completely charred after one time step"
                state = char
            elif state == tree:
                for dx in range(-1, 2):
                    for dy in range(-1, 2):
                        if config[(y+dy)%height, (x+dx)%width] == fire:
                            state = fire
            nextConfig[y, x] = state

    config, nextConfig = nextConfig, config
*/

//setup function will call jupyternotebook thing to accept text-file settings