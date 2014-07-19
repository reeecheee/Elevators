/*
 *	 Car.cc
 * 
 *  Car class source file: 
 * 
 *  Author: Mike Ricci
 *  Date: 20140716
 */

#include <queue>
#include "Passenger.h"
#include "Car.h"

//CONSTRUCTOR
Car::Car()
{

}

//VIRTUAL DESTRUCTOR
Car::~Car()
{

}

//MEMBER FUNCTIONS

//The function addPassenger() loads any passengers on the floor's queue that the
//car is stopped at, up to the capacity of the car.
void Car::addPassenger()
{

}

//The function getFloor() returns the current floor that the car is at.
int Car::getFloor() const
{
	return this->floor;
}

//The function getState() returns the current movement state of the car.
Car::State Car::getState() const
{
	return this->state;
}

//The function rmPassenger() unloads passengers whose destination floor equals
//the current floor that the car is stopped at.
void Car::rmPassenger()
{
	
}

//The function setFloor() sets the car's current floor location.
void Car::setFloor(int floor)
{
	this->floor = floor;
}

//The function updateState() updates the state of the car based on the passengers
//in the car, the passengers on the next floor that the car will pass, and the 
//passengers in the Building's queue.
void Car::updateState()
{

}



