#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <cstdio>
#include <sstream>
#include "../inc/Interp4Command.hh"
#include "../inc/MobileObj.hh"
#include "../inc/LibInterface.hh"
#include "../inc/Set4Libraries.hh"
#include "../inc/Configuration.hh"
#include "../inc/xmlinterp.hh"
#include "../inc/AccessControl.hh"
#include "../inc/Port.hh"



#define LINE_SIZE 500

using namespace std;

int main()
{
  istringstream iStrm; // strumień danych wejściowych komend
  Configuration config;

  if (!ReadFile("config/config.xml", config)) {
    cerr << "!!! Błąd podczas odczytu config.xml" << endl;
    return 1;
  }

  map < string, MobileObj * > objectsList = config.getObjectList();
  Set4Libraries * LibraryList = new Set4Libraries(objectsList);
  
  
  cout << "Port: " << PORT << endl;
  Scene               Scn;
  int                 Socket4Sending;
  

  return 0;
}
