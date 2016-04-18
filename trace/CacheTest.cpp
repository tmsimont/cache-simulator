#include "CacheTest.h"

#define READ 0
#define WRITE 1

//#define DEBUG 1
CacheTest::CacheTest()
{
}

void CacheTest::runTest()
{

	cacheParameters p = cacheParameters(0, 64, "L1", 8 * 512, 1, 5, 1);
	cacheParameters p2 = cacheParameters(1, 64, "L2", 8 * 64 * 1024, 1, 10, 6);
	cacheParameters p3 = cacheParameters(2, 64, "L3", 8 * 1024 * 1024, 1, 15, 11);

	cacheArchitecture a = cacheArchitecture(p);
	a.addCache(p2);
	//a.addCache(p3);

	unsigned int action;
	unsigned int addr;

	unsigned long long time = 0;

	for (string line; getline(cin, line);)
	{
		scanf_s("%u %x", &action, &addr);
		if (action == READ)
		{
			time += a.cacheRead(address(addr));
		}
		else if(action == WRITE)
		{
			time += a.cacheWrite(address(addr));
		}
	}
	cout << "Final results:" << endl;
	cout << "Time: " << time << endl;
}


CacheTest::~CacheTest()
{
}
