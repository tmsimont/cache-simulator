#include "CacheTest.h"
#include <bitset>

#define _CRT_SECURE_NO_WARNINGS 1 

#define READ 0
#define WRITE 1
#define INSTRUCTION 2

//#define DEBUG 1
CacheTest::CacheTest()
{
}

void CacheTest::runTest(int argc, char ** argv )
{


	for (int i = 1; i < argc - 1; i++)
	{
		if (string(argv[i]) == "-iL1")
		{

		}
		else if(string(argv[i]) == "-iL2")
		{

		}
		else if (string(argv[i]) == "-iL3")
		{

		}
		else if (string(argv[i]) == "-dL1")
		{

		}
		else if (string(argv[i]) == "-dL2")
		{

		}
		else if (string(argv[i]) == "-dL3")
		{

		}
	}

	cacheParameters d1 = cacheParameters(0, 64, "dL1", 1024, 2, 5, 1);
	cacheParameters d2 = cacheParameters(1, 64, "dL2", 8 * 64 * 1024, 4, 10, 6);
	cacheParameters d3 = cacheParameters(2, 64, "dL3", 8 * 1024 * 1024, 1, 15, 11);

	cacheArchitecture data = cacheArchitecture(d1);
	data.addCache(d2);
	//data.addCache(d3);
	cacheParameters i1 = cacheParameters(0, 64, "iL1", 1024, 2, 5, 1);
	cacheParameters i2 = cacheParameters(1, 64, "iL2", 8 * 64 * 1024, 4, 10, 6);
	cacheParameters i3 = cacheParameters(2, 64, "iL3", 8 * 1024 * 1024, 1, 15, 11);
	cacheArchitecture instr = cacheArchitecture(i1);
	instr.addCache(i2);
	//instr.addCache(d3);


	unsigned int action;
	unsigned int addr;

	unsigned long long time = 0;



	for (string line; getline(cin, line);)
	{
		scanf_s("%u %x", &action, &addr);
		if (action == READ)
		{
			time += data.cacheRead(address(addr));
		}
		else if(action == WRITE)
		{
			time += data.cacheWrite(address(addr));
		}
		else if (action == INSTRUCTION)
		{
			time += instr.cacheRead(address(addr));
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

CacheTest::~CacheTest()
{
}
