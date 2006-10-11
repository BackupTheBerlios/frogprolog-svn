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
#include "frogprolog.h"

#include "prologenvironment.h"
#include "prolognames.h"

//#include <cassert>
#include <string>

using namespace std;

using namespace PrologSystem;
/*FP_term_ref SP_new_term_ref()
{
   pl_Heap[pl_H].str.type = pl_htStructure;
   pl_Heap[pl_H].str.str = pl_s(pl_intern_list, 0);
   pl_H++;
   
}*/

const wstring pl_converttowide(const char*c)
{
  
	size_t len = strlen(c);
	wchar_t tmp[1];
	mbstate_t state;
	memset(&state, 0, sizeof(state));
	size_t nbytes;
	wstring result;
	while((nbytes = mbrtowc(tmp, c, len, &state)) > 0) {
		if (nbytes >= (size_t) -2) {
			nbytes = 1;
			tmp[0] = *c;
         
          
		};
		result += tmp[0];
		len -= nbytes;
		c += nbytes;      
   
	}
	return result;
   
}

FP_atom FP_atom_from_string(const char* c)
{
	wstring str = pl_converttowide(c);
	return FP_atom_from_wstring(str.c_str());
}
FP_atom FP_atom_from_wstring(const wchar_t* c)
{
   pl_Name n;
   pl_registerName(c, n);
   return n;
}

FP_atom FP_atom_from_wchar(const wchar_t c)
{
   wchar_t t[2];
   t[0] = c;
   t[1] = 0;
   return FP_atom_from_wstring(t);
}
const wchar_t* FP_wstring_from_atom(FP_atom a)
{
   return pl_idToName(a);
}
const char* FP_string_from_atom(FP_atom a)
{
   
}
int FP_atom_length(FP_atom a)
{
   return pl_idToNameLength(a);
}

bool FP_register_atom(FP_atom a)
{
   return true;
}
bool FP_unregister_atom(FP_atom a)
{
   return true;
}

FP_term FP_create_integer(FP_int v)
{
   pl_Heap[pl_H].str.type = pl_htInteger;
   pl_Heap[pl_H].integer.number = v;
   pl_H++;
   return &pl_Heap[pl_H-1];
}

FP_term FP_create_real(FP_real v)
{
   pl_Heap[pl_H].str.type = pl_htReal;
   pl_Heap[pl_H].real.number = v;
   pl_H++;
   return &pl_Heap[pl_H-1];
}

FP_term FP_create_atom(FP_atom a)
{
   pl_Heap[pl_H].str.type = pl_htStructure;
   pl_Heap[pl_H].str.str = pl_s(a, 0);
   pl_H++;
   return &pl_Heap[pl_H-1];
}

FP_term FP_create_char(wchar_t ch) {
   wchar_t str[2];
   str[0] = ch;
   str[1] = 0;
   return FP_create_atom(FP_atom_from_wstring(str));
};

FP_term FP_create_var()
{
   pl_Heap[pl_H].str.type = pl_htReference;
   pl_Heap[pl_H].var.reference = &pl_Heap[pl_H];
   pl_H++;
   return &pl_Heap[pl_H-1];
};

FP_term FP_create_structure(FP_atom name, int arity)
{
   pl_Heap[pl_H].str.type = pl_htStructure;
   pl_Heap[pl_H].str.str = pl_s(name, arity);
   FP_term t = &pl_Heap[pl_H];
   pl_H++;
   for (int i = 0; i < arity; i++) {
      pl_Heap[pl_H].str.type = pl_htReference;
      pl_Heap[pl_H].var.reference = &pl_Heap[pl_H];
      pl_H++;
   };
   return t;
}

FP_term FP_create_structure_from_array(FP_atom name, int arity, FP_term* elements)
{
   pl_Heap[pl_H].str.type = pl_htStructure;
   pl_Heap[pl_H].str.str = pl_s(name, arity);
   FP_term t = &pl_Heap[pl_H];
   pl_H++;
   for (int i = 0; i < arity; i++) {
      pl_Heap[pl_H].str.type = pl_htReference;
      pl_Heap[pl_H].var.reference = (pl_HeapCell*)elements[i];
      pl_H++;
   };
   return t;
}

FP_term FP_create_structure_1(FP_atom name, FP_term el1)
{
   pl_Heap[pl_H].str.type = pl_htStructure;
   pl_Heap[pl_H].str.str = pl_s(name, 1);
   FP_term t = &pl_Heap[pl_H];  pl_H++;
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)el1; pl_H++;
   return t;
}
FP_term FP_create_structure_2(FP_atom name, FP_term el1, FP_term el2)
{
   pl_Heap[pl_H].str.type = pl_htStructure;
   pl_Heap[pl_H].str.str = pl_s(name, 2);
   FP_term t = &pl_Heap[pl_H];  pl_H++;
   
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)el1; pl_H++;
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)el2; pl_H++;
   return t;
}
FP_term FP_create_structure_3(FP_atom name, FP_term el1, FP_term el2, FP_term el3)
{
   pl_Heap[pl_H].str.type = pl_htStructure;
   pl_Heap[pl_H].str.str = pl_s(name, 3);
   FP_term t = &pl_Heap[pl_H];
   pl_H++;
   
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)el1; pl_H++;
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)el2; pl_H++;
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)el3; pl_H++;
   return t;
}
FP_term FP_create_structure_4(FP_atom name, FP_term el1, FP_term el2, FP_term el3, FP_term el4)
{
   pl_Heap[pl_H].str.type = pl_htStructure;
   pl_Heap[pl_H].str.str = pl_s(name, 4);
   FP_term t = &pl_Heap[pl_H];
   pl_H++;
   
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)el1; pl_H++;
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)el2; pl_H++;
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)el3; pl_H++;
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)el4; pl_H++;
   return t;
}
FP_term FP_create_structure_5(FP_atom name, FP_term el1, FP_term el2, FP_term el3, FP_term el4, FP_term el5)
{
   pl_Heap[pl_H].str.type = pl_htStructure;
   pl_Heap[pl_H].str.str = pl_s(name, 5);
   FP_term t = &pl_Heap[pl_H];
   pl_H++;
   
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)el1; pl_H++;
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)el2; pl_H++;
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)el3; pl_H++;
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)el4; pl_H++;
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)el5; pl_H++;
   return t;
}
FP_term FP_create_structure_6(FP_atom name, FP_term el1, FP_term el2, FP_term el3, FP_term el4, FP_term el5, FP_term el6)
{
   pl_Heap[pl_H].str.type = pl_htStructure;
   pl_Heap[pl_H].str.str = pl_s(name, 6);
   FP_term t = &pl_Heap[pl_H];
   pl_H++;
   
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)el1; pl_H++;
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)el2; pl_H++;
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)el3; pl_H++;
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)el4; pl_H++;
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)el5; pl_H++;
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)el6; pl_H++;
   return t;
}
FP_term FP_create_structure_7(FP_atom name, FP_term el1, FP_term el2, FP_term el3, FP_term el4, FP_term el5, FP_term el6, FP_term el7)
{
   pl_Heap[pl_H].str.type = pl_htStructure;
   pl_Heap[pl_H].str.str = pl_s(name, 7);
   FP_term t = &pl_Heap[pl_H];
   pl_H++;
   
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)el1; pl_H++;
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)el2; pl_H++;
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)el3; pl_H++;
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)el4; pl_H++;
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)el5; pl_H++;
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)el6; pl_H++;
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)el7; pl_H++;
   return t;
}
FP_term FP_create_structure_8(FP_atom name, FP_term el1, FP_term el2, FP_term el3, FP_term el4, FP_term el5, FP_term el6, FP_term el7, FP_term el8)
{
   pl_Heap[pl_H].str.type = pl_htStructure;
   pl_Heap[pl_H].str.str = pl_s(name, 8);
   FP_term t = &pl_Heap[pl_H];
   pl_H++;
   
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)el1; pl_H++;
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)el2; pl_H++;
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)el3; pl_H++;
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)el4; pl_H++;
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)el5; pl_H++;
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)el6; pl_H++;
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)el7; pl_H++;
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)el8; pl_H++;
   return t;
}
FP_term FP_create_list(FP_term head, FP_term tail)
{
   pl_Heap[pl_H].str.type = pl_htStructure;
   pl_Heap[pl_H].str.str = pl_s(pl_intern_list, 2);
   FP_term t = &pl_Heap[pl_H];  pl_H++;
   
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)head; pl_H++;
   pl_Heap[pl_H].str.type = pl_htReference; pl_Heap[pl_H].var.reference = (pl_HeapCell*)tail; pl_H++;
   return t;
}

FP_term FP_create_list_from_array(int count, FP_term* elements)
{
   FP_term first;
   pl_HeapCell** lastelement = NULL;
   if (count == 0) {
      pl_Heap[pl_H].str.type = pl_htStructure;
      pl_Heap[pl_H].str.str = pl_s(pl_intern_emptylist, 0);
      FP_term t = &pl_Heap[pl_H];  pl_H++;
      return t;
   } else {
      pl_Heap[pl_H].str.type = pl_htStructure;
      pl_Heap[pl_H].str.str = pl_s(pl_intern_list, 2);
      FP_term t = &pl_Heap[pl_H];  pl_H++;
      first = t;
      pl_Heap[pl_H].str.type = pl_htReference; 
      pl_Heap[pl_H].var.reference = (pl_HeapCell*)elements[0]; 
      pl_H++; 
      pl_Heap[pl_H].str.type = pl_htReference; 
      lastelement = &pl_Heap[pl_H].var.reference;
      pl_H++;
      
      for (int i = 1; i < count; i++) {
	 pl_Heap[pl_H].str.type = pl_htStructure;
	 pl_Heap[pl_H].str.str = pl_s(pl_intern_list, 2);
	 *lastelement = &pl_Heap[pl_H];  pl_H++;
   
	 pl_Heap[pl_H].str.type = pl_htReference; 
	 pl_Heap[pl_H].var.reference = (pl_HeapCell*)elements[i]; 
	 pl_H++; 
	 pl_Heap[pl_H].str.type = pl_htReference; 
	 lastelement = &pl_Heap[pl_H].var.reference;
	 pl_H++;
      };
      
      pl_Heap[pl_H].str.type = pl_htStructure;
      pl_Heap[pl_H].str.str = pl_s(pl_intern_emptylist, 0);
      *lastelement = &pl_Heap[pl_H];  pl_H++;

   };
   return first;
}

FP_term FP_create_list_from_string(int count, const char* c)
{
   FP_term first;
   pl_HeapCell** lastelement = NULL;
   if (count == 0) {
      pl_Heap[pl_H].str.type = pl_htStructure;
      pl_Heap[pl_H].str.str = pl_s(pl_intern_emptylist, 0);
      FP_term t = &pl_Heap[pl_H];  pl_H++;
      return t;
   } else {
      pl_Heap[pl_H].str.type = pl_htStructure;
      pl_Heap[pl_H].str.str = pl_s(pl_intern_list, 2);
      FP_term t = &pl_Heap[pl_H];  pl_H++;
      first = t;
      pl_Heap[pl_H].str.type = pl_htInteger; 
      pl_Heap[pl_H].integer.number = c[0]; 
      pl_H++; 
      pl_Heap[pl_H].str.type = pl_htReference; 
      lastelement = &pl_Heap[pl_H].var.reference;
      pl_H++;
      
      for (int i = 1; i < count; i++) {
	 pl_Heap[pl_H].str.type = pl_htStructure;
	 pl_Heap[pl_H].str.str = pl_s(pl_intern_list, 2);
	 *lastelement = &pl_Heap[pl_H];  pl_H++;
   
	 pl_Heap[pl_H].str.type = pl_htInteger; 
	 pl_Heap[pl_H].integer.number = c[i]; 
	 pl_H++; 
	 pl_Heap[pl_H].str.type = pl_htReference; 
	 lastelement = &pl_Heap[pl_H].var.reference;
	 pl_H++;
      };
      
      pl_Heap[pl_H].str.type = pl_htStructure;
      pl_Heap[pl_H].str.str = pl_s(pl_intern_emptylist, 0);
      *lastelement = &pl_Heap[pl_H];  pl_H++;

   };
   return first;
};

FP_term FP_create_list_from_wstring(int count, const wchar_t* c)
{
   FP_term first;
   pl_HeapCell** lastelement = NULL;
   if (count == 0) {
      pl_Heap[pl_H].str.type = pl_htStructure;
      pl_Heap[pl_H].str.str = pl_s(pl_intern_emptylist, 0);
      FP_term t = &pl_Heap[pl_H];  pl_H++;
      return t;
   } else {
      pl_Heap[pl_H].str.type = pl_htStructure;
      pl_Heap[pl_H].str.str = pl_s(pl_intern_list, 2);
      FP_term t = &pl_Heap[pl_H];  pl_H++;
      first = t;
      pl_Heap[pl_H].str.type = pl_htInteger; 
      pl_Heap[pl_H].integer.number = c[0]; 
      pl_H++; 
      pl_Heap[pl_H].str.type = pl_htReference; 
      lastelement = &pl_Heap[pl_H].var.reference;
      pl_H++;
      
      for (int i = 1; i < count; i++) {
	 pl_Heap[pl_H].str.type = pl_htStructure;
	 pl_Heap[pl_H].str.str = pl_s(pl_intern_list, 2);
	 *lastelement = &pl_Heap[pl_H];  pl_H++;
   
	 pl_Heap[pl_H].str.type = pl_htInteger; 
	 pl_Heap[pl_H].integer.number = c[i]; 
	 pl_H++; 
	 pl_Heap[pl_H].str.type = pl_htReference; 
	 lastelement = &pl_Heap[pl_H].var.reference;
	 pl_H++;
      };
      
      pl_Heap[pl_H].str.type = pl_htStructure;
      pl_Heap[pl_H].str.str = pl_s(pl_intern_emptylist, 0);
      *lastelement = &pl_Heap[pl_H];  pl_H++;

   };
   return first;
};

FP_term FP_create_list_from_wstring_char(int count, const wchar_t* c)
{
   FP_term first;
   pl_HeapCell** lastelement = NULL;
   if (count == 0) {
      pl_Heap[pl_H].str.type = pl_htStructure;
      pl_Heap[pl_H].str.str = pl_s(pl_intern_emptylist, 0);
      FP_term t = &pl_Heap[pl_H];  pl_H++;
      return t;
   } else {
      pl_Heap[pl_H].str.type = pl_htStructure;
      pl_Heap[pl_H].str.str = pl_s(pl_intern_list, 2);
      FP_term t = &pl_Heap[pl_H];  pl_H++;
      first = t;
      pl_Heap[pl_H].str.type = pl_htStructure; 
      pl_Heap[pl_H].str.str = pl_s(FP_atom_from_wchar(c[0]), 0);
      //pl_Heap[pl_H].integer.number = c[0]; 
      pl_H++; 
      pl_Heap[pl_H].str.type = pl_htReference; 
      lastelement = &pl_Heap[pl_H].var.reference;
      pl_H++;
      
      for (int i = 1; i < count; i++) {
	 pl_Heap[pl_H].str.type = pl_htStructure;
	 pl_Heap[pl_H].str.str = pl_s(pl_intern_list, 2);
	 *lastelement = &pl_Heap[pl_H];  pl_H++;
   
	 pl_Heap[pl_H].str.type = pl_htStructure; 
	 pl_Heap[pl_H].str.str = pl_s(FP_atom_from_wchar(c[i]), 0);
	 pl_H++; 
	 pl_Heap[pl_H].str.type = pl_htReference; 
	 lastelement = &pl_Heap[pl_H].var.reference;
	 pl_H++;
      };
      
      pl_Heap[pl_H].str.type = pl_htStructure;
      pl_Heap[pl_H].str.str = pl_s(pl_intern_emptylist, 0);
      *lastelement = &pl_Heap[pl_H];  pl_H++;

   };
   return first;
};

bool FP_get_integer(FP_term t, FP_int* i)
{
   pl_HeapCell* cell = (pl_HeapCell*) t;
   cell = pl_deref(cell);
   if (cell->type != pl_htInteger) return false;
   if (i) {
      *i = cell->integer.number;
   };
   return true;
};

bool FP_get_real(FP_term t, FP_real* d)
{
   pl_HeapCell* cell = (pl_HeapCell*) t;
   cell = pl_deref(cell);
   if (cell->type != pl_htReal) return false;
   if (d) {
      *d = cell->real.number;
   };
   return true;
};

bool FP_get_atom(FP_term t, FP_atom* a)
{
   pl_HeapCell* cell = (pl_HeapCell*) t;
   cell = pl_deref(cell);
   if (cell->type != pl_htStructure || pl_getarity(cell->str.str)!=0) return false;
   if (a) {
      *a = pl_getname(cell->str.str);
   };
   return true;
};

bool FP_get_char(FP_term t, wchar_t *ch)
{
   FP_atom a;
   if (!FP_get_atom(t, &a)) return false;
   const wchar_t* c=FP_wstring_from_atom(a);
   if (wcslen(c) != 1) return false;
   *ch = c[0];
   return true;
};

bool FP_get_address(FP_term t, void** pointer)
{
   pl_HeapCell* cell = (pl_HeapCell*) t;
   cell = pl_deref(cell);
   if (cell->type != pl_htInteger) return false;
   if (pointer) {
      *pointer = (void*)cell->integer.number;
   };
   return true;
};

bool FP_get_var_id(FP_term t, int* i)
{
   pl_HeapCell* cell = (pl_HeapCell*) t;
   cell = pl_deref(cell);
   if (cell->type != pl_htReference) return false;
   *i = ((int)cell - (int)pl_Heap)/sizeof(pl_HeapCell);
   return true;
}

bool FP_get_structure(FP_term t, FP_atom* name, int* arity)
{
   pl_HeapCell* cell = (pl_HeapCell*) t;
   cell = pl_deref(cell);
   if (cell->type != pl_htStructure) return false;
   if (name) {
      *name = pl_getname(cell->str.str);
   };
   if (arity) {
      *arity = pl_getarity(cell->str.str);
   };
   return true;
};

bool FP_get_list(FP_term t, FP_term *head, FP_term *tail)
{
      pl_HeapCell* cell = (pl_HeapCell*) t;
      cell = pl_deref(cell);
      if (cell->type != pl_htStructure || pl_getname(cell->str.str) != pl_intern_list || pl_getarity(cell->str.str) != 2) return false;
      cell++;
      if (head) {
	 *head = pl_deref(cell);
      };
      cell++;
      if (tail) {
	 *tail = pl_deref(cell);
      };
      return true;
};




bool FP_get_arg(FP_term t, int i, FP_term* arg)
{
   pl_HeapCell* cell = (pl_HeapCell*) t;
   cell = pl_deref(cell);
//   assert(i >= 0);
   if (cell->type != pl_htStructure || pl_getarity(cell->str.str) <= i) 
      return false;
   cell+= i+1;
   if (arg) {
      *arg = pl_deref(cell);
   };
   return true;
};

/*bool FP_get_full_list(FP_term t, FP_term* list[], int* count)
{
   
}*/
int FP_get_list_count(FP_term t)
{
   FP_term t2 = t;
   int c = 0;
   while (FP_get_arg(t2, 1, &t2)) {
      c++;
   };
   return c;
}

bool FP_get_list_element(FP_term t, int i, FP_term* arg)
{
   FP_term t2 = t;
   while (i > 0 && FP_get_arg(t2, 1, &t2)) {
      i--;
   };
   if (i != 0) return false;
   FP_get_arg(t2, 0, &t);
   return true;
}

int FP_term_type(FP_term t)
{
   pl_HeapCell* cell = (pl_HeapCell*) t;
   cell = pl_deref(cell);
   switch (cell->type) {
      case pl_htInteger: {
	 return FP_TYPE_INTEGER;
      }; break;
      case pl_htReal: {
	 return FP_TYPE_REAL;
      }; break;
      case pl_htReference: {
	 return FP_TYPE_VARIABLE;
      }; break;
      case pl_htStructure: {
	 if (pl_getarity(cell->str.str) == 0) {
	    return FP_TYPE_ATOM;
	 } else {
	    return FP_TYPE_STRUCTURE;
	 };
      }; break;
   };
}

bool FP_is_variable(FP_term t)
{
   pl_HeapCell* cell = (pl_HeapCell*) t;
   cell = pl_deref(cell);
   return cell->type == pl_htReference;
};

bool FP_is_integer(FP_term t)
{
   pl_HeapCell* cell = (pl_HeapCell*) t;
   cell = pl_deref(cell);
   return cell->type == pl_htInteger;
};
bool FP_is_real(FP_term t)
{
   pl_HeapCell* cell = (pl_HeapCell*) t;
   cell = pl_deref(cell);
   return cell->type == pl_htReal;
};
bool FP_is_atom(FP_term t)
{
   pl_HeapCell* cell = (pl_HeapCell*) t;
   cell = pl_deref(cell);
   return (cell->type == pl_htStructure) && (pl_getarity(cell->str.str)==0);
};
bool FP_is_structure(FP_term t)
{
   pl_HeapCell* cell = (pl_HeapCell*) t;
   cell = pl_deref(cell);
   return (cell->type == pl_htStructure) && (pl_getarity(cell->str.str)!=0);
};
bool FP_is_list(FP_term t)
{
   pl_HeapCell* cell = (pl_HeapCell*) t;
   cell = pl_deref(cell);
   return (cell->type == pl_htStructure) && (pl_getarity(cell->str.str)==2) && (pl_getname(cell->str.str)==pl_intern_list);
};

bool FP_is_empty_list(FP_term t)
{
   pl_HeapCell* cell = (pl_HeapCell*) t;
   cell = pl_deref(cell);
   if (cell->type != pl_htStructure || pl_getname(cell->str.str) != pl_intern_emptylist || pl_getarity(cell->str.str) != 0) return false;
   return true;
};

bool FP_is_atomic(FP_term t)
{
   return FP_is_atom(t) || FP_is_number(t);
}

bool FP_is_number(FP_term t)
{
   pl_HeapCell* cell = (pl_HeapCell*) t;
   cell = pl_deref(cell);
   return (cell->type == pl_htReal) || (cell->type == pl_htInteger);
};

bool FP_testunify(FP_term t1, FP_term t2)
{
   return pl_testunify((pl_HeapCell*)t1, (pl_HeapCell*)t2);
}

bool FP_unify(FP_term t1, FP_term t2)
{
   return pl_unify((pl_HeapCell*)t1, (pl_HeapCell*)t2);
}

int FP_compare(FP_term t1, FP_term t2)
{
   return pl_compare((pl_HeapCell*)t1, (pl_HeapCell*)t2);
}

FP_DATABASE FP_dyn_getDatabase(FP_term t1)
{
   return pl_getCollection((pl_HeapCell*)t1);
}

FP_DATABASE FP_dyn_getDatabase(FP_atom atom, int arity)
{
   return pl_getCollection(atom, arity);
}

int FP_dyn_count(FP_DATABASE coll)
{
   pl_PredicateCollection* c = (pl_PredicateCollection*)coll;
   return  pl_dyn_count(*c);
}
bool FP_dyn_prove(FP_DATABASE coll, int i, FP_term c)
{
   pl_PredicateCollection* c1 = (pl_PredicateCollection*)coll;
   return pl_dyn_prove(*c1, i, (pl_HeapCell*)c);
}
void FP_dyn_addfirst(FP_DATABASE coll, FP_term c)
{
   pl_PredicateCollection* c1 = (pl_PredicateCollection*)coll;
   return  pl_dyn_add(*c1, (pl_HeapCell*)c, pl_addfirst);
}
void FP_dyn_addlast(FP_DATABASE coll, FP_term c)
{
   pl_PredicateCollection* c1 = (pl_PredicateCollection*)coll;
   return  pl_dyn_add(*c1, (pl_HeapCell*)c, pl_addlast);
}
bool FP_dyn_retract(FP_DATABASE coll, FP_term c)
{
   pl_PredicateCollection* c1 = (pl_PredicateCollection*)coll;
   return  pl_dyn_retract(*c1, (pl_HeapCell*)c);
}
void FP_dyn_retractall(FP_DATABASE coll, FP_term c)
{
   pl_PredicateCollection* c1 = (pl_PredicateCollection*)coll;
   return  pl_dyn_retractall(*c1, (pl_HeapCell*)c);
}
void FP_dyn_remove(FP_DATABASE coll, int i)
{
   pl_PredicateCollection* c1 = (pl_PredicateCollection*)coll;
   return  pl_dyn_remove(*c1, i);
}
void FP_dyn_clear(FP_DATABASE coll)
{
   pl_PredicateCollection* c1 = (pl_PredicateCollection*)coll;
   return  pl_dyn_clear(*c1);
}

bool FP_math_is(FP_term target, FP_term formel)
{
   pl_math_pushVar(*((pl_PrologVar*)formel));
   return pl_math_popVar(*((pl_PrologVar*)target));
}

bool FP_math_equal(FP_term f1, FP_term f2)
{
   pl_math_pushVar(*((pl_PrologVar*)f1));
   pl_math_pushVar(*((pl_PrologVar*)f2));
   return pl_math_isEqual();
}
bool FP_math_nonequal(FP_term f1, FP_term f2)
{
   pl_math_pushVar(*((pl_PrologVar*)f1));
   pl_math_pushVar(*((pl_PrologVar*)f2));
   return pl_math_isNonEqual();
}
bool FP_math_greater(FP_term f1, FP_term f2)
{
   pl_math_pushVar(*((pl_PrologVar*)f1));
   pl_math_pushVar(*((pl_PrologVar*)f2));
   return pl_math_isGreater();
}
bool FP_math_less(FP_term f1, FP_term f2)
{
   pl_math_pushVar(*((pl_PrologVar*)f1));
   pl_math_pushVar(*((pl_PrologVar*)f2));
   return pl_math_isLesser();
}
bool FP_math_eqgreater(FP_term f1, FP_term f2)
{
   pl_math_pushVar(*((pl_PrologVar*)f1));
   pl_math_pushVar(*((pl_PrologVar*)f2));
   return pl_math_isEqualGreater();
}
bool FP_math_eqless(FP_term f1, FP_term f2)
{
   pl_math_pushVar(*((pl_PrologVar*)f1));
   pl_math_pushVar(*((pl_PrologVar*)f2));
   return pl_math_isEqualLess();
}

void* FP_malloc(unsigned int size)
{
   
}
void* FP_realloc(void* ptr, unsigned int size)
{
   
}
void* FP_free(void* ptr)
{
   
}

bool FP_startBacktracking()
{
   pl_DoBacktracking();
   if (pl_firsttop == -1) {
      pl_backtracking = false;
      pl_firsttop = 0;
      return false;
   } else {
      return true;
   };
}

void FP_initengine()
{
   pl_initengine();
};
