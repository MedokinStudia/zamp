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