#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <cstdio>
#include <sstream>
#include "Interp4Command.hh"
#include "MobileObj.hh"
#include "LibInterface.hh"
#include "Set4Libraries.hh"



#define LINE_SIZE 500

using namespace std;


bool ExecPreprocessor(const char *NazwaPliku, istringstream &IStrm4Cmds){

  string Cmd4Preproc = "cpp -P ";
  char Line[LINE_SIZE];
  ostringstream OTmpStrm;

  Cmd4Preproc += NazwaPliku;
  FILE * pProc = popen(Cmd4Preproc.c_str(), "r");

  if (!pProc)
    return false;

  while (fgets(Line, LINE_SIZE, pProc)) {
    OTmpStrm << Line;
  }

  IStrm4Cmds.str(OTmpStrm.str());
  return pclose(pProc) == 0;
}



int main()
{
  void *pLibHnd_Move = dlopen("libInterp4Move.so",RTLD_LAZY);
  Interp4Command *(*pCreateCmd_Move)(void);
  void *pFun;

  if (!pLibHnd_Move) {
    cerr << "!!! Brak biblioteki: Interp4Move.so" << endl;
    return 1;
  }


  pFun = dlsym(pLibHnd_Move,"CreateCmd");
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Move = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun);


  Interp4Command *pCmd = pCreateCmd_Move();
  cout << endl;
  cout << pCmd->GetCmdName() << endl;
  cout << endl;
  pCmd->PrintSyntax();
  cout << endl;
  pCmd->PrintCmd();
  cout << endl;
  
  delete pCmd;
  dlclose(pLibHnd_Move);




  LibInterface lib_move("libInterp4Move.so");
  Interp4Command *pCmd_move = lib_move.CreateCmd();
  cout << endl;
  cout << pCmd_move->GetCmdName() << endl;
  cout << endl;
  pCmd_move->PrintSyntax();
  cout << endl;
  pCmd_move->PrintCmd();
  cout << endl;
  delete pCmd_move;




  string plugin;
  istringstream istream;
  ExecPreprocessor("proba.txt", istream);
  while(istream >> plugin)
  {
    if(plugin == "Move")
    {
      LibInterface lib_proba1("libInterp4Move.so");
      Interp4Command *pCmd_proba1 = lib_proba1.CreateCmd();
      cout << endl;
      cout << pCmd_proba1->GetCmdName() << endl;
      cout << endl;
      pCmd_proba1->ReadParams(istream);
      pCmd_proba1->PrintSyntax();
      cout << endl;
      pCmd_proba1->PrintCmd();
      cout << endl;
      delete pCmd_proba1;  
    }

    if(plugin == "Rotate")
    {
      LibInterface lib_proba2("libInterp4Rotate.so");
        Interp4Command *pCmd_proba2 = lib_proba2.CreateCmd();
    cout << endl;
    cout << pCmd_proba2->GetCmdName() << endl;
    cout << endl;
    pCmd_proba2->ReadParams(istream);
    pCmd_proba2->PrintSyntax();
    cout << endl;
    pCmd_proba2->PrintCmd();
    cout << endl;
    delete pCmd_proba2;  
    }

    if(plugin == "Set")
    {
          LibInterface lib_proba3("libInterp4Set.so");
        Interp4Command *pCmd_proba3 = lib_proba3.CreateCmd();
    cout << endl;
    cout << pCmd_proba3->GetCmdName() << endl;
    cout << endl;
    pCmd_proba3->ReadParams(istream);
    pCmd_proba3->PrintSyntax();
    cout << endl;
    pCmd_proba3->PrintCmd();
    cout << endl;
    delete pCmd_proba3; 
    }


    if(plugin == "Pause")
    {
    LibInterface lib_proba4("libInterp4Pause.so");
    Interp4Command *pCmd_proba4 = lib_proba4.CreateCmd();
    cout << endl;
    cout << pCmd_proba4->GetCmdName() << endl;
    cout << endl;
    pCmd_proba4->ReadParams(istream);
    pCmd_proba4->PrintSyntax();
    cout << endl;
    pCmd_proba4->PrintCmd();
    cout << endl;
    delete pCmd_proba4;  
    }

  }

}
