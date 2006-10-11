//
// C++ Interface: enginefactory
//
// Description: 
//
//
// Author: Michael Staud <staud@linux>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef UTIPROLOGENGINEFACTORY_H
#define UTIPROLOGENGINEFACTORY_H

#ifdef __BASEPREDICATES__
#include "externparser.h"
#include "frogprolog.h"
using namespace UtiExternProlog;

namespace UtiExternProlog {
#else
#include "Uti3DCore.h"
#include "prologengine.h"
using namespace UtiProlog;

namespace UtiProlog {
#endif


/**
 * Diese Klasse ist die Basisklasse aller Fabriken für
 * die Syntaxbäume. Sie ist als Singleton implementiert;
@author Michael Staud
*/


class EngineFactory
{
private:
   static EngineFactory* factory;
public:
    EngineFactory();
    ~EngineFactory();
    static EngineFactory* getInstance();
    virtual Body* createBody();
    virtual BodyPart* createBodyPart();
    virtual Fact* createFact();
    virtual Goal* createGoal();
    virtual IntNumber* createIntNumber();
    virtual RealNumber* createRealNumber();
    virtual Structure* createStructure();
    virtual Var* createVar();
    virtual Rule* createRule();
    virtual Program* intern_createProgram();
    virtual PID registerAtom(const char* t1){
#ifdef __BASEPREDICATES__
	return FP_atom_from_string(t1);
#else
	    return 0;
#endif
    };
    virtual PID registerAtomW(const wchar_t* t1){
#ifdef __BASEPREDICATES__
	return FP_atom_from_wstring(t1);
#else
	    return 0;
#endif
    };
};

}

#endif
