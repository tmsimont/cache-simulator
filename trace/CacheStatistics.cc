#include "CacheParameters.h"
#include "CacheStatistics.h"

#include <iostream>
#include <fstream>

cacheStatistics::cacheStatistics(int inNumbOfCaches)
{
	totalTime = 0;
	numbOfCaches = inNumbOfCaches;

<<<<<<< HEAD

	cacheReadHits.resize(numbOfCaches);
	cacheReadHits.assign(numbOfCaches, 0);
	cacheReadMisses.resize(numbOfCaches);
	cacheReadMisses.assign(numbOfCaches, 0);
	cacheWriteHits.resize(numbOfCaches);
	cacheWriteHits.assign(numbOfCaches, 0);
	cacheWriteMisses.resize(numbOfCaches);
=======
	cacheReadHits = vector<int>();
	cacheReadHits.assign(numbOfCaches, 0);
	cacheReadMisses = vector<int>();
	cacheReadMisses.assign(numbOfCaches, 0);
	cacheWriteHits = vector<int>();
	cacheWriteHits.assign(numbOfCaches, 0);
	cacheWriteMisses = vector<int>();
>>>>>>> 7ab3eed46947acfd34e1b24adbcc702e7ad79bc5
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

cacheStatistics::~cacheStatistics()
{

}