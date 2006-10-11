//
// C++ Implementation: externparser
//
// Description:
//
//
// Author: Michael Staud <staud@linux>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "externparser.h"
#include "enginefactory.h"
#include "prolognames.h"
#include <algorithm>

using namespace PrologSystem;

namespace UtiExternProlog {

//Program* prog;

void BodyPart::clearElements() {
    for (int i = 0; i < elements.size(); i++)
        delete elements[i];
    elements.clear();
};

int BodyPart::elementCount() {

    return elements.size();
};

Rule::Rule() {
	guard = NULL;
	body = NULL;
	//head.deleteItems = true;
};

Rule::~Rule() {
	if (guard)
		delete guard;
	if (body)
		delete body;
	for (int i = 0; i < head.size(); i++)
		delete head[i];
};

void Program::addRule(Rule* f)
{
	delete f;
};

void Program::addElement(Fact* t) {
    elements.push_back(t);
};

void Program::clearElements() {
    for (int i = 0; i < elements.size(); i++)
        delete elements[i];
    elements.clear();
};

void Body::clearElements() {
    for (int i = 0; i < elements.size(); i++)
        delete elements[i];
    elements.clear();
};

BaseEngine::BaseEngine() {
}
;
BaseEngine::~BaseEngine() {
}
;

Term::Term() {
}
;
Term::~Term() {
}
;

Var::Var() {
   name = 0;
}
;
Var::~Var() {
}
;

IntNumber::IntNumber() {
   value = 0;
}
;
IntNumber::~IntNumber() {
}
;


RealNumber::RealNumber() {
   value = 0;
}
;
RealNumber::~RealNumber() {
}
;

Structure::Structure() {
   name = 0;
}
;
Structure::~Structure() {
   clearElements();
}
;

Body::Body() {
}
;
Body::~Body() {
   clearElements();
}
;

BodyPart::BodyPart() {
}
;
BodyPart::~BodyPart() {
   clearElements();
}
;

Goal::Goal() {
}
;
Goal::~Goal() {
   delete bengine;
}
;


Fact::Fact() {
}
;
Fact::~Fact() {
   delete head;
   delete body;
}
;

Program::Program() {
	haserror = false;
    
	addOperator(700, opXFX, pl_nameToId(L"="));
	addOperator(700, opXFX, pl_nameToId(L"<"));
	addOperator(700, opXFX, pl_nameToId(L"=.."));
	addOperator(700, opXFX, pl_nameToId(L"=@="));
	addOperator(700, opXFX, pl_nameToId(L"=:="));
	addOperator(700, opXFX, pl_nameToId(L"=<"));
	addOperator(700, opXFX, pl_nameToId(L"=="));
	addOperator(700, opXFX, pl_nameToId(L"=\\="));
	addOperator(700, opXFX, pl_nameToId(L">"));
	addOperator(700, opXFX, pl_nameToId(L">="));
	addOperator(700, opXFX, pl_nameToId(L"@<"));
	addOperator(700, opXFX, pl_nameToId(L"@=<"));
	addOperator(700, opXFX, pl_nameToId(L"@>"));
	addOperator(700, opXFX, pl_nameToId(L"@>="));
	addOperator(700, opXFX, pl_nameToId(L"\\="));
	addOperator(700, opXFX, pl_nameToId(L"\\=="));
	addOperator(700, opXFX, pl_nameToId(L"is"));
	addOperator(600, opXFY, pl_nameToId(L":"));
	addOperator(500, opYFX, pl_nameToId(L"+"));
	addOperator(500, opYFX, pl_nameToId(L"-"));
	addOperator(500, opYFX, pl_nameToId(L"/\\"));
	addOperator(500, opYFX, pl_nameToId(L"\\/"));
	addOperator(500, opYFX, pl_nameToId(L"xor"));
	addOperator(500, opFX, pl_nameToId(L"+"));
	addOperator(500, opFX, pl_nameToId(L"-"));
	addOperator(500, opFX, pl_nameToId(L"?"));
	addOperator(500, opFX, pl_nameToId(L"\\"));
	addOperator(400, opYFX, pl_nameToId(L"*"));
	addOperator(400, opYFX, pl_nameToId(L"/"));
	addOperator(400, opYFX, pl_nameToId(L"//"));
	addOperator(400, opYFX, pl_nameToId(L"rdiv"));
	addOperator(400, opYFX, pl_nameToId(L"<<"));
	addOperator(400, opYFX, pl_nameToId(L">>"));
	addOperator(400, opYFX, pl_nameToId(L"mod"));
	addOperator(400, opYFX, pl_nameToId(L"rem"));
	addOperator(200, opXFX, pl_nameToId(L"**"));
	addOperator(200, opXFY, pl_nameToId(L"^"));
}
;
Program::~Program() {
   for (int i = 0; i < operators.size(); i++) delete operators[i];
   for (int i = 0; i < levels.size(); i++) delete levels[i];
   clearElements();
}
;


void Program::addOperator(int pr, TOperatorType t, PID name)
{
   Operator* op = new Operator();
   op->precedence  = pr;
   op->type = t;
   op->name = name;
   operators.push_back(op);
   ///TODO: Effizienter machen. Das hier ist n*n
   updateOpList();
}

int  opcompare(const void *elem1, const void *elem2 )
{
   OperatorLevel* op1 = *((OperatorLevel**)(elem1));
   OperatorLevel* op2 = *((OperatorLevel**)(elem2));
   if (op1->precedence > op2->precedence) {
      return 1;
   } else if (op1->precedence < op2->precedence) {
      return -1;
   }else {
      return 0;
   }
};

void Program::updateOpList()
{
   levels.clear();
   map<int, OperatorLevel*> l;
   for (int i = 0; i < operators.size(); i++) {
      Operator* op = (Operator*) operators[i];
      OperatorLevel* oplevel;
      if (l.find(op->precedence) == l.end()) {
	 oplevel = new OperatorLevel();
	 oplevel->precedence = op->precedence;
	 l[op->precedence] = oplevel;
	 levels.push_back(oplevel);
      } else {
	 oplevel = l[op->precedence];
      };
      if (oplevel->obinfo.find(op->name) == oplevel->obinfo.end()) {
	 OperatorInfo info;
	 memset(&info, 0, sizeof(info));
	 oplevel->obinfo[op->name] = info;
      };
      OperatorInfo& opinfo = oplevel->obinfo[op->name];
      switch (op->type) {
	 case opXFX:
	 {
	    opinfo.XFX = op;
	 }; break;
	 case opYFX:
	 {
	    opinfo.YFX = op;
	 }; break;
	 case opXFY:
	 {
	    opinfo.XFY = op;
	 }; break;
	 case opXF:
	 {
	    opinfo.XF = op;
	 }; break;
	 case opYF:
	 {
	    opinfo.YF = op;
	 }; break;
	 case opFX:
	 {
	    opinfo.FX = op;
	 }; break;
	 case opFY:
	 {
	    opinfo.FY = op;
	 }; break;
	 
      };
   };
   //TODO: Sortierung ermöglichen
 //  sort(levels.begin(), levels.end(), ?);
   //levels.sort(opcompare);
}

Program* Program::instance = NULL;

Program* Program::getInstance()
{
   if (instance == NULL) {
      instance = EngineFactory::getInstance()->intern_createProgram();
   };
   return instance;
}


};
