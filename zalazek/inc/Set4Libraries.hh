#ifndef  SET4LIBRARIES_HH
#define  SET4LIBRARIES_HH

#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <cstdio>
#include <dlfcn.h>
#include <memory>
#include <vector>
#include "../inc/LibInterface.hh"
#include "../inc/Scene.hh"
#include "../inc/Interp4Command.hh"
#include <thread>
#include "../inc/klient.hh"
using namespace std;

class Set4Libraries{
private:
map <string, LibInterface *> mapLibraries;
Interp4Command * pcmdInstance;
Scene * pscene;

public:
Set4Libraries(map <string, MobileObj * > & _Object_List);
~Set4Libraries();

void LoadLibrary(string path);
bool ExecPreprocessor(const char * fileName, istringstream &Istrm4Cmds);
bool ReadCommands(istringstream & iStrm, int socket);

Scene * getScene() {
    return this -> pscene;
  }
};

#endif