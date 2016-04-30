#ifndef CACHESTATISTICS_H
#define CACHESTATISTICS_H

#include <vector>

class cacheStatistics {
public:
	cacheStatistics(int numbOfCaches);
	~cacheStatistics();
	void incrementCacheReadHits(int priority){ cacheReadHits[priority]++; }
	void incrementCacheReadMisses(int priority){ cacheReadMisses[priority]++; }
	void incrementCacheWriteHits(int priority){ cacheWriteHits[priority]++; }
	void incrementCacheWriteMisses(int priority){ cacheWriteMisses[priority]++; }
	void incrementInstCacheReadHits() { instructionCacheReadHits++; }
	void incrementInstCacheReadMisses() { instructionCacheReadMisses++; }
	void incrementInstCacheWriteHits() { instructionCacheWriteHits++; }
	void incrementInstCacheWriteMisses() { instructionCacheWriteMisses++; }
	void incrementTime(int timeIncrease){ totalTime += timeIncrease; }
	
	void display();

private:
	int numbOfCaches;
	int totalTime;
	std::vector<int> cacheReadHits;
	std::vector<int> cacheReadMisses;
	std::vector<int> cacheWriteHits;
	std::vector<int> cacheWriteMisses;

	int instructionCacheReadHits;
	int instructionCacheReadMisses;
	int instructionCacheWriteHits;
	int instructionCacheWriteMisses;


};

#endif // CACHESTATISTICS_H
