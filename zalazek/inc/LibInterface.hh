#ifndef  LIBINTERFACE_HH
#define  LIBINTERFACE_HH

#include "Interp4Command.hh"
#include <string>
#include <iostream>
#include <dlfcn.h>
#include <sstream>

using namespace std;

class LibInterface{

private:
void* _LibHandler;


public:
string _Lib_name;
LibInterface(string path);
~LibInterface();

Interp4Command* (* pCreateCmd)(void);
};

#endif
