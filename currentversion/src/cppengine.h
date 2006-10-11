#ifndef __CPPENGINE__
#define __CPPENGINE__

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

#include "prologengine.h"

#include <map>

using namespace std;

namespace UtiProlog {
namespace Cpp {

CUtiString getVarName(BaseEngine* eng, PID name);

class CppTarget : public BaseTarget {
public:
    int depth;
    int element;
    int beginElement(int argcount, bool loop);
    void endElement(bool loop);
    void createORCodeBegin(int i, int factssize, int elementdepth);
    void createORCodeEnd(int i, int factssize, int elementdepth);
    void createORCodeFinalize(int i, int factssize, int elementdepth);
    void createANDCodeBegin(int i, int factssize, int elementdepth);
    void createANDCodeEnd(int i, int factssize, int elementdepth);
    void createANDCodeFinalize(int i, int factssize, int elementdepth);
    CppTarget(wostream* stcpp, wostream* stheader);
    ~CppTarget();
    bool SingleStep;
    bool TexViewOutput;
    wostream* strcpp;
    wostream* strheader;
    void setCPP();
    void setHeader();
    wostream* str;
    void newline();
    void incdepth();
    void decdepth();
}
;

class CppAllocCodeHelper  : public AllocCodeHelper {
public:
    CppAllocCodeHelper(BaseTarget* _t);
    virtual void get_structure(PID name, int arity, int Xi, bool permanent);
    virtual void unify_variable(int Xi, bool permanent);
    virtual void unify_value(int Xi, bool permanent);
    virtual void put_structure(PID name, int arity, int Xi, bool permanent);
    virtual void set_variable(int Xi, bool permanent);
    virtual void set_value(int Xi, bool permanent);
    virtual void put_variable(int Xn, bool permanent, int Ai);
    virtual void put_value(int Xn, bool permanent, int Ai);
    virtual void put_structure(PID name, int arity, int Xn, bool permanent, int Ai);
    virtual void get_variable(int Xn, bool permanent, int Ai);
    virtual void get_value(int Xn, bool permanent, int Ai);
    virtual void get_structure(PID name, int arity, int Xn, bool permanent, int Ai);
    void unify_variable(BaseEngine* eng, PID localvar);
    void unify_value(BaseEngine* eng, PID localvar);
    void unify_variable(BaseEngine* eng, PID localvar, int Xi);
    void unify_value(BaseEngine* eng, PID localvar, int Xi);
    void unify_void();

    void put_integer(int number);
    void get_integer(int number);
    void put_real(float number);
    void get_real(float number);
    void get_integer(int number, int Xi);
    void get_real(float number, int Xi);
    HEADVARS* unifyFact;
   // HEADVARS* arguments;
    bool*argused;

};


class CppVar : public Var {

public:

    CppVar();
    ~CppVar();
    void perform(BaseTarget* t);
};

class CppIntNumber : public IntNumber {

public:
    CppIntNumber();
    ~CppIntNumber();
    void perform(BaseTarget* t);

};

class CppRealNumber : public RealNumber {

public:
    CppRealNumber();
    ~CppRealNumber();
    void perform(BaseTarget* t);

};

class CppStructure : public Structure {

public:

    CppStructure();
    ~CppStructure();
    void perform(BaseTarget* t);
};

/*  class CppList : public List
  {
 
  public:
 
    CppList();
    ~CppList();
    void perform(BaseTarget* t);
};*/

class CppBody : public Body {

public:

    CppBody();
    ~CppBody();
    void perform(BaseTarget* t);

};

class CppBodyPart : public BodyPart {
public:
    bool needBacktracking();
    CppBodyPart();
    ~CppBodyPart();
    void perform(BaseTarget* t);
};

class CppGoal : public Goal {

public:
   bool multiheadgoal;
    CppGoal();
    ~CppGoal();
    void perform(BaseTarget* t);
    void doUnify(BaseTarget* t, Term* t1, Term* t2, HEADVARS* f, bool unequal=false);
    bool needUnify(UNIFYMAP& unimap);
    void callCode(BaseTarget* t, Fact* f, Structure* s);
    void callCodeSingle(BaseTarget* t, Structure* s);
    void handleIs(BaseTarget* t, Var* var, Term* term);
    void handleIsTerm(BaseTarget* t, Term* term);
    void handleIsStructure(BaseTarget* t, Structure* s);
    void handleIsStructureLoad(BaseTarget* t, Structure* str);
};

class CppFact : public Fact {
public:
    void printHead(BaseTarget* t);
    void printName(BaseTarget* t);
    void handleBodyVars(BaseTarget* t);
    void printMultiNameHeader(BaseTarget* t);
    void printMultiNameBody(BaseTarget* t);
    void printMultiHead(BaseTarget* t);
public:
    CppFact();
    ~CppFact();
    void perform(BaseTarget* t);

};
class CppForeignFact : public ForeignFact {
public:
   bool first;
    CppForeignFact();
    ~CppForeignFact();
    void perform(BaseTarget* t);
};

enum TNameMode {nmHeader, nmCpp, nmRegister};

struct FactElement {
   FactInfo info;
   CUtiString Name;
};

class CppProgram : public Program {
public:
   vector<FactElement> registerProcs;
   vector<FactElement> registerDynProcs;
public:
    void addNameEnum(BaseTarget* t, TNameMode mode);
    void addDynPredicates(BaseTarget* t);
    CppProgram();
    ~CppProgram();

    /**
     * Creates a list of possible candidates which can
     * be unified with a structure name(a(1),..a(arity)).
     * @param name The name of the structure
     * @param arity The arity of the structure
     * @param inlinecode Returns true if the call can be inlined
     * @param pos a list of possible facts
     * @return Returns true if there are possible candidates
     */
    bool getPossiblePredicates(PID name, int arity, bool& inlinecode, FACTVECTOR& pos);
    void perform(BaseTarget* t);
    void performModule(CUtiString name);
    void loadModule(CUtiString name);
    void performDynamic_Dekl(BaseTarget* t, PID name, int arity);
    void performDynamic_Impl(BaseTarget* t, PID name, int arity);
    void printDynamic_Head(BaseTarget* t, PID name, int arity);
    void ForeignPredicate(CUtiString Atom, CUtiString CName, CallInfo* cinfo, int ccount, CUtiString Header);
    void ForeignPredicate(CUtiString Atom, CUtiString CName, int arity, CUtiString Header);
    void addIncludeHeaders(BaseTarget* t);
};
};
};


#endif
