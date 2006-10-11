//
// C++ Implementation: prolognames
//
// Description: 
//
//
// Author: Michael Staud <staud@linux>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "prolognames.h"

#include <string>
#include <vector>
#include <map>

using namespace std;

namespace PrologSystem {

vector<wstring> pl_names;
map<wstring, pl_Name> pl_namemap;

void pl_registerName(const wchar_t* name, pl_Name &id)
{
   wstring n = name;
   if (pl_namemap.find(n) == pl_namemap.end()) {
      id = pl_names.size();
      pl_names.push_back(n);
      pl_namemap[n] = id;
   } else {
      id = pl_namemap[n];
      
   };
}

pl_Name pl_nameToId(const wchar_t* n)
{
   pl_Name name;
   pl_registerName(n, name);
   return name;
}

void pl_registerForceName(const wchar_t* name, const pl_Name id)
{
   wstring n = name;
   if (pl_namemap.find(n) == pl_namemap.end()) {
      //id = pl_names.size();
      while (pl_names.size() <= id) pl_names.push_back(L"");
      //pl_names.push_back(n);
      pl_names[id] = n;
      pl_namemap[n] = id;
   };
};

const wchar_t* pl_idToName(pl_Name id)
{
//   assert(id >= 0 && id < pl_names.size());
   return pl_names[id].c_str();
};

int pl_idToNameLength(pl_Name id)
{
 //  assert(id >= 0 && id < pl_names.size());
   return pl_names[id].size();
};

}
