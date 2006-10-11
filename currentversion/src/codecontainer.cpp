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
#include "codecontainer.h"

namespace Interpreter {

CodeContainer::CodeContainer()
{
   maxsize = 32386;
   code = new int[maxsize];
   size = 0;
}


CodeContainer::~CodeContainer()
{
}


void CodeContainer::SaveToFile(wchar_t* filename)
{
   CFileStream* str = new CFileStream(filename, S_WRITE);
   SaveToStream(str);
   delete str;
}

void CodeContainer::SaveToStream(CStream* str)
{
   int c = names.size();
   str->WriteInteger(c);
   for (int i = 0; i < c; i++) {
      CUtiString n = names[i];
      WriteStringWide(*str, n);
   };
   /*c = ProcCode.size();
   str->WriteInteger(c);
   for (int i = 0; i < c; i++) {
      OpCommand com = ProcCode[i];
      str->WriteData(&com, sizeof(com));
};*/
}

void CodeContainer::ReadFromFile(wchar_t* filename)
{
   CFileStream* str = new CFileStream(filename, S_READ);
   ReadFromStream(str);
   delete str;
}
void CodeContainer::ReadFromStream(CStream* str)
{
   int c;
   str->ReadInteger(c);
   names.clear();
   //ProcCode.clear();
   CUtiString st;
   for (int i = 0; i < c; i++) {
      ReadStringWide(*str, st);
      names.push_back(st);
   };
  /* str->ReadInteger(c);
   for (int i = 0; i < c; i++) {
      OpCommand com;
      str->ReadData(&com, sizeof(com));
      ProcCode.push_back(com);
}*/
}

int CodeContainer::getCurrentPos()
{
   return size;
}

void CodeContainer::addLabel(int pos, int name, int arity)
{
   
}

int* CodeContainer::addCode(int i)
{
   if (size >= maxsize) return NULL;
   code[size]=i;
   size++;
   return &code[size-1];
}

int CodeContainer::addName(wchar_t* name)
{
   CUtiString n = name;
   names.push_back(n);
   return names.size()-1;
}

}
