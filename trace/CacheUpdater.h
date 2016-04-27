#pragma once
#include "CacheEvent.h"
#include <vector>

class CacheUpdater {
public:
	std::vector<CacheEvent> writeForward();
	std::vector<CacheEvent> writeBack();
};