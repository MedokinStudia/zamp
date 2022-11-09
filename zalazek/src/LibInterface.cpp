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

  _pCreateCmd = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun);
  

  pFun = dlsym(_LibHandler,"GetCmdName");
  
  if (!pFun) 
  {
    std::cerr << "!!! Nie znaleziono funkcji GetCmdName dla "<< fileName << std::endl;
    //return false;
  }
  
  cmdNameFcn = reinterpret_cast<const char* (*)(void)>(pFun);

  cmdName = cmdNameFcn();
}
 

LibInterface::~LibInterface()
{
  dlclose(_LibHandler);
}
  
