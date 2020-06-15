/*
    main.cpp
    DiscreteEventSimulation

    Client used to test "Beers, Bar, Drinkrs" Simulation. Makes use of
    SimulationFramework and SoftwareGurusBar to perform the discrete
    event simulation

    Created by Tyler Tivadar on 5/30/19., adapted from code in class 
*/

#include <iostream>
#include <vector>
#include "event.h"
#include "SoftwareGurusBar.hpp"

using std::vector;

int main( )
{
    // load priority queue with initial Arrive Events then run simulation
    unsigned int t = 0;
    int numPeople = 0;
    vector<int> groupWeights = {0, 10, 30, 20, 25, 15};
    int seatInput = -1;
    
    do
    {
        std::cout<<"Enter number of seats between 20 and 100: ";
        std::cin >> seatInput;
    }
    while(seatInput < 20 || seatInput > 100);
    theBar.freeChairs = seatInput;
    
    srand(time(NULL));
    // load 4 hours (240 minutes) of Arrive Events
    while (t < 240)
    {
        // new group every 2-5 minutes
        // group size ranges from 1 to 5
        t += randBetween(2,5);
        numPeople = theSimulation.weightedProbability(groupWeights);
        theSimulation.scheduleEvent(new ArriveEvent(t, numPeople));
    }
        // then run simulation and print profits
    theSimulation.run( );
    std::cout << "Total profits: $" << theBar.profit << std::endl;

    return 0;
}
