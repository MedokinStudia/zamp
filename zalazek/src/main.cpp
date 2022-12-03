#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <cstdio>
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <vector>
#include "../inc/Interp4Command.hh"
#include "../inc/MobileObj.hh"
#include "../inc/LibInterface.hh"
#include "../inc/Set4Libraries.hh"
#include "../inc/Configuration.hh"
#include "../inc/xmlinterp.hh"
#include "../inc/AccessControl.hh"
#include "../inc/Port.hh"
#include "../inc/klient.hh"


//#define LINE_SIZE 500

using namespace std;



int main()
{
  istringstream iStrm; // strumień danych wejściowych komend
  Configuration config;

  if (!ReadFile("config/config_moj.xml", config)) {
    cerr << "!!! Błąd podczas odczytu config.xml" << endl;
    return 1;
  }

  map < string, MobileObj * > objectsList = config.getObjectList();
  Set4Libraries * LibraryList = new Set4Libraries(objectsList);
  
  
  cout << "Port: " << PORT << endl;
  Scene               Scn;
  int                 Socket4Sending;
  
  if (!OpenConnection(Socket4Sending))
    return 1;
  else
    cout << "Nawiązano połączenie z serwerem." << endl;
  cout<<endl;

  Sender * _Sender = new Sender(Socket4Sending, LibraryList -> getScene());

  /* const char *sConfigCmds =
  "Clear\n"
  "AddObj Name=Podstawa1 RGB=(20,200,200) Scale=(4,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,20) Trans_m=(-1,3,0)\n"
  "AddObj Name=Podstawa1.Ramie1 RGB=(200,0,0) Scale=(3,3,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(4,0,0)\n"
  "AddObj Name=Podstawa1.Ramie1.Ramie2 RGB=(100,200,0) Scale=(2,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(3,0,0)\n"       
  "AddObj Name=Podstawa2 RGB=(20,200,200) Scale=(4,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(-1,-3,0)\n"
  "AddObj Name=Podstawa2.Ramie1 RGB=(200,0,0) Scale=(3,3,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(4,0,0)\n"
  "AddObj Name=Podstawa2.Ramie1.Ramie2 RGB=(100,200,0) Scale=(2,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(3,0,0)\n";

  const char *ruch =
  "UpdateObj Name=Podstawa1 RotXYZ_deg=(0,90,23)\n";

  cout << "Konfiguracja:" << endl;
  cout << sConfigCmds << endl;
  Send(Socket4Sending,sConfigCmds);
  usleep(100000);
  Send(Socket4Sending,ruch);
  cout << "ruch" <<endl;
  cout << ruch <<endl;
  */

  
  //thread Thread4Sending(Fun_CommunicationThread, &_Sender);
  LibraryList -> ExecPreprocessor("program.cmd", iStrm);
  LibraryList -> ReadCommands(iStrm, Socket4Sending);

  //close(Socket4Sending, _Sender, move(Thread4Sending));
  Send(Socket4Sending,"Close\n");
 
  return 0;
}
