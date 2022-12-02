#include <iostream>
#include "Interp4Rotate.hh"
#include "MobileObj.hh"
#include "unistd.h"

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Rotate"; }
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Rotate::CreateCmd();
}


/*!
 *
 */
Interp4Rotate::Interp4Rotate(): _Angular_speedoS(0), _DegreeO(0), _Axis_Name("")
{}


/*!
 *
 */
void Interp4Rotate::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _Obj_name << " " << _Angular_speedoS <<" " <<_Axis_Name<<" " << _DegreeO << endl;
}


/*!
 *
 */
const char* Interp4Rotate::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Rotate::ExecCmd( MobileObj  *pMobObj,  AccessControl *pAccessCtrl) const
{
  double progress;
  char axis = this->_Axis_Name.at(0);

  switch (axis)
  {
  case 'X':
    progress = pMobObj->GetAng_Roll_deg();
    break;

  case 'Y':
    progress = pMobObj->GetAng_Pitch_deg();
    break;

  case 'Z':
    progress = pMobObj->GetAng_Yaw_deg();
    break;
  }

  int direction = this->_Angular_speedoS > 0 ? 1 : -1;
  double setpoint = progress + this->_DegreeO* direction;

  while (setpoint != progress)
  {
    //std::cout<<"beforeLockAccess"<<std::endl;
    pAccessCtrl->LockAccess();
    //std::cout<<"afterLockAccess"<<std::endl;
    progress += this->_Angular_speedoS;

    if (direction == 1)
    {
      if (progress > setpoint)
      {
        progress = setpoint;
      }
    }
    else
    {
      if (progress < setpoint)
      {
        progress = setpoint;
      }
    }

    switch (axis)
    {
    case 'X':
      pMobObj->SetAng_Roll_deg(progress);
      break;

    case 'Y':
      pMobObj->SetAng_Pitch_deg(progress);
      break;

    case 'Z':
      pMobObj->SetAng_Yaw_deg(progress);
      break;
    }
    //std::cout<<"jestem pprzed markchange"<<std::endl;
    pAccessCtrl->MarkChange();
    //std::cout<<"jestem pprzed uACWCESe"<<std::endl;
    pAccessCtrl->UnlockAccess();
    //std::cout<<"witfi"<<std::endl;
    usleep(100000);
  }
  std::cout<<"Rotate Done "<<endl;
  return true;
}


/*!
 *
 */
bool Interp4Rotate::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList >>_Angular_speedoS >> _Axis_Name >> _DegreeO;
  return !Strm_CmdsList.fail();

  return true;
}


/*!
 *
 */
Interp4Command* Interp4Rotate::CreateCmd()
{
  return new Interp4Rotate();
}


/*!
 *
 */
void Interp4Rotate::PrintSyntax() const
{
  cout << "   Rotate  NazwaObiektu  SzybkoscKatowa[o/s]  KatObrotu[o]" << endl;
}
