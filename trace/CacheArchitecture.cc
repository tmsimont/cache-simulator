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

using namespace std;

cacheArchitecture::cacheArchitecture()
{
	numbCaches = 0;
}

cacheArchitecture::cacheArchitecture(cacheParameters firstCache)
{
	numbCaches = 0;
	addCache(firstCache);
}

void cacheArchitecture::addCache(cacheParameters nextCache)
{
	caches.resize(numbCaches + 1);
	caches[numbCaches] = new cache(nextCache);

	// todo: use different updaters based on update policy of cache
	cacheUpdaters.resize(numbCaches + 1);
	cacheUpdaters[numbCaches] = new CacheUpdater(caches[numbCaches]);

	++numbCaches;
}

cache* cacheArchitecture::getCache(int priority)
{
	return caches[priority];
}
CacheUpdater* cacheArchitecture::getCacheUpdater(int priority)
{
	return cacheUpdaters[priority];
}

cache * cacheArchitecture::getInstructionCache()
{
	if (hasInstructionCache)
		return &instructionCache;
	else
		return caches[0];
}

CacheUpdater * cacheArchitecture::getInstructionCacheUpdater()
{
	if (hasInstructionCache)
		return &instructionUpdater;
	else
		return cacheUpdaters[0];
}

int cacheArchitecture::getNumbCaches() {
	return numbCaches;
}

void cacheArchitecture::useInstructionCache(cacheParameters instrCacheParam)
{
	hasInstructionCache = true;
	instructionCache = cache(instrCacheParam);
	instructionUpdater = CacheUpdater(&instructionCache);
}

cacheArchitecture::~cacheArchitecture()
{
	for (int i = 0; i < caches.size(); i++) {
		delete (caches[i]);
	}
	caches.clear();
	for (int i = 0; i < cacheUpdaters.size(); i++) {
		delete (cacheUpdaters[i]);
	}
	cacheUpdaters.clear();
}