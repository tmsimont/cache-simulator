#ifndef CACHESTATISTICS_H
#define CACHESTATISTICS_H

//#include "CacheParameters.h"
#include "CacheArchitecture.h""

#include <vector>

class cacheStatistics {
public:
	cacheStatistics(cacheArchitecture arch);
	void incrementCacheHits(int priority);
	void incrementCacheMisses(int priority);
	void incrementTime(int timeIncrease);
	
	void display();

private:
	int numbOfCaches;
	int totalTime;
	std::vector<int> cacheHits;
	std::vector<int> cacheMisses;

};

#endif // CACHESTATISTICS_H
