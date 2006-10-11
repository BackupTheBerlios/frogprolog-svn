//FrogProlog generated: Mon May  1 17:50:34 2006


// sqr(A0:+integer, A1:-integer).
// assert(A0).
// var(A0).
// nonvar(A0).
// ground(A0).
// atom(A0).
// float(A0).
// integer(A0).
// number(A0).
// atomic(A0).
// simple(A0).
// compound(A0).
// write(A0).
// writeq(A0).
// nl.
// put(A0).
// tab(A0).
// tell(A0).
// telling(A0).
// told.
// read(A0).
// see(A0).
// seeing(A0).
// seen.
// at_end_of_stream.
// put_byte(A0).
// put_char(A0).
// put_code(A0).
// flush_output.
// get_byte(A0).
// get_code(A0).
// get_char(A0).
// peek_byte(A0).
// peek_code(A0).
// peek_char(A0).
// skip(A0).
// functor(A0, A1, A2).
// arg(A0, A1, A2).
// char_type(A0, A1).
// atom_codes(A0, A1).
// atom_chars(A0, A1).
// char_code(A0, A1).
// number_chars(A0, A1).
// number_codes(A0, A1).
// atom_number(A0, A1).
// name(A0, A1).
// term_to_atom(A0, A1).
// atom_to_term(A0, A1, A2).
// atom_concat(A0, A1, A2).
// concat_atom(A0, A1).
// concat_atom(A0, A1, A2).
// atom_length(A0, A1).
// atom_prefix(A0, A1).
// sub_atom(A0, A1, A2, A3, A4).
// showstart :- write(DEA Generator 1.0), nl, write(---------------------), nl.
// loadfile(A) :- write(Loading File: ), write(A), see(A), write( .. done), nl.
// ch_type(-1, Y) :- !, fail.
// ch_type(X, Y) :- char_type(X, Y).
// readbez([]) :- peek_code(X), \+ ch_type(X, csym).
// readbez(.(A, Rest)) :- get_code(A), readbez(Rest).
// eatupwhite :- peek_code(X), \+ ch_type(X, space), !.
// eatupwhite :- get_code(X), eatupwhite.
// reservedword(program).
// reservedword(begin).
// reservedword(end).
// reservedpunct(;, semicolon).
// reservedpunct(., point).
// nexttoken(A) :- peek_code(X), ch_type(X, space), (eatupwhite), fail.
// nexttoken(A) :- at_end_of_stream, =(A, eof).
// nexttoken(A) :- peek_code(X), ch_type(X, csymf), readbez(Code), atom_codes(ATOM, Code), write(ATOM), (reservedword(ATOM), =(A, ATOM); =(A, ident(ATOM))).
// nexttoken(A) :- peek_code(X), atom_codes(ATOM, .(X, [])), reservedpunct(ATOM, NAME), get_code(Y), =(A, NAME).
// nexttoken(X) :- write(Error: ), write(X), write( erwartet), nl.
// scanner(.(A, Rest)) :- nexttoken(A), !, write(Token: ), write(A), nl, (=(A, eof), =(Rest, []); scanner(Rest)).
// init :- showstart, loadfile(zustand.dea), scanner(A), seen, write(A).
//Generated Code:
#include "prologenvironment.h"
#include "prolognames.h"


namespace PrologSystem {
extern pl_Name PLN__cut;
extern pl_Name PLN_fail;
extern pl_Name PLN_false;
extern pl_Name PLN_true;
extern pl_Name PLN_sqr;
extern pl_Name PLN_A0;
extern pl_Name PLN_A1;
extern pl_Name PLN_assert;
extern pl_Name PLN_var;
extern pl_Name PLN_nonvar;
extern pl_Name PLN_ground;
extern pl_Name PLN_atom;
extern pl_Name PLN_float;
extern pl_Name PLN_integer;
extern pl_Name PLN_number;
extern pl_Name PLN_atomic;
extern pl_Name PLN_simple;
extern pl_Name PLN_compound;
extern pl_Name PLN_write;
extern pl_Name PLN_writeq;
extern pl_Name PLN_nl;
extern pl_Name PLN_put;
extern pl_Name PLN_tab;
extern pl_Name PLN_tell;
extern pl_Name PLN_telling;
extern pl_Name PLN_told;
extern pl_Name PLN_read;
extern pl_Name PLN_see;
extern pl_Name PLN_seeing;
extern pl_Name PLN_seen;
extern pl_Name PLN_at_end_of_stream;
extern pl_Name PLN_put_byte;
extern pl_Name PLN_put_char;
extern pl_Name PLN_put_code;
extern pl_Name PLN_flush_output;
extern pl_Name PLN_get_byte;
extern pl_Name PLN_get_code;
extern pl_Name PLN_get_char;
extern pl_Name PLN_peek_byte;
extern pl_Name PLN_peek_code;
extern pl_Name PLN_peek_char;
extern pl_Name PLN_skip;
extern pl_Name PLN_functor;
extern pl_Name PLN_A2;
extern pl_Name PLN_arg;
extern pl_Name PLN_char_type;
extern pl_Name PLN_atom_codes;
extern pl_Name PLN_atom_chars;
extern pl_Name PLN_char_code;
extern pl_Name PLN_number_chars;
extern pl_Name PLN_number_codes;
extern pl_Name PLN_atom_number;
extern pl_Name PLN_name;
extern pl_Name PLN_term_to_atom;
extern pl_Name PLN_atom_to_term;
extern pl_Name PLN_atom_concat;
extern pl_Name PLN_concat_atom;
extern pl_Name PLN_atom_length;
extern pl_Name PLN_atom_prefix;
extern pl_Name PLN_sub_atom;
extern pl_Name PLN_A3;
extern pl_Name PLN_A4;
extern pl_Name PLN_showstart;
extern pl_Name PLN_DEAGenerator1_dot0;
extern pl_Name PLN__minus_minus_minus_minus_minus_minus_minus_minus_minus_minus_minus_minus_minus_minus_minus_minus_minus_minus_minus_minus_minus;
extern pl_Name PLN_loadfile;
extern pl_Name PLN_A;
extern pl_Name PLN_LoadingFile_colon;
extern pl_Name PLN__dot_dotdone;
extern pl_Name PLN_ch_type;
extern pl_Name PLN_Y;
extern pl_Name PLN_X;
extern pl_Name PLN_readbez;
extern pl_Name PLN__bracket_bracketend;
extern pl_Name PLN_csym;
extern pl_Name PLN__dot;
extern pl_Name PLN_Rest;
extern pl_Name PLN_eatupwhite;
extern pl_Name PLN_space;
extern pl_Name PLN_reservedword;
extern pl_Name PLN_program;
extern pl_Name PLN_begin;
extern pl_Name PLN_end;
extern pl_Name PLN_reservedpunct;
extern pl_Name PLN__dashdot;
extern pl_Name PLN_semicolon;
extern pl_Name PLN_point;
extern pl_Name PLN_nexttoken;
extern pl_Name PLN__equal;
extern pl_Name PLN_eof;
extern pl_Name PLN_csymf;
extern pl_Name PLN_Code;
extern pl_Name PLN_ATOM;
extern pl_Name PLN_ident;
extern pl_Name PLN_NAME;
extern pl_Name PLN_Error_colon;
extern pl_Name PLN_erwartet;
extern pl_Name PLN_scanner;
extern pl_Name PLN_Token_colon;
extern pl_Name PLN_init;
extern pl_Name PLN_zustand_dotdea;
void pl_RegisterNames();

class test
{
public:
   test();
   void pl_RegisterDynPredicates();
   bool showstart();
   bool loadfile(pl_PrologVar & A);
   bool ch_type(pl_PrologVar & A0, pl_PrologVar & A1);
   bool ch_type_Choise_0(pl_PrologVar & Y);
   bool ch_type_Choise_1(pl_PrologVar & X, pl_PrologVar & Y);
   bool readbez(pl_PrologVar & A0);
   bool readbez_Choise_0();
   bool readbez_Choise_1(pl_PrologVar & A, pl_PrologVar & Rest);
   bool eatupwhite();
   bool eatupwhite_Choise_0();
   bool eatupwhite_Choise_1();
   bool reservedword(pl_PrologVar & A0);
   bool reservedpunct(pl_PrologVar & A0, pl_PrologVar & A1);
   bool nexttoken(pl_PrologVar & A0);
   bool nexttoken_Choise_0(pl_PrologVar & A);
   bool nexttoken_Choise_1(pl_PrologVar & A);
   bool nexttoken_Choise_2(pl_PrologVar & A);
   bool nexttoken_Choise_3(pl_PrologVar & A);
   bool nexttoken_Choise_4(pl_PrologVar & X);
   bool scanner(pl_PrologVar & A, pl_PrologVar & Rest);
   bool init();
   
};
};

