#include "CacheSearch.h"
#include "CacheSet.h"
#include "CacheBlock.h"
#include <vector>

bool CacheSearch::cacheHasAddress(cache c, address a)
{
	bool found = false;
	cacheSet set = c.getCacheSet(a));
	vector<cacheBlock> blocks = set.getCacheBlocks();
	for (int i = 0; i < blocks.size() && found == false; i++)
		found = blocks[i].inBlock(c.getTag(a));
	return found;
}
