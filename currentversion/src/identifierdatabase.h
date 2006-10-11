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
#ifndef UTIPROLOGIDENTIFIERDATABASE_H
#define UTIPROLOGIDENTIFIERDATABASE_H

#include <map>
#include <string>
#include <vector>

using namespace std;

#include "UtiString.h"

namespace UtiProlog {

/**
This class stores all identifiers and gives them number. These numbers are then returnd to the parser.

@author Michael Staud
*/

typedef int PID;

struct IdentID
{
   CUtiString name;
   bool foreign;
};

class IdentifierDatabase{
protected:
   map<CUtiString, PID> identtoID;
   map<PID, CUtiString> IDtoident;
   map<CUtiString, PID> identtoIDCode;
   map<PID, CUtiString> IDtoidentCode;
   int currentid;
   map<CUtiString, CUtiString> transform;
public:
   vector<IdentID> Names;
    IdentifierDatabase();
    ~IdentifierDatabase();
    PID identifierToID(const CUtiString &str, bool foreign=false);
    PID identifierToID(const char* c);
    PID getVoid();
    CUtiString idToIdentifier(PID ID);
    CUtiString idToIdentifierIdent(PID ID);
    CUtiString idToIdentifierCode(PID ID);
    void registerValue(const CUtiString &str, PID id);
    void clearDatabase();
    void debugPrint();

};

extern IdentifierDatabase idbase;


}

#endif
