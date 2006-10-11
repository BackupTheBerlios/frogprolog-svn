//FrogProlog generated: Wed Oct  4 18:10:23 2006

#include "prologcode.h"
#include "basepredicates.h"
#include "mypred.h"
namespace PrologSystem {
pl_Name PLN_plr_bip;
pl_Name PLN_plr_foreign;
pl_Name PLN_plr_myvar;
pl_Name PLN_plr_pl_my_var;
pl_Name PLN_plr_mypred;
pl_Name PLN_plr_printme;
pl_Name PLN_plr_testterm;
pl_Name PLN_plr_A;
pl_Name PLN_plr_B;
pl_Name PLN_plr_C;
void pl_initModule_prologcode()
{
   static bool loaded = false;
   if (loaded) return;
   loaded = true;
   pl_initModule_bip();
   pl_registerName(L"bip", PLN_plr_bip);
   pl_registerName(L"foreign", PLN_plr_foreign);
   pl_registerName(L"myvar", PLN_plr_myvar);
   pl_registerName(L"pl_my_var", PLN_plr_pl_my_var);
   pl_registerName(L"mypred", PLN_plr_mypred);
   pl_registerName(L"printme", PLN_plr_printme);
   pl_registerName(L"testterm", PLN_plr_testterm);
   pl_registerName(L"A", PLN_plr_A);
   pl_registerName(L"B", PLN_plr_B);
   pl_registerName(L"C", PLN_plr_C);
   pl_RegisterStatic(PLN_plr_printme, 1, (void*)((bool (*) (pl_PrologVar &))plr_printme));
   pl_RegisterStatic(PLN_plr_myvar, 1, (void*)((bool (*) (pl_PrologVar &))pl_my_var));
   
}

bool plr_printme(pl_PrologVar & plr_A0)
{
   void* pl_stackframe = NULL;
   // printme(A0)
   // Possibilities: 2
   int pl_pos0;
   bool pl_exit0 = false;
   pl_begin(pl_pos0, (void*&)pl_stackframe, 1);
   while(!pl_exit0) {
   switch(pl_pos0) {
      case 0: {
         pl_pos0 = 0;
         pl_choisePoint();
         // Test mit: printme(testterm(A, B, C))
         if ((!pl_backtracking) && (!(
             pl_loadVariable(plr_A0, 1)
          && pl_get_structure(pl_s(PLN_plr_testterm,3), 1)
          && pl_unify_variableARG(0)
          && pl_unify_variableARG(1)
          && pl_unify_variableARG(2)
         ))){
            pl_DoBacktracking();
            break;
         };
         if (!plr_printme_Choise_1_0(*pl_ARG[0],*pl_ARG[1],*pl_ARG[2])){
            pl_DoBacktracking();
            break;
         };
         pl_exit0 = true;
         
      }; break;
      case 1: {
         pl_pos0 = 1;
         
         // Test mit: printme(A)
         if ((!pl_backtracking) && (!(
             pl_loadArgVariable(0, plr_A0)
         ))){
            pl_DoBacktracking();
            break;
         };
         if (!plr_printme_Choise_1_1(*pl_ARG[0])){
            pl_DoBacktracking();
            break;
         };
         pl_exit0 = true;
         
      }; break;
      case -1: {
         pl_pos0 = -1;
         pl_exit0 = true;
         
      }; break;
      
   }
   }
   return pl_end(pl_pos0, (void*&)pl_stackframe);
   
   
};

bool plr_printme_Choise_1_0(pl_PrologVar & plr_A, pl_PrologVar & plr_B, pl_PrologVar & plr_C)
{
   void* pl_stackframe = NULL;
   
   int pl_pos0;
   bool pl_exit0 = false;
   pl_begin(pl_pos0, (void*&)pl_stackframe, 3);
   while(!pl_exit0) {
   switch(pl_pos0) {
      case 0: {
         pl_pos0 = 0;
         // write(A)
         // Possibilities: 1
         // Test mit: write(A0)
         if ((!pl_backtracking) && (!(
             pl_loadArgVariable(0, plr_A)
         ))){
            pl_DoBacktracking();
            break;
         };
         if (!pl_foreign_write((HP_term)pl_ARG[0])){
            pl_DoBacktracking();
            break;
         };
         
      }; 
      case 1: {
         pl_pos0 = 1;
         // write(B)
         // Possibilities: 1
         // Test mit: write(A0)
         if ((!pl_backtracking) && (!(
             pl_loadArgVariable(0, plr_B)
         ))){
            pl_DoBacktracking();
            break;
         };
         if (!pl_foreign_write((HP_term)pl_ARG[0])){
            pl_DoBacktracking();
            break;
         };
         
      }; 
      case 2: {
         pl_pos0 = 2;
         // write(C)
         // Possibilities: 1
         // Test mit: write(A0)
         if ((!pl_backtracking) && (!(
             pl_loadArgVariable(0, plr_C)
         ))){
            pl_DoBacktracking();
            break;
         };
         if (!pl_foreign_write((HP_term)pl_ARG[0])){
            pl_DoBacktracking();
            break;
         };
         
      }; 
      case 3: {
         pl_pos0 = 3;
         // nl
         // Possibilities: 1
         // Test mit: nl
         if (!pl_foreign_nl()){
            pl_DoBacktracking();
            break;
         };
         
      }; 
      case 4: {
         pl_pos0 = 4;
         pl_exit0 = true;
         
      }; break;
      case -1: {
         pl_pos0 = -1;
         pl_exit0 = true;
         
      }; break;
      
   }
   }
   return pl_end(pl_pos0, (void*&)pl_stackframe);
   
   
};
bool plr_printme_Choise_1_1(pl_PrologVar & plr_A)
{
   struct pl_Stackframe_Struct {
      pl_PrologVar plr_B;
      };
   pl_Stackframe_Struct* pl_stackframe;
   if (!pl_backtracking) {
      pl_stackframe = (pl_Stackframe_Struct*)pl_getHeapMem(1);
   };
   
   
   int pl_pos0;
   bool pl_exit0 = false;
   pl_begin(pl_pos0, (void*&)pl_stackframe, 1);
   while(!pl_exit0) {
   switch(pl_pos0) {
      case 0: {
         pl_pos0 = 0;
         // write(A)
         // Possibilities: 1
         // Test mit: write(A0)
         if ((!pl_backtracking) && (!(
             pl_loadArgVariable(0, plr_A)
         ))){
            pl_DoBacktracking();
            break;
         };
         if (!pl_foreign_write((HP_term)pl_ARG[0])){
            pl_DoBacktracking();
            break;
         };
         
      }; 
      case 1: {
         pl_pos0 = 1;
         // myvar(B)
         // Possibilities: 1
         // Test mit: myvar(A0)
         if ((!pl_backtracking) && (!(
             pl_loadArgVariable(0, pl_stackframe->plr_B)
         ))){
            pl_DoBacktracking();
            break;
         };
         if (!pl_my_var((HP_term)pl_ARG[0])){
            pl_DoBacktracking();
            break;
         };
         
      }; 
      case 2: {
         pl_pos0 = 2;
         // nl
         // Possibilities: 1
         // Test mit: nl
         if (!pl_foreign_nl()){
            pl_DoBacktracking();
            break;
         };
         
      }; 
      case 3: {
         pl_pos0 = 3;
         pl_exit0 = true;
         
      }; break;
      case -1: {
         pl_pos0 = -1;
         pl_exit0 = true;
         
      }; break;
      
   }
   }
   return pl_end(pl_pos0, (void*&)pl_stackframe);
   
   
};
};
