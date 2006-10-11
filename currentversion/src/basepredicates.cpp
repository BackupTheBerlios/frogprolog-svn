//
// C++ Implementation: basepredicates
//
// Description:
//
//
// Author: Michael Staud <staud@linux>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "basepredicates.h"
#include "externparser.h"
#include "enginefactory.h"
#include "prolog_driver.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <map>

using namespace std;
using namespace UtiExternProlog;


/// sharing oder spezielle Bibliothek?
const string pl_converttomulti(const wchar_t * c) {
    mbstate_t state;
    memset(&state, 0, sizeof(state));
    int buffersize = wcslen(c)*2+3;
    int currentsize = 0;
    char* wp = new char[buffersize];
    char* start = wp;
    do {
        size_t nbytes;
        nbytes = wcrtomb(wp, *c, &state);
        if (nbytes == (size_t)-1) {
            return "";
        }
        wp += nbytes;
        currentsize += nbytes;
        if (currentsize >= buffersize) {
            cerr << "converttomulti: Fehler Buffer ist zu klein für den String";
            delete [] wp;
            return "";

        }

        c++;
    } while(*c != L'\0');
    *wp = 0;
    string result = start;
    delete [] start;
    return result;

}

bool pl_foreign_sqrt(int fin, int* fout) {
    *fout = fin*2;
    return true;
}


bool pl_foreign_assert(FP_term t1) {
    //FP_dyn_assert(t1);
    return true;
};

bool pl_foreign_var(FP_term t) {
    return FP_is_variable(t);
}

bool pl_foreign_nonvar(FP_term t) {
    return !FP_is_variable(t);
}

bool pl_foreign_ground(FP_term t) {
    if (FP_is_variable(t))
        return false;
    if (!FP_is_structure(t))
        return true;
    int arity;
    FP_term subterm;
    FP_get_structure(t, NULL, &arity);
    for (int i = 0; i < arity; i++) {
        FP_get_arg(t, i, &subterm);
        if (!pl_foreign_ground(subterm))
            return false;
    };
    return true;
}

bool pl_foreign_atom(FP_term t) {
    return FP_is_atom(t);
}

bool pl_foreign_float(FP_term t) {
    return FP_is_real(t);
}

bool pl_foreign_integer(FP_term t) {
    return FP_is_integer(t);
}
bool pl_foreign_number(FP_term t) {
    return FP_is_number(t);
}
bool pl_foreign_atomic(FP_term t) {
    return FP_is_atomic(t);
}

bool pl_foreign_simple(FP_term t) {
    return FP_is_atomic(t) || FP_is_variable(t);
}

bool pl_foreign_compound(FP_term t) {
    return !pl_foreign_simple(t);
}

/*bool pl_foreign_write(FP_term stream, FP_term t)
{
	
}
 
bool pl_foreign_writeq(FP_term stream, FP_term t)
{
	
}*/

class pl_IOSystem {
public:
    wostream* outstream;
    wistream* instream;
    wostream* stdout;
    wistream* stdin;
    map<wstring, wostream*> ostrmap;
    map<wstring, wistream*> istrmap;
    wstring outstrname;
    wstring instrname;
    pl_IOSystem() {
        stdout = &wcout;
        stdin = &wcin;
        outstream = &wcout;
        instream = &wcin;
        ostrmap[L"user"] = stdout;
        istrmap[L"user"] = stdin;
        outstrname = L"user";
        instrname = L"user";
    };
};


/*
class convertstream : public istream {
public:
    wistream* instream;
    int_type get()
    {
	    
	    return instream->get();
    };
    __istream_type& get(char_type& __c)
    {
	    wchar_t sb;
	    instream->get(sb);
	    __c = sb;
	    return *this;
    };
    bool eof()
    {
	    return instream->eof();
    }
    bool bad()
    {
	    return bad();
    }
    __istream_type& read(char_type* __s, streamsize __n)
    {
	    wchar_t* sb = new wchar_t[__n];
	    instream->read(sb, __n);
	    for (int i = 0; i < __n; i++) {
		    __s[i] = sb[i];
	    };
	    delete [] sb;
	    return *this;
    }
    inline streamsize gcount() const 
    { return instream->gcount(); }
    convertstream(wistream* ins) {
        instream = ins;
    };
 
};
*/
static pl_IOSystem pl_iostr;

bool pl_foreign_writesec(FP_term t, int level) {
   if (level >= 10) return true;
    if (FP_is_list(t)) {
        FP_term list = t;
        FP_term head;
        FP_term tail;
        *pl_iostr.outstream << L"[";
        do {
            FP_get_list(list, &head, &tail);
            pl_foreign_writesec(head, level+1);
            list = tail;
            if (FP_is_list(list)) {
                *pl_iostr.outstream << L", ";
            } else if (FP_is_empty_list(list)) {
                *pl_iostr.outstream << L"]";
                break;
            } else {
                *pl_iostr.outstream << L"|";
                pl_foreign_write(list);
                break;
            };

        } while(true);
    } else if (FP_is_structure(t)) {
        /// @todo Operatoren beachten
        FP_atom atom;
        int arity;
        FP_get_structure(t, &atom, &arity);
        *pl_iostr.outstream << FP_wstring_from_atom(atom);
        // if (arity > 0) {
        *pl_iostr.outstream << L"(";
        for (int i = 0; i < arity; i++) {
            FP_term t1;
            FP_get_arg(t, i, &t1);
            pl_foreign_writesec(t1, level+1);
            if (i != arity-1)
                *pl_iostr.outstream << L", ";
        };
        *pl_iostr.outstream << L")";
        //};
    } else if (FP_is_atom(t)) {
        FP_atom atom;
        FP_get_atom(t, &atom);
        *pl_iostr.outstream << FP_wstring_from_atom(atom);
    } else if (FP_is_integer(t)) {
        FP_int it;
        FP_get_integer(t, &it);
        *pl_iostr.outstream << it;
    } else if (FP_is_real(t)) {
        FP_real it;
        FP_get_real(t, &it);
        *pl_iostr.outstream << it;
    } else if (FP_is_variable(t)) {
        int value;
        FP_get_var_id(t, &value);
        (*pl_iostr.outstream) << L"X" << value;
    };
    return true;
}

bool pl_foreign_write(FP_term t) {
   return pl_foreign_writesec(t, 0);
};

bool pl_foreign_writeq(FP_term t) {
    pl_foreign_write(t);
    return true;
}

bool pl_foreign_nl() {
    *pl_iostr.outstream << endl;
    return true;
}

bool pl_foreign_put(FP_term t) {
    if (!FP_is_integer(t))
        return false;
    FP_int i;
    FP_get_integer(t, &i);
    wchar_t ch[2];
    ch[0] = i;
    ch[1] = '\0';
    *pl_iostr.outstream << ch;
    return true;
}

bool pl_foreign_tab(FP_term t) {
    if (!FP_is_integer(t))
        return false;
    FP_int i1;
    FP_get_integer(t, &i1);
    if (i1 < 0)
        return false;
    for (int i = 0; i < i1; i++) {
        *pl_iostr.outstream << L" ";
    };
    return true;
}

bool pl_foreign_tell(FP_term t) {
    if (!FP_is_atom(t)) {
        return false;
    };
    FP_atom atom;
    FP_get_atom(t, &atom);
    const wchar_t* c = FP_wstring_from_atom(atom);
    wstring str = c;
    map<wstring, wostream*>::iterator it = pl_iostr.ostrmap.find(str);

    if (it == pl_iostr.ostrmap.end()) {
        string str1 = pl_converttomulti(str.c_str());
        wostream* stream = new wofstream(str1.c_str(), ios_base::out);
        pl_iostr.ostrmap[str] = stream;
        pl_iostr.outstream = stream;
        pl_iostr.outstrname = str;
    } else {
        pl_iostr.outstrname = str;
        pl_iostr.outstream = pl_iostr.ostrmap[str];
    };
    return true;
}

bool pl_foreign_telling(FP_term t) {
    FP_atom atom = FP_atom_from_wstring(pl_iostr.outstrname.c_str());
    FP_term t2 = FP_create_atom(atom);
    return FP_unify(t, t2);
}

bool pl_foreign_told() {
    if (pl_iostr.outstream == pl_iostr.stdout)
        return false;
    wostream* str = pl_iostr.outstream;
    if (dynamic_cast<wofstream*>(str)) {
        dynamic_cast<wofstream*>(str)->close();
    };
    delete str;
    map<wstring, wostream*>::iterator it = pl_iostr.ostrmap.find(pl_iostr.outstrname);

    pl_iostr.ostrmap.erase(it);
    pl_iostr.outstream = pl_iostr.stdout;
    pl_iostr.outstrname = L"user";
    return true;
}

//Read

typedef map<PID, FP_term> pl_varmap;

FP_term pl_foreign_create(Term* term, pl_varmap&m) {
    if (dynamic_cast<Var*>(term)) {
        Var* v = (Var*)term;
        pl_varmap::iterator it = m.find(v->getName());

        if (it == m.end()) {
            FP_term v1 = FP_create_var();
            PID n = v->getName();
            m[n] = v1;
            return v1;
        } else {
            return it->second;
        };

    } else if (dynamic_cast<Structure*>(term)) {
        Structure* s = (Structure*)term;
        FP_term res;
        FP_term * elements = new FP_term[s->elementCount()];
        for (int i = 0; i < s->elementCount(); i++) {
            elements[i] = pl_foreign_create(s->getElement(i), m);
        };

        res = FP_create_structure_from_array(s->getName(), s->elementCount(), elements);
        delete [] elements;
        return res;
    } else if (dynamic_cast<IntNumber*>(term)) {
        IntNumber* t = (IntNumber*)term;
        return FP_create_integer(t->getValue());
    } else if (dynamic_cast<RealNumber*>(term)) {
        RealNumber* t = (RealNumber*)term;
        return FP_create_real(t->getValue());
    }
    return NULL;
};

bool pl_foreign_read(FP_term t) {

    prolog_driver* driver = new prolog_driver();
    driver->newstr = NULL;
    //convertstream constr(pl_iostr.instream);
    //wstring str1;
    //getline(*pl_iostr.instream, str1);
    //string text = "§§§!!!_SELECTED_ONEFACT_!!!§§§ "+pl_converttomulti(str1.c_str());
    //istringstream stext(text);
    driver->parse(*pl_iostr.instream);
    Term* term = driver->newstr;
    pl_varmap m;
    FP_term t2 = pl_foreign_create(term, m);

    delete term;
    delete driver;
    //delete cf;
    return FP_unify(t, t2);
}

bool pl_foreign_see(FP_term t) {
    if (!FP_is_atom(t)) {
        return false;
    };
    FP_atom atom;
    FP_get_atom(t, &atom);
    const wchar_t* c = FP_wstring_from_atom(atom);
    wstring str = c;
    map<wstring, wistream*>::iterator it = pl_iostr.istrmap.find(str);

    if (it == pl_iostr.istrmap.end()) {
        string str1 = pl_converttomulti(str.c_str());
        wistream* stream = new wifstream(str1.c_str(), ios_base::in);
        pl_iostr.istrmap[str] = stream;
        pl_iostr.instream = stream;
        pl_iostr.instrname = str;
    } else {
        pl_iostr.instrname = str;
        pl_iostr.instream = pl_iostr.istrmap[str];
    };
    return true;
}

bool pl_foreign_seeing(FP_term t) {
    FP_atom atom = FP_atom_from_wstring(pl_iostr.instrname.c_str());
    FP_term t2 = FP_create_atom(atom);
    return FP_unify(t, t2);
}

bool pl_foreign_seen() {
   if (pl_iostr.instream == pl_iostr.stdin)
      return false;
   wistream* str = pl_iostr.instream;
   if (dynamic_cast<wifstream*>(str)) {
      dynamic_cast<wifstream*>(str)->close();
   };
   delete str;
   map<wstring, wistream*>::iterator it = pl_iostr.istrmap.find(pl_iostr.instrname);

   pl_iostr.istrmap.erase(it);
   pl_iostr.instream = pl_iostr.stdin;
   pl_iostr.instrname = L"user";
   return true;
}


bool pl_foreign_put_byte(FP_term t)
{
   if (!FP_is_integer(t))
      return false;
   FP_int i1;
   FP_get_integer(t, &i1);
   if (i1 < 0 || i1 > 255)
      return false;
   wchar_t ch = i1;
   pl_iostr.outstream->write(&ch, 1);
   return true;
}

bool pl_foreign_put_char(FP_term t)
{
   if (!FP_is_atom(t))
      return false;
   FP_atom atom;
   int arity;
   FP_get_structure(t, &atom, &arity);
   const wchar_t*at= FP_wstring_from_atom(atom);
  // if (wstrlen(t) != 1) return false;
   
   
   wchar_t t1 = at[0];
   *pl_iostr.outstream << t1;
   return true;
}

bool pl_foreign_put_code(FP_term t)
{
   return pl_foreign_put_byte(t);
}


bool pl_foreign_flush_output()
{
   pl_iostr.outstream->flush();
   return true;
}

bool pl_foreign_get_byte(FP_term t)
{
   if (!pl_iostr.instream->good()) return false;
   wchar_t tk;
   pl_iostr.instream->read(&tk, 1);
   FP_term t1 = FP_create_integer(tk);
   
   return FP_unify(t, t1);
}

bool pl_foreign_get_code(FP_term t)
{
   
   return pl_foreign_get_byte(t);
}

bool pl_foreign_get_char(FP_term t)
{
   if (!pl_iostr.instream->good()) return false;
  wchar_t ch;
  *pl_iostr.instream >> ch;
  wchar_t text[2];
  text[0] = ch;
  text[1] = 0;
  FP_atom a = FP_atom_from_wstring(text);
  FP_term t1 = FP_create_atom(a);
  return FP_unify(t, t1);
}

bool pl_foreign_peek_byte(FP_term t)
{
   if (!pl_iostr.instream->good()) return false;
   wchar_t bt = pl_iostr.instream->peek();
   FP_term t1 = FP_create_integer(bt);
   return FP_unify(t, t1);
}

bool pl_foreign_peek_code(FP_term t)
{
   return pl_foreign_peek_byte(t);
}

bool pl_foreign_at_end_of_stream()
{
   //wcout << L"at_end_of_stream";
   if (pl_iostr.instream->eof()) {
      return true;
   } else {
      return false;
   };
};

bool pl_foreign_peek_char(FP_term t)
{
   if (!pl_iostr.instream->good()) return false;
   wchar_t ch = pl_iostr.instream->peek();
   wchar_t text[2];
   text[0] = ch;
   text[1] = 0;
   FP_atom a = FP_atom_from_wstring(text);
   FP_term t1 = FP_create_atom(a);
   return FP_unify(t, t1);
}

bool pl_foreign_skip(FP_term t)
{
   if (!FP_is_integer(t))
      return false;
   FP_int i1;
   FP_get_integer(t, &i1);
   while (pl_iostr.instream->good()) {
      
      wchar_t tk;
      pl_iostr.instream->read(&tk, 1);
      if (tk == i1) return true;
   }
   return true;
}

bool pl_foreign_functor(FP_term term, FP_term functor, FP_term arity)
{
   if (FP_is_variable(term)) {
      int ar;
      FP_atom atom;
      if (!FP_get_integer(arity, &ar)) return false;
      if (!FP_get_atom(functor, &atom)) return false;
      FP_term newterm = FP_create_structure(atom, ar);
      return FP_unify(term, newterm);
   } else {
      int ar;
      FP_atom atom;
      if (!FP_get_structure(term, &atom, &ar)) return false;
      FP_term term_arity = FP_create_integer(ar);
      FP_term term_functor = FP_create_atom(atom);
      return FP_unify(functor, term_functor) && FP_unify(arity, term_arity);
   }
}

bool pl_foreign_arg(FP_term arg, FP_term term, FP_term value)
{
   if (!FP_is_variable(arg)) {
      int a;
      if (!FP_get_integer(arg, &a)) return false;
      FP_term v;
      if (!FP_get_arg(term, a, &v)) return false;
      return FP_unify(v, value);
   } else {
      //Backtracking?
      return false;
   }
}

bool pl_foreign_between(FP_term low, FP_term high, FP_term value)
{
   
}

bool pl_foreign_succ(FP_term int1, FP_term int2)
{
   
}

bool pl_foreign_plus(FP_term int1, FP_term int2, FP_term int3)
{
   
}



bool pl_foreign_char_type(FP_term char_t, FP_term term)
{
   bool b1 = FP_is_variable(char_t);
   bool b2 = FP_is_variable(term);
   struct ForeignInfo {
      int count;
      wchar_t* name;
      wchar_t* region;
   };
#define CHAR_TYPES 25
   const ForeignInfo infos[CHAR_TYPES] = 
   {{4, L"alnum", L"azAZ09\300\377"},
   {3, L"alpha", L"azAZ\300\377"},
   {4, L"csym", L"azAZ09__"},
   {3, L"csymf", L"azAZ__"},
   {1,L"ascii", L"\0\177"},
   
   {2, L"white", L"  \t\t"},
   {1, L"cntrl", L"\0\37"},
   {1, L"digit", L"09"},
   {1, L"digit/1", L"09"},
   {3, L"xdigit/1", L"09afAF"},
   
   {1, L"graph", L"!~\240\377"},
   {2, L"lower", L"az\336\377"},
   {2, L"lower/1", L"az\336\377"},
   {1, L"to_lower/1", L"\0\377"},
   {2, L"upper", L"AZ\300\335"},
   
   {2, L"upper/1", L"AZ\300\335"},
   {1, L"to_upper/1", L"\0\377"},
   {7, L"punct", L"!/:@['{~\240\277\327\327\367\367"},
   {6, L"space", L"  \t\t\n\n\v\v\f\f\r\r"},
   {0, L"end_of_file", L"-1"},
   
   {1, L"end_of_line", L"\12\15"},
   {1, L"newline", L"\n\n"},
   {3, L"period", L"..!!??"},
   {3, L"quote", L"\"\"''``"}, 
   {3, L"paren/1", L"(([[{{"}};
   if (!b1 && !b2) {
      int character;
      FP_atom a;
      if (FP_is_integer(char_t)) {
	 FP_get_integer(char_t, &character);
      } else {
	 wchar_t ch;
	 if (!FP_get_char(char_t, &ch)) {
	    wcout << L"char_type/2: character erwartet";
	    return false;
	 };
	 character = ch;
      };
      int arity;
      if (FP_get_atom(term, &a)) {
	 const wchar_t* t = FP_wstring_from_atom(a);
	 for (int i = 0; i <CHAR_TYPES; i++) {
	    if (wcscmp(t, infos[i].name)==0) {
	       const wchar_t* region = infos[i].region;
	       int count = infos[i].count;
	       if (count == 0) {
		  if (character == -1) return true;
	       };
	       for (int j = 0; j < count; j++) {
		  if (region[j*2] <= character && character <= region[j*2+1]) {
		     return true;
		  }
	       };
	       return false;
	    };
	 };
	 return false;
      } else if (FP_get_structure(term, &a, &arity)) {
	 if (arity != 1) return false;
	 wstring name = FP_wstring_from_atom(a);
	 FP_term arg;
	 FP_get_arg(term, 0, &arg);
	 name += L"/1";
	 for (int i = 0; i <CHAR_TYPES; i++) {
	    if (wcscmp(name.c_str(), infos[i].name)==0) {
	       const wchar_t* region = infos[i].region;
	       int count = infos[i].count;
	       if (count == 0) {
		  if (character == -1) return true;
	       };
	       for (int j = 0; j < count; j++) {
		  if (region[j*2] <= character && character <= region[j*2+1]) {
		     switch (i) {
			case 8: {
			   return FP_unify(arg, FP_create_integer(character-'0'));
			   
			}; break;
			case 9: {
			   if (j == 0) {
			   return FP_unify(arg, FP_create_integer(character-'0'));
			   } else if (j == 1) {
			      return FP_unify(arg, FP_create_integer(character-'a'+10));
			   }  else {
			      return FP_unify(arg, FP_create_integer(character-'A'+10));
			   } 
			}; break;
			case 12: 
			   case 13:{
			   return FP_unify(arg, FP_create_char(toupper(character)));
			   
			   };break;
			case 15: 
			   case 16:{
			      return FP_unify(arg, FP_create_char(tolower(character)));
			   
			   };break;
			case 24:
			{
			   if (character == L'(') {
			      return FP_unify(arg, FP_create_char(L')'));
			   };
			   if (character == L'{') {
			      return FP_unify(arg, FP_create_char(L'}'));
			   };
			   if (character == L'[') {
			      return FP_unify(arg, FP_create_char(L']'));
			   };
			}; break;
		     };
		     return true;
		  }
	       };
	       return false;
	    };
	 };
	 return false;
      } else {
	 return false;
      };
   } else {
      wcout << L"Error kein Backtracking in char_type/2";
}
}

wstring atomtostr(FP_term a)
{
   if (FP_is_atom(a)) {
      FP_atom atom;
      FP_get_atom(a, &atom);
      return FP_wstring_from_atom(atom);
   } else if (FP_is_integer(a)) {
      FP_int it;
      FP_get_integer(a, &it);
      wchar_t cl[40];
      swprintf(cl, 40, L"%i", it);
      return cl;
   } else if (FP_is_real(a)) {
      FP_real it;
      FP_get_real(a, &it);
      float f = it;
      wchar_t cl[40];
      swprintf(cl, 40, L"%f", f);
      return cl;
   };
};

FP_term strtoatom(const wstring str) {
   int i;
   int i1 = swscanf(str.c_str(), L"%i", &i);
   if (i1 != 0) {
      return FP_create_integer(i);
   };
   float f;
   i1 = swscanf(str.c_str(), L"%f", &f);
   if (i1 != 0) {
      return FP_create_real(f);
   };

   return FP_create_atom(FP_atom_from_wstring(str.c_str()));
};

FP_term strtoatomf(const wstring &str) {

   return FP_create_atom(FP_atom_from_wstring(str.c_str()));
};

bool string_from_list(FP_term string, wstring &res)
{
   int count = FP_get_list_count(string);
   wchar_t* temp = new wchar_t[count+1];
   FP_term current = string;
   for (int i = 0; i < count; i++) {
      FP_term next;
      FP_term value;
      FP_get_list(current, &value, &next);
      if (!FP_is_integer(value)) {
	 return false;
      } else {
	 FP_int it;
	 FP_get_integer(value, &it);
	 temp[i] = it;
      };
      current = next;
   };
   temp[count] =0;
   res = temp;
   delete [] temp;
   return true;
};

bool string_from_list_char(FP_term string, wstring &res)
{
   int count = FP_get_list_count(string);
   wchar_t* temp = new wchar_t[count];
   FP_term current = string;
   for (int i = 0; i < count; i++) {
      FP_term next;
      FP_term value;
      FP_get_list(current, &value, &next);
      if (!FP_is_atom(value)) {
	 return false;
      } else {
	 wchar_t ch;
	 FP_get_char(value, &ch);
	 temp[i] = ch;
      };
      current = next;
   };
   res = temp;
   delete [] temp;
   return true;
};

bool pl_foreign_atom_codes(FP_term atom, FP_term string)
{
   if (!FP_is_variable(atom)) {
      if (!FP_is_atomic(atom)) {
	 wcout << L"Error: atom_codes erwartet atom\n";
	 return false;
      }
      wstring w = atomtostr(atom);
      return FP_unify(string, FP_create_list_from_wstring(w.length(), w.c_str()));
   } else if (FP_is_empty_list(string)) {
      return FP_unify(atom, FP_create_atom(FP_atom_from_wstring(L"")));
   } else if (FP_is_list(string)) {
      wstring str;
      if (!string_from_list(string, str)) {
	 return false;
      };
      return FP_unify(atom, strtoatom(str));
   } else {
      wcout << L"Error: atom_codes erwartet mindestens 1 Argument\n";
      return false;
   };
   return true;
}

bool pl_foreign_atom_chars(FP_term atom, FP_term chars)
{
   if (!FP_is_variable(atom)) {
      if (!FP_is_atomic(atom)) {
	 wcout << L"Error: atom_chars erwartet atom\n";
	 return false;
      }
      wstring w = atomtostr(atom);
      return FP_unify(chars, FP_create_list_from_wstring_char(w.length(), w.c_str()));
   } else if (FP_is_empty_list(chars)) {
      return FP_unify(atom, FP_create_atom(FP_atom_from_wstring(L"")));
   } else if (FP_is_list(chars)) {
      wstring str;
      if (!string_from_list_char(chars, str)) {
	 return false;
      };
      return FP_unify(atom, strtoatom(str));
   } else {
      wcout << L"Error: atom_chars erwartet mindestens 1 Argument\n";
      return false;
   };
   return true;
}

bool pl_foreign_char_code(FP_term atom, FP_term code)
{
   int i;
   if (!FP_is_variable(atom)) {
      wchar_t ch;
      if (FP_get_char(atom, &ch)) {
	 return FP_unify(code, FP_create_integer(ch));
      } else {
	 wcout << L"Error: char_code erwartet ein Atom\n";
	 return false;
      };
   } else if (FP_get_integer(code, &i)) {
      return FP_unify(code, FP_create_char(i));
   } else {
      wcout << L"Error: char_code ungültige Argumente\n";
   };
   return false;
}

bool pl_foreign_number_chars(FP_term number, FP_term char_list)
{
   if (!FP_is_variable(number)) {
      if (!FP_is_integer(number)) return false;
      return pl_foreign_atom_chars(number, char_list);
   } else {
      if (!pl_foreign_atom_chars(number, char_list)) return false;      
      if (!FP_is_integer(number)) return false;
      return true;
   };
}

bool pl_foreign_number_codes(FP_term number, FP_term code_list)
{
   if (!FP_is_variable(number)) {
      if (!FP_is_integer(number)) return false;
      return pl_foreign_atom_codes(number, code_list);
   } else {
      if (!pl_foreign_atom_codes(number, code_list)) return false;      
      if (!FP_is_integer(number)) return false;
      return true;
   };
}

bool pl_foreign_atom_number(FP_term atom, FP_term number)
{
   int i;
   FP_atom a;
   if (!FP_is_variable(number)) {
      if (!FP_is_integer(number)) {
	 wcout << L"Error: atom_number erwartet Zahl\n";
	 return false;
      } 
      wstring w = atomtostr(number);
      return FP_unify(atom, FP_create_atom(FP_atom_from_wstring(w.c_str())));
   } else if (FP_get_atom(atom, &a)) {
      
      wstring str = FP_wstring_from_atom(a);
      int i1 = swscanf(str.c_str(), L"%i", &i);
      if (i1 != 0) {
	 return FP_unify(number, FP_create_integer(i));
      };
      wcout << L"Error: atom_number erwartet als Atom eine Zahl\n";
      return false;
   };
   return false;
}

bool pl_foreign_name(FP_term atomorint, FP_term string)
{
   return pl_foreign_atom_codes(atomorint, string);
}

bool pl_foreign_term_to_atom(FP_term term, FP_term atom)
{
   return false;
}

bool pl_foreign_atom_to_term(FP_term atom, FP_term term, FP_term binding)
{
   return false;
}

bool pl_foreign_atom_concat(FP_term atom1, FP_term atom2, FP_term atom3)
{
   if (FP_is_atomic(atom1) && FP_is_atomic(atom2)) {
      wstring s1 = atomtostr(atom1);
      wstring s2 = atomtostr(atom2);
      s1 += s2;
      return FP_unify(atom3, strtoatomf(s1));
   } else if (FP_is_atomic(atom1) && FP_is_atomic(atom3)) {
      wstring s1 = atomtostr(atom1);
      wstring s2 = atomtostr(atom3);
      wstring start = s2.substr(s1.length());
      if (start != s1) return false;
      s2.erase(s1.length());
     
      return FP_unify(atom2, strtoatomf(s2));
   } else if (FP_is_atomic(atom2) && FP_is_atomic(atom3)) {
      wstring s1 = atomtostr(atom2);
      wstring s2 = atomtostr(atom3);
      wstring start = s2.substr(s1.length(), s2.length()-s1.length());
      if (start != s1) return false;
      s2.erase(s1.length(), s2.length()-s1.length());
     
      return FP_unify(atom1, strtoatomf(s1));
   }
   return false;
}

bool pl_foreign_concat_atom2(FP_term list, FP_term atom)
{
   return false;
}

bool pl_foreign_concat_atom3(FP_term list, FP_term seperator, FP_term atom)
{
   return false;
}

bool pl_foreign_atom_length(FP_term atom, FP_term length)
{
   if (!FP_is_atomic(atom)) {
      wcout << L"atom_length: atom erwartet";
      return false;
   }
   wstring s1 = atomtostr(atom);
   return FP_unify(length, FP_create_integer(s1.length()));
}

bool pl_foreign_atom_prefix(FP_term atom, FP_term prefix)
{
   wstring s1 = atomtostr(atom);
   wstring s2 = atomtostr(prefix);
   wstring start = s1.substr(s2.length());
   if (start != s2) return false;
   return true;
}

bool pl_foreign_sub_atom(FP_term atom, FP_term before, FP_term len, FP_term after, FP_term sub)
{return false;
   
}


bool pl_foreign_asserta(FP_term t1)
{
   FP_DATABASE db = FP_dyn_getDatabase(t1);
   if (db == NULL) return false;
   FP_dyn_addfirst(db, t1);
   return true;
}

bool pl_foreign_assertz(FP_term t1)
{
   FP_DATABASE db = FP_dyn_getDatabase(t1);
   if (db == NULL) return false;
   FP_dyn_addlast(db, t1);
   return true;
}

bool pl_foreign_assert2a(FP_term t1, FP_term t2)
{
   return true;
}

bool pl_foreign_assert2z(FP_term t1, FP_term t2)
{
   return true;
}

bool pl_foreign_retract2(FP_term t1, FP_term t2)
{
   return true;
}

bool pl_foreign_retract(FP_term t1)
{
   FP_DATABASE db = FP_dyn_getDatabase(t1);
   if (db == NULL) return false;
   FP_dyn_retract(db, t1);
   return true;
}

bool pl_foreign_retractall(FP_term t1)
{
   FP_DATABASE db = FP_dyn_getDatabase(t1);
   if (db == NULL) return false;
   FP_dyn_retractall(db, t1);
   return true;
}

bool pl_foreign_abolish(FP_term t1, FP_term t2)
{
   FP_atom atom;
   int arity;
   if (!FP_get_atom(t1, &atom) || !FP_get_integer(t2, &arity)) {
      return false;
   };
   FP_DATABASE db = FP_dyn_getDatabase(atom, arity);
   FP_dyn_clear(db);
   return true;
}

bool pl_foreign_equal(FP_term t1, FP_term t2)
{
   return FP_unify(t1, t2);
}

bool pl_foreign_nonequal(FP_term t1, FP_term t2)
{
   return !FP_testunify(t1, t2);
}

bool pl_foreign_is(FP_term t1, FP_term t2)
{
   return FP_math_is(t1, t2);
}

bool pl_foreign_arithequal(FP_term t1, FP_term t2)
{
   return FP_math_equal(t1, t2);
}

bool pl_foreign_arithnonequal(FP_term t1, FP_term t2)
{
   return FP_math_nonequal(t1, t2);
}

bool pl_foreign_arithless(FP_term t1, FP_term t2)
{
   return FP_math_less(t1, t2);
}

bool pl_foreign_aritheqless(FP_term t1, FP_term t2)
{
   return FP_math_eqless(t1, t2);
}

bool pl_foreign_arithgreater(FP_term t1, FP_term t2)
{
   return FP_math_greater(t1, t2);
}

bool pl_foreign_aritheqgreater(FP_term t1, FP_term t2)
{
   return FP_math_eqgreater(t1, t2);
}

bool pl_foreign_fail()
{
   return false;
}

bool pl_foreign_true()
{
   return true;
}


bool pl_foreign_instequal(FP_term t1, FP_term t2)
{
   return FP_compare(t1, t2) == 0;
}

bool pl_foreign_instnonequal(FP_term t1, FP_term t2)
{
   return FP_compare(t1, t2) != 0;
}

bool pl_foreign_instless(FP_term t1, FP_term t2)
{
   return FP_compare(t1, t2) < 0;
}

bool pl_foreign_insteqless(FP_term t1, FP_term t2)
{
   return FP_compare(t1, t2) <= 0;
}

bool pl_foreign_instgreater(FP_term t1, FP_term t2)
{
   return FP_compare(t1, t2) > 0;
}

bool pl_foreign_insteqgreater(FP_term t1, FP_term t2)
{
   return FP_compare(t1, t2) < 0;
}


bool pl_foreign_bye()
{
   exit(0);
   return true;
}

bool pl_foreign_halt()
{
   exit(0);
   return true;
}

bool pl_foreign_repeat()
{
   /// @todo Implement me
   return true;
}



