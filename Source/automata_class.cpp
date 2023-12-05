// MSSE Berkeley
// CHEM 274B: Group 13, Final Project

// This class works congruently with source.cpp

#include <iostream> 
#include <vector>   //allows for 2d grid
#include <random>   //allows for random number generator in init function
#include <string>   
#include <fstream>  //allow for input from .txt file

#include "Source.h" //allow for init functions
#include "myclass.h"    //allow for rule functions

class Automata
{
    private:
        std::string file_;  //.txt input file
        std::vector<std::vector<int>> grid_;
        int num_steps_; //num of steps the simulation will take
        int size_;  //length of one side of the grid
        static double rate_;   //rate of spread
        static double density_;    //chance that a cell will be active
        int num_states_;    //number of states a cell can be (not including "empty")
        std::vector<std::string> states_;   //states in the following order: unaffected, affected, destroyed 
        std::string neighbors_; //Von Neumann or Moore
        std::string boundary_;  //periodic or fixed
        //rules are the updates - at each time step, look at neighbors
    public:
        Automata(std::string file, int num_steps, int size,
                int num_states, std::vector<std::string> states, 
                std::string neighbors, std::string boundary_type)  //probably will delete this constructor
            : file_(file), num_steps_(num_steps), size_(size), 
              num_states_(num_states), states_(states), neighbors_(neighbors), boundary_(boundary_type)
        {
            //setup from .txt file
            //for num time steps, do time step
            grid_ = initialize_grid(size_, &init_function);
            std::cout << "Time step 0 " << std::endl;

            //create function called run_model that performs steps per num steps
            // moore_neighborhood : pass in grid, returns the state of the cell depending on the neighborhood
                // create seperate function in myautoclass.h
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
            //TODO: determine what occurs at each time step to see if disease spreads
            apply_rules(grid_, &von_neumann_rules);
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
        /*
        //rule function
        int von_neumann_rules() //what's configuring around the index. The 4 directly-adjacent cells
        {
            int state;  //saves the int value of the state that the cell is in
            for(int x = 0; x < size_; x++)
            {
                for(int y = 0; y < size_; y++)
                {
                    state = grid_[x][y];
                    if(state == 2) //if the cell affected in the previous timestep
                    {
                        state = 3;  //now that cell will be dead TODO: implement recovery chance?
                    }
                    else if(state == 1) //if cell is unaffected
                    {
                        for(int dx = -1; dx < 1; dx++)
                        {
                            for(int dy = -1; dy < 1; dy++)
                            {
                                if(grid_[(y+dy)%size_][(x+dx)%size_] == 2)  //if anything in a moore neighborhood
                                {                                           // is on infectious...
                                    state = 2;
                                }
                            }
                        }
                    }
                    //grid_[x][y] == state;
                }
            }
            //periodic() or fixed()
            return state;
        }
        */
        static int init_function(int j, int k)
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

    Automata disease_simulation(file, 10, 10, 3, states, "Moore", "Fixed");
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