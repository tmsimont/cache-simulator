#include "CacheTest.h"
#include <bitset>
#include "CacheSearch.h"

#define _CRT_SECURE_NO_WARNINGS 1 

#define READ 0
#define WRITE 1

#define DEBUG 1
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


void CacheTest::testAddressing() {
	cacheParameters p = cacheParameters(0, 64, "L1", 8 * 512, 1, 5, 1);
	cacheArchitecture a = cacheArchitecture(p);

	cache testingCache = a.getCache(0);

	string addrChars = "10010100101101010011010101101011";
	unsigned int addr = 0;
	for (int i = 0; i < addrChars.length(); ++i) {
		if (addrChars[i] == '1')
			addr++;
		if (i < addrChars.length() - 1)
			addr = addr << 1;
	}
	bitset<32> y(addr);
	cout << "addr bits: ";
	cout << y << endl;

	address testAddress = address(addr);


	bitset<32> z(testingCache.getIndex(testAddress));
	cout << "index bits: ";
	cout << z << endl;

	cout << "index: ";
	cout << testingCache.getIndex(testAddress) << endl;


	bitset<32> z2(testingCache.getOffset(testAddress));
	cout << "offset bits: ";
	cout << z2 << endl;

	cout << "offset: ";
	cout << testingCache.getOffset(testAddress) << endl;


	bitset<32> z3(testingCache.getTag(testAddress));
	cout << "tag bits: ";
	cout << z3 << endl;

	cout << "tag: ";
	cout << testingCache.getTag(testAddress) << endl;

	while (true);

}



int cacheRead(std::vector<cache>& arch, int numbCaches, address add)						//returns time needed to read
{
	int time = 0, i = 0;
	bool found = false;
	CacheSearch finder = CacheSearch();

	while ((i < numbCaches) && (!found))
	{
#ifdef DEBUG
		cout << "Looking in " << arch[i].getName() << " for " << add.getAddr() << endl;
#endif
		found = finder.cacheHasAddress(arch[i], add);
		if (found)
		{
#ifdef DEBUG

			cout << arch[i].getName() << " hit for " << add.getAddr() << endl;
#endif
			time += arch[i].getHitTime();
		}
		else
		{
#ifdef DEBUG
			cout << arch[i].getName() << " miss for " << add.getAddr() << endl;
#endif
			time += arch[i].getMissPenalty();
		}
#ifdef DEBUG
		cout << "Here1" << i << endl;
#endif
		arch[i].write(add);
#ifdef DEBUG
		cout << "Here2" << endl;
#endif
		++i;

		if (found)
			for (i = i - 2; i >= 0; i--)
			{
#ifdef DEBUG
				cout << "Writing back to " << arch[i].getName() << endl;
#endif
				arch[i].write(add);
			}

	}

	if (!found)
	{
		for (i = 0; i < numbCaches; i++)
		{
#ifdef DEBUG
			cout << "Writing to " << arch[i].getName() << endl;
#endif
			arch[i].write(add);
		}
	}

	return time;
}

address getAddressFromString(string addrChars) {
	unsigned int addr = 0;
	for (int i = 0; i < addrChars.length(); ++i) {
		if (addrChars[i] == '1')
			addr++;
		if (i < addrChars.length() - 1)
			addr = addr << 1;
	}
	return address(addr);
}

void CacheTest::stepThrough() {

	cacheParameters p = cacheParameters(0, 64, "L1", 8 * 512, 1, 5, 1);
	cacheParameters p2 = cacheParameters(1, 64, "L2", 8 * 64 * 1024, 1, 10, 6);
	cacheParameters p3 = cacheParameters(2, 64, "L3", 8 * 1024 * 1024, 1, 15, 11);

	cacheArchitecture a = cacheArchitecture(p);
	a.addCache(p2);


	cache testingCache = a.getCache(0);
	cache testingCacheL2 = a.getCache(1);

	address a1 = getAddressFromString("10010100101101010011010101101011");

	testingCacheL2.write(a1);

	std::vector<cache> testarch = std::vector<cache>();
	testarch.push_back(testingCache);
	testarch.push_back(testingCacheL2);
	cacheRead(testarch, 2, a1);

	while (true);
}



void CacheTest::stepThroughSmall() {

	cacheParameters p = cacheParameters(0, 2, "L1", 4, 1, 5, 1);
	cacheParameters p2 = cacheParameters(1, 2, "L2", 16, 1, 10, 6);

	cacheArchitecture a = cacheArchitecture(p);
	a.addCache(p2);


	cache testingCache = a.getCache(0);
	cache testingCacheL2 = a.getCache(1);

	address a1 = getAddressFromString("10010100101101010011010101101001");
	address a2 = getAddressFromString("10010100101101010011010101101011");
	address a3 = getAddressFromString("10010100101101010011010101101111");


	std::vector<cache> testarch = std::vector<cache>();
	testarch.push_back(testingCache);
	testarch.push_back(testingCacheL2);

	cacheRead(testarch, 2, a1);
	cacheRead(testarch, 2, a2);
	cacheRead(testarch, 2, a3);
	cacheRead(testarch, 2, a1);

//	while (true);
}

CacheTest::~CacheTest()
{
}
