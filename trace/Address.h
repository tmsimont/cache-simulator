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
	address(int aB, int tS, int iS, int o);

	int getTag();
	int getIndex();
	int getOffset();
	bool operator==(const address& b);
	static const int ADDRESS_SIZE = 32;
private:
	bitset<ADDRESS_SIZE> addressBits;
	int tagSize;
	int indexSize;
	int offset;
};

#endif // ADDRESS_H
