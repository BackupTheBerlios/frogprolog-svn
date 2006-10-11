//
// C++ Implementation: PrologTerm
//
// Description: 
//
//
// Author: Michael Staud <staud@linux>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "prologengine.h"
#include "enginefactory.h"

namespace UtiProlog {

AllocCodeHelper::AllocCodeHelper(BaseTarget* _t)
{
   t = _t;
}

void AllocCodeHelper::newGoal()
{
   seenregisterarguments.clear();
}

Term::Term()
{
   
}

Term::~Term(){
   
}



Var::Var()
{

}

Var::~Var(){
   
};

BaseEngine* Var::copy()
{
   Var* newbody = EngineFactory::getInstance()->createVar();
	newbody->pos = pos;
	newbody->setName(getName());
	return newbody;
}

bool Var::unify(UNIFYMAP &map, Term* other)
{
   if (map.find(name) != map.end()) {
      return map[name]->unify(map, other);
   };
   if (dynamic_cast<Var*>(other)) {
      Var* v = (Var*)other;
      if (map.find(v->name) != map.end()) {
         return unify(map, map[v->name]);
      };
   }
   if (dynamic_cast<Var*>(other)) {
      Var* v = (Var*)other;
      if (v->name > name) {
         return v->unify(map, this);
      };
      map[name] = v;
      return true;
   } else {
      map[name] = other;
      return true;
   };
   return true;
};

void Var::changenamespace(int add)
{
   name += add;
}
void Var::exchangevar(int oldname, int newname)
{
	if (name == oldname) name = newname;
};


void Var::output(CUtiString &str)
{
   str += idbase.idToIdentifier(name);
};

void Var::performGetCodeEasy(BaseTarget*t, int Xi, int &maxX, AllocCodeHelper* helper)
{
   PID varname = getName();
   if (varname == idbase.getVoid()) {
      helper->unify_void();
      return;
   };
   if (helper->seenregisterarguments.find(varname) !=   helper->seenregisterarguments.end()) {
      if (Xi == -1) {
      helper->unify_value(this, varname);
      } else {
         helper->unify_value(this, varname, Xi);
      };
   } else {

      helper->seenregisterarguments[varname] = varname;
      if (Xi == -1) {
         helper->unify_variable(this, varname);
      } else {
         helper->unify_variable(this, varname, Xi);
      };
   };
};

void Var::performGetCode(BaseTarget*t, int Xi, int &maxX, AllocCodeHelper* helper)
{
   //oout << idname(name);
}

IntNumber::IntNumber()
{
   value = 0;
}

IntNumber::~IntNumber()
{
   
}

BaseEngine* IntNumber::copy()
{
   IntNumber* newbody = EngineFactory::getInstance()->createIntNumber();
	newbody->pos = pos;
	newbody->setValue(getValue());
	return newbody;
}

void IntNumber::output(CUtiString &str)
{
   str += value;
};

bool IntNumber::unify(UNIFYMAP &map, Term* other)
{
   if (dynamic_cast<Var*>(other)) {
      return other->unify(map, this);
   } else if (dynamic_cast<IntNumber*>(other)) {
      IntNumber* n = dynamic_cast<IntNumber*>(other);
      return getValue() == n->getValue();
   } else if (dynamic_cast<RealNumber*>(other)) {
      RealNumber* n = dynamic_cast<RealNumber*>(other);
      return getValue() == n->getValue();
   };
   return false;
}

void IntNumber::performGetCode(BaseTarget*t, int Xi, int &maxX, AllocCodeHelper* helper)
{
  
}



void IntNumber::performGetCodeEasy(BaseTarget*t, int Xi, int &maxX, AllocCodeHelper* helper)
{
   helper->get_integer(getValue(), Xi);
}

RealNumber::RealNumber()
{
   value = 0;
}

RealNumber::~RealNumber()
{
   
}

BaseEngine* RealNumber::copy()
{
   RealNumber* newbody = EngineFactory::getInstance()->createRealNumber();
	newbody->pos = pos;
	newbody->setValue(getValue());
	return newbody;
}

void RealNumber::performGetCode(BaseTarget*t, int Xi, int &maxX, AllocCodeHelper* helper)
{
  
}

void RealNumber::performGetCodeEasy(BaseTarget*t, int Xi, int &maxX, AllocCodeHelper* helper)
{
   helper->get_real(getValue(), Xi);
}
void RealNumber::output(CUtiString &str)
{
   str += (float)value;
};

bool RealNumber::unify(UNIFYMAP &map, Term* other)
{
   if (dynamic_cast<Var*>(other)) {
      return other->unify(map, this);
   } else if (dynamic_cast<IntNumber*>(other)) {
      IntNumber* n = dynamic_cast<IntNumber*>(other);
      return getValue() == n->getValue();
   } else if (dynamic_cast<RealNumber*>(other)) {
      RealNumber* n = dynamic_cast<RealNumber*>(other);
      return getValue() == n->getValue();
   };
   return false;
}

Structure::Structure()
{
   elements.deleteItems = true;
}

Structure::~Structure()
{
   
};

BaseEngine* Structure::copy()
{
   Structure* newbody = EngineFactory::getInstance()->createStructure();
   newbody->pos = pos;
	newbody->setName(getName());
	for (int i = 0; i < elementCount(); i++) {
		newbody->addElement((Term*)getElement(i)->copy());	
	};
	return newbody;
}

void Structure::performGetCodeEasy(BaseTarget*t, int Xi, int &maxX, AllocCodeHelper* helper)
{
   helper->get_structure(name, elements.count, Xi, false);
   int start = maxX;
   int* Xis = new int[elementCount()];
   for (int i = 0; i < elementCount(); i++) {
      Term* term = getElement(i);
      Xis[i] = 0;
      if (dynamic_cast<Var*>(term)) {
	 ((Var*)term)->performGetCodeEasy(t, -1, maxX, helper);
         Xis[i] = -1;
      } else if (dynamic_cast<IntNumber*>(term)) {
	 Xis[i] = -1;
	 helper->get_integer(((IntNumber*)term)->getValue());
      } else if (dynamic_cast<RealNumber*>(term)) {
	 Xis[i] = -1;
	 helper->get_real(((RealNumber*)term)->getValue());
      } else {
         helper->unify_variable(maxX, false);
         Xis[i] = maxX;
        
         maxX++;
      };
   };
   for (int i = 0; i < elementCount(); i++) {
      if (Xis[i] != -1)
         getElement(i)->performGetCodeEasy(t, Xis[i], maxX, helper);
   };
   delete [] Xis;
}

void Structure::output(CUtiString &str)
{
   str += idbase.idToIdentifier(name);
   if (elements.count != 0) {
      str += L"(";
      for (int i = 0; i < elementCount(); i++) {
         getElement(i)->output(str);
         if (i != elementCount()-1) str += L", ";
      };
      
      str += L")";
   };
};

bool Structure::unify(UNIFYMAP &map, Term* other)
{
   if (dynamic_cast<Var*>(other)) {
      return other->unify(map, this);
   } else if (dynamic_cast<Structure*>(other)) {
      Structure* n = dynamic_cast<Structure*>(other);
      if (n->elementCount() != elementCount()) return false;
      if (n->getName() != getName()) return false;
      for (int i = 0; i < elementCount(); i++) {
         if (getElement(i)->unify(map, n->getElement(i)) == false) return false;
      };
      return true;
   };
   return false;
}

void Structure::changenamespace(int add)
{
   for (int i = 0; i < elementCount(); i++) {
      getElement(i)->changenamespace(add);
   };
}

void Structure::exchangevar(int oldname, int newname)
{
	for (int i = 0; i < elementCount(); i++) {
		getElement(i)->exchangevar(oldname, newname);
	};
};

}
