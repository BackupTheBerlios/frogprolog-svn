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
#ifndef __EXTERNPARSER__
#define __EXTERNPARSER__

#include "frogprolog.h"

#include <vector>
#include <string>
#include <map>

using namespace std;

namespace UtiExternProlog {
typedef FP_atom PID;

class BodyPart;
class Goal;
class Program;
class Term;
class Fact;
//extern Program* prog;

class BaseTarget {
public:
    Program* prog;
};

class EnginePos {
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


class BaseEngine {
protected:

public:
    Program* prog;
    EnginePos pos;
    BaseEngine();
    ~BaseEngine();
    virtual void perform(BaseTarget* t) {}
    ;
};

class Term : public BaseEngine {
public:
    Term();
    ~Term();

};

class Var : public Term {
protected:
    PID name;
public:
    virtual void setName(PID n) {
        name = n;
    };
    virtual PID getName() {
        return name;
    };
    Var();
    ~Var();
};

class IntNumber : public Term {
protected:
    int value;
public:
    IntNumber();
    ~IntNumber();
    virtual void setValue(int v) {
        value = v;
    };
    virtual int getValue() {
        return value;
    };
};

class RealNumber : public Term {
protected:
    double value;
public:
    RealNumber();
    ~RealNumber();
    virtual void setValue(double v) {
        value = v;
    };
    virtual double getValue() {
        return value;
    };

};

class Structure : public Term {
protected:
    PID name;
    std::vector<Term*> elements;
public:

    virtual void setName(PID n) {
        name = n;
    };
    virtual PID getName() {
        return name;
    };
    virtual void addElement(Term* t) {
        elements.push_back(t);
    };
    virtual Term* getElement(int index) {
        return (Term*)elements[index];
    };
    virtual void setElement(int index, Term* t) {
        elements[index] = t;
    };
    virtual void deleteElement(int index) {
        // elements.Delete(index);
    };
    virtual void clearElements() {
        for (int i = 0; i < elements.size(); i++)
            delete elements[i];
        elements.clear();
    };
    virtual int elementCount() {
        return elements.size();
    };
    Structure();
    ~Structure();
};

class Body : public BaseEngine {
protected:
    std::vector<BodyPart*> elements;
public:
    virtual void addElement(BodyPart* t) {
        elements.push_back(t);
    };
    virtual BodyPart* getElement(int index) {
        return (BodyPart*)elements[index];
    };
    virtual void deleteElement(int index) {
        //  elements.Delete(index);
    };
    virtual void clearElements();
    virtual int elementCount() {
        return elements.size();
    };
    Body();
    ~Body();

};

class BodyPart : public BaseEngine {
protected:
    std::vector<Goal*> elements;
public:
    virtual void addElement(Goal* t) {
        elements.push_back(t);
    };
    virtual Goal* getElement(int index) {
        return (Goal*)elements[index];
    };
    virtual void deleteElement(int index) {
        //  elements.Delete(index);
    };
    virtual void clearElements();
    virtual int elementCount();
    BodyPart();
    ~BodyPart();
};

enum TGoal {gTerm, gBody, gNotBody};

class Goal : public BaseEngine {
protected:
    TGoal goal;
    BaseEngine* bengine;
public:
    virtual void setGoal(TGoal g) {
        goal = g;
    };
    virtual TGoal getGoal() {
        return goal;
    };
    virtual void setElement(BaseEngine* beng) {
        bengine = beng;
    };
    virtual BaseEngine* getElement() {
        return bengine;
    };
    Goal();
    ~Goal();
};




class Fact : public BaseEngine {
protected:

    Structure* head;
    Body* body;
public:

    virtual void setHead(Structure* h) {
        head = h;
    };
    virtual Structure* getHead() {
        return head;
    };
    virtual void setBody(Body* h) {
        body = h;
    };
    virtual Body* getBody() {
        return body;
    };
    Fact();
    ~Fact();
};


class Rule : public BaseEngine {
public:
    std::vector<Structure*> head;
    Body* guard;
    Body* body;

public:
    enum TRuleType {Propagation, Simplification};
    TRuleType type;
    Rule();
    ~Rule();
    void setGuard(Body* g) {
        guard=g;
    };
    Body* getGuard() {
        return guard;
    };
    void setBody(Body* g) {
        body=g;
    };
    Body* getBody() {
        return body;
    };
    void addHead(Structure* str) {
        head.push_back(str);
    };
    void setType(TRuleType r) {
        type = r;
    };
    TRuleType getType() {
        return type;
    };
};

enum TOperatorType {opXFX, opYFX, opXFY, opXF, opYF, opFX, opFY};

class Operator
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


///TODO: Operatorkontrolle in externe Klasse
class OperatorLevel
{
   public:
      int precedence;
      map<PID, OperatorInfo> obinfo;
};


class Program : public BaseEngine {
private:
      static Program* instance;
public:
      static Program* getInstance();
public:
   //Operatoren
      vector<Operator*> operators;
      vector<OperatorLevel*> levels;
      int getLevelCount() {return levels.size();};
      void addOperator(int pr, TOperatorType t, PID name);
      void updateOpList();
protected:
    // CCacheList elements;
    std::vector<Fact*> elements;
public:
    virtual void addElement(Fact* t);
    virtual void addRule(Rule* f);
    virtual Fact* getElement(int index) {
        return (Fact*)elements[index];
    };
    virtual void deleteElement(int index) {
        //   elements.Delete(index);
    };
    virtual void clearElements();
    virtual int elementCount() {

        return elements.size();
    };
    bool haserror;
    Program();
    ~Program();
};

};

#endif
