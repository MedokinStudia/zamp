#include "LibInterface.hh"

LibInterface::LibInterface(string fileName)
{
  const char* (*cmdNameFcn)(void);
  void *pFun;


  _LibHandler = dlopen(fileName.c_str(),RTLD_LAZY);
  if (!_LibHandler) 
  {
    std::cerr << "!!! Brak biblioteki: " << fileName << std::endl;
    //return false;
  }

  pFun = dlsym(_LibHandler,"CreateCmd");

  if (!pFun) 
  {
    std::cerr << "!!! Nie znaleziono funkcji CreateCmd dla "<< fileName << std::endl;
    //return false;
  }

  pCreateCmd =  * reinterpret_cast < Interp4Command * ( * )(void) > (pFun);
  Interp4Command * pinterp_cmd = pCreateCmd();
  _Lib_name = pinterp_cmd -> GetCmdName();
  delete pinterp_cmd;
}
 

LibInterface::~LibInterface()
{
  dlclose(_LibHandler);
}
  
