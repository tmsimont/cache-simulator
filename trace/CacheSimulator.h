#ifndef CACHESIMULATOR_H
#define CACHESIMULATOR_H
#include "CacheArchitecture.h"
#include "CacheParameters.h"
#include "CacheStatistics.h"
#include <iostream>
#include <string>
class CacheSimulator
{
public:
	CacheSimulator();
	void createArchitecture(string inputfile);
	void readTrace(std::istream& source);
	void output();
	~CacheSimulator();
private:
	cacheArchitecture * architecture;
	bool verboseOutput = false;
	cacheStatistics * statistics;
};

#endif // CACHESIMULATOR_H
