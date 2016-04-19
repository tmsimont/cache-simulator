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

}

address::address(unsigned int addr)
{
	this->addr = addr;
}

unsigned int address::getAddr()
{
	return addr;
}

address& address::operator=(const address &b)
{
	this->addr = b.addr;
	return *this;
}

bool address::operator==(const address& b)
{
	if (this->addr == b.addr)
		return true;
	return false;
}