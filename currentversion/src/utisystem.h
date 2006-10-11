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
 
#ifndef _UTISYSTEM_
#define _UTISYSTEM_

// body file: utisystem.cpp

#include <string>

using namespace std;
#ifdef UFRAMEWORK
#include "UtiString.h"
#else
typedef wstring CUtiString;
#endif

#define UTI_API extern 
#define UTI_APIIMPORT

//#define CUtiString wstring

#include "gdef.h"

namespace UtiFramework {


enum TFileDateType {dtAccess, dtModification, dtStatusChange};

double getFileDate(CUtiString path, TFileDateType type);
void initTime();
double getCurrentTime();
const CUtiString getCurrentDir();
void ChangeDir(CUtiString str);
struct Dir_FileInfo {
   LPVOID Dir;
   LPVOID entity;
   CUtiString name;
   INT64 size;
   bool dir;
};

bool FindFirst(CUtiString path, Dir_FileInfo *fi);
bool FindNext(Dir_FileInfo*fi);
void FindClose(Dir_FileInfo*fi);
const CUtiString converttowide(const char* c);
const string converttomulti(const wchar_t * c);
void sleep(int ms);
LPVOID UtiLoadLibrary(wchar_t* name);
void UtiFreeLibrary(LPVOID module);
LPVOID UtiGetProcAddress(LPVOID module, char* name);
int getFileSize(CUtiString path);

};


#endif
