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
#include "CacheUpdater.h"

using namespace std;

//is not currently returning event that is occurring, just time needed to read/write

class cacheArchitecture
{
public:
	cacheArchitecture();
	cacheArchitecture(cacheParameters firstCache);
	void addCache(cacheParameters nextCache);
	int getNumbCaches();

	cache* getCache(int priority);
	CacheUpdater* getCacheUpdater(int priority);
	cache* getInstructionCache();
	CacheUpdater* getInstructionCacheUpdater();

	// pass a cache and the architecture will use this as instruction cache
	// todo: extend cacheArchitecture to cacheArchitecture instruction?
	void useInstructionCache(cacheParameters instrCacheParam);

	~cacheArchitecture();
private:
	vector<cache*> caches;
	vector<CacheUpdater*> cacheUpdaters;
	cache instructionCache;
	CacheUpdater instructionUpdater;
	bool hasInstructionCache;
	int numbCaches;
};

#endif // CACHEARCHITECTURE_H
