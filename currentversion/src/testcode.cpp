//
// C++ Implementation: testcode
//
// Description: 
//
//
// Author: Michael Staud <staud@linux>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "test.h"

#include <iostream>

using namespace std;
using namespace PrologSystem;

int main() {
   wcout << L"Hallo" << endl;
   pl_Initialize();
   pl_RegisterNames();

   test* prog = new test();
   pl_PrologVar* A = pl_getVar();
   pl_PrologVar* B = pl_getVar();

  // wcout << L"Prog: "<< prog->p(*A, *B) << endl;
   wcout << L"Prog: "<< prog->init() << endl;
   wcout << L"A = ";pl_print(A);wcout << endl;
   wcout << L"B = ";pl_print(B);wcout << endl;
   
   delete prog;
   pl_Free();
   return 0;
};
