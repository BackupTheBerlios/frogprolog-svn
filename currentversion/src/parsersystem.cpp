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
#include "parsersystem.h"
#include <cctype>
#include <iostream>
#include <fstream>
#include <cwchar>
#include "enginefactory.h"
#include "prolog_driver.h"

using namespace std;

#define SETPOS(f) \
   f->pos.beginline = currentpos.beginline;\
   f->pos.begincolumn = currentpos.begincolumn;\
   f->pos.endline = currentpos.endline;\
   f->pos.endcolumn = currentpos.endcolumn;\
   f->pos.beginfile = NULL;\
   f->pos.endfile = NULL;

#define EOL 10
//#define DB(a) a ; wcout << endl;
#define DB(a)

#ifdef __BASEPREDICATES__
namespace UtiExternProlog {
#else 
namespace UtiProlog {
#endif

ParserSystem::ParserSystem(prolog_driver* driv, wistream* is)
{
   ifstr = is;
   driver = driv;
   currentpos.beginline = 1;
   currentpos.begincolumn = 0;
   currentpos.endline = 1;
   currentpos.endcolumn = 0;
   nextCharacter();
   nextToken();
}

void ParserSystem::swapPos()
{
   currentpos.beginline = currentpos.endline;
   currentpos.begincolumn = currentpos.endcolumn;
};

void ParserSystem::nextCharacter()
{
   if (ifstr->eof() || (!ifstr->good())) {
      nextchar = -1;
      return;
   };
 //  nextchar = 0;
   //ifstr->read(&nextchar, 1);
   nextchar = ifstr->get();
   currentpos.endcolumn++;
   if (nextchar == EOL) {
      currentpos.endline++;
      currentpos.endcolumn = 0;
   };
}

void ParserSystem::clearBuffer()
{
   pos = 0;
}

void ParserSystem::putBuffer(wchar_t p)
{
   if (pos < 1024) {
      buffer[pos] = p;
      pos++;
   };
}

void ParserSystem::IntValue()
{
   buffer[pos] = 0;
   intvalue = wcstol(buffer, NULL, 10);

   type = tIntNum;
   DB(wcout << L"int(" << intvalue << "), ");
}

void ParserSystem::FloatValue()
{
   buffer[pos] = 0;
   realvalue = wcstod(buffer, NULL);
		
   type = tFloatNum;
   DB(wcout << L"float(" << realvalue << "), ");
}

void ParserSystem::AtomValue()
{
   buffer[pos] = 0;
   
   const wchar_t* c = buffer;
   if (wcscmp(c, L":-")==0) {
      type = tBeginBody;
      DB(wcout << L"':-', ");
      return;
   };
   id = EngineFactory::getInstance()->registerAtomW(buffer);
   type = tAtom;
   DB(wcout << L"atom(" << buffer << "), ");
}

void ParserSystem::VarValue()
{
   buffer[pos] = 0;
   id = EngineFactory::getInstance()->registerAtomW(buffer);
   type = tVar;
   DB(wcout << L"var(" << buffer<< "), ");
}

bool ParserSystem::isSpecialAtom(wchar_t c)
{
   switch (c) {
      case '+':
      case '-':
      case '*':
      case '/':
      case '\\':
      case '^':
      case '<':
      case '>':
      case '=':
      case '~':
      case ':':
      case '?':
      case '@':
      case '#':
      case '$':
	 case '&': return true;
      default: {
	 return false;
      }; break;
   };
}
wchar_t ParserSystem::peekcode()
{
   wchar_t ch = ifstr->get();
   ifstr->unget();
   return ch;
};

void ParserSystem::nextToken()
{
   swapPos();
   if (ifstr->eof() || (!ifstr->good())) {
      type = tEOF;
   } else if (isspace(nextchar)) {
      do {
	 nextCharacter();
      } while (isspace(nextchar));
      nextToken();
   } else if (isalpha(nextchar) && islower(nextchar)) {
      clearBuffer();
      do {
	 putBuffer(nextchar);
	 nextCharacter();
      } while (isalnum(nextchar) || nextchar == L'_');
      AtomValue();
   } else if (isalpha(nextchar) && isupper(nextchar)) {
      clearBuffer();
      do {
	 putBuffer(nextchar);
	 nextCharacter();
      } while (isalnum(nextchar) || nextchar == L'_');
      VarValue();
   } else if (isdigit(nextchar) || (nextchar == L'-' && isdigit(peekcode()))) {
      clearBuffer();
      do {
	 putBuffer(nextchar);
	 nextCharacter();	 
      } while (isdigit(nextchar));
      if (nextchar != L'.') {
	 IntValue();
      } else {
	 do {
	    putBuffer(nextchar);
	    nextCharacter();	 
	 } while (isdigit(nextchar));
	 FloatValue();
      };
   } else if (nextchar == L'%') {
      do {
	 nextCharacter();
      } while (nextchar != EOL && nextchar != -1);
      nextCharacter();
      nextToken();
   } else if (nextchar == L'/' && peekcode() == L'*') {
      do {
	 nextCharacter();
      } while (!(nextchar == L'*' && peekcode() == L'/'));
      nextCharacter();
      nextCharacter();
      nextToken();
   } else if (isSpecialAtom(nextchar)) {
      clearBuffer();
      do {
	 putBuffer(nextchar);
	 nextCharacter();
      } while (isSpecialAtom(nextchar));
      AtomValue();
   } else if (nextchar == L'(') {
      type = tKlammerAuf; nextCharacter();
      DB(wcout << L"'(',");
   } else if (nextchar == L')') {
      type = tKlammerZu; nextCharacter();
      DB(wcout << L"')',");
   } else if (nextchar == L'[') {
      type = tEckKlammerAuf; nextCharacter();
      if (nextchar == L']') {
	 clearBuffer();
	 putBuffer(L'[');
	 putBuffer(L']');
	 nextCharacter();
	 AtomValue();
      } else {
	 DB(wcout << L"'[',");
      };
   } else if (nextchar == L']') {
      type = tEckKlammerZu; nextCharacter();
      DB(wcout << L"']',");
   } else if (nextchar == L'{') {
      type = tGeschweifteKlammerAuf; nextCharacter();
      if (nextchar == L'}') {
	 clearBuffer();
	 putBuffer(L'{');
	 putBuffer(L'}');
	 nextCharacter();
	 AtomValue();
      } else {
	 DB(wcout << L"'{',");
      };
   } else if (nextchar == L'}') {
      type = tGeschweifteKlammerZu; nextCharacter();
      DB(wcout << L"'}',");
   } else if (nextchar == L',') {
      type = tKomma; nextCharacter();
      DB(wcout << L"',',");
   } else if (nextchar == L';') {
      type = tStrichpunkt; nextCharacter();
      DB(wcout << L"';',");
   } else if (nextchar == L'|') {
      type = tStrich; nextCharacter();
      DB(wcout << L"'|',");
   } else if (nextchar == L'.') {
      type = tDot; nextCharacter();
      DB(wcout << L"'.',");
   } else if (nextchar == L'_') {
      nextCharacter();
      clearBuffer();
      putBuffer(L'_');
      VarValue();
   } else if (nextchar == L'!') {
      nextCharacter();
      clearBuffer();
      putBuffer(L'!');
      AtomValue();
   } else if (nextchar == L'\'') {
      nextCharacter();
      clearBuffer();
      while ((nextchar != L'\'') && (nextchar != -1)) {
	 putBuffer(nextchar);
	 if (nextchar == EOL) {
	    std::wstring str3 = L"Umbruch in String";
	    driver->error(&currentpos, str3.c_str());
	    break;
	 };
	 nextCharacter();
      };
      nextCharacter();
      AtomValue();
   } else if (nextchar == L'\"') {
      nextCharacter();
      clearBuffer();
      while ((nextchar != L'\"') && (nextchar != -1)) {
	 putBuffer(nextchar);
	 if (nextchar == EOL) {
	    std::wstring str3 = L"Umbruch in String";
	    driver->error(&currentpos, str3.c_str());
	    break;
	 };
	 nextCharacter();
      };
      nextCharacter();
      type = tStringList;
   } else {
      std::wstring str3 = L"Illegales Zeichen: ";
      clearBuffer();
      putBuffer(nextchar);
      putBuffer(0);
      str3 += buffer;
      int v = buffer[0];
      wchar_t c[30];
      swprintf(c, 30, L"(%i)/(0x%x)", v);
      str3 += c;
      driver->error(&currentpos, str3.c_str());
      //nextCharacter();
      //nextToken();
      type = tNone;
   };
   
}

ParserSystem::~ParserSystem()
{
}

void ParserSystem::pMatch(TToken t)
{
   if (t==type) {
      nextToken();
   } else {
      pError(tokenToStr(t));
   };
}

void ParserSystem::pMatchAtom(wchar_t* t)
{
   if (type == tAtom && id == getID(t)) {
      nextToken();
   } else {
      pError(t);
   };
}

wchar_t* ParserSystem::tokenToStr(TToken t)
{
   switch (t) {
      case tEOF:
	 return L"EOF";
      case tIntNum:
	 return L"<INT>";
      case tFloatNum:
	 return L"<REAL>";
      case tBeginBody:
	 return L"':-'";
      case tAtom:
	 return L"<ATOM>";
      case tVar:
	 return L"<VAR>";
      case tKlammerAuf:
	 return L"'('";
      case tKlammerZu:
	 return L"')'";
	 
      case tEckKlammerAuf:
	 return L"'['";
      case tEckKlammerZu:
	 return L"']'";
      case tGeschweifteKlammerAuf:
	 return L"'{'";
      case tGeschweifteKlammerZu:
	 return L"'}'";
      case tKomma:
	 return L"','";
      case tStrichpunkt:
	 return L"';'";
      case tStrich:
	 return L"'|'";
      case tDot:
	 return L"'.'";
      case tStringList:
	 return L"'<BLA_BLA>'";

   };
};

PID ParserSystem::getID(wchar_t* t)
{
   return EngineFactory::getInstance()->registerAtomW(t);
}

bool ParserSystem::isNextAtom(wchar_t* t)
{
   if (type == tAtom && id == getID(t)) {
      return true;
   } else {
      return false;
   };
}

bool ParserSystem::isNextToken(TToken t)
{
   if (type == t) {
      return true;
   } else {
      return false;
   };
}

void ParserSystem::pError(wchar_t* expected)
{
   std::wstring str3 = L"Erwartet: ";
   str3 += expected;
   driver->error(&currentpos, str3.c_str());
   throw new ParserException();
};

void ParserSystem::pProgram()
{
   
   try {
      while (!isNextToken(tEOF)) {
	 Fact* f = pFact(); pMatch(tDot);
	 
	 Program::getInstance()->addElement(f);
      };
   } catch (ParserException* e)  {
      wcout << L"Fehler";
   };
}

Term* ParserSystem::pSTerm()
{
   Term* t = pTerm();
   //pMatch(tDot);
   
   return t;
}

Fact* ParserSystem::pFact()
{
   Fact* fact = EngineFactory::getInstance()->createFact();
   SETPOS(fact);
   bool parsed = false;
   if (!isNextToken(tBeginBody)) {
      Term* t = pOpPredicate();
      Structure* str = dynamic_cast<Structure*>(t);
      if (str == NULL) {
	 pError(L"Struktur erwartet");
      };
      fact->setHead(str);
      parsed = true;
   }
   if (isNextToken(tBeginBody)) {
      pMatch(tBeginBody);
      fact->setBody(pBody());
      parsed = true;
      return fact;
   }
   if (!parsed) {
      pMatch(tAtom);
   };
   return fact;
}

Structure* ParserSystem::pPredicate()
{
   Structure* structure = EngineFactory::getInstance()->createStructure();
   SETPOS(structure);
   if (!isNextToken(tKlammerAuf)) {
      structure->setName(pFunctor());
   } else {
      structure->setName(getID(L""));
   };
   if (isNextToken(tKlammerAuf)) {
      pMatch(tKlammerAuf);
      structure->addElement(pOpPredicate());
      while (isNextToken(tKomma)) {
	 pMatch(tKomma);
	 structure->addElement(pOpPredicate());
      };
      pMatch(tKlammerZu);
   };
   return structure;
}

TOp2Type ParserSystem::is2OP(OperatorLevel* lev, PID &name)
{
   if (type != tAtom) return op2None;
   if (lev->obinfo.find(id) == lev->obinfo.end()) {
      return op2None;
   };
   OperatorInfo& info = lev->obinfo[id];
   name = id;
   if (info.XFX) return op2XFX;
   if (info.YFX) return op2YFX;
   if (info.XFY) return op2XFX;
   return op2None;
};

Term* ParserSystem::pOpPredicate()
{
   
   return pOpLevel(Program::getInstance()->getLevelCount()-1);
};


Term* ParserSystem::pOpOperator(OperatorLevel* lev, int level)
{
   if (!lev) {
      return pOpLevel(level);
   };
   Term* resstructure = NULL;
   Term* topterm = NULL;
   map<PID, OperatorInfo>::iterator it;
   while (type == tAtom && ((it = lev->obinfo.find(id)) != lev->obinfo.end()) && 
          (it->second.FX || it->second.FY)) {
     // if (resstructure) {
         Structure* ns = EngineFactory::getInstance()->createStructure();
         ns->setName(id);
         if (resstructure)
            ((Structure*) resstructure)->addElement(ns);
         resstructure = ns;
         if (!topterm) topterm = resstructure;
      
      pMatch(tAtom);
      if (it->second.FX) break;
   };
   
   Term* resterm= pOpLevel(level);
   
   while (type == tAtom && ((it = (lev->obinfo.find(id))) != lev->obinfo.end()) && 
          (it->second.XF || it->second.YF)) {
     // if (resstructure) {
      Structure* ns = EngineFactory::getInstance()->createStructure();
      ns->setName(id);
      if (resstructure)
         ((Structure*) resstructure)->addElement(ns);
      resstructure = ns;
      if (!topterm) topterm = resstructure;
      
      pMatch(tAtom);
      if (it->second.XF) break;
          };
   
   if (resstructure == NULL) {
      resstructure = resterm;
      topterm = resterm;
   } else {
      ((Structure*) resstructure)->addElement(resterm);
   };
   return topterm;
};

 Term* ParserSystem::pOpLevel(int level)
{
   if (level == -1) {
      return pTerm();
   };
   OperatorLevel* lev = (OperatorLevel*)Program::getInstance()->levels[level];
   /*PID name;
   if (isFX(lev, name)) {
      return makeOP(name, pOpLevel(level-1));
      
};*/
   Term* a;
   Term* b;
   PID name;
   a= pOpOperator(lev, level-1);
   TOp2Type t = is2OP(lev, name);
   if (t == op2None) return a;
   Structure* topinsert = NULL;
   Structure* bottominsert = NULL;
   TOp2Type last=t;
   do {
      Structure* str = EngineFactory::getInstance()->createStructure();
      str->setName(name);
      SETPOS(str);
      pMatch(tAtom);
      b = pOpOperator(lev, level-1);
      //str->addElement(a);
      //str->addElement(b);
      if (t != last) pError(L"Mixing of Precedence");
      switch (t) {
	 case op2XFY: {
	    if (bottominsert == NULL) {
	       str->addElement(a);
	       
	    } else {
	       a = bottominsert->getElement(1);
	       bottominsert->setElement(1, str);
	       str->addElement(a);
	    };
	    bottominsert = str;
	    if (topinsert == NULL) topinsert = str;
	 }; break;
	 case op2YFX: {
	    if (topinsert == NULL) {
	       str->addElement(a);
	    } else {
	       str->addElement(topinsert);
	    };
	    topinsert = str;
	 };break;
	 case op2XFX: {
	    if (topinsert == NULL && bottominsert == NULL) {
	       str->addElement(a);
	       topinsert = str;
	       bottominsert = str;
	    } else {
	       pError(L"Operator clash");
	    };
	 };break;
      };
      str->addElement(b);
      if (t == op2XFX) break;
   } while ((t = is2OP(lev, name)) != op2None);
   return topinsert;
};

Body* ParserSystem::pBody()
{
   Body* body = EngineFactory::getInstance()->createBody();
   SETPOS(body);
   body->addElement(pBodyPart());
   while (isNextToken(tStrichpunkt)) {
      pMatch(tStrichpunkt);
      body->addElement(pBodyPart());
   };
   return body;
}

BodyPart* ParserSystem::pBodyPart()
{
   BodyPart* part = EngineFactory::getInstance()->createBodyPart();
   SETPOS(part);
   pGoal(part);
 //  part->addElement(pGoal());
   while (isNextToken(tKomma)) {
      pMatch(tKomma);
      pGoal(part);
     // part->addElement(pGoal());
   };
   return part;
}
Goal* ParserSystem::pGoal(BodyPart* bpart)
{
   Goal* goal = EngineFactory::getInstance()->createGoal();
   SETPOS(goal);
   if (isNextToken(tKlammerAuf)) {
      pMatch(tKlammerAuf);
      
      Body* b = pBody();
      pMatch(tKlammerZu);
      if (b->elementCount() == 1 && bpart != NULL) {
          delete goal;
          BodyPart* bp = b->getElement(0);
          for (int i = 0; i < bp->elementCount(); i++) {
             bpart->addElement(bp->getElement(i));
          };
          return NULL;
      } else {
         goal->setGoal(gBody);
         goal->setElement(b);
      };
      
   } else if (isNextAtom(L"\\+")) {
      pMatchAtom(L"\\+");
      goal->setGoal(gNotBody);
      goal->setElement(pGoal(NULL));
   } else if (isNextAtom(L"not")) {
      pMatchAtom(L"not");
      pMatch(tKlammerAuf);
      goal->setGoal(gNotBody);
      goal->setElement(pGoal(NULL));
      pMatch(tKlammerZu);
   } else {
      goal->setGoal(gTerm);
      goal->setElement(pOpPredicate());
   };
   if (bpart) bpart->addElement(goal);
   return goal;
}
PID ParserSystem::pFunctor()
{
   PID r = id;
   pMatch(tAtom);
   return r;
}
Term* ParserSystem::pTerm()
{
   switch (type) {
      case tKlammerAuf:
      case tAtom: {
	 return pPredicate();
      };break;
      case tVar: {
	 return pVar();
      };break;
      case tIntNum: {
	 return pIntNumber();
      };break;
      case tFloatNum: {
	 return pRealNumber();
      };break;
      case tEckKlammerAuf: {
	 return pList();
      };break;
      case tGeschweifteKlammerAuf: {
	 return pBrace();
      };break;
      case tStringList: {
	 return pStringList();
      };break;
      default: {
	 pError(L"'<ATOM>, <VAR>, <INT>, <REAL>, '[', '<BLABLA>'");
	 return NULL;
      };
   };
}
Term* ParserSystem::pVar()
{
   Var* var = EngineFactory::getInstance()->createVar();
   SETPOS(var);
   var->setName(id);
   pMatch(tVar);
   return var;
}
Term* ParserSystem::pIntNumber()
{
   IntNumber* integer = EngineFactory::getInstance()->createIntNumber();
   SETPOS(integer);
   integer->setValue(intvalue);
   pMatch(tIntNum);
   return integer;
}
Term* ParserSystem::pRealNumber()
{
   RealNumber* real = EngineFactory::getInstance()->createRealNumber();
   SETPOS(real);
   real->setValue(realvalue);
   pMatch(tFloatNum);
   return real;
}
Term* ParserSystem::pList()
{
   pMatch(tEckKlammerAuf);
   Structure* res=NULL;
   Term* first=NULL;
   bool f= true;
   while (!(isNextToken(tEckKlammerZu) || isNextToken(tStrich))) {
      if (!f) pMatch(tKomma);
	f = false;
      Term* t = pTerm();
      Structure* structure = EngineFactory::getInstance()->createStructure();
      SETPOS(structure);
      structure->setName(EngineFactory::getInstance()->registerAtomW(L"."));
      structure->addElement(t);
      if (res) {
	 res->addElement(structure);
      } else {
	 first = structure;
      }
      res = structure;
   };
   if (!isNextToken(tStrich)) {
      Structure* structure = EngineFactory::getInstance()->createStructure();
      SETPOS(structure);
      structure->setName(EngineFactory::getInstance()->registerAtomW(L"[]"));
      if (res) {
         res->addElement(structure);
      } else {
         first = structure;
      }
      res = structure;
   } else {
      pMatch(tStrich);
      Term* structure = pTerm();
      SETPOS(structure);
      if (res) {
	 res->addElement(structure);
      } else {
	 first = structure;
      }
      //res = structure;
   };
   pMatch(tEckKlammerZu);
   return first;
}

Term* ParserSystem::pBrace()
{
   pMatch(tGeschweifteKlammerAuf);
   
   Structure* structure = EngineFactory::getInstance()->createStructure();
   SETPOS(structure);
   structure->setName(EngineFactory::getInstance()->registerAtomW(L"{}"));
   structure->addElement(pTerm());
   while (isNextToken(tKomma)) {
      pMatch(tKomma);
      structure->addElement(pTerm());
   };
   pMatch(tGeschweifteKlammerZu);
};

Term* ParserSystem::pStringList()
{
   buffer[pos]=0;
   wchar_t* c = buffer;
   PID dot = EngineFactory::getInstance()->registerAtomW(L".");
   PID emptylist = EngineFactory::getInstance()->registerAtomW(L"[]");
   Structure* lastelement = NULL;
   int length = wcslen(c);
   Structure* r_struct;
   if (length == 0) {
      Structure* structure;
      r_struct= EngineFactory::getInstance()->createStructure();
      SETPOS(r_struct);
      structure = r_struct;
      structure->setName(emptylist);
   } else {
      Structure* structure;
      r_struct = EngineFactory::getInstance()->createStructure();
      SETPOS(r_struct);
      structure = r_struct;
      IntNumber* intvalue = EngineFactory::getInstance()->createIntNumber();
      SETPOS(intvalue);
      intvalue->setValue(c[0]);
      structure->addElement(intvalue);
      
      structure->setName(dot);
      lastelement=r_struct;
      for (int i = 1; i < length; i++) {
	 structure = EngineFactory::getInstance()->createStructure();
	 SETPOS(structure);
	 intvalue = EngineFactory::getInstance()->createIntNumber();
	 SETPOS(intvalue);
	 intvalue->setValue(c[i]);
	 structure->addElement(intvalue);
	 structure->setName(dot);
	 lastelement->addElement(structure);
	 lastelement = structure;
      };
      structure = EngineFactory::getInstance()->createStructure();
      SETPOS(structure);
      structure->setName(emptylist);
      lastelement->addElement(structure);
   };
   
   return r_struct;
   
}


}
