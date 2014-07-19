/*
 *	 Building.cc
 * 
 *  Building class source file: 
 * 
 *  Author: Mike Ricci
 *  Date: 20140716
 */

#include <queue>
#include <string>
#include <vector>
#include "Passenger.h"
#include "Floor.h"
#include "Car.h"
#include "Building.h"

//CONSTRUCTOR
Building::Building(std::string filepath, int numCars, int speed, int numFloors)
{
	
}

//VIRTUAL DESCTRUCTOR
Building::~Building()
{

}

//MEMBER FUNCTIONS

//The function addTravelTime() adds a passenger's travel time to the Building's
//travelTimes vector.  Travel time = (drop off time) - (pick up time)
void Building::addTravelTime(int travelTime)
{
	this->travelTimes.push_back(travelTime);
}

//The function addWaitTime() adds a passenger's wait time to the Building's
//waitTimes vector.  Wait time = (pick up time) - (start time)
void Building::addWaitTime(int waitTime)
{
	this->waitTimes.push_back(waitTime);
}

//The function calcTravelTime() calculates the average of the times stored in the
//Building's travelTimes vector and stores it in avgTravelTime.
void Building::calcTravelTime()
{
	int sum = 0;
	int count = 0;
	int avg;

	for(int i : travelTimes)
	{
		sum += i;
		++count;
	}

	avg = sum / count;
	this->avgTravelTime = avg;
}

//The function calcWaitTime() calculates the average of the times stored in the
//Building's waitTimes vector and stores it in avgWaitTime.
void Building::calcWaitTime()
{
	int sum = 0;
	int count = 0;
	int avg;

	for(int i : waitTimes)
	{
		sum += i;
		++count;
	}

	avg = sum / count;
	this->avgTravelTime = avg;
}

//The function getNextFloorCall()
int Building::getNextFloorCall() const
{
	return this->passengers.front().getFloorEnd();
}

//The function incrementClock() steps the Building's clock ahead by 1 second.
void Building::incrementClock()
{
	this->time = time + 1;
}

//The function updateCarStates() calls Car::updateState() on each Car object
//in the Building's cars vector.
void Building::updateCarStates()
{
	for(auto car : cars)
	{
		car.updateState();
	}
}



