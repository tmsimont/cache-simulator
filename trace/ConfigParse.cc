#include "ConfigParse.h"
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <string>
#include <sstream>

using std::vector;
using std::string;


// trim from start
static inline std::string &ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
	return ltrim(rtrim(s));
}


std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}


/**
 * Note: MUST BE EMPTY LINE AT END OF FILE
 */
ConfigParse::ConfigParse(string inputfile)
{

	ifstream confstream;
	try {
		confstream.open(inputfile);
	}
	catch (exception& e)
	{
		std::cout << "usage: [executable] [configuration file] < [input file] > [output file]" << endl;
		return;
	}
	_hasInstructionCache = false; // default

	bool parsingCaches = false;
	bool parsingCache = false;

	params = vector<cacheParameters>();
	cacheParameters parsedParms;

	int inorderPriority = 0;

	for (string line; getline(confstream, line); )
	{
		// allow comment
		if (trim(line)[0] == '#') continue;

		// ignore empty lines (if not parsing cache)
		if (!parsingCaches && !parsingCache && trim(line) == "") continue;

		if (trim(line).compare("caches") == 0) {
			parsingCaches = true;
			continue;
		}

		// todo: parse "use instruction cache" (boolean)
		if (!parsingCaches && !parsingCache) {
			vector<string> splits = split(line, ':');
			if (trim(splits[0]).compare("instructionCache") != 0) {
				continue;
			}
			else {
				if (trim(splits[1]).compare("yes") == 0) {
					_hasInstructionCache = true;
				}
				if (trim(splits[1]).compare("true") == 0) {
					_hasInstructionCache = true;
				}
				continue;
			}
		}


		// inner loop on group of caches
		if (parsingCaches) {

			// name is first line of cache
			vector<string> splits = split(line, ':');
			if (trim(splits[0]).compare("name") != 0) {
				continue;
			}
			else {
				parsingCache = true;
				parsingCaches = false;
				parsedParms = cacheParameters();
				parsedParms.name = trim(splits[1]);
				parsedParms.priority = inorderPriority++;
				continue;
			}
		}

		// inner parse individual cache
		if (parsingCache) {

			// break on empty line
			if (line == "") {
				parsingCache = false;
				parsingCaches = true;
				params.push_back(parsedParms);
				continue;
			}

			// parse individual params
			vector<string> splits = split(line, ':');
			if (trim(splits[0]).compare("associativity") == 0) {
				parsedParms.associativity = atoi(splits[1].c_str());
			}
			if (trim(splits[0]).compare("size") == 0) {
				parsedParms.size = atoi(splits[1].c_str());
			}
			if (trim(splits[0]).compare("blockSize") == 0) {
				parsedParms.blockSize = atoi(splits[1].c_str());
			}
			if (trim(splits[0]).compare("missPenalty") == 0) {
				parsedParms.missPenalty = atoi(splits[1].c_str());
			}
			if (trim(splits[0]).compare("hitTime") == 0) {
				parsedParms.hitTime = atoi(splits[1].c_str());
			}
			if (trim(splits[0]).compare("replacementPolicy") == 0) {
				if (trim(splits[1]).compare("PsuedoLRU")) {
					parsedParms.replacementPolicy = cacheParameters::ReplacementPolicy::PSEUDOLRU;
				}
				else {
					parsedParms.replacementPolicy = cacheParameters::ReplacementPolicy::RANDOM;
				}
			}
			if (trim(splits[0]).compare("writePolicy") == 0) {
				if (trim(splits[1]).compare("THROUGH")) {
					parsedParms.writePolicy = cacheParameters::WritePolicy::THROUGH;
				}
				else {
					parsedParms.writePolicy = cacheParameters::WritePolicy::BACK;
				}
				// TODO: support write back
				parsedParms.writePolicy = cacheParameters::WritePolicy::THROUGH;
			}
		}
	}

	confstream.close();
}

vector<cacheParameters> ConfigParse::getParams()
{
	return params;
}

void ConfigParse::printParams() {
	for (int i = 0; i < params.size(); ++i) {
		cout << "cache " << params[i].name << endl;
		cout << "  associativity : " << params[i].associativity << endl;
		cout << "  size : " << params[i].size << endl;
		cout << "  blockSize : " << params[i].blockSize << endl;
		cout << "  missPenalty : " << params[i].missPenalty << endl;
		cout << "  hitTime : " << params[i].hitTime << endl;
		cout << "  replacementPolicy : " << params[i].replacementPolicy << endl;
	}
}

bool ConfigParse::hasInstructionCache()
{
	return _hasInstructionCache;
}