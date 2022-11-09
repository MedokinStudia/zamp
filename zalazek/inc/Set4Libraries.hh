#ifndef  SET4LIBRARIES_HH
#define  SET4LIBRARIES_HH

#include "Interp4Command.hh"
#include <string>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <dlfcn.h>
#include <vector>
#include "LibInterface.hh"
#include "Scene.hh"

using namespace std;

class Set4Libraries{
private:
map <string, shared_ptr<LibInterface>> _mapLibraries;
Interp4Command * _cmdInstance;

public:
bool execPreprocessor(const char * fileName, istringstream &Istrm4Cmds);
bool loadLibraries(vector<string> pluginPath);
bool execCommands(istream &cmdStream, shared_ptr<Scene> &scene);
};

#endif