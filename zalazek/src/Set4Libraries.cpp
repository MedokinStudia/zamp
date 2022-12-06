#include "../inc/Set4Libraries.hh"

using namespace std;

Set4Libraries::Set4Libraries(map< string, MobileObj * > & _Object_List) {
  this -> pscene = new Scene(_Object_List);
  LoadLibrary("libs/libInterp4Move.so");
  LoadLibrary("libs/libInterp4Set.so");
  LoadLibrary("libs/libInterp4Rotate.so");
  LoadLibrary("libs/libInterp4Pause.so");
}

Set4Libraries::~Set4Libraries() {
  mapLibraries.clear();
  if (nullptr != pscene)
    delete pscene;
}

void Set4Libraries::LoadLibrary(string path) {
  LibInterface * pLibrary = new LibInterface(path);
  mapLibraries.insert({
    pLibrary -> _Lib_name,
    pLibrary
  });
}

bool Set4Libraries::ExecPreprocessor(const char * NazwaPliku, istringstream & IStrm4Cmds) {
  string Cmd4Preproc = "cpp -P ";
  char Line[500];
  ostringstream OTmpStrm;

  Cmd4Preproc += NazwaPliku;
  FILE * pProc = popen(Cmd4Preproc.c_str(), "r");

  if (!pProc)
    return false;

  while (fgets(Line, 500, pProc)) {
    OTmpStrm << Line;
  }

  IStrm4Cmds.str(OTmpStrm.str());
  return pclose(pProc) == 0;
}



bool Set4Libraries::ReadCommands(istringstream & iStrm, int socket) {
  string _Cmd_Name, _Obj_Name;
  bool flag;
  string message = "Clear\n";

  vector < MobileObj * > _objectsList = this -> getScene() -> getObjects();

  for (MobileObj * _objectPtr: _objectsList) {
    message += "AddObj " + _objectPtr -> returnParameters();
  }
  const char * sConfigCmds = message.c_str();
  Send(socket, sConfigCmds);

  while (iStrm >> _Cmd_Name)
  {
    vector < thread * > _THREAD_list;

    while (_Cmd_Name != "End_Parallel_Actions") {

      if (_Cmd_Name != "Pause" && _Cmd_Name != "Begin_Parallel_Actions")
        iStrm >> _Obj_Name;
      flag = true;
      map < string, LibInterface * > ::iterator Iter = this -> mapLibraries.find(_Cmd_Name);
      if (Iter == this -> mapLibraries.end()) {
        if (_Cmd_Name != "Begin_Parallel_Actions")
          cerr << "Komenda " << _Cmd_Name << " nie została odnaleziona" << endl;

        flag = false;
      }
      

      if (flag) {
        Interp4Command * pCommand = Iter -> second -> pCreateCmd();
        if (!pCommand -> ReadParams(iStrm)) {
          cerr << "!!! Nieporawne parametry dla komendy '" << _Cmd_Name << endl;
          delete pCommand;
          return false;
        }
        MobileObj * _Obj = this -> pscene -> FindMobileObj(_Obj_Name);
        if (_Obj == nullptr) {
          cerr << "!!! Obiekt " << _Obj_Name << " nie istnieje" << endl;
          delete pCommand;
          return false;
        } 
        else
        {
          pCommand -> PrintCmd();
          thread * new_thread = new thread( & Interp4Command::ExecCmd, pCommand, _Obj, this -> pscene);
          _THREAD_list.push_back(new_thread);
        }
      }

      iStrm >> _Cmd_Name;
    }
    for (thread * thread_object: _THREAD_list)
    {
      thread_object -> join();
      delete thread_object;
    }
  }
  return true;
}
