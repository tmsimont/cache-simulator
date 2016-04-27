/* Author: Cory Linfield, Trevor Simonton, Rania Abdraba, and Anthony Pfaff
Course: CSCI 5593
Project: Semester Project Implementation
File: CacheArchitecture.h
*/

#ifndef CACHEARCHITECTURE_H
#define CACHEARCHITECTURE_H

#include <string>
#include <vector>

#include "Cache.h"
#include "Address.h"
#include "CacheParameters.h"

using namespace std;

//is not currently returning event that is occurring, just time needed to read/write

class cacheArchitecture
{
public:
	cacheArchitecture();
	cacheArchitecture(cacheParameters firstCache);
	void addCache(cacheParameters nextCache);
	int cacheRead(address add);						//returns time needed to read
	int cacheWrite(address add);					//returns time needed to write
	int instructionRead(address add);
	int getNumbCaches();

	cache getCache(int priority);

	// pass a cache and the architecture will use this as instruction cache
	// todo: extend cacheArchitecture to cacheArchitecture instruction?
	void useInstructionCache(cache instrCache);

	~cacheArchitecture();
private:
	vector<cache> caches;
	cache instructionCache;
	bool hasInstructionCache;
	int numbCaches;
};

#endif // CACHEARCHITECTURE_H
