#include "CacheUpdaterRandom.h"
#include <random>
#include <iomanip>

cacheBlock * CacheUpdaterRandom::getBlockForReplacement(address * addr, cacheSet * set)
{
	default_random_engine generator;
	uniform_int_distribution<int> distribution(0, set->numbBlocks - 1);
	generator.seed((unsigned int)time(nullptr));
	return &(set->blocks[distribution(generator)]);
}

CacheUpdaterRandom::~CacheUpdaterRandom()
{
}
