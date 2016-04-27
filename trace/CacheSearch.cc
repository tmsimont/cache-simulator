#include "CacheSearch.h"
#include "CacheSet.h"
#include "CacheBlock.h"
#include <vector>

bool CacheSearch::cacheHasAddress(cache *c, address *a)
{
	bool found = false;
	cacheSet *set = c->getCacheSet(*a);
	for (int i = 0; i < set->blocks.size() && found == false; i++)
		found = set->blocks[i].inBlock(c->getTag(*a));
	return found;
}