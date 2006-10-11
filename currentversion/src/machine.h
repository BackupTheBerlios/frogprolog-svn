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
#ifndef INTERPRETERMACHINE_H
#define INTERPRETERMACHINE_H

#include "codecontainer.h"

namespace Interpreter {

/*enum THeapType {htReference, htStructure, htInteger, htReal, htAtom};

union HeapCell;


struct PL_PROLOGVAR
{
   THeapType type; 
   HeapCell* reference;
};

struct StructureInfo
{
   THeapType type;
   PSTRINFO str;
};

struct IntegerInfo
{
   THeapType type;
   int number;
};


struct RealInfo
{
   THeapType type;
   float number;
};

struct AtomInfo
{
   THeapType type;
   PNAME name;
};


union HeapCell 
{
   THeapType type;
   PL_PROLOGVAR var;
   StructureInfo str;
   IntegerInfo integer;
   RealInfo real;
   AtomInfo atom;
};

enum TUnifyMode {umRead, umWrite};
*/
/**
@author Michael Staud
*/
class Machine{
public:
    Machine();

    ~Machine();
    CodeContainer* PS;
   /* HeapCell H[2048];
    HeapCell* ST[2048];
    PL_PROLOGVAR* TR[2048];
    unsigned int PC;
    unsigned int HP;
    unsigned int SP;
    unsigned int FP;
    unsigned int BTP;
    unsigned int TP;
    TUnifyMode modus;*/
    void Run();
};

}

#endif
