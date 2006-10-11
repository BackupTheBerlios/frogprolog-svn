//
// C++ Interface: prolognames
//
// Description: 
//
//
// Author: Michael Staud <staud@linux>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef __PROLOGNAMES__
#define __PROLOGNAMES__

namespace PrologSystem {

typedef int pl_Name;

void pl_registerName(const wchar_t* name, pl_Name &id);
void pl_registerForceName(const wchar_t* name, const pl_Name id);
pl_Name pl_nameToId(const wchar_t* n);
const wchar_t* pl_idToName(pl_Name id);
int pl_idToNameLength(pl_Name id);

}

#endif
