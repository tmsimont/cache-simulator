#ifndef CONFIGPARSE_H
#define CONFIGPARSE_H

#include <iostream>
#include <fstream>
#include "CacheParameters.h"
#include <vector>
#include <string>

class ConfigParse {
public:
	ConfigParse(string inputfile);
	vector<cacheParameters> getParams();
	void printParams();
	bool hasInstructionCache();
	bool verboseOutput();
private:
	vector<cacheParameters> params;
	bool _verboseOutput = false;
	bool _hasInstructionCache;
};

#endif // CONFIGPARSE_H
