/*
 *	 Floor.cc
 * 
 *  Floor class source file: The Floor class represents a floor in a building.
 *  The floor object can hold passengers, and provides functions to add and
 *  remove passengers.
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

//The function addPass() adds a pointer to a passenger to the floor's queue.
void Floor::addPass(Passenger* passenger)
{
	this->passengers.push(passenger);
}

//The function nextPass() returns a pointer to the first passenger queued
//at the floor.
Passenger* Floor::nextPass() const
{
	if(!this->passengers.empty()) // guard against runtime errors
	{
		return this->passengers.front();
	}
	else
	{
		return nullptr;
	}
}

//The function rmPass() pops the first passenger in the queue and returns
//a pointer to that passenger.
void Floor::rmPass()
{
	if(!this->passengers.empty()) // guard against runtime errors
	{
		this->passengers.pop();
	}
}