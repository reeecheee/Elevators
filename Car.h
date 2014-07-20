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

	Car(int speed);
	virtual ~Car();

	void addPassenger(Passenger* passenger);
	int getFloor() const;
	int getNumPassAboard() const;
	State getPrevState() const;
	State getState() const;
	int getTimeInState() const;
	void rmPassenger();
	void setFloor(int floor);
	void setPrevState(State state);
	void setState(State newState);
	void setTimeInState(int time);
	void updateState(int nextFlrCall);

private:

	std::deque<Passenger*> passengers;
	int floor = 0;
	State prevState = STOPPED;
	int speed;
	State state = STOPPED;
	int timeInState = 0;

}; // end Car class

#endif // _CAR_H_

