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
Car::Car(int speed)
{
	this->speed = speed;
}

//VIRTUAL DESTRUCTOR
Car::~Car()
{

}

//MEMBER FUNCTIONS

//The function addPassenger() loads any passengers on the floor's queue that the
//car is stopped at, up to the capacity of the car.
void Car::addPassenger(Passenger* passenger)
{
	while(this->passengers.size() <= 8)
	{
		this->passengers.push(passenger);
	}
}

//The function getFloor() returns the current floor that the car is at.
int Car::getFloor() const
{
	return this->floor;
}

//The function getNumPassAboard() returns the number of passengers currently
//in the car.
int Car::getNumPassAboard() const
{
	//std::queue::size() returns type size_type, but this functions returns an int?
	//...it works, so don't complain, but I'm curious
	return this->passengers.size();
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
	
	if(this->getNumPassAboard() == 0) // the car is empty
	{
		//head for the next queued Building passenger's start floor
		//switch case on getState()
		//STOPPED = 0
		//STOPPING = 1
		//MOVING_UP = 2
		//MOVING_DOWN = 3
	}
	   
	
	else if(this->getNumPassAboard() > 0) // the car has one or more passengers aboard
	{
		//head for the first queued Car passenger's start floor
		//switch case on getState()
		//STOPPED = 0
		//STOPPING = 1
		//MOVING_UP = 2
		//MOVING_DOWN = 3
	}
}



