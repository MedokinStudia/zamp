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
/*   map<string, MobileObj*> lista_przyklad;
  MobileObj *obj1 = new MobileObj;
  MobileObj *obj2 = new MobileObj;
  cout << &lista_przyklad << endl;
  cout << obj2 << endl;
  lista_przyklad.insert({"Alpha",obj1});
  lista_przyklad.insert({"Beta",obj2});

  Set4Libraries *LibraryList = new Set4L(lista_przyklad);
 */

  istringstream iStrm; // strumień danych wejściowych komend
  Configuration config;

  if (false == ReadFile("config/config.xml", config)) {
    cerr << "!!! Błąd podczas odczytu config.xml" << endl;
    return 1;
  }

  map < string, MobileObj * > objectsList = config.getObjectList();
  Set4Libraries * LibraryList = new Set4Libraries(objectsList);
  
  
  cout << "Port: " << PORT << endl;
  Scene               Scn;
  int                 Socket4Sending;
  
  //if (!OpenConnection(Socket4Sending))
  //  return 1;
  //else 
  //  cout << "polaczono z serwerem" << endl;
/*   Sender * _Sender = new Sender(Socket4Sending, LibraryList -> getScene());

  thread   Thread4Sending(Fun_CommunicationThread,&ClientSender);
  const char *sConfigCmds =
"Clear\n"
"AddObj Name=Podstawa1 RGB=(20,200,200) Scale=(4,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,20) Trans_m=(-1,3,0)\n"
"AddObj Name=Podstawa1.Ramie1 RGB=(200,0,0) Scale=(3,3,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(4,0,0)\n"
"AddObj Name=Podstawa1.Ramie1.Ramie2 RGB=(100,200,0) Scale=(2,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(3,0,0)\n"       
"AddObj Name=Podstawa2 RGB=(20,200,200) Scale=(4,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(-1,-3,0)\n"
"AddObj Name=Podstawa2.Ramie1 RGB=(200,0,0) Scale=(3,3,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(4,0,0)\n"
"AddObj Name=Podstawa2.Ramie1.Ramie2 RGB=(100,200,0) Scale=(2,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(3,0,0)\n";


  cout << "Konfiguracja:" << endl;
  cout << sConfigCmds << endl;
  
  Send(Socket4Sending,sConfigCmds);
  

  cout << "Akcja:" << endl;    
  for (GeomObject &rObj : Scn._Container4Objects) {
    usleep(20000);
    ChangeState(Scn);
    Scn.MarkChange();
    usleep(100000);
  }
  usleep(100000);

  cout << "Close\n" << endl; // To tylko, aby pokazac wysylana instrukcje
  Send(Socket4Sending,"Close\n");
  ClientSender.CancelCountinueLooping();
  Thread4Sending.join();
  close(Socket4Sending); */

  return 0;
}
