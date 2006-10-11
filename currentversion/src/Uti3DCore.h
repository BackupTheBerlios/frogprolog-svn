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
//Definition der Basisklassen
#ifndef __UTI3DCORE__
#define __UTI3DCORE__

//#define EDITOR

#include "gdef.h"

#include "utichar.h"
#include <iostream>
#ifndef _UNICODE
#define _UNICODE
#endif

using namespace std;

#define PRINT(a) a

#define UTI_OK 0
#define UTI_READERROR 1001
#define UTI_ERROR_SAME_CLASS 1000 //Wenn assign mit derselben Klasse aufgerufen wird
//#define CREATENETWORK
#define HResult unsigned int
/*#ifndef LPVOID
#define LPVOID void*
#endif*/
typedef void *LPVOID;
typedef unsigned int UINT;
typedef unsigned short USHORT;

#define U_INT32 int
#define U_UINT32 unsigned int
#define U_INT16 short int
#define U_UINT16 unsigned short int
#define U_SINGLE float
#define U_DOUBLE double
#define U_CHAR TCHAR
#define U_SCHAR char
typedef unsigned char UCHAR;
//#include <stdiostr.h>
//#define byte unsigned cdeclarationhar
#define RGB_MAKE(r, g, b)    ((UINT) (((r) << 16) | ((g) << 8) | (b)))
#define RGB_GETRED(rgb)    (((rgb) >> 16) & 0xff)
#define RGB_GETGREEN(rgb)    (((rgb) >> 8) & 0xff)
#define RGB_GETBLUE(rgb)    ((rgb) & 0xff)

#define S_SHIFT 16
#define S_MULT 65536.0f

#define S_READ 0
#define S_WRITE 1
const float PI =3.1415926535897932384626433832795f;
#define UTEXT(a) L##a


const int UTI_UTIOB = 0;
const int UTI_ANIMATION = 100;
const int UTI_ANIMATIONINFO = 200;
const int UTI_ANIMATIONCLASS = 300;
const int UTI_ANIPOINT = 400;
const int UTI_ANIDOUBLEPOINT = 500;
const int UTI_ANIORDERPOINT = 700;
const int UTI_DOUBLECLASS  = 600;
const int UTI_POLYGON = 1;
const int UTI_GROUP = 2;
const int UTI_JOINT = 0x100000;
const int UTI_HANGIN = 0x200000;

const int UTI_CONTENT = 0x1000;
const int UTI_ANALYTICALOBJECT = 0x80000;
const int UTI_DUPLICATE = 0x8000;
const int  UTI_CREATEITEMS =0x20000;
const int  UTI_RECREATE = 0x40000;
const int  UTI_PHYSIKINFO = 0x80000;
const int  UTI_LEVEL =    0x100000;
const int  UTI_NOPROZESS =    0x10000000;
const int  UTI_LOD = 0x40000000;

const int UTI_CLOSED = 0x10000;
const int UTI_CLONE = 0x2000;
const int UTI_GROUPSELECTED =0x4000;
const int UTI_EDIT = 9;
const int UTI_SCROLLBAR = 10;
const int UTI_BUTTON = 11;
const int UTI_TREEVIEW = 12;
const int UTI_STRING = 13;
const int UTI_CAMERA = 14;
const int UTI_WORLD = 15;
const int UTI_ITEMS = 16;
const int UTI_ENGINE = 17;
const int UTI_UTILIST = 18;
const int UTI_ANIMATIONLIST = 19;
const int UTI_ANIMATIONMANAGER = 20;
const int UTI_LINE = 21;
const int UTI_LIGHT = 8;
const int UTI_MENUITEM = 23;
const int UTI_SPRITEEFFECT = 30;
const int UTI_GLOWEFFECT = 31;
const int UTI_LINEEFFECT = 32;
const int UTI_CIRCLEEFFECT = 33;
const int UTI_MODELEFFECT = 34;
const int UTI_PARTICLEEFFECT = 35;
const int UTI_DECALEFFECT = 36;
const int UTI_SOUNDEFFECT = 37;
const int UTI_TEXT = 128;
const int UTI_SOUND = 0x0040;
const int UTI_3DTRIPLE = 38;
const int UTI_4DQUATRE = 39;
const int UTI_CSYSTEM = 41;
const int UTI_TERRAIN = 42;
const int UTI_LSYSTEM = 0x10000;
const int UTI_NURBSSURFACE = 43;
const int UTI_ROTATIONEFFECT = 44;
const int UTI_TRIMODEL = 45;
const int UTI_NURBSCURVE = 46;
const int UTI_CLOTHEFFECT = 47;
const int UTI_FORM = 1045;
const int UTI_CHECKBOX = 48;
const int UTI_WELLENEFFECT = 49;

const int PF_MULTITEXTURE = 0x0001;
const int PF_USEMATRIX = 0x0002;
const int PF_DECALTYPMASK = 0x0004+0x0008;
const int PF_FLATDECAL = 0x0004;
const int PF_NODEEPDECAL = 0x0008;
const int PF_MOVEPOLYGON = 0x0008+0x0004;
const int PF_USENOLIGHT = 0x0010;
const int PF_INVISIBLE = 0x0020;
const int PF_GAMETEXTURE = 0x0040;
const int PF_SPRITE = 0x0080;
const int PF_LIGHTMAP = 0x0100;
const int PF_COLOR = 0x0200;
const int PF_BLEND = 0x0400;
const int UTI_INVISIBLE = 0x0010;
const int UTI_NOHIT = 0x0040;
const int UTI_GROUPTEXTURE = 0x0080;
const int UTI_ShowTrace = 0x0080;
const int UTI_TEXTURETRANSFORMATION = 0x400000;
const int UTI_SCRIPT = 0x80000000;
const int OBJ_PROZESSUPDATE = 0x00800000;
const int stParentMatrix = 0x0001;
const int LINK_WORLD = 0x0001;
const int LINK_SMOOTH = 0x0002;
const int LINK_LOOKATNULL = 0x0004;
const int LIGHT_CREATESHADOWS = 1;
const int UTI_USEMATRIX = 0x0020;

const int TRI_FLAT = 4;


UINT UTIRGB(unsigned char r, unsigned char g, unsigned char b);
//#define abs(x) ((x) >= 0 ? (x) : -(x))

//#ifndef min
#define umin(a,b) ((a) <= (b) ? (a) : (b))
#define umax(a,b) ((a) >= (b) ? (a) : (b))
//#endif


#ifdef _UNICODE
#ifndef UNICODE
#define UNICODE
#endif

#endif

const float PAlpha = 0.01f;
const float NAlpha = 0.001f;
//typedef signed INT64   *PINT64;

#ifdef _DEBUG
#define utiassert(a) if (!(a)) { doutiassert(UTEXT(#a), __FILE__, __LINE__, __DATE__); };
#define utiassert2(a, b) if (!(a)) { doutiassert(UTEXT(#a), __FILE__, __LINE__, __DATE__); };
#else
#define utiassert(a) ;
#define utiassert2(a, b) ;
#endif
void doutiassert(TCHAR* expression, char* file, int line, char* date);
int ToPower2(int i);
void ForceDir(TCHAR* path);
void zeromem(LPVOID l, int count);
void DumpMemory();

class CUtiOB;
class CStream;
class CUtiString;

#ifdef _WIN32
#define UINT64VALUE(a) a
#define swprintf _snwprintf
#else
#define UINT64VALUE(a) a ## ULL 

#endif

typedef struct Chunk_Str
{
    char ckID[10];
    int ckSize;
}
SChunkStr, *PChunkStr;

//typedef hash_map <LPVOID, int> hash_di;
//typedef pair <LPVOID, int> di_pair;

#define GetAValue(a) (a >> 24)

/*struct SCode
{
	int low, high;
};*/

//#define SCode __int64

typedef GUID SCode;
typedef SCode TCode;
// {28CB7626-DEE5-454a-9759-30908816E33D}
static const SCode NULLCODE =
    {
        0x00000000, 0x0000, 0x0000, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
    };

// {28CB7626-DEE5-454a-9759-30908816E33D}
static const GUID STDMAT =
    {
        0x8BEF00B1, 0x836E, 0x4B89, { 0xB2, 0xD9, 0x88, 0x2F, 0xE4, 0xE9, 0x10, 0xE1 }
    };


int urandom(int max);
//define urandom(max) (rand() % max)
float urandom();
const SCode createCode();
const SCode IntToCode(int i);
const int CodeToInt(const SCode i);

struct SString20
{
    unsigned char length;
    TCHAR name[20];
};


float sqr(float d);
bool compareCode(SCode c1, SCode c2);
int compare(float a, float b);
bool PtInRectE(float x, float y, float x1, float y1, float x2, float y2);
bool FileExists(TCHAR* name);
INT64 FileSize(U_CHAR*name);
int UtiGetRValue(int color);
int UtiGetGValue(int color);
int UtiGetBValue(int color);
int UtiRGB(int r, int g, int b);
void ShowMessage(wchar_t* text);

#define SETRANGE(a, b, c) if (a < b) a = b; if (a > c) a = c;

typedef struct NODE_TYP
{
    CUtiOB * data;
    float value;
    NODE_TYP* next;
    NODE_TYP* prev;
}
NODE, *NODE_PTR;

struct SProzess
{   int type;
    float time;
    UINT l;   
};

typedef struct _RECT
{
    long left;
    long top;
    long right;
    long bottom;
}
UTIRECT, *PUTIRECT;


struct SVector4
{
    float x;
    float y;
    float z;
    float a;
};

struct SVector3
{
    float x;
    float y;
    float z;
};

SVector4 setVector4(float x, float y, float z, float w);
void NormRect(UTIRECT &r);

struct SLightRec
{
    bool active;
    SVector4 Ambient, Diffuse, Specular, Position;
    SVector3 SpotDirection;
    float SpotExponent;
    float SpotCutOff;
    float ConstantAttenuation;
    float LinearAttenuation;
    float QuadraticAttenuation;
};

typedef struct SMatRec_Typ
{
    SCode Material;
    CUtiOB* MaterialP;
    int UsePoints;
    float Points[4][3];
    SMatRec_Typ* next;
}
SMatRec, *PMatRec;


struct SMultiRec
{
    int count;
    SMatRec mat;
    CUtiOB* MaterialP;
    int UsePoints;
    void* plane;
    unsigned char lightmapsize;
    unsigned short lightmapflags;
    unsigned char* lightmap;
    UINT textureinfo;

};


void CheckFileName(TCHAR* c);

void Fehler(TCHAR* s);

//typedef CUTILISTCALLBACK void (NODE_PTR, bool)
bool Writefunc(NODE_PTR node, void* data);

enum {OnClick, OnDblClick, OnChange, OnScroll, OnCreate, OnActivate, OnDeactivate, OnOpenGLInit, OnClose, OnDestroy, OnMove, OnMouseMove, OnMouseDown, OnMouseUp, OnKeyUp, OnKeyDown, OnPaint, OnQuit, OnSize,
      OnExpanding, OnCollapsing, OnExpanded, OnSelChanged, OnSelChanging, OnCollapsed, OnIdle, OnKeyPress};

typedef UINT SColor;

struct SUtiBTreeNode
{
    void *data;
    void *low;
    void *high;
};

class CUtiBTree
{
    SUtiBTreeNode* mainnode;

};


class CStream
{
public:
    int count;
    bool docount;
    void BeginCount()
    {
        docount = true;
        count = 0;
    };
    void EndCount()
    {
        docount = false;
    };
    virtual void setPosition(UINT i);
    virtual UINT getReadPosition()
    {
        return(0);
    };
    virtual UINT getWritePosition()
    {
        return(0);
    };
    virtual bool eof()
    {
        return(true);
    };
    virtual bool fail()
    {
        return(false);
    };
    void ReadDouble(double &d);
    void WriteDouble(double d);
    void ReadFloat(float &f);
    void WriteFloat(float f);
    void ReadInteger(int &i);
    void WriteInteger(int i);
    void ReadBoolean(bool &b);
    void WriteBoolean(bool b);
    virtual void ReadData(void* data, unsigned int size);
    virtual void WriteData(const void* data, unsigned int size);
	unsigned int Read(void* data, unsigned int size) {
		ReadData(data, size); return size;};
    unsigned int Write(void* data, unsigned int size) {
		WriteData(data, size); return size;};
  virtual ~CStream(){};
};

class CFileStream : public CStream
{
public:
    ~CFileStream();
    CFileStream(TCHAR *name, int i, bool trunc=true);
    LPVOID strm;
    bool iswrite;
    bool fail();
    bool eof();
    void ReadData(void* data, unsigned int size);
    void WriteData(const void* data, unsigned int size);
	
    void setPosition(UINT i);
    UINT getReadPosition();
    UINT getWritePosition();
};

class CMemoryStream : public CStream
{
public:
    LPVOID Memory;
    int Size;
    bool failed;
    int Position;
    CMemoryStream();
    ~CMemoryStream();
    bool fail()
    {
        return(failed);
    };
    bool eof()
    {
        return(Position == Size);
    };
    void ReadData(void* data, unsigned int size);
    void WriteData(const void* data, unsigned int size);
    void setPosition(UINT i);
    UINT getReadPosition();
    UINT getWritePosition();
    void LoadFromFile(TCHAR*c);
};

class CTypeInterface;
class CXNode;
class CWriteReadInterface;

class CUtiOB
{
public:
    CUtiOB();
#ifdef EDITOR

    UINT TreeItem;
    void *v;
    virtual void AddTreeItem(void* view, UINT parent, TCHAR *c);
    virtual void DeleteItem(void* view);
#endif

    int typinfo;
    virtual ~CUtiOB();
    HResult Assign(CUtiOB*ob, int flags);
	virtual CUtiOB* CreateCopy() {return NULL;};
	virtual wchar_t* GetName(){return NULL;};
	virtual CUtiOB* GetParent() {return NULL;};
	virtual bool HasParent(CUtiOB* ob) {return false;};
    virtual int getWeighti()
    {
        return 0;
    };
    virtual void TypeInfo(CTypeInterface* type)
    {};
    virtual const SCode GetTypeCode()
    {
        return NULLCODE;
    };
    virtual const SCode GetCode()
    {
        return NULLCODE;
    };
    virtual HResult Read(CStream & Stream, int Flags, int version);
    virtual HResult Write(CStream & Stream, int Flags, int version);
	void Read(CStream * Stream, int Flags, int version){Read(*Stream, Flags, version);};
    void Write(CStream * Stream, int Flags, int version){Write(*Stream, Flags, version);};
    virtual void xread(CXNode* n, CWriteReadInterface* wri);
    virtual void xwrite(CXNode* n, CWriteReadInterface* wri);
    virtual int GetMessageUti(CUtiOB *Sender, int msg, int lParam, int wParam, bool &handled);
};

template <class T>
class Array : public CUtiOB
{
protected:
    bool dynamic;
public:
    T* array;
    int array_size;
    void isDynamic()
    {
        return dynamic;
    }
    int size()
    {
        return array_size;
    }
    Array(int size) : CUtiOB()
    {
        dynamic = true;
        array_size = size;
        array = new T[array_size];
    }
    Array(T* ar, int size): CUtiOB()
    {
        dynamic = false;
        array_size = size;
        array = ar;
    }
    Array(const Array &narray);
    ~Array()
    {
        if (dynamic)
            delete [] array;
    }
    void ReferenzTo(const Array &a)
    {
        dynamic = false;
        array_size = a.array_size;
        array = a.array;
    }
    T &operator[](unsigned int p)
    {
        utiassert(p >= 0 && p < (unsigned int)array_size);
        return array[p];

    }
    const T &operator[](unsigned int p) const
    {
        utiassert(p >= 0 && p < array_size);
        return array[p];

    }
    // Array& operator=(const Array & str);


};


template <class T>
Array<T>::Array(const Array &narray) : CUtiOB()
{
    dynamic = true;
    array_size = array.size();
    array = new T[array_size];
    wcout << "Warnung: Array wird kopiert"<<endl;
    for (int i = 0; i < array_size; i++)
    {
        array[i] = array[i];

    }

}

typedef Array<unsigned char> ArrayUC;

class CMemManager : public CUtiOB
{
public:
    bool locked;
    void* data;
    int datasize;
    int fileindex;
    CMemManager();
    CMemManager(int datasize);
    ~CMemManager();
    void Init(int datasize);
    void Lock();
    void Unlock();
    void Free();
    void GetFilename(TCHAR* c);
};

class CMemController : public CUtiOB
{
public:
    CMemController(): CUtiOB()
    {}
    ;
    ~CMemController()
    {}
    ;
    virtual void FreeMemory(CUtiOB* ob);
};
class CUtiList : public CUtiOB
{
public:
    CMemController* MemController;
    void CheckArray(int count);
    void GetObjectByValue(float value, CUtiOB* &obj);
    void GetObjects(float value, CUtiOB* &First, CUtiOB* &Next);
    void Swapitems(NODE_PTR f1, NODE_PTR f2);
    void sortItems();
    CUtiOB* getItem(int i);
    NODE_PTR getNode(int i);
    int indexof(CUtiOB* obj);
    void EnumItems(void *data, bool (*enumfunc) (NODE_PTR, void*));
    NODE_PTR indexofNode(CUtiOB *obj);
    void Clear();
    void Delete(NODE_PTR node);
    void Delete(CUtiOB *data);
    NODE_PTR Add(CUtiOB *data, float value);
    void AddList(CUtiList *list);
    bool sorted;
    bool deleteItems;
    int count;
    NODE_PTR GetFirstItem();
    bool GetNextPointer(NODE_PTR &node);
    NODE_PTR first;
    NODE_PTR last;
    CUtiList();
    ~CUtiList();
    HResult Read(CStream & Stream, int Flags, int version, CUtiOB* ( *enumfunc)(CUtiOB* parent, int type), CUtiOB* parent);
    HResult Write(CStream & Stream, int Flags, int version);
protected:

};



class CCacheList : public CUtiOB
{
protected:
    virtual LPVOID* ReserveMem(int count);
    virtual void FreeMem(LPVOID vd);
    void ValidNewSize(int newcount);
    virtual void FreeItem(LPVOID* item);
public:
    LPVOID *pointers;
    int count;
    int capacity;
    int inc;
    bool deleteItems;
    CMemController* MemController;
    CCacheList();
    ~CCacheList();
    void Clear();
    //LPVOID &operator[](unsigned int p);
    //const LPVOID &operator[](unsigned int p) const;
    inline LPVOID &operator[](unsigned int p)
    {
       utiassert(p >= 0 && p < (unsigned int)count);
       return pointers[p];
    }
    inline const LPVOID &operator[](unsigned int p) const
    {
       utiassert(p >= 0 && p < (unsigned int)count);
        return pointers[p];
    }
    virtual void Add(LPVOID item);

    void AddList(CCacheList* list);
    void AddList(CUtiList* list);
    virtual void Delete(int index);
    void Remove(LPVOID item);
    void Extract(int index);
	void Extract(LPVOID item);
    void RemoveExtract(LPVOID item);
    int IndexOf(LPVOID item);
    void Move(int source, int dest);
    void Insert(LPVOID item, int index);
    void Pack();
    void SetNewSize(int size);
    void Sort(int (UTICDECL *compare )(const void *elem1, const void *elem2 ));
    HResult Read(CStream & Stream, int Flags, int version, CUtiOB* (UTICDECL *enumfunc)(CUtiOB* parent, int type), CUtiOB* parent);
    HResult Write(CStream & Stream, int Flags, int version);

};

typedef CCacheList CList;


class CHeapList : public CCacheList
{
protected:
    inline int GetItemWeighti(int i);
    inline int getParent(int k);
    void upheap(int item);
    void downheap(int item);
public:

    void Add(LPVOID item);
    void Delete(int index);
};

const int UTI_MEM_SIZE =256;

class CMemoryManager : public CUtiOB
{
public:
    virtual CUtiOB* CreateObject()
    {
        return(NULL);
    };
    CUtiOB* Buffer[UTI_MEM_SIZE];
    CUtiOB* GetObjectUti();
    void FreeObject(CUtiOB* ob);
    void Put(CUtiOB* ob);
    virtual void DoFree(CUtiOB* ob)
    {}
    ;
    virtual void DoInit(CUtiOB* ob)
    {}
    ;
    CMemoryManager();
    ~CMemoryManager();
};

class CThread : public CUtiOB
{
protected:
    LPVOID thread;
    bool init;
    int KillThread(); // Eigentlich nicht noig, da return in Execute dasselbe bewirkt
public:
    void IsReady();
    bool ToTerminate;
    virtual void Execute();
    void Terminate();
    CThread();
    ~CThread();
    int WaitFor();


};

class CCriticalSection : public CUtiOB
{
protected:
    //CRITICAL_SECTION cs;
    LPVOID cs;
public:
    CCriticalSection();
    ~CCriticalSection();
    void Enter();
    void Leave();
	bool tryEnter();
};

class CUtiEvent : public CUtiOB
{
protected:
    LPVOID Event;
public:

    CUtiEvent(bool initstate, TCHAR* Name, bool WaitForDoesReset);
    ~CUtiEvent();
    void Activate();
    void Deactivate();
    int WaitFor(int timeout);
};

class CPersistentMem : public CUtiOB
{
public:
    LPVOID data;
    int datasize;
    CPersistentMem();
    HResult Read(CStream & Stream, int Flags, int version);
    HResult Write(CStream & Stream, int Flags, int version);
};

class CPersistent : public CUtiOB
{
public:
    CCacheList list;
    CPersistent();
    void AddMem(LPVOID data, int datasize);
    HResult Read(CStream & Stream, int Flags, int version);
    HResult Write(CStream & Stream, int Flags, int version);
    void SaveToFile(TCHAR* filename);
    void LoadFromFile(TCHAR* filename);
};

void WriteCode(CStream &Stream, SCode code, int version);
void ReadCode(CStream &Stream, SCode &code, int version);

enum TBaseObjOperation  {opCreate, opDestroy, opRead, opWrite, opSearch};
struct TBaseOperation
{
    TBaseObjOperation Operation;
};
struct TBaseSaveInfo
{
    TBaseObjOperation Operation;
    CStream* Stream;
    int Flags;
    int version;

};

class CBaseObject : public CUtiOB
{
protected:
    CUtiOB* FParent;
    virtual void GetTypeInfo(LPVOID P, TBaseObjOperation Operation, int readFlags, int version);
    void RString(LPVOID P, LPVOID str, TCHAR* std, int fl, TCHAR* name);
    void RInt(LPVOID P, int* value, int std, int fl, TCHAR* name);
    void RFloat(LPVOID P, float* value, float std, int fl, TCHAR* name);
    void RDouble(LPVOID P, double* value, double std, int fl, TCHAR* name);
    void RVector(LPVOID P, LPVOID vector, float stdx, float stdy, float stdz, int fl, TCHAR* name);
    void RVectorList(LPVOID P, CCacheList *vlist, int fl, TCHAR* name);
    void RClassList(LPVOID P, CCacheList *classlist, int fl,CUtiOB* (UTICDECL *createfunc)(CUtiOB* parent), TCHAR* name);
    void RMultiClassList(LPVOID P, CCacheList *classlist, int fl,CUtiOB* (UTICDECL *createfunc)(CUtiOB* parent, UINT type), TCHAR* name);
    void RClass(LPVOID P, CUtiOB** ob, int fl, CUtiOB* (UTICDECL *createfunc)(CUtiOB* parent),TCHAR* name);
    void RCode(LPVOID P, SCode * code, bool zero, int fl, TCHAR* name);
    void RDate(LPVOID P, double * code, double std, int fl, TCHAR* name);
    void RBool(LPVOID P, bool* bvar, bool std, int fl, TCHAR* name);
public:
    SCode Code;
    int Flags;
    CBaseObject(CUtiOB* parent);
    ~CBaseObject();
    HResult Read(CStream & Stream, int Flags, int version);
    HResult Write(CStream & Stream, int Flags, int version);
    virtual CUtiOB* GetParent();
    virtual CUtiOB* SearchObj(SCode code);

};



#endif
