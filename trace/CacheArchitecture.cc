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

cacheArchitecture::cacheArchitecture()
{
	numbCaches = 0;
}

cacheArchitecture::cacheArchitecture(cacheParameters firstCache)
{
	arch.resize(1);
	arch[0] = cache(firstCache);
	numbCaches = 1;
}

void cacheArchitecture::addCache(cacheParameters nextCache)
{
	arch.resize(numbCaches + 1);
	arch[numbCaches] = cache(nextCache);
				//Add cache
	++numbCaches;

}

cache cacheArchitecture::getCache(int priority)
{
	return arch[priority];
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
#ifdef DEBUG
		cout << "Looking in " << arch[i].getName() << " for " << add.getAddr() << endl;
#endif
		found = finder.cacheHasAddress(arch[i], add);
		if (found)
		{
#ifdef DEBUG

			cout << arch[i].getName() << " hit for " << add.getAddr() << endl;
#endif
			time += arch[i].getHitTime();
		}
		else
		{
#ifdef DEBUG
			cout << arch[i].getName() << " miss for " << add.getAddr() << endl;
#endif
			time += arch[i].getMissPenalty();
		}


		++i;

		if (found)
			for (i = i - 2; i >= 0; i--)
			{
#ifdef DEBUG
				cout << "Writing back to " << arch[i].getName() << endl;
#endif
				arch[i].write(add);
			}

	}

	if (!found)
	{
		for (i = 0; i < numbCaches; i++)
		{
#ifdef DEBUG
			cout << "Writing to " << arch[i].getName() << endl;
#endif
			arch[i].write(add);
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
#ifdef DEBUG
		cout << "Looking in " << arch[i].getName() << " for " << add.getAddr() << endl;
#endif
		found = finder.cacheHasAddress(arch[i], add);
		if (found)
		{
#ifdef DEBUG
			cout << arch[i].getName() << " hit for " << add.getAddr() << endl;
#endif
			time += arch[i].getHitTime();

		}
		else
		{
#ifdef DEBUG
			cout << arch[i].getName() << " miss for " << add.getAddr() << endl;
#endif
			time += arch[i].getMissPenalty();
		}


		++i;

		if (found)
			for (i = i - 2; i >= 0; i--)
			{
#ifdef DEBUG
				cout << "Writing back to " << arch[i].getName() << endl;
#endif
				arch[i].write(add);
			}

	}

	if (!found)
	{
		for (i = 0; i < numbCaches; i++)
		{
#ifdef DEBUG
			cout << "Writing to " << arch[i].getName() << endl;
#endif
			arch[i].write(add);
		}
	}

	return time;
}


cacheArchitecture::~cacheArchitecture()
{

}