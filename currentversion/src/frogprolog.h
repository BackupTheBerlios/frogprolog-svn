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
#ifndef __FROGPROLOG__
#define __FROGPROLOG__

typedef void* FP_term;
typedef int FP_atom;
typedef int FP_int;
typedef double FP_real;

#define HP(a) (*((pl_PrologVar*)(a)))

/**
 * Wandelt einen String in ein Atom um
 * @param c Ein Multibyte C-String
 * @return Ein Atom
 */
FP_atom FP_atom_from_string(const char* c);
/**
 * Wandelt einen String in ein Atom um
 * @param c Ein Unicode C-String
 * @return Ein Atom
 */
FP_atom FP_atom_from_wstring(const wchar_t* c);
FP_atom FP_atom_from_wchar(const wchar_t c);
const wchar_t* FP_wstring_from_atom(FP_atom a);
const char* FP_string_from_atom(FP_atom a);
int FP_atom_length(FP_atom a);

bool FP_register_atom(FP_atom a);
bool FP_unregister_atom(FP_atom a);

FP_term FP_create_integer(FP_int v);
FP_term FP_create_real(FP_real v);
FP_term FP_create_atom(FP_atom a);
FP_term FP_create_char(wchar_t ch);
FP_term FP_create_var();
FP_term FP_create_structure(FP_atom name, int arity);
FP_term FP_create_structure_from_array(FP_atom name, int arity, FP_term* elements);
FP_term FP_create_structure_1(FP_atom name, FP_term el1);
FP_term FP_create_structure_2(FP_atom name, FP_term el1, FP_term el2);
FP_term FP_create_structure_3(FP_atom name, FP_term el1, FP_term el2, FP_term el3);
FP_term FP_create_structure_4(FP_atom name, FP_term el1, FP_term el2, FP_term el3, FP_term el4);
FP_term FP_create_structure_5(FP_atom name, FP_term el1, FP_term el2, FP_term el3, FP_term el4, FP_term el5);
FP_term FP_create_structure_6(FP_atom name, FP_term el1, FP_term el2, FP_term el3, FP_term el4, FP_term el5, FP_term el6);
FP_term FP_create_structure_7(FP_atom name, FP_term el1, FP_term el2, FP_term el3, FP_term el4, FP_term el5, FP_term el6, FP_term el7);
FP_term FP_create_structure_8(FP_atom name, FP_term el1, FP_term el2, FP_term el3, FP_term el4, FP_term el5, FP_term el6, FP_term el7, FP_term el8);
FP_term FP_create_list(FP_term head, FP_term tail);
FP_term FP_create_list_from_array(int count, FP_term* elements);
FP_term FP_create_list_from_string(int count, const char* c);
FP_term FP_create_list_from_wstring(int count, const wchar_t* c);
FP_term FP_create_list_from_wstring_char(int count, const wchar_t* c);

bool FP_get_integer(FP_term t, FP_int* i);
bool FP_get_real(FP_term t, FP_real* d);
bool FP_get_atom(FP_term t, FP_atom* a);
bool FP_get_char(FP_term t, wchar_t *ch);
bool FP_get_address(FP_term t, void** pointer);
bool FP_get_var_id(FP_term t, int* i);

bool FP_get_structure(FP_term t, FP_atom* name, int* arity);
bool FP_get_list(FP_term t, FP_term *head, FP_term *tail);
bool FP_get_arg(FP_term t, int i, FP_term* arg);
//bool FP_get_full_list(FP_term t, FP_term* list[], int* count);
int FP_get_list_count(FP_term t);
bool FP_get_list_element(FP_term t, int i, FP_term* arg);

const int FP_TYPE_VARIABLE = 100;
const int FP_TYPE_INTEGER = 101;
const int FP_TYPE_REAL = 102;
const int FP_TYPE_ATOM = 103;
const int FP_TYPE_STRUCTURE = 104;

int FP_term_type(FP_term t);
bool FP_is_variable(FP_term t);
bool FP_is_integer(FP_term t);
bool FP_is_real(FP_term t);
bool FP_is_atom(FP_term t);
bool FP_is_structure(FP_term t);
bool FP_is_list(FP_term t);
bool FP_is_empty_list(FP_term t);
bool FP_is_atomic(FP_term t);
bool FP_is_number(FP_term t);

bool FP_unify(FP_term t1, FP_term t2);
bool FP_testunify(FP_term t1, FP_term t2);
int FP_compare(FP_term t1, FP_term t2);

typedef void * FP_DATABASE;

FP_DATABASE FP_dyn_getDatabase(FP_term t1);
FP_DATABASE FP_dyn_getDatabase(FP_atom atom, int arity);

int FP_dyn_count(FP_DATABASE coll);
bool FP_dyn_prove(FP_DATABASE coll, int i, FP_term c);
void FP_dyn_addfirst(FP_DATABASE coll, FP_term c);
void FP_dyn_addlast(FP_DATABASE coll, FP_term c);
bool FP_dyn_retract(FP_DATABASE coll, FP_term c);
void FP_dyn_retractall(FP_DATABASE coll, FP_term c);
void FP_dyn_remove(FP_DATABASE coll, int i);
void FP_dyn_clear(FP_DATABASE coll);

bool FP_math_is(FP_term target, FP_term formel);
bool FP_math_equal(FP_term f1, FP_term f2);
bool FP_math_nonequal(FP_term f1, FP_term f2);
bool FP_math_greater(FP_term f1, FP_term f2);
bool FP_math_less(FP_term f1, FP_term f2);
bool FP_math_eqgreater(FP_term f1, FP_term f2);
bool FP_math_eqless(FP_term f1, FP_term f2);

void FP_initengine();
bool FP_startBacktracking();

void* FP_malloc(unsigned int size);
void* FP_realloc(void* ptr, unsigned int size);
void* FP_free(void* ptr);
#endif
