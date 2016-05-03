#ifndef CACHESTATISTICS_H
#define CACHESTATISTICS_H

#include "Cache.h"
#include <map>
#include <vector>
#include <string>

class cacheStatistics {
public:
	cacheStatistics(int numbOfCaches);
	~cacheStatistics();
	void incrementCacheReadHits(cache* c);
	void incrementCacheReadMisses(cache* c);
	void incrementCacheWriteHits(cache* c);
	void incrementCacheWriteMisses(cache* c);
	void incrementTime(int timeIncrease){ totalTime += timeIncrease; }	
	void display(std::string c, std::string t);

private:
	int numbOfCaches;
	int totalTime;
	std::map<std::string, int> cacheReadHits;
	std::map<std::string, int> cacheReadMisses;
	std::map<std::string, int> cacheWriteHits;
	std::map<std::string, int> cacheWriteMisses;

};

#endif // CACHESTATISTICS_H
