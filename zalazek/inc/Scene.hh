#ifndef  SCENE_HH
#define  SCENE_HH

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "MobileObj.hh"

using namespace std;

class Scene{
private:

map <string,MobileObj*> mapMobileObjects;
public:
Scene();
Scene(map < string, MobileObj * > & List);
~Scene(){
    mapMobileObjects.clear();
}


MobileObj* FindMobileObj(string sName);
void AddMobileObj(string sName);

map <string,
MobileObj * > getObjList() {
return this -> mapMobileObjects;
}
vector < MobileObj * > getObjects();

};
#endif