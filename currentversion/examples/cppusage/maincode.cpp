#include "prologcode.h"
#include "frogprolog.h"

#include <iostream>

using namespace std;
using namespace PrologSystem;

int main() {
   pl_Initialize();
   pl_initModule_prologcode();
   pl_initengine();
   //Mit Backtracking ueber Loesungen
   HP_term t = HP_create_structure_3(
         HP_atom_from_wstring(L"testterm"),
          HP_create_integer(5), 
          HP_create_char(L'a'), 
          HP_create_atom(HP_atom_from_wstring(L"atom"))
       );
   while (plr_printme(HP(t)) && HP_startBacktracking()) {
  
   };
   pl_Free();
   return 0;
};
