#include "CacheUpdaterPseudoLRU.h"

using std::vector;

CacheUpdaterPseudoLRU::CacheUpdaterPseudoLRU(cache * target) : CacheUpdater(target)
{
	nWayBits = vector<vector<bool>>();
	for (int i = 0; i < target->numbSets; ++i) {
		vector<bool> nway = vector<bool>();
		for (int j = 0; j < target->getAssociativity(); ++j) {
			nway.push_back(0);
		}
		nWayBits.push_back(nway);
	}
}

std::vector<CacheEvent> CacheUpdaterPseudoLRU::writeToCache(address * addr)
{
	events = std::vector<CacheEvent>();

	// get set from cache based on address (cache will use index)
	int targetIdx = targetCache->getIndex(*addr);
	cacheSet *targetSet = targetCache->getCacheSet(*addr);

	// determine target block
	cacheBlock * targetBlock;

	// find the first not-recently used
	bool searching = true;
	int i = 0;
	while (searching && i < nWayBits[targetIdx].size()) {
		searching = nWayBits[targetIdx][i] && searching;
		++i;
	}
	--i;
	// we're assuming i < nWayBits.size() because nWayBits is maintained at each hit...
	targetBlock = &(targetSet->blocks[i]);
	recordUse(targetIdx, i);

	// adjust the block tag and valid bit
	address tag = address(targetCache->getTag(addr->getAddr()));
	targetBlock->validBit = true;
	targetBlock->addr = tag;

	return events;
}

void CacheUpdaterPseudoLRU::hitCache(address * addr, int setIdx, int blockIdx)
{
	recordUse(setIdx, blockIdx);
}

void CacheUpdaterPseudoLRU::recordUse(int setIdx, int blockIdx) {
	// mark block as recently used
	nWayBits[setIdx][blockIdx] = 1;

	// check if all bits are now 1
	bool full = true;
	for (int i = 0; i < nWayBits[setIdx].size() && full; ++i) {
		full = nWayBits[setIdx][i] && full;
	}

	// if all are 1, reset bits
	if (full) {
		for (int j = 0; j < targetCache->getAssociativity(); ++j) {
			nWayBits[setIdx][j] = 0;
		}
		// keep this bit as 1, all others now 0
		nWayBits[setIdx][blockIdx] = 1;
	}
}