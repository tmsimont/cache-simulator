#pragma once
#include "CacheArchitecture.h"
#include "Cache.h"
#include "Address.h"


class CacheSearch {
public:
	bool cacheHasAddress(cache * c, address * a);
};