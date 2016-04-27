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
#include "CacheSearch.h"

#define DEBUG 1

using namespace std;

void eventCapture(string str) {
#ifdef DEBUG
	cout << str << endl;
#endif
}

cacheArchitecture::cacheArchitecture()
{
	numbCaches = 0;
}

cacheArchitecture::cacheArchitecture(cacheParameters firstCache)
{
	caches.resize(1);
	caches[0] = cache(firstCache);
	numbCaches = 1;
}

void cacheArchitecture::addCache(cacheParameters nextCache)
{
	caches.resize(numbCaches + 1);
	caches[numbCaches] = cache(nextCache);
	++numbCaches;

}

cache cacheArchitecture::getCache(int priority)
{
	return caches[priority];
}

int cacheArchitecture::getNumbCaches() {
	return numbCaches;
}

int cacheArchitecture::cacheRead(address add)						//returns time needed to read
{
	int time = 0, i = 0;
	bool found = false;
	CacheSearch finder = CacheSearch();

	while ((i < numbCaches) && (!found))
	{
		eventCapture("Looking in " + caches[i].getName() + " for ");// add.getAddr()
		found = finder.cacheHasAddress(caches[i], add);
		if (found)
		{
			eventCapture(caches[i].getName() + " hit for "); // add.getAddr()
			time += caches[i].getHitTime();
		}
		else
		{
			eventCapture(caches[i].getName() + " miss for "); // add.getAddr();
			time += caches[i].getMissPenalty();
		}
		++i;

		if (found)
			for (i = i - 2; i >= 0; i--)
			{
				eventCapture("Writing forward to " + caches[i].getName());
				caches[i].write(add);
			}

	}

	if (!found)
	{
		for (i = 0; i < numbCaches; i++)
		{
			eventCapture("Writing to " + caches[i].getName());
			caches[i].write(add);
		}
	}

	return time;
}

int cacheArchitecture::cacheWrite(address add)						//returns time needed to write
{
	int time = 0, i = 0;
	bool found = false;
	CacheSearch finder = CacheSearch();

	while ((i < numbCaches) && (!found))
	{
		eventCapture("Looking in " + caches[i].getName() + " for ");// add.getAddr()
		found = finder.cacheHasAddress(caches[i], add);
		if (found)
		{
			eventCapture(caches[i].getName() + " hit for "); // add.getAddr();
			time += caches[i].getHitTime();

		}
		else
		{
			eventCapture(caches[i].getName() + " miss for ");// + add.getAddr());
			time += caches[i].getMissPenalty();
		}


		++i;

		if (found)
			for (i = i - 2; i >= 0; i--)
			{
				eventCapture("Writing forward to " + caches[i].getName());
				caches[i].write(add);
			}

	}

	if (!found)
	{
		for (i = 0; i < numbCaches; i++)
		{
			eventCapture("Writing to " + caches[i].getName());
			caches[i].write(add);
		}
	}

	return time;
}

int cacheArchitecture::instructionRead(address add)
{
	// pass read to normal process if no instruction cache
	if (!hasInstructionCache) {
		return cacheRead(add);
	}

	// otherwise basically do the same thing... but treat caches[0] as instruction

	int time = 0, i = 0;
	bool found = false;
	CacheSearch finder = CacheSearch();

	while ((i < numbCaches) && (!found))
	{
		cache* lookingIn = &(caches[i]);
		if (i == 0) {
			lookingIn = &instructionCache;
		}

		eventCapture("Looking in " + lookingIn->getName() + " for ");// add.getAddr()
		found = finder.cacheHasAddress(*lookingIn, add);
		if (found)
		{
			eventCapture(lookingIn->getName() + " hit for "); // add.getAddr()
			time += lookingIn->getHitTime();
		}
		else
		{
			eventCapture(lookingIn->getName() + " miss for "); // add.getAddr();
			time += lookingIn->getMissPenalty();
		}
		++i;

		if (found)
			for (i = i - 2; i >= 0; i--)
			{
				eventCapture("Writing forward to " + lookingIn->getName());
				lookingIn->write(add);
			}

	}

	if (!found)
	{
		for (i = 0; i < numbCaches; i++)
		{
			cache* lookingIn = &(caches[i]);
			if (i == 0) {
				lookingIn = &instructionCache;
			}
			eventCapture("Writing to " + lookingIn->getName());
			lookingIn->write(add);
		}
	}

	return time;
}


void cacheArchitecture::useInstructionCache(cache instrCache)
{
	hasInstructionCache = true;
	instructionCache = instrCache;
}

cacheArchitecture::~cacheArchitecture()
{

}