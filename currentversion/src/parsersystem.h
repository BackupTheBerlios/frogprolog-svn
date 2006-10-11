/***************************************************************************
 *   Copyright (C) 2006 by Michael Staud   *
 *   ms73@informatik.uni-ulm.de   *
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
#ifndef PARSERPARSERSYSTEM_H
#define PARSERPARSERSYSTEM_H
#include "identifierdatabase.h"

#include <iostream>

#ifdef __BASEPREDICATES__
#include "externparser.h"
using namespace UtiExternProlog;
#else
#include "prologengine.h"
using namespace UtiProlog;
#endif


using namespace std;

class prolog_driver;

#ifdef __BASEPREDICATES__
namespace UtiExternProlog {
#else 
namespace UtiProlog {
#endif

enum TToken {tNone,tEOF, tIntNum, tFloatNum, tBeginBody, tAtom, tVar, tKlammerAuf, tKlammerZu, tEckKlammerAuf, tEckKlammerZu, tGeschweifteKlammerAuf, tGeschweifteKlammerZu, tKomma, tStrichpunkt, tStrich, tDot, tStringList};

enum TOp2Type {op2None, op2XFY, op2YFX, op2XFX};

struct PositionInfo {
   int beginline;
   int begincolumn;
   int endline;
   int endcolumn;
};

class ParserException {
   
};

/**
@author Michael Staud
*/
class ParserSystem{
public:
   void IntValue();
   void FloatValue();
   void AtomValue();
   void VarValue();
   bool isSpecialAtom(wchar_t c);
public:
   PositionInfo currentpos;
   TToken type;
   PID id;
   int intvalue;
   double realvalue;
   wchar_t nextchar;
   wistream* ifstr;
   wchar_t buffer[1024];
   int pos;
   void swapPos();
   void clearBuffer();
   void putBuffer(wchar_t p);
   void nextToken();
   wchar_t peekcode();
   void nextCharacter();
   prolog_driver* driver;
   ParserSystem(prolog_driver* driv, wistream* is);
    ~ParserSystem();
   
public:
   //Parser
   TOp2Type is2OP(OperatorLevel* lev, PID &name);
   Term* pOpOperator(OperatorLevel* lev , int level);
   PID getID(wchar_t* t);
   wchar_t* tokenToStr(TToken t);
   void pMatch(TToken t);
   void pMatchAtom(wchar_t* t);
   bool isNextAtom(wchar_t* t);
   bool isNextToken(TToken t);
   void pError(wchar_t* expected);
   void pProgram();
   Term* pSTerm();
   Fact* pFact();
   Structure* pPredicate();
   Term* pOpPredicate();
   Term* pOpLevel(int level);
   Body* pBody();
   BodyPart* pBodyPart();
   Goal* pGoal(BodyPart* bpart);
   PID pFunctor();
   Term* pTerm();
   Term* pVar();
   Term* pIntNumber();
   Term* pRealNumber();
   Term* pList();
   Term* pBrace();
   Term* pStringList();
};

}

#endif
