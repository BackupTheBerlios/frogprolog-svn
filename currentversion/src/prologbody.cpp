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
#include "enginefactory.h"

namespace UtiProlog
{

  Program* Program::instance = NULL;

  void Program::init()
  {
    if (instance != NULL)
    {
      delete instance;
      instance = NULL;
    };
  }

  Program* Program::getInstance()
  {
    if (instance == NULL)
    {
      instance = EngineFactory::getInstance()->intern_createProgram();
    };
    return instance;
  }

  Body::Body()
  {
    elements.deleteItems = true;
  }

  Body::~Body() {}
  ;

  BaseEngine* Body::copy()
  {
    Body* newbody = EngineFactory::getInstance()->createBody();

    newbody->pos = pos;
    for (int i = 0; i < elementCount(); i++)
    {
      newbody->addElement((BodyPart*)getElement(i)->copy());
    };
    return newbody;
  }

  void Body::exchangevar(int oldname, int newname)
  {
    for (int i = 0; i < elementCount(); i++)
    {
      getElement(i)->exchangevar(oldname, newname);
    };
  };

  void Body::output(CUtiString &str)
  {

    if (elements.count != 0)
    {
      for (int i = 0; i < elementCount(); i++)
      {
        getElement(i)->output(str);
        if (i != elementCount()-1)
          str += L"; ";
      }
    };

  };

  BodyPart::BodyPart()
  {
    elements.deleteItems = true;
  }

  BodyPart::~BodyPart() {}

  BaseEngine* BodyPart::copy()
  {
    BodyPart* newbody = EngineFactory::getInstance()->createBodyPart();

    newbody->pos = pos;
    for (int i = 0; i < elementCount(); i++)
    {
      newbody->addElement((Goal*)getElement(i)->copy());
    };
    return newbody;
  }

  void BodyPart::exchangevar(int oldname, int newname)
  {
    for (int i = 0; i < elementCount(); i++)
    {
      getElement(i)->exchangevar(oldname, newname);
    };
  };

  void BodyPart::output(CUtiString &str)
  {

    if (elements.count != 0)
    {

      for (int i = 0; i < elementCount(); i++)
      {
        getElement(i)->output(str);
        if (i != elementCount()-1)
          str += L", ";
      }
    };

  };

  Goal::Goal()
  {
    bengine = NULL;
    goal = gTerm;
  }

  Goal::~Goal()
  {
    if (bengine)
      delete bengine;
  };

  BaseEngine* Goal::copy()
  {
    Goal* newbody = EngineFactory::getInstance()->createGoal();
    newbody->pos = pos;
    newbody->setElement(getElement()->copy());
    newbody->setGoal(getGoal());
    return newbody;
  }

  void Goal::exchangevar(int oldname, int newname)
  {
    if (goal == gTerm)
    {
      ((Term*)bengine)->exchangevar(oldname, newname);
    };
    if (goal == gBody)
    {
      ((Body*)bengine)->exchangevar(oldname, newname);
    };
    if (goal == gNotBody)
    {
      ((Goal*)bengine)->exchangevar(oldname, newname);
    };
  };

  void Goal::output(CUtiString &str)
  {
    if (goal == gTerm)
    {
      bengine->output(str);
    };
    if (goal == gBody)
    {
      str += L"("; bengine->output(str);str += L")";
    };
    if (goal == gNotBody)
    {
      str += L"\\+ "; bengine->output(str);
    };

  };

  Rule::Rule()
  {
    guard = NULL;
    body = NULL;
    head.deleteItems = true;
  };

  Rule::~Rule()
  {
    if (guard)
      delete guard;
    if (body)
      delete body;
  };

  Fact::Fact()
  {
    head = NULL;
    body = NULL;
    helper = NULL;
    hasBodyVars = false;
    hasHeadVars = false;
    searched = false;
    BodyVarsCount=0;
    HeadVarsCount=0;
    factpos = 0;
    singlefact = true;
    foreign = false;
  }

  void Fact::setSingleFact(bool b)
  {
    singlefact = b;
  };

  Fact::~Fact()
  {
    if (head)
      delete head;
    if (body)
      delete body;
  }

  void Fact::searchTerm(Term* term, bool head, Goal* currentgoal)
  {
    term->setFactParent(this);
    if (dynamic_cast<Structure*>(term))
    {
      searchStructure((Structure*)term, head, currentgoal);
    }
    else if (dynamic_cast<Var*>(term))
    {
      Var* v = (Var*)term;
      CUtiString n = idbase.idToIdentifier(v->getName());
      // wcout << n.c_str() << endl;
      if (n != L"_")
      {

        if (Vars.find(v->getName()) == Vars.end())
        {
          VarInfo info;
          info.firstgoal = currentgoal;
          info.permanent = false || head;
          info.headvar = head;
          if (head)
          {
            hasHeadVars = true;
            HeadVarsCount++;
          }
          else
          {
            hasBodyVars = true;
            BodyVarsCount++;
          };
          Vars[v->getName()] = info;
          if (head)
          {
            int c = headvars.size();
            headvars[v->getName()] =c;
          };
        }
        else
        {
          VarInfo &info = Vars[v->getName()];
          if (info.permanent == false && info.firstgoal != currentgoal)
          {
            info.permanent = true;
          };
        }
      };
    };
  }

  void Fact::searchStructure(Structure* t, bool head, Goal* currentgoal)
  {
    t->setFactParent(this);

    for (int i = 0; i < t->elementCount(); i++)
    {
      Term* term = t->getElement(i);
      searchTerm(term, head, currentgoal);
    };
  }


  void Fact::searchBody(Body* t)
  {
    t->setFactParent(this);
    for (int i = 0; i < t->elementCount(); i++)
    {
      searchBodyPart(t->getElement(i));
    };
  }

  void Fact::searchBodyPart(BodyPart* t)
  {
    t->setFactParent(this);
    for (int i = 0; i < t->elementCount(); i++)
    {
      searchGoal(t->getElement(i));
    };
  }

  void Fact::searchGoal(Goal* t)
  {
    t->setFactParent(this);
    switch (t->getGoal())
    {
    case gTerm:
      {
        searchTerm((Term*)t->getElement(), false, t);
      }
      ;
      break;
    case gBody:
      {
        searchBody((Body*)t->getElement());
      }
      ;
      break;
    case gNotBody:
      {
        searchGoal((Goal*)t->getElement());
      };
    };
  }

  void Fact::searchVars()
  {
    if (!searched)
    {

      if (getHead() !=  NULL)
        searchStructure(getHead(), true, NULL);
      if (getBody() !=  NULL)
        searchBody(getBody());
      map<PID, VarInfo>::iterator it;
      int count = 0;
      for (it = Vars.begin(); it != Vars.end(); it++)
      {
        VarInfo &info = it->second;
        if (info.permanent)
        {
          permanentvars[it->first] = count;
          count++;
        };
      };
    }
    searched = true;
  }

  void Fact::output(CUtiString &str)
  {
    if (head)
      head->output(str);
    if (body)
    {
      str += L" :- ";
      body->output(str);
    };
    str += L".";

  };



  ForeignFact::ForeignFact()
  {
    stype = stDll;
    directcall = true;
  }

  ForeignFact::~ForeignFact() {}

  void ForeignFact::output(CUtiString &str)
  {
    if (directcall)
    {
      Fact::output(str);
      return;
    }
    if (head)
    {
      str += idbase.idToIdentifier(head->getName());
    };
    if (parameter.size())
    {
      str += L"(";
      for (int i = 0; i < parameter.size(); i++)
      {
        CallInfo inf = parameter[i];
        str += idbase.idToIdentifier(dynamic_cast<Var*>(getHead()->getElement(i))->getName());
        str += L":";
        switch (inf.type)
        {
        case ci_in_Integer:
          {
            str += L"+integer";
          }
          ;
          break;
        case ci_in_Float:
          {
            str += L"+float";
          }
          ;
          break;
        case ci_in_String:
          {
            str += L"+string";
          }
          ;
          break;
        case ci_in_Atom:
          {
            str += L"+atom";
          }
          ;
          break;
        case ci_out_Integer:
          {
            str += L"-integer";
          }
          ;
          break;
        case ci_out_Float:
          {
            str += L"-float";
          }
          ;
          break;
        case ci_out_String:
          {
            str += L"-string";
          }
          ;
          break;
        case ci_out_Atom:
          {
            str += L"-atom";
          }
          ;
          break;
        };
        if (i != parameter.size()
            -1)
          str += L", ";
      };
      str += L")";
    };
    str += L".";
  };

  Program::Program()
  {
    elements.deleteItems = true;
    rules.deleteItems = true;
    buildinlist.deleteItems = true;
    haserror = false;
    operators.deleteItems = true;
    levels.deleteItems = true;
    modules.deleteItems = true;
    //   prog = this;
    idbase.identifierToID(L"\\+");
    idbase.identifierToID(L"not");
    addOperator(700, opXFX, idbase.identifierToID(L"="));
    addOperator(700, opXFX, idbase.identifierToID(L"<"));
    addOperator(700, opXFX, idbase.identifierToID(L"=.."));
    addOperator(700, opXFX, idbase.identifierToID(L"=@="));
    addOperator(700, opXFX, idbase.identifierToID(L"=:="));
    addOperator(700, opXFX, idbase.identifierToID(L"=<"));
    addOperator(700, opXFX, idbase.identifierToID(L"=="));
    addOperator(700, opXFX, idbase.identifierToID(L"=\\="));
    addOperator(700, opXFX, idbase.identifierToID(L">"));
    addOperator(700, opXFX, idbase.identifierToID(L">="));
    addOperator(700, opXFX, idbase.identifierToID(L"@<"));
    addOperator(700, opXFX, idbase.identifierToID(L"@=<"));
    addOperator(700, opXFX, idbase.identifierToID(L"@>"));
    addOperator(700, opXFX, idbase.identifierToID(L"@>="));
    addOperator(700, opXFX, idbase.identifierToID(L"\\="));
    addOperator(700, opXFX, idbase.identifierToID(L"\\=="));
    addOperator(700, opXFX, idbase.identifierToID(L"is"));
    addOperator(600, opXFY, idbase.identifierToID(L":"));
    addOperator(500, opYFX, idbase.identifierToID(L"+"));
    addOperator(500, opYFX, idbase.identifierToID(L"-"));
    addOperator(500, opYFX, idbase.identifierToID(L"/\\"));
    addOperator(500, opYFX, idbase.identifierToID(L"\\/"));
    addOperator(500, opYFX, idbase.identifierToID(L"xor"));
    addOperator(500, opFX, idbase.identifierToID(L"+"));
    addOperator(500, opFX, idbase.identifierToID(L"-"));
    addOperator(500, opFX, idbase.identifierToID(L"?"));
    addOperator(500, opFX, idbase.identifierToID(L"\\"));
    addOperator(400, opYFX, idbase.identifierToID(L"*"));
    addOperator(400, opYFX, idbase.identifierToID(L"/"));
    addOperator(400, opYFX, idbase.identifierToID(L"//"));
    addOperator(400, opYFX, idbase.identifierToID(L"rdiv"));
    addOperator(400, opYFX, idbase.identifierToID(L"<<"));
    addOperator(400, opYFX, idbase.identifierToID(L">>"));
    addOperator(400, opYFX, idbase.identifierToID(L"mod"));
    addOperator(400, opYFX, idbase.identifierToID(L"rem"));
    addOperator(200, opXFX, idbase.identifierToID(L"**"));
    addOperator(200, opXFY, idbase.identifierToID(L"^"));
  }

  void Program::addOperator(int pr, TOperatorType t, PID name)
  {
    Operator* op = new Operator();
    op->precedence  = pr;
    op->type = t;
    op->name = name;
    operators.Add(op);
    ///TODO: Effizienter machen. Das hier ist n*n
    updateOpList();
  }

  int  opcompare(const void *elem1, const void *elem2 )
  {
    OperatorLevel* op1 = *((OperatorLevel**)(elem1));
    OperatorLevel* op2 = *((OperatorLevel**)(elem2));
    if (op1->precedence > op2->precedence)
    {
      return 1;
    }
    else if (op1->precedence < op2->precedence)
    {
      return -1;
    }
    else
    {
      return 0;
    }
  };

  void Program::updateOpList()
  {
    levels.Clear();
    map<int, OperatorLevel*> l;
    for (int i = 0; i < operators.count; i++)
    {
      Operator* op = (Operator*) operators[i];
      OperatorLevel* oplevel;
      if (l.find(op->precedence) == l.end())
      {
        oplevel = new OperatorLevel();
        oplevel->precedence = op->precedence;
        l[op->precedence] = oplevel;
        levels.Add(oplevel);
      }
      else
      {
        oplevel = l[op->precedence];
      };
      if (oplevel->obinfo.find(op->name) == oplevel->obinfo.end())
      {
        OperatorInfo info;
        memset(&info, 0, sizeof(info));
        oplevel->obinfo[op->name] = info;
      };
      OperatorInfo& opinfo = oplevel->obinfo[op->name];
      switch (op->type)
      {
      case opXFX:
        {
          opinfo.XFX = op;
        }
        ; break;
      case opYFX:
        {
          opinfo.YFX = op;
        }
        ; break;
      case opXFY:
        {
          opinfo.XFY = op;
        }
        ; break;
      case opXF:
        {
          opinfo.XF = op;
        }
        ; break;
      case opYF:
        {
          opinfo.YF = op;
        }
        ; break;
      case opFX:
        {
          opinfo.FX = op;
        }
        ; break;
      case opFY:
        {
          opinfo.FY = op;
        }
        ; break;

      };
    };
    levels.Sort(opcompare);
  }

  Program::~Program() {}

  void Program::addLibDir(const CUtiString & name)
  {
    libdirs.push_back(name);
  }


  void Program::RegisterPredicate(BaseBuildInPredicate* pred)
  {
    FactInfo info;
    info.arity = pred->getArity();
    info.name = idbase.identifierToID(pred->getName());
    buildinlist.Add(pred);
    buildin[info] = pred;
  };

  BaseBuildInPredicate* Program::getRegisterPredicate(Structure* str)
  {
    FactInfo in;
    in.arity = str->elementCount();
    in.name = str->getName();
    BUILDINMAP::iterator iter = buildin.find(in);
    if (iter != buildin.end())
    {
      return iter->second;
    }
    else
    {
      return NULL;
    };
  }

  FactInfo Fact::getFactInfo()
  {
    FactInfo info;
    info.name = getHead()->getName();
    info.arity = getHead()->elementCount();
    return info;
  }

  void Fact::setFactPos(int p)
  {
    factpos = p;
  };

  bool Program::isDynamic(PID name, int arity)
  {
    FactInfo fi;
    fi.name = name;
    fi.arity = arity;
    if (dynamicfacts.find(fi) != dynamicfacts.end())
    {
      return true;
    };
    return false;
  };

  void Program::createConstraintRules()
  {
    DYNAMICSET::iterator it;
    for (it = constraintfacts.begin(); it != constraintfacts.end(); it++)
    {
      createConstraintRule(*it);
    };

  }

  void Program::createConstraintRule(FactInfo info)
  {
    RULEMAP::iterator it = constraintinfo.find(info);
    RULEVECTOR & v = it->second;
    Fact* f = EngineFactory::getInstance()->createFact();
    Structure* head = EngineFactory::getInstance()->createStructure();
    head->setName(info.name);
    PID* con_vars = new PID[info.arity];
    PID* old_vars = new PID[info.arity];
    bool* replace = new bool[info.arity];
    for (int i = 0; i < info.arity; i++)
    {
      Var* v = EngineFactory::getInstance()->createVar();
      CUtiString s = L"a";
      s += i;
      con_vars[i] = idbase.identifierToID(s.c_str());
      v->setName(con_vars[i]);
      head->addElement(v);
      /// @todo hey hier fehlt es wenn keine Variablen verwendet werden

    };
    f->setHead(head);
    Body* mainbody = EngineFactory::getInstance()->createBody();
    f->setBody(mainbody);
    for (int i = 0; i < v.size(); i++)
    {
      Rule* rule = v[i];
      if (rule->getType() != Rule::Simplification)
        continue;
      int mainheadpos = -1;
      Structure* mainhead=NULL;
      for (int i = 0; i < rule->head.count; i++)
      {
        Structure* str = (Structure*)rule->head[i];
        if (str->getName() == info.name && str->elementCount() == info.arity)
        {
          mainheadpos = i;
          mainhead = str;
          break;
        };
      };
      if (mainheadpos == -1) continue;
      BodyPart* part = EngineFactory::getInstance()->createBodyPart();
      mainbody->addElement(part);
      //Ersetzung bestimmen
      for (int i = 0; i < info.arity; i++)
      {
        Term* t = mainhead->getElement(i);
        if (dynamic_cast<Var*>(t))
        {
          replace[i] = true;
          old_vars[i] = ((Var*)t)->getName();
        }
        else
        {
          old_vars[i] = 0;
          replace[i] = false;
          Goal* replacegoal = EngineFactory::getInstance()->createGoal();
          replacegoal->setGoal(gTerm);
          Structure* gleich = EngineFactory::getInstance()->createStructure();
          replacegoal->setElement(gleich);
          part->addElement(replacegoal);
          gleich->setName(idbase.identifierToID("="));

          Var* newvar = EngineFactory::getInstance()->createVar();
          newvar->setName(con_vars[i]);
          gleich->addElement(newvar);
          gleich->addElement((Term*)mainhead->getElement(i)->copy());
        };
      };
      //Jetzt die einzelnen anderen Constraints checken
      PID* constraint_id = new PID[rule->head.count];
      for (int i = 0; i < rule->head.count; i++)
      {
        Structure* str = (Structure*)rule->head[i];
        if (str == mainhead)
        {
          constraint_id[i] = -1;
          continue;
        };
        Goal* findconstraint = EngineFactory::getInstance()->createGoal();
        findconstraint->setGoal(gTerm);
        Structure* fc = EngineFactory::getInstance()->createStructure();
        findconstraint->setElement(fc);
        part->addElement(findconstraint);
        fc->setName(idbase.identifierToID("findconstraint"));

        Structure* constraint = (Structure*)str->copy();
        //Ersetzen
        for (int j = 0; j < info.arity; j++)
          if (replace[j])
            constraint->exchangevar(old_vars[j], con_vars[j]);

        fc->addElement(constraint);
        CUtiString s = L"nr_";
        s += i;
        constraint_id[i] = idbase.identifierToID(s.c_str());
        Structure* nr = EngineFactory::getInstance()->createStructure();
        nr->setName(constraint_id[i]);
        fc->addElement(nr);
      };
      //Ok Constraints geladen
      //Jetzt ist der Guard dran
      if (rule->getGuard())
      {
        Goal* guard = EngineFactory::getInstance()->createGoal();
        guard->setGoal(gBody);
        Body* g = (Body*)rule->getGuard()->copy();
        for (int j = 0; j < info.arity; j++)
          if (replace[j])
            g->exchangevar(old_vars[j], con_vars[j]);
        guard->setElement(g);
        part->addElement(guard);
      };
      //Ok Guard hat akzeptiert weg mit den Constraints
      for (int i = 0; i < rule->head.count; i++)
      {
        Structure* str = (Structure*)rule->head[i];
        if (str == mainhead)
        {
          continue;
        };
        Goal* deleteconstraint = EngineFactory::getInstance()->createGoal();
        deleteconstraint->setGoal(gTerm);
        Structure* fc = EngineFactory::getInstance()->createStructure();
        deleteconstraint->setElement(fc);
        part->addElement(deleteconstraint);
        fc->setName(idbase.identifierToID("deleteconstraint"));

        Structure* nr = EngineFactory::getInstance()->createStructure();
        nr->setName(constraint_id[i]);
        fc->addElement(nr);
      };
      //Cut
      Goal* cut = EngineFactory::getInstance()->createGoal();
      cut->setGoal(gTerm);
      Structure* fc = EngineFactory::getInstance()->createStructure();
      cut->setElement(fc);
      part->addElement(cut);
      fc->setName(idbase.identifierToID("!"));

      //Jetzt ist der Body dran
      if (rule->getBody())
      {
        Goal* guard = EngineFactory::getInstance()->createGoal();
        guard->setGoal(gBody);
        Body* g = (Body*)rule->getBody()->copy();
        for (int j = 0; j < info.arity; j++)
          if (replace[j])
            g->exchangevar(old_vars[j], con_vars[j]);
        guard->setElement(g);
        part->addElement(guard);
      };

      delete [] constraint_id;

    };

    addElement(f);
    delete [] con_vars;
    delete [] old_vars;
    delete [] replace;
  }

  void Program::addElement(Fact* t)
  {
    elements.Add(t);
    if (t->getHead() == NULL)
      return;
    FactInfo info;
    info = t->getFactInfo();
    FACTMAP::iterator it = factinfo.find(info);
    if (it != factinfo.end())
    {
      FACTVECTOR & v = it->second;
      t->setFactPos(v.size());
      if (v.size()==1)
        v[0]->setSingleFact(false);
      t->setSingleFact(false);
      v.push_back(t);
    }
    else
    {
      FACTVECTOR v;
      t->setFactPos(0);
      //t->setSingleFact(false);
      t->setSingleFact(true);
      Structure* str = t->getHead();
      for (int i = 0; i < str->elementCount(); i++)
      {
        if (!dynamic_cast<Var*>(str->getElement(i)))
        {
          t->setSingleFact(false);
          break;
        };
      };
      v.push_back(t);
      factinfo[info] = v;
    };
  };

  void Program::addRule(Rule* r)
  {
    for (int i = 0; i < r->head.count; i++)
    {
      Structure* str = (Structure*)r->head[i];
      FactInfo info;
      info.name = str->getName();
      info.arity = str->elementCount();
      RULEMAP::iterator it = constraintinfo.find(info);
      if (it != constraintinfo.end())
      {
        RULEVECTOR & v = it->second;
        v.push_back(r);
      }
      else
      {

        constraintfacts.insert(info);
        RULEVECTOR v;
        v.push_back(r);
        constraintinfo[info] = v;
        wcout << L"Constraint " << idbase.idToIdentifier(info.name) << L"/" << info.arity << endl;
        //str->error(L"Dieses Constraint wurde nicht deklariert");
      };
    };
  }

  void Program::output(CUtiString &str)
  {

    if (elements.count != 0)
    {
      for (int i = 0; i < elementCount(); i++)
      {
        str += L"// ";
        getElement(i)->output(str);
        if (i != elementCount()-1)
          str += L"\n";
      }
    };

  };

  void Program::parseDirectCall(BaseTarget* t, Structure* str)
  {

    if (str->getName() == idbase.identifierToID("dynamic"))
    {
      parseInfo(t, str, itDynamic);
    }
    else if (str->getName() == idbase.identifierToID("foreign"))
    {
      parseForeignInfo(t, str);
    }
    else if (str->getName() == idbase.identifierToID("chr_constraint"))
    {
      parseNewConstraintInfo(t, str);
    }
    else if (str->getName() == idbase.identifierToID("constraints"))
    {
      parseInfo(t, str, itConstraint);
    }
    else if (str->getName() ==idbase.identifierToID("op") && str->elementCount() == 3)
    {
       parseOperator(t, str);
    }
    ;
  }

  void Program::parseDirectCalls(BaseTarget* t)
  {
    for (int i = 0; i < elementCount(); i++)
    {
      Fact* f = getElement(i);
      if (!f->getHead() && f->getBody())
      {
        Body* b = f->getBody();
        for (int j = 0; j < b->elementCount(); j++)
        {
          BodyPart* bp = b->getElement(j);
          for (int k = 0; k < bp->elementCount(); k++)
          {
            Goal* g = bp->getElement(k);
            if (g->getGoal() == gTerm)
            {
              if (dynamic_cast<Structure*>(g->getElement())
                 )
              {
                Structure* str = (Structure*)g->getElement();
                parseDirectCall(t, str);
              };
            };
          };
        };
      };
    };
  }
  void Program::parseOperator(BaseTarget* t, Structure* f)
  {
     IntNumber* precedence = dynamic_cast<IntNumber*>(f->getElement(0));
     Structure* type = dynamic_cast<Structure*>(f->getElement(1));
     Structure* name = dynamic_cast<Structure*>(f->getElement(2));
     if (!precedence || !type || !name || !(type->elementCount() == 0) || !(name->elementCount() == 0)) {
        error(L"Fehler bei op");
     };
     if (!(precedence->getValue() >= 0 || precedence->getValue() <= 1200)) {
        error(L"op: precedence ist nicht im gültigen Bereich");
        return;
     };
     int d_pr = precedence->getValue();
     TOperatorType optype = opXFY;
     if (type->getName() == idbase.identifierToID("fx")) {
        optype = opFX;
     } else if (type->getName() == idbase.identifierToID("fy")) {
        optype = opFY;
     } else if (type->getName() == idbase.identifierToID("xf")) {
        optype = opXF;
     } else if (type->getName() == idbase.identifierToID("yf")) {
        optype = opYF;
     } else if (type->getName() == idbase.identifierToID("xfx")) {
        optype = opXFX;
     } else if (type->getName() == idbase.identifierToID("yfx")) {
        optype = opYFX;
     } else if (type->getName() == idbase.identifierToID("xfy")) {
        optype = opXFY;
     } else {
        error(L"op: type ist ungültig.");
        return;
     };
     addOperator(d_pr, optype,name->getName());
  };
  
  void Program::parseForeignInfo(BaseTarget* t, Structure* f)
  {
    ///* todo besseres System
    if (f->elementCount() != 3)
    {
      error(L"Fehler bei Foreign");
      return;
    };
    CUtiString predname;
    int arity;
    CUtiString cppname;
    CUtiString hname;
    Structure* str = dynamic_cast<Structure*>(f->getElement(0));
    if (str && str->elementCount() == 2  && str->getName() == idbase.identifierToID("/"))
    {
      Structure* atom = dynamic_cast<Structure*>(str->getElement(0));
      IntNumber* n = dynamic_cast<IntNumber*>(str->getElement(1));
      if (n && atom && atom->elementCount() ==0)
      {
        predname = idbase.idToIdentifier(atom->getName());
        arity = n->getValue();
      }
      else
      {
        error(L"Fehler bei foreign");
      };
    }
    else
    {
      error(L"Fehler bei foreign");
    };

    str = dynamic_cast<Structure*>(f->getElement(1));
    if (str && str->elementCount() == 0)
    {
      cppname = idbase.idToIdentifier(str->getName());
    }
    else
    {
      error(L"Fehler bei foreign");
    };
    str = dynamic_cast<Structure*>(f->getElement(2));
    if (str && str->elementCount() == 0)
    {
      hname = idbase.idToIdentifier(str->getName());
    }
    else
    {
      error(L"Fehler bei foreign");
    };
    this->ForeignPredicate(predname, cppname, arity, hname);
  };

  void Program::parseInfo(BaseTarget* t, Structure* f, TInfoType type)
  {
    for (int i = 0; i < f->elementCount(); i++)
    {
      Structure* str = dynamic_cast<Structure*>(f->getElement(i));
      if (str && str->elementCount() == 2  && str->getName() == idbase.identifierToID("/"))
      {
        Structure* atom = dynamic_cast<Structure*>(str->getElement(0));
        IntNumber* n = dynamic_cast<IntNumber*>(str->getElement(1));
        if (n && atom && atom->elementCount() ==0)
        {
          switch (type)
          {
          case itDynamic:
            {
              registerDynamicElement(atom->getName(), n->getValue());
            }
            ;
            break;
          case itConstraint:
            {
              registerConstraintElement(atom->getName(), n->getValue());
            };
          };
        }
        else
        {
          error(L"Fehler bei Constraint");
        };
      }
      else
      {
        error(L"Fehler bei Dynamic");
      };
    };
  };

  void Program::parseNewConstraintInfo(BaseTarget* t, Structure* f)
  {
    for (int i = 0; i < f->elementCount(); i++)
    {
      Structure* str = dynamic_cast<Structure*>(f->getElement(i));
      if (str && str->elementCount() == 2  && str->getName() == idbase.identifierToID("/"))
      {
        Structure* atom = dynamic_cast<Structure*>(str->getElement(0));
        IntNumber* n = dynamic_cast<IntNumber*>(str->getElement(1));
        if (n && atom && atom->elementCount() ==0)
        {

          registerConstraintElement(atom->getName(), n->getValue());
        }
        else
        {
          error(L"Fehler bei Constraint");
        };
      }
      else
      {
        registerConstraintElement(str->getName(), str->elementCount());
      };

    };
  };
  void Program::registerDynamicElement(PID name, int arity)
  {
    FactInfo fi;
    fi.arity = arity;
    fi.name = name;
    dynamicfacts.insert(fi);
  }
  void Program::registerConstraintElement(PID name, int arity)
  {
    /*  FactInfo fi;
    fi.arity = arity;
    fi.name = name;
    constraintfacts.insert(fi);
    RULEVECTOR r;
    constraintinfo[fi] = r;*/
  }

  Structure* plc_str(PID name, Term* t1,Term* t2,
                     Term* t3,Term* t4,Term* t5,
                     Term* t6,
                     Term* t7,
                     Term* t8)
  {
    Structure* structure = EngineFactory::getInstance()->createStructure();
    structure->setName(name);
    if (!t1) return structure;
    structure->addElement(t1);
    if (!t2) return structure;
    structure->addElement(t2);
    if (!t3) return structure;
    structure->addElement(t3);
    if (!t4) return structure;
    structure->addElement(t4);
    if (!t5) return structure;
    structure->addElement(t5);
    if (!t6) return structure;
    structure->addElement(t6);
    if (!t7) return structure;
    structure->addElement(t7);
    if (!t8) return structure;
    structure->addElement(t8);
    return structure;
  }
  Structure* plc_strN(PID name, vector<Term*> terme)
  {
    Structure* structure = EngineFactory::getInstance()->createStructure();
    structure->setName(name);
    for (int i = 0; i < terme.size(); i++)
    {
      structure->addElement(terme[i]);
    };
    return structure;
  };

  Var* plc_var(PID name)
  {
    Var* var = EngineFactory::getInstance()->createVar();
    //  SETPOS(var);
    var->setName(name);
    return var;
  }

  IntNumber* plc_int(int integer)
  {
    IntNumber* i = EngineFactory::getInstance()->createIntNumber();
    //SETPOS(integer);
    i->setValue(integer);

    return i;
  }
  RealNumber* plc_real(float real)
  {
    RealNumber* r = EngineFactory::getInstance()->createRealNumber();
    r->setValue(real);
    return r;
  }
  Term* plc_listN(vector<Term*> terme)
  {

    Structure* res;
    Term* first;
    for (int i = 0; i < terme.size(); i++)
    {
      Term* t = terme[i];
      Structure* structure = EngineFactory::getInstance()->createStructure();
      structure->setName(EngineFactory::getInstance()->registerAtomW(L"."));
      structure->addElement(t);
      if (res)
      {
        res->addElement(structure);
      }
      else
      {
        first = structure;
      }
      res = structure;
    };
    Structure* structure = EngineFactory::getInstance()->createStructure();

    structure->setName(EngineFactory::getInstance()->registerAtomW(L"[]"));
    if (res)
    {
      res->addElement(structure);
    }
    else
    {
      first = structure;
    }
    res = structure;

    return first;
  };
  Structure* plc_listEL(Term* head, Term* trail)
  {
    Structure* structure = EngineFactory::getInstance()->createStructure();
    structure->setName(EngineFactory::getInstance()->registerAtomW(L"."));
    structure->addElement(head);
    structure->addElement(trail);
    return structure;
  }
  Goal* plc_goal(Term* g)
  {
    Goal* goal = EngineFactory::getInstance()->createGoal();
    goal->setGoal(gTerm);
    goal->setElement(g);
    return goal;
  };
  Goal* plc_notgoal(Term* g)
  {
    Goal* goal = EngineFactory::getInstance()->createGoal();
    goal->setGoal(gNotBody);
    goal->setElement(g);
    return goal;
  };

  Goal* plc_goal(Body* b)
  {
    Goal* goal = EngineFactory::getInstance()->createGoal();
    goal->setGoal(gBody);
    goal->setElement(b);
    return goal;
  }

  Structure* plc_true()
  {
    return plc_str(EngineFactory::getInstance()->registerAtomW(L"true"));
  }

  Structure* plc_false()
  {
    return plc_str(EngineFactory::getInstance()->registerAtomW(L"false"));
  }
  Structure* plc_fail()
  {
    return plc_str(EngineFactory::getInstance()->registerAtomW(L"fail"));
  }
  Structure* plc_cut()
  {
    return plc_str(EngineFactory::getInstance()->registerAtomW(L"!"));
  }
  Structure* plc_equal(Term*t1, Term*t2)
  {
    return plc_str(EngineFactory::getInstance()->registerAtomW(L"="), t1, t2);
  }
  PID plc_name(wchar_t*t)
  {
    return EngineFactory::getInstance()->registerAtomW(L"\\=");
  };

  Structure* plc_notequal(Term*t1, Term*t2)
  {
    return plc_str(EngineFactory::getInstance()->registerAtomW(L"\\="), t1, t2);
  }
  Body* plc_bodylist(BaseEngine* e1,
                     BaseEngine* e2,
                     BaseEngine* e3,
                     BaseEngine* e4,
                     BaseEngine* e5,
                     BaseEngine* e6,
                     BaseEngine* e7,
                     BaseEngine* e8,
                     BaseEngine* e9,
                     BaseEngine* e10)
  {
    Body* body = EngineFactory::getInstance()->createBody();
    BodyPart* current;
    Goal* newgoal = NULL;
    //      assert(newgoal != NULL);
#define ADD(A) \
   if (A == NULL) return body;\
    if (dynamic_cast<BodyPart*>(A)) {\
      current = NULL;\
      body->addElement((BodyPart*)A);\
   } else {\
      if (dynamic_cast<Term*>(A)) {\
         newgoal = plc_goal((Term*)A);\
      } else if (dynamic_cast<Body*>(A)) {\
         newgoal = plc_goal((Body*) A);\
      } else if (dynamic_cast<Goal*>(A)) {\
         newgoal = (Goal*)A;\
      };\
   \
      if (current == NULL) {\
	 current = EngineFactory::getInstance()->createBodyPart();\
	 body->addElement(current);\
      };\
      current->addElement(newgoal);\
   }

    ADD(e1);
    ADD(e2);
    ADD(e3);
    ADD(e4);
    ADD(e5);
    ADD(e6);
    ADD(e7);
    ADD(e8);
    ADD(e9);
    ADD(e10);
#undef ADD
    return body;
  }
  BodyPart* plc_bodypartlist(BaseEngine* e1,
                             BaseEngine* e2,
                             BaseEngine* e3,
                             BaseEngine* e4,
                             BaseEngine* e5,
                             BaseEngine* e6,
                             BaseEngine* e7,
                             BaseEngine* e8,
                             BaseEngine* e9,
                             BaseEngine* e10)
  {
    BodyPart* body = EngineFactory::getInstance()->createBodyPart();
    Goal* newgoal = NULL;

#define ADD(A) \
   if (A == NULL) return body;\
      if (dynamic_cast<Term*>(A)) {\
         newgoal = plc_goal((Term*)A);\
} else if (dynamic_cast<Body*>(A)) {\
         newgoal = plc_goal((Body*) A);\
} else if (dynamic_cast<Goal*>(A)) {\
         newgoal = (Goal*)A;\
};\
   \
      body->addElement(newgoal);\

   ADD(e1);
    ADD(e2);
    ADD(e3);
    ADD(e4);
    ADD(e5);
    ADD(e6);
    ADD(e7);
    ADD(e8);
    ADD(e9);
    ADD(e10);
#undef ADD
    return body;
  }
  Fact* plc_fact(Structure* head, Body* body, bool foreign)
  {
    Fact* fact = EngineFactory::getInstance()->createFact();
    fact->setHead(head);
    fact->setBody(body);
    fact->foreign = foreign;
    return fact;
  };

  void plc_factadd(Structure* head, Body* body, bool foreign)
  {
    plc_addfact(plc_fact(head, body, foreign));
  }

  void plc_addfact(Fact* f)
  {
    Program::getInstance()->addElement(f);
  }

}
