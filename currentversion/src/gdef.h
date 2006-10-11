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
#ifndef __GDEF__
#define __GDEF__


#ifdef _WIN32
#include <guiddef.h>
#else

#include <stddef.h>

typedef struct _GUID {
    unsigned long  Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char  Data4[ 8 ];
} GUID;
#include <string.h>
__inline int IsEqualGUID(GUID rguid1, GUID rguid2)
{
    return memcmp(&rguid1, &rguid2, sizeof(GUID))==0;
}

__inline int operator==(GUID guidOne, GUID guidOther)
{
    return IsEqualGUID(guidOne,guidOther);
}

__inline int operator!=(GUID guidOne, GUID guidOther)
{
    return !(guidOne == guidOther);
}



__inline int operator<(GUID guidOne, GUID guidOther)
{
   if (guidOne == guidOther) return false;
   if (guidOne.Data1 < guidOther.Data1) return true;
   if (guidOne.Data1 != guidOther.Data1) return false;
   if (guidOne.Data2 < guidOther.Data2) return true;
   if (guidOne.Data2 != guidOther.Data2) return false;
   if (guidOne.Data3 < guidOther.Data3) return true;
   if (guidOne.Data3 != guidOther.Data3) return false;
   for (int i = 0; i < 8; i++)  {
      if (guidOne.Data4[i] < guidOther.Data4[i]) return true;
      if (guidOne.Data4[i] != guidOther.Data4[i]) return false;      
};
   return false;
};

__inline int operator<=(GUID guidOne, GUID guidOther)
{
   if (guidOne == guidOther) return true;
   if (guidOne.Data1 < guidOther.Data1) return true;
   if (guidOne.Data1 != guidOther.Data1) return false;
   if (guidOne.Data2 < guidOther.Data2) return true;
   if (guidOne.Data2 != guidOther.Data2) return false;
   if (guidOne.Data3 < guidOther.Data3) return true;
   if (guidOne.Data3 != guidOther.Data3) return false;
   for (int i = 0; i < 8; i++)  {
      if (guidOne.Data4[i] < guidOther.Data4[i]) return true;
      if (guidOne.Data4[i] != guidOther.Data4[i]) return false;      
   };
   return false;
};

__inline int operator>(GUID guidOne, GUID guidOther)
{
   return !(guidOther <= guidOne);
};
__inline int operator>=(GUID guidOne, GUID guidOther)
{
   return !(guidOther < guidOne);
};

#endif

typedef void *LPVOID;
#ifdef _WIN32
typedef __int64 INT64, *PINT64;
typedef unsigned __int64 UINT64;
#else
typedef long long INT64, *PINT64;
typedef unsigned long long UINT64;
#endif
#ifdef _WIN32
#define UTICDECL __cdecl
#define STDCALL __stdcall
#define UTIAPIENTRY __stdcall
#else
#define UTICDECL 
#define STDCALL
#define APIENTRY

#endif

typedef unsigned short WORD;
#ifndef _WIN32
typedef unsigned int DWORD;
typedef bool BOOL;
#endif

#endif 
