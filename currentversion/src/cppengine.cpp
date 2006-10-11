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

#include "cppengine.h"

#include "cppbuildin.h"
#include "cpphelper.h"


namespace UtiProlog {
namespace Cpp {
const int VARADD = 1000000;
const wchar_t* argumentname = L"ARG_";
CUtiString getVarName(BaseEngine* eng, PID name) {
    CppFact* f= (CppFact*)eng->factparent;

    if (name >= VARADD) {
       PID n = name-VARADD;
       if (n == idbase.identifierToID(L"_")) {
	  return L"pl_getVoid()";
       } else {
	  return argumentname+idbase.idToIdentifierCode(n);
       }
    } else {
       if (name == idbase.identifierToID(L"_")) {
	  return L"pl_getVoid()";
       };
        if (!f) {
            return idbase.idToIdentifierCode(name);
        };
        VarInfo& info = f->Vars[name];
        if (info.headvar) {
	   return idbase.idToIdentifierCode(name);
        } else {
            CUtiString str = L"pl_stackframe->";
	    str += idbase.idToIdentifierCode(name);
            return str;
        };
    }
};

CUtiString makeDynName(PID name, int arity) {
    CUtiString str;
    str += L"pl_dyn_";
    str += idname(name);
    str += L"_";
    str += arity;
    return str;
}
void makeBacktracking(BaseTarget* t) {
    oout << L"{";
    oout_incdepth();
    oout_newline();
    oout << L"pl_DoBacktracking();";
    oout_newline();
    oout << L"break;";
    oout_decdepth();
    oout_newline();
    oout << L"};";
    oout_newline();
};

CppAllocCodeHelper::CppAllocCodeHelper(BaseTarget* _t) : AllocCodeHelper(_t) {
   unifyFact = NULL;
//   arguments = NULL;
}
void CppAllocCodeHelper::put_variable(int Xn, bool permanent, int Ai) {}
void CppAllocCodeHelper::put_value(int Xn, bool permanent, int Ai) {}
void CppAllocCodeHelper::put_structure(PID name, int arity, int Xn, bool permanent, int Ai) {}
void CppAllocCodeHelper::get_variable(int Xn, bool permanent, int Ai) {}
void CppAllocCodeHelper::get_value(int Xn, bool permanent, int Ai) {}
void CppAllocCodeHelper::get_structure(PID name, int arity, int Xn, bool permanent, int Ai) {}
void CppAllocCodeHelper::put_structure(PID name, int arity, int Xi, bool permanent) {
    oout << L"pl_put_structure(pl_s(PLN_" << idname(name) << L"," << arity << L"), " << Xi << ");";
    oout_newline();
}


void CppAllocCodeHelper::set_variable(int Xi, bool permanent) {
    oout << L"pl_set_variable(" << Xi << L");";
    oout_newline();
}

void CppAllocCodeHelper::set_value(int Xi, bool permanent) {
    oout << L"pl_set_value(" << Xi << L");";
    oout_newline();
}
void CppAllocCodeHelper::get_structure(PID name, int arity, int Xi, bool permanent) {
    oout << L" && pl_get_structure(pl_s(PLN_" << idname(name) << L"," << arity << L"), " << Xi << ")";
    oout_newline();
}

void CppAllocCodeHelper::put_integer(int number) {
    oout << L"pl_put_integer(" << number /*<< L", " << Xi */<< ");";
    oout_newline();
};
void CppAllocCodeHelper::get_integer(int number) {
    oout << L" && pl_get_integer(" << number /*<< L", " << Xi */<< ")";
    oout_newline();
};

void CppAllocCodeHelper::put_real(float number) {
    oout << L"pl_put_real(" << number /*<< L", " << Xi*/ << ");";
    oout_newline();
};
void CppAllocCodeHelper::get_real(float number) {
    oout << L" && pl_get_real(" << number /*<< L", " << Xi*/ << ")";
    oout_newline();
};
void CppAllocCodeHelper::get_integer(int number, int Xi) {
    oout << L" && pl_get_integer(" << number << L", " << Xi << ")";
    oout_newline();
}
void CppAllocCodeHelper::get_real(float number, int Xi) {
    oout << L" && pl_get_real(" << number << L", " << Xi << ")";
    oout_newline();
}

void CppAllocCodeHelper::unify_void()
{
   oout << L" && pl_unify_void()";
   oout_newline();
};

void CppAllocCodeHelper::unify_variable(int Xi, bool permanent) {
    oout << L" && pl_unify_variable(" << Xi << L")";
    oout_newline();
}
void CppAllocCodeHelper::unify_value(int Xi, bool permanent) {
    oout << L" && pl_unify_value(" << Xi << L")";
    oout_newline();
}

void CppAllocCodeHelper::unify_variable(BaseEngine* eng, PID localvar) {
   if (localvar > VARADD) {
//      assert(unifyFact->find(localvar-VARADD) != unifyFact->end());
	 
      int arg = (*unifyFact)[localvar-VARADD];
      if (argused[arg] == false) {
	 argused[arg] = true;
         oout << L" && pl_unify_variableARG(" << arg << L")";
      } else {
	 oout << L" && pl_unify_valueARG(" << arg << L")";
      };
   } else {
    oout << L" && pl_unify_variable(" << getVarName(eng, localvar) << L")";
    
   }oout_newline();
}

void CppAllocCodeHelper::unify_value(BaseEngine* eng, PID localvar) {
   if (localvar > VARADD) {
//      assert(unifyFact->find(localvar-VARADD) != unifyFact->end());
      int arg = (*unifyFact)[localvar-VARADD];
      
      if (argused[arg] == false) {
	 argused[arg] = true;
	 oout << L" && pl_unify_variableARG(" << arg << L")";
      } else {
	 oout << L" && pl_unify_valueARG(" << arg << L")";
      };
   } else { 
   
   oout << L" && pl_unify_value(" << getVarName(eng, localvar) << L")";
    
   }
   oout_newline();
}



void CppAllocCodeHelper::unify_variable(BaseEngine* eng, PID localvar, int Xi) {
    oout << L" && pl_unify_variable(" << getVarName(eng, localvar) << L", " << Xi << L")";
    oout_newline();
};
void CppAllocCodeHelper::unify_value(BaseEngine* eng, PID localvar, int Xi) {
    oout << L" && pl_unify_value(" << getVarName(eng, localvar) << L", " << Xi << L")";
    oout_newline();
};
CppTarget::CppTarget(wostream* stcpp, wostream* stheader) {
    str = stheader;
    strcpp = stcpp;
    strheader = stheader;
    depth = 0;
    element = 0;
    SingleStep = false;
    TexViewOutput = false;
    setHeader();
};

void CppTarget::setCPP()
{
   str = strcpp;
}

void CppTarget::setHeader()
{
   str = strheader;
}

CppTarget::~CppTarget() {}
;
void CppTarget::createORCodeBegin(int i, int factssize, int elementdepth) {
    BaseTarget *t = this;
    oout << L"case " << i << L": {";
    oout_incdepth();
    oout_newline();
    oout << L"pl_pos" << elementdepth << L" = " << i << L";";
    oout_newline();
    if (i != factssize-1)
        oout << L"pl_choisePoint();";
    oout_newline();
}
void CppTarget::createORCodeEnd(int i, int factssize, int elementdepth) {
    BaseTarget *t = this;
    oout << L"pl_exit" << elementdepth << L" = true;";
    oout_newline();
    oout_decdepth();
    oout_newline();
    oout << L"}; break;";
    oout_newline();
}

void CppTarget::createORCodeFinalize(int i, int factssize, int elementdepth) {
    BaseTarget *t = this;
    oout << L"case -1: {";
    oout_incdepth();
    oout_newline();
    oout << L"pl_pos" << elementdepth << L" = " << -1 << L";";
    oout_newline();
    oout << L"pl_exit" << elementdepth << L" = true;";
    oout_newline();

    oout_decdepth();
    oout_newline();
    oout << L"}; break;";
    oout_newline();
}
void CppTarget::createANDCodeBegin(int i, int factssize, int elementdepth) {
    *str << L"case " << i << L": {";
    incdepth();
    newline();
    *str << L"pl_pos" << elementdepth << L" = " << i << L";";
    newline();
}
void CppTarget::createANDCodeEnd(int i, int factssize, int elementdepth) {
    decdepth();
    newline();
    *str << L"}; ";
    newline();
}
void CppTarget::createANDCodeFinalize(int i, int factssize, int elementdepth) {
    *str << L"case " << factssize << L": {";
    incdepth();
    newline();
    *str << L"pl_pos" << elementdepth << L" = " << factssize << L";";
    newline();
    *str << L"pl_exit" << elementdepth << L" = true;";
    newline();

    decdepth();
    newline();
    *str << L"}; break;";
    newline();

    *str << L"case -1: {";
    incdepth();
    newline();
    *str << L"pl_pos" << elementdepth << L" = " << -1 << L";";
    newline();
    *str << L"pl_exit" << elementdepth << L" = true;";
    newline();

    decdepth();
    newline();
    *str << L"}; break;";
    newline();
}

int CppTarget::beginElement(int argcount, bool loop) {
    int k = element;
    element++;
    *str << L"int pl_pos" << k << L";";
    newline();
    *str << L"bool pl_exit" << k << L" = false;";
    newline();
    if (k == 0) {
        *str << L"pl_begin(pl_pos" << k << L", (void*&)pl_stackframe, " << argcount << L");";
    } else {
        *str << L"pl_begin(pl_pos" << k << L");";
    };
    if (loop) {
        newline();
        *str << L"while(!pl_exit" << k << L") {";
        newline();
        *str << L"switch(pl_pos" << k << L") {";
        incdepth();
    }
    newline();

    return k;
};
void CppTarget::endElement(bool loop) {
    if (loop) {
        decdepth();
        newline();
        *str << L"}";
        newline();
        *str << L"}";
    };
    newline();
    element--;
    int k = element;
    if (k == 0) {

        if (SingleStep)
            *str << L"pl_debug(L\"Exit \"); ";

        *str << L"return pl_end(pl_pos" << k << L", (void*&)pl_stackframe);";
    } else {
        *str << L"if (!pl_end(pl_pos" << k << L")) break;";
    };
};
void CppTarget::newline() {
    *str << endl;
    for (int i = 0; i < depth; i++)
        *str << L"   ";
}
void CppTarget::incdepth() {
    depth += 1;
}

void CppTarget::decdepth() {
    depth -= 1;
    if (depth < 0)
        depth = 0;
}


CppVar::CppVar() {}
CppVar::~CppVar() {}
void CppVar::perform(BaseTarget* t) {}

CppIntNumber::CppIntNumber() {}
CppIntNumber::~CppIntNumber() {}
void CppIntNumber::perform(BaseTarget* t) {}


CppRealNumber::CppRealNumber() {}
CppRealNumber::~CppRealNumber() {}
void CppRealNumber::perform(BaseTarget* t) {}


CppStructure::CppStructure() {}
CppStructure::~CppStructure() {}

void CppStructure::perform(BaseTarget* t) {}

CppBody::CppBody() {}
CppBody::~CppBody() {}
void CppBody::perform(BaseTarget* t) {
    if (elementCount() == 1) {
        getElement(0)->perform(t);
    } else if (elementCount() > 1) {
        int elementdepth;
        elementdepth = target->beginElement(owner->HeadVarsCount, true);
        for (int i = 0; i < elementCount(); i++) {
            target->createORCodeBegin(i, elementCount(), elementdepth);
            getElement(i)->perform(t);
            target->createORCodeEnd(i, elementCount(), elementdepth);
        };
        target->createORCodeFinalize(0, elementCount(), elementdepth);
        target->endElement(true);
        oout_newline();
    };
}
CppBodyPart::CppBodyPart() {}
CppBodyPart::~CppBodyPart() {}
bool CppBodyPart::needBacktracking() {
    return true;
};
void CppBodyPart::perform(BaseTarget* t) {
    int elementdepth;
    if (needBacktracking()) {
        /* elementdepth = target->beginElement(owner->HeadVarsCount, true);
         for (int i = 0; i < elementCount(); i++)
         {
           oout << L"case " << i << L": {";
           oout_incdepth();
           oout_newline();
           oout << L"pl_pos" << elementdepth << L" = " << i << L";";
           oout_newline();
           getElement(i)->perform(t);
           oout_decdepth();
           oout_newline();
           oout << L"}; ";
           oout_newline();
         };
         //EndCase
         oout << L"case " << elementCount() << L": {";
         oout_incdepth();
         oout_newline();
         oout << L"pl_pos" << elementdepth << L" = " << elementCount() << L";";
         oout_newline();
         oout << L"pl_exit" << elementdepth << L" = true;";
         oout_newline();

         oout_decdepth();
         oout_newline();
         oout << L"}; break;";
         oout_newline();

         oout << L"case -1: {";
         oout_incdepth();
         oout_newline();
         oout << L"pl_pos" << elementdepth << L" = " << -1 << L";";
         oout_newline();
         oout << L"pl_exit" << elementdepth << L" = true;";
         oout_newline();

         oout_decdepth();
         oout_newline();
         oout << L"}; break;";
         oout_newline();
         target->endElement(true);
        };*/
        elementdepth = target->beginElement(owner->HeadVarsCount, true);
        for (int i = 0; i < elementCount(); i++) {
            target->createANDCodeBegin(i, elementCount(), elementdepth);
            getElement(i)->perform(t);
            target->createANDCodeEnd(i, elementCount(), elementdepth);
        };
        //EndCase
        target->createANDCodeFinalize(elementCount(), elementCount(), elementdepth);
        target->endElement(true);
    };
    oout_newline();
}

CppGoal::CppGoal() { multiheadgoal = false;}
CppGoal::~CppGoal() {}
bool CppGoal::needUnify(UNIFYMAP& unimap) {
    UNIFYMAP::iterator it;
    for (it = unimap.begin(); it != unimap.end(); it++) {
        PID var = it->first;
        Term* term = (Term*)it->second;
        if (var < VARADD)
            return true;
        if (dynamic_cast<Var*>(term) == NULL)
            return true;
    }
    return false;
};
void CppGoal::doUnify(BaseTarget* t, Term* t1, Term* t2, HEADVARS* f, bool unequal) {
    UNIFYMAP unimap;
    //HEADVARS arg;
    bool* argused=NULL;
    if (f) {
       argused = new bool[f->size()];
       for (int i = 0; i < f->size(); i++) argused[i] = false;
    };
    int argument = 0;
    if (!t1->unify(unimap, t2)) {
        error(L"Unification error, not succesful");
        return;
    };
    /** @todo vorsicht, die Argumentliste stimmt nicht
     * Oh je. Die Argumentliste beim Fact wird auch
     * umsortiert. So stimmt das. Aber der Aufruf
     * könnte nicht korrekt sein.
     * */
    if (unimap.size() == 0)
        return;
    UNIFYMAP::iterator it;
    int unimapcount = 0;
     for (it = unimap.begin(); it != unimap.end(); it++) {
        PID var = it->first;
	if (var < VARADD && var == idbase.identifierToID(L"_")) {
	   continue;
	} else {
	  if (var-VARADD == idbase.identifierToID(L"_")) {
		    continue;
	   };
	}
       unimapcount++;
    }
    if (unimapcount == 0) return;
    if (unequal) {
       oout << L"if ((!pl_backtracking) && ((";
    } else {
       oout << L"if ((!pl_backtracking) && (!(";
    };
    oout_newline();
    bool first= true;

    for (it = unimap.begin(); it != unimap.end(); it++) {
        PID var = it->first;
        Term* term = (Term*)it->second;
        //if (var >= VARADD && dynamic_cast<Var*>(term) != NULL) continue;
	if (var < VARADD && var == idbase.identifierToID(L"_")) {
	   continue;
	} else {
	  if (var-VARADD == idbase.identifierToID(L"_")) {
		    continue;
	   };
	}
        if (first) {
            oout << L"    ";//loadVariable(";
            first = false;
        } else {
            oout << L" && ";//loadVariable(";
        }
        bool needunify = true;

        if (var < VARADD) {
            oout << "pl_loadVariable(" << getVarName(this, var) << L", 1)";
	} else  {
	    argument = (*f)[var-VARADD];
            if (argused[argument] == false) {
	       argused[argument] = true;
                //arg[var] = argument;
                if (dynamic_cast<Var*>(term)) {
                    oout << L"pl_loadArgVariable(" << argument << L", " << getVarName(this,static_cast<Var*>(term)->getName()) << L")";
                    needunify = false;
                } else if (dynamic_cast<IntNumber*>(term)) {
                    oout << L"pl_put_integer_ARG(" << ((IntNumber*)term)->getValue() << L", "  << argument << L")";
                    needunify = false;
                } else if (dynamic_cast<RealNumber*>(term)) {
                    oout << L"pl_put_real_ARG(" << ((RealNumber*)term)->getValue() << L", "  << argument << L")";
                    needunify = false;
                } else {
                    oout << L"pl_loadArgVar(" << argument << ", 1)";
                }
		
            } else {
                if (dynamic_cast<Var*>(term)) {
		   oout << L"pl_loadArgValue(" << argument << L"," << getVarName(this,static_cast<Var*>(term)->getName()) << L")";
                    needunify = false;
                } else if (dynamic_cast<IntNumber*>(term)) {
                    oout << L"pl_get_integer_ARG(" << ((IntNumber*)term)->getValue() << L", "  << argument << L")";
                    needunify = false;
                } else if (dynamic_cast<RealNumber*>(term)) {
                    oout << L"pl_get_real_ARG(" << ((RealNumber*)term)->getValue() << L", "  << argument << L")";
                    needunify = false;
                } else {
		   oout << L"pl_loadArgVal(" << argument << ", 1)";
                };
            };
        };
        oout_newline();
        if (needunify) {
            int max = 2;
            CppAllocCodeHelper* h = new CppAllocCodeHelper(t);
	    h->unifyFact = f;
	//    h->arguments = &arg;
	    h->argused = argused;
            term->performGetCodeEasy(t, 1,max, h);
            delete h;
        };
    };
    oout << L")))";
    makeBacktracking(t);
    delete [] argused;
}
void CppGoal::callCode(BaseTarget* t, Fact* f, Structure* s) {
    Structure* str = f->getHead();

    CUtiString out;
    str->output(out);
    oout <<L"// Test mit: "<< out;
    oout_newline();

    str->changenamespace(VARADD);
    doUnify(t, str, s, &f->headvars);
    str->changenamespace(-VARADD);
    if (f->getBody()) {
        oout << L"if (!";
        ((CppFact*)f)->printName(t);
        oout << L"(";
        for (int i = 0; i < f->HeadVarsCount; i++) {
            oout << L"*pl_ARG[" << i << L"]";
            if (i != f->HeadVarsCount-1)
                oout << L",";
        };
        oout << L"))";
        makeBacktracking(t);
    } else if (s->elementCount() == 1 &&
                                (s->getName() == idbase.identifierToID("assert") ||
                                 s->getName() == idbase.identifierToID("assertz") ||
                                 s->getName() == idbase.identifierToID("asserta") ||
                                 s->getName() == idbase.identifierToID("retract") ||
                                 s->getName() == idbase.identifierToID("retractall"))) {
            Term * t2 = s->getElement(0);
            Structure* str2 = dynamic_cast<Structure*>(t2);
            if (str2) {
                if (s->getName() == idbase.identifierToID("retract")) {
                    oout << L"if (!pl_dyn_retract(";
                    oout << makeDynName(str2->getName(), str2->elementCount());
                    oout << L", (pl_HeapCell*)pl_ARG[0]))";
                    makeBacktracking(t);
                } else if (s->getName() == idbase.identifierToID("retractall")) {
                    oout << L"pl_dyn_retractall(";
                    oout << makeDynName(str2->getName(), str2->elementCount());
                    oout << L", (pl_HeapCell*)pl_ARG[0]);";
                } else {
                    oout << L"pl_dyn_add(";
                    /// @todo test ob es wirklich ein dynamisches Prädikat ist
                    oout << makeDynName(str2->getName(), str2->elementCount());
                    if (s->getName() == idbase.identifierToID("asserta")) {
                        oout << L", (pl_HeapCell*)pl_ARG[0], pl_addfirst);";
                    } else {
                        oout << L", (pl_HeapCell*)pl_ARG[0], pl_addlast);";
                    }
                }
                //makeBacktracking(t);
            } else {
                error(L"Bei Assert/Retract wird als Parameter eine Structure erwartet.");
            };
        } else if (s->elementCount() == 2 &&
                   s->getName() == idbase.identifierToID("abolish")) {
            Term * t2 = s->getElement(0);
            Term * t3 = s->getElement(1);
            Structure* str2 = dynamic_cast<Structure*>(t2);
            IntNumber* num = dynamic_cast<IntNumber*>(t3);
            if (str2 && num) {
                oout << L"pl_dyn_clear(";
                oout << makeDynName(str2->getName(), num->getValue());
                oout << L");";
            } else {
                error(L"Bei Abolish wird als 1. Parameter eine Structure erwartet und als zweiter eine Integerzahl.");
            };
        } else if (dynamic_cast<CppForeignFact*>(f)) {
            CppForeignFact* f2 = (CppForeignFact*)f;
            if (!f2->directcall) {
                for (int i = 0; i < f2->parameter.size(); i++) {
                    CallInfo inf = f2->parameter[i];
                    switch (inf.type) {
                    case ci_in_Integer: {
                            oout << L"int pl_arg" << i << L";";

                        }
                        ;
                        break;
                    case ci_out_Integer: {
                            oout << L"int pl_arg" << i << L"=0;";


                        }
                        ;
                        break;
                    default: {}
                        ;
                        break;
                    }
                    oout_newline();
                };
                oout << L"if ((!pl_backtracking) && (!(";
                bool first = true;
#define ADDFIRSTAND  if (first) { first = false;  } else {  oout << L"    && ";};

                for (int i = 0; i < f2->parameter.size(); i++) {
                    CallInfo inf = f2->parameter[i];
                    switch (inf.type) {
                    case ci_in_Integer: {
                            ADDFIRSTAND;
                            oout << L"pl_call_getInt(" << L"pl_ARG[" << i << L"], &pl_arg" << i << L")";
                            oout_newline();
                        }
                        ;
                        break;
                    default: {}
                        ;
                        break;
                    };
                };

                ADDFIRSTAND;
                //((CppFact*)f)->printName(t);
                oout << f2->CName;
                oout << L"(";
                for (int i = 0; i < f2->parameter.size(); i++) {
                    CallInfo inf = f2->parameter[i];
                    switch (inf.type) {
                    case ci_in_Integer: {
                            oout << L"pl_arg" << i;
                        }
                        ;
                        break;
                    case ci_out_Integer: {
                            oout << L"&pl_arg" << i;
                        }
                        ;
                        break;
                    default: {}
                        ;
                        break;
                    };
                    if (i != f2->parameter.size()-1) {
                        oout << L", ";
                    };
                };
                oout << L")";
                oout_newline();


                for (int i = 0; i < f2->parameter.size(); i++) {
                    CallInfo inf = f2->parameter[i];
                    switch (inf.type) {
                    case ci_out_Integer: {
                            ADDFIRSTAND;
                            oout << L"pl_call_unifyInt(" << L"pl_ARG[" << i << L"], pl_arg" << i << L")";
                            oout_newline();
                        }
                        ;
                        break;
                    default: {}
                        ;
                        break;
                    };
                };

                oout << L")))";
                makeBacktracking(t);
            } else {
                oout << L"if (!";
                oout << f2->CName;
                oout << L"(";
                for (int i = 0; i < f->HeadVarsCount; i++) {
                    oout << L"(FP_term)pl_ARG[" << i << L"]";
                    if (i != f->HeadVarsCount-1)
                        oout << L",";
                };
                oout << L"))";
                makeBacktracking(t);
            };
        };
};

void CppGoal::callCodeSingle(BaseTarget* t, Structure* s) {

    CUtiString out;
    s->output(out);
    oout <<L"// Call: "<< out;
    oout_newline();
    CppStructure* str = new CppStructure();
    str->setName(s->getName());
    CUtiString name;
    HEADVARS vars;
    for (int i = 0; i < s->elementCount(); i++) {
        CppVar* var = new CppVar();
        name = L"A";
        name += i;
        var->setName(idbase.identifierToID(name));
	vars[var->getName()] = i;
        str->addElement(var);
	
    };

    str->changenamespace(VARADD);
    doUnify(t, str, s, &vars);
    str->changenamespace(-VARADD);
    delete str;

    oout << L"if (!";
    oout << idname(s->getName());
    oout << L"(";
    for (int i = 0; i < s->elementCount(); i++) {
        oout << L"*pl_ARG[" << i << L"]";
        if (i != s->elementCount()-1)
            oout << L",";
    };
    oout << L"))";
    makeBacktracking(t);

};
void CppGoal::handleIs(BaseTarget* t, Var* var, Term* term) {
    if (!var) {
        error(L"Variable bei is erwartet");
    };
    handleIsTerm(t, term);
    oout << L"pl_math_popVar(" << getVarName(this, var->getName()) << L");";
    oout_newline();
};

void CppGoal::handleIsTerm(BaseTarget* t, Term* term) {
    if (dynamic_cast<Structure*>(term)) {
        handleIsStructure(t, (Structure*)term);
    } else if (dynamic_cast<Var*>(term)) {
        oout << L"pl_math_pushVar(" << getVarName(this, ((Var*)term)->getName()) << L");";
        oout_newline();
    } else if (dynamic_cast<RealNumber*>(term)) {
        oout << L"pl_math_pushReal(" << ((RealNumber*)term)->getValue() << L");";
        oout_newline();
    } else if (dynamic_cast<IntNumber*>(term)) {
        oout << L"pl_math_pushInt(" << ((IntNumber*)term)->getValue() << L");";
        oout_newline();
    };
}

void CppGoal::handleIsStructureLoad(BaseTarget* t, Structure* str) {
    for (int i = 0; i < str->elementCount(); i++) {
        handleIsTerm(t, str->getElement(i));
    };
}

void CppGoal::handleIsStructure(BaseTarget* t, Structure* s) {
    if (s->getName() == idbase.identifierToID(".") && s->elementCount() == 2) {
        handleIsTerm(t, s->getElement(0));
        return;
    };
    handleIsStructureLoad(t, s);
    //Wichtig: diese Liste muss mit prologenvironment.cpp synchronisiert werden
    if (s->getName() == idbase.identifierToID("+") && s->elementCount() == 2) {
        oout << L"pl_math_add();";
    } else if (s->getName() == idbase.identifierToID("-") && s->elementCount() == 2) {
        oout << L"pl_math_sub();";
    } else if (s->getName() == idbase.identifierToID("*") && s->elementCount() == 2) {
        oout << L"pl_math_mul();";
    } else if (s->getName() == idbase.identifierToID("/") && s->elementCount() == 2) {
        oout << L"pl_math_div();";
    } else if (s->getName() == idbase.identifierToID("-") && s->elementCount() == 1) {
        oout << L"pl_math_neg();";
    } else if (s->getName() == idbase.identifierToID("+") && s->elementCount() == 1) {
        //oout << L"pl_math_sub();";
    } else if (s->getName() == idbase.identifierToID("//") && s->elementCount() == 2) {
        oout << L"pl_math_intdev();";
    } else if (s->getName() == idbase.identifierToID("rem") && s->elementCount() == 2) {
        oout << L"pl_math_rem();";
    } else if (s->getName() == idbase.identifierToID("mod") && s->elementCount() == 2) {
        oout << L"pl_math_mod();";
    } else if (s->getName() == idbase.identifierToID("integer") && s->elementCount() == 1) {
        oout << L"pl_math_integer();";
    } else if (s->getName() == idbase.identifierToID("float_fractional_part") && s->elementCount() == 1) {
        oout << L"pl_math_float_fractional_part();";
    } else if (s->getName() == idbase.identifierToID("float_integer_part") && s->elementCount() == 1) {
        oout << L"pl_math_float_integer_part();";
    } else if (s->getName() == idbase.identifierToID("float") && s->elementCount() == 1) {
        oout << L"pl_math_float();";
    } else if (s->getName() == idbase.identifierToID("/\\") && s->elementCount() == 2) {
        oout << L"pl_math_and();";
    } else if (s->getName() == idbase.identifierToID("\\/") && s->elementCount() == 2) {
        oout << L"pl_math_or();";
    } else if (s->getName() == idbase.identifierToID("#") && s->elementCount() == 2) {
        oout << L"pl_math_xor();";
    } else if (s->getName() == idbase.identifierToID("\\") && s->elementCount() == 1) {
        oout << L"pl_math_not();";
    } else if (s->getName() == idbase.identifierToID(">>") && s->elementCount() == 2) {
        oout << L"pl_math_shiftright();";
    } else if (s->getName() == idbase.identifierToID("<<") && s->elementCount() == 2) {
        oout << L"pl_math_shiftleft();";
    }

    oout_newline();
}

void CppGoal::perform(BaseTarget* t) {
    CUtiString out;
    this->output(out);
    oout <<L"// "<< out;
    if (target->SingleStep) {
        oout_newline();
        oout << L"pl_debug(L\"Goal: " << out << L"\");";

    };
    if (target->TexViewOutput) {
        oout_newline();
        oout << L"pl_step(L\"Goal: " << out << L"\");";
    };
    oout_newline();
    if (goal == gTerm) {

       if (dynamic_cast<Structure*>(getElement())) {
            Structure* s = (Structure*)getElement();
            BaseBuildInPredicate* pred = target->prog->getRegisterPredicate(s);

            if (s->getName() == idbase.identifierToID(L"=") && s->elementCount() == 2) {
                Term* t1 = (Term*)s->getElement(0);
                Term* t2 = (Term*)s->getElement(1);
                doUnify(t, t1, t2, NULL);
	    } else if (s->getName() == idbase.identifierToID(L"\\=") && s->elementCount() == 2) {
	       Term* t1 = (Term*)s->getElement(0);
	       Term* t2 = (Term*)s->getElement(1);
	       doUnify(t, t1, t2, NULL, true);
	    } else if (s->getName() == idbase.identifierToID(L"is") && s->elementCount() == 2) {
                Var* var = dynamic_cast<Var*>(s->getElement(0));
                Term* t2 = (Term*)s->getElement(1);
                handleIs(t, var, t2);
            } else if (s->getName() == idbase.identifierToID(L"repeat") && s->elementCount() == 0) {
                target->beginElement(0, false);
                oout << L"pl_choisePoint();";
                oout_newline();
                target->endElement(false);
            } else if (s->getName() == idbase.identifierToID(L"=:=") && s->elementCount() == 2) {
                handleIsTerm(t, s->getElement(0));
                handleIsTerm(t, s->getElement(1));
                oout << L"if (!pl_math_isEqual())";
                makeBacktracking(t);

            } else if (s->getName() == idbase.identifierToID(L"=\\=") && s->elementCount() == 2) {
                handleIsTerm(t, s->getElement(0));
                handleIsTerm(t, s->getElement(1));
                oout << L"if (!pl_math_isNonEqual())";
                makeBacktracking(t);

            } else if (s->getName() == idbase.identifierToID(L"<") && s->elementCount() == 2) {
                handleIsTerm(t, s->getElement(0));
                handleIsTerm(t, s->getElement(1));
                oout << L"if (!pl_math_isLesser())";
                makeBacktracking(t);

            } else if (s->getName() == idbase.identifierToID(L">") && s->elementCount() == 2) {
                handleIsTerm(t, s->getElement(0));
                handleIsTerm(t, s->getElement(1));
                oout << L"if (!pl_math_isGreater())";
                makeBacktracking(t);
            } else if (s->getName() == idbase.identifierToID(L"=<") && s->elementCount() == 2) {
                handleIsTerm(t, s->getElement(0));
                handleIsTerm(t, s->getElement(1));
                oout << L"if (!pl_math_isEqualLess())";
                makeBacktracking(t);
            } else if (s->getName() == idbase.identifierToID(L">=") && s->elementCount() == 2) {
                handleIsTerm(t, s->getElement(0));
                handleIsTerm(t, s->getElement(1));
                oout << L"if (!pl_math_isEqualGreater())";
                makeBacktracking(t);
            } else if (pred) {
                pred->performCode(t, s);
            } else {
                CppProgram* p = (CppProgram*)t->prog;
                bool hascode=false;
                UNIFYMAP unimap;
                FACTVECTOR facts;
                FACTVECTOR possiblefacts;
                bool inlinecode = false;
                if (!p->getPossiblePredicates(s->getName(), s->elementCount(), inlinecode, possiblefacts) ) {
                    error(L"Das Pr\"adikat wurde nicht gefunden.");
                    return;
                };
                if (factparent == NULL)
                    inlinecode = true;
                if (!inlinecode) {
                    callCodeSingle(t, s);
                } else {
                    for (int i = 0; i < possiblefacts.size(); i++) {
                        Fact* f = possiblefacts[i];
                        Structure* str = f->getHead();
                        str->changenamespace(VARADD);
                        if (str->unify(unimap, s)) {
                            facts.push_back(f);
                        };
                        str->changenamespace(-VARADD);
                        unimap.clear();
                    };
                    oout << L"// Possibilities: " <<facts.size();
                    oout_newline();
                    if (facts.size() == 0) {
                        error( L"Unification error, not succesful" );
                    };
                    if (facts.size() == 1 && multiheadgoal == false) {
                        //ToDo zusammenfassen
                        Fact* f = facts[0];
                        callCode(t, f, s);
                    } else {
                        int elementdepth;
                        if (factparent == NULL) {
                            //Multihead Goal
                            elementdepth = target->beginElement(owner->getHead()->elementCount(), true);
                        } else {
                            elementdepth = target->beginElement(owner->HeadVarsCount, true);
                        }
                        for (int i = 0; i < facts.size(); i++) {

                            target->createORCodeBegin(i, facts.size(), elementdepth);
                            Fact* f = facts[i];
                            callCode(t, f, s);
                            target->createORCodeEnd(i, facts.size(), elementdepth);

                        };
                        target->createORCodeFinalize(0, facts.size(), elementdepth);

                        target->endElement(true);
                        oout_newline();
                    };
                };

            };
       } else if (dynamic_cast<Var*>(getElement())) {
	  Var* v = dynamic_cast<Var*>(getElement());
	  oout << L"if (!pl_FreeCall((pl_HeapCell*)&" << getVarName(this, v->getName()) << "))";
	  makeBacktracking(t);
       }
        ;
    } else if (goal == gBody) {
        getElement()->perform(t);
    } else if (goal == gNotBody) {
        int elementdepth, elementdepth2;
        elementdepth = target->beginElement(owner->HeadVarsCount, true);

        target->createORCodeBegin(0, 2, elementdepth);
//        oout << L"pl_choisePoint()";
        oout_newline();

        elementdepth2 = target->beginElement(owner->HeadVarsCount, true);

        target->createANDCodeBegin(0, 2, elementdepth2);
        getElement()->perform(t);
        target->createANDCodeEnd(0, 2, elementdepth2);
        target->createANDCodeBegin(1, 2, elementdepth2);
        oout << L"pl_cut();";
        oout_newline();
        oout << L"pl_DoBacktracking();";
        oout_newline();
        oout << L"break;";
        oout_newline();
        target->createANDCodeEnd(1, 2, elementdepth2);
        target->createANDCodeFinalize(2, 2, elementdepth2);
        target->endElement(true);



        target->createORCodeEnd(0, 2, elementdepth);

        target->createORCodeBegin(1, 2, elementdepth);
        oout << L"//true";
        oout_newline();
        target->createORCodeEnd(1, 2, elementdepth);

        target->createORCodeFinalize(0, 2, elementdepth);
        target->endElement(true);
        oout_newline();

    };
}

CppFact::CppFact() {}
CppFact::~CppFact() {}

void CppFact::printHead(BaseTarget* t) {
    oout << L"(";
    map<PID, int>::iterator i;
    bool first = true;
    PID* hv = new PID[headvars.size()];
    for (i = headvars.begin(); i != headvars.end(); i++) {
       int pos = i->second;
       PID p = i->first;
       hv[pos] = p;
    };
    for (int j = 0; j < headvars.size(); j++) {
            if (!first)
                oout << L", ";
            first = false;
            PID id = hv[j];
            oout << L"pl_PrologVar & " << idname(id);
    };
    delete [] hv;
    oout << L")";
}
void CppFact::printMultiHead(BaseTarget* t) {
    oout << L"(";
    Structure* str = getHead();
    bool first = true;
    for (int i = 0; i < str->elementCount(); i++) {
        if (!first)
            oout << L", ";
        first = false;
	CUtiString s;
	s = L"A";
	s += i;
	PID id = idbase.identifierToID(s);
	
	oout << L"pl_PrologVar & " << idname(id);
    };
    oout << L")";
};

void CppFact::handleBodyVars(BaseTarget* t) {
    if (hasBodyVars) {
        //Hat eigene Variablen
        oout << L"struct pl_Stackframe_Struct {";
        oout_incdepth();
        oout_newline();

        map<PID, VarInfo>::iterator i;
        bool first = true;
        int varcount =0;
        for (i = Vars.begin(); i != Vars.end(); i++) {
            VarInfo &info = i->second;
            if (!info.headvar) {
                if (!first)
                    oout_newline();
                first = false;
                PID id = i->first;
                oout << L"pl_PrologVar " << idname(id) << L";";
                varcount++;
            }
        };
        oout_newline();
        oout << L"};";

        oout_decdepth();
        oout_newline();
        oout << L"pl_Stackframe_Struct* pl_stackframe;";
        oout_newline();
        oout << L"if (!pl_backtracking) {";
        oout_incdepth();
        oout_newline();
        //oout << L"pl_stackframe = new (pl_getHeapMem("<<varcount << L")) pl_Stackframe_Struct;";
	
	oout << L"pl_stackframe = (pl_Stackframe_Struct*)pl_getHeapMem("<<varcount << L");";
        oout_decdepth();
        oout_newline();
        oout << L"};";
        oout_newline();
    } else {

        oout << L"void* pl_stackframe = NULL;";


    };
    oout_newline();
}

void CppFact::printName(BaseTarget* t) {
    oout <<idname(getHead()->getName());
    if (singlefact == false) {
        oout << L"_Choise_";
        oout << getHead()->elementCount();
        oout << L"_";
        oout << factpos;
    };

};

void CppFact::printMultiNameHeader(BaseTarget* t) {
    oout << L"bool ";
    oout <<idname(getHead()->getName());

    printMultiHead(t);
    oout << L";";
    oout_newline();
    FactInfo fi;
    fi.name = getHead()->getName();
    fi.arity = getHead()->elementCount();
    //((CppProgram*)Program::getInstance())->registerProcs.push_back(fi);
}

void CppFact::printMultiNameBody(BaseTarget* t) {
   oout << L"bool " /*<< ((CppProgram*)t->prog)->progname.c_str() << L"::"*/;
    oout <<idname(getHead()->getName());
    printMultiHead(t);
    oout_newline();
    oout << L"{";
    oout_incdepth();
    oout_newline();
    oout << L"void* pl_stackframe = NULL;";
    oout_newline();
    Structure* mainstr = getHead();

    //InsertCode here
    CppStructure* str = new CppStructure();
    str->setName(mainstr->getName());
    for (int i = 0; i < mainstr->elementCount(); i++) {
        CppVar* var = new CppVar();
        CUtiString s;
        s = L"A";
        s += i;
        var->setName(idbase.identifierToID(s));
        str->addElement(var);
    };
    // int headvar = HeadVarsCount;
    //HeadVarsCount = mainstr->elementCount();
    CppGoal* goal = new CppGoal();
    goal->owner = this;
    goal->multiheadgoal = true;
    goal->setElement(str);
    goal->setGoal(gTerm);
    goal->perform(t);
    delete goal;
    //    oout << L"return !pl_backtracking;";
    oout_newline();
    oout_decdepth();
    oout_newline();
    oout << L"};";
    oout_newline();
    oout_newline();
    // HeadVarsCount = headvar;
}

void CppProgram::performDynamic_Dekl(BaseTarget* t, PID name, int arity) {
   FactElement fi;
   fi.info.name = name;
   fi.info.arity = arity;
   fi.Name = idname(name);
   registerProcs.push_back(fi);

   fi.info.name = name;
   fi.info.arity = arity;
   fi.Name = makeDynName(name, arity);
   registerDynProcs.push_back(fi);
    oout << L"extern pl_PredicateCollection ";
    oout << makeDynName(name, arity);
    oout << L";";
    oout_newline();
    oout << L"bool ";
    oout <<idname(name);

    printDynamic_Head(t, name, arity);
    oout << L";";
    oout_newline();
}
void CppProgram::performDynamic_Impl(BaseTarget* t, PID name, int arity) {
   oout << L"pl_PredicateCollection ";
   oout << makeDynName(name, arity);
   oout << L";";
   oout_newline();
   
   oout << L"bool "/* << progname.c_str() << L"::"*/;
    oout <<idname(name);
    printDynamic_Head(t, name, arity);
    oout_newline();
    oout << L"{";
    oout_incdepth();
    oout_newline();
    oout << L"void* pl_stackframe = NULL;";

    int k = 0;
    oout_newline();
    oout << L"int pl_pos" << k << L";";
    oout_newline();
    oout << L"bool pl_exit" << k << L" = false;";
    oout_newline();
    oout << L"pl_begin(pl_pos" << k << L", (void*&)pl_stackframe, " << arity << L");";

    oout_newline();
    oout << L"while(!pl_exit" << k << L") {";

    oout_incdepth();
    oout_newline();
    oout << L"if (pl_pos0 < pl_dyn_count(";
    oout <<  makeDynName(name, arity);
    oout  << L")-1) {";
    oout_incdepth();
    oout_newline();
    oout << L"pl_choisePoint();";
    oout_newline();
    oout << L"if (!pl_dyn_prove(";
    oout <<  makeDynName(name, arity);
    oout << L", pl_pos0))";
    //makeBacktracking(t);
    oout << L"{";
    oout_incdepth();
    oout_newline();
    oout << L"pl_DoBacktracking();";
    oout_newline();
    oout << L"continue;";
    oout_decdepth();
    oout_newline();
    oout << L"};";
    oout_newline();
    oout << L"pl_exit0 = true;";
    oout_decdepth();
    oout_newline();

    oout << L"} else ";
    oout << L"if (pl_pos0 == pl_dyn_count(";
    oout <<  makeDynName(name, arity);
    oout << L")-1) {";
    oout_incdepth();
    oout_newline();
    oout << L"if (!pl_dyn_prove(";

    oout <<  makeDynName(name, arity);
    oout << L", pl_pos0))";

    makeBacktracking(t);


    oout_newline();
    oout << L"pl_exit0 = true;";
    oout_decdepth();
    oout_newline();
    oout << L"} else {";
    oout_incdepth();
    oout_newline();
    oout << L"pl_pos0 = -1;";
    oout_newline();
    oout << L"pl_exit0 = true;";
    oout_newline();
    oout << L"pl_DoBacktracking();";
    oout_newline();
    oout << L"break;";
    oout_decdepth();
    oout_newline();
    oout << L"}";
    //elementdepth = target->beginElement(arity);
    /*for (int i = 0; i < facts.size(); i++)
    {

    target->createORCodeBegin(i, facts.size(), elementdepth);
    Fact* f = facts[i];
    callCode(t, f, s);
    target->createORCodeEnd(i, facts.size(), elementdepth);

    };*/
    //target->createORCodeFinalize(0, 100, elementdepth);


    oout_decdepth();
    /*oout_newline();
    oout << L"}";*/
    oout_newline();
    oout << L"}";
    oout_newline();
    oout << L"return pl_end(pl_pos" << k << L", (void*&)pl_stackframe);";


    //target->endElement();
    // oout_newline();

    //oout_newline();
    // oout << L"return !pl_backtracking;";
    oout_newline();
    oout_decdepth();
    oout_newline();
    oout << L"};";
    oout_newline();
    oout_newline();
}
void CppProgram::printDynamic_Head(BaseTarget* t, PID name, int arity) {
    oout << L"(";

    bool first = true;
    for (int i = 0; i < arity; i++) {
        if (!first)
            oout << L", ";
        first = false;
        oout << L"pl_PrologVar & A" << i;
    };
    oout << L")";
};


void CppForeignFact::perform(BaseTarget* t) {
   if (foreign) {
      return;
   };
   if (first) {
      
      first = false;
      if (factpos == 0) {
	 
	 FactElement fi;
	 fi.info.name = getHead()->getName();
	 fi.info.arity = getHead()->elementCount();
	 fi.Name = CName;
	 ((CppProgram*)Program::getInstance())->registerProcs.push_back(fi);
      };
   };
};

void CppFact::perform(BaseTarget* t) {
   if (foreign) {
      return;
   };
    if (t->prog->isDynamic(getHead()->getName(), getHead()->elementCount())) {
        return;
    };
    if (!searched) {
        searchVars();

        searched = true;
	if (factpos == 0) {
	  // FactInfo fi;
	   //fi.name = getHead()->getName();
	   //fi.arity = getHead()->elementCount();
	   FactElement fi;
	   fi.info.name = getHead()->getName();
	   fi.info.arity = getHead()->elementCount();
	   fi.Name = idname(fi.info.name);
	   ((CppProgram*)Program::getInstance())->registerProcs.push_back(fi);
	};
        //Vordeklaration
        if (!singlefact && factpos == 0)
            printMultiNameHeader(t);
	if (!getBody()) {
	   if (singlefact)
	      printMultiNameHeader(t);
            return;
	}
        oout << L"bool ";
        printName(t);
        printHead(t);
        oout << L";";
    } else {
        if (!singlefact && factpos == 0)
            printMultiNameBody(t);
	if (!getBody()) {
	   if (singlefact)
	      printMultiNameBody(t);
            return;
	}
	oout << L"bool " /*<< ((CppProgram*)t->prog)->progname.c_str() << L"::"*/;
        printName(t);
        printHead(t);
        oout_newline();
        oout << L"{";
        oout_incdepth();
        oout_newline();
        handleBodyVars(t);
        oout_newline();

        if (target->SingleStep) {
            CUtiString out;
            this->output(out);
            oout << L"pl_debug(L\"Enter: " << out << L"\");";
            oout_newline();
        };

        getBody()->perform(t);
        if (target->SingleStep) {
            CUtiString out;
            this->output(out);
            // oout << L"wcout << \"Exit: " << out << L"\" << endl;";
            oout_newline();
        };
        //      oout << L"return !pl_backtracking;";
        oout_newline();
        oout_decdepth();
        oout_newline();
        oout << L"};";
    };
    oout_newline();
}
CppForeignFact::CppForeignFact() {first = true;}
CppForeignFact::~CppForeignFact() {}
CppProgram::CppProgram() : Program() {
    progname = L"PrologProgram";
    RegisterCppBuildIn(this);
}
CppProgram::~CppProgram() {}

enum DynCommand {dcUnifyValue, dcUnifyVariable, dcGetStructure, dcGetInteger, dcGetFloat,
                 dcUnifyValueARG, dcUnifyVariableARG, dcGetStructureARG, dcGetIntegerARG, dcGetFloatARG};

struct UnifyCommand {
    DynCommand command;
    /// @todo machmal ist das Argument nicht nötig
    short Xi;
    short Arg;
    union {
        float real;
        int integer;
        struct {
            PID name;
            int arity;
        };
    };
};
class MemReserve {
public:
    map<Term*, int> hcell;
    set
        <Term*> newvarset;
    int xi;
    MemReserve() {
        xi = 1;
    };
    bool isFirstVar(Term* c) {
        if (newvarset.find(c) == newvarset.end()) {
            newvarset.insert(c);
            return false;
        } else {
            return true;
        };
    };
    void reserve(Term* c, int &i) {
        i = xi;
        hcell[c] = i;
    };
    void read(Term* c, int &i) {
        i = hcell[c];
    };
};
typedef vector<UnifyCommand> DYNAMICPREDICATE;

void get_code_pre(Term* c, DYNAMICPREDICATE &pred, MemReserve* res);
void get_code(Term* c, DYNAMICPREDICATE &pred, MemReserve* res);

void get_code_arg(Term* c, DYNAMICPREDICATE &pred, MemReserve* res) {
    int Xi;
    Term* current;
    UnifyCommand com;
    Structure* c2 = dynamic_cast<Structure*>(c);
//    assert(c2 != NULL);
    int arity = c2->elementCount();
    for (int i = 0; i < arity; i++) {
        c = c2->getElement(i);
        com.Arg = i;
        if (dynamic_cast<Var*>(c)) {
            if (res->isFirstVar(c)) {
                res->reserve(c, Xi);
                com.command = dcUnifyVariableARG;
                com.Xi = Xi;
                pred.push_back(com);
                //		 ASSERTDEBUG(wcout << L"assert: UnifyVariable X" << Xi << " A" << com.Arg <<endl);
            } else {
                res->read(c, Xi);
                com.command = dcUnifyValueARG;
                com.Xi = Xi;
                pred.push_back(com);
                //ASSERTDEBUG(wcout << L"assert: UnifyValue X" << Xi << " A" << com.Arg <<endl);
            };
        } else if (dynamic_cast<RealNumber*>(c)) {
            com.command = dcGetFloatARG;
            com.real = dynamic_cast<RealNumber*>(c)->getValue();
            pred.push_back(com);
            //ASSERTDEBUG(wcout << L"assert: GetFloat " << com.real << " A" << com.Arg <<endl);
        } else if (dynamic_cast<IntNumber*>(c)) {
            com.command = dcGetIntegerARG;
            com.integer = dynamic_cast<IntNumber*>(c)->getValue();
            pred.push_back(com);
            //ASSERTDEBUG(wcout << L"assert: GetInteger " << com.real << " A" << com.Arg <<endl);
        } else if (dynamic_cast<Structure*>(c)) {
            Structure* str = (Structure*)c;
            res->reserve(c, Xi);

            com.command = dcGetStructureARG;
            com.name = str->getName();
            com.arity = str->elementCount();
            com.Xi = Xi;
            int arity = str->elementCount();
            pred.push_back(com);
            //ASSERTDEBUG(wcout << L"assert: GetStructure " << pl_idToName(pl_getname(com.str)) << L"/" << arity << " A" << com.Arg <<endl);
            for (int i = 0; i < arity; i++) {
                current = str->getElement(i);
                get_code_pre(current,pred, res);
            };
            for (int i = 0; i < arity; i++) {
                current = str->getElement(i);
                get_code(current,pred, res);
            };
        };

    };
};


void get_code(Term* c, DYNAMICPREDICATE &pred, MemReserve* res) {
    int Xi;
    Term* current;
    UnifyCommand com;
    if (dynamic_cast<Structure*>(c)) {
        Structure* str = (Structure*)c;
        res->read(c, Xi);

        com.command = dcGetStructure;
        com.name = str->getName();
        com.arity = str->elementCount();
        com.Xi = Xi;
        pred.push_back(com);
        int arity = str->elementCount();

        for (int i = 0; i < arity; i++) {
            current = str->getElement(i);
            get_code_pre(current,pred, res);
        };


        for (int i = 0; i < arity; i++) {
            current = str->getElement(i);
            get_code(current,pred, res);
        };
    };
};

void get_code_pre(Term* c, DYNAMICPREDICATE &pred, MemReserve* res) {
    int Xi;
    //   pl_HeapCell* current;
    UnifyCommand com;
    com.Arg = -1;
    if (dynamic_cast<Var*>(c)) {
        if (res->isFirstVar(c)) {
            res->reserve(c, Xi);
            com.command = dcUnifyVariable;
            com.Xi = Xi;
            pred.push_back(com);
            //ASSERTDEBUG(wcout << L"assert: UnifyVariable X" << Xi <<endl);
        } else {
            res->read(c, Xi);
            com.command = dcUnifyValue;
            com.Xi = Xi;
            pred.push_back(com);
            //ASSERTDEBUG(wcout << L"assert: UnifyValue X" << Xi <<endl);
        };
    } else if (dynamic_cast<RealNumber*>(c)) {


        com.command = dcGetFloat;
        com.real = dynamic_cast<RealNumber*>(c)->getValue();
        pred.push_back(com);
        //ASSERTDEBUG(wcout << L"assert: GetFloat " << com.real <<endl);
    } else if (dynamic_cast<IntNumber*>(c)) {

        com.command = dcGetInteger;
        com.integer = dynamic_cast<IntNumber*>(c)->getValue();
        pred.push_back(com);
        //ASSERTDEBUG(wcout << L"assert: GetInteger " << com.integer <<endl);
    } else if (dynamic_cast<Structure*>(c)) {
        res->reserve(c, Xi);
        com.command = dcUnifyVariable;
        com.Xi = Xi;
        pred.push_back(com);
        //ASSERTDEBUG(wcout << L"assert: UnifyVariable X" << Xi <<endl);
    };
}

const UnifyCommand com[1] = { {
                                  dcUnifyValue, 0
                              }
                            };

void CppProgram::addDynPredicates(BaseTarget* t) {
    DYNAMICSET::iterator it;
    for (it = dynamicfacts.begin(); it != dynamicfacts.end(); it++) {
        FactInfo fr = *it;
        oout << L"// " << idrealname(fr.name) << "\\" << fr.arity;
        oout_newline();
        FACTVECTOR pos;
        bool inlinecode;
        getPossiblePredicates(fr.name, fr.arity, inlinecode, pos);
        for (int i = 0; i < pos.size(); i++) {
            MemReserve res;
            DYNAMICPREDICATE dyn;
            Fact* f = pos[i];

            get_code_arg(f->getHead(), dyn, &res);

            oout << L"{";
            oout_incdepth();
            oout_newline();
            /// @todo nur eine Variable verwenden
            oout << L"pl_UnifyCommand ucom[" << dyn.size() << "];";
            for (int i = 0; i < dyn.size(); i++) {

                UnifyCommand c = dyn[i];
                switch (c.command) {
                case dcUnifyValue: {
                        oout << "ucom["<<i<<"].command=pl_dcUnifyValue;";
                        oout_newline();
                    }
                    ;
                    break;
                case dcUnifyVariable: {
                        oout << "ucom["<<i<<"].command=pl_dcUnifyVariable;";
                    }
                    ;
                    break;
                case dcGetStructure: {
                        oout
                        << "ucom["<<i<<"].command=pl_dcGetStructure;"
                        <<" ucom["<<i<<"].str = pl_s(PLN_" << idname(c.name) << L", " << c.arity << L")" << L";";
                        oout_newline();
                    };
                    break;
                case dcGetInteger: {
                        oout << "ucom["<<i<<"].command=pl_dcGetInteger; ucom["<<i<<"].integer = " << c.integer << L";";
                        oout_newline();
                    }
                    ;
                    break;
                case dcGetFloat: {
                        oout << "ucom["<<i<<"].command=pl_dcGetFloat; ucom["<<i<<"].real = " << c.real << L";";
                        oout_newline();
                    }
                    ;
                    break;
                case dcUnifyValueARG: {
                        oout << "ucom["<<i<<"].command=pl_dcUnifyValueARG;";
                        oout_newline();
                    }
                    ;
                    break;
                case dcUnifyVariableARG: {
                        oout << "ucom["<<i<<"].command=pl_dcUnifyVariableARG;";
                        oout_newline();
                    }
                    ;
                    break;

                case dcGetStructureARG: {
                        oout
                        << "ucom["<<i<<"].command=pl_dcGetStructureARG;"
                        <<" ucom["<<i<<"].str = pl_s(PLN_" << idname(c.name) << L", " << c.arity << L")" << L";";
                        oout_newline();
                    };
                    break;
                case dcGetIntegerARG: {
                        oout << "ucom["<<i<<"].command=pl_dcGetIntegerARG; ucom["<<i<<"].integer = " << c.integer << L";";
                        oout_newline();
                    }
                    ;
                    break;
                case dcGetFloatARG: {
                        oout << "ucom["<<i<<"].command=pl_dcGetFloatARG; ucom["<<i<<"].real = " << c.real << L";";
                        oout_newline();
                    }
                    ;
                    break;
                };
                oout << "ucom["<<i<<"].Xi = " << c.Xi << L";";
                oout_newline();
                oout << "ucom["<<i<<"].Arg = " << c.Arg << L";";
                oout_newline();
            };
            oout << L"pl_dyn_fixed_add(" <<makeDynName(fr.name, fr.arity) << L", " << "ucom, " << dyn.size() << ");";


            oout_decdepth();
            oout_newline();
            oout << L"}";
            oout_newline();
        }
    };
}
void CppProgram::addNameEnum(BaseTarget* t, TNameMode mode) {
    // oout << L"enum TPL_NAME {";
    bool first = true;

    for (int i = 0; i < idbase.Names.size(); i++) {
        IdentID &s = idbase.Names[i];
	if (!s.foreign) {

            switch (mode) {
            case nmHeader: {
                    oout << L"extern pl_Name PLN_" << idname(i) << L";";
                }
                ;
                break;
            case nmCpp: {
                    oout << L"pl_Name PLN_" << idname(i) << L";";
                }
                ;
                break;
            case nmRegister: {
                    oout << L"pl_registerName(L\"" << idrealname(i) << L"\", PLN_"<< idname(i) << L");";
                }
                ;
                break;
            };
            oout_newline();
        };
    };
    //oout << L"};" << endl << endl;
}
void CppProgram::addIncludeHeaders(BaseTarget* t) {
    set<CUtiString> headerset;
    for (int i = 0; i < elementCount(); i++) {
        Fact* f = getElement(i);
        if (dynamic_cast<ForeignFact*>(f)) {
            ForeignFact* f2 = dynamic_cast<ForeignFact*>(f);
            CUtiString h = f2->Source;
            if (headerset.find(h) == headerset.end()) {
                oout << L"#include \"" << h << L".h\"";
                oout_newline();
                headerset.insert(h);
            };
        };
    };
}
void CppProgram::ForeignPredicate(CUtiString Atom, CUtiString CName, int arity, CUtiString Header) {
    CppForeignFact* fact = new CppForeignFact();
    fact->Source = Header;
    fact->CName = CName;
    fact->stype = stHeader;
    fact->directcall = true;
    CppStructure* str = new CppStructure();
    str->setName(idbase.identifierToID(Atom));
    for (int i = 0; i < arity; i++) {
        CUtiString s = L"A";
        s += i;
        CppVar* v = new CppVar();
        v->setName(idbase.identifierToID(s));
        str->addElement(v);
    };
    fact->setHead(str);
    fact->searchVars();
    addElement(fact);
};

void CppProgram::ForeignPredicate(CUtiString Atom, CUtiString CName, CallInfo* cinfo, int ccount, CUtiString Header) {
    /*CppForeignFact* fact = new CppForeignFact();
    fact->Source = Header;
    fact->CName = CName;
    fact->stype = stHeader;
    fact->directcall = false;
    CppStructure* str = new CppStructure();
    str->setName(idbase.identifierToID(Atom));
    for (int i = 0; i < ccount; i++) {
        fact->parameter.push_back(cinfo[i]);
        CUtiString s = L"A";
        s += i;
        CppVar* v = new CppVar();
        v->setName(idbase.identifierToID(s));
        str->addElement(v);
    };
    fact->setHead(str);
    fact->searchVars();
   addElement(fact);*/
}

bool CppProgram::getPossiblePredicates(PID name, int arity, bool& inlinecode, FACTVECTOR& pos) {
   FactInfo fi;
    fi.arity = arity;
    fi.name = name;
   if (dynamicfacts.find(fi) != dynamicfacts.end()) {
      if (factinfo.find(fi) != factinfo.end()) pos = factinfo[fi];
      inlinecode = false;
      return true;
   };
    
    if (factinfo.find(fi) == factinfo.end())
        return false;
    pos = factinfo[fi];
    if (pos.size() > 4/* || dynamicfacts.find(fi) != dynamicfacts.end()*/) {
        inlinecode = false;
        return true;
    };
    if (pos.size() > 0) {
       for (int i = 0; i < pos.size(); i++) {
	  if (pos[i]->foreign && dynamic_cast<ForeignFact*>(pos[i])==NULL) {
	     inlinecode = false;
	     return true;
	  }
       };
    };
    inlinecode = true;
    return true;
};

void CppProgram::loadModule(CUtiString name)
{

   CUtiString libname;
   bool found = false;
   for (int i = 0; i < libdirs.size(); i++) {
      CUtiString n = libdirs.at(i);
      n += L"/";
      n += name;
      n += L".module";
     // wcout << n.c_str() << endl;
      if (FileExists(n.c_str())) {
         found = true;
         libname = libdirs.at(i);
         libname += L"/";
         libname +=  name;
      };
   };
   if (!found) {  
      wcout << L"Das Modul '" << name << "' wurde nicht gefunden." << endl;
      exit(2);
      return;
   }
   
   Module* m = new Module();
   m->Name = libname;
   m->Name.ExtractFileName();
   m->Path = libname;
   modules.Add(m);
   CUtiString n = libname;
   n += L".module";
   CFileStream* str = new CFileStream(n.c_str(), S_READ);
   int count = 0;
   int id;
   str->ReadInteger(id);
   str->ReadInteger(count);
   map<int, int> oldtonewmap;
   CUtiString nname;

   int newid;
   for (int i = 0; i < count; i++) {
      str->ReadInteger(id);
      ReadStringWide(*str, nname);
      newid = idbase.identifierToID(nname, true);
      oldtonewmap[id] = newid;
   };
   
   str->ReadInteger(count);
   int arity;
   int strname;
   for (int i = 0; i < count; i++) {
      str->ReadInteger(strname);
      str->ReadInteger(arity);
      strname = oldtonewmap[strname];
      vector<Term*> t;
      for (int j = 0; j <arity; j++) {
	 CUtiString n = L"A";
	 n += i;
	 t.push_back(plc_var(idbase.identifierToID(name)));
      };
      plc_factadd(plc_strN(strname, t), NULL, true);
   };
   
   str->ReadInteger(count);
   int v;
   for (int i = 0; i < count; i++) {
   
      CppForeignFact* fact = new CppForeignFact();
      fact->foreign = true;
      str->ReadInteger(strname);
      str->ReadInteger(arity);
      strname = oldtonewmap[strname];
      ReadStringWide(*str, fact->CName);
      //wcout << fact->CName << endl;
      ReadStringWide(*str, fact->Source);
      str->ReadBoolean(fact->directcall);
      str->ReadInteger(v);
      fact->stype = (TSourceType)v;
      int paramcount;
      str->ReadInteger(paramcount);
      for (int i = 0; i < paramcount; i++) {
	 CallInfo info;
	 str->ReadInteger(v);
	 info.type = (TCallInfoType)v;
	 fact->parameter.push_back(info);
      };
      CppStructure* str = new CppStructure();
      str->setName(strname);
      for (int i = 0; i < arity; i++) {
	 CUtiString s = L"A";
	 s += i;
	 CppVar* var = new CppVar();
	 var->setName(idbase.identifierToID(s));
	 str->addElement(var);
      };
      fact->setHead(str);
      fact->searchVars();
      addElement(fact);
   };
   delete str;
}

void CppProgram::performModule(CUtiString name)
{
   CFileStream* str = new CFileStream(name.c_str(), S_WRITE);
   int count = 0;
   for (int i = 0; i < idbase.Names.size(); i++) {
      IdentID &s = idbase.Names[i];
      if (!s.foreign) {
	 count++;
      };
   };
   int id = 100;
   str->WriteInteger(id);
   str->WriteInteger(count);
   for (int i = 0; i < idbase.Names.size(); i++) {
      IdentID &s = idbase.Names[i];
      if (!s.foreign) {
	 str->WriteInteger(i);
	 WriteStringWide(*str, s.name);
      };
   };
   count = 0;
   for (int i = 0; i < elementCount(); i++) {
      Fact* f = getElement(i);
      if (f->getHead() && !f->foreign && (!(dynamic_cast<CppForeignFact*>(f))))
	 count++;	
   };
   str->WriteInteger(count);
   for (int i = 0; i < elementCount(); i++) {
      Fact* f = getElement(i);
      if (f->getHead() && !f->foreign && (!(dynamic_cast<CppForeignFact*>(f))) ) {
	 str->WriteInteger(f->getHead()->getName());
	 str->WriteInteger(f->getHead()->elementCount());
      };
   };
   
   count = 0;
   for (int i = 0; i < elementCount(); i++) {
      Fact* f = getElement(i);
      if (f->getHead() && !f->foreign && dynamic_cast<CppForeignFact*>(f))
	 count++;	
   };
   str->WriteInteger(count);
   for (int i = 0; i < elementCount(); i++) {
      Fact* f = getElement(i);
      if (f->getHead() && !f->foreign && dynamic_cast<CppForeignFact*>(f)) {
	 CppForeignFact* fact = (CppForeignFact*)f;
	 str->WriteInteger(fact->getHead()->getName());
	 str->WriteInteger(fact->getHead()->elementCount());
	 WriteStringWide(*str, fact->CName);
	 WriteStringWide(*str, fact->Source);
	 str->WriteBoolean(fact->directcall);
	 int v = (int)fact->stype;
	 str->WriteInteger(v);
	 str->WriteInteger(fact->parameter.size());
	 for (int i = 0; i < fact->parameter.size(); i++) {
	    v = (int)fact->parameter[i].type;
	    str->WriteInteger(v);
	 };
	 /*struct CallInfo
	 {
	    TCallInfoType type;
	 };

	 class ForeignFact : public Fact
	 {
	    public:
	       CUtiString Source;
	       CUtiString CName;
	       TSourceType stype;
	       bool directcall;
	       vector<CallInfo> parameter;*/
      };
   };
   delete str;
   
}

void CppProgram::perform(BaseTarget* t) {
    t->prog = this;
    parseDirectCalls(t);
    createConstraintRules();
    //CUtiString str;
    //output(str);
    //oout << endl << str.c_str() << endl;
    oout << L"//Generated Code:" << endl;
    //    oout << L"#include \"PrologClass.h\"" << endl;
    //oout << L"#include <iostream>" << endl;
    //oout << L"#include <stack>" << endl;
    //oout << L"#include <vector>" << endl;
    //oout << L"using namespace std;" << endl;
    oout << L"#ifndef __" << progname.c_str() << "_h"<< endl;
    oout << L"#define __" << progname.c_str() << "_h"<< endl;
    oout << L"#include \"prologenvironment.h\"" << endl ;
    oout << L"#include \"prolognames.h\"" << endl << endl;
    for (int i = 0; i< modules.count; i++) {
       Module* m = (Module*)modules[i];
       oout << L"#include \"" << m->Name << ".h\"" << endl;
    };
    
    oout << endl;
    oout << L"namespace PrologSystem {" << endl;
    addNameEnum(t, nmHeader);
    //oout << L"#include \"testheader.h\"" << endl << endl;
    //addStrInfo(t);
    //oout << L"void pl_RegisterNames();" << endl << endl;

    //oout << L"class " << progname.c_str() << L"" << endl;
    //oout << L"{" << endl;
    //oout << L"public:";
   // oout_incdepth();
    oout_newline();
    oout << L"void pl_initModule_" << progname.c_str() << L"();";
    oout_newline();
    //oout << L"void pl_RegisterDynPredicates();";
    //oout_newline();
    
    DYNAMICSET::iterator it;
    for (it = dynamicfacts.begin(); it != dynamicfacts.end(); it++) {
        FactInfo fr = *it;
        performDynamic_Dekl(t, fr.name, fr.arity);
    };
    
    for (int i = 0; i < elementCount(); i++) {
        Fact* f = getElement(i);
        if (f->getHead())
            f->perform(t);
    };
    //oout_decdepth();
    oout_newline();
    //oout << L"};" << endl;
    oout << L"};" << endl;
    oout << endl;
    
    oout << L"#endif"<< endl;
    
    target->setCPP();
    addIncludeHeaders(t);

    oout << L"namespace PrologSystem {" << endl;
    //  oout << L"#include \"testimplementation.cpp\"" << endl << endl;
    addNameEnum(t, nmCpp);

   /* oout << L"void pl_RegisterNames()" << endl;
    oout << L"{";
    oout_incdepth();
    oout_newline();
    addNameEnum(t, nmRegister);
    oout_decdepth();
    oout_newline();
    oout << L"}" << endl << endl;*/
    
    oout << L"void pl_initModule_" << progname.c_str() << L"()"<<endl;
    oout << L"{";
    oout_incdepth();
    oout_newline();
    oout << L"static bool loaded = false;";
    oout_newline();
    oout << L"if (loaded) return;";
    oout_newline();
    oout << L"loaded = true;";
    oout_newline();
    for (int i = 0; i< modules.count; i++) {
       Module* m = (Module*)modules[i];
       oout << L"pl_initModule_" << m->Name << "();";
       oout_newline();
    };
    addNameEnum(t, nmRegister);
    addDynPredicates(t);
    for (int i = 0; i < registerProcs.size(); i++) {
       FactElement fi = registerProcs[i];
       //(bool (*) (pl_PrologVar &))
       oout << L"pl_RegisterStatic(PLN_" << idname(fi.info.name) << ", " << fi.info.arity << ", (void*)((bool (*) (";
for (int i = 0; i < fi.info.arity; i++) {
    oout << L"pl_PrologVar &";
   if (fi.info.arity-1 != i)
     oout << L", ";
};

      oout << L"))" << fi.Name << L"));";
       oout_newline();
       
    };
    registerProcs.clear();
    for (int i = 0; i < registerDynProcs.size(); i++) {
       FactElement fi = registerDynProcs[i];
       
       oout << L"pl_RegisterDynamic(PLN_" << idname(fi.info.name) << ", " << fi.info.arity << ", &" << fi.Name << ");";
       oout_newline();
       
    };
    registerDynProcs.clear();
    oout_decdepth();
    oout_newline();
    oout << L"}" << endl << endl;
    /*oout << L"" << progname.c_str() << L"::" << progname.c_str() << L"()" << endl;
    oout << L"{";
    oout_incdepth();
    oout_newline();
    oout << L"pl_RegisterDynPredicates();";
    oout_newline();
    oout_decdepth();
    oout_newline();
    oout << L"}" << endl << endl;

    oout << L"void " << progname.c_str() << L"::pl_RegisterDynPredicates()" << endl;
    oout << L"{";
    oout_incdepth();
    oout_newline();
    addDynPredicates(t);
    oout_decdepth();
    oout_newline();
    oout << L"}" << endl << endl;*/

    for (it = dynamicfacts.begin(); it != dynamicfacts.end(); it++) {
        FactInfo fr = *it;
        performDynamic_Impl(t, fr.name, fr.arity);
    };
    for (int i = 0; i < elementCount(); i++) {
        Fact* f = getElement(i);
        if (f->getHead())
            f->perform(t);
    };
    oout << L"};" << endl;
    //oout << L"#include \"testcode.cpp\"" << endl << endl;
}
};
}
;
