#include "CacheParameters.h"
#include "CacheStatistics.h"

#include <iostream>
#include <fstream>

void createIfNDef(std::string key, std::map<std::string, int>& stat) {
  const auto &e = stat.find(key);
  if (e == stat.end()) {
    stat[key] = 0;
  }
}

cacheStatistics::cacheStatistics(int inNumbOfCaches)
{
	totalTime = 0;
	numbOfCaches = inNumbOfCaches;
  cacheReadHits = std::map<std::string, int>();
  cacheReadMisses = std::map<std::string, int>();
  cacheWriteHits = std::map<std::string, int>();
  cacheWriteMisses = std::map<std::string, int>();
}

void cacheStatistics::incrementCacheReadHits(cache* c) {
  createIfNDef(c->getName(), cacheReadHits);
  cacheReadHits[c->getName()]++;
}

void cacheStatistics::incrementCacheReadMisses(cache* c) {
  createIfNDef(c->getName(), cacheReadMisses);
  cacheReadMisses[c->getName()]++;
}

void cacheStatistics::incrementCacheWriteHits(cache* c) {
  createIfNDef(c->getName(), cacheWriteHits);
  cacheWriteHits[c->getName()]++;
}

void cacheStatistics::incrementCacheWriteMisses(cache* c) {
  createIfNDef(c->getName(), cacheWriteMisses);
  cacheWriteMisses[c->getName()]++;
}

void cacheStatistics::display()
{
	std::cout << "-----------------------------------------------\n";
	std::cout << "Simulation Statistics\n";
	std::cout << "Total Time: " << totalTime << std::endl;

  std::cout << "CACHE\tEVENT       \tCOUNT" << std::endl;
	for (auto &item : cacheReadMisses)
	{
		std::cout << item.first
      << "\t"
      << "READ  MISSES\t"
      << cacheReadMisses[item.first]
      << "\t"
      << std::endl;
	}
	for (auto &item : cacheReadHits)
	{
		std::cout << item.first
      << "\t"
      << "READ  HITS  \t"
      << cacheReadHits[item.first]
      << "\t"
      << std::endl;
	}
	for (auto &item : cacheWriteMisses)
	{
		std::cout << item.first
      << "\t"
      << "WRITE MISSES\t"
      << cacheWriteMisses[item.first]
      << "\t"
      << std::endl;
	}
	for (auto &item : cacheWriteHits)
	{
		std::cout << item.first
      << "\t"
      << "WRITE HITS  \t"
      << cacheWriteHits[item.first]
      << "\t"
      << std::endl;
	}

	std::cout << "-----------------------------------------------\n";
}

cacheStatistics::~cacheStatistics()
{

}
