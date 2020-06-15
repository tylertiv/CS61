/*
    SoftwareGurusBar.hpp
    DiscreteEventSimulation

    Implements all necesary components specific to the Beers, Bars, Drinkers
    Simulation. Makes use of the the Simulation Framework provided in event.h
    and extends the event class provided there.
 
    Created by Tyler Tivadar on 5/22/19.
*/

#ifndef SoftwareGurusBar_hpp
#define SoftwareGurusBar_hpp

#include "event.h"
#include <time.h>

using std::cout;
using std::endl;
using std::string;

// randomInteger class is used to obtain random integers. Uses rand
//               in order generate a random number for the randBetween function
class randomInteger
{
public:
    unsigned int operator ( ) (unsigned int);
} randomizer;


unsigned int randomInteger::operator ( ) (unsigned int max)
{
    // rand return random integer
    // convert to unsigned to make positive
    // take remainder to put in range unsigned
    int rval = rand( );
    return rval % max;
}

unsigned int randBetween(int low, int high)
{
    return low + randomizer(high - low);
};

// SoftwareGurusBar class makes use of the simulation framework to schedule
//                  arrive, order, reorder, and leave events for the bar.
//                  Contains a profit tracking variable and counts number
//                  of currently available seats at the bar
class SoftwareGurusBar
{
public:
    // try with 50 chairs, then try with 40, 60, ... // in order to find out “optimal” profit prospects
    SoftwareGurusBar():freeChairs(0), profit(0.0) { }
    SoftwareGurusBar(int numSeats):freeChairs(numSeats), profit(0.0) { }
    bool canSeat (unsigned int numberOfPeople); // slide 15
    void order(unsigned int beerType);
    void leave(unsigned int numberOfPeople);
    unsigned int freeChairs; double profit;
    void setSeats(int);
}theBar;



bool SoftwareGurusBar::canSeat (unsigned int numberOfPeople)
{
    // if sufficient room, then seat customers
    cout << "Time: " << theSimulation.currentTime;
    cout << " Group of " << numberOfPeople << " customers arrives";
    if (numberOfPeople < freeChairs)
    {
        cout << " Group is seated" << endl;
        freeChairs -= numberOfPeople;
        return true;
    }
    else
    {
        cout << " Group is seated" << endl; freeChairs -= numberOfPeople;
        cout << " No room, group leaves" << endl;
        return false;
    }
}

void SoftwareGurusBar::order (unsigned int beerType)
{
    string beerTypes[] {"Local", "Imported", "Special"};
    int beerPrices[] {2, 3, 4};
    
    // serve beer
    cout << "Time: " << theSimulation.currentTime;
    cout << " serviced order for " << beerTypes[beerType] << " beer " << '(' << beerType+1 <<  ')' << endl; // update profit based on this beerType
    
    profit += beerPrices[beerType];
}

void SoftwareGurusBar::leave (unsigned int numberOfPeople)
{
    // people leave, free up chairs
    cout << "Time: " << theSimulation.currentTime;
    cout << " group of size " << numberOfPeople << " leaves" << endl;
    freeChairs += numberOfPeople;
}

class ArriveEvent : public Event
{
public:
    ArriveEvent (unsigned int time, unsigned int gs): Event(time), groupSize(gs) { }
    virtual void processEvent ( );
protected:
    unsigned int groupSize;
};

class OrderEvent : public Event
{
public:
    OrderEvent (unsigned int time, unsigned int gs): Event(time), groupSize(gs) { }
    virtual void processEvent ( );
protected:
    unsigned int groupSize;
};

class LeaveEvent : public Event
{
public:
    LeaveEvent (unsigned int time, unsigned int gs) : Event(time), groupSize(gs){ }
    virtual void processEvent ( );
protected:
    unsigned int groupSize;
};

class ReorderEvent : public Event
{
public:
    ReorderEvent (unsigned int time, unsigned int gs) : Event(time), groupSize(gs){ }
    virtual void processEvent();
protected:
    unsigned int groupSize;
};

void ArriveEvent::processEvent( )
{
    if (theBar.canSeat(groupSize))
        // place an order within 2 & 10 minutes
        theSimulation.scheduleEvent (new OrderEvent(theSimulation.currentTime + randBetween(2,10),groupSize));
    
}

void OrderEvent::processEvent( )
{
    vector<int> orderProb = {15, 60, 25};
    // each member of the group orders a beer (type 1,2,3)
    for (int i = 0; i < groupSize; i++)
        theBar.order(theSimulation.weightedProbability(orderProb));
    int t = theSimulation.currentTime + randBetween(15,35);
    // schedule the posibility for a reorder if early enough
    // schedule a LeaveEvent for this group of drinkers
    // all the group leaves together
    if(t < 180) // stops reorders within the last hour or the group will take too long to finish their drinks
        theSimulation.scheduleEvent(new ReorderEvent(t, groupSize));
    else
        theSimulation.scheduleEvent(new LeaveEvent(t, groupSize));
};

void LeaveEvent::processEvent( )
{
    theBar.leave(groupSize);
}

void ReorderEvent::processEvent()
{
    int rand = randBetween(1, 100);
    int t = theSimulation.currentTime + randBetween(15,35);
    
    
    if(rand < 33 && t <= 205)
    {
        cout << "Group of " << groupSize << " reordering: " << endl;
        theSimulation.scheduleEvent(new OrderEvent(theSimulation.currentTime,groupSize));
    }
}
#endif /* SoftwareGurusBar_hpp */
