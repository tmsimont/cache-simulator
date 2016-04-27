#ifndef CACHESEARCH_H
#define CACHESEARCH_H
#include "CacheArchitecture.h"
#include "Cache.h"
#include "Address.h"


class CacheSearch {
public:
	bool cacheHasAddress(cache * c, address * a);
};

#endif // CACHESEARCH_H