//FrogProlog generated: Wed Jul 19 12:00:01 2006

#include "bip.h"
#include "basepredicates.h"
namespace PrologSystem {
pl_Name PLN_plr__backslash_plus;
pl_Name PLN_plr_not;
pl_Name PLN_plr__equal;
pl_Name PLN_plr__less;
pl_Name PLN_plr__equal_dot_dot;
pl_Name PLN_plr__equal_addsymbol_equal;
pl_Name PLN_plr__equal_colon_equal;
pl_Name PLN_plr__equal_less;
pl_Name PLN_plr__equal_equal;
pl_Name PLN_plr__equal_backslash_equal;
pl_Name PLN_plr__greater;
pl_Name PLN_plr__greater_equal;
pl_Name PLN_plr__addsymbol_less;
pl_Name PLN_plr__addsymbol_equal_less;
pl_Name PLN_plr__addsymbol_greater;
pl_Name PLN_plr__addsymbol_greater_equal;
pl_Name PLN_plr__backslash_equal;
pl_Name PLN_plr__backslash_equal_equal;
pl_Name PLN_plr_is;
pl_Name PLN_plr__colon;
pl_Name PLN_plr__plus;
pl_Name PLN_plr__minus;
pl_Name PLN_plr__divide_backslash;
pl_Name PLN_plr__backslash_divide;
pl_Name PLN_plr_xor;
pl_Name PLN_plr__question;
pl_Name PLN_plr__backslash;
pl_Name PLN_plr__multiply;
pl_Name PLN_plr__divide;
pl_Name PLN_plr__divide_divide;
pl_Name PLN_plr_rdiv;
pl_Name PLN_plr__less_less;
pl_Name PLN_plr__greater_greater;
pl_Name PLN_plr_mod;
pl_Name PLN_plr_rem;
pl_Name PLN_plr__multiply_multiply;
pl_Name PLN_plr__potence;
pl_Name PLN_plr__cut;
pl_Name PLN_plr_fail;
pl_Name PLN_plr_false;
pl_Name PLN_plr_true;
pl_Name PLN_plr_assert;
pl_Name PLN_plr_A0;
pl_Name PLN_plr_asserta;
pl_Name PLN_plr_assertz;
pl_Name PLN_plr_A1;
pl_Name PLN_plr_retract;
pl_Name PLN_plr_retractall;
pl_Name PLN_plr_abolish;
pl_Name PLN_plr_bye;
pl_Name PLN_plr_halt;
pl_Name PLN_plr_repeat;
pl_Name PLN_plr_var;
pl_Name PLN_plr_nonvar;
pl_Name PLN_plr_ground;
pl_Name PLN_plr_atom;
pl_Name PLN_plr_float;
pl_Name PLN_plr_integer;
pl_Name PLN_plr_number;
pl_Name PLN_plr_atomic;
pl_Name PLN_plr_simple;
pl_Name PLN_plr_compound;
pl_Name PLN_plr_write;
pl_Name PLN_plr_writeq;
pl_Name PLN_plr_nl;
pl_Name PLN_plr_put;
pl_Name PLN_plr_tab;
pl_Name PLN_plr_tell;
pl_Name PLN_plr_telling;
pl_Name PLN_plr_told;
pl_Name PLN_plr_read;
pl_Name PLN_plr_see;
pl_Name PLN_plr_seeing;
pl_Name PLN_plr_seen;
pl_Name PLN_plr_at_end_of_stream;
pl_Name PLN_plr_put_byte;
pl_Name PLN_plr_put_char;
pl_Name PLN_plr_put_code;
pl_Name PLN_plr_flush_output;
pl_Name PLN_plr_get_byte;
pl_Name PLN_plr_get_code;
pl_Name PLN_plr_get_char;
pl_Name PLN_plr_get;
pl_Name PLN_plr_peek_byte;
pl_Name PLN_plr_peek_code;
pl_Name PLN_plr_peek_char;
pl_Name PLN_plr_skip;
pl_Name PLN_plr_functor;
pl_Name PLN_plr_A2;
pl_Name PLN_plr_arg;
pl_Name PLN_plr_char_type;
pl_Name PLN_plr_atom_codes;
pl_Name PLN_plr_atom_chars;
pl_Name PLN_plr_char_code;
pl_Name PLN_plr_number_chars;
pl_Name PLN_plr_number_codes;
pl_Name PLN_plr_atom_number;
pl_Name PLN_plr_name;
pl_Name PLN_plr_term_to_atom;
pl_Name PLN_plr_atom_to_term;
pl_Name PLN_plr_atom_concat;
pl_Name PLN_plr_concat_atom;
pl_Name PLN_plr_atom_length;
pl_Name PLN_plr_atom_prefix;
pl_Name PLN_plr_sub_atom;
pl_Name PLN_plr_A3;
pl_Name PLN_plr_A4;
pl_Name PLN_plr_dynamic;
pl_Name PLN_plr__dollarinstance;
pl_Name PLN_plr_findall;
pl_Name PLN_plr_X;
pl_Name PLN_plr_Goal;
pl_Name PLN_plr_Xs;
pl_Name PLN_plr__dollarmark;
pl_Name PLN_plr_X1;
pl_Name PLN_plr_intern_reap_;
pl_Name PLN_plr_addVar;
pl_Name PLN_plr__bracket_bracketend;
pl_Name PLN_plr_REST;
pl_Name PLN_plr_Ys;
pl_Name PLN_plr__dot;
pl_Name PLN_plr_catch;
pl_Name PLN_plr_ProtectedGoal;
pl_Name PLN_plr_Pattern;
pl_Name PLN_plr_Handler;
pl_Name PLN_plr_on_exception;
pl_Name PLN_plr_throw;
pl_Name PLN_plr_Exception;
pl_Name PLN_plr_raise_exception;
pl_Name PLN_plr_member;
pl_Name PLN_plr_Y;
pl_Name PLN_plr_append;
pl_Name PLN_plr_Zs;
pl_Name PLN_plr_reverse;
pl_Name PLN_plr_reversein;
pl_Name PLN_plr_Acc;
void pl_initModule_bip()
{
   static bool loaded = false;
   if (loaded) return;
   loaded = true;
   pl_registerName(L"\\+", PLN_plr__backslash_plus);
   pl_registerName(L"not", PLN_plr_not);
   pl_registerName(L"=", PLN_plr__equal);
   pl_registerName(L"<", PLN_plr__less);
   pl_registerName(L"=..", PLN_plr__equal_dot_dot);
   pl_registerName(L"=@=", PLN_plr__equal_addsymbol_equal);
   pl_registerName(L"=:=", PLN_plr__equal_colon_equal);
   pl_registerName(L"=<", PLN_plr__equal_less);
   pl_registerName(L"==", PLN_plr__equal_equal);
   pl_registerName(L"=\\=", PLN_plr__equal_backslash_equal);
   pl_registerName(L">", PLN_plr__greater);
   pl_registerName(L">=", PLN_plr__greater_equal);
   pl_registerName(L"@<", PLN_plr__addsymbol_less);
   pl_registerName(L"@=<", PLN_plr__addsymbol_equal_less);
   pl_registerName(L"@>", PLN_plr__addsymbol_greater);
   pl_registerName(L"@>=", PLN_plr__addsymbol_greater_equal);
   pl_registerName(L"\\=", PLN_plr__backslash_equal);
   pl_registerName(L"\\==", PLN_plr__backslash_equal_equal);
   pl_registerName(L"is", PLN_plr_is);
   pl_registerName(L":", PLN_plr__colon);
   pl_registerName(L"+", PLN_plr__plus);
   pl_registerName(L"-", PLN_plr__minus);
   pl_registerName(L"/\\", PLN_plr__divide_backslash);
   pl_registerName(L"\\/", PLN_plr__backslash_divide);
   pl_registerName(L"xor", PLN_plr_xor);
   pl_registerName(L"?", PLN_plr__question);
   pl_registerName(L"\\", PLN_plr__backslash);
   pl_registerName(L"*", PLN_plr__multiply);
   pl_registerName(L"/", PLN_plr__divide);
   pl_registerName(L"//", PLN_plr__divide_divide);
   pl_registerName(L"rdiv", PLN_plr_rdiv);
   pl_registerName(L"<<", PLN_plr__less_less);
   pl_registerName(L">>", PLN_plr__greater_greater);
   pl_registerName(L"mod", PLN_plr_mod);
   pl_registerName(L"rem", PLN_plr_rem);
   pl_registerName(L"**", PLN_plr__multiply_multiply);
   pl_registerName(L"^", PLN_plr__potence);
   pl_registerName(L"!", PLN_plr__cut);
   pl_registerName(L"fail", PLN_plr_fail);
   pl_registerName(L"false", PLN_plr_false);
   pl_registerName(L"true", PLN_plr_true);
   pl_registerName(L"assert", PLN_plr_assert);
   pl_registerName(L"A0", PLN_plr_A0);
   pl_registerName(L"asserta", PLN_plr_asserta);
   pl_registerName(L"assertz", PLN_plr_assertz);
   pl_registerName(L"A1", PLN_plr_A1);
   pl_registerName(L"retract", PLN_plr_retract);
   pl_registerName(L"retractall", PLN_plr_retractall);
   pl_registerName(L"abolish", PLN_plr_abolish);
   pl_registerName(L"bye", PLN_plr_bye);
   pl_registerName(L"halt", PLN_plr_halt);
   pl_registerName(L"repeat", PLN_plr_repeat);
   pl_registerName(L"var", PLN_plr_var);
   pl_registerName(L"nonvar", PLN_plr_nonvar);
   pl_registerName(L"ground", PLN_plr_ground);
   pl_registerName(L"atom", PLN_plr_atom);
   pl_registerName(L"float", PLN_plr_float);
   pl_registerName(L"integer", PLN_plr_integer);
   pl_registerName(L"number", PLN_plr_number);
   pl_registerName(L"atomic", PLN_plr_atomic);
   pl_registerName(L"simple", PLN_plr_simple);
   pl_registerName(L"compound", PLN_plr_compound);
   pl_registerName(L"write", PLN_plr_write);
   pl_registerName(L"writeq", PLN_plr_writeq);
   pl_registerName(L"nl", PLN_plr_nl);
   pl_registerName(L"put", PLN_plr_put);
   pl_registerName(L"tab", PLN_plr_tab);
   pl_registerName(L"tell", PLN_plr_tell);
   pl_registerName(L"telling", PLN_plr_telling);
   pl_registerName(L"told", PLN_plr_told);
   pl_registerName(L"read", PLN_plr_read);
   pl_registerName(L"see", PLN_plr_see);
   pl_registerName(L"seeing", PLN_plr_seeing);
   pl_registerName(L"seen", PLN_plr_seen);
   pl_registerName(L"at_end_of_stream", PLN_plr_at_end_of_stream);
   pl_registerName(L"put_byte", PLN_plr_put_byte);
   pl_registerName(L"put_char", PLN_plr_put_char);
   pl_registerName(L"put_code", PLN_plr_put_code);
   pl_registerName(L"flush_output", PLN_plr_flush_output);
   pl_registerName(L"get_byte", PLN_plr_get_byte);
   pl_registerName(L"get_code", PLN_plr_get_code);
   pl_registerName(L"get_char", PLN_plr_get_char);
   pl_registerName(L"get", PLN_plr_get);
   pl_registerName(L"peek_byte", PLN_plr_peek_byte);
   pl_registerName(L"peek_code", PLN_plr_peek_code);
   pl_registerName(L"peek_char", PLN_plr_peek_char);
   pl_registerName(L"skip", PLN_plr_skip);
   pl_registerName(L"functor", PLN_plr_functor);
   pl_registerName(L"A2", PLN_plr_A2);
   pl_registerName(L"arg", PLN_plr_arg);
   pl_registerName(L"char_type", PLN_plr_char_type);
   pl_registerName(L"atom_codes", PLN_plr_atom_codes);
   pl_registerName(L"atom_chars", PLN_plr_atom_chars);
   pl_registerName(L"char_code", PLN_plr_char_code);
   pl_registerName(L"number_chars", PLN_plr_number_chars);
   pl_registerName(L"number_codes", PLN_plr_number_codes);
   pl_registerName(L"atom_number", PLN_plr_atom_number);
   pl_registerName(L"name", PLN_plr_name);
   pl_registerName(L"term_to_atom", PLN_plr_term_to_atom);
   pl_registerName(L"atom_to_term", PLN_plr_atom_to_term);
   pl_registerName(L"atom_concat", PLN_plr_atom_concat);
   pl_registerName(L"concat_atom", PLN_plr_concat_atom);
   pl_registerName(L"atom_length", PLN_plr_atom_length);
   pl_registerName(L"atom_prefix", PLN_plr_atom_prefix);
   pl_registerName(L"sub_atom", PLN_plr_sub_atom);
   pl_registerName(L"A3", PLN_plr_A3);
   pl_registerName(L"A4", PLN_plr_A4);
   pl_registerName(L"dynamic", PLN_plr_dynamic);
   pl_registerName(L"$instance", PLN_plr__dollarinstance);
   pl_registerName(L"findall", PLN_plr_findall);
   pl_registerName(L"X", PLN_plr_X);
   pl_registerName(L"Goal", PLN_plr_Goal);
   pl_registerName(L"Xs", PLN_plr_Xs);
   pl_registerName(L"$mark", PLN_plr__dollarmark);
   pl_registerName(L"X1", PLN_plr_X1);
   pl_registerName(L"intern_reap_", PLN_plr_intern_reap_);
   pl_registerName(L"addVar", PLN_plr_addVar);
   pl_registerName(L"[]", PLN_plr__bracket_bracketend);
   pl_registerName(L"REST", PLN_plr_REST);
   pl_registerName(L"Ys", PLN_plr_Ys);
   pl_registerName(L".", PLN_plr__dot);
   pl_registerName(L"catch", PLN_plr_catch);
   pl_registerName(L"ProtectedGoal", PLN_plr_ProtectedGoal);
   pl_registerName(L"Pattern", PLN_plr_Pattern);
   pl_registerName(L"Handler", PLN_plr_Handler);
   pl_registerName(L"on_exception", PLN_plr_on_exception);
   pl_registerName(L"throw", PLN_plr_throw);
   pl_registerName(L"Exception", PLN_plr_Exception);
   pl_registerName(L"raise_exception", PLN_plr_raise_exception);
   pl_registerName(L"member", PLN_plr_member);
   pl_registerName(L"Y", PLN_plr_Y);
   pl_registerName(L"append", PLN_plr_append);
   pl_registerName(L"Zs", PLN_plr_Zs);
   pl_registerName(L"reverse", PLN_plr_reverse);
   pl_registerName(L"reversein", PLN_plr_reversein);
   pl_registerName(L"Acc", PLN_plr_Acc);
   // $instance\1
   pl_RegisterStatic(PLN_plr__dollarinstance, 1, (void*)plr__dollarinstance);
   pl_RegisterStatic(PLN_plr_assert, 1, (void*)pl_foreign_assertz);
   pl_RegisterStatic(PLN_plr_asserta, 1, (void*)pl_foreign_asserta);
   pl_RegisterStatic(PLN_plr_assertz, 1, (void*)pl_foreign_assertz);
   pl_RegisterStatic(PLN_plr_assert, 2, (void*)pl_foreign_assert2z);
   pl_RegisterStatic(PLN_plr_asserta, 2, (void*)pl_foreign_assert2a);
   pl_RegisterStatic(PLN_plr_assertz, 2, (void*)pl_foreign_assert2z);
   pl_RegisterStatic(PLN_plr_retract, 2, (void*)pl_foreign_retract2);
   pl_RegisterStatic(PLN_plr_retract, 1, (void*)pl_foreign_retract);
   pl_RegisterStatic(PLN_plr_retractall, 1, (void*)pl_foreign_retractall);
   pl_RegisterStatic(PLN_plr_abolish, 2, (void*)pl_foreign_abolish);
   pl_RegisterStatic(PLN_plr__equal, 2, (void*)pl_foreign_equal);
   pl_RegisterStatic(PLN_plr__backslash_equal, 2, (void*)pl_foreign_nonequal);
   pl_RegisterStatic(PLN_plr_is, 2, (void*)pl_foreign_is);
   pl_RegisterStatic(PLN_plr__equal_colon_equal, 2, (void*)pl_foreign_arithequal);
   pl_RegisterStatic(PLN_plr__equal_backslash_equal, 2, (void*)pl_foreign_arithnonequal);
   pl_RegisterStatic(PLN_plr__less, 2, (void*)pl_foreign_arithless);
   pl_RegisterStatic(PLN_plr__equal_less, 2, (void*)pl_foreign_aritheqless);
   pl_RegisterStatic(PLN_plr__greater, 2, (void*)pl_foreign_arithgreater);
   pl_RegisterStatic(PLN_plr__greater_equal, 2, (void*)pl_foreign_aritheqgreater);
   pl_RegisterStatic(PLN_plr_fail, 0, (void*)pl_foreign_fail);
   pl_RegisterStatic(PLN_plr_false, 0, (void*)pl_foreign_fail);
   pl_RegisterStatic(PLN_plr_true, 0, (void*)pl_foreign_true);
   pl_RegisterStatic(PLN_plr__equal_equal, 2, (void*)pl_foreign_instequal);
   pl_RegisterStatic(PLN_plr__backslash_equal_equal, 2, (void*)pl_foreign_instnonequal);
   pl_RegisterStatic(PLN_plr__addsymbol_less, 2, (void*)pl_foreign_instless);
   pl_RegisterStatic(PLN_plr__addsymbol_equal_less, 2, (void*)pl_foreign_insteqless);
   pl_RegisterStatic(PLN_plr__addsymbol_greater, 2, (void*)pl_foreign_instgreater);
   pl_RegisterStatic(PLN_plr__addsymbol_greater_equal, 2, (void*)pl_foreign_insteqgreater);
   pl_RegisterStatic(PLN_plr_bye, 0, (void*)pl_foreign_bye);
   pl_RegisterStatic(PLN_plr_halt, 0, (void*)pl_foreign_halt);
   pl_RegisterStatic(PLN_plr_repeat, 0, (void*)pl_foreign_repeat);
   pl_RegisterStatic(PLN_plr_var, 1, (void*)pl_foreign_var);
   pl_RegisterStatic(PLN_plr_nonvar, 1, (void*)pl_foreign_nonvar);
   pl_RegisterStatic(PLN_plr_ground, 1, (void*)pl_foreign_ground);
   pl_RegisterStatic(PLN_plr_atom, 1, (void*)pl_foreign_atom);
   pl_RegisterStatic(PLN_plr_float, 1, (void*)pl_foreign_float);
   pl_RegisterStatic(PLN_plr_integer, 1, (void*)pl_foreign_integer);
   pl_RegisterStatic(PLN_plr_number, 1, (void*)pl_foreign_number);
   pl_RegisterStatic(PLN_plr_atomic, 1, (void*)pl_foreign_atomic);
   pl_RegisterStatic(PLN_plr_simple, 1, (void*)pl_foreign_simple);
   pl_RegisterStatic(PLN_plr_compound, 1, (void*)pl_foreign_compound);
   pl_RegisterStatic(PLN_plr_write, 1, (void*)pl_foreign_write);
   pl_RegisterStatic(PLN_plr_writeq, 1, (void*)pl_foreign_writeq);
   pl_RegisterStatic(PLN_plr_nl, 0, (void*)pl_foreign_nl);
   pl_RegisterStatic(PLN_plr_put, 1, (void*)pl_foreign_put);
   pl_RegisterStatic(PLN_plr_tab, 1, (void*)pl_foreign_tab);
   pl_RegisterStatic(PLN_plr_tell, 1, (void*)pl_foreign_tell);
   pl_RegisterStatic(PLN_plr_telling, 1, (void*)pl_foreign_telling);
   pl_RegisterStatic(PLN_plr_told, 0, (void*)pl_foreign_told);
   pl_RegisterStatic(PLN_plr_read, 1, (void*)pl_foreign_read);
   pl_RegisterStatic(PLN_plr_see, 1, (void*)pl_foreign_see);
   pl_RegisterStatic(PLN_plr_seeing, 1, (void*)pl_foreign_seeing);
   pl_RegisterStatic(PLN_plr_seen, 0, (void*)pl_foreign_seen);
   pl_RegisterStatic(PLN_plr_at_end_of_stream, 0, (void*)pl_foreign_at_end_of_stream);
   pl_RegisterStatic(PLN_plr_put_byte, 1, (void*)pl_foreign_put_byte);
   pl_RegisterStatic(PLN_plr_put_char, 1, (void*)pl_foreign_put_char);
   pl_RegisterStatic(PLN_plr_put_code, 1, (void*)pl_foreign_put_code);
   pl_RegisterStatic(PLN_plr_flush_output, 0, (void*)pl_foreign_flush_output);
   pl_RegisterStatic(PLN_plr_get_byte, 1, (void*)pl_foreign_get_byte);
   pl_RegisterStatic(PLN_plr_get_code, 1, (void*)pl_foreign_get_code);
   pl_RegisterStatic(PLN_plr_get_char, 1, (void*)pl_foreign_get_char);
   pl_RegisterStatic(PLN_plr_get, 1, (void*)pl_foreign_get_char);
   pl_RegisterStatic(PLN_plr_peek_byte, 1, (void*)pl_foreign_peek_byte);
   pl_RegisterStatic(PLN_plr_peek_code, 1, (void*)pl_foreign_peek_code);
   pl_RegisterStatic(PLN_plr_peek_char, 1, (void*)pl_foreign_peek_char);
   pl_RegisterStatic(PLN_plr_skip, 1, (void*)pl_foreign_skip);
   pl_RegisterStatic(PLN_plr_functor, 3, (void*)pl_foreign_functor);
   pl_RegisterStatic(PLN_plr_arg, 3, (void*)pl_foreign_arg);
   pl_RegisterStatic(PLN_plr_char_type, 2, (void*)pl_foreign_char_type);
   pl_RegisterStatic(PLN_plr_atom_codes, 2, (void*)pl_foreign_atom_codes);
   pl_RegisterStatic(PLN_plr_atom_chars, 2, (void*)pl_foreign_atom_chars);
   pl_RegisterStatic(PLN_plr_char_code, 2, (void*)pl_foreign_char_code);
   pl_RegisterStatic(PLN_plr_number_chars, 2, (void*)pl_foreign_number_chars);
   pl_RegisterStatic(PLN_plr_number_codes, 2, (void*)pl_foreign_number_codes);
   pl_RegisterStatic(PLN_plr_atom_number, 2, (void*)pl_foreign_atom_number);
   pl_RegisterStatic(PLN_plr_name, 2, (void*)pl_foreign_name);
   pl_RegisterStatic(PLN_plr_term_to_atom, 2, (void*)pl_foreign_term_to_atom);
   pl_RegisterStatic(PLN_plr_atom_to_term, 3, (void*)pl_foreign_atom_to_term);
   pl_RegisterStatic(PLN_plr_atom_concat, 3, (void*)pl_foreign_atom_concat);
   pl_RegisterStatic(PLN_plr_concat_atom, 2, (void*)pl_foreign_concat_atom2);
   pl_RegisterStatic(PLN_plr_concat_atom, 3, (void*)pl_foreign_concat_atom3);
   pl_RegisterStatic(PLN_plr_atom_length, 2, (void*)pl_foreign_atom_length);
   pl_RegisterStatic(PLN_plr_atom_prefix, 2, (void*)pl_foreign_atom_prefix);
   pl_RegisterStatic(PLN_plr_sub_atom, 5, (void*)pl_foreign_sub_atom);
   pl_RegisterStatic(PLN_plr_findall, 3, (void*)plr_findall);
   pl_RegisterStatic(PLN_plr_intern_reap_, 2, (void*)plr_intern_reap_);
   pl_RegisterStatic(PLN_plr_catch, 3, (void*)plr_catch);
   pl_RegisterStatic(PLN_plr_on_exception, 3, (void*)plr_on_exception);
   pl_RegisterStatic(PLN_plr_throw, 1, (void*)plr_throw);
   pl_RegisterStatic(PLN_plr_raise_exception, 1, (void*)plr_raise_exception);
   pl_RegisterStatic(PLN_plr_member, 2, (void*)plr_member);
   pl_RegisterStatic(PLN_plr_append, 3, (void*)plr_append);
   pl_RegisterStatic(PLN_plr_reverse, 2, (void*)plr_reverse);
   pl_RegisterStatic(PLN_plr_reversein, 3, (void*)plr_reversein);
   pl_RegisterDynamic(PLN_plr__dollarinstance, 1, &pl_dyn_plr__dollarinstance_1);
   
}

pl_PredicateCollection pl_dyn_plr__dollarinstance_1;
bool plr__dollarinstance(pl_PrologVar & A0)
{
   void* pl_stackframe = NULL;
   int pl_pos0;
   bool pl_exit0 = false;
   pl_begin(pl_pos0, (void*&)pl_stackframe, 1);
   while(!pl_exit0) {
      if (pl_pos0 < pl_dyn_count(pl_dyn_plr__dollarinstance_1)-1) {
         pl_choisePoint();
         if (!pl_dyn_prove(pl_dyn_plr__dollarinstance_1, pl_pos0)){
            pl_DoBacktracking();
            continue;
         };
         pl_exit0 = true;
      } else if (pl_pos0 == pl_dyn_count(pl_dyn_plr__dollarinstance_1)-1) {
         if (!pl_dyn_prove(pl_dyn_plr__dollarinstance_1, pl_pos0)){
            pl_DoBacktracking();
            break;
         };
         
         pl_exit0 = true;
      } else {
         pl_pos0 = -1;
         pl_exit0 = true;
         pl_DoBacktracking();
         break;
      }
   }
   return pl_end(pl_pos0, (void*&)pl_stackframe);
   
};

bool plr_findall(pl_PrologVar & plr_A0, pl_PrologVar & plr_A1, pl_PrologVar & plr_A2)
{
   void* pl_stackframe = NULL;
   // findall(A0, A1, A2)
   // Possibilities: 2
   int pl_pos0;
   bool pl_exit0 = false;
   pl_begin(pl_pos0, (void*&)pl_stackframe, 3);
   while(!pl_exit0) {
   switch(pl_pos0) {
      case 0: {
         pl_pos0 = 0;
         pl_choisePoint();
         // Test mit: findall(X, Goal, Xs)
         if ((!pl_backtracking) && (!(
             pl_loadArgVariable(0, plr_A0)
          && pl_loadArgVariable(1, plr_A1)
          && pl_loadArgVariable(2, plr_A2)
         ))){
            pl_DoBacktracking();
            break;
         };
         if (!plr_findall_Choise_0(*pl_ARG[0],*pl_ARG[1],*pl_ARG[2])){
            pl_DoBacktracking();
            break;
         };
         pl_exit0 = true;
         
      }; break;
      case 1: {
         pl_pos0 = 1;
         
         // Test mit: findall(X, Goal, Xs)
         if ((!pl_backtracking) && (!(
             pl_loadArgVariable(0, plr_A0)
          && pl_loadArgVariable(1, plr_A1)
          && pl_loadArgVariable(2, plr_A2)
         ))){
            pl_DoBacktracking();
            break;
         };
         if (!plr_findall_Choise_1(*pl_ARG[0],*pl_ARG[1],*pl_ARG[2])){
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

bool plr_findall_Choise_0(pl_PrologVar & plr_X, pl_PrologVar & plr_Goal, pl_PrologVar & plr_Xs)
{
   void* pl_stackframe = NULL;
   
   int pl_pos0;
   bool pl_exit0 = false;
   pl_begin(pl_pos0, (void*&)pl_stackframe, 3);
   while(!pl_exit0) {
   switch(pl_pos0) {
      case 0: {
         pl_pos0 = 0;
         // asserta($instance($mark))
         // Possibilities: 1
         // Test mit: asserta(A0)
         if ((!pl_backtracking) && (!(
             pl_loadArgVar(0, 1)
          && pl_get_structure(pl_s(PLN_plr__dollarinstance,1), 1)
          && pl_unify_variable(2)
          && pl_get_structure(pl_s(PLN_plr__dollarmark,0), 2)
         ))){
            pl_DoBacktracking();
            break;
         };
         pl_dyn_add(pl_dyn_plr__dollarinstance_1, (pl_HeapCell*)pl_ARG[0], pl_addfirst);
      }; 
      case 1: {
         pl_pos0 = 1;
         // Goal
         if (!pl_FreeCall((pl_HeapCell*)&plr_Goal)){
            pl_DoBacktracking();
            break;
         };
         
      }; 
      case 2: {
         pl_pos0 = 2;
         // asserta($instance(X))
         // Possibilities: 1
         // Test mit: asserta(A0)
         if ((!pl_backtracking) && (!(
             pl_loadArgVar(0, 1)
          && pl_get_structure(pl_s(PLN_plr__dollarinstance,1), 1)
          && pl_unify_variable(plr_X)
         ))){
            pl_DoBacktracking();
            break;
         };
         pl_dyn_add(pl_dyn_plr__dollarinstance_1, (pl_HeapCell*)pl_ARG[0], pl_addfirst);
      }; 
      case 3: {
         pl_pos0 = 3;
         // fail
         pl_DoBacktracking();	 break;
         
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
bool plr_findall_Choise_1(pl_PrologVar & plr_X, pl_PrologVar & plr_Goal, pl_PrologVar & plr_Xs)
{
   struct pl_Stackframe_Struct {
      pl_PrologVar plr_X1;
      };
   pl_Stackframe_Struct* pl_stackframe;
   if (!pl_backtracking) {
      pl_stackframe = (pl_Stackframe_Struct*)pl_getHeapMem(1);
   };
   
   
   int pl_pos0;
   bool pl_exit0 = false;
   pl_begin(pl_pos0, (void*&)pl_stackframe, 3);
   while(!pl_exit0) {
   switch(pl_pos0) {
      case 0: {
         pl_pos0 = 0;
         // retract($instance(X1))
         // Possibilities: 1
         // Test mit: retract(A0)
         if ((!pl_backtracking) && (!(
             pl_loadArgVar(0, 1)
          && pl_get_structure(pl_s(PLN_plr__dollarinstance,1), 1)
          && pl_unify_variable(pl_stackframe->plr_X1)
         ))){
            pl_DoBacktracking();
            break;
         };
         if (!pl_dyn_retract(pl_dyn_plr__dollarinstance_1, (pl_HeapCell*)pl_ARG[0])){
            pl_DoBacktracking();
            break;
         };
         
      }; 
      case 1: {
         pl_pos0 = 1;
         // intern_reap_(X1, addVar([], Xs))
         // Possibilities: 2
         int pl_pos1;
         bool pl_exit1 = false;
         pl_begin(pl_pos1);
         while(!pl_exit1) {
         switch(pl_pos1) {
            case 0: {
               pl_pos1 = 0;
               pl_choisePoint();
               // Test mit: intern_reap_(X, addVar(REST, Ys))
               if ((!pl_backtracking) && (!(
                   pl_loadArgVariable(0, pl_stackframe->plr_X1)
                && pl_loadArgVar(1, 1)
                && pl_get_structure(pl_s(PLN_plr__bracket_bracketend,0), 1)
                && pl_loadArgVariable(2, plr_Xs)
               ))){
                  pl_DoBacktracking();
                  break;
               };
               if (!plr_intern_reap__Choise_0(*pl_ARG[0],*pl_ARG[1],*pl_ARG[2])){
                  pl_DoBacktracking();
                  break;
               };
               pl_exit1 = true;
               
            }; break;
            case 1: {
               pl_pos1 = 1;
               
               // Test mit: intern_reap_($mark, addVar(Xs, Xs))
               if ((!pl_backtracking) && (!(
                   pl_loadVariable(plr_Xs, 1)
                && pl_get_structure(pl_s(PLN_plr__bracket_bracketend,0), 1)
                && pl_loadVariable(pl_stackframe->plr_X1, 1)
                && pl_get_structure(pl_s(PLN_plr__dollarmark,0), 1)
                && pl_loadArgVar(0, 1)
                && pl_get_structure(pl_s(PLN_plr__bracket_bracketend,0), 1)
               ))){
                  pl_DoBacktracking();
                  break;
               };
               pl_exit1 = true;
               
            }; break;
            case -1: {
               pl_pos1 = -1;
               pl_exit1 = true;
               
            }; break;
            
         }
         }
         if (!pl_end(pl_pos1)) break;
         
      }; 
      case 2: {
         pl_pos0 = 2;
         // !
         pl_cut();
         
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
bool plr_intern_reap_(pl_PrologVar & plr_A0, pl_PrologVar & plr_A1)
{
   void* pl_stackframe = NULL;
   // intern_reap_(A0, A1)
   // Possibilities: 2
   int pl_pos0;
   bool pl_exit0 = false;
   pl_begin(pl_pos0, (void*&)pl_stackframe, 2);
   while(!pl_exit0) {
   switch(pl_pos0) {
      case 0: {
         pl_pos0 = 0;
         pl_choisePoint();
         // Test mit: intern_reap_(X, addVar(REST, Ys))
         if ((!pl_backtracking) && (!(
             pl_loadVariable(plr_A1, 1)
          && pl_get_structure(pl_s(PLN_plr_addVar,2), 1)
          && pl_unify_variableARG(1)
          && pl_unify_variableARG(2)
          && pl_loadArgVariable(0, plr_A0)
         ))){
            pl_DoBacktracking();
            break;
         };
         if (!plr_intern_reap__Choise_0(*pl_ARG[0],*pl_ARG[1],*pl_ARG[2])){
            pl_DoBacktracking();
            break;
         };
         pl_exit0 = true;
         
      }; break;
      case 1: {
         pl_pos0 = 1;
         
         // Test mit: intern_reap_($mark, addVar(Xs, Xs))
         if ((!pl_backtracking) && (!(
             pl_loadVariable(plr_A0, 1)
          && pl_get_structure(pl_s(PLN_plr__dollarmark,0), 1)
          && pl_loadVariable(plr_A1, 1)
          && pl_get_structure(pl_s(PLN_plr_addVar,2), 1)
          && pl_unify_variableARG(0)
          && pl_unify_valueARG(0)
         ))){
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

bool plr_intern_reap__Choise_0(pl_PrologVar & plr_X, pl_PrologVar & plr_REST, pl_PrologVar & plr_Ys)
{
   struct pl_Stackframe_Struct {
      pl_PrologVar plr_X1;
      };
   pl_Stackframe_Struct* pl_stackframe;
   if (!pl_backtracking) {
      pl_stackframe = (pl_Stackframe_Struct*)pl_getHeapMem(1);
   };
   
   
   int pl_pos0;
   bool pl_exit0 = false;
   pl_begin(pl_pos0, (void*&)pl_stackframe, 3);
   while(!pl_exit0) {
   switch(pl_pos0) {
      case 0: {
         pl_pos0 = 0;
         // \=(X, $mark)
         if ((!pl_backtracking) && ((
             pl_loadVariable(plr_X, 1)
          && pl_get_structure(pl_s(PLN_plr__dollarmark,0), 1)
         ))){
            pl_DoBacktracking();
            break;
         };
         
      }; 
      case 1: {
         pl_pos0 = 1;
         // retract($instance(X1))
         // Possibilities: 1
         // Test mit: retract(A0)
         if ((!pl_backtracking) && (!(
             pl_loadArgVar(0, 1)
          && pl_get_structure(pl_s(PLN_plr__dollarinstance,1), 1)
          && pl_unify_variable(pl_stackframe->plr_X1)
         ))){
            pl_DoBacktracking();
            break;
         };
         if (!pl_dyn_retract(pl_dyn_plr__dollarinstance_1, (pl_HeapCell*)pl_ARG[0])){
            pl_DoBacktracking();
            break;
         };
         
      }; 
      case 2: {
         pl_pos0 = 2;
         // !
         pl_cut();
         
      }; 
      case 3: {
         pl_pos0 = 3;
         // intern_reap_(X1, addVar(.(X, REST), Ys))
         // Possibilities: 2
         int pl_pos1;
         bool pl_exit1 = false;
         pl_begin(pl_pos1);
         while(!pl_exit1) {
         switch(pl_pos1) {
            case 0: {
               pl_pos1 = 0;
               pl_choisePoint();
               // Test mit: intern_reap_(X, addVar(REST, Ys))
               if ((!pl_backtracking) && (!(
                   pl_loadArgVariable(0, pl_stackframe->plr_X1)
                && pl_loadArgVar(1, 1)
                && pl_get_structure(pl_s(PLN_plr__dot,2), 1)
                && pl_unify_variable(plr_X)
                && pl_unify_variable(plr_REST)
                && pl_loadArgVariable(2, plr_Ys)
               ))){
                  pl_DoBacktracking();
                  break;
               };
               if (!plr_intern_reap__Choise_0(*pl_ARG[0],*pl_ARG[1],*pl_ARG[2])){
                  pl_DoBacktracking();
                  break;
               };
               pl_exit1 = true;
               
            }; break;
            case 1: {
               pl_pos1 = 1;
               
               // Test mit: intern_reap_($mark, addVar(Xs, Xs))
               if ((!pl_backtracking) && (!(
                   pl_loadVariable(pl_stackframe->plr_X1, 1)
                && pl_get_structure(pl_s(PLN_plr__dollarmark,0), 1)
                && pl_loadVariable(plr_Ys, 1)
                && pl_get_structure(pl_s(PLN_plr__dot,2), 1)
                && pl_unify_variable(plr_X)
                && pl_unify_variable(plr_REST)
                && pl_loadArgVar(0, 1)
                && pl_get_structure(pl_s(PLN_plr__dot,2), 1)
                && pl_unify_variable(plr_X)
                && pl_unify_variable(plr_REST)
               ))){
                  pl_DoBacktracking();
                  break;
               };
               pl_exit1 = true;
               
            }; break;
            case -1: {
               pl_pos1 = -1;
               pl_exit1 = true;
               
            }; break;
            
         }
         }
         if (!pl_end(pl_pos1)) break;
         
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
bool plr_catch(pl_PrologVar & plr_ProtectedGoal, pl_PrologVar & plr_Pattern, pl_PrologVar & plr_Handler)
{
   void* pl_stackframe = NULL;
   
   int pl_pos0;
   bool pl_exit0 = false;
   pl_begin(pl_pos0, (void*&)pl_stackframe, 3);
   while(!pl_exit0) {
   switch(pl_pos0) {
      case 0: {
         pl_pos0 = 0;
         // ProtectedGoal
         if (!pl_FreeCall((pl_HeapCell*)&plr_ProtectedGoal)){
            pl_DoBacktracking();
            break;
         };
         
      }; 
      case 1: {
         pl_pos0 = 1;
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
bool plr_on_exception(pl_PrologVar & plr_Pattern, pl_PrologVar & plr_ProtectedGoal, pl_PrologVar & plr_Handler)
{
   void* pl_stackframe = NULL;
   
   int pl_pos0;
   bool pl_exit0 = false;
   pl_begin(pl_pos0, (void*&)pl_stackframe, 3);
   while(!pl_exit0) {
   switch(pl_pos0) {
      case 0: {
         pl_pos0 = 0;
         // ProtectedGoal
         if (!pl_FreeCall((pl_HeapCell*)&plr_ProtectedGoal)){
            pl_DoBacktracking();
            break;
         };
         
      }; 
      case 1: {
         pl_pos0 = 1;
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
bool plr_throw(pl_PrologVar & plr_Exception)
{
   void* pl_stackframe = NULL;
   
   int pl_pos0;
   bool pl_exit0 = false;
   pl_begin(pl_pos0, (void*&)pl_stackframe, 1);
   while(!pl_exit0) {
   switch(pl_pos0) {
      case 0: {
         pl_pos0 = 0;
         // write(Exception)
         // Possibilities: 1
         // Test mit: write(A0)
         if ((!pl_backtracking) && (!(
             pl_loadArgVariable(0, plr_Exception)
         ))){
            pl_DoBacktracking();
            break;
         };
         if (!pl_foreign_write((FP_term)pl_ARG[0])){
            pl_DoBacktracking();
            break;
         };
         
      }; 
      case 1: {
         pl_pos0 = 1;
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
bool plr_raise_exception(pl_PrologVar & plr_Exception)
{
   void* pl_stackframe = NULL;
   
   int pl_pos0;
   bool pl_exit0 = false;
   pl_begin(pl_pos0, (void*&)pl_stackframe, 1);
   while(!pl_exit0) {
   switch(pl_pos0) {
      case 0: {
         pl_pos0 = 0;
         // write(Exception)
         // Possibilities: 1
         // Test mit: write(A0)
         if ((!pl_backtracking) && (!(
             pl_loadArgVariable(0, plr_Exception)
         ))){
            pl_DoBacktracking();
            break;
         };
         if (!pl_foreign_write((FP_term)pl_ARG[0])){
            pl_DoBacktracking();
            break;
         };
         
      }; 
      case 1: {
         pl_pos0 = 1;
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
bool plr_member(pl_PrologVar & plr_A0, pl_PrologVar & plr_A1)
{
   void* pl_stackframe = NULL;
   // member(A0, A1)
   // Possibilities: 2
   int pl_pos0;
   bool pl_exit0 = false;
   pl_begin(pl_pos0, (void*&)pl_stackframe, 2);
   while(!pl_exit0) {
   switch(pl_pos0) {
      case 0: {
         pl_pos0 = 0;
         pl_choisePoint();
         // Test mit: member(X, .(X, Xs))
         if ((!pl_backtracking) && (!(
             pl_loadVariable(plr_A1, 1)
          && pl_get_structure(pl_s(PLN_plr__dot,2), 1)
          && pl_unify_variableARG(0)
          && pl_unify_variableARG(1)
          && pl_loadArgValue(0,plr_A0)
         ))){
            pl_DoBacktracking();
            break;
         };
         pl_exit0 = true;
         
      }; break;
      case 1: {
         pl_pos0 = 1;
         
         // Test mit: member(X, .(Y, Ys))
         if ((!pl_backtracking) && (!(
             pl_loadVariable(plr_A1, 1)
          && pl_get_structure(pl_s(PLN_plr__dot,2), 1)
          && pl_unify_variableARG(1)
          && pl_unify_variableARG(2)
          && pl_loadArgVariable(0, plr_A0)
         ))){
            pl_DoBacktracking();
            break;
         };
         if (!plr_member_Choise_1(*pl_ARG[0],*pl_ARG[1],*pl_ARG[2])){
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

bool plr_member_Choise_1(pl_PrologVar & plr_X, pl_PrologVar & plr_Y, pl_PrologVar & plr_Ys)
{
   void* pl_stackframe = NULL;
   
   int pl_pos0;
   bool pl_exit0 = false;
   pl_begin(pl_pos0, (void*&)pl_stackframe, 3);
   while(!pl_exit0) {
   switch(pl_pos0) {
      case 0: {
         pl_pos0 = 0;
         // member(X, Ys)
         // Possibilities: 2
         int pl_pos1;
         bool pl_exit1 = false;
         pl_begin(pl_pos1);
         while(!pl_exit1) {
         switch(pl_pos1) {
            case 0: {
               pl_pos1 = 0;
               pl_choisePoint();
               // Test mit: member(X, .(X, Xs))
               if ((!pl_backtracking) && (!(
                   pl_loadVariable(plr_Ys, 1)
                && pl_get_structure(pl_s(PLN_plr__dot,2), 1)
                && pl_unify_variableARG(0)
                && pl_unify_variableARG(1)
                && pl_loadArgValue(0,plr_X)
               ))){
                  pl_DoBacktracking();
                  break;
               };
               pl_exit1 = true;
               
            }; break;
            case 1: {
               pl_pos1 = 1;
               
               // Test mit: member(X, .(Y, Ys))
               if ((!pl_backtracking) && (!(
                   pl_loadVariable(plr_Ys, 1)
                && pl_get_structure(pl_s(PLN_plr__dot,2), 1)
                && pl_unify_variableARG(1)
                && pl_unify_variableARG(2)
                && pl_loadArgVariable(0, plr_X)
               ))){
                  pl_DoBacktracking();
                  break;
               };
               if (!plr_member_Choise_1(*pl_ARG[0],*pl_ARG[1],*pl_ARG[2])){
                  pl_DoBacktracking();
                  break;
               };
               pl_exit1 = true;
               
            }; break;
            case -1: {
               pl_pos1 = -1;
               pl_exit1 = true;
               
            }; break;
            
         }
         }
         if (!pl_end(pl_pos1)) break;
         
      }; 
      case 1: {
         pl_pos0 = 1;
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
bool plr_append(pl_PrologVar & plr_A0, pl_PrologVar & plr_A1, pl_PrologVar & plr_A2)
{
   void* pl_stackframe = NULL;
   // append(A0, A1, A2)
   // Possibilities: 2
   int pl_pos0;
   bool pl_exit0 = false;
   pl_begin(pl_pos0, (void*&)pl_stackframe, 3);
   while(!pl_exit0) {
   switch(pl_pos0) {
      case 0: {
         pl_pos0 = 0;
         pl_choisePoint();
         // Test mit: append([], Ys, Ys)
         if ((!pl_backtracking) && (!(
             pl_loadVariable(plr_A0, 1)
          && pl_get_structure(pl_s(PLN_plr__bracket_bracketend,0), 1)
          && pl_loadVariable(plr_A2, 1)
          && pl_unify_variable(plr_A1, 1)
          && pl_loadArgVariable(0, plr_A1)
         ))){
            pl_DoBacktracking();
            break;
         };
         pl_exit0 = true;
         
      }; break;
      case 1: {
         pl_pos0 = 1;
         
         // Test mit: append(.(X, Xs), Ys, .(X, Zs))
         if ((!pl_backtracking) && (!(
             pl_loadVariable(plr_A0, 1)
          && pl_get_structure(pl_s(PLN_plr__dot,2), 1)
          && pl_unify_variableARG(0)
          && pl_unify_variableARG(1)
          && pl_loadVariable(plr_A2, 1)
          && pl_get_structure(pl_s(PLN_plr__dot,2), 1)
          && pl_unify_valueARG(0)
          && pl_unify_variableARG(3)
          && pl_loadArgVariable(2, plr_A1)
         ))){
            pl_DoBacktracking();
            break;
         };
         if (!plr_append_Choise_1(*pl_ARG[0],*pl_ARG[1],*pl_ARG[2],*pl_ARG[3])){
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

bool plr_append_Choise_1(pl_PrologVar & plr_X, pl_PrologVar & plr_Xs, pl_PrologVar & plr_Ys, pl_PrologVar & plr_Zs)
{
   void* pl_stackframe = NULL;
   
   int pl_pos0;
   bool pl_exit0 = false;
   pl_begin(pl_pos0, (void*&)pl_stackframe, 4);
   while(!pl_exit0) {
   switch(pl_pos0) {
      case 0: {
         pl_pos0 = 0;
         // append(Xs, Ys, Zs)
         // Possibilities: 2
         int pl_pos1;
         bool pl_exit1 = false;
         pl_begin(pl_pos1);
         while(!pl_exit1) {
         switch(pl_pos1) {
            case 0: {
               pl_pos1 = 0;
               pl_choisePoint();
               // Test mit: append([], Ys, Ys)
               if ((!pl_backtracking) && (!(
                   pl_loadVariable(plr_Xs, 1)
                && pl_get_structure(pl_s(PLN_plr__bracket_bracketend,0), 1)
                && pl_loadVariable(plr_Zs, 1)
                && pl_unify_variable(plr_Ys, 1)
                && pl_loadArgVariable(0, plr_Ys)
               ))){
                  pl_DoBacktracking();
                  break;
               };
               pl_exit1 = true;
               
            }; break;
            case 1: {
               pl_pos1 = 1;
               
               // Test mit: append(.(X, Xs), Ys, .(X, Zs))
               if ((!pl_backtracking) && (!(
                   pl_loadVariable(plr_Xs, 1)
                && pl_get_structure(pl_s(PLN_plr__dot,2), 1)
                && pl_unify_variableARG(0)
                && pl_unify_variableARG(1)
                && pl_loadVariable(plr_Zs, 1)
                && pl_get_structure(pl_s(PLN_plr__dot,2), 1)
                && pl_unify_valueARG(0)
                && pl_unify_variableARG(3)
                && pl_loadArgVariable(2, plr_Ys)
               ))){
                  pl_DoBacktracking();
                  break;
               };
               if (!plr_append_Choise_1(*pl_ARG[0],*pl_ARG[1],*pl_ARG[2],*pl_ARG[3])){
                  pl_DoBacktracking();
                  break;
               };
               pl_exit1 = true;
               
            }; break;
            case -1: {
               pl_pos1 = -1;
               pl_exit1 = true;
               
            }; break;
            
         }
         }
         if (!pl_end(pl_pos1)) break;
         
      }; 
      case 1: {
         pl_pos0 = 1;
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
bool plr_reverse(pl_PrologVar & plr_Xs, pl_PrologVar & plr_Ys)
{
   void* pl_stackframe = NULL;
   
   int pl_pos0;
   bool pl_exit0 = false;
   pl_begin(pl_pos0, (void*&)pl_stackframe, 2);
   while(!pl_exit0) {
   switch(pl_pos0) {
      case 0: {
         pl_pos0 = 0;
         // reversein(Xs, [], Ys)
         // Possibilities: 2
         int pl_pos1;
         bool pl_exit1 = false;
         pl_begin(pl_pos1);
         while(!pl_exit1) {
         switch(pl_pos1) {
            case 0: {
               pl_pos1 = 0;
               pl_choisePoint();
               // Test mit: reversein(.(X, Xs), Acc, Ys)
               if ((!pl_backtracking) && (!(
                   pl_loadVariable(plr_Xs, 1)
                && pl_get_structure(pl_s(PLN_plr__dot,2), 1)
                && pl_unify_variableARG(0)
                && pl_unify_variableARG(1)
                && pl_loadArgVariable(3, plr_Ys)
                && pl_loadArgVar(2, 1)
                && pl_get_structure(pl_s(PLN_plr__bracket_bracketend,0), 1)
               ))){
                  pl_DoBacktracking();
                  break;
               };
               if (!plr_reversein_Choise_0(*pl_ARG[0],*pl_ARG[1],*pl_ARG[2],*pl_ARG[3])){
                  pl_DoBacktracking();
                  break;
               };
               pl_exit1 = true;
               
            }; break;
            case 1: {
               pl_pos1 = 1;
               
               // Test mit: reversein([], Ys, Ys)
               if ((!pl_backtracking) && (!(
                   pl_loadVariable(plr_Xs, 1)
                && pl_get_structure(pl_s(PLN_plr__bracket_bracketend,0), 1)
                && pl_loadVariable(plr_Ys, 1)
                && pl_get_structure(pl_s(PLN_plr__bracket_bracketend,0), 1)
                && pl_loadArgVar(0, 1)
                && pl_get_structure(pl_s(PLN_plr__bracket_bracketend,0), 1)
               ))){
                  pl_DoBacktracking();
                  break;
               };
               pl_exit1 = true;
               
            }; break;
            case -1: {
               pl_pos1 = -1;
               pl_exit1 = true;
               
            }; break;
            
         }
         }
         if (!pl_end(pl_pos1)) break;
         
      }; 
      case 1: {
         pl_pos0 = 1;
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
bool plr_reversein(pl_PrologVar & plr_A0, pl_PrologVar & plr_A1, pl_PrologVar & plr_A2)
{
   void* pl_stackframe = NULL;
   // reversein(A0, A1, A2)
   // Possibilities: 2
   int pl_pos0;
   bool pl_exit0 = false;
   pl_begin(pl_pos0, (void*&)pl_stackframe, 3);
   while(!pl_exit0) {
   switch(pl_pos0) {
      case 0: {
         pl_pos0 = 0;
         pl_choisePoint();
         // Test mit: reversein(.(X, Xs), Acc, Ys)
         if ((!pl_backtracking) && (!(
             pl_loadVariable(plr_A0, 1)
          && pl_get_structure(pl_s(PLN_plr__dot,2), 1)
          && pl_unify_variableARG(0)
          && pl_unify_variableARG(1)
          && pl_loadArgVariable(3, plr_A2)
          && pl_loadArgVariable(2, plr_A1)
         ))){
            pl_DoBacktracking();
            break;
         };
         if (!plr_reversein_Choise_0(*pl_ARG[0],*pl_ARG[1],*pl_ARG[2],*pl_ARG[3])){
            pl_DoBacktracking();
            break;
         };
         pl_exit0 = true;
         
      }; break;
      case 1: {
         pl_pos0 = 1;
         
         // Test mit: reversein([], Ys, Ys)
         if ((!pl_backtracking) && (!(
             pl_loadVariable(plr_A0, 1)
          && pl_get_structure(pl_s(PLN_plr__bracket_bracketend,0), 1)
          && pl_loadVariable(plr_A2, 1)
          && pl_unify_variable(plr_A1, 1)
          && pl_loadArgVariable(0, plr_A1)
         ))){
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

bool plr_reversein_Choise_0(pl_PrologVar & plr_X, pl_PrologVar & plr_Xs, pl_PrologVar & plr_Acc, pl_PrologVar & plr_Ys)
{
   void* pl_stackframe = NULL;
   
   int pl_pos0;
   bool pl_exit0 = false;
   pl_begin(pl_pos0, (void*&)pl_stackframe, 4);
   while(!pl_exit0) {
   switch(pl_pos0) {
      case 0: {
         pl_pos0 = 0;
         // reversein(Xs, .(X, Acc), Ys)
         // Possibilities: 2
         int pl_pos1;
         bool pl_exit1 = false;
         pl_begin(pl_pos1);
         while(!pl_exit1) {
         switch(pl_pos1) {
            case 0: {
               pl_pos1 = 0;
               pl_choisePoint();
               // Test mit: reversein(.(X, Xs), Acc, Ys)
               if ((!pl_backtracking) && (!(
                   pl_loadVariable(plr_Xs, 1)
                && pl_get_structure(pl_s(PLN_plr__dot,2), 1)
                && pl_unify_variableARG(0)
                && pl_unify_variableARG(1)
                && pl_loadArgVariable(3, plr_Ys)
                && pl_loadArgVar(2, 1)
                && pl_get_structure(pl_s(PLN_plr__dot,2), 1)
                && pl_unify_variable(plr_X)
                && pl_unify_variable(plr_Acc)
               ))){
                  pl_DoBacktracking();
                  break;
               };
               if (!plr_reversein_Choise_0(*pl_ARG[0],*pl_ARG[1],*pl_ARG[2],*pl_ARG[3])){
                  pl_DoBacktracking();
                  break;
               };
               pl_exit1 = true;
               
            }; break;
            case 1: {
               pl_pos1 = 1;
               
               // Test mit: reversein([], Ys, Ys)
               if ((!pl_backtracking) && (!(
                   pl_loadVariable(plr_Xs, 1)
                && pl_get_structure(pl_s(PLN_plr__bracket_bracketend,0), 1)
                && pl_loadVariable(plr_Ys, 1)
                && pl_get_structure(pl_s(PLN_plr__dot,2), 1)
                && pl_unify_variable(plr_X)
                && pl_unify_variable(plr_Acc)
                && pl_loadArgVar(0, 1)
                && pl_get_structure(pl_s(PLN_plr__dot,2), 1)
                && pl_unify_variable(plr_X)
                && pl_unify_variable(plr_Acc)
               ))){
                  pl_DoBacktracking();
                  break;
               };
               pl_exit1 = true;
               
            }; break;
            case -1: {
               pl_pos1 = -1;
               pl_exit1 = true;
               
            }; break;
            
         }
         }
         if (!pl_end(pl_pos1)) break;
         
      }; 
      case 1: {
         pl_pos0 = 1;
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
