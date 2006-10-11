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
#include "cppfactory.h"
#include "cppengine.h"

namespace UtiProlog {
namespace Cpp {
CppFactory::CppFactory()
   : EngineFactory()
   {
   }


   CppFactory::~CppFactory()
   {
   }

   Body* CppFactory::createBody()
   {
      return new CppBody();
   }

   BodyPart* CppFactory::createBodyPart()
   {
      return new CppBodyPart();
   }

   Fact* CppFactory::createFact()
   {
      return new CppFact();
   }

   Goal* CppFactory::createGoal()
   {
      return new CppGoal();
   }

   IntNumber* CppFactory::createIntNumber()
   {
      return new CppIntNumber();
   }

   RealNumber* CppFactory::createRealNumber()
   {
      return new CppRealNumber();
   }
   Structure* CppFactory::createStructure()
   {
      return new CppStructure();
   }
   Var* CppFactory::createVar()
   {
      return new CppVar();
   }
   Program* CppFactory::intern_createProgram()
   {
      return new CppProgram();
   }
   PID CppFactory::registerAtom(const char* t1)
   {
      return UtiProlog::idbase.identifierToID(t1);
   }
   PID CppFactory::registerAtomW(const wchar_t* t1)
   {
      return UtiProlog::idbase.identifierToID(t1);
   }

};
}
