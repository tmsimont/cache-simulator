#pragma once
#include "CacheArchitecture.h"
#include <iostream>
#include <string>
class CacheTest
{
public:
	CacheTest();
	static void runTest();
	static void testAddressing();
	static void printCache(cache c);
	~CacheTest();
};

