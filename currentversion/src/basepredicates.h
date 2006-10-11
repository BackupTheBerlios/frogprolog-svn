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

#ifndef __BASEPREDICATESUNIT__
#define __BASEPREDICATESUNIT__

#include "frogprolog.h"


bool pl_foreign_sqrt(int fin, int* fout);

bool pl_foreign_asserta(FP_term t1);
bool pl_foreign_assertz(FP_term t1);
bool pl_foreign_assert2a(FP_term t1, FP_term t2);
bool pl_foreign_assert2z(FP_term t1, FP_term t2);
bool pl_foreign_retract2(FP_term t1, FP_term t2);
bool pl_foreign_retract(FP_term t1);
bool pl_foreign_retractall(FP_term t1);
bool pl_foreign_abolish(FP_term t1, FP_term t2);
bool pl_foreign_equal(FP_term t1, FP_term t2);
bool pl_foreign_nonequal(FP_term t1, FP_term t2);
bool pl_foreign_is(FP_term t1, FP_term t2);
bool pl_foreign_arithequal(FP_term t1, FP_term t2);
bool pl_foreign_arithnonequal(FP_term t1, FP_term t2);
bool pl_foreign_arithless(FP_term t1, FP_term t2);
bool pl_foreign_aritheqless(FP_term t1, FP_term t2);
bool pl_foreign_arithgreater(FP_term t1, FP_term t2);
bool pl_foreign_aritheqgreater(FP_term t1, FP_term t2);
bool pl_foreign_fail();
bool pl_foreign_true();

bool pl_foreign_instequal(FP_term t1, FP_term t2);
bool pl_foreign_instnonequal(FP_term t1, FP_term t2);
bool pl_foreign_instless(FP_term t1, FP_term t2);
bool pl_foreign_insteqless(FP_term t1, FP_term t2);
bool pl_foreign_instgreater(FP_term t1, FP_term t2);
bool pl_foreign_insteqgreater(FP_term t1, FP_term t2);

bool pl_foreign_bye();
bool pl_foreign_halt();
bool pl_foreign_repeat();

bool pl_foreign_var(FP_term t);
bool pl_foreign_nonvar(FP_term t);
bool pl_foreign_ground(FP_term t);
bool pl_foreign_atom(FP_term t);
bool pl_foreign_float(FP_term t);
bool pl_foreign_integer(FP_term t);
bool pl_foreign_number(FP_term t);
bool pl_foreign_atomic(FP_term t);
bool pl_foreign_simple(FP_term t);
bool pl_foreign_compound(FP_term t);
//bool pl_foreign_write(FP_term stream, FP_term t);
//bool pl_foreign_writeq(FP_term stream, FP_term t);
bool pl_foreign_write(FP_term t);
bool pl_foreign_writeq(FP_term t);
bool pl_foreign_nl();
bool pl_foreign_put(FP_term t);
bool pl_foreign_tab(FP_term t);
bool pl_foreign_tell(FP_term t);
bool pl_foreign_telling(FP_term t);
bool pl_foreign_told();

//read usw.

bool pl_foreign_read(FP_term t);
bool pl_foreign_see(FP_term t);
bool pl_foreign_seeing(FP_term t);
bool pl_foreign_seen();
bool pl_foreign_at_end_of_stream();

bool pl_foreign_put_byte(FP_term t);
bool pl_foreign_put_char(FP_term t);
bool pl_foreign_put_code(FP_term t);

bool pl_foreign_flush_output();
bool pl_foreign_get_byte(FP_term t);
bool pl_foreign_get_code(FP_term t);
bool pl_foreign_get_char(FP_term t);
bool pl_foreign_peek_byte(FP_term t);
bool pl_foreign_peek_code(FP_term t);
bool pl_foreign_peek_char(FP_term t);
bool pl_foreign_skip(FP_term t);

bool pl_foreign_functor(FP_term term, FP_term functor, FP_term arity);
bool pl_foreign_arg(FP_term arg, FP_term term, FP_term value);
bool pl_foreign_between(FP_term low, FP_term high, FP_term value);
bool pl_foreign_succ(FP_term int1, FP_term int2);
bool pl_foreign_plus(FP_term int1, FP_term int2, FP_term int3);

bool pl_foreign_char_type(FP_term char_t, FP_term term);

bool pl_foreign_atom_codes(FP_term atom, FP_term string);
bool pl_foreign_atom_chars(FP_term atom, FP_term chars);
bool pl_foreign_char_code(FP_term atom, FP_term code);
bool pl_foreign_number_chars(FP_term number, FP_term char_list);
bool pl_foreign_number_codes(FP_term number, FP_term code_list);
bool pl_foreign_atom_number(FP_term atom, FP_term number);
bool pl_foreign_name(FP_term atomorint, FP_term string);
bool pl_foreign_term_to_atom(FP_term term, FP_term atom);
bool pl_foreign_atom_to_term(FP_term atom, FP_term term, FP_term binding);
bool pl_foreign_atom_concat(FP_term atom1, FP_term atom2, FP_term atom3);
bool pl_foreign_concat_atom2(FP_term list, FP_term atom);
bool pl_foreign_concat_atom3(FP_term list, FP_term seperator, FP_term atom);
bool pl_foreign_atom_length(FP_term atom, FP_term length);
bool pl_foreign_atom_prefix(FP_term atom, FP_term prefix);
bool pl_foreign_sub_atom(FP_term atom, FP_term before, FP_term len, FP_term after, FP_term sub);

#endif
