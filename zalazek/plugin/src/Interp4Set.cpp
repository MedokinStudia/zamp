#include <iostream>
#include "Interp4Set.hh"
#include "MobileObj.hh"

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
Interp4Set::Interp4Set(): _Xposition(0), _Yposition(0), _DegreeozO(0)
{}


/*!
 *
 */
void Interp4Set::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _Obj_name << " " <<  _Xposition << " " << _Yposition << " " << _DegreeozO << endl;
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
bool Interp4Set::ExecCmd( MobileObj  *pMobObj,  int  Socket) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
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

    if(!(Strm_CmdsList >> _DegreeozO))
    {
        std::cout << "Blad kata"<< endl;
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
