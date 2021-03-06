/*
 *	 Car.cc
 * 
 *  Car class source file: The Car class represents an elevator car.  The car can
 *  be in a number of states.  Functions are provided to allow the operation of the
 *  car, as well as the addition/removal of passengers from the car.
 * 
 *  Author: Mike Ricci
 *  Date: 20140716
 */

#include <deque>
#include <vector>
#include "Passenger.h"
#include "Car.h"

//CONSTRUCTOR
Car::Car(int carNum, int speed)
{
	this->carNum = carNum;
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
	if(this->passengers.size() <= 8)
	{
		this->passengers.push_back(passenger);
	}
}

//The function getCarNum() returns the number of the car.
int Car::getCarNum() const
{
	return this->carNum;
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
	int prevUnload = 0; //last minute bandaid fix
	
	while(it != this->passengers.end())
	{
		if((*it)->getFloorEnd() == floor)
		{
			if((*it)->getTimeStart() == prevUnload) // last minute bandaid fix
			{
				++it; // don't try to unload passengers more than once...segfault
			}
			else
			{
				// erasing the element the iterator points to will increment it
				unloaded.push_back(*it);
				this->passengers.erase(it);
				prevUnload = (*it)->getTimeStart();
			}
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
void Car::setPrevState(Car::State state)
{
	this->prevState = state;
}

//The function setState() sets the car's state to the enum newState.
void Car::setState(Car::State newState)
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
void Car::updateState(int nextFlrCall, bool passOnNext)
{
	// do nothing if no passengers are waiting to be picked up and no passengers
	// are aboard requiring to be dropped off
	if(nextFlrCall == -1 && this->getNumPassAboard() == 0)
	{
		return;
	}
	
	switch(this->getState())
	{
		case Car::STOPPED: //STOPPED = 0
		{
			if(this->passengers.size() == 0) // car is empty
			{
				if(this->getFloor() > nextFlrCall) // car is above next queued passenger
				{
					this->setState(Car::MOVING_DOWN); // head to pick up next queued passenger
					this->setTimeInState(0);
				}
				else if(this->getFloor() < nextFlrCall) // car is above next queued passenger
				{
					this->setState(Car::MOVING_UP); // head to pick up next queued passenger
					this->setTimeInState(0);
				}
			}
			else // car has passengers aboard
			{
				if(this->passengers.front()->getFloorEnd() >= 0 && // guard against OOR excepts
				   this->passengers.front()->getFloorEnd() <= 99)
				{
					if(this->getFloor() > this->passengers.front()->getFloorEnd())
					{
						this->setState(Car::MOVING_DOWN); // head to drop off next queued passenger
						this->setTimeInState(0);
					}
					else if(this->getFloor() < this->passengers.front()->getFloorEnd())
					{
						this->setState(Car::MOVING_UP); // head to drop off next queued passenger
						this->setTimeInState(0);
					}
				}
			}
			break;
		} // end STOPPED case
		
		case Car::STOPPING: //STOPPING = 1
		{
			if(this->timeInState < 2) // still STOPPING
			{
				++timeInState;
			}
			else // STOPPING completed
			{
				this->setState(Car::STOPPED);
				
				if(this->prevState == Car::MOVING_UP)
				{
					if(this->getFloor()+1 <= 99) // guard against out of range exceptions
					{
						this->setFloor(this->getFloor() + 1); // arrive at floor above
					}
				}
				else
				{
					if(this->getFloor()-1 >= 0) // guard against out of range exceptions
					{
						this->setFloor(this->getFloor() - 1); // arrive at floor below
					}
				}
				this->setTimeInState(0);
			}

			break;
		} // end STOPPING case
		
		case Car::MOVING_UP: //MOVING_UP = 2
		{
			if(this->timeInState < speed) // still MOVING_UP
			{
				++timeInState;
			}
			else // MOVING_UP completed
			{
				if(passOnNext) // passengers on next floor
				{
					this->setPrevState(Car::MOVING_UP); // set previous state
					this->setState(Car::STOPPING); // start stopping
					this->setTimeInState(0); // start timing stopping					
				}
				else if(this->getFloor()+1 == this->passengers.front()->getFloorEnd())
				{  
					this->setPrevState(Car::MOVING_UP); // set previous state
					this->setState(Car::STOPPING); // start stopping
					this->setTimeInState(0); // start timing stopping
				}
				else // no passengers on next floor, keep MOVING_UP
				{
					if(this->getFloor()+1 <= 99) // guard against out of range exceptions
					{
						this->setFloor(this->getFloor() + 1); // achieve next floor
						this->setTimeInState(0); // restart timer
					}
					else
					{
						this->setState(Car::STOPPING); // start stopping
						this->setTimeInState(0); // restart timer
					}
				}
			}
			break;
		} // end MOVING_UP case
		
		case Car::MOVING_DOWN: //MOVING_DOWN = 3
		{
			if(this->timeInState < speed) // still MOVING_DOWN
			{
				++timeInState;
			}
			else // MOVING_DOWN completed
			{
				if(passOnNext) // passengers on next flor
				{
					this->setPrevState(Car::MOVING_DOWN); // set previous state
					this->setState(Car::STOPPING); // start stopping
					this->setTimeInState(0); // start timing stopping
				}
				else if(this->getFloor()-1 == this->passengers.front()->getFloorEnd())
				{  
					this->setPrevState(Car::MOVING_DOWN); // set previous state
					this->setState(Car::STOPPING); // start stopping
					this->setTimeInState(0); // start timing stopping
				}
				else //no passengers on next floor, keep MOVING_DOWN
				{
					if(this->getFloor()-1 >= 0) // guard against out of range exceptions
					{
						this->setFloor(this->getFloor() - 1); // achieve next floor
						this->setTimeInState(0); // restart timer
					}
					else
					{
						this->setState(Car::STOPPING); // start stopping
						this->setTimeInState(0); // restart timer
					}
				}
			}
			break;
		} // end MOVING_DOWN case
	} // end switch
} // end updateState()