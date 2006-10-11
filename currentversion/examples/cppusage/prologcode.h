//FrogProlog generated: Wed Oct  4 18:10:23 2006

//Generated Code:
#ifndef __prologcode_h
#define __prologcode_h
#include "prologenvironment.h"
#include "prolognames.h"

#include "bip.h"

namespace PrologSystem {
extern pl_Name PLN_plr_bip;
extern pl_Name PLN_plr_foreign;
extern pl_Name PLN_plr_myvar;
extern pl_Name PLN_plr_pl_my_var;
extern pl_Name PLN_plr_mypred;
extern pl_Name PLN_plr_printme;
extern pl_Name PLN_plr_testterm;
extern pl_Name PLN_plr_A;
extern pl_Name PLN_plr_B;
extern pl_Name PLN_plr_C;

void pl_initModule_prologcode();
bool plr_printme(pl_PrologVar & plr_A0);
bool plr_printme_Choise_1_0(pl_PrologVar & plr_A, pl_PrologVar & plr_B, pl_PrologVar & plr_C);
bool plr_printme_Choise_1_1(pl_PrologVar & plr_A);

};

#endif
