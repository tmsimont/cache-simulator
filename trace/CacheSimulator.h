#ifndef CACHESIMULATOR_H
#define CACHESIMULATOR_H
#include "CacheArchitecture.h"
#include "CacheParameters.h"
#include <iostream>
#include <string>
class CacheSimulator
{
public:
	CacheSimulator();
	void createArchitecture(string jsonFilename);
	void readTrace(std::istream& source);
	~CacheSimulator();
private:
	cacheArchitecture * architecture;
};

#endif CACHESIMULATOR_H