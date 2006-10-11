//
// C++ Implementation: machine
//
// Description: 
//
//
// Author: Michael Staud <staud@linux>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "machine.h"

namespace Interpreter {

Machine::Machine()
{
   PS = new CodeContainer();
  /* PC = 0;
   HP = 0;
   SP = 0;
   FP = 0;
   BTP = 0;
   TP = 0;*/
}


Machine::~Machine()
{
   delete PS;
}




void Machine::Run()
{
  /* OpCommand com;
   while (PC >= 0 && PC < 2048) {
      com = getCommand(PC);
      switch (com.type) {
	 case opPutAtom: {
	    SP++;
	    H[HP].type = htAtom;
	    H[HP].atom.name = com.atom.name;
	    ST[SP] = &H[HP];
	    
	    HP++;
	 }; break;
	 case opPutVar: {
	    SP++;
	    H[HP].type = htReference;
	    H[HP].var.reference = &H[HP];
	    ST[FP+com.var.i] = &H[HP];
	    ST[SP] = ST[FP+com.var.i];
	    HP++;
	 }; break;
	 case opPutRef: {
	    SP++;
	    ST[SP] = ST[FP+com.var.i];
	 }; break;
	 case opPutStruct: {
	    int n = getArity(com.structure.info);
	    SP = SP - n + 1;
	    H[HP].type = htStructure;
	    H[HP].str.str = com.structure.info;
	    ST[SP] = &H[HP];
	    
	    HP++;
	 };
	 
	 
      };
      
};*/
}

}
