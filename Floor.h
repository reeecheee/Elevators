/*
 *	 Floor.h
 * 
 *  Floor class header file: 
 * 
 *  Author: Mike Ricci
 *  Date: 20140716
 */

#ifndef _FLOOR_H_
#define _FLOOR_H_

class Floor
{
public:

	Floor();
	virtual ~Floor();
	
	void addPassenger(Passenger passenger);

private:

	std::vector<Passenger> passengers;

}; // end Floor class

#endif // _FLOOR_H_

