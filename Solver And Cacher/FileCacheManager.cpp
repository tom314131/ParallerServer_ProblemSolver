#include "FileCacheManager.h"

bool FileCacheManager:: IsSolutionExists(std:: string problem){
    if(this->newProblems.count(problem)>0){
        return true;
    }
    if(this->loadedProblems.count(problem)>0){
        return true;
    }
    string line, currentProblem, currentSolution;
    while(getline(*this->readFromCache,line)){
        vector<string> probAndSol =this->ProblemAndSolutionFromCache(line);
        this->loadedProblems[probAndSol[0]]=probAndSol[1];
        if(problem.compare(probAndSol[0])==0)
        {
            return true;
        }
    }
    return false;
}


std:: string FileCacheManager:: GetSolution(std:: string problem){
    if(this->newProblems.count(problem)>0){
        return this->newProblems[problem];
    }
    if(this->loadedProblems.count(problem)>0){
        return this->loadedProblems[problem];
    }
}


void FileCacheManager::SaveSolution(std:: string problem,
                                    std:: string solution){
    this->newProblems[problem] = solution;
}

vector<string> FileCacheManager:: ProblemAndSolutionFromCache(string line){
    string problem = line.substr(0,line.find('$'));
    string solution = line.substr(line.find('$')+1, line.length());

    vector<string> problemAndSol;
    problemAndSol.push_back(problem);
    problemAndSol.push_back(solution);
    return problemAndSol;
}
FileCacheManager:: ~FileCacheManager(){
    this->writeToCache = new ofstream(CACHE_FILE,ios_base::app);
    map<string, string>::iterator it = this->newProblems.begin();
    while (it != this->newProblems.end()) {
        *this->writeToCache << it->first + "$" + it->second << endl;
        it++;
    }
    this->writeToCache->close();
    this->readFromCache->close();
    delete this->readFromCache;
    delete this->writeToCache;
}

CacheManager<string, string> *FileCacheManager::Clone() {
    return new FileCacheManager();
}

