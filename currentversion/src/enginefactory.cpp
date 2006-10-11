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


#include "enginefactory.h"



#ifdef __BASEPREDICATES__
namespace UtiExternProlog {
#else

#include "wamfactory.h"
#include "cppfactory.h"
namespace UtiProlog {
#endif

EngineFactory* EngineFactory::factory = NULL;

EngineFactory::EngineFactory()
{
   
}

EngineFactory* EngineFactory::getInstance()
{
   if (factory == NULL) {
      char* c = getenv("FP_BACKEND");
#ifdef __BASEPREDICATES__
      factory = new EngineFactory();
      
#else 
     if (c == NULL || (strcmp(c, "CPP")==0)) {
   factory = new Cpp::CppFactory();
     } else if (strcmp(c, "WAM")==0) {
	factory = new WAM::WAMFactory();
     };
#endif
   };
   return factory;
};


EngineFactory::~EngineFactory()
{
}

Body* EngineFactory::createBody()
{
   return new Body();
}

BodyPart* EngineFactory::createBodyPart()
{
   return new BodyPart();
}

Fact* EngineFactory::createFact()
{
   return new Fact();
}

Goal* EngineFactory::createGoal()
{
   return new Goal();
}

IntNumber* EngineFactory::createIntNumber()
{
   return new IntNumber();
}


RealNumber* EngineFactory::createRealNumber()
{
   return new RealNumber();
}
Structure* EngineFactory::createStructure()
{
   return new Structure();
}
Var* EngineFactory::createVar()
{
   return new Var();
}

Rule* EngineFactory::createRule()
{
   return new Rule();
};
Program* EngineFactory::intern_createProgram()
{
   return new Program();
}
}
