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
#ifndef PROLOGSYSTEMPROLOGENVIRONMENT_H
#define PROLOGSYSTEMPROLOGENVIRONMENT_H

#include "prolognames.h"
#include <cstdlib>
using namespace std;
//#include <iostream>

namespace PrologSystem {

extern int pl_firsttop;

class pl_PrologEnvironment;

extern pl_PrologEnvironment* pl_env;

enum pl_HeapType {pl_htReference, pl_htReal, pl_htInteger, pl_htStructure};

union pl_HeapCell;

typedef int pl_int;
typedef double pl_real;

struct pl_PrologVar
{
   pl_HeapType type; 
   pl_HeapCell* reference;
};

typedef unsigned int pl_PSTRINFO;

struct pl_StructureInfo
{
   pl_HeapType type;
   pl_PSTRINFO str;
};

struct pl_IntegerInfo
{
   pl_HeapType type;
   int number;
};


struct pl_RealInfo
{
   pl_HeapType type;
   float number;
};


union pl_HeapCell 
{
   pl_HeapType type;
   pl_PrologVar var;
   pl_StructureInfo str;
   pl_IntegerInfo integer;
   pl_RealInfo real;
};

 enum pl_DynCommand {pl_dcUnifyValue, pl_dcUnifyVariable, pl_dcGetStructure, pl_dcGetInteger, pl_dcGetFloat,
    pl_dcUnifyValueARG, pl_dcUnifyVariableARG, pl_dcGetStructureARG, pl_dcGetIntegerARG, pl_dcGetFloatARG};

struct pl_UnifyCommand {
   pl_DynCommand command;
   /// @todo machmal ist das Argument nicht nötig
   short Xi;
   short Arg;
   union {
      pl_real real;
      pl_int integer;
      struct {
	 pl_PSTRINFO str;
      };
   };
};


class pl_PredicateCollection {
public:
   void* predicates;
   void clear();
   void remove(int i);
   pl_PredicateCollection();
   ~pl_PredicateCollection();
   int arity; //wird gesetzt durch RegisterDynamic
   pl_Name name;
};

const pl_Name pl_intern_plus=0;
const pl_Name pl_intern_sub=1;
const pl_Name pl_intern_mul=2;
const pl_Name pl_intern_div=3;
const pl_Name pl_intern_intdiv=4;
const pl_Name pl_intern_rem=5;
const pl_Name pl_intern_mod=6;
const pl_Name pl_intern_integer=7;
const pl_Name pl_intern_float_integer_part=8;
const pl_Name pl_intern_float_fractional_part=9;
const pl_Name pl_intern_float=10;
const pl_Name pl_intern_or=11;
const pl_Name pl_intern_and=12;
const pl_Name pl_intern_xor=13;
const pl_Name pl_intern_not=14;
const pl_Name pl_intern_shiftleft=15;
const pl_Name pl_intern_shiftright=16;
const pl_Name pl_intern_list=17;
const pl_Name pl_intern_emptylist=18;
const pl_Name pl_intern_cut=19;

enum pl_NumberType {pl_ntInteger, pl_ntReal};



struct pl_StackElement {
   pl_NumberType type;
   union {
      pl_real real;
      pl_int integer;
   };
};

#define pl_getarity(a) (a >> 24)
#define pl_getname(a) (a & 0xFFFFFF)
#define pl_s(name, arity) ((((int)name)& 0xFFFFFF) | (arity << 24))

pl_HeapCell* pl_deref(pl_HeapCell* address);
void pl_bind(pl_PrologVar* var, pl_HeapCell* adr);
void pl_reduceVarTrail(int s);
bool pl_loadVariable(pl_PrologVar& V, int Xi);
bool pl_get_structure(pl_PSTRINFO s, int Xi);
bool pl_get_structure_ARG(pl_PSTRINFO s, int Xi);
bool pl_get_integer(int i, int Xi);
bool pl_get_real(float f, int Xi);
bool pl_get_integer(int i);
bool pl_get_real(float f);
bool pl_get_integer_ARG(int i, int a);
bool pl_get_real_ARG(float f, int a);
bool pl_put_integer_ARG(int f, int a);
bool pl_put_real_ARG(float f, int a);
bool pl_loadArgVar(int argument, int Xi);
bool pl_loadArgVal(int argument, int Xi);
bool pl_loadArgVariable(int argument, pl_PrologVar& V);
bool pl_loadArgValue(int argument, pl_PrologVar& V);
pl_PrologVar& pl_getVoid();
bool pl_unify_void();
bool pl_unify_variable(pl_PrologVar& V, int Xi);
bool pl_unify_value(pl_PrologVar& V, int Xi);
bool pl_unify_variable(pl_PrologVar& V);
bool pl_unify_value(pl_PrologVar& V);
bool pl_unify_variable(int Xi);
bool pl_unify_value(int Xi);
bool pl_unify_variableARG(int Xi);
bool pl_unify_valueARG(int Xi);
bool pl_unify_variable_ARG(int Xi, int a);
bool pl_unify_value_ARG(int Xi, int a);
bool pl_testunify(pl_HeapCell* a1, pl_HeapCell* a2);
bool pl_unify(pl_HeapCell* a1, pl_HeapCell* a2);
int pl_compare(pl_HeapCell* a1, pl_HeapCell* a2);
void* pl_getHeapMem(int amount);
void pl_takeTopElement();
void pl_takeTopElement(bool useframe);
void pl_generateBacktrackingTree();
   //void trail_bind(CPrologVar* var);
void pl_begin(int &pos);
bool pl_end(int &pos);
void pl_begin(int &pos, void*&it, int argcount);
bool pl_end(int &pos, void*&it);
void pl_choisePoint();
void pl_cut();
void pl_DoBacktracking();
void pl_TakeElement(bool useend);
void pl_clearTrail();
void pl_trail_bind(pl_PrologVar* var);
pl_PrologVar* pl_getVar();
void pl_print(pl_HeapCell* c);
void pl_print(pl_PrologVar* c);
void pl_print(pl_PrologVar& c);

void pl_debuginit();
void pl_debugfree();
void pl_debug(wchar_t* text);
void pl_step(wchar_t* text);

//Dynamic Predicates
int pl_dyn_count(pl_PredicateCollection& coll);
bool pl_dyn_prove(pl_PredicateCollection& coll, int i);
bool pl_dyn_prove(pl_PredicateCollection& coll, int i, pl_HeapCell* c);
enum pl_dyn_addtype {pl_addfirst, pl_addlast};
void pl_dyn_fixed_add(pl_PredicateCollection& coll, const pl_UnifyCommand* unify, int count);
void pl_dyn_add(pl_PredicateCollection& coll, pl_HeapCell* c, pl_dyn_addtype t);
bool pl_dyn_retract(pl_PredicateCollection & coll, pl_HeapCell* c);
void pl_dyn_retractall(pl_PredicateCollection & coll, pl_HeapCell* c);
void pl_dyn_remove(pl_PredicateCollection& coll, int i);
void pl_dyn_clear(pl_PredicateCollection& coll);

//Foreign interface
bool pl_call_getInt(pl_PrologVar* Var, pl_int *i);
bool pl_call_unifyInt(pl_PrologVar* Var, pl_int value);
bool pl_call_getFloat(pl_PrologVar* Var, pl_real *i);
bool pl_call_unifyFloat(pl_PrologVar* Var, pl_real value);


//Mathematik
void pl_math_pushInt(pl_int value);
void pl_math_pushReal(pl_real value);
void pl_math_pushVar(pl_PrologVar& c);
void pl_math_calcStructure(pl_HeapCell* str);
void pl_math_pushCell(pl_HeapCell* c);
bool pl_math_popVar(pl_PrologVar& c);
bool pl_math_isEqual();
bool pl_math_isNonEqual();
bool pl_math_isGreater();
bool pl_math_isLesser();
bool pl_math_isEqualGreater();
bool pl_math_isEqualLess();
void pl_math_add();
void pl_math_sub();
void pl_math_mul();
void pl_math_div();
void pl_math_intdiv();
void pl_math_neg();
void pl_math_rem();
void pl_math_mod();
void pl_math_integer();
void pl_math_float_integer_part();
void pl_math_float_fractional_part();
void pl_math_float();
void pl_math_or();
void pl_math_and();
void pl_math_xor();
void pl_math_not();
void pl_math_shiftleft();
void pl_math_shiftright();
//Funktionen
/*void pl_math_abs();
void pl_math_sign();
void pl_math_gcd();
void pl_math_min();
void pl_math_max();
void pl_math_msb();
void pl_math_round();
void pl_math_truncate();
void pl_math_floor();
void pl_math_ceiling();
void pl_math_sin();
void pl_math_cos();
void pl_math_tan();
void pl_math_cot();
void pl_math_sinh();
void pl_math_cosh();
void pl_math_tanh();
void pl_math_coth();
void pl_math_asin();
void pl_math_acos();
void pl_math_atan();
void pl_math_atan2();
void pl_math_acot();
void pl_math_acot2();
void pl_math_asinh();
void pl_math_acosh();
void pl_math_atanh();
void pl_math_acoth();
void pl_math_sqrt();
void pl_math_log();
void pl_math_log2();
void pl_math_exp();
void pl_math_inf();
void pl_math_nan();*/

//Temporäre Elemente
//extern pl_UnifyMode pl_unifymode;
extern pl_PrologVar* pl_ARG[256];
extern pl_HeapCell* pl_X[256];
extern pl_HeapCell* pl_S;

/*extern stack<pl_CTrailElement*> pl_trail;
extern stack<pl_PrologVar*> pl_vartrail;
extern stack<int*> pl_currentselector;
extern vector<pl_ChoiseElement> pl_exitenterstack;*/


#define pl_MathStackSize 64
/*extern pl_StackElement pl_mathstack[pl_MathStackSize];
extern int pl_mathstackcount;

extern int pl_exitenterstackpos;
extern int* pl_toppos;
extern int pl_firsttop;
extern void** pl_localframe;*/
extern bool pl_backtracking;
//Ladbare Elemente
extern unsigned int pl_H;
extern pl_HeapCell* pl_Heap;
extern int pl_maxheapsize; 

void pl_Initialize();
void pl_Free();

void pl_CreateEnv();
void pl_FreeEnv();


void pl_RegisterStatic(pl_Name n, int arity, void* func);
void pl_RegisterDynamic(pl_Name n, int arity, pl_PredicateCollection* coll);
bool pl_FreeCall(pl_HeapCell* cell);
void pl_initengine();
pl_PredicateCollection* pl_getCollection(pl_HeapCell* cell);
pl_PredicateCollection* pl_getCollection(pl_Name n, int arity);
/**
@author Michael Staud
*/
class pl_PrologEnvironment{
public:
   unsigned int H;
   pl_HeapCell* Heap;
   int maxheapsize;
   pl_PrologEnvironment();
   ~pl_PrologEnvironment();
    void LoadEnv();
    void SaveEnv();

};

}

#endif
