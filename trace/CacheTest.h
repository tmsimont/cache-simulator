#include "CacheArchitecture.h"
#include <iostream>
#include <string>
class CacheTest
{
public:
	CacheTest();
	static void runTest(int argc, char ** argv);
	static void testAddressing();
	static void printCache(cache c);
	~CacheTest();
};

