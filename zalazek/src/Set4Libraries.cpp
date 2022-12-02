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



bool Set4Libraries::ReadCommands(std::istringstream & iStrm, int socket) {
  std::string _Com_Name, _Obj_Name;
  bool flag;
  std::string message = "Clear\n";

  std::vector < MobileObj * > _objectsList = this -> getScene() -> getObjects();

  //Send(socket, "Clear\n");
  for (MobileObj * _objectPtr: _objectsList) {
    message += "AddObj " + _objectPtr -> returnParameters();
  }
  const char * sConfigCmds = message.c_str();
  Send(socket, sConfigCmds);
  //std::cout << message;

  while (iStrm >> _Com_Name) // sprawdza, czy w strumieniu jest jeszcze jakaś komenda
  {
    std::vector < std::thread * > _THREAD_list;

    while (_Com_Name != "End_Parallel_Actions") {
      //if(_Com_Name == "End_Parallel_Actions") break;

      if (_Com_Name != "Pause" && _Com_Name != "Begin_Parallel_Actions")
        iStrm >> _Obj_Name;
      flag = true;
      std::map < std::string, LibInterface * > ::iterator Iter = this -> mapLibraries.find(_Com_Name);
      if (Iter == this -> mapLibraries.end()) {
        if (_Com_Name != "Begin_Parallel_Actions")
          std::cerr << "Komenda " << _Com_Name << " nie została odnaleziona" << std::endl;

        flag = false;
      }

      // Tworzy komendę na podstawie funkcji wtyczki

      if (flag) {
        Interp4Command * pCommand = Iter -> second -> pCreateCmd();
        if (!pCommand -> ReadParams(iStrm)) {
          std::cerr << "!!! Nieporawne parametry dla komendy '" << _Com_Name << std::endl;
          delete pCommand;
          return false;
        }
        MobileObj * _Obj = this -> pscene -> FindMobileObj(_Obj_Name);
        //std::cout << _Obj_Name<<std::endl;
        if (_Obj == nullptr) {
          std::cerr << "!!! Obiekt " << _Obj_Name << " nie istnieje" << std::endl;
          delete pCommand;
          return false;
        } else {
          //pCommand->ExecCmd(_Obj, this->scena);
          pCommand -> PrintCmd();
          std::thread * new_thread = new std::thread( & Interp4Command::ExecCmd, pCommand, _Obj, this -> pscene);
          _THREAD_list.push_back(new_thread);
          //if(pCommand->ExecCmd(_Obj, socket)){std::cout<<"Udało się załodować obiekt z sceny"<<std::endl;}
        }
      }

      iStrm >> _Com_Name;
    }
    for (std::thread * thread_object: _THREAD_list) // czekaj na zakończenie wszystkich zadań
    {
      thread_object -> join();
      delete thread_object;
    }
  }
  return true;
}
