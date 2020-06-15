/*
    event.h
    DiscreteEventSimulation

    event.h file contains all files necessary to implement a framework for discrete event
    simulation. This includes the Simulation framework class as well as a general event class
    that can be more specified to suit the needs of the specific simulation.
 
    Created by Tyler Tivadar on 5/26/19.
    Copyright © 2019 Tyler Tivadar. All rights reserved.
*/

#ifndef event_h
#define event_h

#include "PriorityQueue.h"
#include <vector>
#include <queue>

using std::vector;
using std::priority_queue;


// class Event : general event that contains an abstract processing function.
//               can be extended based on the uses of the simulation
 
class Event
{
public:
    // constructor requires time of event
    Event (unsigned int t) : time(t) { }
    // time is a public data field
    unsigned int time;
    // execute event by invoking this method
    virtual void processEvent( ) { }
};

// class eventComparison: used to compare events. The one with the lower
//                        time stamp will return true if larger
class eventComparison
{
public:
    bool operator () (Event * left, Event * right)
    {
        return left->time > right->time;
    }
};

// class SimuationFramework: handles control of the simulation. Also has
//                           ability to generate weighted probabilities
class SimulationFramework
{
public:
    SimulationFramework ( ) : currentTime(0) { }
    void scheduleEvent (Event * newEvent)
    {
        // insert newEvent into eventQueue (Priority Queue)
        // Priority Queue is based on MinHeap using newEvent’s time
        eventQueue.push(newEvent);
    }
    void run( );
    unsigned int currentTime;
    int weightedProbability(vector<int>);
    
protected:
    priority_queue <Event*, vector<Event *>, eventComparison> eventQueue;
}theSimulation;

void SimulationFramework::run( )
{
    // execute events until event queue becomes empty
    while (!eventQueue.empty( ))
    {
        // copy & remove min-priority element (min time) from eventQueue
        Event * nextEvent = eventQueue.top();
        eventQueue.pop( );
        // update simulation’s current time
        currentTime = nextEvent->time;
        // process nextEvent
        nextEvent->processEvent( );
        // cleanup nextEvent object
        delete nextEvent;
    }
}

int SimulationFramework::weightedProbability(vector<int> weights)
{
    int sum = 0;
    int runningTotal = 0;
    int counter = 0;
    
    for(int i = 0; i < weights.size(); i++)
    {
        sum += weights[i];
    }
    
    int rval = std::rand() % sum;
    
    while(counter < weights.size() - 1)
    {
        runningTotal += weights[counter];
        if(rval < runningTotal)
            break;
        counter++;
    }
    return counter;
}
#endif /* event_h */
