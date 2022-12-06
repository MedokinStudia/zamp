#include <iostream>
#include "Interp4Move.hh"
#include "MobileObj.hh"
#include "unistd.h"

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Move"; }
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Move::CreateCmd();
}


/*!
 *
 */
Interp4Move::Interp4Move(): _Obj_name(""), _Speed_mmS(0),  _Distance_m(0)
{}


/*!
 *
 */
void Interp4Move::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _Obj_name << " " <<  _Speed_mmS  << " " << _Distance_m  << endl;
}


/*!
 *
 */
const char* Interp4Move::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Move::ExecCmd( MobileObj  *pMobObj,  AccessControl *pAccessCtrl) const
{
  int direction = this->_Speed_mmS > 0 ? 1 : -1; //jezeli predkosc ujemna to kierunek ujemny
  int iterations = std::floor(this->_Distance_m/this->_Speed_mmS);

  for (int i = 0; i < iterations; ++i)
  {
    pAccessCtrl->LockAccess();
    Vector3D position = pMobObj->GetPositoin_m();
    double angleX = pMobObj->GetAng_Roll_deg();
    double angleY = pMobObj->GetAng_Pitch_deg();
    double angleZ = pMobObj->GetAng_Yaw_deg();
    
    //position[0] += this->_Speed_mmS * direction * cos(M_PI * angle/180);
    //position[1] += this->_Speed_mmS * direction * sin(M_PI * angle/180);
    position[0] += this->_Speed_mmS * direction * (cos(M_PI * angleY/180) * cos(M_PI * angleZ/180));
    position[1] += this->_Speed_mmS * direction * (sin(M_PI * angleX/180) * sin(M_PI * angleZ/180) + cos(M_PI * angleZ/180) * sin(M_PI * angleY/180) * cos(M_PI * angleX/180));
    position[2] += this->_Speed_mmS * direction * (sin(M_PI * angleX/180) * sin(M_PI * angleZ/180) - cos(M_PI * angleX/180) * cos(M_PI * angleZ/180) * sin(M_PI * angleY/180));
    
    pMobObj->SetPosition_m(position);
    pAccessCtrl->MarkChange();
    pAccessCtrl->UnlockAccess();
    usleep(100000);

  }
  cout<<"Move DONE "<<endl;
  return true;
}


/*!
 *
 */
bool Interp4Move::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList>> _Speed_mmS >> _Distance_m;
  return !Strm_CmdsList.fail();
}


/*!
 *
 */
Interp4Command* Interp4Move::CreateCmd()
{
  return new Interp4Move();
}


/*!
 *
 */
void Interp4Move::PrintSyntax() const
{
  cout << "   Move  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << endl;
}
