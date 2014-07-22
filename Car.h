/*
 *	 Car.h
 * 
 *  Car class header file: 
 * 
 *  Author: Mike Ricci
 *  Date: 20140716
 */

#ifndef _CAR_H_
#define _CAR_H_

#include <deque>

class Car
{
public:

	enum State
	{
		STOPPED,    // = 0
		STOPPING,   // = 1
		MOVING_UP,  // = 2
		MOVING_DOWN // = 3
	};

	Car(int carNum, int speed);
	virtual ~Car();

	void addPassenger(Passenger* passenger);
	int getCarNum() const;
	int getFloor() const;
	int getNumPassAboard() const;
	Car::State getPrevState() const;
	Car::State getState() const;
	int getTimeInState() const;
	std::vector<Passenger*> rmPassenger(int floor);
	void setFloor(int floor);
	void setPrevState(Car::State state);
	void setState(State newState);
	void setTimeInState(int time);
	void updateState(int nextFlrCall, bool passOnNext);

private:

	int carNum;
	std::deque<Passenger*> passengers;
	int floor = 0;
	Car::State prevState = STOPPED;
	int speed;
	Car::State state = STOPPED;
	int timeInState = 0;

}; // end Car class

#endif // _CAR_H_

