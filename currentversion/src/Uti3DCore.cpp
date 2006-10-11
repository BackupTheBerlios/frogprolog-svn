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

#define _WIN32_WINNT 0x0400


#include "Uti3DCore.h"
#include "Uti3DMath.h"
#include "UtiString.h"
#include "UtiArchiv.h"





#include <cmath>
#ifdef WIN32
#include <objbase.h>
#include <process.h>
#include <winbase.h>
#else
#ifdef USETHREADS
#include <pthread.h>
#endif
#endif
#include <cstdio>

#include <fstream>
#include <strstream>
#include <set>
#include <typeinfo>
#include <iostream>
#include "utisystem.h"

using namespace std;

using namespace UtiFramework;

ostrstream dout;

#ifdef _DEBUG
//#define USEMEMDUMP
#endif


#ifdef USEMEMDUMP
set
    <CUtiOB*> UtiOBInstanceObj;
#endif

void CheckFileName(TCHAR* c)
{

    if (!FileExists(c))
    {
        wcout << "Die Datei " << c << " konnte nicht gefunden werden"  << endl;
	
    }
    /*if (FileExists(c)) {
       CUtiString g;
       g = UTEXT("C:\\Michael\\SpaceRelease\\");
       g += c;
    CUtiString kl;
    kl = g;
    kl.ExtractFilePath();
    ForceDir(kl.getString());
       if (!FileExists(g.getString())) {
          CopyFile(c, g.getString(), false);
       };

    };*/

}
;

int UtiGetRValue(int color)
{
    return color & 0xFF;
}
int UtiGetGValue(int color)
{
    return (color >> 8) &0xFF;
}
int UtiGetBValue(int color)
{
    return (color >> 16) & 0xFF;
}
int UtiRGB(int r, int g, int b)
{
    return r || g << 8 || b << 16;
}


void ShowMessage(wchar_t* text)
{
   wcout << text << endl;
#ifdef WIN32
   MessageBox(0, text, L"assert", 0);
#endif
}

void zeromem(LPVOID l, int count)
{
    memset(l, '\0', count);
}

float sqr(float d)
{
    return d*d;
}

int urandom(int max)
{
    return(rand() % max);
}

float urandom()
{
    return((float)rand() / RAND_MAX);
}

int ToPower2(int i)
{
    int r= i;
#define powm(a) if (i <= a) return(a);

    powm(1);
    powm(2);
    powm(4);
    powm(8);
    powm(16);
    powm(32);
    powm(64);
    powm(128);
    powm(256);
    powm(512);
    powm(1024);
    powm(2048);
    powm(4096);
    powm(4096*2);
    powm(4096*4);
    powm(4096*8);
    powm(4096*9);
#undef powm

    return(256);
}

bool Writefunc(NODE_PTR node, void* data)
{
    CStream * strm = (CStream*)data;
    node->data->Write(*strm, 0, 0);
    return true;
}

bool compareCode(SCode c1, SCode c2)
{
    // return((c1 == c2));
    return(IsEqualGUID(c1, c2));
}

const SCode createCode()
{
    SCode result;
    // CoCreateGUID(result);
#ifdef WIN32

    UuidCreate(&result);
#else

    result.Data1 = urandom(65535) << 16 | urandom(255);
    ;
    result.Data2 = urandom(65535);
    result.Data3 = urandom(65535);
    result.Data4[0] = urandom(255);
    result.Data4[1] = urandom(255);
    result.Data4[2] = urandom(255);
    result.Data4[3] = urandom(255);
    result.Data4[4] = urandom(255);
    result.Data4[5] = urandom(255);
    result.Data4[6] = urandom(255);
    result.Data4[7] = urandom(255);
#endif

    return result;
}



const SCode IntToCode(int i)
{
    SCode result = NULLCODE;
    result.Data1 = i;
    return result;
}

const int CodeToInt(const SCode i)
{
    int result = i.Data1;
    if (result < 0)
        result = 1000000000;
    return result;
}

bool PtInRectE(float x, float y, float x1, float y1, float x2, float y2)
{
    return(x > x1 && x < x2 && y < y1  && y > y2);
};


SVector4 setVector4(float x, float y, float z, float w)
{
    SVector4 res;
    res.x = x;
    res.y = y;
    res.z = z;
    res.a = w;
    return(res);
}

void NormRect(UTIRECT &r)
{
    int i;
    if (r.top > r.bottom)
    {
        i = r.top;
        r.top = r.bottom;
        r.bottom = i;
    };
    if (r.left > r.right)
    {
        i = r.left;
        r.left = r.right;
        r.right = i;
    };
}

void ForceDir(TCHAR* path)
{
    CUtiString P(path);
    P.ExtractFilePath();
    if (!FileExists(P.getString()))
    {
        ForceDir(P.getString());

    }
#ifdef WIN32
    CreateDirectory(path, NULL);
#else

#endif
}

void doutiassert(TCHAR* expression,char* file, int line, char* date)
{
    TCHAR c[256];
    CUtiString f;
    f.LoadAnsi(file);
    CUtiString d;
    d.LoadAnsi(date);
    swprintf(c,256, UTEXT("UTIASSERT: %s \n\n Datei: %s \n Zeile: %i \n Datum der Kompilierung: %s"), expression, f.c_str(), line, d.c_str());
     ShowMessage(c);
}

void doutiassert2(TCHAR* expression, TCHAR* file, int line, TCHAR* date, TCHAR* info)
{
    TCHAR c[256];
    swprintf(c, 256,UTEXT("UTIASSERT: %s \n\n Datei: %s \n Zeile: %i \n Datum der Kompilierung: %s\n\n%s"), expression, file, line, date, info);
    // MessageBox(0, c, UTEXT("Benutzerfehler"), 0);
     ShowMessage(c);
}



HResult CUtiOB::Write(CStream &Stream, int Flags, int version)
{
    return(UTI_OK);
}

HResult CUtiOB::Read(CStream &Stream, int Flags, int version)
{
    return(UTI_OK);
}

int CUtiOB::GetMessageUti(CUtiOB *Sender, int msg, int lParam, int wParam, bool &handled)
{
    return(0);
}

void CUtiOB::xread(CXNode* n, CWriteReadInterface* wri)
{

};


void CUtiOB::xwrite(CXNode* n, CWriteReadInterface* wri)
{

};

CUtiOB::~CUtiOB()
{
#ifdef EDITOR
    DeleteItem(v);
#endif
#ifdef USEMEMDUMP

    utiassert(UtiOBInstanceObj.find(this) != UtiOBInstanceObj.end());
    UtiOBInstanceObj.erase(this);
#endif
}

HResult CUtiOB::Assign(CUtiOB*ob, int flags)
{
    /*HResult res;
       UINT a = (unsigned int)&ob;
    UINT b = (unsigned int)this;
    if (a == b) {
    	return(UTI_ERROR_SAME_CLASS);
    }
       CSharedFile memfile(GMEM_DDESHARE | GMEM_MOVEABLE, 4096);

    res = ob.Write(memfile, 0, 0);
    if (res != UTI_OK) return res;
    memfile.SeekToBegin();

    res = Read(memfile, 0, 0);
    if (res != UTI_OK) return res;
    return (UTI_OK);*/
    return(UTI_OK);
}

void CStream::WriteData(const void *data, unsigned int size)
{
}

void CStream::ReadData(void *data, unsigned int size)
{
}

void CStream::WriteInteger(int i)
{
    WriteData(&i, 4);

}

void CStream::ReadInteger(int &i)
{
    ReadData(&i, 4);
}

void CStream::ReadBoolean(bool &b)
{
    ReadData(&b, 1);
}

void CStream::WriteBoolean(bool b)
{
    WriteData(&b, 1);
}

void CStream::WriteFloat(float f)
{
    WriteData(&f, sizeof f);
}

void CStream::ReadFloat(float &f)
{
    ReadData(&f, sizeof f);
}

void CStream::WriteDouble(double d)
{
    WriteData(&d, sizeof d);
}

void CStream::ReadDouble(double &d)
{
    ReadData(&d, sizeof d);
}

void CFileStream::WriteData(const void *data, unsigned int size)
{

    fstream* str = (fstream*) strm;
    if (docount)
    {
        count = count +size;
    }
    else
    {
        str->write((U_SCHAR* )data, size);
    };
}

void CFileStream::ReadData(void *data, unsigned int size)
{

    std::fstream* str = (std::fstream*) strm;
    str->read((U_SCHAR* )data, size);
}

CFileStream::CFileStream(U_CHAR *name, int i, bool trunc) : CStream()
{
    fstream* str = new fstream();
    strm = str;
    if (i == S_READ)
        CheckFileName(name);

    docount = false;
    count = 0;
    iswrite = false;
    CUtiString namestr(name);
    char* ansiname = namestr.GetAnsi();
    if (i == S_READ)
        str->open(ansiname, ios::binary | ios::in);
    else
    {
        iswrite = true;
        /*if (!trunc)
        r |= ios::trunc;
        else
        r|= ios::ate;*/
        if (trunc)
        {
            str->open(ansiname, ios::binary | ios::out | ios::trunc);
        }
        else
        {
            str->open(ansiname, ios::binary | ios::out | ios::ate);
        }
    };
    delete [] ansiname;


}

CFileStream::~CFileStream()
{

    std::fstream* str = (std::fstream*) strm;
    str->clear();// - K�nte ntzlich sein
    str->flush();
    str->close();
    delete str;

}

bool CFileStream::fail()
{
    fstream* str = (fstream*) strm;
    return(str->fail()!=0);
};
bool CFileStream::eof()
{
    std::fstream* str = (std::fstream*) strm;
    return(str->eof()!=0);
};

void CFileStream::setPosition(UINT i)
{
    fstream* str = (fstream*) strm;
    if (iswrite)
    {
        str->seekp(i);
        //strm.seekg(i);
    }
    else
    {
        str->seekg(i);
    }

    /* CUtiString k;
    k = (int)i;
    MessageBox(0, k.getString(), UTEXT("klk"), 0);*/
}

UINT CFileStream::getReadPosition()
{
    fstream* str = (fstream*) strm;
    return(str->tellg());
}

UINT CFileStream::getWritePosition()
{
    fstream* str = (fstream*) strm;
    return(str->tellp());
}

void CStream::setPosition(UINT i)
{
    //nix
}

CUtiList::CUtiList()
{
    sorted = false;
    deleteItems = false;
    first = NULL;
    last = NULL;
    count = 0;
    MemController = NULL;
    //   typinfo = UTI_UTILIST;
    CheckArray(10);
}

void CUtiList::CheckArray(int count)
{
    /*	if (count > arraysize) {
    		int old = arraysize;
    	    arraysize = count+20;
    		NODE* ptr = new NODE[arraysize];
    		if (array) {
    		memcpy(ptr, array, sizeof(NODE)*old);
    		delete array;
    		ptr[0].prev = NULL;
    		ptr[0].next = &ptr[1];
    		for (int i = 1; i < count; i++) {
    		   ptr[i].prev = &ptr[i-1];
    		   if (i != count-1) {
    			  ptr[i].next = &ptr[i+1];
    		   } else {
    			  ptr[i].next = NULL;
    			  last = &ptr[count-1];
    		   }
    		};
    		first = &ptr[0];
    		};
    		array = ptr;
    	};	  */
};

HResult CUtiList::Read(CStream & Stream, int Flags, int version, CUtiOB* (UTICDECL *enumfunc)(CUtiOB* parent, int type), CUtiOB* parent)
{
    Clear();
    Stream.ReadInteger(count);
    int type = 0;
    //CUtiOB* ob;
    for (int i = 0; i < count; i++)
    {
        Stream.WriteInteger(type);
        if (type == UTI_UTIOB)
            return(UTI_READERROR);
        CUtiOB* t = enumfunc(parent, type);
        if (t)
        {
            t->Read(Stream, Flags, version);
            Add(t, 0);
        };
    }
    return(UTI_OK);
}

HResult CUtiList::Write(CStream & Stream, int Flags, int version)
{
    Stream.WriteInteger(count);
    NODE_PTR node = GetFirstItem();
    CUtiOB *obj;
    do
    {
        obj = (CUtiOB*)node->data;
        if (version == 1)
        {
            // Stream.WriteInteger(obj->typinfo);
        };
        obj->Write(Stream, Flags, version);
    }
    while (GetNextPointer(node));
    return(UTI_OK);
}



CUtiList::~CUtiList()
{
    Clear();

}

NODE_PTR CUtiList::GetFirstItem()
{
    return(first);
}

bool CUtiList::GetNextPointer(NODE_PTR &node)
{
    node = node->next;
    return(node != NULL);
}

void CUtiList::Delete(CUtiOB *data)
{
    Delete(indexofNode(data));
}

void CUtiList::AddList(CUtiList *list)
{
    NODE_PTR node = list->GetFirstItem();
    while (node)
    {
        Add(node->data, node->value);
        list->GetNextPointer(node);
    };


};

NODE_PTR CUtiList::Add(CUtiOB *data, float value)
{
    NODE_PTR new_node = NULL;
    NODE_PTR search = NULL;
    new_node = new NODE;
    new_node->data = data;
    new_node->value = value;
    new_node->next = NULL;
    new_node->prev = NULL;
    count++;
    if (first == NULL)
    {
        first = last = new_node;
        return new_node;
    }
    else if ((first != NULL) && (first == last))
    {
        if ((sorted) && (new_node->value < first->value))
        {
            first = new_node;
            new_node->next = last;
            last->prev = new_node;
        }
        else
        {
            first->next = new_node;
            new_node->prev = first;
            last = new_node;
        }
        return new_node;
    }
    else
    {
        if (sorted)
        {
            search = first;
            while ((search != NULL) && (search->value < new_node->value))
            {
                search = search->next;
            }
            if (search == NULL)
            {
                last->next = new_node;
                new_node->prev = last;
                last = new_node;
                return(new_node);
            }
            if (search == first)
            {
                first->prev = new_node;
                new_node->next = first;
                first = new_node;
                return(new_node);
            }
            new_node->prev = search->prev;
            new_node->next = search;

            search->prev->next = new_node;
            search->prev = new_node;

        }
        else
        {
            last->next = new_node;
            new_node->prev = last;
            last = new_node;
        }
        return(new_node);
    }
}

void CUtiList::Delete(NODE_PTR node)
{
    if (!node)
        return;
    if (first == NULL)
        return;
    if (deleteItems)
    {
        if (node->data)
        {
            if (MemController)
            {
                MemController->FreeMemory(node->data);
            }
            else
            {
                delete node->data;
            };
        };
    }
    if (node == first)
    {
        first = first->next;
        if (first)
            first->prev = NULL;
        delete node;
        count--;
        return;
    }
    if (node == last)
    {
        last = last->prev;
        last->next = NULL;
        delete node;
        count--;
        return;
    }
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
    count--;
    return;

}

void CUtiList::Clear()
{
    NODE_PTR node, n2;
	first = last = NULL;
    node = first;
    while (node != NULL)
    {
        n2 = node;
        node = node->next;
        if (deleteItems)
        {
			CUtiOB* sick = n2->data;
            n2->data = NULL;
            delete sick;
            
        }
        delete n2;
    }
    first = last = NULL;
    count = 0;
}




void CUtiList::EnumItems(void *data, bool (UTICDECL *enumfunc)(NODE_PTR,void *))
{
    NODE_PTR node, nnext;
    node = first;
    bool ok;
    while (node != NULL)
    {
        nnext = node->next;
        ok = (*enumfunc)(node, data);
        if (!ok)
            return;
        node = nnext;
    }
}

int CUtiList::indexof(CUtiOB *obj)
{
    NODE_PTR node;
    node = first;
    int i = 0;
    while (node != NULL)
    {

        if (obj == node->data)
            return(i);
        node = node->next;
        i++;
    }
    return(-1);
}

NODE_PTR CUtiList::indexofNode(CUtiOB *obj)
{
    NODE_PTR node;
    node = first;

    while (node != NULL)
    {  

        if (obj == node->data)
            return(node);
        node = node->next;
    }
    return(NULL);
}

CUtiOB* CUtiList::getItem(int i)
{
    NODE_PTR node;
    node = first;
    int index = 0;
    while (node != NULL)
    {

        if (index == i)
            return(node->data);
        node = node->next;
        index++;
    }
    return (NULL);
}

NODE_PTR CUtiList::getNode(int i)
{
    NODE_PTR node;
    node = first;
    int index = 0;
    while (node != NULL)
    {

        if (index == i)
            return(node);
        node = node->next;
        index++;
    }
    return (NULL);
}

void CUtiList::sortItems()
{
}

void CUtiList::Swapitems(NODE_PTR f1, NODE_PTR f2)
{
    NODE_PTR dummy;

    dummy = f1->next;
    f1->next = f2->next;
    f2->next = dummy;

    dummy = f1->prev;
    f1->prev = f2->prev;
    f2->prev = dummy;

    if (f1->prev == NULL)
        first = f1;
    if (f1->next == NULL)
        last = f1;

    if (f2->prev == NULL)
        first = f2;
    if (f2->next == NULL)
        last = f2;
}

void Fehler(U_CHAR* s)
{
    //   cout << s;
}

void CUtiList::GetObjects(float value, CUtiOB *&First, CUtiOB *&Next)
{

    NODE_PTR node;
    node = first;
    First = NULL;
    Next = NULL;
    while (node != NULL)
    {

        if (node->value >= value)
        {
            if (node->prev)
            {
                First = node->prev->data;
                Next = node->data;
            }
            else
            {
                First = node->data;
                Next = node->next->data;
            };

            return;
        }
        node = node->next;
    }
    return;
}

void CUtiList::GetObjectByValue(float value, CUtiOB *&obj)
{
    NODE_PTR node;
    node = first;
    obj = NULL;
    while (node != NULL)
    {

        if ((node->value > (value-EPSILON))&&(node->value < (value+EPSILON)))
        {
            obj = node->data;
            return;
        }
        node = node->next;
    }
    return;
}

CUtiOB::CUtiOB()
{
    //	typinfo = UTI_UTIOB;
#ifdef EDITOR
    TreeItem = 0;
#endif
#ifdef USEMEMDUMP

    UtiOBInstanceObj.insert(this);
#endif
}

#ifdef EDITOR
void CUtiOB::DeleteItem(void* view)
{
   /* CUtiTreeView *tree = (CUtiTreeView*) view;
    if (TreeItem != 0)
    {
        tree->DeleteItem(TreeItem);
    }*/
}

void CUtiOB::AddTreeItem(void* view, UINT parent, U_CHAR *c)
{
    //v = view;
};
#endif


int compare(float a, float b)  //wenn a > b dann result = 1;
{
    float c = a-b;
    if ((c < NAlpha) && (c > -NAlpha))
    {
        return(0);
    }
    if (c < 0)
        return(-1);
    if (c > 0)
        return(1);
    return(0);
}

bool FileExists(U_CHAR* name)
{
    /*ifstream s(name);

    if (s.fail() || s.eof()) return(false); else return(true);*/
   /* Dir_FileInfo d;
    CUtiString n(name);
    CUtiString path;

    path=n;
    path.ExtractFilePath();
    n.ExtractFileName();
    if (!UtiFramework::FindFirst(path, &d))
        return 0;
    if (d.name == n)
        return true;
   // wcout << n.getString() <<endl;
    while (UtiFramework::FindNext(&d))
    {
       // wcout << d.name.getString() <<endl;
        if (d.name == n)
            return true;
    }

    UtiFramework::FindClose(&d);

    return(false);*/
    if ( UtiFramework::getFileSize(name) == -1)
    return false;
    return true;

}

INT64 FileSize(U_CHAR*name)
{


   /* Dir_FileInfo d;
    CUtiString n(name);
    CUtiString path;

    path=n;
    path.ExtractFilePath();
    n.ExtractFileName();
    UtiFramework::FindFirst(path, &d);
    if (d.name == n)
        return d.size;
    while (UtiFramework::FindNext(&d))
    {
        if (d.name == n)
            return d.size;
    }

    UtiFramework::FindClose(&d);*/

    return UtiFramework::getFileSize(name);

}

CMemManager::CMemManager() :CUtiOB()
{
    data = NULL;
    datasize = 0;
    locked = true;
    fileindex = 0;
}

void CMemManager::GetFilename(U_CHAR* c)
{
    swprintf(c,256, UTEXT("Memory%x.tmp"), fileindex);
};

CMemManager::CMemManager(int datasize):CUtiOB()
{
    data = NULL;
    datasize = 0;
    locked = true;
    fileindex = 0;
    Init(datasize);
}

void CMemManager::Init(int datasize)
{
    Free();
    data = new U_SCHAR[datasize];
    this->datasize = datasize;
    fileindex = (UINT)urandom(0xffff)*urandom(0xffff);
    locked = true;
}

void CMemManager::Free()
{
    if (!fileindex)
        return;
    if (data)
        delete [] (U_SCHAR*)data;
    data = NULL;
    datasize = 0;
    locked = true;

    U_CHAR c[256];
    GetFilename(c);
    if (FileExists(c))
    {
        //  wremove(c);
    };

};

CMemManager::~CMemManager()
{
    Free();

}

void CMemManager::Lock()
{

    if (locked)
        return;
    if (!fileindex)
        return;
    U_CHAR c[256];
    GetFilename(c);

    locked = true;
    data = new U_SCHAR[datasize];

    CFileStream* s = new CFileStream(c,S_READ);
    if (s->fail())
    {
        memset(data, 0, datasize);
    }
    else
    {
        s->ReadData(data, datasize);

    };
    delete s;
    //   _wremove(c);
}

void CMemManager::Unlock()
{
    return;

    if (!locked)
        return;
    if (!fileindex)
        return;
    U_CHAR c[256];
    GetFilename(c);
    locked = false;
    CFileStream* s = new CFileStream(c,S_WRITE);
    s->WriteData(data, datasize);
    delete s;
    delete (U_SCHAR*)data;
    data = NULL;

}

CMemoryStream::~CMemoryStream()
{
    if (Memory)
        delete[] (U_SCHAR*)Memory;
}

CMemoryStream::CMemoryStream() : CStream()
{
    Memory=NULL;
    Position = 0;
    failed = false;
    //  FileName[0] = 0;
}

void CMemoryStream::LoadFromFile(U_CHAR*c)
{

    CheckFileName(c);
    INT64 Size = UtiFileSize(c);
    CFileStream* f = UtiOpenFile(c);
    Memory = new char[Size];
    f->ReadData(Memory, Size);
    Position = 0;
    delete f;
    /* #ifdef WIN32
    HANDLE res;
    res = CreateFile(c, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (res == INVALID_HANDLE_VALUE) return;

    if (Memory) delete Memory;
    Size = GetFileSize(res, NULL);
    Memory = new char[Size];
    unsigned long Read=0;
    ReadFile(res, Memory, Size, &Read, NULL);

    Position = 0;
    CloseHandle(res);
    #endif*/
    //	FileName = c;
    /* CFileStream* f = new CFileStream(c, S_READ);
     f->strm.


     delete f;*/
};

void CMemoryStream::WriteData(const void *data, unsigned int size)
{
    if (docount)
    {
        count = count +size;
    }
    else
    {
        // strm.write((U_SCHAR* )data, size);
    };
}

void CMemoryStream::ReadData(void *data, unsigned int size)
{
    if (Position + size > Size)
    {
        failed = true;
        return;
    };
    memcpy(data,(LPVOID) ((UINT)Memory+Position), size);
    Position += size;
}


void CMemoryStream::setPosition(UINT i)
{
    Position = i;
}

UINT CMemoryStream::getReadPosition()
{
    return(Position);
}

UINT CMemoryStream::getWritePosition()
{
    return(Position);
}



void CCacheList::ValidNewSize(int newcount)
{
    bool changed = false;

    if (newcount > capacity)
    {  //grow
        while (newcount > capacity)
        {
            capacity += inc;
        };
        changed = true;
    }
    else if (newcount < capacity-inc*2)
    {
        capacity = newcount+inc;
        if (capacity < inc)
            capacity = inc;
        changed = true;
    };
    int size = count;
    if (newcount < size)
    {
        size = newcount;
        changed = true;
    }
    if (changed)
    {
        LPVOID* ptr = ReserveMem(capacity);
        memcpy(ptr, pointers, sizeof(LPVOID)*size);
        FreeMem( pointers);
        pointers = ptr;
    }
    count = newcount;
}

LPVOID* CCacheList::ReserveMem(int count)
{
    return new LPVOID[count];
}

void CCacheList::FreeMem(LPVOID vd)
{
    delete [] (LPVOID*)vd;
}

CCacheList::CCacheList() : CUtiOB()
{
    count = 0;
    inc = 20;
    capacity = inc;
    pointers = ReserveMem(capacity);
 //   pointers[0] = NULL;
    deleteItems = false;
    MemController = NULL;
}

void CCacheList::SetNewSize(int size)
{
    utiassert(size < 0);
    ValidNewSize(size);
}



void CCacheList::Insert(LPVOID item, int index)
{
    ValidNewSize(count+1);
    for (int i = count-1; i > index; i--)
    {
        pointers[i] = pointers[i-1];
    };
    pointers[index] = item;

}

CCacheList::~CCacheList()
{
    //Clear();
    if (deleteItems)
    {
        for (int i= 0; i < count; i++)
        {
            //FreeItem(&pointers[i]);
            delete (CUtiOB*)pointers[i];
        };
    };
    count = 0;
    if (pointers)
    {
        FreeMem(pointers);
        pointers = NULL;

    }
};

/*int PolyCompare(const void *p1, const void * p2)
{
	TPoly* poly1 = (TPoly*)*(UINT*)p1;
	TPoly* poly2 = (TPoly*)*(UINT*)p2;
	if (poly1->zaverage == poly2->zaverage) return(0);
	if (poly1->zaverage > poly2->zaverage) {
       return(-1);
	} else {
       return(1);
	};
}*/

void CCacheList::Sort(int (UTICDECL *compare )(const void *elem1, const void *elem2 ))
{
    if (count == 0)
        return;
    qsort(pointers, count, 4, compare);
}

void CCacheList::FreeItem(LPVOID* item)
{
    CUtiOB* ob = (CUtiOB*)*item;
    *item = NULL;
    if (deleteItems)
    {
        if (MemController)
        {
            MemController->FreeMemory(ob);
        }
        else
        {
            delete ob;
        };
    }
    *item = NULL;
};


void CCacheList::Clear()
{
    if (count == 0)
        return;
    for (int i= 0; i < count; i++)
    {
        FreeItem(&pointers[i]);
    };
    ValidNewSize(0);
};

void CCacheList::Add(LPVOID item)
{
    ValidNewSize(count+1);
    pointers[count-1] = item;
};

void CCacheList::Remove(LPVOID item)
{
    int i = IndexOf(item);
    if (i != -1)
    {
        Delete(i);
    };
}

void CCacheList::Extract(LPVOID item)
{
    int i = IndexOf(item);
	if (i == -1) return;
	Extract(i);
}

void CCacheList::Extract(int index)
{
    for (int i = index; i < count-1; i++)
    {
        pointers[i] = pointers[i+1];
    };
    ValidNewSize(count-1);
}

void CCacheList::RemoveExtract(LPVOID item)
{
    Extract(IndexOf(item));
}


void CCacheList::Delete(int index)
{
    //	memmove(ptr[index], ptr[index+1], (count-index)*sizeof(LPVOID));
    utiassert(index >= 0 && index < count);
    LPVOID t = pointers[index];
    Extract(index);
    FreeItem(&t);

};

int CCacheList::IndexOf(LPVOID item)
{
    for (int i= 0; i < count; i++)
    {
        if (pointers[i] == item)
            return(i);
    };
    return(-1);
};

void CCacheList::Move(int source, int dest)
{
    utiassert(source >= 0 && dest < count);
    LPVOID temp;
    temp = pointers[source];
    pointers[source] = pointers[dest];
    pointers[dest] = temp;
}

void CCacheList::Pack()
{
    int newcount=inc;
    for (int i = 0; i < count; i++)
    {
        if (pointers[i] != NULL)
            newcount++;
    };
    LPVOID* ptr = ReserveMem(newcount);//new LPVOID[newcount];
    capacity = newcount;
    newcount=0;
    for (int i = 0; i < count; i++)
    {
        if (pointers[i] != NULL)
        {
            ptr[newcount]	= pointers[i];
            newcount++;
        }
    };
    count = newcount;
    // delete [] pointers;
    FreeMem(pointers);
    pointers = ptr;
}

void CCacheList::AddList(CCacheList* list)
{
    int oldcount = count;
    ValidNewSize(count+list->count);
    memcpy(&pointers[oldcount], list->pointers, list->count*sizeof(LPVOID));
};

void CCacheList::AddList(CUtiList *list)
{
    NODE_PTR node = list->GetFirstItem();
    while (node)
    {
        Add(node->data);
        list->GetNextPointer(node);
    };


};



HResult CCacheList::Read(CStream & Stream, int Flags, int version, CUtiOB* (UTICDECL *enumfunc)(CUtiOB* parent, int type), CUtiOB* parent)
{
    Clear();
    Stream.ReadInteger(count);
    int type = 0;
    //CUtiOB* ob;
    for (int i = 0; i < count; i++)
    {

        Stream.ReadInteger(type);
        if (type == UTI_UTIOB)
            return(UTI_READERROR);
        CUtiOB* t = enumfunc(parent, type);
        if (t)
        {
            t->Read(Stream, Flags, version);
            Add(t);
        };
    }
    return(UTI_OK);
}

HResult CCacheList::Write(CStream & Stream, int Flags, int version)
{
    Stream.WriteInteger(count);
    CUtiOB *obj;
    for (int i=0; i< count; i++)
    {
        obj = (CUtiOB*)pointers[i];
        if (version == 1)
        {
            //	    Stream.WriteInteger(obj->typinfo);
        };
        obj->Write(Stream, Flags, version);
    };
    return(UTI_OK);
}

int CHeapList::getParent(int k)
{
    if (k == 0)
        return -1;
    if (k && 1 == 0)
    {
        return (k-2) >> 1;
    }
    else
    {
        return (k-1) >> 1;
    };
    return -1;

}

void CHeapList::Add(LPVOID item)
{
    CCacheList::Add(item);
    upheap(count-1);
}

int CHeapList::GetItemWeighti(int i)
{

    return ((CUtiOB*)pointers[i])->getWeighti();
};

void CHeapList::downheap(int item)
{
    int itemweight = GetItemWeighti(item);
    int childleft;
    int childright;
    int chwl, chwr;
    while (true)
    {
        childleft = item*2+1;
        childright = item*2+2;
        if (childleft >= count)
            return;
        if (childright >= count)
        {
            chwl = GetItemWeighti(childleft);
            if (chwl > itemweight)
            {
                Move(childleft, item);
                return;
            };
            return;
        };
        chwl = GetItemWeighti(childleft);
        chwr = GetItemWeighti(childright);
        if (chwl <= itemweight && chwr <= itemweight)
            return;
        if (chwl > itemweight || chwr > itemweight)
        {
            if (chwl > chwr)
            {
                Move(childleft, item);
                item = childleft;

            }
            else
            {
                Move(childright, item);
                item = childright;
            };

        };
    };
}

void CHeapList::upheap(int item)
{
    int parent = getParent(item);
    int itemweight = GetItemWeighti(item);
    while (parent != -1)
    {
        int pw =GetItemWeighti(parent);
        if (pw < itemweight)
        {
            //Move(parent, item);
            LPVOID temp;
            temp = pointers[parent];
            pointers[parent] = pointers[item];
            pointers[item] = temp;

            //Move
            item = parent;
            parent = getParent(item);
        }
        else
        {
            //Ok
            return;
        };
    };
}

void CHeapList::Delete(int index)
{
    if (index != 0)
        return;
    if (count == 1)
    {
        CCacheList::Delete(0);
        return;
    }
    LPVOID t = pointers[0];
    pointers[0] = pointers[count-1];


    ValidNewSize(count-1);
    FreeItem(&t);

    downheap(0);
};


CPersistentMem::CPersistentMem() : CUtiOB()
{
}

HResult CPersistentMem::Read(CStream & Stream, int Flags, int version)
{
    Stream.ReadData(data, datasize);
    return 0;
}

HResult CPersistentMem::Write(CStream & Stream, int Flags, int version)
{
    Stream.WriteData(data, datasize);
    return 0;
}

CPersistent::CPersistent()
{
    list.deleteItems = true;
}

void CPersistent::AddMem(LPVOID data, int datasize)
{
    CPersistentMem* mem = new CPersistentMem();
    mem->data = data;
    mem->datasize = datasize;
    list.Add(mem);

}
HResult CPersistent::Read(CStream & Stream, int Flags, int version)
{
    for (int i = 0; i < list.count; i++)
    {
        CUtiOB* o = (CUtiOB*)list[i];
        o->Read(Stream, Flags, version);
    };
    return 0;
}

HResult CPersistent::Write(CStream & Stream, int Flags, int version)
{
    for (int i = 0; i < list.count; i++)
    {
        CUtiOB* o = (CUtiOB*)list[i];
        o->Write(Stream, Flags, version);
    };
    return 0;
}

void CPersistent::SaveToFile(U_CHAR* filename)
{
    CFileStream strm(filename, S_WRITE);
    Write(strm, 0, 1);
}

void CPersistent::LoadFromFile(U_CHAR* filename)
{
    CFileStream strm(filename, S_READ);
    Read(strm, 0, 1);

}



void CThread::Execute()
{
}

void CThread::Terminate()
{
    ToTerminate = true;
}

void _MichiThreadProc(void* pParam)
{
    ((CThread*)pParam)->Execute();
};
#ifndef WIN32
void* _MichiThreadProc_POSIX(void* pParam)
{
    ((CThread*)pParam)->Execute();
#ifdef USETHREADS
	pthread_exit(NULL);
#endif
	return NULL;
};
#endif

CThread::CThread() : CUtiOB()
{
    ToTerminate = false;
    init = false;
#ifdef WIN32

    thread = (HANDLE)_beginthread(_MichiThreadProc, 0, this);
#else
#ifdef USETHREADS
    pthread_t * newthread = new pthread_t;
    int rc = pthread_create(newthread, NULL, _MichiThreadProc_POSIX, this);
	thread = newthread;
#endif
#endif
}

CThread::~CThread()
{
    Terminate();
    WaitFor();
#ifdef WIN32

#else
#ifdef USETHREADS
  sdacscdsadvc  delete (pthread_t *)thread;
#endif
#endif
}


void CThread::IsReady()
{
    init = true;
}

int CThread::WaitFor()
{
#ifdef WIN32
    WaitForSingleObject(thread, INFINITE );
#else
    cout << "pthread_join((*(pthread_t *)thread), NULL);";
#endif

    return 0;
}


int CThread::KillThread()
{
#ifdef WIN32
    _endthread();
#else
#ifdef USETHREADS
    pthread_exit(NULL);
#endif
#endif

    return 0;
}

CCriticalSection::CCriticalSection() : CUtiOB()
{

#ifdef WIN32
    cs = new CRITICAL_SECTION;
    InitializeCriticalSection((CRITICAL_SECTION*)cs);
#else
#ifdef USETHREADS
    pthread_mutex_t* mymutex = new pthread_mutex_t;
	pthread_mutex_init(mymutex, NULL);
	cs = mymutex;
#endif
#endif
}
CCriticalSection::~CCriticalSection()
{
#ifdef WIN32
    DeleteCriticalSection((CRITICAL_SECTION*)cs);
    delete (CRITICAL_SECTION*)cs;
#else
#ifdef USETHREADS
    pthread_mutex_destroy((pthread_mutex_t*) cs);
	delete (pthread_mutex_t*) cs;
#endif
#endif

}

bool CCriticalSection::tryEnter()
{
#ifdef WIN32
    return TryEnterCriticalSection((CRITICAL_SECTION*)cs);
#else
 //   Datentyp testen
#ifdef USETHREADS
	return pthread_mutex_trylock((pthread_mutex_t*) cs);
#endif
#endif
}

void CCriticalSection::Enter()
{
#ifdef WIN32
    EnterCriticalSection((CRITICAL_SECTION*)cs);
#else
#ifdef USETHREADS
    pthread_mutex_lock((pthread_mutex_t*) cs);
#endif
#endif
}
void CCriticalSection::Leave()
{
#ifdef WIN32
    LeaveCriticalSection((CRITICAL_SECTION*)cs);
#else
#ifdef USETHREADS
   pthread_mutex_unlock((pthread_mutex_t*) cs);
#endif
#endif
}

CUtiEvent::CUtiEvent(bool initstate, TCHAR*Name, bool WaitForDoesReset)
{
    //	this->Name = Name;
#ifdef WIN32
    this->Event = CreateEvent(NULL, !WaitForDoesReset, initstate, Name);
#else
#ifdef USETHREADS
    pthread_cond_t* cond = new pthread_cond_t;
    Event = cond;
	pthread_cond_init((pthread_cond_t*)Event, NULL);
#endif
#endif
}

CUtiEvent::~CUtiEvent()
{
#ifdef WIN32
    CloseHandle(Event);
#else
#ifdef USETHREADS
	pthread_cond_destroy((pthread_cond_t*)Event);

    delete (pthread_cond_t*)Event;
#endif
#endif
}

void CUtiEvent::Activate()
{
#ifdef WIN32
    SetEvent(Event);
#else
wcout << L"Das ist nicht hier gut";
#endif
}

void CUtiEvent::Deactivate()
{
#ifdef WIN32
    ResetEvent(Event);
#else

#endif
}

int CUtiEvent::WaitFor(int timeout)
{
#ifdef WIN32
    return WaitForSingleObject(Event, timeout);
#else
	wcout << L"Braucht man hier Mutexe?";
	//pthread_cond_wait
    return 0;
#endif
    //WAIT_OBJECT_0
    //WAIT_TIMEOUT
    //WAIT_FAILED

}

void CMemController::FreeMemory(CUtiOB* ob)
{
    delete ob;
}


CUtiOB* CMemoryManager::GetObjectUti()
{
    for (int i = 0; i < UTI_MEM_SIZE; i++)
    {
        if (Buffer[i])
        {
            CUtiOB* bf = Buffer[i];
            Buffer[i] = NULL;
            DoInit(bf);
            return bf;
        };
    };
    return CreateObject();
}

void CMemoryManager::FreeObject(CUtiOB* ob)
{
    Put(ob);
}

void CMemoryManager::Put(CUtiOB* ob)
{

    for (int i = 0; i < UTI_MEM_SIZE; i++)
    {
        if (!Buffer[i])
        {
            Buffer[i] = ob;
            DoFree(ob);
            return;
        };
    };
    delete ob;
}

CMemoryManager::CMemoryManager() : CUtiOB()
{
    zeromem(Buffer, sizeof(LPVOID)*UTI_MEM_SIZE);

}

CMemoryManager::~CMemoryManager()
{
    for (int i = 0; i < UTI_MEM_SIZE; i++)
    {
        if (Buffer[i])
        {
            delete Buffer[i];
            return;
        };
    };
}
void WriteCode(CStream &Stream, SCode code, int version)
{
    if (version >= 11)
    {
        Stream.WriteData(&code, sizeof(code));
    }
    else
    {

        Stream.WriteData(&code, 8);

    };
};
void ReadCode(CStream &Stream, SCode &code, int version)
{
    if (version >= 11)
    {
        Stream.ReadData(&code, sizeof(code));
    }
    else
    {
        code = NULLCODE;
        Stream.ReadData(&code, 8);

    };
};

//CBaseObject
//    CUtiOB* FParent;
void CBaseObject::GetTypeInfo(LPVOID P, TBaseObjOperation Operation, int readFlags, int version)
{
}

void CBaseObject::RString(LPVOID P, LPVOID str, TCHAR* std, int fl, TCHAR* name)
{
    TBaseOperation* op = (TBaseOperation*)P;
    CUtiString* st = (CUtiString*)str;
    switch (op->Operation)
    {
    case opCreate:
        {
            *st =std;
        }
        ;
        break;
    case opDestroy:
        {
        }
        ;
        break;
    case opRead:
        {
            TBaseSaveInfo *op1 = (TBaseSaveInfo*)P;
            st->Read(*op1->Stream, op1->Flags, op1->version);
        }
        ;
        break;
    case opWrite:
        {
            TBaseSaveInfo *op1 = (TBaseSaveInfo*)P;
            st->Write(*op1->Stream, op1->Flags, op1->version);
        }
        ;
        break;
    };
}

void CBaseObject::RInt(LPVOID P, int* value, int std, int fl, TCHAR* name)
{
    TBaseOperation* op = (TBaseOperation*)P;
    switch (op->Operation)
    {
    case opCreate:
        {
            *value =std;
        }
        ;
        break;
    case opDestroy:
        {
        }
        ;
        break;
    case opRead:
        {
            TBaseSaveInfo *op1 = (TBaseSaveInfo*)P;
            op1->Stream->ReadInteger(*value);
        }
        ;
        break;
    case opWrite:
        {
            TBaseSaveInfo *op1 = (TBaseSaveInfo*)P;
            op1->Stream->WriteInteger(*value);
        }
        ;
        break;
    };
}

void CBaseObject::RFloat(LPVOID P, float* value, float std, int fl, TCHAR* name)
{
    TBaseOperation* op = (TBaseOperation*)P;
    switch (op->Operation)
    {
    case opCreate:
        {
            *value =std;
        }
        ;
        break;
    case opDestroy:
        {
        }
        ;
        break;
    case opRead:
        {
            TBaseSaveInfo *op1 = (TBaseSaveInfo*)P;
            op1->Stream->ReadFloat(*value);
        }
        ;
        break;
    case opWrite:
        {
            TBaseSaveInfo *op1 = (TBaseSaveInfo*)P;
            op1->Stream->WriteFloat(*value);
        }
        ;
        break;
    };
}

void CBaseObject::RDouble(LPVOID P, double* value, double std, int fl, TCHAR* name)
{
    TBaseOperation* op = (TBaseOperation*)P;
    switch (op->Operation)
    {
    case opCreate:
        {
            *value =std;
        }
        ;
        break;
    case opDestroy:
        {
        }
        ;
        break;
    case opRead:
        {
            TBaseSaveInfo *op1 = (TBaseSaveInfo*)P;
            op1->Stream->ReadDouble(*value);
        }
        ;
        break;
    case opWrite:
        {
            TBaseSaveInfo *op1 = (TBaseSaveInfo*)P;
            op1->Stream->WriteDouble(*value);
        }
        ;
        break;
    };
}

void CBaseObject::RVector(LPVOID P, LPVOID vector, float stdx, float stdy, float stdz, int fl, TCHAR* name)
{
    TBaseOperation* op = (TBaseOperation*)P;
    CVector* v = (CVector*)vector;
    switch (op->Operation)
    {
    case opCreate:
        {
            v->setVector(stdx, stdy, stdz);
        }
        ;
        break;
    case opDestroy:
        {
        }
        ;
        break;
    case opRead:
        {
            TBaseSaveInfo *op1 = (TBaseSaveInfo*)P;
            //op1->Stream->ReadDouble(*value);
            v->Read(*op1->Stream);
        }
        ;
        break;
    case opWrite:
        {
            TBaseSaveInfo *op1 = (TBaseSaveInfo*)P;
            v->Write(*op1->Stream);
        }
        ;
        break;
    };
}

void CBaseObject::RVectorList(LPVOID P, CCacheList *vlist, int fl, TCHAR* name)
{
    TBaseOperation* op = (TBaseOperation*)P;
    switch (op->Operation)
    {
    case opCreate:
        {
            vlist->deleteItems = true;
        }
        ;
        break;
    case opDestroy:
        {
            vlist->Clear();
        }
        ;
        break;
    case opRead:
        {
            TBaseSaveInfo *op1 = (TBaseSaveInfo*)P;
            //op1->Stream->ReadDouble(*value);
            //v->Read(op1->Stream);
            vlist->Clear();
            int count;
            op1->Stream->ReadInteger(count);
            CVector* k;
            for (int i = 0; i < count; i++)
            {
                k = new CVector();
                k->Read(*op1->Stream);
                vlist->Add(k);
            };
        }
        ;
        break;
    case opWrite:
        {
            TBaseSaveInfo *op1 = (TBaseSaveInfo*)P;
            int c = vlist->count;
            op1->Stream->WriteInteger(c);
            for (int i = 0; i < c; i++)
            {
                CVector* k = (CVector*)vlist->pointers[i];
                k->Write(*op1->Stream);
            };
        }
        ;
        break;
    };
}

void CBaseObject::RClassList(LPVOID P, CCacheList *classlist, int fl,CUtiOB* (UTICDECL *createfunc)(CUtiOB* parent), TCHAR* name)
{
    TBaseOperation* op = (TBaseOperation*)P;
    switch (op->Operation)
    {
    case opCreate:
        {
            classlist->deleteItems = true;
        }
        ;
        break;
    case opDestroy:
        {
            classlist->Clear();
        }
        ;
        break;
    case opRead:
        {
            TBaseSaveInfo *op1 = (TBaseSaveInfo*)P;
            //op1->Stream->ReadDouble(*value);
            //v->Read(op1->Stream);
            classlist->Clear();
            int count;
            op1->Stream->ReadInteger(count);
            CUtiOB* k;
            for (int i = 0; i < count; i++)
            {
                k = createfunc(this);
                k->Read(*op1->Stream, op1->Flags, op1->version);
                classlist->Add(k);
            };
        }
        ;
        break;
    case opWrite:
        {
            TBaseSaveInfo *op1 = (TBaseSaveInfo*)P;
            int c = classlist->count;
            op1->Stream->WriteInteger(c);
            for (int i = 0; i < c; i++)
            {
                CUtiOB* k = (CUtiOB*)classlist->pointers[i];
                k->Write(*op1->Stream, op1->Flags, op1->version);
            };
        }
        ;
        break;
    };

}

void CBaseObject::RMultiClassList(LPVOID P, CCacheList *classlist, int fl,CUtiOB* (UTICDECL *createfunc)(CUtiOB* parent, UINT type), TCHAR* name)
{
    TBaseOperation* op = (TBaseOperation*)P;
    switch (op->Operation)
    {
    case opCreate:
        {
            classlist->deleteItems = true;
        }
        ;
        break;
    case opDestroy:
        {
            classlist->Clear();
        }
        ;
        break;
    case opRead:
        {
            TBaseSaveInfo *op1 = (TBaseSaveInfo*)P;
            //op1->Stream->ReadDouble(*value);
            //v->Read(op1->Stream);
            classlist->Clear();
            int count;
            op1->Stream->ReadInteger(count);
            CUtiOB* k;
            int kp;
            for (int i = 0; i < count; i++)
            {
                op1->Stream->ReadInteger(kp);
                k = createfunc(this, kp);
                k->Read(*op1->Stream, op1->Flags, op1->version);
                classlist->Add(k);
            };
        }
        ;
        break;
    case opWrite:
        {
            TBaseSaveInfo *op1 = (TBaseSaveInfo*)P;
            int c = classlist->count;
            op1->Stream->WriteInteger(c);
            for (int i = 0; i < c; i++)
            {
                CUtiOB* k = (CUtiOB*)classlist->pointers[i];
                //  op1->Stream->WriteInteger(k->typinfo);
                k->Write(*op1->Stream, op1->Flags, op1->version);
            };
        }
        ;
        break;
    };
}

void CBaseObject::RClass(LPVOID P, CUtiOB** ob, int fl, CUtiOB* (UTICDECL *createfunc)(CUtiOB* parent),TCHAR* name)
{

    TBaseOperation* op = (TBaseOperation*)P;
    switch (op->Operation)
    {
    case opCreate:
        {
            if (createfunc)
                *ob = createfunc(this);
        }
        ;
        break;
    case opDestroy:
        {
            if (createfunc)
                delete *ob;
        }
        ;
        break;
    case opRead:
        {
            TBaseSaveInfo *op1 = (TBaseSaveInfo*)P;
            (*ob)->Read(*op1->Stream, op1->Flags, op1->version);
        }
        ;
        break;
    case opWrite:
        {
            TBaseSaveInfo *op1 = (TBaseSaveInfo*)P;
            (*ob)->Write(*op1->Stream, op1->Flags, op1->version);
        }
        ;
        break;
    };
}

void CBaseObject::RCode(LPVOID P, SCode * code, bool zero, int fl, TCHAR* name)
{

    TBaseOperation* op = (TBaseOperation*)P;
    switch (op->Operation)
    {
    case opCreate:
        {
            if (zero)
            {
                *code =NULLCODE;
            }
            else
            {
                *code = createCode();
            };
        }
        ;
        break;
    case opDestroy:
        {
        }
        ;
        break;
    case opRead:
        {
            TBaseSaveInfo *op1 = (TBaseSaveInfo*)P;
            // op1->Stream->ReadData(code, sizeof(SCode));
            ReadCode(*op1->Stream, Code, op1->version);
        }
        ;
        break;
    case opWrite:
        {
            TBaseSaveInfo *op1 = (TBaseSaveInfo*)P;
            // op1->Stream->WriteData(code, sizeof(SCode));
            WriteCode(*op1->Stream, Code, op1->version);
        }
        ;
        break;
    };
}

void CBaseObject::RDate(LPVOID P, double * code, double std, int fl, TCHAR* name)
{
    TBaseOperation* op = (TBaseOperation*)P;
    switch (op->Operation)
    {
    case opCreate:
        {
            *code =std;
        }
        ;
        break;
    case opDestroy:
        {
        }
        ;
        break;
    case opRead:
        {
            TBaseSaveInfo *op1 = (TBaseSaveInfo*)P;
            op1->Stream->ReadData(code, sizeof(double));
        }
        ;
        break;
    case opWrite:
        {
            TBaseSaveInfo *op1 = (TBaseSaveInfo*)P;
            op1->Stream->WriteData(code, sizeof(double));
        }
        ;
        break;
    };
}

void CBaseObject::RBool(LPVOID P, bool* bvar, bool std, int fl, TCHAR* name)
{
    TBaseOperation* op = (TBaseOperation*)P;
    switch (op->Operation)
    {
    case opCreate:
        {
            *bvar =std;
        }
        ;
        break;
    case opDestroy:
        {
        }
        ;
        break;
    case opRead:
        {
            TBaseSaveInfo *op1 = (TBaseSaveInfo*)P;
            op1->Stream->ReadBoolean(*bvar);
        }
        ;
        break;
    case opWrite:
        {
            TBaseSaveInfo *op1 = (TBaseSaveInfo*)P;
            op1->Stream->WriteBoolean(*bvar);
        }
        ;
        break;
    };
}


//	SCode Code;
//	UINT Flags;
CBaseObject::CBaseObject(CUtiOB* parent) : CUtiOB()
{
    FParent = parent;
    Flags = 0;
    Code = createCode();
    TBaseOperation op;
    op.Operation = opCreate;
    GetTypeInfo(&op, opCreate, 0, 0);
}

CBaseObject::~CBaseObject()
{

    TBaseOperation op;
    op.Operation = opDestroy;
    GetTypeInfo(&op, opDestroy, 0, 0);
}

HResult CBaseObject::Read(CStream & Stream, int Flags, int version)
{
    Stream.ReadInteger(this->Flags);
    //Stream.ReadData(&Code, sizeof(Code));
    ReadCode(Stream, Code, version);
    TBaseSaveInfo op;
    op.Operation = opRead;
    op.Stream = &Stream;
    op.Flags = Flags;
    op.version = version;
    GetTypeInfo(&op, opRead, Flags, version);
    return 0;
}
HResult CBaseObject::Write(CStream & Stream, int Flags, int version)
{
    Stream.WriteInteger(this->Flags);
    Stream.WriteData(&Code, sizeof(Code));
    TBaseSaveInfo op;
    op.Operation = opWrite;
    op.Stream = &Stream;
    op.Flags = Flags;
    op.version = version;
    GetTypeInfo(&op, opWrite, Flags, version);
    return 0;
}

CUtiOB* CBaseObject::GetParent()
{
    return FParent;
}
CUtiOB* CBaseObject::SearchObj(SCode code)
{
    return NULL;

}

UINT UTIRGB(unsigned char r, unsigned char g, unsigned char b)
{
    return r | g << 8 | b << 16;
}

typedef set
    <CUtiOB*>::iterator iter;

void DumpMemory()
{
#ifdef USEMEMDUMP
    ofstream printout("memdump.txt");
    for (iter i = UtiOBInstanceObj.begin(); i != UtiOBInstanceObj.end(); i++)
    {
        CUtiOB* ob = *i;
        printout << typeid(*ob).name() << "\n";
    }
#endif
}
