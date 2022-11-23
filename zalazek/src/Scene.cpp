#include "../inc/Scene.hh"

Scene::Scene(){}

Scene::Scene(std::map < std::string, MobileObj * > & List): mapMobileObjects(List) {
  cout << "Stworzono scene z " <<mapMobileObjects.size() << " obiektami" << std::endl;
}

MobileObj * Scene::FindMobileObj(std::string sName) {
  std::map < std::string, MobileObj * > ::iterator Iter = this -> mapMobileObjects.find(sName);

  if (Iter == this -> mapMobileObjects.end()) return nullptr;

  else return Iter -> second;
}

void Scene::AddMobileObj(std::string sName) {
  MobileObj * pMobObj = new MobileObj;
  this -> mapMobileObjects.insert({
    sName,
    pMobObj
  });
}

vector < MobileObj * > Scene::getObjects() {
  std::vector < MobileObj * > result;
  std::map < std::string, MobileObj * > ::iterator Iter;

  for (Iter = mapMobileObjects.begin(); Iter != mapMobileObjects.end(); Iter++) {
    result.push_back(Iter -> second);
  }

  return result;
}