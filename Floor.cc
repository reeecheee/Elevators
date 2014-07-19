/*
 *	 Floor.cc
 * 
 *  Floor class source file: 
 * 
 *  Author: Mike Ricci
 *  Date: 20140716
 */

#include <queue>
#include "Passenger.h"
#include "Floor.h"

//CONSTRUCTOR
Floor::Floor()
{

}

//VIRTUAL DESCTRUCTOR
Floor::~Floor()
{

}

//MEMBER FUNCTIONS

//The function addPassenger() adds a pointer to a passenger to the floor's queue.
void Floor::addPassenger(Passenger* passenger)
{
	this->passengers.push(passenger);
}

//The function firstPassenger() returns a pointer to the first passenger queued
//at the floor.
Passenger* Floor::firstPassenger() const
{
	return this->passengers.front();
}

//The function rmPassenger() pops the first passenger in the queue and returns
//a pointer to that passenger.
void Floor::rmPassenger()
{
	this->passengers.pop();
}




