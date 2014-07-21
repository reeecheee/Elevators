/*
 *	 Car.cc
 * 
 *  Car class source file: 
 * 
 *  Author: Mike Ricci
 *  Date: 20140716
 */

#include <deque>
#include <vector>
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
		this->passengers.push_back(passenger);
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

//The function getPrevState() returns the state the car was in before it moved
//into the STOPPING state.
Car::State Car::getPrevState() const
{
	return this->prevState;
}

//The function getState() returns the current movement state of the car.
Car::State Car::getState() const
{
	return this->state;
}

//The function getTimeInState() returns the amount of time spent in the current
//state.  The class is designed to reset the timer when state is changed or when
//a new floor is reached.
int Car::getTimeInState() const
{
	return this->timeInState;
}

//The function rmPassenger() unloads passengers whose destination floor equals
//the passed floor, and returns a vector containing pointers to those passengers.
std::vector<Passenger*> Car::rmPassenger(int floor)
{
	std::vector<Passenger*> unloaded;
	std::deque<Passenger*>::iterator it = this->passengers.begin();
	
	while(it != this->passengers.end())
	{
		if((*it)->getFloorEnd() == floor)
		{
			// erasing the element the iterator points to will increment it
			unloaded.push_back(*it);
			this->passengers.erase(it);
		}
		else
		{
			++it;
		}
	}
	return unloaded;
}

//The function setFloor() sets the car's current floor location.
void Car::setFloor(int floor)
{
	this->floor = floor;
}

//The function setPrevState() sets the car's last movement direction before moving
//into the stopping state.
void Car::setPrevState(State state)
{
	this->prevState = state;
}

//The function setState() sets the car's state to the enum newState.
void Car::setState(State newState)
{
	this->state = newState;
}

//The function setTimeInState() sets the timeInState variable to the passed int.
void Car::setTimeInState(int time)
{
	this->timeInState = time;
}

//The function updateState() updates the state of the car based on the passengers
//in the car, the passengers on the next floor that the car will pass, and the 
//passengers in the Building's queue.
void Car::updateState(int nextFlrCall)
{
	switch(this->getState())
	{
		case 0: //STOPPED = 0
		{
			//unload passengers if applicable
/*			std::deque<Passenger*>::iterator it = this->passengers.begin();
			for(it; it != this->passengers.end(); ++it)
			{
				//PROBLEM: can't iterate through the queue
				//SOLUTION: change Car::passengers to a deque
			}*/

			//load new passengers if any exist
				//PROBLEM: car doesn't know what passengers are on what floor
				//SOLUTION: ???

			if(this->passengers.size() == 0) // car is empty
			{
				if(this->getFloor() > nextFlrCall) // car is above next queued passenger
				{
					this->setState(MOVING_DOWN); // head to pick up next queued passenger
				}
				else if(this->getFloor() < nextFlrCall) // car is above next queued passenger
				{
					this->setState(MOVING_UP); // head to pick up next queued passenger
				}
			}
			else // car has passengers aboard
			{
				if(this->getFloor() > this->passengers.front()->getFloorEnd())
				{
					this->setState(MOVING_DOWN); // head to drop off next queued passenger
				}
				else if(this->getFloor() < this->passengers.front()->getFloorEnd())
				{
					this->setState(MOVING_UP); // head to drop off next queued passenger
				}
			}
			break;
		} // end STOPPED case
		
		case 1: //STOPPING = 1
		{
			if(this->timeInState < 2) // still STOPPING
			{
				++timeInState;
			}
			else // STOPPING completed
			{
				this->setState(STOPPED);
				
				if(this->prevState == MOVING_UP)
				{
					this->setFloor(this->getFloor() + 1); // arrive at floor above
				}
				else
				{
					this->setFloor(this->getFloor() - 1); // arrive at floor below
				}
				
				this->setTimeInState(0);
			}

			break;
		} // end STOPPING case
		
		case 2: //MOVING_UP = 2
		{
			if(this->timeInState < speed) // still MOVING_UP
			{
				++timeInState;
			}
			else // MOVING_UP completed
			{
				this->setState(STOPPING); // start stopping
				this->setTimeInState(0); // start timing stopping
			}
			break;
		} // end MOVING_UP case
		
		case 3: //MOVING_DOWN = 3
		{
			if(this->timeInState < speed) // still MOVING_DOWN
			{
				++timeInState;
			}
			else // MOVING_DOWN completed
			{
				this->setState(STOPPING); // start stopping
				this->setTimeInState(0); // start timing stopping
			}
			break;
		} // end MOVING_DOWN case
	} // end switch
} // end updateState()