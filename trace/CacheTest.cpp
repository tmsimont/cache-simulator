#include "CacheTest.h"
#include <bitset>

#define _CRT_SECURE_NO_WARNINGS 1 

#define READ 0
#define WRITE 1
#define INSTRUCTION 2

CacheTest::CacheTest()
{
}


void CacheTest::testAddressing() {
	/*
	cacheParameters p = cacheParameters(0, 64, "L1", 8 * 512, 1, 5, 1);
	cacheArchitecture a = cacheArchitecture(p);

	cache testingCache = *(a.getCache(0));

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
	*/

}

CacheTest::~CacheTest()
{
}
