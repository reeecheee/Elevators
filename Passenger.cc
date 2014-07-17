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
int Passenger::getFloorEnd() const
{

}


