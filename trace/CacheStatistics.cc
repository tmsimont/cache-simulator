#include "CacheParameters.h"
#include "CacheArchitecture.h"

#include <iostream>
#include <fstream>

cacheStatistics::cacheStatistics(cacheArchitecture arch)
{
	totalTime = 0;
	numbOfCaches = arch.getNumbCaches();

	cacheHits.assign(numbOfCaches, 0);
	cacheMisses.assign(numbOfCaches, 0);

}

void cacheStatistics::incrementCacheHits(int priority)
{
	cacheHits[priority]++;
}

void cacheStatistics::incrementCacheMisses(int priority)
{
	cacheMisses[priority]++;
}

void cacheStatistics::incrementTime(int timeIncrease)
{
	totalTime += timeIncrease;
}

void cacheStatistics::display()
{
	std::cout << "-----------------------------------------------\n";
	std::cout << "Simulation Statistics\n";
	std::cout << "Total Time: " << totalTime << endl;

	for (int i = 0; i < numbOfCaches; ++i)
	{
		std::cout << "Cache " << i << " hits: " << cacheHits[i] << ", misses: " << cacheMisses[i] << endl;
	}
	std::cout << "-----------------------------------------------\n";
}