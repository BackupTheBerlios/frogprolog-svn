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

#ifndef __UtiString__
#define __UtiString__


//#include "StdAfx.h"
#include "Uti3DCore.h"


#include "utichar.h"
#include <wchar.h>
#include <iostream>

//#define wcscmp _tcscmp
/*#define wcslen _tcslen
#define remove _tremove
#define swprintf _stprintf
#define swscanf _stscanf
#define wcscpy _tcscpy*/

class CUtiString;
static const unsigned int INCBUFFER = 15;

#define IsNumber(a) (a >= UTEXT('0') && a <= UTEXT('9'))
#define IsLetter(a) ((a >= UTEXT('A') && a <= UTEXT('Z')) || (a >= UTEXT('a') && a <= UTEXT('z')))
#define IsUnderLine(a) (a == UTEXT('_'))
#define IsCharacter(a) ((a != UTEXT(' ')) && (a > 30))
#define IsBezeichner(a) (IsNumber(a) || IsLetter(a) || IsUnderLine(a))
#define IsVergleich(a) (a == UTEXT('>') || a == UTEXT('<') || a == UTEXT('='))
const int MAX_ITEMS = 256;


bool IsInteger(U_CHAR *str, int length);
int SearchChar(U_CHAR *str, U_CHAR c, int length);
int SearchCharBackward(U_CHAR *str, U_CHAR c, int length);
int SearchChar(U_CHAR *str, U_CHAR c, int length, int charpos);
int SearchStringBackward(U_CHAR *str, U_CHAR* c, int length, int searchlength);
int SearchString(U_CHAR *str, U_CHAR* c, int length, int searchlength);
int SearchStringBackwardBez(U_CHAR *str, U_CHAR* c, int length, int searchlength);
int SearchStringBez(U_CHAR *str, U_CHAR* c, int length, int searchlength);
bool ValidBez(U_CHAR* str, int i, int length, int searchlength);
void SearchBeginEnd(U_CHAR*str, int length, int &beginpos, int &endpos, bool last);
void SearchStrings(U_CHAR* str, U_CHAR*c, int length, int searchlength, int* result, int &rescount);
const CUtiString CalcNumberedFileName(TCHAR* start, TCHAR* ende);


class CUtiString : public CUtiOB
{
private:
	void replace(const U_CHAR *s);
	U_CHAR* string;
	int length;
	int buffersize;
public:
#ifdef EDITOR
	CUtiOB* parent;
#endif		
	int Pos(U_CHAR* substr);
	int Pos(int start, U_CHAR* substr);
	void Copy(CUtiString* target, int start, int length);
	int getlength() {return(length);};
	void SetFloat(double f, int count);
	int ToInt();
	double ToFloat();
	int calcbuffersize(int len);
	static void IntToStrRadix(int i, U_CHAR *str, int length, int radix);
	void IntToStr(int i);
	void Delete(int index, int length);
	void FloatToStr(const float i);
	void getLine(int line, CUtiString *str);
	int getLineCount();
	static void IntToStr(int i, U_CHAR *str);
	U_CHAR* getString() const;
	U_CHAR* c_str() const;
	void ReadProp(TCHAR* name, CUtiString* result, TCHAR* defaultitem);
	void AddPascalString(U_CHAR* str, int length);
	void insert(unsigned int pos, unsigned int slen, const TCHAR *s);
	class EStringAllocateFailure{};
	class EOutOfRangeError{};
	CUtiString(const CUtiString &s);
	CUtiString(const U_CHAR c);
	CUtiString(const U_CHAR *c);
	CUtiString();
	~CUtiString();
        CUtiString &operator =(const CUtiString &s);
	CUtiString &operator =(const U_CHAR *s);
	CUtiString &operator =(const U_CHAR c);
	CUtiString &operator =(int i);
	CUtiString &operator =(float i);
	CUtiString &operator+=(const CUtiString &s);
        CUtiString &operator+=(const U_CHAR *s);
	CUtiString &operator+=(const U_CHAR c);
        CUtiString &operator+=(const int i);
	CUtiString &operator+=(const float i);
	friend const CUtiString operator+(const CUtiString &s1, const CUtiString &s2)
	{
		CUtiString temp = s1.string;
		temp.insert(temp.length, wcslen(s2.string), s2.string);
		return(temp);
	}
	friend const CUtiString operator+(const U_CHAR *s, const CUtiString &s2)
	{
		CUtiString temp = s;
		temp.insert(temp.length, wcslen(s2.string), s2.string);
		return(temp);
	}
	friend const CUtiString operator+(const U_CHAR c, const CUtiString &s2)
	{
		CUtiString temp = c;
		temp.insert(temp.length, wcslen(s2.string), s2.string);
		return(temp);
	}
	const CUtiString operator+(const U_CHAR *s) const;
	const CUtiString operator+(const U_CHAR c) const;
	const CUtiString operator+(const int i) const;	
	const CUtiString operator+(const float f) const;
	U_CHAR &operator[](unsigned int p);
	const U_CHAR &operator[](unsigned int p) const;
	bool operator<(const CUtiString &s) const {if ((!string) || (!s.string)) return (false);return(wcscmp(string, s.string) < 0);}
	bool operator<=(const CUtiString &s) const {if ((!string) || (!s.string)) return (false);return(wcscmp(string, s.string) <= 0);}
	bool operator==(const CUtiString &s) const {if ((!string) || (!s.string)) return (false);return(wcscmp(string, s.string) == 0);}
	bool operator!=(const CUtiString &s) const {if ((!string) || (!s.string)) return (false);return(wcscmp(string, s.string) != 0);}
	bool operator>=(const CUtiString &s) const {if ((!string) || (!s.string)) return (false);return(wcscmp(string, s.string) >= 0);}
	bool operator>(const CUtiString &s) const {if ((!string) || (!s.string)) return (false);return(wcscmp(string, s.string) > 0);}
	bool operator==(const TCHAR *s) const {if ((!string) || (!s)) return (false);return(wcscmp(string, s) == 0);}
	bool operator<(const TCHAR *s) const {if ((!string) || (!s)) return (false);return(wcscmp(string, s) < 0);}
	bool operator<=(const TCHAR *s) const {if ((!string) || (!s)) return (false);return(wcscmp(string, s) <= 0);}
	bool operator!=(const TCHAR *s) const {if ((!string) || (!s)) return (false);return(wcscmp(string, s) != 0);}
	bool operator>=(const TCHAR *s) const {if ((!string) || (!s)) return (false);return(wcscmp(string, s) >= 0);}
	bool operator>(const TCHAR *s) const {if ((!string) || (!s)) return (false);return(wcscmp(string, s) > 0);}

	CUtiString operator()(unsigned int p, unsigned int l) const;
	bool IsEmpty(){return(string[0] == 0);};
	HResult Read(CStream & Stream, int Flags, int version);
	HResult Write(CStream & Stream, int Flags, int version);
	void LoadFromFile(U_CHAR* filename);
	void SaveToFile(U_CHAR* filename);
	void LoadFromFile(CUtiString filename);
	void SaveToFile(CUtiString filename);
	void DecLength(int i);
	void ExtractFileName();
	void ExtractRealFileName();
	void ExtractFilePath();
	void ExtractFileExt();
        const CUtiString LowerCase();
        const CUtiString UpperCase();
        void ToLowerCase();
        void ToUpperCase();
        
	void MakeFile();
	int LastDelimiter(U_CHAR* substr);
	void ReplaceChar(TCHAR oldchar, TCHAR newchar);
	//void ReadProp(char* name, CUtiString* result);
	void LoadAnsi(const char* c);
	char* GetAnsi();
};

const CUtiString CodeToString(const SCode s2);

const CUtiString RandomString(TCHAR* start, int l, int h, TCHAR* ende);
void ReadStringWide(CStream & Stream, CUtiString &s);
void WriteStringWide(CStream & Stream, CUtiString &s);

std::wostream & operator<<(std::wostream & os, const CUtiString & str);

#endif
