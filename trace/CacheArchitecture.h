/* Author: Cory Linfield, Trevor Simonton, Rania Abdraba, and Anthony Pfaff
Course: CSCI 5593
Project: Semester Project Implementation
File: CacheArchitecture.h
*/

#ifndef CACHEARCHITECTURE_H
#define CACHEARCHITECTURE_H

#include <string>
#include <vector>

#include "Cache.h"
#include "Address.h"
#include "CacheParameters.h"

using namespace std;

//is not currently returning event that is occurring, just time needed to read/write

class cacheArchitecure
{
public:
	cacheArchitecture();
	cacheArchitecture(cacheParameters firstCache);
	void addCache(cacheParameters nextCache);
	int cacheRead(address add);						//returns time needed to read
	int cacheWrite(address add);					//returns time needed to write

	~cacheArchitecture();
private:
	vector<cache> arch;
	int numbCaches;
};

#endif // CACHEARCHITECTURE_H
