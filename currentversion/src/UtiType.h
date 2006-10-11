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

#ifndef __UTITYPE__
#define __UTITYPE__

#include <string>
#include <vector>
#include <map>
using namespace std;

//#include "Uti3DCore.h"
#include "Uti3DMath.h"
#include "UtiString.h"



const int TYPE_STREAM = 1;
const int TYPE_EXPOSE = 2;


class CXDocument;
class CXNode;

class CUtiException
{
public:
  CUtiString n;
  CUtiException();

};

class CClassRTTI : public CUtiOB
{
public:
  virtual const SCode GetCode(){return NULLCODE;};
  virtual CUtiOB* CreateClass(CUtiOB* Parent){return NULL;};
  virtual const CUtiString getName();
};

class CCallClass : public CClassRTTI
{
public:
  CUtiOB* (UTICDECL *create )(CUtiOB* Parent);
  SCode Code;
  CCallClass(CUtiOB* (UTICDECL *_create)(CUtiOB* Parent), SCode cd) : CClassRTTI()
  {
    Code = cd;
    create = _create;
  };
  virtual const SCode GetCode(){return Code;};
  virtual CUtiOB* CreateClass(CUtiOB* Parent){return create(Parent);};
  virtual const CUtiString getName();
};

class CRTTIManager : public CUtiOB
{
public:
  CCacheList classes;
  map<SCode, CClassRTTI*> clmap;
  CRTTIManager();
  ~CRTTIManager();
  void AddRTTI(CClassRTTI* cl, LPVOID Data);
  CUtiOB* CreateClass(SCode code, CUtiOB* parent);

};


extern CRTTIManager rttimanager;

class CTypeInterface : public CUtiOB
{
public:
  virtual void RInt(int &i, int std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a){};
  virtual void RByte(unsigned char &i, unsigned char std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a){};
  virtual void REnum(unsigned char &i, unsigned char std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a){};
  virtual void RFloat(float &i, float std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a){};
  virtual void RDouble(double &i, double std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a){};
  virtual void RVector(CVector &i, CVector std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a){};
  virtual void RColor(SVector4 &i, SVector4 std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a){};
  virtual void RCode(SCode &i, SCode std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a){};
  virtual void RReference(CUtiOB* &i, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a){};
  virtual void RObject(CUtiOB &i, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a){};
  //	virtual void RObject(CUtiOB* &i, int std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a){};
  virtual void RBool(bool &i, bool std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a){};
  virtual void RString(CUtiString &i, TCHAR* std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a){};
  virtual void RObjectList(CCacheList &i, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a){};
  virtual void RObjectOwns(CUtiOB* &i,  int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a){};
};

class CXWriteInterface : public CTypeInterface
{
public:
  CXNode* n;
  CWriteReadInterface* wri;
  static void Perform(CUtiOB* obj, CXNode* n, CWriteReadInterface* wri);
  CXWriteInterface(CXNode* n, CWriteReadInterface* wri);
  void RInt(int &i, int std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a);
  void RByte(unsigned char &i, unsigned char std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a);
  void REnum(unsigned char &i, unsigned char std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a);
  void RFloat(float &i, float std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a);
  void RDouble(double &i, double std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a);
  void RVector(CVector &i, CVector std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a);
  void RColor(SVector4 &i, SVector4 std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a);
  void RCode(SCode &i, SCode std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a);
  void RReference(CUtiOB* &i, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a);
  void RObject(CUtiOB &i,  int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a);
  void RBool(bool &i, bool std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a);
  void RString(CUtiString &i, TCHAR* std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a);
  void RObjectList(CCacheList &i, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a);
  void RObjectOwns(CUtiOB* &i,  int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a);
};



class CXReadInterface : public CTypeInterface
{
public:
  CXNode* n;
  CWriteReadInterface* wri;
  static void Perform(CUtiOB* obj, CXNode* n, CWriteReadInterface* wri);
  CXReadInterface(CXNode* n, CWriteReadInterface* wri);
  void RInt(int &i, int std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a);
  void RByte(unsigned char &i, unsigned char std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a);
  void REnum(unsigned char &i, unsigned char std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a);
  void RFloat(float &i, float std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a);
  void RDouble(double &i, double std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a);
  void RVector(CVector &i, CVector std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a);
  void RColor(SVector4 &i, SVector4 std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a);
  void RCode(SCode &i, SCode std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a);
  void RReference(CUtiOB* &i, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a);
  void RObject(CUtiOB &i,int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a);
  void RBool(bool &i, bool std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a);
  void RString(CUtiString &i, TCHAR* std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a);
  void RObjectList(CCacheList &i, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a);
  void RObjectOwns(CUtiOB* &i,  int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a);
};

class CWriteReadInterface : public CUtiOB
{
public:
  CWriteReadInterface(): CUtiOB(){};

};

void XWriteClass(CXNode* n, LPVOID wri, CUtiOB* cl);
CUtiOB* XReadClass(CXNode* n, LPVOID wri, CUtiOB* parent);
void XSaveToFile(TCHAR* string, CUtiOB* cl);
CUtiOB* XLoadFromFile(TCHAR* string, CUtiOB* parent);

class CLinkInfo : public CUtiOB
{
public:
  CUtiOB** obj;
  SCode code;
};
/*
class CObjInfo : public CUtiOB
{
public:
  CUtiOB* obj;
  SCode code;
};
*/
class CReadInfo : public CWriteReadInterface
{
public:
  CCacheList links;
  //CCacheList ObjList;
  map<SCode, CUtiOB*> objmap;
  CReadInfo();
  ~CReadInfo();
  void AddLink(CUtiOB** obj, SCode code);
  void AddObject(CUtiOB* obj, SCode code);
  void Link();
};

class CXNode : public CUtiOB
{
protected:
  CXDocument* doc;
  CXNode* parent;
public:
  CXNode(CXNode* parent, CXDocument* doc);
  virtual void setName(TCHAR* name){};
  virtual const CUtiString getName(){return L"";};
  virtual void setPropBool(TCHAR* name, const bool b){};
  virtual const bool getPropBool(TCHAR* name, const bool std){return std;};
  virtual void setPropInt(TCHAR* name, const int b){};
  virtual const int getPropInt(TCHAR* name, const int std){return std;};
  virtual void setPropFloat(TCHAR* name, const float b){};
  virtual const float getPropFloat(TCHAR* name, const float std){return std;};
  virtual void setPropDouble(TCHAR* name, const double b){};
  virtual const double getPropDouble(TCHAR* name, const double std){return std;};
  virtual void setPropCode(TCHAR* name, const SCode b){};
  virtual const SCode getPropCode(TCHAR* name, const SCode std){return std;};
  virtual void setPropVector(TCHAR* name, const CVector b){};
  virtual const CVector getPropVector(TCHAR* name, const CVector std){return std;};
  virtual void setPropColor(TCHAR* name, const SVector4 b){};
  virtual const SVector4 getPropColor(TCHAR* name, const SVector4 std){return std;};
  virtual void setPropString(TCHAR* name, TCHAR* b){};
  virtual const CUtiString getPropString(TCHAR* name, const TCHAR* std){return std;};
  virtual void setPropData(TCHAR* name, unsigned char* Data, size_t size){};
  virtual bool getPropData(TCHAR* name, unsigned char* &Data, size_t &size){return false;};
  virtual bool PropExists(TCHAR* name){return false;};
  virtual HResult Read(CStream & Stream, int Flags, int version){return 0;};
  virtual HResult Write(CStream & Stream, int Flags, int version){return 0;};
  virtual CXNode* AddNode(TCHAR* name){return NULL;};
  virtual CXNode* GetNodeByName(TCHAR* name){return NULL;};
  virtual void DeleteNode(TCHAR* name){};
  virtual void Delete(int i){};
  virtual void Remove(CXNode* n){};
  virtual int GetChildCount(){return 0;};
  virtual CXNode* GetChild(int i){return NULL;};
  virtual void ClearNodes(){};
  virtual void ClearProperties(){};
};

class CBaseProp : public CUtiOB
{
public:
  int id;
};

class CStringProp : public CBaseProp
{
public:
  CUtiString b;
};

class CBoolProp : public CBaseProp
{
public:
  bool b;
};

class CIntProp : public CBaseProp
{
public:
  int b;
};

class CFloatProp : public CBaseProp
{
public:
  float b;
};

class CDoubleProp : public CBaseProp
{
public:
  double b;
};

class CCodeProp : public CBaseProp
{
public:
  SCode b;
};

class CVectorProp : public CBaseProp
{
public:
  CVector b;
};

class CColorProp : public CBaseProp
{
public:
  SVector4 b;
};

class CDataProp : public CBaseProp
{
public:
  int size;
  unsigned char* data;
  CDataProp();
  ~CDataProp();
};

class CUtiTypeException : public CUtiException
  {}
;

const int X_STRING = 1;
const int X_DATA = 2;
const int X_BOOL = 3;
const int X_CODE = 4;
const int X_COLOR = 5;
const int X_INT = 6;
const int X_DOUBLE = 7;
const int X_SINGLE = 8;
const int X_VECTOR = 9;

class CXUtiNode : public CXNode
{
public:
  CCacheList Nodes;
  CCacheList Properties;
  map <int, CBaseProp*> prophash;
  map <int, CXUtiNode*> nodehash;
  int Name;
  CBaseProp* FindPropByIndex(int x);
  CXUtiNode(CXNode* parent, CXDocument* doc);
  virtual void setName(TCHAR* name);
  virtual const CUtiString getName();
  virtual void setPropBool(TCHAR* name, const bool b);
  virtual const bool getPropBool(TCHAR* name, const bool std);
  virtual void setPropInt(TCHAR* name, const int b);
  virtual const int getPropInt(TCHAR* name, const int std);
  virtual void setPropFloat(TCHAR* name, const float b);
  virtual const float getPropFloat(TCHAR* name, const float std);
  virtual void setPropDouble(TCHAR* name, const double b);
  virtual const double getPropDouble(TCHAR* name, const double std);
  virtual void setPropCode(TCHAR* name, const SCode b);
  virtual const SCode getPropCode(TCHAR* name, const SCode std);
  virtual void setPropVector(TCHAR* name, const CVector b);
  virtual const CVector getPropVector(TCHAR* name, const CVector std);
  virtual void setPropColor(TCHAR* name, const SVector4 b);
  virtual const SVector4 getPropColor(TCHAR* name, const SVector4 std);
  virtual void setPropString(TCHAR* name, TCHAR* b);
  virtual const CUtiString getPropString(TCHAR* name, const TCHAR* std);
  virtual void setPropData(TCHAR* name, unsigned char* Data, size_t size);
  virtual bool getPropData(TCHAR* name, unsigned char* &Data, size_t &size);
  virtual bool PropExists(TCHAR* name);
  virtual HResult Read(CStream & Stream, int Flags, int version);
  virtual HResult Write(CStream & Stream, int Flags, int version);
  virtual CXNode* AddNode(TCHAR* name);
  virtual CXNode* GetNodeByName(TCHAR* name);
  virtual void DeleteNode(TCHAR* name);
  virtual void Delete(int i);
  virtual void Remove(CXNode* n);
  virtual int GetChildCount();
  virtual CXNode* GetChild(int i);
  virtual void ClearNodes();
  virtual void ClearProperties();
};

class CXDocument : public CUtiOB
{
public:
  CXNode* root;
  CXDocument();
  ~CXDocument();
  virtual void SaveToStream(CStream &Stream){};
  virtual void LoadFromStream(CStream &Stream){};
  virtual void SaveToFile(TCHAR* name){};
  virtual void LoadFromFile(TCHAR* name){};
};

class CXName : public CUtiOB
{
public:
  int ref;
  CUtiString name;
};

class CXUtiDocument : public CXDocument
{
public:
  CCacheList strlist;
  //hash_map <wstring, int> listindex;
  map <wstring, int> listindex;
  CXUtiDocument();
  ~CXUtiDocument();
  int AddString(TCHAR*s);
  void RemoveString(TCHAR*id);
  void RemoveIndex(int index);
  void IncIndex(int index);
  int FindString(TCHAR* s);
  const CUtiString GetString(int id);
  virtual void SaveToStream(CStream &Stream);
  virtual void LoadFromStream(CStream &Stream);
  virtual void SaveToFile(TCHAR* name);
  virtual void LoadFromFile(TCHAR* name);
};

#endif
