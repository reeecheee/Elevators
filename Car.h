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
		STOPPED,
		STOPPING,
		MOVING_UP,
		MOVING_DOWN
	};

	Car();
	virtual ~Car();

	void addPassenger();
	int getFloor() const;
	State getState() const;
	void removePassenger();
	void setFloor();
	void updateState();

private:

	std::queue<Passenger> passengers;
	int floor = 0;
	static const int speed = 10;
	State state = STOPPED;

}; // end Car class

#endif // _CAR_H_

