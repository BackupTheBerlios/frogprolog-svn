/***************************************************************************
 *   Copyright (C) 2006 by Michael Staud   *
 *   michael.staud@uni-ulm.de   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "cppbuildin.h"
#include "cpphelper.h"
#include "cppengine.h"

namespace UtiProlog
{
namespace Cpp {
  namespace BuildIn
  {

    class CutPred : public BaseBuildInPredicate
    {
    public:
      int getArity()
      {
        return 0;
      };
      CUtiString getName()
      {
        return L"!";
      };
      void performCode(BaseTarget*t, Structure* s)
      {
        oout << L"pl_cut();";
        oout_newline();
      };
    };

    class FailPred : public BaseBuildInPredicate
    {
    public:
      int getArity()         { return 0;    };
      CUtiString getName()   { return L"fail"; };
      void performCode(BaseTarget*t, Structure* s)
      {
        oout << L"pl_DoBacktracking();	 break;";
        oout_newline();
      };
    };

    class FalsePred : public FailPred
    {
    public:
      CUtiString getName()   { return L"false"; };
    };

    class TruePred : public BaseBuildInPredicate
    {
    public:
      CUtiString getName()   { return L"true"; };
    };
  };

  void RegisterCppBuildIn(Program* p)
  {
    p->RegisterPredicate(new BuildIn::CutPred());
    p->RegisterPredicate(new BuildIn::FailPred());
    p->RegisterPredicate(new BuildIn::FalsePred());
    p->RegisterPredicate(new BuildIn::TruePred());
  }
  
};
};
