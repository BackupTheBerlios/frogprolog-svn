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
#ifndef INTERPRETERCODECONTAINER_H
#define INTERPRETERCODECONTAINER_H

#include "Uti3DCore.h"
#include "UtiString.h"
#include<vector>

using namespace std;

namespace Interpreter {

/**
@author Michael Staud
*/

enum TOpCode {opAllocate, opDeallocate, opCall, opTryMeElse, opRetryMeElse,opTrustMe, opUnifyValueA, opUnifyVariableA, opUnifyValue, opUnifyVariable,
   opUnifyValueYA, opUnifyVariableYA, opUnifyValueY, opUnifyVariableY,
   opGetInteger, opGetReal, opGetIntegerA, opGetRealA, opGetStructure, opPutStructure, opGetStructureA, opPutStructureA,opSetVariable, opSetValue, opSetVariableY, opPutVariable, opPutVariableY, opPutValueY, opPutInteger, opSetValueY, opPutValue,opPutIntegerA, opPutReal};

class CodeContainer{
protected:
    vector<CUtiString> names;
    //PSTRINFO getStrInfo(PNAME name, int arity);
    //void setStrInfo(PSTRINFO in, PNAME &name, int &arity);
public:
    int* code;
    int size;
    int maxsize;
    CodeContainer();
    ~CodeContainer();
    int* addCode(int i);
    int addName(wchar_t* name);
    int getCurrentPos();
    void addLabel(int pos, int name, int arity);
    void SaveToFile(wchar_t* filename);
    void SaveToStream(CStream* str);
    void ReadFromFile(wchar_t* filename);
    void ReadFromStream(CStream* str);
};

}

#endif
