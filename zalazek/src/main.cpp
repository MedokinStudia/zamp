#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <cstdio>
#include <sstream>
#include "Interp4Command.hh"
#include "MobileObj.hh"
#include "LibraryInterface.hh"



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


  void *pLibHnd_Set = dlopen("libInterp4Set.so",RTLD_LAZY);
  Interp4Command *(*pCreateCmd_Set)(void);
  void *pFun_1;

  if (!pLibHnd_Set) {
    cerr << "!!! Brak biblioteki: Interp4Set.so" << endl;
    return 1;
  }


  pFun_1 = dlsym(pLibHnd_Set,"CreateCmd");
  if (!pFun_1) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Set = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun_1);


  Interp4Command *pCmd_1 = pCreateCmd_Set();
  cout << endl;
  cout << pCmd_1->GetCmdName() << endl;
  cout << endl;
  pCmd_1->PrintSyntax();
  cout << endl;
  pCmd_1->PrintCmd();
  cout << endl;
  
  delete pCmd_1;
  dlclose(pLibHnd_Set);



  void *pLibHnd_Rotate = dlopen("libInterp4Rotate.so",RTLD_LAZY);
  Interp4Command *(*pCreateCmd_Rotate)(void);
  void *pFun_2;

  if (!pLibHnd_Rotate) {
    cerr << "!!! Brak biblioteki: Interp4Rotate.so" << endl;
    return 1;
  }


  pFun_2 = dlsym(pLibHnd_Rotate,"CreateCmd");
  if (!pFun_2) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Rotate = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun_2);


  Interp4Command *pCmd_2 = pCreateCmd_Rotate();
  cout << endl;
  cout << pCmd_2->GetCmdName() << endl;
  cout << endl;
  pCmd_2->PrintSyntax();
  cout << endl;
  pCmd_2->PrintCmd();
  cout << endl;
  
  delete pCmd_2;
  dlclose(pLibHnd_Rotate);






  void *pLibHnd_Pause = dlopen("libInterp4Pause.so",RTLD_LAZY);
  Interp4Command *(*pCreateCmd_Pause)(void);
  void *pFun_3;

  if (!pLibHnd_Pause) {
    cerr << "!!! Brak biblioteki: Interp4Rotate.so" << endl;
    return 1;
  }


  pFun_3 = dlsym(pLibHnd_Pause,"CreateCmd");
  if (!pFun_3) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Pause = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun_3);


  Interp4Command *pCmd_3 = pCreateCmd_Pause();
  cout << endl;
  cout << pCmd_3->GetCmdName() << endl;
  cout << endl;
  pCmd_3->PrintSyntax();
  cout << endl;
  pCmd_3->PrintCmd();
  cout << endl;
  
  delete pCmd_3;
  dlclose(pLibHnd_Pause);





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

  LibInterface lib_set("libInterp4Set.so");
  Interp4Command *pCmd_set = lib_set.CreateCmd();
  cout << endl;
  cout << pCmd_set->GetCmdName() << endl;
  cout << endl;
  pCmd_set->PrintSyntax();
  cout << endl;
  pCmd_set->PrintCmd();
  cout << endl;
  delete pCmd_set;

  LibInterface lib_rotate("libInterp4Rotate.so");
  Interp4Command *pCmd_rotate = lib_rotate.CreateCmd();
  cout << endl;
  cout << pCmd_rotate->GetCmdName() << endl;
  cout << endl;
  pCmd_rotate->PrintSyntax();
  cout << endl;
  pCmd_rotate->PrintCmd();
  cout << endl;
  delete pCmd_rotate;

  LibInterface lib_pause("libInterp4Pause.so");
  Interp4Command *pCmd_pause = lib_pause.CreateCmd();
  cout << endl;
  cout << pCmd_pause->GetCmdName() << endl;
  cout << endl;
  pCmd_pause->PrintSyntax();
  cout << endl;
  pCmd_pause->PrintCmd();
  cout << endl;
  delete pCmd_pause;  
}
