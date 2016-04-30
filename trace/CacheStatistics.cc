#include "CacheParameters.h"
#include "CacheStatistics.h"

#include <iostream>
#include <fstream>

cacheStatistics::cacheStatistics(int numbOfCaches)
{
	totalTime = 0;

	cacheReadHits.assign(numbOfCaches, 0);
	cacheReadMisses.assign(numbOfCaches, 0);
	cacheWriteHits.assign(numbOfCaches, 0);
	cacheWriteMisses.assign(numbOfCaches, 0);

	instructionCacheReadHits = 0;
	instructionCacheReadMisses = 0;
	instructionCacheWriteHits = 0;
	instructionCacheWriteMisses = 0;
}

void cacheStatistics::display()
{
	std::cout << "-----------------------------------------------\n";
	std::cout << "Simulation Statistics\n";
	std::cout << "Total Time: " << totalTime << endl;

	for (int i = 0; i < numbOfCaches; ++i)
	{
		std::cout << "Cache " << i << " Read Hits: " << cacheReadHits[i] << ", Read Misses: " << cacheReadMisses[i] << endl;
		std::cout << "       Write Hits: " << cacheWriteHits[i] << ", Write Misses: " << cacheWriteMisses[i] << endl;
	}

	std::cout << "Instruction Cache Read Hits: " << instructionCacheReadHits << ", Read Misses: " << instructionCacheReadMisses << endl;
	std::cout << "                  Write Hits: " << instructionCacheWriteHits << ", Write Misses: " << instructionCacheWriteMisses << endl;

	std::cout << "-----------------------------------------------\n";
}