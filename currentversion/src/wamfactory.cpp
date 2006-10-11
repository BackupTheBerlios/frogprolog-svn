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
#include "wamfactory.h"
#include "wamengine.h"

namespace UtiProlog {
namespace WAM {
//WAMEngine
WAMFactory::WAMFactory()
   : EngineFactory()
   {
   }


   WAMFactory::~WAMFactory()
   {
   }

   Body* WAMFactory::createBody()
   {
      return new WAMBody();
   }

   BodyPart* WAMFactory::createBodyPart()
   {
      return new WAMBodyPart();
   }

   Fact* WAMFactory::createFact()
   {
      return new WAMFact();
   }

   Goal* WAMFactory::createGoal()
   {
      return new WAMGoal();
   }

   IntNumber* WAMFactory::createIntNumber()
   {
      return new WAMIntNumber();
   }

   RealNumber* WAMFactory::createRealNumber()
   {
      return new WAMRealNumber();
   }
   Structure* WAMFactory::createStructure()
   {
      return new WAMStructure();
   }
   Var* WAMFactory::createVar()
   {
      return new WAMVar();
   }
   PID WAMFactory::registerAtom(const char* t1)
   {
      return UtiProlog::idbase.identifierToID(t1);
   }
   PID WAMFactory::registerAtomW(const wchar_t* t1)
   {
      return UtiProlog::idbase.identifierToID(t1);
   }
   Program* WAMFactory::intern_createProgram()
   {
      return new WAMProgram();
   }

}
}
