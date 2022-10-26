#ifndef  LIBINTERFACE_HH
#define  LIBINTERFACE_HH

#include "Interp4Command.hh"
#include <string>
#include <iostream>

using namespace std;

class LibInterface{

private:
void* _LibHandler();

public:
string _CmdName();

LibInterface(string path);
~LibInterface();

Interp4Command* (* _pCreateCmd)(void);

};
#endif
