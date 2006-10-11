#ifndef __WAMENGINE__
#define __WAMENGINE__

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

#include "codecontainer.h"

#include <set>
#include <map>

using namespace std;

namespace UtiProlog {
namespace WAM {

class WAMTarget : public BaseTarget {
public:
    Interpreter::CodeContainer* container;
    WAMTarget();
    ~WAMTarget();
    void allocate(int N);
    void deallocate();
    void call(PID name,int arity);
    int* try_me_else();
    int* retry_me_else(int* i);
    void trust_me(int* i);
    void addLabel(PID name, int arity);
    void unifyValue(int Xi, int arg);
    void unifyVariable(int Xi, int arg);
    void unifyValue(int Xi);
    void unifyVariable(int Xi);
    void unifyValueY(int Xi, int arg);
    void unifyVariableY(int Xi, int arg);
    void unifyValueY(int Xi);
    void unifyVariableY(int Xi);
    void get_integer(int value);
    void get_real(float value);
    void get_integer(int value, int arg);
    void get_real(float value, int arg);
    void get_structure(PID name, int arity, int xi);
    void get_structureA(PID name, int arity, int arg);
    void put_structure(PID name, int arity, int xi);
    void set_variable(int Xi);
    void set_value(int Xi);
    void set_variableY(int Xi);
    void set_valueY(int Xi);
    void put_int(int value);
    void put_real(float value);
    void put_int(int value, int arg);
    void put_real(float value, int arg);
    void put_variable(int Xi, int arg);
    void put_value(int Xi, int arg);
    void put_variableY(int Xi, int arg);
    void put_valueY(int Xi, int arg);
    void put_structureA(PID name, int arity, int arg);
};

class WAMVar : public Var {

public:

    WAMVar();
    ~WAMVar();
    void perform(BaseTarget* t);
};

class WAMIntNumber : public IntNumber {

public:
    WAMIntNumber();
    ~WAMIntNumber();
    void perform(BaseTarget* t);

};

class WAMRealNumber : public RealNumber {

public:
    WAMRealNumber();
    ~WAMRealNumber();
    void perform(BaseTarget* t);

};

class WAMStructure : public Structure {

public:

    WAMStructure();
    ~WAMStructure();
    void perform(BaseTarget* t);
};

/*class WAMList : public List
{

   public:

      WAMList();
      ~WAMList();
      void perform(BaseTarget* t);
};*/

class WAMBody : public Body {

public:

    WAMBody();
    ~WAMBody();
    void perform(BaseTarget* t);

};

class WAMBodyPart : public BodyPart {
public:
    bool needBacktracking();
    WAMBodyPart();
    ~WAMBodyPart();
    void perform(BaseTarget* t);
};

class WAMGoal : public Goal {

public:

    WAMGoal();
    ~WAMGoal();
    void perform(BaseTarget* t);
};

class WAMFact : public Fact {
public:
    WAMFact();
    ~WAMFact();
    void perform(BaseTarget* t);
};



class WAMProgram : public Program {
public:
    Fact* currentfact;
    map<Term*, int> hcell;
    map<PID, int> vcell;
    set
        <PID> newvarset;
    int xi;

    bool isFirstVar(PID c);
    void reserve(Term* c, int &i);
    void read(Term* c, int &i);
    void reserve(PID c, int &i);
    void read(PID c, int &i);

    CUtiString progname;
    WAMProgram();
    ~WAMProgram();
    void perform(BaseTarget* t);
    void compile(WAMTarget* t, FactInfo f, FACTVECTOR & vec);
    void generateClause(WAMTarget* t, Fact* f);
    void generateElement(WAMTarget* t, Goal* g);
    void generateElementEqual(WAMTarget* t, Structure*s);
    void generateElementCall(WAMTarget* t, Structure*s);
    void initvars();
    void getcode(WAMTarget* t, Term* term, int arg);
    void getcode(WAMTarget* t, Term* term);
    void getcode_pre(WAMTarget* t, Term* term);

    void getcode_str(WAMTarget* t, Structure* term, int arg);
    void getcode_str(WAMTarget* t, Structure* term);
    void getcode_pre_str(WAMTarget* t, Structure* term);

    void getcode_newvar(WAMTarget* t, Var* term, int arg);
    void getcode_pre_newvar(WAMTarget* t, Var* term);

    void getcode_oldvar(WAMTarget* t, Var* t, int arg);
    void getcode_pre_oldvar(WAMTarget* t, Var* term);

    void getcode_int(WAMTarget* t, IntNumber* t, int arg);
    void getcode_pre_int(WAMTarget* t, IntNumber* t);

    void getcode_real(WAMTarget* t, RealNumber* t, int arg);
    void getcode_pre_real(WAMTarget* t, RealNumber* t);
    
    void putcode(WAMTarget* t, Term* term);
    void putcode(WAMTarget* t, Term* term, int arg);
    void putcode_str(WAMTarget* t, Structure* term, int arg);
    void putcode_newvar(WAMTarget* t, Var* term, int arg);
    void putcode_oldvar(WAMTarget* t, Var* term, int arg);
    void putcode_int(WAMTarget* t, IntNumber* term, int arg);
    void putcode_real(WAMTarget* t, RealNumber* term, int arg);
    
    void putcode_str(WAMTarget* t, Structure* term);
    void putcode_pre(WAMTarget* t, Term* term);
    void putcode_pre_str(WAMTarget* t, Structure* term);
    void putcode_post(WAMTarget* t, Term* term);
    void putcode_post_str(WAMTarget* t, Structure* term);
    void putcode_post_newvar(WAMTarget* t, Var* term);
    void putcode_post_oldvar(WAMTarget* t, Var* term);
    void putcode_post_int(WAMTarget* t, IntNumber* term);
    void putcode_post_real(WAMTarget* t, RealNumber* term);
};
};
};


#endif
