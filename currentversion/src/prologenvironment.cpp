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
#include "prologenvironment.h"
#include "prolognames.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include <map>
#include <set>
//#include <stack>
#include <vector>
#include <iostream>

#define ASSERTDEBUG(a) 
//#define DEBUGMODE
using namespace std;

namespace PrologSystem
{
   class pl_CTrailElement;
   class pl_CBeginElementFrame;
   enum pl_UnifyMode {pl_umRead, pl_umWrite};
  // enum pl_FactType {pl_Static};
   const int PDLMAX=64;
   pl_HeapCell* PDL[PDLMAX];
   int PDLSize=0;
#define STACK_PUSH(a, el) /*assert(a ## Size < a ## MAX);*/ a[a ## Size] = el; a ## Size++;
#define STACK_TOP(a, top) top = a[a ## Size-1];
#define STACK_POP(a) /*assert(a ## Size > 0);*/ a ## Size--;
#define STACK_SIZE(a) a ## Size
#define STACK_CLEAR(a) a ## Size = 0;
#define DEKL_STACK(type, a, size) const int a ## MAX = size; type a[ a ## MAX]; int a ## Size = 0;

/*#define STACK_PUSH(a, el) a.push(el);
#define STACK_TOP(a, t) t = a.top();
#define STACK_POP(a) a.pop();
#define STACK_SIZE(a) a.size()
#define DEKL_STACK(type, a, size) stack<type> a;*/

   struct pl_FactElement
   {
	 pl_Name name;
	 int arity;
	// pl_FactType type;
	 void* data;
   };
   struct pl_FactInfo
   {
      pl_Name name;
      int arity;
   };

   __inline int operator==(const pl_FactInfo& One, const pl_FactInfo &Other)
   {
      return (One.name == Other.name) && (One.arity == Other.arity);
   }

   __inline int operator!=(const pl_FactInfo& One, const pl_FactInfo &Other)
   {
      return !(One == Other);
   }


   __inline int operator<(const pl_FactInfo& One, const pl_FactInfo &Other)
   {
   //if (One == Other) return false;
      if (One.name < Other.name) return true;
      if (One.name != Other.name) return false;
      if (One.arity < Other.arity) return true;
      return false;
   };


   /*enum pl_ChoiseType {pl_ctEnterFrame, pl_ctEnter, pl_ctExit};
   struct pl_ChoiseElement
   {
      pl_ChoiseType type;
      int ParentPos;
      int oldFrame;
      pl_CBeginElementFrame* begin;
};*/
  pl_PrologEnvironment* pl_env;

  pl_UnifyMode pl_unifymode;
  pl_PrologVar* pl_ARG[256];
  pl_HeapCell* pl_X[256];
  pl_HeapCell* pl_S;
  
  //stack<pl_CTrailElement*> pl_trail;
  DEKL_STACK(pl_CTrailElement*, pl_trail,65000);
  //stack<pl_CBeginElementFrame*> pl_elementstack;
  DEKL_STACK(pl_CBeginElementFrame*, pl_elementstack, 10000);
  //stack<pl_PrologVar*> pl_vartrail;
  
  DEKL_STACK(pl_PrologVar*, pl_vartrail, 65000);
  DEKL_STACK(int*, pl_currentselector, 10000);
//stack<int*> pl_currentselector;
   class pl_MemoryStack {
   public:
       static const int MAXSIZE = 100000;
       char c[100000];
       int size;
       pl_MemoryStack()
       {
         size = 0;
       };
       inline void* getMem(int count){
           int s = size;
//           assert(s+count <= MAXSIZE);
           size += count;
           return &c[s];
       }
       inline void* freeMem(void* mem) {
          size = ((int)mem - (int)c);
       //   assert(size >= 0);
      //    assert(size < MAXSIZE);
       };
       void clear()
       {
           size = 0;
       }

   };
   pl_MemoryStack pl_stack;
  //vector<pl_ChoiseElement> pl_exitenterstack;
  //int pl_exitenterstackpos;
  int* pl_toppos;
  int pl_firsttop;
  void** pl_localframe;
  void* pl_nextlocalframe;
  bool pl_backtracking;
  bool pl_ignorenext;
  typedef map<pl_FactInfo, pl_FactElement> pl_DatabaseMap;
  typedef map<pl_FactInfo, pl_PredicateCollection*> pl_DynDatabaseMap;
  pl_DynDatabaseMap pl_globaldyndatabase;
  pl_DatabaseMap pl_globaldatabase;
  //Ladbare Elemente
  unsigned int pl_H;
  pl_HeapCell* pl_Heap;
  int pl_maxheapsize;

  pl_StackElement pl_mathstack[pl_MathStackSize];
  int pl_mathstackcount;
#ifdef DEBUGMODE
  wofstream pl_dout;
#endif
  void pl_initCurrentSelector()
  {
     STACK_CLEAR(pl_currentselector);
     pl_toppos = &pl_firsttop;
     STACK_PUSH(pl_currentselector, pl_toppos);
  }
  void pl_initengine()
  {
     pl_H = 0;
     pl_stack.clear();
     
     STACK_CLEAR(pl_vartrail);
     STACK_CLEAR(pl_elementstack);
     STACK_CLEAR(pl_trail);
     pl_initCurrentSelector();
     
     PDLSize = 0;
  }
  void pl_RegisterInternNames()
  {
    pl_registerForceName(L"+", pl_intern_plus);
    pl_registerForceName(L"-", pl_intern_sub);
    pl_registerForceName(L"*", pl_intern_mul);
    pl_registerForceName(L"/", pl_intern_div);
    pl_registerForceName(L"//", pl_intern_intdiv);
    pl_registerForceName(L"rem", pl_intern_rem);
    pl_registerForceName(L"mod", pl_intern_mod);
    pl_registerForceName(L"integer", pl_intern_integer);
    pl_registerForceName(L"float_integer_part", pl_intern_float_integer_part);
    pl_registerForceName(L"float_fractional_part", pl_intern_float_fractional_part);
    pl_registerForceName(L"float", pl_intern_float);
    pl_registerForceName(L"/\\", pl_intern_or);
    pl_registerForceName(L"\\/", pl_intern_and);
    pl_registerForceName(L"#", pl_intern_xor);
    pl_registerForceName(L"\\", pl_intern_not);
    pl_registerForceName(L"<<", pl_intern_shiftleft);
    pl_registerForceName(L">>", pl_intern_shiftright);
    pl_registerForceName(L".", pl_intern_list);
    pl_registerForceName(L"[]", pl_intern_emptylist);
    pl_registerForceName(L"!", pl_intern_cut);
  };

  void pl_Initialize()
  {
    pl_backtracking = false;
    pl_ignorenext = false;
    pl_firsttop = 0;
    
    pl_S = NULL;
//    pl_exitenterstackpos = 0;
    pl_mathstackcount = 0;
   // pl_toppos = &pl_firsttop;
    //STACK_PUSH(pl_currentselector, pl_toppos);
    pl_initCurrentSelector();
    pl_RegisterInternNames();
    pl_CreateEnv();
    pl_debuginit();
    
  }

  void pl_Free()
  {
     pl_debugfree();
    pl_clearTrail();
    pl_FreeEnv();
  }

  void pl_CreateEnv()
  {
    pl_env = new pl_PrologEnvironment();
    pl_env->LoadEnv();
  }
  void pl_FreeEnv()
  {
    delete pl_env;
  }
  enum pl_TrailType {pl_ttBeginElement, pl_ttBeginElementFrame, pl_ttEndElement, pl_ttEndElementFrame, pl_ttChoisePoint};
  /*struct pl_TrailElement
  {
    union {
       struct EndElement {
           int parent;
       };
       struct BeginElementFrame {
           int argcount;
	   pl_PrologVar** ARGS;
       };
       struct EndElementFrame {
           int parent;
	   int oldheapsize;
	   pl_CBeginElementFrame* begin;
       };
       struct ChoisePoint {
           int pos;
	   int oldheapsize;
	   int vartrailsize;
       };
    }
  };*/
  class pl_CTrailElement
  {
     public:
	//pl_CTrailElement();
	virtual void undo();
        virtual pl_TrailType getType()=0;
  };

  class pl_CBeginElement : public pl_CTrailElement
  {
     public:
	pl_CBeginElement();
	void undo();
        pl_TrailType getType(){return pl_ttBeginElement;};
  };
  /*inline pl_CTrailElement* createBeginElement()
  {
     return new pl_CBeginElement();
  } */
  class pl_CEndElement : public pl_CTrailElement
  {
     public:
	int parent;
	pl_CEndElement(int p);
	~pl_CEndElement();
	void undo();
        pl_TrailType getType(){return pl_ttEndElement;};
  };/*
  inline pl_CEndElement* createEndElement(int p)
  {

  };*/

  class pl_CBeginElementFrame : public pl_CTrailElement
  {
     public:
	//int oldheapsize;
	int argcount;
	pl_PrologVar** ARGS;
	pl_CBeginElementFrame(/*int currentframesize,*/ int _argcount);
	~pl_CBeginElementFrame();
	void undo();
        pl_TrailType getType(){return pl_ttBeginElementFrame;};
  };
  class pl_CEndElementFrame : public pl_CTrailElement
  {
     public:
	int parent;
	int oldheapsize;
	pl_CBeginElementFrame* begin;
	pl_CEndElementFrame(int p, int currentframesize, pl_CBeginElementFrame* _begin);
	~pl_CEndElementFrame();
	void undo();
        pl_TrailType getType(){return pl_ttEndElementFrame;};
  };

  class pl_CChoisePoint : public pl_CTrailElement
  {
     public:
	int pos;
	int oldheapsize;
	int vartrailsize;
	pl_CChoisePoint(int p, int currentframesize, int _vartrailsize);
	~pl_CChoisePoint();
	void undo();
       pl_TrailType getType(){return pl_ttChoisePoint;};
  };

  class pl_DynamicPredicate {
	public:
  // pl_DynamicPredicate(){};
  // ~pl_DynamicPredicate();
	   vector<pl_UnifyCommand> commands;
     };

/*  pl_CTrailElement::pl_CTrailElement()
  {}*/

  void pl_CTrailElement::undo()
  {}

  pl_CBeginElement::pl_CBeginElement()
  {
    // wcout << L"BeginElement added" << endl;
  }

  void pl_CBeginElement::undo()
  {
    
    /*pl_ChoiseElement el;
    el.type = pl_ctExit;
    el.oldFrame = 0;
    el.ParentPos = 0;
     pl_exitenterstack.push_back(el);*/
     *pl_toppos = -1;
  };


  pl_CEndElement::pl_CEndElement(int p)
  {
    parent = p;
    //wcout << L"EndElement added("<< p << L")" << endl;
  }

  pl_CEndElement::~pl_CEndElement()
  {}

  void pl_CEndElement::undo()
  {

    /*pl_ChoiseElement el;
    el.type = pl_ctEnter;
    el.oldFrame = 0;
    el.ParentPos = parent;
    pl_exitenterstack.push_back(el);
    */
     *pl_toppos = parent;
  }


  pl_CBeginElementFrame::pl_CBeginElementFrame(/*int currentframesize,*/ int _argcount)
  {
    //oldheapsize = currentframesize;
    argcount = _argcount;
    if (argcount)
    {
      ARGS = new (pl_stack.getMem(sizeof(pl_PrologVar*)*argcount)) pl_PrologVar*[argcount];
      for (int i = 0; i < argcount; i++)
      {
        ARGS[i] = pl_ARG[i];
      };
    };
    //wcout << L"BeginElementFrame(" << oldheapsize << L")" << endl;
  }

  pl_CBeginElementFrame::~pl_CBeginElementFrame()
  {
    if (argcount)
      delete [] ARGS;
  }

  void pl_CBeginElementFrame::undo()
  {
     /*
    pl_ChoiseElement el;
    el.type = pl_ctExit;
    el.oldFrame = 0;
    el.ParentPos = 0;
    pl_exitenterstack.push_back(el);
     */
     *pl_toppos = -1;

  };


  pl_CEndElementFrame::pl_CEndElementFrame(int p, int currentframesize, pl_CBeginElementFrame* _begin)
  {

    parent = p;
    oldheapsize = currentframesize;
    begin = _begin;
    //wcout << L"EndElementFrame(" << parent << L")" << endl;
  }

  pl_CEndElementFrame::~pl_CEndElementFrame()
  {}

  void pl_CEndElementFrame::undo()
  {

    /*pl_ChoiseElement el;
    el.type = pl_ctEnterFrame;
    el.oldFrame = oldheapsize;
    el.ParentPos = parent;
    el.begin = begin;
    pl_exitenterstack.push_back(el);
    */
     
     pl_nextlocalframe = &pl_Heap[oldheapsize];
     *pl_toppos = parent;
     if (begin)
     {
	STACK_PUSH(pl_elementstack, begin);
	for (int i = 0; i <begin->argcount; i++)
	{
	   pl_ARG[i] = begin->ARGS[i];
	};
     };
  }

  pl_CChoisePoint::pl_CChoisePoint(int p, int currentframesize, int _vartrailsize)
  {
    pos = p;
    oldheapsize = currentframesize;
    vartrailsize = _vartrailsize;
#ifdef DEBUGMODE
   // pl_dout << L"ChoisePoint added("<< p << L" pl_Heap: " << oldheapsize << L")  \\\\" << endl;
#endif

  }

  pl_CChoisePoint::~pl_CChoisePoint()
  {}

  void pl_CChoisePoint::undo()
  {
    
    pl_H = oldheapsize;  //Kann man sofort setzen
    pl_reduceVarTrail(vartrailsize);
    /*pl_ChoiseElement el;
    el.type = pl_ctEnter;
    el.oldFrame = 0;
    el.ParentPos = pos+1;
    pl_exitenterstack.push_back(el);*/
    *pl_toppos = pos+1;

  }
  
  typedef vector<pl_DynamicPredicate*> DYNPRED;

  void pl_PredicateCollection::clear()
  {
     for (int i = 0; i < ((DYNPRED*)predicates)->size(); i++)
    {
       delete (*((DYNPRED*)predicates))[i];
    };
    ((DYNPRED*)predicates)->clear();
  }

  void pl_PredicateCollection::remove(int i)
  {
     DYNPRED::iterator it = ((DYNPRED*)predicates)->begin();
    it += i;
    if (((DYNPRED*)predicates)->end() != it)
    {
       ((DYNPRED*)predicates)->erase(it);
    };
  }

  pl_PredicateCollection::pl_PredicateCollection()
  {
     predicates = new DYNPRED();
  }

  pl_PredicateCollection::~pl_PredicateCollection()
  {
     clear();
     delete ((DYNPRED*)predicates);
  }

  int pl_dyn_count(pl_PredicateCollection& coll)
  {
     DYNPRED* p1 = (DYNPRED*)coll.predicates;
     int count = p1->size();
     return count;
  }
  bool pl_dyn_retract(pl_PredicateCollection & coll, pl_HeapCell* c)
  {
     int oldHeapSize = pl_H;
     int oldVarSize = STACK_SIZE(pl_vartrail);
     
     for (int i = 0; i < ((DYNPRED*)coll.predicates)->size(); i++) {
	if (pl_dyn_prove(coll, i, c)) {

	   pl_dyn_remove(coll, i);
	   return true;
	};
	
	pl_reduceVarTrail(oldVarSize);
	pl_H = oldHeapSize;
	
	
     };
     
     return false;
  }
  void pl_dyn_retractall(pl_PredicateCollection & coll, pl_HeapCell* c)
  {
     /// @todo: das geht in O(n) nicht in O(n^2)
      int oldHeapSize = pl_H;
     int oldVarSize = STACK_SIZE(pl_vartrail);
     do {
	bool res = pl_dyn_retract(coll, c);
	pl_reduceVarTrail(oldVarSize);
	pl_H = oldHeapSize;
	if (!res) return;
     } while(true);
   //  while (pl_dyn_retract(coll, c)) {};
  };
  bool pl_dyn_prove(pl_PredicateCollection& coll, int i, pl_HeapCell* c)
  {
     pl_HeapCell* v = pl_deref(c);
     if (v->type ==pl_htReference) {
	pl_Heap[pl_H].str.type = pl_htStructure;
	pl_Heap[pl_H].str.str =  pl_s(coll.name, coll.arity);
	pl_bind((pl_PrologVar*)v, &pl_Heap[pl_H]);
	pl_H++;
	for (int i = 0; i < coll.arity;i++) {
	   pl_Heap[pl_H].type = pl_htReference;
	   pl_Heap[pl_H].var.reference = (pl_HeapCell*)&pl_Heap[pl_H];
	   pl_ARG[i] = (pl_PrologVar*)&pl_Heap[pl_H];
	   pl_H++;
	};
     } else if (v->type ==pl_htStructure){
	pl_FactInfo fi;
	fi.name = pl_getname(v->str.str);
	fi.arity = pl_getarity(v->str.str);
	for (int i = 0; i < fi.arity; i++) {
	   v++;
	   pl_ARG[i] = (pl_PrologVar*)v;
	};
     } else {
	return false;
     };
     return pl_dyn_prove(coll, i);
  }
  bool pl_dyn_prove(pl_PredicateCollection& coll, int i)
  {
//     assert(i >= 0 && i < ((DYNPRED*)coll.predicates)->size());
     DYNPRED* p1 = (DYNPRED*)coll.predicates;
    pl_DynamicPredicate* pred = (*p1)[i];
    for (int i = 0; i < pred->commands.size(); i++)
    {
      pl_UnifyCommand &com = pred->commands[i];
      switch (com.command)
      {
      case pl_dcUnifyValue:
        {
	   if (!pl_unify_value(com.Xi)) return false;
        }
        ; break;
	 case pl_dcUnifyVariable:
        {
	   if (!pl_unify_variable(com.Xi)) return false;
        }
        ; break;
	 case pl_dcGetStructure:
        {
	   if (!pl_get_structure(com.str, com.Xi)) return false;
        }
        ; break;
	 case pl_dcGetInteger:
        {
	   if (!pl_get_integer(com.integer)) return false;
        }
        ; break;
	 case pl_dcGetFloat:
        {
	   if (!pl_get_real(com.real)) return false;
        }
        ; break;
	 case pl_dcUnifyValueARG:
        {
	   if (!pl_unify_value_ARG(com.Xi, com.Arg)) return false;
        }
        ; break;
	 case pl_dcUnifyVariableARG:
        {
	   if (!pl_unify_variable_ARG(com.Xi, com.Arg)) return false;
        }
        ; break;
	 case pl_dcGetStructureARG:
        {
	   if (!pl_get_structure_ARG(com.str, com.Arg)) return false;
        }
        ; break;
	 case pl_dcGetIntegerARG:
        {
	   if (!pl_get_integer_ARG(com.integer, com.Arg)) return false;
        }
        ; break;
	 case pl_dcGetFloatARG:
        {
	   if (!pl_get_real_ARG(com.real, com.Arg)) return false;
        }
        ; break;
      };
    };
    return true;
  }

  class pl_MemReserve
  {
  public:
    map<pl_HeapCell*, int> hcell;
    set<pl_HeapCell*> newvarset;
    int xi;
    pl_MemReserve()
    {
      xi = 1;
    };
    bool isFirstVar(pl_HeapCell* c)
    {
      if (newvarset.find(c) == newvarset.end())
      {
        newvarset.insert(c);
        return false;
      }
      else
      {
        return true;
      };
    };
    void reserve(pl_HeapCell* c, int &i)
    {
      i = xi;
      hcell[c] = i;
    };
    void read(pl_HeapCell* c, int &i)
    {
      i = hcell[c];
    };
  };

  void pl_get_code_pre(pl_HeapCell* c, pl_DynamicPredicate* pred, pl_MemReserve* res);
  void pl_get_code(pl_HeapCell* c, pl_DynamicPredicate* pred, pl_MemReserve* res);

  void pl_get_code_arg(pl_HeapCell* c, pl_DynamicPredicate* pred, pl_MemReserve* res)
  {
    int Xi;
    pl_HeapCell* current;
    pl_UnifyCommand com;
    pl_HeapCell* c2 = pl_deref(c);
//    assert(c->type == pl_htStructure);
    int arity = pl_getarity(c->str.str);
    for (int i = 0; i < arity; i++)
    {
      c2++;
      c = pl_deref(c2);
      com.Arg = i;
      switch (c->type)
      {
      case pl_htReference:
        {
          if (res->isFirstVar(c))
          {
            res->reserve(c, Xi);
            com.command = pl_dcUnifyVariableARG;
            com.Xi = Xi;
            pred->commands.push_back(com);
	    ASSERTDEBUG(wcout << L"assert: UnifyVariable X" << Xi << " A" << com.Arg <<endl);
          }
          else
          {
            res->read(c, Xi);
	    com.command = pl_dcUnifyValueARG;
            com.Xi = Xi;
            pred->commands.push_back(com);
	    ASSERTDEBUG(wcout << L"assert: UnifyValue X" << Xi << " A" << com.Arg <<endl);
          };
        }
        ; break;
      case pl_htReal:
        {
	   com.command = pl_dcGetFloatARG;
          com.real = c->real.number;
          pred->commands.push_back(com);
	  ASSERTDEBUG(wcout << L"assert: GetFloat " << com.real << " A" << com.Arg <<endl);
        }
        ; break;
      case pl_htInteger:
        {
	   com.command = pl_dcGetIntegerARG;
          com.integer = c->integer.number;
          pred->commands.push_back(com);
	  ASSERTDEBUG(wcout << L"assert: GetInteger " << com.real << " A" << com.Arg <<endl);
        }
        ; break;
      case pl_htStructure:
        {
          res->reserve(c, Xi);

	  com.command = pl_dcGetStructureARG;
          com.str = c->str.str;
          com.Xi = Xi;
	  int arity = pl_getarity(c->str.str);
          pred->commands.push_back(com);
		ASSERTDEBUG(wcout << L"assert: GetStructure " << pl_idToName(pl_getname(com.str)) << L"/" << arity << " A" << com.Arg <<endl);
          
          current = c;

          for (int i = 0; i < arity; i++)
          {
            current++;
            pl_get_code_pre(current,pred, res);
          };
          current = c;

          for (int i = 0; i < arity; i++)
          {
            current++;
            pl_get_code(current,pred, res);
          };
        }
        ; break;

      };
    };
  };

  void pl_get_code(pl_HeapCell* c, pl_DynamicPredicate* pred, pl_MemReserve* res)
  {
    int Xi;
    pl_HeapCell* current;
    pl_UnifyCommand com;
    c = pl_deref(c);
    switch (c->type)
    {
    case pl_htStructure:
      {
        res->read(c, Xi);

	com.command = pl_dcGetStructure;
        com.str = c->str.str;
        com.Xi = Xi;
        pred->commands.push_back(com);
        int arity = pl_getarity(c->str.str);
	ASSERTDEBUG(wcout << L"assert: GetStructure " << pl_idToName(pl_getname(com.str)) << L"/" << arity << L", X" << Xi <<endl);
        current = c;

        for (int i = 0; i < arity; i++)
        {
          current++;
          pl_get_code_pre(current,pred, res);
        };
        current = c;

        for (int i = 0; i < arity; i++)
        {
          current++;
          pl_get_code(current,pred, res);
        };
      }
      ; break;

    };
  };

  void pl_get_code_pre(pl_HeapCell* c, pl_DynamicPredicate* pred, pl_MemReserve* res)
  {
    int Xi;
    pl_HeapCell* current;
    pl_UnifyCommand com;
    com.Arg = -1;
    c = pl_deref(c);
    switch (c->type)
    {
    case pl_htReference:
      {
        if (res->isFirstVar(c))
        {
          res->reserve(c, Xi);
	  com.command = pl_dcUnifyVariable;
          com.Xi = Xi;
          pred->commands.push_back(com);
	  ASSERTDEBUG(wcout << L"assert: UnifyVariable X" << Xi <<endl);
        }
        else
        {
          res->read(c, Xi);
	  com.command = pl_dcUnifyValue;
          com.Xi = Xi;
          pred->commands.push_back(com);
	  ASSERTDEBUG(wcout << L"assert: UnifyValue X" << Xi <<endl);
        };
      }
      ; break;
    case pl_htReal:
      {

	 com.command = pl_dcGetFloat;
        com.real = c->real.number;
        pred->commands.push_back(com);
	ASSERTDEBUG(wcout << L"assert: GetFloat " << com.real <<endl);
      }
      ; break;
    case pl_htInteger:
      {

	 com.command = pl_dcGetInteger;
        com.integer = c->integer.number;
        pred->commands.push_back(com);
	ASSERTDEBUG(wcout << L"assert: GetInteger " << com.integer <<endl);
      }
      ; break;
    case pl_htStructure:
      {
        res->reserve(c, Xi);
	com.command = pl_dcUnifyVariable;
        com.Xi = Xi;
        pred->commands.push_back(com);
	ASSERTDEBUG(wcout << L"assert: UnifyVariable X" << Xi <<endl);
      }
      ; break;

    };
  }
  
  void pl_dyn_fixed_add(pl_PredicateCollection& coll, const pl_UnifyCommand* unify, int count)
  {
     /// @todo dies auch für Groundprädikate einsetzen.
     pl_DynamicPredicate* pred = new pl_DynamicPredicate();
     for (int i = 0; i < count; i++) {
	pred->commands.push_back(unify[i]);
     };
     ((DYNPRED*)coll.predicates)->push_back(pred);
  };
  void pl_dyn_add(pl_PredicateCollection& coll, pl_HeapCell* c, pl_dyn_addtype t)
  {
    pl_DynamicPredicate* pred = new pl_DynamicPredicate();
    pl_MemReserve memp;
    pl_HeapCell* first = pl_deref(c);
    //int i;
    //memp.reserve(first, i);
    //    Fehler: Diese Code muss so verändert werden, dass für jedes einzelne Element
    //	  das Argument zuerst geladen wird
    pl_get_code_arg(first, pred, &memp);
    if (t == pl_addlast) {
       ((DYNPRED*)coll.predicates)->push_back(pred);
    } else {
       ((DYNPRED*)coll.predicates)->insert(((DYNPRED*)coll.predicates)->begin(), pred);
    };
  }

  void pl_dyn_remove(pl_PredicateCollection& coll, int i)
  {
    coll.remove(i);
  }

  void pl_dyn_clear(pl_PredicateCollection& coll)
  {
    coll.clear();
  }



  void pl_print(pl_PrologVar* c)
  {
    pl_print((pl_HeapCell*)c);
  };

  void pl_print(pl_PrologVar& c)
  {
    pl_print((pl_HeapCell*)&c);
  };

  void pl_print(pl_HeapCell* c)
  {
    pl_HeapCell* d = pl_deref(c);
    if (d->type == pl_htReference)
    {
      unsigned int pos = ((unsigned int)d-(unsigned int)pl_Heap)/sizeof(pl_HeapCell);
      wcout << L"X" << pos;
    }
    else if (d->type == pl_htStructure)
    {
      int arity = pl_getarity(d->str.str);
      wcout << pl_idToName(pl_getname(d->str.str));
      if (arity >= 1)
      {
        wcout << L"(";
        for (int i = 0; i < arity; i++)
        {
          d++;
          pl_print(d);
          if (i != arity-1) wcout << L",";
        };
        wcout << L")";
      };
    }
    else if (d->type == pl_htInteger)
    {
      wcout << d->integer.number;

    }
    else if (d->type == pl_htReal)
    {
      wcout << d->real.number;

    };
  };

  bool pl_loadVariable(pl_PrologVar& V, int Xi)
  {
     
     pl_X[Xi] = (pl_HeapCell*)&V; pl_unifymode = pl_umRead;pl_S = (pl_HeapCell*)&V;
    return true;
  }

  pl_HeapCell* pl_deref(pl_HeapCell* address)
  {
    //TODO Speed Up
     while (address->type == pl_htReference && address->var.reference != address) {
	address = address->var.reference;
     }
     return address;
     /* if (address->type == pl_htReference && address->var.reference != address)
    {
      return pl_deref(address->var.reference);
    }
    else
    {
      return address;
  };*/
  }

  bool pl_get_structure(pl_PSTRINFO s, int Xi)
  {
    pl_HeapCell* addr = pl_deref(pl_X[Xi]);
    switch (addr->type)
    {
    case pl_htReference:
      {
        pl_Heap[pl_H].str.type = pl_htStructure;
        pl_Heap[pl_H].str.str = s;
        pl_bind((pl_PrologVar*)addr, &pl_Heap[pl_H]);
        pl_H++;
        pl_unifymode = pl_umWrite;
      }
      ; break;
    case pl_htStructure:
      {
        if (addr->str.str == s)
        {
          pl_S = addr;
          pl_S++;
          pl_unifymode = pl_umRead;
        }
        else
        {
          return false;
        };
      }
      ; break;
    default:
      return false;
    };
    return true;
  }

  bool pl_get_structure_ARG(pl_PSTRINFO s, int a)
  {
     pl_HeapCell* addr = pl_deref((pl_HeapCell*)pl_ARG[a]);
    switch (addr->type)
    {
    case pl_htReference:
      {
        pl_Heap[pl_H].str.type = pl_htStructure;
        pl_Heap[pl_H].str.str = s;
        pl_bind((pl_PrologVar*)addr, &pl_Heap[pl_H]);
        pl_H++;
        pl_unifymode = pl_umWrite;
      }
      ; break;
    case pl_htStructure:
      {
        if (addr->str.str == s)
        {
          pl_S = addr;
          pl_S++;
          pl_unifymode = pl_umRead;
        }
        else
        {
          return false;
        };
      }
      ; break;
    default:
      return false;
    };
    return true;
  }

  bool pl_get_integer(int i, int Xi)
  {
    pl_HeapCell* addr = pl_deref(pl_X[Xi]);
    switch (addr->type)
    {
    case pl_htReference:
      {
        pl_Heap[pl_H].integer.type = pl_htInteger;
        pl_Heap[pl_H].integer.number = i;
        pl_bind((pl_PrologVar*)addr, &pl_Heap[pl_H]);
        pl_H++;
        pl_unifymode = pl_umWrite;
      }
      ; break;
    case pl_htInteger:
      {
        if (addr->integer.number == i)
        {
          pl_S = addr;
          pl_S++;
          pl_unifymode = pl_umRead;
        }
        else
        {
          return false;
        };
      }
      ; break;
    case pl_htReal:
      {
        if (addr->real.number == i)
        {
          pl_S = addr;
          pl_S++;
          pl_unifymode = pl_umRead;
        }
        else
        {
          return false;
        };
      }
      ; break;
    default:
      return false;
    };
    return true;
  }

  bool pl_get_real(float f, int Xi)
  {
    pl_HeapCell* addr = pl_deref(pl_X[Xi]);
    switch (addr->type)
    {
    case pl_htReference:
      {
        pl_Heap[pl_H].real.type = pl_htReal;
        pl_Heap[pl_H].real.number = f;
        pl_bind((pl_PrologVar*)addr, &pl_Heap[pl_H]);
        pl_H++;
        pl_unifymode = pl_umWrite;
      }
      ; break;
    case pl_htInteger:
      {
        if (addr->integer.number == f)
        {
          pl_S = addr;
          pl_S++;
          pl_unifymode = pl_umRead;
        }
        else
        {
          return false;
        };
      }
      ; break;
    case pl_htReal:
      {
        if (addr->real.number == f)
        {
          pl_S = addr;
          pl_S++;
          pl_unifymode = pl_umRead;
        }
        else
        {
          return false;
        };
      }
      ; break;
    default:
      return false;
    };
    return true;
  }

  bool pl_get_integer_ARG(int i, int a)
  {
     pl_HeapCell* addr = pl_deref((pl_HeapCell*)pl_ARG[a]);
     switch (addr->type)
     {
	case pl_htReference:
	{
	   pl_Heap[pl_H].integer.type = pl_htInteger;
	   pl_Heap[pl_H].integer.number = i;
	   pl_bind((pl_PrologVar*)addr, &pl_Heap[pl_H]);
	   pl_H++;
	   pl_unifymode = pl_umWrite;
	}
	; break;
	case pl_htInteger:
	{
	   if (addr->integer.number == i)
	   {
	      pl_S = addr;
	      pl_S++;
	      pl_unifymode = pl_umRead;
	   }
	   else
	   {
	      return false;
	   };
	}
	; break;
	case pl_htReal:
	{
	   if (addr->real.number == i)
	   {
	      pl_S = addr;
	      pl_S++;
	      pl_unifymode = pl_umRead;
	   }
	   else
	   {
	      return false;
	   };
	}
	; break;
	default:
	   return false;
     };
     return true;
  }

  bool pl_get_real_ARG(float f, int a)
  {
     pl_HeapCell* addr = pl_deref((pl_HeapCell*)pl_ARG[a]);
     switch (addr->type)
     {
	case pl_htReference:
	{
	   pl_Heap[pl_H].real.type = pl_htReal;
	   pl_Heap[pl_H].real.number = f;
	   pl_bind((pl_PrologVar*)addr, &pl_Heap[pl_H]);
	   pl_H++;
	   pl_unifymode = pl_umWrite;
	}
	; break;
	case pl_htInteger:
	{
	   if (addr->integer.number == f)
	   {
	      pl_S = addr;
	      pl_S++;
	      pl_unifymode = pl_umRead;
	   }
	   else
	   {
	      return false;
	   };
	}
	; break;
	case pl_htReal:
	{
	   if (addr->real.number == f)
	   {
	      pl_S = addr;
	      pl_S++;
	      pl_unifymode = pl_umRead;
	   }
	   else
	   {
	      return false;
	   };
	}
	; break;
	default:
	   return false;
     };
     return true;
  }
  /*bool pl_get_integer_ARG(int i, int a)
  {
     pl_HeapCell* addr = pl_deref((pl_HeapCell*)pl_ARG[a]);
     switch (addr->type)
     {
	case pl_htReference:
	{
	   pl_Heap[pl_H].integer.type = pl_htInteger;
	   pl_Heap[pl_H].integer.number = i;
	   pl_bind((pl_PrologVar*)addr, &pl_Heap[pl_H]);
	   pl_H++;
	   pl_unifymode = pl_umWrite;
	}
	; break;
	case pl_htInteger:
	{
	   if (addr->integer.number == i)
	   {
	      pl_S = addr;
	      pl_S++;
	      pl_unifymode = pl_umRead;
	   }
	   else
	   {
	      return false;
	   };
	}
	; break;
	case pl_htReal:
	{
	   if (addr->real.number == i)
	   {
	      pl_S = addr;
	      pl_S++;
	      pl_unifymode = pl_umRead;
	   }
	   else
	   {
	      return false;
	   };
	}
	; break;
	default:
	   return false;
     };
     return true;
  }
  */
  bool pl_put_integer_ARG(int f, int a)
  {
     pl_Heap[pl_H].integer.type = pl_htInteger;
     pl_Heap[pl_H].integer.number = f;
     pl_ARG[a] = (pl_PrologVar*)&pl_Heap[pl_H];
     pl_H++;
     return true;
  }
  bool pl_put_real_ARG(float f, int a)
  {
     pl_Heap[pl_H].real.type = pl_htReal;
     pl_Heap[pl_H].real.number = f;
     pl_ARG[a] = (pl_PrologVar*)&pl_Heap[pl_H];
     pl_H++;
     return true;
  }
  bool pl_get_integer(int i)
  {
    if (pl_unifymode == pl_umRead)
    {

      pl_HeapCell* addr = pl_S;
      pl_S++;
      switch (addr->type)
      {
      case pl_htReference:
        {
          pl_Heap[pl_H].integer.type = pl_htInteger;
          pl_Heap[pl_H].integer.number = i;
          pl_bind((pl_PrologVar*)addr, &pl_Heap[pl_H]);
          pl_H++;
        }
        ; break;
      case pl_htInteger:
        {
          if (addr->integer.number == i)
          {
            return true;

          }
          else
          {
            return false;
          };
        }
        ; break;
      case pl_htReal:
        {
          if (addr->real.number == i)
          {
            return true;
          }
          else
          {
            return false;
          };
        }
        ; break;
      default:
        return false;
      };
    }
    else
    {
      pl_Heap[pl_H].integer.type = pl_htInteger;
      pl_Heap[pl_H].integer.number = i;
      pl_H++;
    };

    return true;
  }

  bool pl_get_real(float i)
  {
     if (pl_unifymode == pl_umRead)
     {

	pl_HeapCell* addr = pl_S;
	pl_S++;
	switch (addr->type)
	{
	   case pl_htReference:
	   {
	      pl_Heap[pl_H].real.type = pl_htReal;
	      pl_Heap[pl_H].real.number = i;
	      pl_bind((pl_PrologVar*)addr, &pl_Heap[pl_H]);
	      pl_H++;
	   }
	   ; break;
	   case pl_htInteger:
	   {
	      if (addr->integer.number == i)
	      {
		 return true;

	      }
	      else
	      {
		 return false;
	      };
	   }
	   ; break;
	   case pl_htReal:
	   {
	      if (addr->real.number == i)
	      {
		 return true;
	      }
	      else
	      {
		 return false;
	      };
	   }
	   ; break;
	   default:
	      return false;
	};
     }
     else
     {
	pl_Heap[pl_H].real.type = pl_htReal;
	pl_Heap[pl_H].real.number = i;
	pl_H++;
     };

     return true;
  }

  bool pl_loadArgVar(int argument, int Xi)
  {
    //Das ist irgendwie unschön
    pl_Heap[pl_H].type = pl_htReference;
    pl_Heap[pl_H].var.reference = (pl_HeapCell*)&pl_Heap[pl_H];
    pl_ARG[argument] = (pl_PrologVar*)&pl_Heap[pl_H];
    pl_X[Xi] = (pl_HeapCell*)pl_ARG[argument];
    pl_H++;
    return true;
  }
  bool pl_loadArgVal(int argument, int Xi)
  {
     pl_Heap[pl_H].type = pl_htReference;
     pl_Heap[pl_H].var.reference = (pl_HeapCell*)&pl_Heap[pl_H];
     pl_X[Xi] = (pl_HeapCell*)pl_ARG[argument];
     pl_H++;
    return pl_unify((pl_HeapCell*)pl_ARG[argument], pl_X[Xi]);
  }

  bool pl_loadArgVariable(int argument, pl_PrologVar& V)
  {
    //Das ist irgendwie unschön
    pl_ARG[argument] = &V;
    return true;
  }
  bool pl_loadArgValue(int argument, pl_PrologVar& V)
  {
   // pl_unify((pl_HeapCell*)pl_ARG[argument], (pl_HeapCell*)&V);
    return pl_unify((pl_HeapCell*)pl_ARG[argument], (pl_HeapCell*)&V);
  }
  pl_PrologVar& pl_getVoid()
  {
     pl_Heap[pl_H].type = pl_htReference;
     pl_Heap[pl_H].var.reference = &pl_Heap[pl_H];
     pl_PrologVar* p = (pl_PrologVar*)&pl_Heap[pl_H];
     pl_H++;
     return *p;
  };
  bool pl_unify_void()
  {
     if (pl_unifymode == pl_umRead)
     {
	pl_S++;
	return true;
     }
     else
     {
	pl_Heap[pl_H].type = pl_htReference;
	pl_Heap[pl_H].var.reference = &pl_Heap[pl_H];
	pl_H++;
     };
     pl_S++;
     return true;
  }
  
  bool pl_unify_variable(pl_PrologVar& V, int Xi)
  {
    if (pl_unifymode == pl_umRead)
    {
     // pl_X[Xi] = pl_S;
       pl_X[Xi] = (pl_HeapCell*)&V;
       pl_S++;
       return pl_unify(pl_X[Xi], pl_S-1);
    }
    else
    {
      //Das ist Dumm!
     /* pl_Heap[pl_H].type = pl_htReference;
      pl_Heap[pl_H].var.reference = (pl_HeapCell*)&V;
      pl_X[Xi] = (pl_HeapCell*)&V;
       pl_H++;*/
       pl_Heap[pl_H] = *pl_X[Xi];
       pl_H++;
    };
    pl_S++;
    return true;
  }
  bool pl_unify_value(pl_PrologVar& V, int Xi)
  {
    if (pl_unifymode == pl_umRead)
    {
       pl_X[Xi] = (pl_HeapCell*)&V;
      pl_S++;
      return pl_unify(pl_X[Xi], pl_S-1);
    }
    else
    {
      //Das ist Dumm!
      pl_Heap[pl_H] = *pl_X[Xi];
      pl_H++;
    };
    pl_S++;
    return true;
  }
  
  bool pl_unify_variable(pl_PrologVar& V)
  {
     if (pl_unifymode == pl_umRead)
     {
	pl_S++;
	return pl_unify((pl_HeapCell*)&V, pl_S-1);
     }
     else
     {
	pl_Heap[pl_H] = (pl_HeapCell&)V;
	pl_H++;
     };
     pl_S++;
     return true;
  }
  bool pl_unify_value(pl_PrologVar& V)
  {
     if (pl_unifymode == pl_umRead)
     {
	pl_S++;
	return pl_unify((pl_HeapCell*)&V, pl_S-1);
     }
     else
     {
	pl_Heap[pl_H] = (pl_HeapCell&)V;
	pl_H++;
     };
     pl_S++;
     return true;
  }

  bool pl_unify_variable(int Xi)
  {
    if (pl_unifymode == pl_umRead)
    {
      pl_X[Xi] = pl_S;
    }
    else
    {
      //Das ist Dumm!
      pl_Heap[pl_H].type = pl_htReference;
      pl_Heap[pl_H].var.reference = (pl_HeapCell*)&pl_Heap[pl_H];
      pl_X[Xi] = (pl_HeapCell*)&pl_Heap[pl_H];
      pl_H++;
    };
    pl_S++;
    return true;
  }
  bool pl_unify_value(int Xi)
  {
    if (pl_unifymode == pl_umRead)
    {
      //pl_X[Xi] = pl_S;
       pl_S++;
      return pl_unify(pl_X[Xi], pl_S-1);
    }
    else
    {

      pl_Heap[pl_H] = *pl_X[Xi];
      pl_H++;
    };
    pl_S++;
    return true;
  }

  
  bool pl_unify_variableARG(int Xi)
  {
     if (pl_unifymode == pl_umRead)
     {
	if (pl_S->type == pl_htReference) {
	   pl_ARG[Xi] = (pl_PrologVar*)pl_S;
	} else {
	   pl_Heap[pl_H].type = pl_htReference;
	   pl_Heap[pl_H].var.reference = pl_S;
	   pl_ARG[Xi] = (pl_PrologVar*)&pl_Heap[pl_H];
	   pl_H++;
	};
     }
     else
     {
      //Das ist Dumm!
	pl_Heap[pl_H].type = pl_htReference;
	pl_Heap[pl_H].var.reference = (pl_HeapCell*)&pl_Heap[pl_H];
	pl_ARG[Xi] = (pl_PrologVar*)&pl_Heap[pl_H];
	pl_H++;
     };
     pl_S++;
     return true;
  }
  bool pl_unify_valueARG(int Xi)
  {
     if (pl_unifymode == pl_umRead)
     {
	//pl_ARG[Xi] = pl_S;
	pl_S++;
	return pl_unify((pl_HeapCell*)pl_ARG[Xi], pl_S-1);
     }
     else
     {

	pl_Heap[pl_H] = *((pl_HeapCell*)pl_ARG[Xi]);
	pl_H++;
     };
     pl_S++;
     return true;
  }
  bool pl_unify_variable_ARG(int Xi, int a)
  {
     pl_X[Xi] = (pl_HeapCell*)pl_ARG[a];

    return true;
  }
  bool pl_unify_value_ARG(int Xi, int a)
  {
     return pl_unify(pl_X[Xi], (pl_HeapCell*)pl_ARG[a]);

  }

  void pl_reduceVarTrail(int s)
  {
    pl_PrologVar* var;
    while (STACK_SIZE(pl_vartrail) > s)
    {
      STACK_TOP(pl_vartrail, var);
      var->reference = (pl_HeapCell*)var;
      STACK_POP(pl_vartrail);
    };
  };

  int pl_compare(pl_HeapCell* a1, pl_HeapCell* a2)
  {
    pl_HeapCell* t1 = pl_deref(a1);
    pl_HeapCell* t2 = pl_deref(a2);
    if (t1 == t2) return 0;
    if (t1->type < t2->type) return 1;
    if (t1->type > t2->type) return -1;
    if (t1->type == t2->type)
    {
      switch (t1->type)
      {
      case pl_htReference:
        {
          if (t1 < t2) return 1;
          if (t1 > t2) return -1;

        }
        ; break;
      case pl_htReal:
        {
          if (t1->real.number < t2->real.number) return 1;
          if (t1->real.number > t2->real.number) return -1;
          if (t1->real.number == t2->real.number) return 0;
        }
        ; break;
      case pl_htInteger:
        {
          if (t1->real.number < t2->real.number) return 1;
          if (t1->real.number > t2->real.number) return -1;
          if (t1->real.number == t2->real.number) return 0;
        }
        ; break;
      case pl_htStructure:
        {
          int a1 = pl_getarity(t1->str.str);
          int a2 = pl_getarity(t2->str.str);
          if (a1 < a2) return 1;
          if (a1 > a2) return -1;
          if (a1 == a2)
          {
            pl_Name n1 = pl_getname(t1->str.str);
            pl_Name n2 = pl_getname(t2->str.str);
            if (n1 != n2)
            {
              const wchar_t* c1 = pl_idToName(n1);
              const wchar_t* c2 = pl_idToName(n2);
              return wcscmp(c1, c2);
            }
            else
            {
              t1++;
              t2++;
              for (int i = 0; i < a1; i++)
              {
                int i = pl_compare(t1, t2);
                if (i != 0) return i;
                t1++;
                t2++;
              };
              return 0;
            };
          }
        }
        ; break;
      };
    };
    return -1;
  };
  bool pl_testunify(pl_HeapCell* a1, pl_HeapCell* a2) {
     int oldHeapSize = pl_H;
     int oldVarSize = STACK_SIZE(pl_vartrail);
     bool res = pl_unify(a1, a2);
     pl_reduceVarTrail(oldVarSize);
	pl_H = oldHeapSize;
	return res;
  };
  bool pl_unify(pl_HeapCell* a1, pl_HeapCell* a2)
  {
    //stack<pl_HeapCell*> PDL;
    PDLSize = 2;
    PDL[0] = a1;
    PDL[1] = a2;
   // PDL.push(a1);
   // PDL.push(a2);
    while (PDLSize != 0)
    {
//       assert(PDLSize >= 2);
       pl_HeapCell* d1 = pl_deref(PDL[PDLSize-1]);
     // PDL.pop();
      pl_HeapCell* d2 = pl_deref(PDL[PDLSize-2]);
      //PDL.pop();
      PDLSize -= 2;
      if (d1 != d2)
      {
        if (d1->type == pl_htReference)
        {
          pl_bind((pl_PrologVar*)d1, d2);
        }
        else if (d2->type == pl_htReference)
        {
          pl_bind((pl_PrologVar*)d2, d1);
        }
        else
        {
          switch (d1->type)
          {
          case pl_htStructure:
            {
              if (d2->type != pl_htStructure) return false;
              if (d1->str.str != d2->str.str) return false;
              int n = pl_getarity(d1->str.str);
              for (int i = 0; i < n; i++)
              {
                d1++;
                d2++;
		PDL[PDLSize] = a1;
		PDL[PDLSize+1] = a2;
		PDLSize += 2;
//		assert(PDLSize < PDLSize-2);
             
              };
            }
            ; break;
          case pl_htInteger:
            {
              if (d2->type == pl_htInteger)
              {
                return d1->integer.number == d2->integer.number;
              }
              else if (d2->type == pl_htReal)
              {
                return d1->integer.number == d2->real.number;
              };
              return false;

            }
            ; break;
          case pl_htReal:
            {
              if (d2->type == pl_htInteger)
              {
                return d1->real.number == d2->integer.number;
              }
              else if (d2->type == pl_htReal)
              {
                return d1->real.number == d2->real.number;
              };
              return false;

            }
            ; break;
          };
        };
      };
    };
    return true;
  }

  void* pl_getHeapMem(int amount)
  {
    if (pl_H +amount > pl_maxheapsize)
    {
      return NULL;
    }
    void* res = &pl_Heap[pl_H];
    for (int i = 0; i < amount; i++)
    {
      pl_Heap[pl_H+i].var.type = pl_htReference;
      pl_Heap[pl_H+i].var.reference = &pl_Heap[pl_H+i];
    };
    pl_H += amount;
    return res;
  }

  pl_PrologVar* pl_getVar()
  {
//    assert(pl_H+1 < pl_maxheapsize);
    pl_Heap[pl_H].type = pl_htReference;
    pl_Heap[pl_H].var.reference = &pl_Heap[pl_H];
    pl_H += 1;

    return &pl_Heap[pl_H-1].var;
  }

  void pl_begin(int &pos)
  {
    if (pl_backtracking)
    {
      STACK_PUSH(pl_currentselector, &pos);
      pl_toppos = &pos;
      *pl_toppos = -1; 
      pl_takeTopElement(false);
    }
    else
    {

      STACK_PUSH(pl_currentselector, &pos);
      pl_toppos = &pos;
      *pl_toppos = 0;
      STACK_PUSH(pl_trail, new (pl_stack.getMem(sizeof(pl_CBeginElement))) pl_CBeginElement());
    };
  }

  bool pl_end(int &pos)
  {
    if (pl_backtracking)
    {
      STACK_POP(pl_currentselector);
      STACK_TOP(pl_currentselector, pl_toppos);
      //pl_toppos = pl_currentselector.top();
      if (pl_toppos == &pl_firsttop) return false;
      //pl_TakeElement(true);
      pl_takeTopElement();
      return false;
    }
    else
    {
      //pl_currentselector.pop();
      //pl_toppos = pl_currentselector.top();
      STACK_POP(pl_currentselector);
      STACK_TOP(pl_currentselector, pl_toppos);
      pl_CTrailElement* el;
      STACK_TOP(pl_trail, el);
      if (STACK_SIZE(pl_trail) && el->getType() == pl_ttBeginElement/* dynamic_cast<pl_CBeginElement*>(el)*/)
      {
        //delete el;
        pl_stack.freeMem(el);
        STACK_POP(pl_trail);
	return true;
      };
      STACK_PUSH(pl_trail, new (pl_stack.getMem(sizeof(pl_CEndElement))) pl_CEndElement(*pl_toppos));
      return true;
    };
  }
  void pl_begin(int &pos, void*&it, int argcount)
  {
    if (pl_backtracking)
    {
      STACK_PUSH(pl_currentselector, &pos);
      pl_toppos = &pos;
      pl_localframe = &it;
      *pl_localframe = pl_nextlocalframe;
      *pl_toppos = -1;
      //it = NULL;
      //pl_TakeElement(false);
      pl_takeTopElement(true);
     // pl_localframe = NULL;

      /*Beim Backtracking fügt pl_CEndElementFrame::Undo das passende
       pl_CBeginElementFrame Element in pl_elementstack.ein*/
    }
    else
    {
      STACK_PUSH(pl_currentselector, &pos);
      pl_toppos = &pos;
      *pl_toppos = 0;
      int heappos;
      if (it)
      {
        heappos = ((unsigned int) it-(unsigned int) pl_Heap)/sizeof(pl_HeapCell);
      }
      else
      {
        heappos = -1;
      };
      pl_CBeginElementFrame* bef = new (pl_stack.getMem(sizeof(pl_CBeginElementFrame))) pl_CBeginElementFrame(/*heappos,*/ argcount);
      STACK_PUSH(pl_trail, bef);
      STACK_PUSH(pl_elementstack, bef);
    };
  }
  bool pl_end(int &pos, void*&it)
  {
    if (pl_backtracking)
    {
      STACK_POP(pl_currentselector);
      STACK_TOP(pl_currentselector, pl_toppos);
     // pl_toppos = pl_currentselector.top();
      if (pl_toppos == &pl_firsttop || STACK_SIZE(pl_currentselector)== 0) {
	 pl_backtracking = false;
	 return false;
      }
      /*if (pl_currentselector.size()== 0)
      {
        //Fertig
        return false;
    };*/
      pl_localframe = &it;
      //pl_TakeElement(true);
      STACK_POP(pl_elementstack);
      pl_takeTopElement();
      /** @todo das ist nicht schön
       * Das Problem ist das wenn man false zurückgibt
       * dann wird in der unteren Prozedure Backtracking
       * ausgelöst, falls es durch den vorherigen Befehl
       * aktiviert wird.
       * Dies muss verhindert werden. Stattdessen soll
       * eine neuauswahl erfolgen
       * 
       * Oh je, das klappt nicht wenn das Teil direkt
       * angerufen wird. 
       * 
       * */
      if (!pl_backtracking)
	 pl_ignorenext = true;
      pl_localframe = NULL;
      return false;
    }
    else
    {
      //pl_currentselector.pop();
      //pl_toppos = pl_currentselector.top();
      STACK_POP(pl_currentselector);
      STACK_TOP(pl_currentselector, pl_toppos);
      pl_CTrailElement* el;
      STACK_TOP(pl_trail, el);
      if (STACK_SIZE(pl_trail) && el->getType() == pl_ttBeginElementFrame/*dynamic_cast<pl_CBeginElementFrame*>(el)*/)
      {
        //delete el;
        pl_stack.freeMem(el);
        STACK_POP(pl_trail);
        STACK_POP(pl_elementstack);
        return true;
      };
      int heappos;
      if (it)
      {
        heappos = ((unsigned int) it-(unsigned int) pl_Heap)/sizeof(pl_HeapCell);
      }
      else
      {
        heappos = -1;
      };
      pl_CBeginElementFrame* bef;// = pl_elementstack.top();
      STACK_TOP(pl_elementstack, bef);
      STACK_POP(pl_elementstack);
      STACK_PUSH(pl_trail,new (pl_stack.getMem(sizeof(pl_CEndElementFrame))) pl_CEndElementFrame(*pl_toppos, heappos, bef));
      /*if (pl_currentselector.size()== 0) {
      return;
      };*/
      return true;
    };
  }

  void pl_cut()
  {
    pl_CTrailElement* el;
    pl_CTrailElement* el2;
    if (!pl_backtracking)
    {
      int level = 0;
      while (STACK_SIZE(pl_trail) >= 0)
      {
        pl_CTrailElement* el;// = pl_trail.top();
        STACK_TOP(pl_trail, el);
        if (el->getType() == pl_ttBeginElement/*dynamic_cast<pl_CBeginElement*>(el)*/)
        {
          if (level == 0)
          {
	     STACK_POP(pl_trail);
             STACK_TOP(pl_trail, el2);
	     if (el2->getType() == pl_ttChoisePoint /*dynamic_cast<pl_CChoisePoint*>(el2)*/) {
		//delete el2;
		STACK_POP(pl_trail);
	     };
	     STACK_PUSH(pl_trail, el);
            return;
          };
          level--;
        }
        else if (el->getType() == pl_ttEndElement /*dynamic_cast<pl_CEndElement*>(el)*/)
        {
          level++;
        }
        else if (el->getType() == pl_ttBeginElementFrame /*dynamic_cast<pl_CBeginElementFrame*>(el)*/)
        {
          if (level == 0)
          {
	     STACK_POP(pl_trail);
             STACK_TOP(pl_trail, el2);
	     if (el2->getType() == pl_ttChoisePoint /*dynamic_cast<pl_CChoisePoint*>(el2)*/) {
		//delete el2;
		STACK_POP(pl_trail);
	     };
	     STACK_PUSH(pl_trail, el);
            return;
          };
          level--;
        }
        else if (el->getType() == pl_ttEndElementFrame /*dynamic_cast<pl_CEndElementFrame*>(el)*/)
        {
          level++;
        }
        //delete el;
        pl_stack.freeMem(el);
        STACK_POP(pl_trail);
      };
    };
  };

  void pl_choisePoint()
  {
    if (!pl_backtracking)
    {
      STACK_PUSH(pl_trail,new (pl_stack.getMem(sizeof(pl_CChoisePoint))) pl_CChoisePoint(*pl_toppos, pl_H, STACK_SIZE(pl_vartrail)));
    };
  }
  void pl_DoBacktracking()
  {
    if (pl_backtracking) return;
    if (pl_ignorenext) {
       pl_ignorenext = false;
       return;
    };
    
    pl_backtracking = true;
    //pl_TakeElement(false);
    pl_generateBacktrackingTree();
    pl_takeTopElement();
  }

  void pl_takeTopElement()
  {
    //assert(pl_exitenterstackpos < pl_exitenterstack.size());
//    assert(pl_trail.size() >= 1);
    pl_CTrailElement* el;// = pl_trail.top();
    if (STACK_SIZE(pl_trail) == 0) {
      pl_firsttop = -1;
      pl_backtracking = false;
      return;
    };
    STACK_TOP(pl_trail, el);
    STACK_POP(pl_trail);
    //pl_ChoiseElement & ch = pl_exitenterstack[pl_exitenterstackpos];
    //pl_exitenterstackpos++;
    el->undo();
    pl_TrailType t = el->getType();/* dynamic_cast<pl_CChoisePoint*>(el) != NULL;*/
    //delete el;
        pl_stack.freeMem(el);
    /*switch (ch.type)
    {
    case pl_ctEnterFrame:
      {
        
	pl_nextlocalframe = &pl_Heap[ch.oldFrame];
        *pl_toppos = ch.ParentPos;
        if (ch.begin)
        {
          pl_elementstack.push(ch.begin);
          for (int i = 0; i < ch.begin->argcount; i++)
          {
            pl_ARG[i+1] = ch.begin->ARGS[i];
          };
        };
      }
      ; break;
    case pl_ctEnter:
      {
        *pl_toppos = ch.ParentPos;
      }
      ; break;
    case pl_ctExit:
      {
        *pl_toppos = -1;
      }
      ; break;
  };*/
    ///@todo pl_trail.size() braucht man vielleicht
    if (t == pl_ttChoisePoint /*|| pl_trail.size() == 0*/)
    {
      pl_backtracking = false;
    };
  }


  void pl_takeTopElement(bool useframe)
  {
    pl_takeTopElement();
  }


  void pl_generateBacktrackingTree()
  {
    /*pl_exitenterstackpos = 0;
    pl_exitenterstack.clear();
    pl_CTrailElement* el;

    bool choise= false;
    do
    {

      el = pl_trail.top();
      pl_trail.pop();
      el->undo();
      choise = dynamic_cast<pl_CChoisePoint*>(el) != NULL;
      delete el;
    }
     while ((!choise) && pl_trail.size() != 0);*/
#ifdef DEBUGMODE
    /*pl_dout << L"\\begin{tabular}{|l|l|} \\hline" << endl;
    pl_dout << L" \\multicolumn{2}{|c|}{";
    pl_dout << L"Backtracking Plan";
    pl_dout << L"}\\\\\\hline \\hline" << endl;
    
    for (int i = 0; i < pl_exitenterstack.size(); i++)
    {
      pl_ChoiseElement & ch = pl_exitenterstack[i];
 //     pl_dout << L" " << i << L": ";
      switch (ch.type)
      {
      case pl_ctEnterFrame:
        {
         
	  pl_dout << L"EnterFrame & " << ch.ParentPos << L"\\\\" << endl;
        }
        ; break;
      case pl_ctEnter:
        {
         // *pl_toppos = ch.ParentPos;
	  pl_dout << L"Enter & " << ch.ParentPos << L"\\\\"<< endl;
        }
        ; break;
      case pl_ctExit:
        {
         // *pl_toppos = -1;
	  pl_dout << L"Exit & \\\\"<< endl;

        }
        ; break;
      };
      

    };
    pl_dout << L"\\hline \n \\end{tabular} \n \\\\" << endl;*/
#endif
    pl_backtracking = true;
  }


  void pl_clearTrail()
  {
    pl_CTrailElement* t;
    while(STACK_SIZE(pl_trail)) { 
       STACK_TOP(pl_trail, t);
       //delete el;
        pl_stack.freeMem(t);
       STACK_POP(pl_trail);
       //pl_trail.pop(); 
     };
  }

  void pl_trail_bind(pl_PrologVar* var)
  {
#ifdef DEBUGMODE
   // wcout << L"Variable gebunden" << endl;
#endif
   // pl_vartrail.push(var);
    STACK_PUSH(pl_vartrail, var);
    //  pl_trail.push(new CVarBound(var));
  }

  void pl_bind(pl_PrologVar* var, pl_HeapCell* adr)
  {
    if (adr->type == pl_htReference && (unsigned int)adr < (unsigned int)var)
    {
      pl_trail_bind((pl_PrologVar*)adr);

      adr->var.reference = (pl_HeapCell*)var;
      return;
    };
    pl_trail_bind(var);
    var->reference = adr;
  }

  void pl_math_pushInt(pl_int value)
  {
//    assert(pl_mathstackcount < pl_MathStackSize);
    pl_mathstack[pl_mathstackcount].type = pl_ntInteger;
    pl_mathstack[pl_mathstackcount].integer = value;
    pl_mathstackcount++;
  }

  void pl_math_pushReal(pl_real value)
  {
//    assert(pl_mathstackcount < pl_MathStackSize);
    pl_mathstack[pl_mathstackcount].type = pl_ntReal;
    pl_mathstack[pl_mathstackcount].real = value;
    pl_mathstackcount++;
  }

  void pl_math_calcStructure(pl_HeapCell* str)
  {
//    assert(str->type == pl_htStructure);
    int arity = pl_getarity(str->str.str);
    int name = pl_getname(str->str.str);
    pl_HeapCell* v =str;
    v++;
    if (name == pl_intern_list && arity == 2)
    {
      return;
    };

    for (int i = 0; i < arity; i++)
    {
      pl_math_pushCell(v);
      v++;
    };
    switch (arity)
    {
    case 1:
      {
        switch (name)
        {
        case pl_intern_sub:
          pl_math_neg();
          break;
        case pl_intern_integer:
          pl_math_integer();
          break;
        case pl_intern_float:
          pl_math_float();
          break;
        case pl_intern_float_integer_part:
          pl_math_float_integer_part();
          break;
        case pl_intern_float_fractional_part:
          pl_math_float_fractional_part();
          break;
        case pl_intern_not:
          pl_math_not();
          break;
        };
      }
      ; break;
    case 2:
      {
        switch (name)
        {
        case pl_intern_plus:
          pl_math_add();
          break;
        case pl_intern_sub:
          pl_math_sub();
          break;
        case pl_intern_mul:
          pl_math_mul();
          break;
        case pl_intern_div:
          pl_math_div();
          break;
        case pl_intern_intdiv:
          pl_math_intdiv();
          break;
        case pl_intern_rem:
          pl_math_rem();
          break;
        case pl_intern_mod:
          pl_math_mod();
          break;
        case pl_intern_or:
          pl_math_or();
          break;
        case pl_intern_and:
          pl_math_and();
          break;
        case pl_intern_xor:
          pl_math_xor();
          break;
        case pl_intern_shiftright:
          pl_math_shiftright();
          break;
        case pl_intern_shiftleft:
          pl_math_shiftleft();
          break;
        };
      }
      ; break;
    default:
      {
        wcout << L"Error: Unbekannte Struktur in Ausdruck";
      };
    };

  };

  void pl_math_pushCell(pl_HeapCell* c)
  {
//    assert(pl_mathstackcount < pl_MathStackSize);
    //TODO
    pl_HeapCell* d = pl_deref(c);
    if (d->type == pl_htReference)
    {

      wcout << L"Error: Nicht unifizierte Variable" << endl;

    }
    else if (d->type == pl_htStructure)
    {
       pl_math_calcStructure(d);
    /*  wcout << L"Oje" << endl;
      pl_mathstack[pl_mathstackcount].type = pl_ntInteger;
      pl_mathstack[pl_mathstackcount].integer = 0;
       pl_mathstackcount++;*/
    }
    else if (d->type == pl_htInteger)
    {
      pl_mathstack[pl_mathstackcount].type = pl_ntInteger;
      pl_mathstack[pl_mathstackcount].integer = d->integer.number;
      pl_mathstackcount++;

    }
    else if (d->type == pl_htReal)
    {
      pl_mathstack[pl_mathstackcount].type = pl_ntReal;
      pl_mathstack[pl_mathstackcount].real = d->real.number;
      pl_mathstackcount++;
    };
  };

  void pl_math_pushVar(pl_PrologVar& c)
  {
    pl_math_pushCell((pl_HeapCell*)&c);
  };

  bool pl_math_popVar(pl_PrologVar& c)
  {
//    assert(pl_mathstackcount >= 1);
    pl_HeapCell* d = pl_deref((pl_HeapCell*)&c);
    pl_mathstackcount--;
    if (d->type == pl_htReference)
    {
      if (pl_mathstack[pl_mathstackcount].type == pl_ntInteger)
      {
        pl_Heap[pl_H].integer.type = pl_htInteger;
        pl_Heap[pl_H].integer.number = pl_mathstack[pl_mathstackcount].integer;
        pl_bind((pl_PrologVar*)d, &pl_Heap[pl_H]);
        pl_H++;
      }
      else
      {
        pl_Heap[pl_H].real.type = pl_htReal;
        pl_Heap[pl_H].real.number = pl_mathstack[pl_mathstackcount].real;
        pl_bind((pl_PrologVar*)d, &pl_Heap[pl_H]);
        pl_H++;
      };
      return true;
    }
    else if (d->type == pl_htStructure)
    {

      return false;
    }
    else if (d->type == pl_htInteger)
    {
      if (pl_mathstack[pl_mathstackcount].type == pl_ntInteger)
      {
        return pl_mathstack[pl_mathstackcount].integer == d->integer.number;
      }
      else
      {
        return pl_mathstack[pl_mathstackcount].real == d->integer.number;
      };


    }
    else if (d->type == pl_htReal)
    {
      if (pl_mathstack[pl_mathstackcount].type == pl_ntInteger)
      {
        return pl_mathstack[pl_mathstackcount].integer == d->real.number;
      }
      else
      {
        return pl_mathstack[pl_mathstackcount].real == d->real.number;
      };
    };
  };

#define PL_GETVAR(a) (pl_mathstack[a].type == pl_ntInteger ? pl_mathstack[a].integer : pl_mathstack[a].real)

  bool pl_math_isEqual()
  {
   // assert(pl_mathstackcount >= 2);
    bool ret =  PL_GETVAR(pl_mathstackcount-2) == PL_GETVAR(pl_mathstackcount-1);
    pl_mathstackcount -= 2;
    return ret;
  }
  bool pl_math_isNonEqual()
  {
   // assert(pl_mathstackcount >= 2);
    bool ret =  PL_GETVAR(pl_mathstackcount-2) != PL_GETVAR(pl_mathstackcount-1);
    pl_mathstackcount -= 2;
    return ret;
  }
  bool pl_math_isGreater()
  {
  //  assert(pl_mathstackcount >= 2);
    bool ret =  PL_GETVAR(pl_mathstackcount-2) > PL_GETVAR(pl_mathstackcount-1);
    pl_mathstackcount -= 2;
    return ret;
  }
  bool pl_math_isLesser()
  {
//    assert(pl_mathstackcount >= 2);
    bool ret =  PL_GETVAR(pl_mathstackcount-2) < PL_GETVAR(pl_mathstackcount-1);
    pl_mathstackcount -= 2;
    return ret;
  }
  bool pl_math_isEqualGreater()
  {
//    assert(pl_mathstackcount >= 2);
    bool ret =  PL_GETVAR(pl_mathstackcount-2) >= PL_GETVAR(pl_mathstackcount-1);
    pl_mathstackcount -= 2;
    return ret;
  }
  bool pl_math_isEqualLess()
  {
//    assert(pl_mathstackcount >= 2);
    bool ret =  PL_GETVAR(pl_mathstackcount-2) <= PL_GETVAR(pl_mathstackcount-1);
    pl_mathstackcount -= 2;
    return ret;
  }
  void pl_math_add()
  {
//    assert(pl_mathstackcount >= 2);
    //bool ret =  PL_GETVAR(pl_mathstackcount-2) > PL_GETVAR(pl_mathstackcount-1);
    if (pl_mathstack[pl_mathstackcount-2].type == pl_ntInteger && pl_mathstack[pl_mathstackcount-1].type == pl_ntInteger)
    {
      pl_mathstack[pl_mathstackcount-2].integer = pl_mathstack[pl_mathstackcount-2].integer + pl_mathstack[pl_mathstackcount-1].integer;
    }
    else
    {
      pl_real value = PL_GETVAR(pl_mathstackcount-2) + PL_GETVAR(pl_mathstackcount-1);
      pl_mathstack[pl_mathstackcount-2].type = pl_ntReal;
      pl_mathstack[pl_mathstackcount-2].real = value;
    };
    pl_mathstackcount -= 1;
  }
  void pl_math_sub()
  {
//    assert(pl_mathstackcount >= 2);
    //bool ret =  PL_GETVAR(pl_mathstackcount-2) > PL_GETVAR(pl_mathstackcount-1);
    if (pl_mathstack[pl_mathstackcount-2].type == pl_ntInteger && pl_mathstack[pl_mathstackcount-1].type == pl_ntInteger)
    {
      pl_mathstack[pl_mathstackcount-2].integer = pl_mathstack[pl_mathstackcount-2].integer - pl_mathstack[pl_mathstackcount-1].integer;
    }
    else
    {
      pl_real value = PL_GETVAR(pl_mathstackcount-2) - PL_GETVAR(pl_mathstackcount-1);
      pl_mathstack[pl_mathstackcount-2].type = pl_ntReal;
      pl_mathstack[pl_mathstackcount-2].real = value;
    };
    pl_mathstackcount -= 1;
  }
  void pl_math_mul()
  {
//    assert(pl_mathstackcount >= 2);
    //bool ret =  PL_GETVAR(pl_mathstackcount-2) > PL_GETVAR(pl_mathstackcount-1);
    if (pl_mathstack[pl_mathstackcount-2].type == pl_ntInteger && pl_mathstack[pl_mathstackcount-1].type == pl_ntInteger)
    {
      pl_mathstack[pl_mathstackcount-2].integer = pl_mathstack[pl_mathstackcount-2].integer * pl_mathstack[pl_mathstackcount-1].integer;
    }
    else
    {
      pl_real value = PL_GETVAR(pl_mathstackcount-2) * PL_GETVAR(pl_mathstackcount-1);
      pl_mathstack[pl_mathstackcount-2].type = pl_ntReal;
      pl_mathstack[pl_mathstackcount-2].real = value;
    };
    pl_mathstackcount -= 1;
  }
  void pl_math_div()
  {
//    assert(pl_mathstackcount >= 2);
    //bool ret =  PL_GETVAR(pl_mathstackcount-2) > PL_GETVAR(pl_mathstackcount-1);

    pl_real value = (double)PL_GETVAR(pl_mathstackcount-2) / (double)PL_GETVAR(pl_mathstackcount-1);
    pl_mathstack[pl_mathstackcount-2].type = pl_ntReal;
    pl_mathstack[pl_mathstackcount-2].real = value;

    pl_mathstackcount -= 1;
  }
  void pl_math_intdiv()
  {
//    assert(pl_mathstackcount >= 2);
    pl_int value = (pl_int)(PL_GETVAR(pl_mathstackcount-2) + PL_GETVAR(pl_mathstackcount-1));
    pl_mathstack[pl_mathstackcount-2].type = pl_ntInteger;
    pl_mathstack[pl_mathstackcount-2].integer = value;
    pl_mathstackcount -= 1;
  }

  void pl_math_neg()
  {
//    assert(pl_mathstackcount >= 1);
    if (pl_mathstack[pl_mathstackcount-1].type == pl_ntInteger)
    {
      pl_mathstack[pl_mathstackcount-1].integer = -pl_mathstack[pl_mathstackcount-1].integer;
    }
    else
    {
      pl_mathstack[pl_mathstackcount-1].real = -pl_mathstack[pl_mathstackcount-1].real;
    };
  };
  void pl_math_rem()
  {
//    assert(pl_mathstackcount >= 2);

    pl_int value = (pl_int)PL_GETVAR(pl_mathstackcount-2) % (pl_int)PL_GETVAR(pl_mathstackcount-1);
    pl_mathstack[pl_mathstackcount-2].type = pl_ntInteger;
    pl_mathstack[pl_mathstackcount-2].integer = value;

    pl_mathstackcount -= 1;
  }
  void pl_math_mod()
  {
//    assert(pl_mathstackcount >= 2);
    //bool ret =  PL_GETVAR(pl_mathstackcount-2) > PL_GETVAR(pl_mathstackcount-1);
    if (pl_mathstack[pl_mathstackcount-2].type == pl_ntInteger && pl_mathstack[pl_mathstackcount-1].type == pl_ntInteger)
    {
      pl_mathstack[pl_mathstackcount-2].integer = pl_mathstack[pl_mathstackcount-2].integer % pl_mathstack[pl_mathstackcount-1].integer;
    }
    else
    {
      pl_real value1 = PL_GETVAR(pl_mathstackcount-2);
      pl_real value2 = PL_GETVAR(pl_mathstackcount-1);
      pl_mathstack[pl_mathstackcount-2].type = pl_ntReal;
      pl_mathstack[pl_mathstackcount-2].real = fmod(value1,value2);
    };
    pl_mathstackcount -= 1;
  }

  void pl_math_integer()
  {
//    assert(pl_mathstackcount >= 1);
    if (pl_mathstack[pl_mathstackcount-1].type == pl_ntReal)
    {
      pl_mathstack[pl_mathstackcount-1].integer = (pl_int)pl_mathstack[pl_mathstackcount-1].real;
      pl_mathstack[pl_mathstackcount-1].type = pl_ntInteger;
    };
  };
  void pl_math_float_integer_part()
  {
//    assert(pl_mathstackcount >= 1);
    if (pl_mathstack[pl_mathstackcount-1].type == pl_ntReal)
    {
      pl_mathstack[pl_mathstackcount-1].real = (pl_int)pl_mathstack[pl_mathstackcount-1].real;
      pl_mathstack[pl_mathstackcount-1].type = pl_ntReal;
    }
    else
    {
      pl_mathstack[pl_mathstackcount-1].real = pl_mathstack[pl_mathstackcount-1].integer;
      pl_mathstack[pl_mathstackcount-1].type = pl_ntReal;
    };
  };

  void pl_math_float_fractional_part()
  {
//    assert(pl_mathstackcount >= 1);
    if (pl_mathstack[pl_mathstackcount-1].type == pl_ntReal)
    {
      pl_mathstack[pl_mathstackcount-1].real = pl_mathstack[pl_mathstackcount-1].real-((pl_int)pl_mathstack[pl_mathstackcount-1].real);
      pl_mathstack[pl_mathstackcount-1].type = pl_ntReal;
    }
    else
    {
      pl_mathstack[pl_mathstackcount-1].real = 0;
      pl_mathstack[pl_mathstackcount-1].type = pl_ntReal;
    };
  }

  void pl_math_float()
  {
//    assert(pl_mathstackcount >= 1);
    if (pl_mathstack[pl_mathstackcount-1].type == pl_ntInteger)
    {
      pl_mathstack[pl_mathstackcount-1].real = pl_mathstack[pl_mathstackcount-1].integer;
      pl_mathstack[pl_mathstackcount-1].type = pl_ntReal;
    };
  };

  void pl_math_or()
  {
//    assert(pl_mathstackcount >= 2);
    //bool ret =  PL_GETVAR(pl_mathstackcount-2) > PL_GETVAR(pl_mathstackcount-1);
    if (pl_mathstack[pl_mathstackcount-2].type == pl_ntInteger && pl_mathstack[pl_mathstackcount-1].type == pl_ntInteger)
    {
      pl_mathstack[pl_mathstackcount-2].integer = pl_mathstack[pl_mathstackcount-2].integer | pl_mathstack[pl_mathstackcount-1].integer;
    }
    else
    {
      wcout << L"Error: Integer erwartet" << endl;
    };
    pl_mathstackcount -= 1;
  }
  void pl_math_and()
  {
//    assert(pl_mathstackcount >= 2);
    //bool ret =  PL_GETVAR(pl_mathstackcount-2) > PL_GETVAR(pl_mathstackcount-1);
    if (pl_mathstack[pl_mathstackcount-2].type == pl_ntInteger && pl_mathstack[pl_mathstackcount-1].type == pl_ntInteger)
    {
      pl_mathstack[pl_mathstackcount-2].integer = pl_mathstack[pl_mathstackcount-2].integer & pl_mathstack[pl_mathstackcount-1].integer;
    }
    else
    {
      wcout << L"Error: Integer erwartet" << endl;
    };
    pl_mathstackcount -= 1;
  }
  void pl_math_xor()
  {
//    assert(pl_mathstackcount >= 2);
    //bool ret =  PL_GETVAR(pl_mathstackcount-2) > PL_GETVAR(pl_mathstackcount-1);
    if (pl_mathstack[pl_mathstackcount-2].type == pl_ntInteger && pl_mathstack[pl_mathstackcount-1].type == pl_ntInteger)
    {
      pl_mathstack[pl_mathstackcount-2].integer = pl_mathstack[pl_mathstackcount-2].integer ^ pl_mathstack[pl_mathstackcount-1].integer;
    }
    else
    {
      wcout << L"Error: Integer erwartet" << endl;
    };
    pl_mathstackcount -= 1;
  }
  void pl_math_not()
  {
//    assert(pl_mathstackcount >= 1);
    //bool ret =  PL_GETVAR(pl_mathstackcount-2) > PL_GETVAR(pl_mathstackcount-1);
    if (pl_mathstack[pl_mathstackcount-1].type == pl_ntInteger)
    {
      pl_mathstack[pl_mathstackcount-1].integer = ~pl_mathstack[pl_mathstackcount-1].integer;
    }
    else
    {
      wcout << L"Error: Integer erwartet" << endl;
    };
  }

  void pl_math_shiftleft()
  {
//    assert(pl_mathstackcount >= 2);
    //bool ret =  PL_GETVAR(pl_mathstackcount-2) > PL_GETVAR(pl_mathstackcount-1);
    if (pl_mathstack[pl_mathstackcount-2].type == pl_ntInteger && pl_mathstack[pl_mathstackcount-1].type == pl_ntInteger)
    {
      pl_mathstack[pl_mathstackcount-2].integer = pl_mathstack[pl_mathstackcount-2].integer << pl_mathstack[pl_mathstackcount-1].integer;
    }
    else
    {
      wcout << L"Error: Integer erwartet" << endl;
    };
    pl_mathstackcount -= 1;
  }
  void pl_math_shiftright()
  {
//    assert(pl_mathstackcount >= 2);
    //bool ret =  PL_GETVAR(pl_mathstackcount-2) > PL_GETVAR(pl_mathstackcount-1);
    if (pl_mathstack[pl_mathstackcount-2].type == pl_ntInteger && pl_mathstack[pl_mathstackcount-1].type == pl_ntInteger)
    {
      pl_mathstack[pl_mathstackcount-2].integer = pl_mathstack[pl_mathstackcount-2].integer >> pl_mathstack[pl_mathstackcount-1].integer;
    }
    else
    {
      wcout << L"Error: Integer erwartet" << endl;
    };
    pl_mathstackcount -= 1;
  }

  //Foreign interface
  bool pl_call_getInt(pl_PrologVar* Var, pl_int *i)
  {

    pl_HeapCell* v = pl_deref((pl_HeapCell*)Var);
    if (v->type != pl_htInteger) return false;
    *i = v->integer.number;

    return true;
  };

  bool pl_call_unifyInt(pl_PrologVar* Var, pl_int value)
  {
    pl_HeapCell* v = pl_deref((pl_HeapCell*)Var);
    if (v->type == pl_htReference)
    {
      pl_Heap[pl_H].integer.type = pl_htInteger;
      pl_Heap[pl_H].integer.number = value;
      pl_bind((pl_PrologVar*)v, &pl_Heap[pl_H]);
      pl_H++;
      return true;
    }
    else if (v->type == pl_htInteger)
    {
      return v->integer.number == value;
    };
    return false;
  };

  bool pl_call_getFloat(pl_PrologVar* Var, pl_real *i)
  {
    pl_HeapCell* v = pl_deref((pl_HeapCell*)Var);
    if (v->type != pl_htReal) return false;
    *i = v->real.number;

    return true;
  };

  bool pl_call_unifyFloat(pl_PrologVar* Var, pl_real value)
  {
    pl_HeapCell* v = pl_deref((pl_HeapCell*)Var);
    if (v->type == pl_htReference)
    {
      pl_Heap[pl_H].real.type = pl_htReal;
      pl_Heap[pl_H].real.number = value;
      pl_bind((pl_PrologVar*)v, &pl_Heap[pl_H]);
      pl_H++;
      return true;
    }
    else if (v->type == pl_htInteger)
    {
      return v->integer.number == value;
    };
    return false;
  };

  pl_PrologEnvironment::pl_PrologEnvironment()
  {
    pl_Heap = new pl_HeapCell[1024];
    pl_H = 0;
    pl_maxheapsize = 1024;
  }


  pl_PrologEnvironment::~pl_PrologEnvironment()
  {
    delete [] pl_Heap;
  }

  void pl_PrologEnvironment::LoadEnv()
  {
    pl_H = pl_H;
    pl_Heap = pl_Heap;
    pl_maxheapsize = pl_maxheapsize;
  }

  void pl_PrologEnvironment::SaveEnv()
  {}
  
  void pl_RegisterStatic(pl_Name n, int arity, void* func)
  {
     pl_FactElement fe;
     fe.name = n;
     fe.arity = arity;
     fe.data = func;
//     fe.type = pl_Static;
     pl_FactInfo fi;
     fi.arity = arity;
     fi.name = n;
     pl_DatabaseMap::iterator it = pl_globaldatabase.find(fi);
     if (it != pl_globaldatabase.end()) {
	wcout << L"Warnung: Ein Fact aus der Globalen Datenbank ist doppelt. Altes wird entfernt. Dies kann zu ernsthaften Fehlern führen." << endl;
     };
     pl_globaldatabase[fi] = fe;
  }
  void pl_RegisterDynamic(pl_Name n, int arity, pl_PredicateCollection* coll)
  {
     pl_FactInfo fi;
     fi.arity = arity;
     fi.name = n;
     coll->arity = arity;
     coll->name = n;
     pl_DynDatabaseMap::iterator it = pl_globaldyndatabase.find(fi);
     if (it != pl_globaldyndatabase.end()) {
	wcout << L"Warnung: Ein Fact aus der Globalen Datenbank ist doppelt. Altes wird entfernt. Dies kann zu ernsthaften Fehlern führen." << endl;
     };
     pl_globaldyndatabase[fi] = coll;
   }
  bool pl_doArgCall(int arity, void* func) {
    
     switch (arity) {
	case 0: {
	   return ((bool (*) ())func)();
	};
	case 1: {
	   return ((bool (*) (pl_PrologVar &))func)(*pl_ARG[0]);
	};
	case 2: {
	   return ((bool (*) (pl_PrologVar &, pl_PrologVar &))func)(*pl_ARG[0], *pl_ARG[1]);
	};
	case 3: {
	   return ((bool (*) (pl_PrologVar &, pl_PrologVar &, pl_PrologVar &))func )(*pl_ARG[0], *pl_ARG[1], *pl_ARG[2]);
	};
	case 4: {
	   return ((bool (*) (pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &))func)(*pl_ARG[0], *pl_ARG[1], *pl_ARG[2], *pl_ARG[3]);
	};
	case 5: {
	   return ((bool (*) (pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &))func)(*pl_ARG[0], *pl_ARG[1], *pl_ARG[2], *pl_ARG[3], *pl_ARG[4]);
	};
	case 6: {
	   return ((bool (*) (pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &))func)(*pl_ARG[0], *pl_ARG[1], *pl_ARG[2], *pl_ARG[3], *pl_ARG[4], *pl_ARG[5]);
	};
	case 7: {
	   return ((bool (*) (pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &))func)(*pl_ARG[0], *pl_ARG[1], *pl_ARG[2], *pl_ARG[3], *pl_ARG[4], *pl_ARG[5], *pl_ARG[6]);
	};
	case 8: {
	   return ((bool (*) (pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &,  pl_PrologVar &, pl_PrologVar &))func)(*pl_ARG[0], *pl_ARG[1], *pl_ARG[2], *pl_ARG[3], *pl_ARG[4], *pl_ARG[5], *pl_ARG[6], *pl_ARG[7]);
	};
	case 9: {
	   return ((bool (*) (pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &,  pl_PrologVar &, pl_PrologVar &, pl_PrologVar &))func)(*pl_ARG[0], *pl_ARG[1], *pl_ARG[2], *pl_ARG[3], *pl_ARG[4], *pl_ARG[5], *pl_ARG[6], *pl_ARG[7], *pl_ARG[8]);
	};
	case 10: {
	   return ((bool (*) (pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &,  pl_PrologVar &,  pl_PrologVar &, pl_PrologVar &, pl_PrologVar &))func)(*pl_ARG[0], *pl_ARG[1], *pl_ARG[2], *pl_ARG[3], *pl_ARG[4], *pl_ARG[5], *pl_ARG[6], *pl_ARG[7], *pl_ARG[8], *pl_ARG[9]);
	};
	case 11: {
	   return ((bool (*) (pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &,  pl_PrologVar &, pl_PrologVar &,  pl_PrologVar &, pl_PrologVar &, pl_PrologVar &))func)(*pl_ARG[0], *pl_ARG[1], *pl_ARG[2], *pl_ARG[3], *pl_ARG[4], *pl_ARG[5], *pl_ARG[6], *pl_ARG[7], *pl_ARG[8], *pl_ARG[9], *pl_ARG[10]);
	};
	case 12: {
	   return ((bool (*) (pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &,  pl_PrologVar &,  pl_PrologVar &, pl_PrologVar &,  pl_PrologVar &, pl_PrologVar &, pl_PrologVar &))func)(*pl_ARG[0], *pl_ARG[1], *pl_ARG[2], *pl_ARG[3], *pl_ARG[4], *pl_ARG[5], *pl_ARG[6], *pl_ARG[7], *pl_ARG[8], *pl_ARG[9], *pl_ARG[10], *pl_ARG[11]);
	};
	case 13: {
	   return ((bool (*) (pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &,  pl_PrologVar &,pl_PrologVar &,  pl_PrologVar &, pl_PrologVar &,  pl_PrologVar &, pl_PrologVar &, pl_PrologVar &))func)(*pl_ARG[0], *pl_ARG[1], *pl_ARG[2], *pl_ARG[3], *pl_ARG[4], *pl_ARG[5], *pl_ARG[6], *pl_ARG[7], *pl_ARG[8], *pl_ARG[9], *pl_ARG[10], *pl_ARG[11], *pl_ARG[12]);
	};
	case 14: {
	   return ((bool (*) (pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &,pl_PrologVar &,pl_PrologVar &,  pl_PrologVar &, pl_PrologVar &,  pl_PrologVar &, pl_PrologVar &, pl_PrologVar &))func)(*pl_ARG[0], *pl_ARG[1], *pl_ARG[2], *pl_ARG[3], *pl_ARG[4], *pl_ARG[5], *pl_ARG[6], *pl_ARG[7], *pl_ARG[8], *pl_ARG[9], *pl_ARG[10], *pl_ARG[11], *pl_ARG[12], *pl_ARG[13]);
	};
	case 15: {
	   return ((bool (*) (pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &,pl_PrologVar &,pl_PrologVar &,pl_PrologVar &,  pl_PrologVar &, pl_PrologVar &,  pl_PrologVar &, pl_PrologVar &, pl_PrologVar &))func)(*pl_ARG[0], *pl_ARG[1], *pl_ARG[2], *pl_ARG[3], *pl_ARG[4], *pl_ARG[5], *pl_ARG[6], *pl_ARG[7], *pl_ARG[8], *pl_ARG[9], *pl_ARG[10], *pl_ARG[11], *pl_ARG[12], *pl_ARG[13], *pl_ARG[14]);
	};
	case 16: {
	   return ((bool (*) (pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &, pl_PrologVar &,pl_PrologVar &,pl_PrologVar &,pl_PrologVar &,pl_PrologVar &,  pl_PrologVar &, pl_PrologVar &,  pl_PrologVar &, pl_PrologVar &, pl_PrologVar &))func)(*pl_ARG[0], *pl_ARG[1], *pl_ARG[2], *pl_ARG[3], *pl_ARG[4], *pl_ARG[5], *pl_ARG[6], *pl_ARG[7], *pl_ARG[8], *pl_ARG[9], *pl_ARG[10], *pl_ARG[11], *pl_ARG[12], *pl_ARG[13], *pl_ARG[14], *pl_ARG[15]);
	};
	default: {
	   wcout << L"Oh je, für dynamischen Aufruf ist dieser Prädikat zu groß" << endl;
	   return false;
   
        };
     };
  };
  bool pl_FreeCall(pl_HeapCell* cell)
  {
     pl_FactInfo fi;
     pl_HeapCell* v = pl_deref(cell);
     if (v->type != pl_htStructure) {
	return false;
     };
     fi.name = pl_getname(v->str.str);
     fi.arity = pl_getarity(v->str.str);
     pl_DatabaseMap::iterator it = pl_globaldatabase.find(fi);
     if (it == pl_globaldatabase.end()) {
	return false;
     }
     pl_FactElement& el = it->second;
     if (!pl_backtracking) {
	for (int i = 0; i < fi.arity; i++) {
	   v++;
	   pl_ARG[i] = (pl_PrologVar*)v;
	};
      };
      return pl_doArgCall(fi.arity, el.data);
  }
  pl_PredicateCollection* pl_getCollection(pl_Name n, int arity)
  {
     pl_FactInfo fi;
     fi.name = n;
     fi.arity = arity;
     if (fi.name == pl_intern_cut && fi.arity == 0) {
	pl_cut();
	return NULL;
     };
     pl_DynDatabaseMap::iterator it = pl_globaldyndatabase.find(fi);
     if (it == pl_globaldyndatabase.end()) {
	return NULL;
     }
     return it->second;
  }
  pl_PredicateCollection* pl_getCollection(pl_HeapCell* cell)
  {
    
     pl_HeapCell* v = pl_deref(cell);
     if (v->type != pl_htStructure) {
	return NULL;
     };
     return pl_getCollection(pl_getname(v->str.str), pl_getarity(v->str.str));
     
  }
  
  void pl_debuginit()
  {
#ifdef DEBUGMODE
     pl_dout.open("work.tex");
     pl_dout << L"\\documentclass{article}" << endl;
     pl_dout << L"\\usepackage{ngerman}" << endl;
     pl_dout << L"\\usepackage{latexsym}" << endl;
     pl_dout << L"\\usepackage[dvips]{graphicx}" << endl;

     pl_dout << L"\\author{Michael Staud}" << endl;
     pl_dout << L"\\title{Steps}" << endl;
     pl_dout << L"\\frenchspacing" << endl;
     pl_dout << L"\\begin{document}" << endl;
     pl_dout << L"\\maketitle" << endl;
     pl_dout << L"\\tableofcontents" << endl;
     pl_dout << L"\\section{Einzelne Schritte}" << endl;
#endif
  }
  
  void pl_debugfree()
  {
#ifdef DEBUGMODE
     pl_dout << L"\\end{document}" << endl;
     pl_dout.flush();
     pl_dout.close();
#endif
  };
  
  void pl_debug(wchar_t* text)
  {
#ifdef DEBUGMODE
     pl_dout << text << L" \\\\ " << endl;
#endif
  };
  
  void pl_step(wchar_t* text)
  {
#ifdef DEBUGMODE
     pl_dout << L"\\subsection{" << text << L"}" << endl;
     
     pl_dout << L"\\begin{tabular}{|l|l|} \\hline" << endl;
     pl_dout << L" \\multicolumn{2}{|c|}{";
     pl_dout << L"Stack";
     pl_dout << L"}\\\\\\hline \\hline" << endl;
     //pl_trail
     vector<pl_CTrailElement*> temp;
     while (pl_trail.size() != 0) {
	temp.push_back(pl_trail.top());
	pl_trail.pop();
     };
     for (int i = 0; i < temp.size(); i++) {
	pl_trail.push(temp[temp.size()-i-1]);
	pl_CTrailElement* te = temp[temp.size()-i-1];
	if (dynamic_cast<pl_CBeginElement*>(te)) {
	   pl_dout << L"BeginElement & " << L"\\\\" << endl;
	} else if (dynamic_cast<pl_CEndElement*>(te)) {
	   pl_dout << L"EndElement & " << dynamic_cast<pl_CEndElement*>(te)->parent << L"\\\\" << endl;
	} else if (dynamic_cast<pl_CBeginElementFrame*>(te)) {
	   pl_dout << L"BeginElementFrame & " << L"\\\\" << endl;
	} else if (dynamic_cast<pl_CEndElementFrame*>(te)) {
	   pl_dout << L"EndElementFrame & " << dynamic_cast<pl_CEndElementFrame*>(te)->parent << L"\\\\" << endl;
	} else if (dynamic_cast<pl_CChoisePoint*>(te)) {
	   pl_dout << L"ChoisePoint & " << dynamic_cast<pl_CChoisePoint*>(te)->pos << L"\\\\" << endl;
	}
     };
     
 //    pl_dout << L"EnterFrame & " << ch.ParentPos << L"\\\\" << endl;

     pl_dout << L"\\hline \n \\end{tabular} \n \\\\" << endl;
     
     
     pl_dout << L"\\begin{tabular}{|l|l|} \\hline" << endl;
     pl_dout << L" \\multicolumn{2}{|c|}{";
     pl_dout << L"Heap";
     pl_dout << L"}\\\\\\hline \\hline" << endl;
     //pl_trail
     
     for (int i = 0; i < pl_H; i++) {
	pl_HeapCell hc = pl_Heap[i];
	switch (hc.type) {
	   case pl_htReference: {
	      
	      pl_dout << L"REF & " << (((int)hc.var.reference)-((int)pl_Heap))/sizeof(pl_HeapCell)<< L"\\\\" << endl;
	   }; break;
	   case pl_htReal:{
	      pl_dout << L"REAL & " << hc.real.number << L"\\\\" << endl;
	   }; break;
	   case pl_htInteger:{
	      pl_dout << L"INT & " << hc.integer.number << L"\\\\" << endl;
	   }; break;
	   case pl_htStructure:{
	      pl_dout << L"STR & " << pl_idToName(pl_getname(hc.str.str)) << L"/" << pl_getarity(hc.str.str) << L"\\\\" << endl;
	   }; break;
	};
     };

     pl_dout << L"\\hline \n \\end{tabular} \n \\\\" << endl;
#endif
  }
}
