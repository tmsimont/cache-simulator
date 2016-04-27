#ifndef CACHESEARCH_H
#define CACHESEARCH_H
#include "CacheArchitecture.h"
#include "Cache.h"
#include "Address.h"


class CacheSearch {
public:
	void search(cache * c, address * a);
	bool wasFound() { return found; };
	int blockWhereFound() { return blockIdx; }
	int setWhereFound() { return setIdx; }
private:
	bool found;
	int setIdx;
	int blockIdx;
};

#endif // CACHESEARCH_H