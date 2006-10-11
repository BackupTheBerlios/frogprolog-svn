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
#ifndef UTIPROLOGCPPFACTORY_H
#define UTIPROLOGCPPFACTORY_H

#include "enginefactory.h"

namespace UtiProlog {
namespace Cpp {
/**
@author Michael Staud
*/
class CppFactory : public UtiProlog::EngineFactory
{
   public:
      CppFactory();
      ~CppFactory();
      Body* createBody();
      BodyPart* createBodyPart();
      Fact* createFact();
      Goal* createGoal();
      IntNumber* createIntNumber();
      RealNumber* createRealNumber();
      Structure* createStructure();
      Var* createVar();
      Program* intern_createProgram();
      PID registerAtom(const char* t1);
      PID registerAtomW(const wchar_t* t1);
};
}
}

#endif
