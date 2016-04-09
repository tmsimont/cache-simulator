#pragma once
#include <vector>
#include "Cache.h"

using std::vector;

class Cache {
public:
	// todo: consider a hash map "L1" map to a Cache instance
	vector<Cache> sets;
};