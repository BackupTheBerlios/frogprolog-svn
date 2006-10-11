/***************************************************************************
 *   Copyright (C) 2005 by Michael Staud   *
 *   staud@linux   *
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
#include "identifierdatabase.h"
#include <iostream>

//#include <assert.h>

namespace UtiProlog
{

  IdentifierDatabase idbase;

  IdentifierDatabase::IdentifierDatabase()
  {
    currentid = 0;
    /*transform[L"catch"] = L"plr_catch";
    transform[L"try"] = L"plr_try";
    transform[L"while"] = L"plr_while";
    transform[L"do"] = L"plr_do";
    transform[L"void"] = L"plr_void";
    transform[L"int"] = L"plr_int";
    transform[L"float"] = L"plr_float";
    transform[L"double"] = L"plr_double";
    transform[L"catch"] = L"plr_catch";*/
  }


  IdentifierDatabase::~IdentifierDatabase()
  {}

  void IdentifierDatabase::debugPrint()
  {
    for (map<PID, CUtiString>::iterator i = IDtoident.begin(); i != IDtoident.end(); i++)
    {
      wcout << i->first << L": " << i->second.c_str() << endl;
    };
  }
  PID IdentifierDatabase::getVoid()
  {
     return identifierToID(L"_");
  }
  
  PID IdentifierDatabase::identifierToID(const CUtiString &str, bool foreign)
  {
    map<CUtiString, PID>::iterator it = identtoID.find(str);
    if (it != identtoID.end())
    {
       if (foreign) Names[it->second].foreign = true;
      return it->second;
    }
    else
    {
      identtoID[str] = currentid;
      IDtoident[currentid] = str;
      int id = currentid;
      IdentID idid;
      idid.name = str;
      idid.foreign = foreign;
      Names.push_back(idid);
      currentid++;
      registerValue(str, id);
      return id;
    };
  };

  PID IdentifierDatabase::identifierToID(const char* c)
  {
    CUtiString k;
    k.LoadAnsi(c);
    return identifierToID(k);
  }

  CUtiString IdentifierDatabase::idToIdentifier(PID ID)
  {
    map<PID, CUtiString>::iterator it = IDtoident.find(ID);
    if (it != IDtoident.end())
    {
      return it->second;
    }
    else
    {
//      assert(false);
      return L"error";
    };
  }
  CUtiString IdentifierDatabase::idToIdentifierIdent(PID ID)
  {
     map<PID, CUtiString>::iterator it = IDtoident.find(ID);
     if (it != IDtoident.end())
     {
	CUtiString source = it->second;
	CUtiString res_source=L"";
	for (int i = 0; i < source.getlength(); i++) {
	   wchar_t t = source[i];
	   switch (t) {
	      case '\\': 
		 res_source += L"\\\\";
		 break;
	      case '\'':
		 res_source += L"\\'";
		    break;
	      case '\"':
		 res_source += L"\\\"";
		 break;
	      case '\n':
		 res_source += L"\\n";
		 break;
	      default:
		 res_source += t;
	   };
	};
	return res_source;
     }
     else
     {
//	assert(false);
	return L"error";
     };
  }
  CUtiString IdentifierDatabase::idToIdentifierCode(PID ID)
  {
    map<PID, CUtiString>::iterator it = IDtoidentCode.find(ID);
    if (it != IDtoidentCode.end())
    {
      return it->second;
    }
    else
    {
//      assert(false);
      return L"Interner Error";
    };
  }

  void IdentifierDatabase::registerValue(const CUtiString &str, PID id)
  {
    CUtiString s = str;
    map<CUtiString, CUtiString>::iterator it = transform.find(str);
    if (it != transform.end()) s = it->second;
    
    if (s.getlength() >= 3 && s[0] == L'p' && s[1] == L'l' && s[2] == L'_')
    {
      s = L"plr_"+s;
    }
    else if (s.getlength() >= 4 && s[0] == L'p' && s[1] == L'l' && s[2] == L's' && s[3] == L'_')
    {
      s = L"plr_"+s;
    } else {
       s = L"plr_"+s;
    };
    CUtiString newstr;
    for (int i = 0; i < s.getlength(); i++)
    {
      wchar_t ch = s[i];
      if ((ch >= L'a' && ch <= L'z') ||
          (ch >= L'A' && ch <= L'Z') ||
          (ch >= L'0' && ch <= L'9') ||
          (ch == L'_'))
      {
	 newstr += ch;
      } else {
	 switch (ch) {
	    case L'+':
	    {
	       newstr += L"_plus";
	    }; break;
	    case L'-':
	    {
	       newstr += L"_minus";
	    }; break;
	    case L'*':
	    {
	       newstr += L"_multiply";
	    }; break;
	    case L'/':
	    {
	       newstr += L"_divide";
	    }; break;
	    case L'\\':
	    {
	       newstr += L"_backslash";
	    }; break;
	    case L'^':
	    {
	       newstr += L"_potence";
	    }; break;
	    case L'<':
	    {
	       newstr += L"_less";
	    }; break;
	    case L'>':
	    {
	       newstr += L"_greater";
	    }; break;
	    case L'=':
	    {
	       newstr += L"_equal";
	    }; break;
	    case L'~':
	    {
	       newstr += L"_tilde";
	    }; break;
	    case L':':
	    {
	       newstr += L"_colon";
	    }; break;
	    case L'.':
	    {
	       newstr += L"_dot";
	    }; break;
	    case L'?':
	    {
	       newstr += L"_question";
	    }; break;
	    case L'@':
	    {
	       newstr += L"_addsymbol";
	    }; break;
	    case L'#':
	    {
	       newstr += L"_rhomb";
	    }; break;
	    case L'$':
	    {
	       newstr += L"_dollar";
	    }; break;
	    case L'&':
	    {
	       newstr += L"_and";
	    }; break;
	    case L'!':
	    {
	       newstr += L"_cut";
	    }; break;
	    case L';':
	    {
	       newstr += L"_dashdot";
	    }; break;
	    case L'{':
	    {
	       newstr += L"_brace";
	    }; break;
	    case L'}':
	    {
	       newstr += L"_braceend";
	    }; break;
	    case L'[':
	    {
	       newstr += L"_bracket";
	    }; break;
	    case L']':
	    {
	       newstr += L"_bracketend";
	    }; break;
	 };
      }
      ;
    };
    CUtiString teststr;
    if (newstr.getlength() > 60) {
       newstr.Copy(&teststr, 0, 60);
    } else {
       teststr = newstr;
    }
    
    int i = 0;
    while (identtoIDCode.find(teststr) != identtoIDCode.end()) {
       teststr = newstr;
       teststr += i;
       i++;
    };
    identtoIDCode[teststr] = id;
    IDtoidentCode[id] = teststr;
  }

  void IdentifierDatabase::clearDatabase()
  {
    currentid = 0;
    identtoID.clear();
    IDtoident.clear();
    identtoIDCode.clear();
    IDtoidentCode.clear();
  }


}
