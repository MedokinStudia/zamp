#ifndef  SCENE_HH
#define  SCENE_HH

#include <map>
#include <memory>
#include <string>

#include <MobileObj.hh>

using namespace std;

class Scene{
private:

map <string, shared_ptr<MobileObj>> _mapMobileObjects;

public:
    MobileObj* FindMobileObj(const char *sName);
    void AddMobileObj(MobileObj *pMobObj);
};
#endif