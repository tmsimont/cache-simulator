/* Author: Cory Linfield, Trevor Simonton, Rania Abdraba, and Anthony Pfaff
Course: CSCI 5593
Project: Semester Project Implementation
File: Address.h
*/

#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>
#include <vector>
#include <bitset>

using namespace std;

class address
{
public:
	address();
	address(unsigned int addr);
	bool operator==(const address& b);
	address& operator=(const address &b);
	static const int ADDRESS_SIZE = 32;
	unsigned int getAddr();
private:
	unsigned int addr;
};

#endif // ADDRESS_H
