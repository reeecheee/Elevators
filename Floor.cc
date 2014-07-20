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

//The function addPass() adds a pointer to a passenger to the floor's queue.
void Floor::addPass(Passenger* passenger)
{
	this->passengers.push(passenger);
}

//The function nextPass() returns a pointer to the first passenger queued
//at the floor.
Passenger* Floor::nextPass() const
{
	return this->passengers.front();
}

//The function rmPass() pops the first passenger in the queue and returns
//a pointer to that passenger.
void Floor::rmPass()
{
	this->passengers.pop();
}




