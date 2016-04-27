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
#include "CacheUpdaterRandom.h"
#include "CacheUpdaterLRU.h"
#include "CacheUpdaterFIFO.h"
#include "CacheUpdaterPseudoLRU.h"

using namespace std;
CacheUpdater * getUpdaterForPolicy(cacheParameters::ReplacementPolicy policy, cache * targetCache);

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

	cacheUpdaters.resize(numbCaches + 1);
	cacheUpdaters[numbCaches] = getUpdaterForPolicy(caches[numbCaches]->getReplacementPolicy(), caches[numbCaches]);

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
		return instructionCache;
	else
		return caches[0];
}

CacheUpdater * cacheArchitecture::getInstructionCacheUpdater()
{
	if (hasInstructionCache)
		return instructionUpdater;
	else
		return cacheUpdaters[0];
}

int cacheArchitecture::getNumbCaches() {
	return numbCaches;
}

void cacheArchitecture::useInstructionCache(cacheParameters instrCacheParam)
{
	hasInstructionCache = true;
	instructionCache = new cache(instrCacheParam);
	instructionUpdater = getUpdaterForPolicy(instructionCache->getReplacementPolicy(), instructionCache);
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
	if (hasInstructionCache) {
		delete instructionCache;
		delete instructionUpdater;
	}
}

CacheUpdater * getUpdaterForPolicy(cacheParameters::ReplacementPolicy policy, cache * targetCache) {
	switch (policy) {
	case cacheParameters::ReplacementPolicy::LRU:
		return new CacheUpdaterLRU(targetCache);

	case cacheParameters::ReplacementPolicy::PSEUDOLRU:
		return new CacheUpdaterPseudoLRU(targetCache);

	case cacheParameters::ReplacementPolicy::FIFO:
		return new CacheUpdaterFIFO(targetCache);

	case cacheParameters::ReplacementPolicy::RANDOM:
	default:
		return new CacheUpdaterRandom(targetCache);
	}
}