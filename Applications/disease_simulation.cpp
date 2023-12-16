// Chem 274B: Software Engineering Fundamentals for
//            Molecular Sciences  
// Creator: Laura Jones
// Date Created: 12/13/2023
// Last revisited: 12/13/2023
//
//  This file generates an object demonstrating the functionality
//          of our automata class library. It will create a simulation
//          of the flu virus spreading under generalized conditions
//
//

#include <iostream>
#include <string>
#include <vector>
#include <random>   //allow for random number generation

#include "source_automata_compiled.h"   //API with class declarations

int DiseaseCustomRule(int, int, std::vector<int>);  //custom rule declaration
int DiseaseCustomInit(int, int, int);   //custom init declaration

int main(void)
{
    std::string output = "disease_simulation.txt";
    int num_steps = 7; //number of steps

    //For this demonstration, a cellular automata will be generated to 
    //  simulate the spread of the flu in a population

    CellularAutomata disease_simulation(30, 30, 5, 2,
                                         BoundaryType::Fixed, NeighborhoodType::VonNeumann,
                                        DiseaseCustomInit, DiseaseCustomRule, output);

    std::cout << std::endl << "States: Empty(0), Healthy Unvaccinated(1)" << std::endl;
    std::cout << "Healthy Vaccinated(2), Infected(3), Dead(4)" << std::endl;

    std::cout << std::endl << "Disease simulation for population of 2500 people" << std::endl;

    std::cout << "Initial grid: " << std::endl;
    disease_simulation.displayGrid();

    for(int i = 1; i < num_steps; i++)
    {
        std::cout << "step " << i << std::endl;
        disease_simulation.step();
        //disease_simulation.displayGrid();
    }

    return 0;
}

int DiseaseCustomInit(int x, int y, int num_states)
{
    int empty = 0;
    int healthy_unvaccinated = 1;
    int healthy_vaccinated = 2;
    int infected = 3;
    int dead = 4;

    double initial_infection = 0.4; //chance cell is infected
    double density = .5;    //chance cell is a person
    double vaccination_rate = 1; //0.49;    //for adults 18+

    std::random_device rd;
    std::mt19937 gen(rd()); // generate random value
    std::uniform_real_distribution<> dis(0.0, 1.0);

    if (dis(gen) < density && dis(gen) > initial_infection) //if cell is not empty and not infected
    {
        if(dis(gen) < vaccination_rate)
        {
            return healthy_vaccinated;
        }
        else {
            return healthy_unvaccinated;
        }
    }
    else if(dis(gen) < density && dis(gen) < initial_infection) {
        return infected;
    }
    else{
        return empty;
    }
} 

int DiseaseCustomRule(int current_state, int num_states, std::vector<int> neighbors)
{
    int empty = 0;
    int healthy_unvaccinated = 1;
    int healthy_vaccinated = 2;
    int infected = 3;
    int dead = 4;

    float mortality_rate = .10; //12.6/100000;   //citation in readme
    float rate_of_infection_vax = .10; //6/7292;   //citation in readme
    float rate_of_infection_unvax = .20; //28/15678;   //citation in readme

    std::random_device rd;
    std::mt19937 gen(rd()); // generate random value
    std::uniform_real_distribution<> dis(0.0, 1.0);
    
    //determine if any sick people in radius
    bool potential = false;
    for (const auto &it : neighbors) {
        if (it == infected){
            potential = true;
        }
    }

    if(current_state == dead || current_state == empty) {
        return current_state;
    }
    else if(current_state == infected) {
        if(dis(gen) < mortality_rate) {
            std::cout << "someone has died ): " << std::endl;
            return dead;   //cell is now dead
        }
        else {
            return healthy_vaccinated;  //cell is now recovered and vaccinated
        }
    }
    else if(current_state == healthy_unvaccinated && potential)  //if cell is healthy unvax
    {
        if(dis(gen) < rate_of_infection_unvax)
        {
            std::cout << "an unvaccinated person got sick" << std::endl;
            return infected;   //cell is infected
        }
        else {
            return healthy_unvaccinated; //cell doesn't get sick, stays the same
        }
    }
    else if(current_state == healthy_vaccinated && potential){
        if(dis(gen) < rate_of_infection_vax)
        {
            std::cout << "a vaccinated person got sick" << std::endl;
            return infected;    //cell is infected
        }
        else {
            return healthy_vaccinated;  //cell doesn't get sick, stays the same
        }
    }
    else {  //if no chance for infection or death, cell stays the same
        return current_state;
    }
} 