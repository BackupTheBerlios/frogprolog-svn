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

#include "wamengine.h"


#define target ((WAMTarget*)t)
#define idname(A) (idbase.idToIdentifier(A))
#define idcode(A) (idbase.idToIdentifierCode(A))

using namespace Interpreter;

namespace UtiProlog {
namespace WAM {
   
WAMTarget::WAMTarget() {
    container = new Interpreter::CodeContainer();
};

WAMTarget::~WAMTarget() {
    delete container;
};
void WAMTarget::allocate(int N) {
    wcout << L"allocate " << N << endl;
    container->addCode(opAllocate);
    container->addCode(N);
}
void WAMTarget::deallocate() {
    wcout << L"deallocate" << endl;
    container->addCode(opDeallocate);
}
void WAMTarget::call(PID name,int arity) {
    wcout << L"call " << name << L"/" << arity << endl;
    container->addCode(opCall);
    container->addCode(name);
    container->addCode(arity);
}
int* WAMTarget::try_me_else() {
   container->addCode(opTryMeElse);
   int * r = container->addCode(0);
   wcout << L"try_me_else " << endl;
    return r;
}

int* WAMTarget::retry_me_else(int* i) {
   *i = container->getCurrentPos();
   container->addCode(opRetryMeElse);
   int * r = container->addCode(0);
   wcout << L"retry_me_else " << endl;
    return r;
}

void WAMTarget::trust_me(int* i) {
   *i = container->getCurrentPos();
   container->addCode(opTrustMe);
   wcout << L"trust_me " << endl;
}
void WAMTarget::addLabel(PID name, int arity) {
   container->addLabel(container->getCurrentPos(), name, arity);
   wcout << L"label " << name << L"/" << arity << endl;
}

void WAMTarget::unifyValue(int Xi, int arg) {
   container->addCode(opUnifyValueA);
   container->addCode(Xi);
   container->addCode(arg);
   wcout << L"unifyValue X" << Xi << ", A" << arg << endl;
}
void WAMTarget::unifyVariable(int Xi, int arg) {
   container->addCode(opUnifyVariableA);
   container->addCode(Xi);
   container->addCode(arg);
   wcout << L"unifyVariable X" << Xi << ", A" << arg << endl;
}
void WAMTarget::unifyValue(int Xi) {
   container->addCode(opUnifyValue);
   container->addCode(Xi);
   wcout << L"unifyValue X" << Xi << endl;
}
void WAMTarget::unifyVariable(int Xi) {
   container->addCode(opUnifyVariable);
   container->addCode(Xi);
   wcout << L"unifyVariable X" << Xi << endl;
}
void WAMTarget::unifyValueY(int Xi, int arg) {
   container->addCode(opUnifyValueYA);
   container->addCode(Xi);
   container->addCode(arg);
   wcout << L"unifyValue Y" << Xi << ", A" << arg << endl;
}
void WAMTarget::unifyVariableY(int Xi, int arg) {
   container->addCode(opUnifyVariableYA);
   container->addCode(Xi);
   container->addCode(arg);
   wcout << L"unifyVariable Y" << Xi << ", A" << arg << endl;
}
void WAMTarget::unifyValueY(int Xi) {
   container->addCode(opUnifyValueY);
   container->addCode(Xi);
   wcout << L"unifyValue Y" << Xi << endl;
}
void WAMTarget::unifyVariableY(int Xi) {
   container->addCode(opUnifyVariableY);
   container->addCode(Xi);
   wcout << L"unifyVariable Y" << Xi << endl;
}
void WAMTarget::get_integer(int value) {
   container->addCode(opGetInteger);
   container->addCode(value);
   wcout << L"get_integer " << value << endl;
}
void WAMTarget::get_real(float value) {
   container->addCode(opGetReal);
   container->addCode(*((int*)&value));
   wcout << L"get_real " << value << endl;
}
void WAMTarget::get_integer(int value, int arg) {
   container->addCode(opGetIntegerA);
   container->addCode(value);
   container->addCode(arg);
   wcout << L"get_integer " << value << ", A" << arg << endl;
}
void WAMTarget::get_real(float value, int arg) {
   container->addCode(opGetRealA);
   container->addCode(*((int*)&value));
   container->addCode(arg);
   wcout << L"get_real " << value << ", A" << arg << endl;
}
void WAMTarget::get_structure(PID name, int arity, int xi) {
   container->addCode(opGetStructure);
   container->addCode(name);
   container->addCode(arity);
   container->addCode(xi);
   wcout << L"get_structure " << name << "/" << arity << ", X" << xi << endl;
}
void WAMTarget::put_structure(PID name, int arity, int xi) {
   container->addCode(opPutStructure);
   container->addCode(name);
   container->addCode(arity);
   container->addCode(xi);
   wcout << L"put_structure " << name << "/" << arity << ", X" << xi << endl;
}
void WAMTarget::put_structureA(PID name, int arity, int arg) {
   container->addCode(opPutStructureA);
   container->addCode(name);
   container->addCode(arity);
   container->addCode(arg);
   wcout << L"put_structure " << name << "/" << arity << ", A" << arg << endl;
}
void WAMTarget::get_structureA(PID name, int arity, int arg) {
   container->addCode(opGetStructureA);
   container->addCode(name);
   container->addCode(arity);
   container->addCode(arg);
   wcout << L"get_structure " << name << "/" << arity << ", A" << arg << endl;
}

void WAMTarget::set_variable(int Xi)
{
   container->addCode(opSetVariable);
   container->addCode(Xi);
   wcout << L"set_variable X" << Xi << endl;
}

void WAMTarget::set_value(int Xi)
{
   container->addCode(opSetValue);
   container->addCode(Xi);
   wcout << L"set_value X" << Xi << endl;
}
    
void WAMTarget::set_variableY(int Xi)
{
   container->addCode(opSetVariableY);
   container->addCode(Xi);
   wcout << L"set_variable Y" << Xi << endl;
}

void WAMTarget::set_valueY(int Xi)
{
   container->addCode(opSetValueY);
   container->addCode(Xi);
   wcout << L"set_value Y" << Xi << endl;
}

void WAMTarget::put_variable(int Xi, int arg)
{
   container->addCode(opPutVariable);
   container->addCode(Xi);
   container->addCode(arg);
   wcout << L"put_variable X" << Xi << ", A" << arg << endl;
}

void WAMTarget::put_value(int Xi, int arg)
{
   container->addCode(opPutValue);
   container->addCode(Xi);
   container->addCode(arg);
   wcout << L"put_value X" << Xi << ", A" << arg << endl;
}

void WAMTarget::put_variableY(int Xi, int arg)
{
   container->addCode(opPutVariableY);
   container->addCode(Xi);
   container->addCode(arg);
   wcout << L"put_variable Y" << Xi << ", A" << arg << endl;
}

void WAMTarget::put_valueY(int Xi, int arg)
{
   container->addCode(opPutValueY);
   container->addCode(Xi);
   container->addCode(arg);
   wcout << L"put_value Y" << Xi << ", A" << arg << endl;
}

void WAMTarget::put_int(int value)
{
   container->addCode(opPutInteger);
   container->addCode(value);
   wcout << L"put_integer " << value << endl;
}

void WAMTarget::put_real(float value)
{
   container->addCode(opPutReal);
   container->addCode(*((int*)&value));
   wcout << L"put_real " << value << endl;
}

void WAMTarget::put_int(int value, int arg)
{
   container->addCode(opPutIntegerA);
   container->addCode(value);
   container->addCode(arg);
   wcout << L"put_integer " << value <<", A" << arg << endl;
}

void WAMTarget::put_real(float value, int arg)
{
   container->addCode(opPutReal);
   container->addCode(*((int*)&value));
   container->addCode(arg);
   wcout << L"put_real " << value <<", A" << arg <<  endl;
}

WAMVar::WAMVar() {
}
WAMVar::~WAMVar() {
}
void WAMVar::perform(BaseTarget* t) {
}

WAMIntNumber::WAMIntNumber() {
}
WAMIntNumber::~WAMIntNumber() {
}
void WAMIntNumber::perform(BaseTarget* t) {
}


WAMRealNumber::WAMRealNumber() {
}
WAMRealNumber::~WAMRealNumber() {
}
void WAMRealNumber::perform(BaseTarget* t) {
}


WAMStructure::WAMStructure() {
}
WAMStructure::~WAMStructure() {
}

void WAMStructure::perform(BaseTarget* t) {
}

WAMBody::WAMBody() {
}
WAMBody::~WAMBody() {
}
void WAMBody::perform(BaseTarget* t) {
    if (elementCount() == 1) {
        getElement(0)->perform(t);
    };
}
WAMBodyPart::WAMBodyPart() {
}
WAMBodyPart::~WAMBodyPart() {
}
bool WAMBodyPart::needBacktracking() {
    return true;
};
void WAMBodyPart::perform(BaseTarget* t) {
    int elementdepth;
    if (needBacktracking()) {

        for (int i = 0; i < elementCount(); i++) {

            getElement(i)->perform(t);

        };
    };

}

WAMGoal::WAMGoal() {
}
WAMGoal::~WAMGoal() {
}

void WAMGoal::perform(BaseTarget* t) {
    factparent->helper->newGoal();
    switch (goal) {
    case gTerm: {

            if (dynamic_cast<Structure*>(getElement())) {
                Structure* s = (Structure*)getElement();
                WAMProgram* p = (WAMProgram*)t->prog;
                //s->putStructureInArguments(factparent);
                int max = 2;
                for (int i = 0; i < s->elementCount(); i++) {
                    Term* el = s->getElement(i);
                    //                  el->performGetCodeA(t, 1,true,i+1, max, factparent->helper);
                };
            };
        }
        ;
        break;
        /*         case gUnification: {
                    Term* t1 = (Term*)getElement();
                    Term* t2 = (Term*)getElement2();
                    UNIFYMAP unimap;
                    if (!t1->unify(unimap, t2)) {
                       wcout << L"Unification error, not succesful" << endl;
                    };
                    UNIFYMAP::iterator it;
                    for (it = unimap.begin(); it != unimap.end(); it++) {
                       PID var = it->first;
                       Term* term = (Term*)it->second;
                      
                      //wcout << idname(var) << L" == " ;
                      
                       //oout << L"loadVariable(" << getVarName(this, var) << L", 1);";
                       //oout_newline();
                       int max = 2;
                       //WAMAllocCodeHelper* h = new WAMAllocCodeHelper(t);
                       //term->performGetCode(factparent->helper, 1, true, max, h);
                      // delete h;
                    };
                   
              }; break;*/
    };
}

WAMFact::WAMFact() {
}
WAMFact::~WAMFact() {
}

void WAMFact::perform(BaseTarget* t) {
    if (!searched) {
        searchVars();

        searched = true;
    }

}
WAMProgram::WAMProgram() : Program() {
    progname = L"PrologProgram";
}
WAMProgram::~WAMProgram() {
}
void WAMProgram::perform(BaseTarget* t) {
    t->prog = this;

    /*for (int i = 0; i < elementCount(); i++) {
     
      
       Fact* f = getElement(i);
       f->perform(t);
    };*/
    //FACTMAP factinfo;
    for (FACTMAP::iterator i = factinfo.begin(); i != factinfo.end(); i++) {
        compile((WAMTarget*)t, i->first, i->second);
    }
}
void WAMProgram::compile(WAMTarget* t, FactInfo f, FACTVECTOR & vec) {
    t->addLabel(f.name, f.arity);
    if (vec.size() == 1) {
        generateClause(t, vec[0]);
        t->deallocate();
    } else if (vec.size() == 2) {
        int * v = t->try_me_else();
        generateClause(t, vec[0]);
        t->trust_me(v);
        generateClause(t, vec[1]);
        t->deallocate();
    } else {
        int * v = t->try_me_else();
        generateClause(t, vec[0]);
        for (int i = 1; i < vec.size()-1; i++) {
            v = t->retry_me_else(v);
            generateClause(t, vec[i]);
        }
        t->trust_me(v);
        generateClause(t, vec[vec.size()-1]);
        t->deallocate();
    }
}

void WAMProgram::initvars() {
    xi = 1;
    hcell.clear();
    vcell.clear();
    newvarset.clear();
}

void WAMProgram::generateClause(WAMTarget* t, Fact* f) {
    Structure* head = f->getHead();
    BodyPart* part = f->getBody()->getElement(0);
    t->allocate(f->permanentvars.size());
    initvars();
    currentfact = f;
    for (int i = 0; i < head->elementCount(); i++) {
        getcode(t, head->getElement(i), i);
    };
    for (int i = 0; i < part->elementCount(); i++) {
        generateElement(t, part->getElement(i));
    }
}
void WAMProgram::generateElement(WAMTarget* t, Goal* g) {
    Structure* s = dynamic_cast<Structure*>(g->getElement());
    if (g->getGoal() == gTerm && s != NULL) {
        if (s->getName() == idbase.identifierToID("=") && s->elementCount() == 2) {
            generateElementEqual(t, s);
        } else {
            generateElementCall(t, s);
        }
    };
}
void WAMProgram::generateElementEqual(WAMTarget* t, Structure*s) {
    putcode(t, s->getElement(0), 0);
    getcode(t, s->getElement(1), 0);
};
void WAMProgram::generateElementCall(WAMTarget* t, Structure*s) {
    for (int i = 0; i < s->elementCount(); i++) {
        putcode(t, s->getElement(i), i);
    }
    t->call(s->getName(), s->elementCount());
};
bool WAMProgram::isFirstVar(PID c) {
    if (newvarset.find(c) == newvarset.end()) {
        newvarset.insert(c);
        return false;
    } else {
        return true;
    };
};
void WAMProgram::reserve(Term* c, int &i) {
    i = xi;
    hcell[c] = i;
};
void WAMProgram::read(Term* c, int &i) {
    i = hcell[c];
};

void WAMProgram::reserve(PID c, int &i) {
    i = xi;
    vcell[c] = i;
};
void WAMProgram::read(PID c, int &i) {
    i = vcell[c];
};
void WAMProgram::getcode(WAMTarget* t, Term* term, int arg) {
    if (dynamic_cast<Structure*>(term)) {
        getcode_str(t,(Structure*)term, arg);
    } else if (dynamic_cast<IntNumber*>(term)) {
        getcode_int(t, (IntNumber*)term, arg);
    } else if (dynamic_cast<RealNumber*>(term)) {
        getcode_real(t,(RealNumber*)term, arg);
    } else if (dynamic_cast<Var*>(term)) {
        if (isFirstVar(((Var*)term)->getName())) {
            getcode_newvar(t,(Var*)term, arg);
        } else {
            getcode_oldvar(t,(Var*)term, arg);
        };
    }
}
void WAMProgram::getcode(WAMTarget* t, Term* term) {
    if (dynamic_cast<Structure*>(term)) {
        getcode_str(t, (Structure*)term);
    }
}
void WAMProgram::getcode_pre(WAMTarget* t, Term* term) {
    if (dynamic_cast<Structure*>(term)) {
        getcode_pre_str(t,(Structure*)term);
    } else if (dynamic_cast<IntNumber*>(term)) {
        getcode_pre_int(t,(IntNumber*)term);
    } else if (dynamic_cast<RealNumber*>(term)) {
        getcode_pre_real(t,(RealNumber*)term);
    } else if (dynamic_cast<Var*>(term)) {
        if (isFirstVar(((Var*)term)->getName())) {
            getcode_pre_newvar(t,(Var*)term);
        } else {
            getcode_pre_oldvar(t,(Var*)term);
        };
    }
}

void WAMProgram::getcode_str(WAMTarget* t, Structure* term, int arg) {
    //int xi;
    //reserve(term, xi);
    t->get_structureA(term->getName(), term->elementCount(),arg);
    for (int i = 0; i < term->elementCount(); i++) {
        getcode_pre(t, term->getElement(i));
    };
    for (int i = 0; i < term->elementCount(); i++) {
        getcode(t, term->getElement(i));
    };
}
void WAMProgram::getcode_str(WAMTarget* t, Structure* term) {
    int xi;
    read(term, xi);
    t->get_structure(term->getName(), term->elementCount(), xi);
    for (int i = 0; i < term->elementCount(); i++) {
        getcode_pre(t, term->getElement(i));
    };
    for (int i = 0; i < term->elementCount(); i++) {
        getcode(t, term->getElement(i));
    };
}
void WAMProgram::getcode_pre_str(WAMTarget* t, Structure* term) {
    int xi;
    reserve(term, xi);
    t->unifyVariable(xi);
}

void WAMProgram::getcode_newvar(WAMTarget* t, Var* term, int arg) {
    map<PID, int>::iterator it = currentfact->permanentvars.find(term->getName());
    if (it == currentfact->permanentvars.end()) {
        int xi;
        reserve(term->getName(), xi);
        t->unifyVariable(xi, arg);
    } else {
        t->unifyVariableY(it->second, arg);
    }
}
void WAMProgram::getcode_pre_newvar(WAMTarget* t, Var* term) {
    map<PID, int>::iterator it = currentfact->permanentvars.find(term->getName());
    if (it == currentfact->permanentvars.end()) {
        int xi;
        reserve(term->getName(), xi);
        t->unifyVariable(xi);
    } else {
        t->unifyVariableY(it->second);
    }
}

void WAMProgram::getcode_oldvar(WAMTarget* t, Var* term, int arg) {
    map<PID, int>::iterator it = currentfact->permanentvars.find(term->getName());
    if (it == currentfact->permanentvars.end()) {
        int xi;
        read(term->getName(), xi);
        t->unifyValue(xi, arg);
    } else {
        t->unifyValueY(it->second, arg);
    }
}
void WAMProgram::getcode_pre_oldvar(WAMTarget* t, Var* term) {
    map<PID, int>::iterator it = currentfact->permanentvars.find(term->getName());
    if (it == currentfact->permanentvars.end()) {
        int xi;
        read(term->getName(), xi);
        t->unifyValue(xi);
    } else {
        t->unifyValueY(it->second);
    }
}

void WAMProgram::getcode_int(WAMTarget* t, IntNumber* term, int arg) {
    t->get_integer(term->getValue(), arg);
}
void WAMProgram::getcode_pre_int(WAMTarget* t, IntNumber* term) {
    t->get_integer(term->getValue());
}

void WAMProgram::getcode_real(WAMTarget* t, RealNumber* term, int arg) {
    t->get_real(term->getValue(), arg);
}
void WAMProgram::getcode_pre_real(WAMTarget* t, RealNumber* term) {
    t->get_real(term->getValue());
}

void WAMProgram::putcode(WAMTarget* t, Term* term)
{
   if (dynamic_cast<Structure*>(term)) {
      putcode_str(t, (Structure*)term);
   }
}

void WAMProgram::putcode(WAMTarget* t, Term* term, int arg)
{
   if (dynamic_cast<Structure*>(term)) {
      putcode_str(t,(Structure*)term, arg);
   } else if (dynamic_cast<IntNumber*>(term)) {
      putcode_int(t, (IntNumber*)term, arg);
   } else if (dynamic_cast<RealNumber*>(term)) {
      putcode_real(t,(RealNumber*)term, arg);
   } else if (dynamic_cast<Var*>(term)) {
      if (isFirstVar(((Var*)term)->getName())) {
	 putcode_newvar(t,(Var*)term, arg);
      } else {
	 putcode_oldvar(t,(Var*)term, arg);
      };
   }
}

void WAMProgram::putcode_str(WAMTarget* t, Structure* term, int arg)
{
   for (int i = 0; i < term->elementCount(); i++) {
      putcode_pre(t, term->getElement(i));
   }
   
   for (int i = 0; i < term->elementCount(); i++) {
      putcode(t, term->getElement(i));
   }
   t->put_structureA(term->getName(), term->elementCount(), arg);
   for (int i = 0; i < term->elementCount(); i++) {
      putcode_post(t, term->getElement(i));
   }
}

void WAMProgram::putcode_newvar(WAMTarget* t, Var* term, int arg)
{
   map<PID, int>::iterator it = currentfact->permanentvars.find(term->getName());
   if (it == currentfact->permanentvars.end()) {
      int xi;
      reserve(term->getName(), xi);
      t->put_variable(xi, arg);
   } else {
      t->put_variableY(it->second, arg);
   }
}
void WAMProgram::putcode_oldvar(WAMTarget* t, Var* term, int arg)
{
   map<PID, int>::iterator it = currentfact->permanentvars.find(term->getName());
   if (it == currentfact->permanentvars.end()) {
      int xi;
      read(term->getName(), xi);
      t->put_value(xi, arg);
   } else {
      t->put_valueY(it->second, arg);
   }
}
void WAMProgram::putcode_int(WAMTarget* t, IntNumber* term, int arg)
{
   t->put_int(term->getValue(), arg);
}
void WAMProgram::putcode_real(WAMTarget* t, RealNumber* term, int arg)
{
   t->put_real(term->getValue(), arg);
}


void WAMProgram::putcode_str(WAMTarget* t, Structure* term)
{
   for (int i = 0; i < term->elementCount(); i++) {
      putcode_pre(t, term->getElement(i));
   }
   
   for (int i = 0; i < term->elementCount(); i++) {
      putcode(t, term->getElement(i));
   }
   int xi;
   read(term, xi);
   t->put_structure(term->getName(), term->elementCount(), xi);
   for (int i = 0; i < term->elementCount(); i++) {
      putcode_post(t, term->getElement(i));
   }
}

void WAMProgram::putcode_pre(WAMTarget* t, Term* term)
{
   if (dynamic_cast<Structure*>(term)) {
      putcode_pre_str(t, (Structure*)term);
   }
}

void WAMProgram::putcode_pre_str(WAMTarget* t, Structure* term)
{
   int xi;
   reserve(term, xi);
}

void WAMProgram::putcode_post(WAMTarget* t, Term* term)
{
   if (dynamic_cast<Structure*>(term)) {
      putcode_post_str(t,(Structure*)term);
   } else if (dynamic_cast<IntNumber*>(term)) {
      putcode_post_int(t, (IntNumber*)term);
   } else if (dynamic_cast<RealNumber*>(term)) {
      putcode_post_real(t,(RealNumber*)term);
   } else if (dynamic_cast<Var*>(term)) {
      if (isFirstVar(((Var*)term)->getName())) {
	 putcode_post_newvar(t,(Var*)term);
      } else {
	 putcode_post_oldvar(t,(Var*)term);
      };
   }
}

void WAMProgram::putcode_post_str(WAMTarget* t, Structure* term)
{
   int xi;
   read(term, xi);
   t->set_value(xi);
}

void WAMProgram::putcode_post_newvar(WAMTarget* t, Var* term)
{
   map<PID, int>::iterator it = currentfact->permanentvars.find(term->getName());
   if (it == currentfact->permanentvars.end()) {
      int xi;
      reserve(term->getName(), xi);
      t->set_variable(xi);
   } else {
      t->set_variableY(it->second);
   }
}

void WAMProgram::putcode_post_oldvar(WAMTarget* t, Var* term)
{
   map<PID, int>::iterator it = currentfact->permanentvars.find(term->getName());
   if (it == currentfact->permanentvars.end()) {
      int xi;
      read(term->getName(), xi);
      t->set_value(xi);
   } else {
      t->set_valueY(it->second);
   }
}

void WAMProgram::putcode_post_int(WAMTarget* t, IntNumber* term)
{
   t->put_int(term->getValue());
}

void WAMProgram::putcode_post_real(WAMTarget* t, RealNumber* term)
{
   t->put_real(term->getValue());
}
};
}
;
