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
#include "UtiString.h"
#include "UtiArchiv.h"
#include <iostream>
#include <fstream>

#include <string.h>
#include <stdio.h>
#ifdef _WIN32
#include <objbase.h>
#endif
#include "utisystem.h"
#include <string>

using namespace std;
using namespace UtiFramework;

std::wostream & operator<<(std::wostream & os, const CUtiString & str) 
{
   os << str.c_str();
   return os;
};


const CUtiString RandomString(TCHAR* start, int l, int h, TCHAR* ende)
{
    CUtiString s;
    s = start;
    int r = l+urandom(h-l+1);
    s += r;
    s += ende;
    return s;
}

const CUtiString CalcNumberedFileName(TCHAR* start, TCHAR* ende)
{
    CUtiString res;
    int k= 0;
    do
    {
        res = start;
        res += k;
        res += ende;
        k++;
    }
    while (FileExists(res.getString()));
    return res;
}

CUtiString CUtiString::operator()(unsigned int p, unsigned int l) const
{
    CUtiString tmp = UTEXT("");
    tmp.insert(0, l, string+p);
    return(tmp);
}

bool IsInteger(U_CHAR *str, int length)
{
    for (int i = 0; i < length; i++)
    {
        if (IsCharacter(str[i]))
        {
            if (!IsNumber(str[i]))
            {
                return(false);

            };
        };
    };
    return(true);
};

int SearchChar(U_CHAR *str, U_CHAR c, int length)
{
    int res = -1;
    for (int i = 0; i < (int)length; i++)
    {
        if (str[i] == c)
        {
            res = i;
            return(res);
        };
    };
    return(res);
}

int SearchCharBackward(U_CHAR *str, U_CHAR c, int length)
{
    int res = -1;
    for (int i = length-1; i >= 0; i--)
    {
        if (str[i] == c)
        {
            res = i;
            return(res);
        };
    };
    return(res);
}


bool IsEqual(U_CHAR* str, U_CHAR* item, int length)
{
    for (int i = 0; i < length; i++)
    {
        if (toupper(str[i]) != toupper(item[i]))
        {
            return(false);
        };
    };
    return(true);
};


bool ValidBez(U_CHAR* str, int i, int length, int searchlength)
{
    if (i != 0)
    {
        if (IsBezeichner(str[i-1]))
        {
            return(false);
        };
    };
    if (i+searchlength < length)
    {
        if (IsBezeichner(str[i+searchlength]))
        {
            return(false);
        };
    };
    return(true);
};

bool ValidVergleich(U_CHAR* str, int i, int length, int searchlength)
{
    if (i != 0)
    {
        if (IsVergleich(str[i-1]))
        {
            return(false);
        };
    };
    if (i+searchlength < length)
    {
        if (IsVergleich(str[i+searchlength]))
        {
            return(false);
        };
    };
    return(true);
};

int SearchString(U_CHAR *str, U_CHAR* c, int length, int searchlength)
{
    int res = -1;
    int i = 0;
    for (i = 0; i < (int)length-(int)searchlength; i++)
    {
        //if (!ValidBez(str, i, length, searchlength)) continue;
        if (IsEqual(&str[i], c, searchlength))
        {
            res = i;
            return(res);
        };
    };
    return(res);
}

#define IsBez(a) if ((i+(int)wcslen(a)-1 < (int)length) && IsEqual(&str[i], a, wcslen(a)) && ValidBez(str, i, length, wcslen(a)))

void SearchBeginEnd(U_CHAR*str, int length, int &beginpos, int &endpos, bool last)
{
    beginpos = -1;
    endpos = -1;
    int i = 0;
    int level = 0;
    int searchlength = 3;
    for (i = 0; i < (int)length; i++)
    {
        IsBez(UTEXT("begin"))
        {
            if (level == 0)
                beginpos = i;
            level++;
        }
        IsBez(UTEXT("record"))
        {
            if (level == 0)
                beginpos = -1;
            level++;
        };
        IsBez(UTEXT("class"))
        {
            if (level == 0)
                beginpos = -1;
            level++;
        };
        IsBez(UTEXT("case"))
        {
            if (level == 0)
                beginpos = -1;
            level++;
        };
        IsBez(UTEXT("object"))
        {
            if (level == 0)
                beginpos = -1;
            level++;
        };
        IsBez(UTEXT("end"))
        {
            level--;
            if ((level == 0) && (beginpos != -1))
            {
                endpos = i;
                if (!last)
                    return;
            };
        };

    };
};

int SearchStringBackward(U_CHAR *str, U_CHAR* c, int length, int searchlength)
{
    int res = -1;
    int i = 0;

    for (i = 0; i < (int)(length-searchlength); i++)
    {
        //if (!ValidBez(str, i, length, searchlength)) continue;
        if (IsEqual(&str[i], c, searchlength))
        {
            res = i;
        };
    };
    return(res);
}



void SearchStrings(U_CHAR* str, U_CHAR*c, int length, int searchlength, int* result, int &rescount)
{
    int i = 0;
    rescount = 0;
    int level = 0;
    for (i = 0; i < (int)length-searchlength; i++)
    {
        if (str[i] == UTEXT('('))
        {
            level = level + 1;
            continue;
        };
        if (str[i] == UTEXT(')'))
        {
            level = level - 1;
            //if (level < 0) DEBUG(UTEXT("SearchStrings: Zu viele geschlossene Klammern."));
            continue;
        };
        if (level != 0)
            continue;
        if (IsBezeichner(c[0])) //nur wenn der Suchstring selbst ein Bezeichner ist
            if (!ValidBez(str, i, length, searchlength))
                continue;
        if (IsVergleich(c[0]))
        {
            if (!ValidVergleich(str, i, length, searchlength))
                continue;
        };
        if (IsEqual(&str[i], c, searchlength))
        {
            if (rescount < MAX_ITEMS)
            {
                result[rescount] = i;
                rescount++;

            }
            else
            {
                //DEBUG(UTEXT("SearchStrings: Zu Viele Items"));
            };
        };
    };
}

int SearchStringBez(U_CHAR *str, U_CHAR* c, int length, int searchlength)
{
    int res = -1;
    int i = 0;
    int j = 0;

    if (length < searchlength)
        return(-1);
    for (i = 0; i < (int)(length-searchlength+2); i++)
    {
        //if (!ValidBez(str, i, length, searchlength)) continue;
        //if (IsEqual(&str[i], c, searchlength)) {
        //  res = i;
        //  return(res);
        //};
        IsBez(c)
        {
            res = i;
            return(res);
        };
    };
    return(res);
}

int SearchStringBackwardBez(U_CHAR *str, U_CHAR* c, int length, int searchlength)
{
    int res = -1;
    int i = 0;
    int j = 0;

    for (i = 0; i < (int)(length-searchlength); i++)
    {
        if (!ValidBez(str, i, length, searchlength))
            continue;
        if (IsEqual(&str[i], c, searchlength))
        {
            res = i;
        };
    };
    return(res);
}

int SearchChar(U_CHAR *str, U_CHAR c, int length, int charpos)
{
    int res = -1;
    for (int i = 0; i < (int)length; i++)
    {
        if (str[i] == c)
        {
            charpos--;
            if (charpos == 0)
            {
                res = i;
                return(res);
            };
        };
    };
    if (charpos == 1)
    { //Bei vorletztem, l�ge setzen
        res = length;
    };
    return(res);
}



void CUtiString::replace(const U_CHAR *s)
{
    int newlength = (int)wcslen(s);
    if (string != NULL && buffersize > newlength+1 && buffersize/2 < newlength+1)
    {
        length = newlength;
        for (int i = 0; i < length; i++)
        {
            string[i] = s[i];
        }
        string[length] = 0;
    }
    else
    {
        if (string != NULL)
            delete[](string);
        string = NULL;

        length = newlength;
        buffersize = calcbuffersize(length);
        string = new U_CHAR[buffersize];
        if (string == NULL)
        {
            // throw (CUtiString::EStringAllocateFailure());
        }
        wcscpy(string, s);
    };
}

CUtiString::CUtiString() : CUtiOB()
{
#ifdef EDITOR
    parent= NULL;
#endif

    string = NULL;

    length = 0;
    buffersize = 0;
    // typinfo = UTI_STRING;
    *this = UTEXT("");
}

CUtiString::CUtiString(const U_CHAR *c) : CUtiOB()
{
    string = NULL;
#ifdef EDITOR

    parent= NULL;
#endif

    this->replace(c);
    //  typinfo = UTI_STRING;
}

void CUtiString::ReadProp(TCHAR* name, CUtiString* result, TCHAR* defaultitem)
{
    CUtiString str;

    int c = getLineCount();
    int l = wcslen(name);
    int j;
    for (int i=0; i < c; i++)
    {
        getLine(i, &str);
        int p = str.Pos(UTEXT(":"));
        if (p != -1)
        {
            if (l != p)
                continue;
            bool b = true;
            for (j = 0; j < p; j++)
            {
                if (str[j] != name[j])
                {
                    b = false;
                    break;
                };

            };
            //str.Copy(&Name, 0, i);

            //if (wcscmp(Name.getString(),name) == 0) {
            if (b)
            {
                str.Copy(result, p+1, str.getlength()-p-1);
                return;
            };
            //};
        };
    };
    *result = defaultitem;
};


CUtiString::CUtiString(const U_CHAR c) : CUtiOB()
{
    string = NULL;
    U_CHAR s[2];
    s[0] = c;
    s[1] = 0;
    replace(s);
#ifdef EDITOR

    parent= NULL;
#endif
    //	typinfo = UTI_STRING;
}

CUtiString::CUtiString(const CUtiString &s) : CUtiOB()
{
    string = NULL;

    replace(s.string);
#ifdef EDITOR

    parent= NULL;
#endif
    //	typinfo = UTI_STRING;
}

CUtiString::~CUtiString()
{
    if (string != NULL)
        delete[](string);
}

void CUtiString::ReplaceChar(TCHAR oldchar,TCHAR newchar)
{
    for (int i = 0; i < getlength(); i++)
    {
        TCHAR k=(*this)[i];
        if (k == oldchar)
            (*this)[i] = newchar;

    }
}

void CUtiString::getLine(int line, CUtiString *str)
{
    //*str = UTEXT("");
    int i=0;
    while (line != 0 && string[i] != 0)
    {
        if (string[i] == 13 || string[i] == 10)
        {
            line--;
            i++;
            if (string[i] == 10)
                i++;
        }
        else
        {
            i++;
        };

    }
    if (string[i] == 0)
    {
		*str = L"";
        return;
    };
    int start = i;
    while (string[i] != 13 && string[i] != 10 && string[i] != 0)
    {
        //  *str += string[i];
        i++;
    }
    ;
    int ende = i;
    Copy(str, start, ende-start);
}

int CUtiString::getLineCount()
{
    int i=0;
    int line = 1;
    if (*this == UTEXT(""))
        return(0);
    while (line != 0 && string[i] != 0)
    {
        if (string[i] == 13)
        {
            line++;

        };
        i++;
    }
    //line++;
    return(line);

}

int CUtiString::Pos(U_CHAR* substr)
{
    int l = wcslen(substr);
    if (l == 1)
    {
        for (int i = 0; i < (int)length; i++)
        {
            if (string[i] == substr[0])
            {
                return(i);
            };
        }
    }
    else
    {
        for (int i = 0; i < (int)length-l+1; i++)
        {
            if (wcsncmp(&string[i], substr, l)==0)
            {
                return(i);
            };
        }
    };
    return(-1);
}

int CUtiString::Pos(int start, U_CHAR* substr)
{
    int l = wcslen(substr);
    if (l == 1)
    {
        for (int i = start; i < (int)length; i++)
        {
            if (string[i] == substr[0])
            {
                return(i);
            };
        }
    }
    else
    {
        for (int i = start; i < (int)length-l+1; i++)
        {
            if (wcsncmp(&string[i], substr, l)==0)
            {
                return(i);
            };
        }
    }
    return(-1);
}

int CUtiString::LastDelimiter(U_CHAR* substr)
{
    int l = wcslen(substr);
    int lastpos = length;
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < l; j++)
        {
            if (string[i] == substr[j])
            {
                lastpos = i;
            }
        };
    };
    return lastpos;
}

void CUtiString::Copy(CUtiString* target, int start, int length)
{
    //*target = UTEXT("");
    int end = start+length;
    if (end >= (int)wcslen(string))
        end = (int)wcslen(string);

    if (target->string != NULL)
        delete[](target->string);
    target->string = NULL;

    target->length = end-start;
    target->buffersize = INCBUFFER+target->length+1;
    target->string = new(U_CHAR[target->buffersize]);
    if (target->string == NULL)
    {
        // throw (CUtiString::EStringAllocateFailure());
    }

    for (int i= start; i < end; i++)
    {
        target->string[i-start] = string[i];
    };
    target->string[end-start] = 0;
}

void CUtiString::Delete(int index, int length)
{
    U_CHAR* c = new U_CHAR[getlength()+1];
    int l = 0;
    for (int i = 0; i < index; i++)
    {
        c[l] = string[i];
        l++;
    };
    int l2 = getlength();
    for (int i = index+length; i < l2; i++)
    {
        c[l] = string[i];
        l++;
    };
    c[l] = 0;
    *this = c;
}


HResult CUtiString::Read(CStream & Stream, int Flags, int version)
{
    int i;
    Stream.ReadInteger(i);
    char* c = new char[i+1];
    Stream.ReadData(c, (i+1)*sizeof(char));
    //replace(c);
    LoadAnsi(c);
    delete [] c;
    return(UTI_OK);
}

HResult CUtiString::Write(CStream & Stream, int Flags, int version)
{
    Stream.WriteInteger(length);
    Stream.WriteData(string, length+1);
    return(UTI_OK);
}

CUtiString& CUtiString::operator =(const CUtiString &s)
{
    if (this == &s)
        return(*this);
    replace(s.string);
    return(*this);
}

U_CHAR& CUtiString::operator[](unsigned int p)
{
    utiassert(p>=0 && p<=getlength());
    return(string[p]);
}

const U_CHAR& CUtiString::operator[](unsigned int p) const
{
    utiassert((p>=0) && (p<=length));
    return(string[p]);
}

CUtiString& CUtiString::operator =(const U_CHAR *s)
{
    if (s == NULL)
        return(*this);
    replace(s);
    return(*this);
}

CUtiString& CUtiString::operator =(const U_CHAR c)
{
    U_CHAR s[2];
    s[0] = c;
    s[1] = 0;
    replace(s);
    return(*this);
}

CUtiString& CUtiString::operator =(int i)
{
    U_CHAR s[40];
    swprintf(s, 40, UTEXT("%i"), i);

    replace(s);
    return(*this);
}

CUtiString& CUtiString::operator =(float i)
{
    U_CHAR s[40];
    swprintf(s, 40,UTEXT("%.f"), i);

    replace(s);
    return(*this);
}




CUtiString& CUtiString::operator+=(const CUtiString &s)
{
    insert(length, wcslen(s.string), s.string);
    return(*this);
}

CUtiString& CUtiString::operator+=(const U_CHAR *s)
{
    insert(length, wcslen(s), s);
    return(*this);
}

CUtiString& CUtiString::operator+=(const U_CHAR c)
{
    insert(length, 1, &c);
    return(*this);
}

CUtiString& CUtiString::operator+=(const int i)
{
    U_CHAR s[40];
    swprintf(s, 40,UTEXT("%i"), i);
    insert(length, wcslen(s), s);
    return(*this);
}

CUtiString& CUtiString::operator+=(const float i)
{
    U_CHAR s[40];
    swprintf(s, 40,UTEXT("%f"), i);
    insert(length, wcslen(s), s);
    return(*this);
}


const CUtiString CUtiString::operator+(const U_CHAR *s) const
{
    CUtiString temp = string;
    temp.insert(length, wcslen(s), s);
    return(temp);
}

const CUtiString CUtiString::operator+(const U_CHAR c) const
{
    CUtiString temp = string;
    temp.insert(length, 1, &c);
    return(temp);
}

const CUtiString CUtiString::operator+(const int i) const
{
    CUtiString temp = string;
    U_CHAR s[40];
    swprintf(s,40, UTEXT("%i"), i);

    temp.insert(length, wcslen(s), s);
    return(temp);
}

void CUtiString::DecLength(int i)
{
    if (length-i >= 0)
    {
        string[length-i] = 0;
        length -= i;
    };
};


const CUtiString CUtiString::operator+(const float i) const
{
    CUtiString temp = string;
    U_CHAR s[40];
    swprintf(s,40, UTEXT("%.f"), i);

    temp.insert(length, wcslen(s), s);
    return(temp);
}

int CUtiString::calcbuffersize(int len)
{
    int minlen = len+1;
    int k = 4;
    for (int i = 0; i < 20;i++)
    {
        if (minlen <= k)
            return k;
        k *= 2;

    }
    /*if (minlen <= 4) return 4;
    if (minlen <= 8) return 8;
    if (minlen <= 16) return 16;
    if (minlen <= 32) return 32;
    if (minlen <= 64) return 64;*/
    return len+1+15;
}


void CUtiString::insert(unsigned int pos, unsigned int slen, const TCHAR *s)
{
    if (string == NULL)
    {
        length = slen;
        buffersize=calcbuffersize(length);
        string = new(U_CHAR[buffersize]);
        if (string == NULL)
        {
            //throw (CUtiString::EStringAllocateFailure());
        }
        wcscpy(string, s);
    }
    else
    {
        int newlength = length+slen+1;
        if (buffersize > newlength && buffersize / 2 < newlength)
        {
            for (int i = 0; i < length-pos; i++)
            {
                string[pos+slen+i] = string[pos+i];
            };
            for (int i = 0; i < slen; i++)
            {

                string[pos+i] = s[i];
            };
            length = length + slen;
            string[length] = 0;

        }
        else
        {

            buffersize = calcbuffersize(length+slen);
            U_CHAR *sptr = new(U_CHAR[buffersize]);
            if (sptr == NULL)
            {
                //throw (CUtiString::EStringAllocateFailure());
            }
            unsigned int y=0;
            unsigned int x=0;

            for (x=0; x<pos; x++)
            {
                sptr[y++] = string[x];
            }
            for (x=0;x <slen; x++)
            {
                sptr[y++] = s[x];
            }
            for (x=pos; x <= length;x++)
            {
                sptr[y++] = string[x];
            }

            length = length + slen;
            sptr[length] = 0;
            delete[] string;
            string = sptr;
        }
    }
    /*#ifdef EDITOR
    	bool b;
    	if (parent) parent->GetMessageUti(this, OnChange, 0, 0, b);
    #endif*/
}

/*void CUtiString::ReadProp(char* name, CUtiString* result)
{
   CUtiString str;
   CUtiString Name;
   CUtiString inhalt;
   int c = getLineCount();
   for (int i=0; i < c; i++) {
	  getLine(i, &str);
	  int i = str.Pos(UTEXT(":"));
	  if (i != -1) {
		 str.Copy(&Name, 0, i);
		 if (wcscmp(Name.getString(),name) == 0) {
			 str.Copy(result, i+1, str.getlength()-i-1);
		 };
	  };
   };
};*/

U_CHAR* CUtiString::getString() const
{
    return(string);
}

U_CHAR* CUtiString::c_str() const
{
    return(string);
}

void CUtiString::IntToStr(int i, U_CHAR *str)
{
    swprintf(str, 40,UTEXT("%i"), i);
    //_itoa(i, str, 10);
}

void CUtiString::IntToStr(int i)
{
    U_CHAR buffer[40];
    swprintf(buffer,40, UTEXT("%i"), i);
    replace(buffer);

}

void CUtiString::FloatToStr(const float i)
{
    U_CHAR buffer[40];
    swprintf(buffer, 40,UTEXT("%f"), i);
    replace(buffer);

}

void CUtiString::ExtractRealFileName()
{
    ExtractFileName();
    int i = Pos(UTEXT("."));
    CUtiString s;
    Copy(&s, 0, i);
    *this = s;
}

void CUtiString::ExtractFileName()
{
    int i = LastDelimiter(UTEXT("\\:/"));
    if (Pos(UTEXT("\\")) == -1 && Pos(UTEXT(":")) == -1 && Pos(UTEXT("/")) == -1)
        return;
    CUtiString s;
    Copy(&s, i+1, 100000);
    *this = s;
}

void CUtiString::ExtractFileExt()
{
    ExtractFileName();
    int i = Pos(UTEXT("."));
    CUtiString s;
    Copy(&s, i+1, 1000000);
    *this = s;
}

void CUtiString::ExtractFilePath()
{
    int i = LastDelimiter(UTEXT("\\:/"));
    if (i == length)
    {
        *this = UTEXT("");
    }
    else
    {
        CUtiString s;
        Copy(&s, 0, i);
        *this = s;
    }
}

const CUtiString CUtiString::LowerCase()
{
   CUtiString s = *this;
   s.ToLowerCase();
   return s;
}

const CUtiString CUtiString::UpperCase()
{
   CUtiString s = *this;
   s.ToUpperCase();
   return s;
}
void CUtiString::ToLowerCase()
{
   for (int i = 0; i < length; i++) {
      string[i] = towlower(string[i]);
   };
}

void CUtiString::ToUpperCase()
{
   for (int i = 0; i < length; i++) {
      string[i] = towupper(string[i]);
   };
}

void CUtiString::MakeFile()
{
    int l = getlength();
    for (int i = 0; i < l; i++)
    {
        if (string[i] == UTEXT('/') || string[i] == UTEXT('\\') || string[i] == UTEXT(':')|| string[i] == UTEXT('*')
                || string[i] == UTEXT('?')|| string[i] == UTEXT('"')|| string[i] == UTEXT('<')
                || string[i] == UTEXT('>')|| string[i] == UTEXT('|'))
        {
            string[i] = UTEXT('_');


        }
    };
}

void CUtiString::IntToStrRadix(int i, U_CHAR *str,int length, int radix)
{
    swprintf(str, length,  UTEXT("%i"), i);
    //_itoa(i, str, radix);
}

int CUtiString::ToInt()
{

    return(wcstol(string, 0, 10));
}

double CUtiString::ToFloat()
{
    U_CHAR *stopstring;
    return(wcstod( string, &stopstring ));
}

void CUtiString::SaveToFile(U_CHAR* filename)
{
    CUtiString namestr(filename);
    char* ansiname = namestr.GetAnsi();
    wofstream s(ansiname);
    delete ansiname;
    s << getString();

};

void CUtiString::SaveToFile(CUtiString filename)
{
    SaveToFile(filename.getString());
};

void CUtiString::LoadFromFile(CUtiString filename)
{
    LoadFromFile(filename.getString());
}

void CUtiString::LoadFromFile(U_CHAR* filename)
{
    CheckFileName(filename);
    if (!UtiFileExists(filename)) return;
    INT64 size = UtiFileSize(filename);
    if (size < 0) {
       wcout << "Konnte die Datei " << filename << " nicht laden";
       return;
    
    }
    char* c = new char[size+1];
    CFileStream* str = UtiOpenFile(filename);
    str->ReadData(c, size);
    c[size] = 0;
    cout << c;
    this->LoadAnsi(c);

    delete str;
    delete [] c;

    /*	ifstream s(filename);
        bool first = true;
    	while (!s.eof()) {
    		if (first) {
    			first = false;
    		} else {
    			U_CHAR c=13;
    			*this += c;
    			c =10;
    			*this += c;
    		};
    		U_CHAR c[1024];
    		s.getline(c, 1024);
    		*this += c;
    	};*/
};

/*void ConvertAnsiStringToWide( WCHAR* wstrDestination, const CHAR* strSource, size_t cchDestChar )
{
    if( wstrDestination==NULL || strSource==NULL )
        return;

    if( cchDestChar == -1 )
        cchDestChar = strlen(strSource)+1;

    MultiByteToWideChar( CP_ACP, 0, strSource, -1,
                         wstrDestination, cchDestChar-1 );

    wstrDestination[cchDestChar-1] = 0;
}
*/
void CUtiString::LoadAnsi(const char* c)
{
    /*size_t size = strlen(c);
    TCHAR* cw = new TCHAR[size+3];
    ConvertAnsiStringToWide(cw, c, size+2);
    *this = cw;
    delete [] cw;*/
    *this = converttowide(c);
}

char* CUtiString::GetAnsi()
{
    std::string r = converttomulti(this->c_str());

    char* c = new char[r.length()+1];
    //	int l=length+1;
    //WideCharToMultiByte(CP_UTF8, 0, string,length, c, l,NULL, NULL);
    //	c[length] = 0;
    strcpy(c, r.c_str());
    return c;
};

void CUtiString::AddPascalString(U_CHAR* str, int length)
{
    if (length < 50)
    {
        U_CHAR c[52];
        for (int i =0; i < length; i++)
        {
            c[i] = str[i];
        };
        c[length]=0;
        *this += c;

    }
    else if (length < 256)
    {
        U_CHAR c[258];
        for (int i =0; i < length; i++)
        {
            c[i] = str[i];
        };
        c[length]=0;
        *this += c;

    }
    else
    {
        U_CHAR* c = new U_CHAR[length+1];

        for (int i =0; i < length; i++)
        {
            c[i] = str[i];
        };
        c[length]=0;
        *this += c;
        delete [] c;
    };
};

void CUtiString::SetFloat(double f, int count)
{
    /*U_CHAR *buf;
    int dec, s;
    double r = f;
    if (r < 0) r = -r;
    if(r >= 1) count++;if (r >= 10) count++;if (r >= 100) count++;if (r >= 100000000) count++;if (r >= 1000) count++;
    if (r >= 10000) count++;if (r >= 100000) count++; if (r >= 1000000) count++;if (r >= 10000000) count++;

    buf  = _ecvt(f, count, &dec, &s);
    replace(buf);
    U_CHAR c[2];
    c[0] = 46;
    c[1] = 0;

    insert(dec, 1, c);
    U_CHAR *c1;
    c1 = UTEXT("-");
    if (s) {
     insert(0, 1, c1);
    };*/
    U_CHAR buffer[40];
    float f1=f;
    swprintf(buffer, 40, UTEXT("%f"), f1);
    replace(buffer);

}


void ReadStringWide(CStream & Stream, CUtiString &s)
{
    int count;
    Stream.ReadInteger(count);
    wchar_t *t = new wchar_t[count+1];
    if (sizeof(wchar_t) == 2) {
        Stream.ReadData(t, count*sizeof(wchar_t));
    } else {
       for (int i = 0; i < count; i++) {
          t[i] = 0;
          Stream.ReadData(&t[i], 2);
       };
    };
    t[count] = 0;
#ifdef _UNICODE

    s = t;
#else
#ifdef WIN32
    char* c = new char[count+1];
    WideCharToMultiByte(CP_UTF8, 0, t, count, c, count,NULL, NULL);
    s = c;
    delete [] c;
#endif
#endif

    delete []t;
}

void WriteStringWide(CStream & Stream, CUtiString &s)
{
    int count = s.getlength();
    Stream.WriteInteger(count);
#ifdef _UNICODE
    if (sizeof(wchar_t) == 2) {
        Stream.WriteData(s.getString(), count*2);
    } else {
       const wchar_t* k = s.getString();
       for (int i = 0;i < count; i++) {
          Stream.WriteData(&k[i], 2);
       };
       
    };
#else
#ifdef WIN32
    wchar_t *t = new wchar_t[count+1];
    MultiByteToWideChar(CP_UTF8, 0, s.getString(), count, t, count+1);
    Stream.WriteData(t, count*2);
#endif
#endif

}

const CUtiString CodeToString(const SCode s2)
{
    wchar_t t[100];
    #ifdef _WIN32
    StringFromGUID2(s2, t, 100);
    #else
    CUtiString z;
    return z;
    #endif
    int count = 95;
    CUtiString s;

#ifdef _UNICODE

    s = t;
#else
#ifdef WIN32
    char* c = new char[count+1];
    WideCharToMultiByte(CP_UTF8, 0, t, count, c, count,NULL, NULL);
    s = c;
    delete [] c;
#else

#endif
#endif

    return s;
}
