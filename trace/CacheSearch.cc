#include "CacheSearch.h"
#include "CacheSet.h"
#include "CacheBlock.h"
#include <vector>

void CacheSearch::search(cache *c, address *a)
{
	found = false;
	cacheSet *set = c->getCacheSet(*a);
	for (int i = 0; i < set->blocks.size() && found == false; i++) {
		found = set->blocks[i].inBlock(c->getTag(*a));
		blockIdx = i;
		setIdx = c->getIndex(*a);
	}
}