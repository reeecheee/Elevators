/*
 *	 Passenger.cc
 * 
 *  Passenger class source file: The passenger class represents elevator passengers
 *  and stores their origin and destination floors, the time they arrive at the
 *  origin, and their pick up and drop off times.  Getters are provided for the
 *  initial time/floors, getters and setters are provided for the times that are
 *  determined at pick up and drop off.
 * 
 *  Author: Mike Ricci
 *  Date: 20140716
 */

#include "Passenger.h"

//CONSTRUCTOR
Passenger::Passenger(int timeStart, int floorStart, int floorEnd)
{
	this->timeStart = timeStart;

	if(floorStart >= 0 && floorStart <= 99) //guard against out of range excepts
	{
		this->floorStart = floorStart;
	}

	if(floorEnd >= 0 && floorStart <= 99) //guard against out of range excepts
	{
		this->floorEnd = floorEnd;
	}
}

//VIRTUAL DESCTRUCTOR
Passenger::~Passenger()
{

}

//MEMBER FUNCTIONS

//The function getFloorEnd() returns the passenger's destination floor.
int Passenger::getFloorEnd() const
{
	return this->floorEnd;
}

//The function getFloorStart() returns the passenger's start floor.
int Passenger::getFloorStart() const
{
	return this->floorStart;
}

//The function getTimeDropOff() returns the time the passenger was dropped off
//at their destination floor.
int Passenger::getTimeDropOff() const
{
	return this->timeDropOff;
}

//The function getTimePickUp() returns the time the passenger was picked up at
//their origin floor.
int Passenger::getTimePickUp() const
{
	return this->timePickUp;
}

//The function getTimeStart() returns the time the passenger was created.
int Passenger::getTimeStart() const
{
	return this->timeStart;
}

//The function setTimeDropOff() sets the time the passenger was dropped off at 
//their destination floor.
void Passenger::setTimeDropoff(int time)
{
	this->timeDropOff = time;
}

//The function setTimePickUp() sets the time the passenger was picked up at
//their origin floor.
void Passenger::setTimePickUp(int time)
{
	this->timePickUp = time;
}