#pragma once
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
private:
	cacheArchitecture architecture;
};

