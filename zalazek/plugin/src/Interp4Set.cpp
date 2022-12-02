#include <iostream>
#include "Interp4Set.hh"
#include "MobileObj.hh"
#include "unistd.h"
using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Set"; }
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Set::CreateCmd();
}


/*!
 *
 */
Interp4Set::Interp4Set(): _Xposition(0), _Yposition(0), _Kat_Ox(0),_Kat_Oy(0),_Kat_Oz(0)
{}


/*!
 *
 */
void Interp4Set::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _Obj_name << " " <<  _Xposition << " " << _Yposition << " "  << _Kat_Ox << " "  << _Kat_Oy << " "  << _Kat_Oz << " "  << endl;
}


/*!
 *
 */
const char* Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Set::ExecCmd( MobileObj  *pMobObj,  AccessControl *pAccessCtrl) const
{
  Vector3D new_position = pMobObj->GetPositoin_m();
  new_position[0] = this->_Xposition;
  new_position[1] = this->_Yposition;
  pMobObj->SetPosition_m(new_position);

  pMobObj->SetAng_Roll_deg(this->_Kat_Ox);
  pMobObj->SetAng_Pitch_deg(this->_Kat_Oy);
  pMobObj->SetAng_Yaw_deg(this->_Kat_Oz);
  usleep(300000);
  return true;
}


/*!
 *
 */
bool Interp4Set::ReadParams(std::istream& Strm_CmdsList)
{
    if(!(Strm_CmdsList >> _Obj_name))
    {
        std::cout << "Blad nazwy"<< endl;
        return 1;
    }

    if(!(Strm_CmdsList >> _Xposition))
    {
        std::cout << "Blad WspX"<< endl;
        return 1;
    }

    if(!(Strm_CmdsList >> _Yposition))
    {
        std::cout << "Blad Wspy"<< endl;
        return 1;
    }

    if(!(Strm_CmdsList >> _Kat_Ox))
    {
        std::cout << "Blad kata Ox"<< endl;
        return 1;
    }
    
    if(!(Strm_CmdsList >> _Kat_Oy))
    {
        std::cout << "Blad kata Oy"<< endl;
        return 1;
    }

    if(!(Strm_CmdsList >> _Kat_Oz))
    {
        std::cout << "Blad kata Oz"<< endl;
        return 1;
    }


  return true;
}


/*!
 *
 */
Interp4Command* Interp4Set::CreateCmd()
{
  return new Interp4Set();
}


/*!
 *
 */
void Interp4Set::PrintSyntax() const
{
  cout << "   Set  NazwaObiektu  WspX WspY KatOZ[o]" << endl;
}
