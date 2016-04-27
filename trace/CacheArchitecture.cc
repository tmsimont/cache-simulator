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

cache* cacheArchitecture::getCache(int priority)
{
	return &(caches[priority]);
}

cache * cacheArchitecture::getInstructionCache()
{
	if (hasInstructionCache)
		return &instructionCache;
	else
		return &(caches[0]);
}

int cacheArchitecture::getNumbCaches() {
	return numbCaches;
}

void cacheArchitecture::useInstructionCache(cacheParameters instrCacheParam)
{
	hasInstructionCache = true;
	instructionCache = cache(instrCacheParam);
}

cacheArchitecture::~cacheArchitecture()
{

}