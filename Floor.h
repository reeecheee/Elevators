/*
 *	 Floor.h
 * 
 *  Floor class header file: The Floor class represents a floor in a building.
 *  The floor object can hold passengers, and provides functions to add and
 *  remove passengers.
 * 
 *  Author: Mike Ricci
 *  Date: 20140716
 */

#ifndef _FLOOR_H_
#define _FLOOR_H_

#include <queue>

class Floor
{
public:

	Floor();
	virtual ~Floor();
	
	void addPass(Passenger* passenger);
	Passenger* nextPass() const;
	void rmPass();

private:

	std::queue<Passenger*> passengers;

}; // end Floor class

#endif // _FLOOR_H_