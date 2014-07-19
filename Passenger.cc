/*
 *	 Passenger.cc
 * 
 *  Passenger class source file: 
 * 
 *  Author: Mike Ricci
 *  Date: 20140716
 */

#include "Passenger.h"


//CONSTRUCTOR
Passenger::Passenger(int timeStart, int floorStart, int floorEnd)
{
	this->timeStart = timeStart;
	this->floorStart = floorStart;
	this->floorEnd = floorEnd;
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


