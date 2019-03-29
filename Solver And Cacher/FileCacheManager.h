#ifndef AP_SECONDMS_FILECACHEMANAGER_H
#define AP_SECONDMS_FILECACHEMANAGER_H

#include "CacheManager.h"
#include <string>
#include <map>
#include <fstream>
#include <vector>

#define CACHE_FILE "cache.txt"

using namespace std;

class FileCacheManager : public CacheManager<string, string> {
private:
    ofstream *writeToCache;
    fstream *readFromCache;
    map<string, string> loadedProblems;
    map<string, string> newProblems;


public:
    //CTOR
    FileCacheManager() {
        this->readFromCache = new fstream();
        this->readFromCache->open(CACHE_FILE);
    }

    bool IsSolutionExists(string problem) override;

    string GetSolution(string problem) override;

    void SaveSolution(string problem, string solution) override;

    ~FileCacheManager() override;

    vector<string> ProblemAndSolutionFromCache(string line);

    CacheManager<string, string> *Clone() override;
};


#endif
