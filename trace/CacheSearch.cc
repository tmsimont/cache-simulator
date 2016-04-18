#include "CacheSearch.h"

bool CacheSearch::cacheHasAddress(cacheArchitecture ca, address a)
{
	int time = 0, i = 0;
	bool found = false;

	while ((i < ca.getNumbCaches()) && (!found))
	{
		cache& thisCache = ca.getCache(i);
		found = thisCache.hasAddress(a);
		if (found)
		{
			time += thisCache.getHitTime();
		}
		else
		{
			time += thisCache.getMissPenalty();
		}
		thisCache.write(a);
		++i;
	}

	return time;
}
