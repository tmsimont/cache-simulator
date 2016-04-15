/* Author: Cory Linfield, Trevor Simonton, Rania Abdraba, and Anthony Pfaff
Course: CSCI 5593
Project: Semester Project Implementation
File: CacheArchitecture.cc
*/

#include <cassert>
#include <iomanip>
#include <iostream>
#include <string>
#include <iterator>

#include "CacheArchitecture.h"
#include "Cache.h"
#include "Address.h"

using namespace std;

cacheArchitecture::cacheArchitecture()
{
	numbCaches = 0;
}

cacheArchitecture::cacheArchitecture(cacheParameters firstCache)
{
	arch.resize(1);
	arch[0] = new cahce(firstCache);
	numbCaches = 1;
}

void cacheParameter::addCache(cacheParameters nextCache)
{
	arch.resize(numbCaches + 1);
	arch[numbCaches] = new cache(nextCache);
				//Add cache
	++numbCaches;

}

int cacheParameter::cacheRead(address add)						//returns time needed to read
{
	int time = 0, i = 0;
	bool found = false;

	while ((i < numbCaches) && (!found))
	{
		found = arch[i].hasAddress(add);
		if (found)
			time += arch[i].getHitTime();
		else
			time += arch[i].getMissPenalty();

		++i;
	}

	return time;
}

int cacheParameter::cacheWrite(address add)						//returns time needed to write
{
	int time = 0, i = 0;
	bool found = false;

	while ((i < numbCaches) && (!found))
	{
		found = arch[i].hasAddress(add);
		if (found)
			time += arch[i].getHitTime();
		else
			time += arch[i].getMissPenalty();

		++i;
	}

	return time;
}


cacheArchitecture::~cacheArchitecture()
{
	erase arch;
}