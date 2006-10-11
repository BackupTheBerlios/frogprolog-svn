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

#ifndef __PROLOGENGINE__
#define __PROLOGENGINE__

#include <map>
#include <set>

using namespace std;

#include "identifierdatabase.h"
namespace UtiProlog {

class EngineFactory;
class BodyPart;
class Goal;
class Program;
class Term;
class Fact;
struct FactInfo
{
   PID name;
   int arity;
};

__inline int operator==(FactInfo One, FactInfo Other)
{
   return (One.name == Other.name) && (One.arity == Other.arity);
}

__inline int operator!=(FactInfo One, FactInfo Other)
{
   return !(One == Other);
}


__inline int operator<(FactInfo One, FactInfo Other)
{
   if (One == Other) return false;
   if (One.name < Other.name) return true;
   if (One.name != Other.name) return false;
   if (One.arity < Other.arity) return true;
   return false;
};
//extern Program* prog;

typedef map<PID, Term*> UNIFYMAP;

class BaseTarget : public CUtiOB
{
public:
   Program* prog;
};

class EnginePos
{
public:
	/// @todo zu viel Speicherplatz verbraucht?
   //CUtiString filename;
   int beginline;
   int begincolumn;
   int endline;
   int endcolumn;
   string* beginfile;
   string* endfile;
};

class BaseEngine : public CUtiOB
{
protected:
   
public:	
   Fact* factparent;
   Fact* owner;
   EnginePos pos;
   BaseEngine();
   ~BaseEngine();
   virtual BaseEngine* copy(){};
   virtual void error(wchar_t* text);
   virtual void perform(BaseTarget* t){};
   virtual void output(CUtiString &str){};
   virtual void setFactParent(Fact*f ){factparent = f;owner = f;};
};

enum TAllocType {atNone};

class AllocCodeHelper  : public CUtiOB
{
protected:
   BaseTarget* t;
public:
   map<PID, int> seenregisterarguments;
   map<PID, int> permanentvars;
   AllocCodeHelper(BaseTarget* _t);
   virtual void newGoal();
   virtual void get_structure(PID name, int arity, int Xi, bool permanent)=0;
   virtual void unify_variable(int Xi, bool permanent)=0;
   virtual void unify_value(int Xi, bool permanent)=0;
   virtual void unify_variable(BaseEngine* eng, PID localvar){};
   virtual void unify_value(BaseEngine* eng, PID localvar){};
   virtual void unify_variable(BaseEngine* eng, PID localvar, int Xi){};
   virtual void unify_value(BaseEngine* eng, PID localvar, int Xi){};
   virtual void put_structure(PID name, int arity, int Xi, bool permanent)=0;
   virtual void set_variable(int Xi, bool permanent)=0;
   virtual void set_value(int Xi, bool permanent)=0;
   virtual void put_variable(int Xn, bool permanent, int Ai)=0;
   virtual void put_value(int Xn, bool permanent, int Ai)=0;
   virtual void put_structure(PID name, int arity, int Xn, bool permanent, int Ai)=0;
   virtual void get_variable(int Xn, bool permanent, int Ai)=0;
   virtual void get_value(int Xn, bool permanent, int Ai)=0;
   virtual void get_structure(PID name, int arity, int Xn, bool permanent, int Ai)=0;
   
   virtual void unify_void()=0;
   
   virtual void put_integer(int number){};
   virtual void get_integer(int number){};
   virtual void put_real(float number){};
   virtual void get_real(float number){};
   virtual void get_integer(int number, int Xi){};
   virtual void get_real(float number, int Xi){};
};

class Term : public BaseEngine
{
public:
   Term();
   ~Term();
   virtual bool unify(UNIFYMAP &map, Term* other){};
   virtual void changenamespace(int add){};
   virtual void exchangevar(int oldname, int newname){};
   virtual void performGetCodeEasy(BaseTarget*t, int Xi,  int &maxX, AllocCodeHelper* helper){};
   
};

class Var : public Term
{
protected:
   PID name;
public:
   virtual void setName(PID n) {name = n;};
   virtual PID getName() {return name;};
   void output(CUtiString &str);
   Var();
   ~Var();
   BaseEngine* copy();
   bool unify(UNIFYMAP &map, Term* other);
   void changenamespace(int add);
   void exchangevar(int oldname, int newname);
   void performGetCode(BaseTarget*t, int Xi, int &maxX, AllocCodeHelper* helper);
   void performGetCodeEasy(BaseTarget*t, int Xi, int &maxX, AllocCodeHelper* helper);
};

class IntNumber : public Term
{
protected:
   int value;
public:
   IntNumber();
   ~IntNumber();
   BaseEngine* copy();
   virtual void setValue(int v){value = v;};
   virtual int getValue(){return value;};
   void output(CUtiString &str);
   bool unify(UNIFYMAP &map, Term* other);
   void performGetCode(BaseTarget*t, int Xi, int &maxX, AllocCodeHelper* helper);
   void performGetCodeEasy(BaseTarget*t, int Xi, int &maxX, AllocCodeHelper* helper);
};

class RealNumber : public Term
{
protected:
   double value;
public:
   RealNumber();
   ~RealNumber();
   BaseEngine* copy();
   virtual void setValue(double v){value = v;};
   virtual double getValue(){return value;};
   void output(CUtiString &str);
   bool unify(UNIFYMAP &map, Term* other);
   void performGetCode(BaseTarget*t, int Xi, int &maxX, AllocCodeHelper* helper);
   void performGetCodeEasy(BaseTarget*t, int Xi, int &maxX, AllocCodeHelper* helper);
  
};

class Structure : public Term
{
protected:
   PID name;
   CCacheList elements;
public:
   
   virtual void setName(PID n) {name = n;};
   virtual PID getName() {return name;};
   BaseEngine* copy();
   void output(CUtiString &str);
   virtual void addElement(Term* t) {elements.Add(t);};
   virtual Term* getElement(int index) {return (Term*)elements[index];};
   virtual void setElement(int index, Term* t) {elements[index] = t;};
   virtual void deleteElement(int index) {elements.Delete(index);};
   virtual void clearElements() {elements.Clear();};
   virtual int elementCount() {return elements.count;};
   Structure();
   ~Structure();
   bool unify(UNIFYMAP &map, Term* other);
   void changenamespace(int add);
   void exchangevar(int oldname, int newname);
   void performGetCodeEasy(BaseTarget*t, int Xi, int &maxX, AllocCodeHelper* helper);
};


class Body : public BaseEngine
{
protected:
   CCacheList elements;
public:
   virtual void addElement(BodyPart* t) {elements.Add(t);};
   virtual BodyPart* getElement(int index) {return (BodyPart*)elements[index];};
   virtual void deleteElement(int index) {elements.Delete(index);};
   virtual void clearElements() {elements.Clear();};
   virtual int elementCount() {return elements.count;};
   void output(CUtiString &str);
   void exchangevar(int oldname, int newname);
   BaseEngine* copy();
   Body();
   ~Body();
   
};

class BodyPart : public BaseEngine
{
protected:
   CCacheList elements;
public: 
   virtual void addElement(Goal* t) {elements.Add(t);};
   virtual Goal* getElement(int index) {return (Goal*)elements[index];};
   virtual void deleteElement(int index) {elements.Delete(index);};
   virtual void clearElements() {elements.Clear();};
   virtual int elementCount() {return elements.count;};
   void output(CUtiString &str);
   void exchangevar(int oldname, int newname);
   BaseEngine* copy();
   BodyPart();
   ~BodyPart();
};

//enum TGoal {gTerm, gUnification, gBody, gInstanceEqual, gIs, gFail, gTrue, gFalse, gCut};

enum TGoal {gTerm, gBody, gNotBody};

class Goal : public BaseEngine
{
protected:
   TGoal goal;
   BaseEngine* bengine;
public:
   virtual void setGoal(TGoal g) {goal = g;};
   virtual TGoal getGoal(){return goal;};
   virtual void setElement(BaseEngine* beng) {bengine = beng;};
   virtual BaseEngine* getElement() {return bengine;};
   void output(CUtiString &str);
   void exchangevar(int oldname, int newname);
   BaseEngine* copy();
   Goal();
   ~Goal();
};

class Rule : public BaseEngine
{
public:
	
	Body* guard;
	Body* body;
	
public:	
	enum TRuleType {Propagation, Simplification};
	TRuleType type;
	Rule();
	~Rule();
	CCacheList head;
	void setGuard(Body* g) {guard=g;};
	Body* getGuard(){return guard;};
	void setBody(Body* g) {body=g;};
	Body* getBody(){return body;};
	void addHead(Structure* str) {head.Add(str);};
	void setType(TRuleType r) {type = r;};
	TRuleType getType() {return type;};
};

struct VarInfo
{
   bool headvar;
   bool permanent;
   Goal* firstgoal;
};

typedef map<PID, int> HEADVARS;

class Fact : public BaseEngine
{
protected:
   bool searched;
   void searchStructure(Structure* t, bool head, Goal* currentgoal);
   void searchBody(Body* t);
   void searchBodyPart(BodyPart* t);
   void searchGoal(Goal* t);
   void searchTerm(Term* term, bool head, Goal* currentgoal);
   Structure* head;
   Body* body;
   int factpos;
   bool singlefact;
public:
   bool hasBodyVars;
   bool hasHeadVars;
   int BodyVarsCount;
   int HeadVarsCount;
   bool foreign;
   AllocCodeHelper* helper;
   map<PID, VarInfo> Vars;
   map<PID, int> permanentvars;
   HEADVARS headvars;
   FactInfo getFactInfo();
   void searchVars();
   virtual void setHead(Structure* h) {head = h;};
   virtual Structure* getHead() {return head;};
   virtual void setBody(Body* h) {body = h;};
   virtual Body* getBody() {return body;};
   void setFactPos(int p);
   void setSingleFact(bool b);
   void output(CUtiString &str);
   Fact();
   ~Fact();
};

enum TSourceType {stHeader, stDll};

enum TCallInfoType {ci_in_Integer, ci_in_Float, ci_in_String, ci_in_Atom, 
   ci_out_Integer, ci_out_Float, ci_out_String, ci_out_Atom};

struct CallInfo
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
   vector<CallInfo> parameter;
   void output(CUtiString &str);
   ForeignFact();
   ~ForeignFact();
};


class BaseBuildInPredicate : public BaseEngine {
public:
   BaseBuildInPredicate(){};
   ~BaseBuildInPredicate(){};
   virtual CUtiString getName(){return L"";};
   virtual int getArity(){return 0;};
   virtual void performCode(BaseTarget*t, Structure* s){};
};

typedef vector<Fact*> FACTVECTOR;
typedef vector<Rule*> RULEVECTOR;
typedef map<FactInfo, FACTVECTOR> FACTMAP;
typedef map<FactInfo, RULEVECTOR> RULEMAP;
typedef map<FactInfo, BaseBuildInPredicate*> BUILDINMAP;
typedef set<FactInfo> DYNAMICSET;

enum TInfoType {itDynamic, itConstraint};

enum TOperatorType {opXFX, opYFX, opXFY, opXF, opYF, opFX, opFY};

class Operator : public CUtiOB
{
public:
   int precedence;
   TOperatorType type;
   PID name;
};

struct OperatorInfo
{
   Operator* XFX;
   Operator* YFX;
   Operator* XFY;
   Operator* XF;
   Operator* YF;
   Operator* FX;
   Operator* FY;
};

class OperatorLevel : public CUtiOB
{
public:
   int precedence;
   map<PID, OperatorInfo> obinfo;
};


/**
 * Erzeugt eine neue Struktur. Die Stelligkeit wird
 * durch die Anzahl der Terme bestimmt, die angegeben werden
 * @param name Name der Struktur in Form eines Atoms
 * @param t1 Term 1
 * @param t2 Term 2
 * @param t3 ...
 * @param t4 ...
 * @param t5 ...
 * @param t6 ...
 * @param t7 ...
 * @param t8 ...
 * @return Die neue Struktur
 */
Structure* plc_str(PID name, Term* t1=NULL,Term* t2=NULL,
		   Term* t3=NULL,Term* t4=NULL,Term* t5=NULL,
		   Term* t6=NULL,
		   Term* t7=NULL,
		   Term* t8=NULL);

/**
 * Erzeugt eine neue Struktur mit beliebiger Stelligkeit
 * @param name Name der Struktur
 * @param terme Die Terme in Form eines vectors
 * @return Die neue Struktur
 */
Structure* plc_strN(PID name, vector<Term*> terme);
Var* plc_var(PID name);
IntNumber* plc_int(int integer);
RealNumber* plc_real(float real);
Term* plc_listN(vector<Term*> terme);
Structure* plc_listEL(Term* head, Term* trail);
Goal* plc_goal(Term* g);
Goal* plc_notgoal(Term* g);
Goal* plc_goal(Body* b);
Structure* plc_true();
Structure* plc_false();
Structure* plc_fail();
Structure* plc_cut();
Structure* plc_equal(Term*t1, Term*t2);
Structure* plc_notequal(Term*t1, Term*t2);
Body* plc_bodylist(BaseEngine* e1,
		   BaseEngine* e2=NULL,
		   BaseEngine* e3=NULL,
		   BaseEngine* e4=NULL,
		   BaseEngine* e5=NULL,
		   BaseEngine* e6=NULL,
		   BaseEngine* e7=NULL,
		   BaseEngine* e8=NULL,
		   BaseEngine* e9=NULL,
		   BaseEngine* e10=NULL);
BodyPart* plc_bodypartlist(BaseEngine* e1,
		   BaseEngine* e2=NULL,
		   BaseEngine* e3=NULL,
		   BaseEngine* e4=NULL,
		   BaseEngine* e5=NULL,
		   BaseEngine* e6=NULL,
		   BaseEngine* e7=NULL,
		   BaseEngine* e8=NULL,
		   BaseEngine* e9=NULL,
		   BaseEngine* e10=NULL);
Fact* plc_fact(Structure* head, Body* body, bool foreign=false);
void plc_factadd(Structure* head, Body* body, bool foreign=false);
void plc_addfact(Fact* f);
PID plc_name(wchar_t*t);

class Module : public CUtiOB {
public:
   CUtiString Name;
   CUtiString Path;
};

class Program : public BaseEngine
{
private:
   static Program* instance;
public:
   static Program* getInstance();
   static void init();
public:
   //Operatoren
   CCacheList operators;
   CCacheList levels;
   CCacheList modules;
   int getLevelCount() {return levels.count;};
   void addOperator(int pr, TOperatorType t, PID name);
   void updateOpList();
protected:
   CCacheList elements;
   CCacheList rules;
   CCacheList buildinlist;
   FACTMAP factinfo;
   BUILDINMAP buildin;
   DYNAMICSET dynamicfacts;
   DYNAMICSET constraintfacts;
   RULEMAP constraintinfo;
   vector<CUtiString> libdirs;
public: 
	
   /**
 * Searches for special predicates in fact's without a head
 * @param t the target
    */
	void parseDirectCalls(BaseTarget* t);
        void parseDirectCall(BaseTarget* t, Structure* str);
    /**
	 * Handles the predicates
	 * @param t The target
	 * @param f The term
	 * @param type Die Art des Prädikats
     */
	void parseInfo(BaseTarget* t, Structure* f, TInfoType type);
	void parseNewConstraintInfo(BaseTarget* t, Structure* f);
        void parseForeignInfo(BaseTarget* t, Structure* f);
        void parseOperator(BaseTarget* t, Structure* f);
    /**
	 * Registers a dynamic predicate
	 * @param name the name of the predicate
	 * @param arity the arity of the predicate
     */
	void registerDynamicElement(PID name, int arity);
	void registerConstraintElement(PID name, int arity);
	void createConstraintRules();
	void createConstraintRule(FactInfo info);
   /**
    * Returns true if the fact is dynamic
    * @param name name of the fact
    * @param arity arity of the fact
    * @return true if dynamic
    */
   virtual bool isDynamic(PID name, int arity);
   virtual void addElement(Fact* t);
   virtual void addRule(Rule* r);
   virtual Fact* getElement(int index) {return (Fact*)elements[index];};
   virtual void deleteElement(int index) {elements.Delete(index);};
   virtual void clearElements() {elements.Clear();};
   virtual int elementCount() {return elements.count;};
   void output(CUtiString &str);
   virtual void performModule(CUtiString name){};
   virtual void loadModule(CUtiString name){};
   void addLibDir(const CUtiString & name);
   bool haserror;
   CUtiString progname;
   Program();
   ~Program();
   void RegisterPredicate(BaseBuildInPredicate* pred);
   BaseBuildInPredicate* getRegisterPredicate(Structure* str);
   virtual void ForeignPredicate(CUtiString Atom, CUtiString CName, CallInfo* cinfo, int ccount, CUtiString Header){};
   virtual void ForeignPredicate(CUtiString Atom, CUtiString CName, int arity, CUtiString Header){};
};



};

#endif
