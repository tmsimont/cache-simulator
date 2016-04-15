/* Author: Cory Linfield, Trevor Simonton, Rania Abdraba, and Anthony Pfaff
Course: CSCI 5593
Project: Semester Project Implementation
File: Address.cc
*/

#include <cassert>
#include <iomanip>
#include <iostream>
#include <string>
#include <iterator>

#include "Address.h"

using namespace std;

address::address()
{
	addressBits = 0;
	tagSize = 0;
	indexSize = 0;
	offset = 0;
}

address::address(int aB, int tS, int iS, int o)
{
	addressBits = aB;
	tagSize = tS;
	indexSize = iS;
	offset = o;
}

int address::getTag()
{
	return tagSize;
}

int address::getIndex()
{
	return indexSize;
}

int address::getOffset()
{
	return offset;
}