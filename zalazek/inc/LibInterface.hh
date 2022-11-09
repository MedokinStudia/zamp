#ifndef  LIBINTERFACE_HH
#define  LIBINTERFACE_HH

#include "Interp4Command.hh"
#include <string>
#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <cstdio>
#include <sstream>

using namespace std;

class LibInterface{

private:
void* _LibHandler;
string cmdName;


public:
LibInterface(string path);
~LibInterface();

Interp4Command* (* _pCreateCmd)(void);
Interp4Command* CreateCmd(){ return _pCreateCmd(); }

string GetName(){return cmdName;}
};

#endif
