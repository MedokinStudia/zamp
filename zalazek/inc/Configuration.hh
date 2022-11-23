#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH
#include "MobileObj.hh"

#include <map>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Configuration {

  map < string, MobileObj * > mapMobileObjects;
 
  vector < string > LibraryList;

  public:
    ~Configuration() {
      mapMobileObjects.clear();
    }

  void AddLibraryName(const string & LibraryName);
  void AddMobileObj(const string & ObjectName,
                    const Vector3D & Scale,
                    const string & RGB,
                    const Vector3D & Shift,
                    const Vector3D & RotXYZ,
                    const Vector3D & Trans);

  vector < string > & getLibraryList() {
    return this -> LibraryList;
  }
  
  map < string, MobileObj * > & getObjectList() {
    return this -> mapMobileObjects;
  }

};

#endif
