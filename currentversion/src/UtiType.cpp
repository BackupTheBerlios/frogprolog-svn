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

#include "Uti3DCore.h"
#include "Uti3DMath.h"
#include "UtiType.h"
#include "UtiArchiv.h"

CRTTIManager rttimanager;

CUtiException::CUtiException()
{
    n = L"";
};

const CUtiString CClassRTTI::getName()
{
    return L"";
};

const CUtiString CCallClass::getName()
{
    return L"";
};

void CXWriteInterface::Perform(CUtiOB* obj, CXNode* n, CWriteReadInterface* wri)
{
    CXWriteInterface* i = new CXWriteInterface(n, wri);
    obj->TypeInfo(i);
    delete i;
}

CXWriteInterface::CXWriteInterface(CXNode* n, CWriteReadInterface* wri)
{
    this->n = n;
    this->wri = wri;
}

void CXWriteInterface::RInt(int &i, int std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a)
{
    if (flags & TYPE_STREAM)
    {
        n->setPropInt(Name, i);
    }
}

void CXWriteInterface::RByte(unsigned char &i, unsigned char std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a)
{
    if (flags & TYPE_STREAM)
    {
        n->setPropInt(Name, i);
    }
}

void CXWriteInterface::REnum(unsigned char &i, unsigned char std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a)
{
    if (flags & TYPE_STREAM)
    {
        n->setPropInt(Name, i);
    }
}
void CXWriteInterface::RFloat(float &i, float std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a)
{
    if (flags & TYPE_STREAM)
    {
        n->setPropFloat(Name, i);
    }
}
void CXWriteInterface::RDouble(double &i, double std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a)
{
    if (flags & TYPE_STREAM)
    {
        n->setPropDouble(Name, i);
    }
}
void CXWriteInterface::RVector(CVector &i, CVector std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a)
{
    if (flags & TYPE_STREAM)
    {
        n->setPropVector(Name, i);
    }
}
void CXWriteInterface::RColor(SVector4 &i, SVector4 std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a)
{
    if (flags & TYPE_STREAM)
    {
        n->setPropColor(Name, i);
    }
}
void CXWriteInterface::RCode(SCode &i, SCode std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a)
{
    if (flags & TYPE_STREAM)
    {
        n->setPropCode(Name, i);
    }
}
void CXWriteInterface::RReference(CUtiOB* &i, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a)
{
    if (flags & TYPE_STREAM)
    {
       
       SCode c1;
       if (i) {
       c1 = i->GetCode();
       } else {
          c1 = NULLCODE;
       };
        n->setPropCode(Name, c1);
    }
}
void CXWriteInterface::RObject(CUtiOB &i, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a)
{
    if (flags & TYPE_STREAM)
    {
        CXNode* node = n->AddNode(Name);
        //t = XReadClass(node, wri, this);
        XWriteClass(node, wri, &i);
        //   i.xread(node, wri);
    }
}

void CXWriteInterface::RObjectOwns(CUtiOB* &i, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a)
{
   if (flags & TYPE_STREAM)
   {
      CXNode* node = n->AddNode(Name);

      XWriteClass(node, wri, i);

   }
}
void CXWriteInterface::RBool(bool &i, bool std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a)
{
    if (flags & TYPE_STREAM)
    {
        n->setPropBool(Name, i);
    }
}
void CXWriteInterface::RString(CUtiString &i, TCHAR* std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a)
{
    if (flags & TYPE_STREAM)
    {
        n->setPropString(Name, i.getString());
    }
}
void CXWriteInterface::RObjectList(CCacheList &i, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a)
{
    if (flags & TYPE_STREAM)
    {
        CXNode* node = n->AddNode(Name);
        node->setPropInt(Name, i.count);
        for (int l = 0; l < i.count; l++)
        {
            CXNode* subnode = node->AddNode(L"class");
            CUtiOB* ob = (CUtiOB*)i[l];
            XWriteClass(subnode, wri, ob);
        };
    };
}

void CXReadInterface::Perform(CUtiOB* obj, CXNode* n, CWriteReadInterface* wri)
{
    CXReadInterface* i = new CXReadInterface(n, wri);
    obj->TypeInfo(i);
    delete i;
}

CXReadInterface::CXReadInterface(CXNode* n, CWriteReadInterface* wri)
{
    this->n = n;
    this->wri = wri;
}

void CXReadInterface::RInt(int &i, int std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a)
{
    if (flags & TYPE_STREAM)
    {
        i = n->getPropInt(Name, std);
    }
}

void CXReadInterface::RByte(unsigned char &i, unsigned char std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a)
{
    if (flags & TYPE_STREAM)
    {
        i = n->getPropInt(Name, std);
    }
}

void CXReadInterface::REnum(unsigned char &i, unsigned char std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a)
{
    if (flags & TYPE_STREAM)
    {
        i = n->getPropInt(Name, std);
    }
}
void CXReadInterface::RFloat(float &i, float std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a)
{
    if (flags & TYPE_STREAM)
    {
        i = n->getPropFloat(Name, std);
    }
}
void CXReadInterface::RDouble(double &i, double std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a)
{
    if (flags & TYPE_STREAM)
    {
        i = n->getPropDouble(Name, std);
    }
}
void CXReadInterface::RVector(CVector &i, CVector std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a)
{
    if (flags & TYPE_STREAM)
    {
        i = n->getPropVector(Name, std);
    }
}
void CXReadInterface::RColor(SVector4 &i, SVector4 std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a)
{
    if (flags & TYPE_STREAM)
    {
        i = n->getPropColor(Name, std);
    }
}
void CXReadInterface::RCode(SCode &i, SCode std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a)
{
    if (flags & TYPE_STREAM)
    {
        i = n->getPropCode(Name, std);
    }
}
void CXReadInterface::RReference(CUtiOB* &i, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a)
{
    if (flags & TYPE_STREAM)
    {
        SCode code = n->getPropCode(Name, NULLCODE);
        if (compareCode(code, NULLCODE))
        {
            i = NULL;

        }
        else
        {
            dynamic_cast<CReadInfo*>(wri)->AddLink(&i, code);

        };
    }
}
void CXReadInterface::RObject(CUtiOB &i,  int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a)
{
    if (flags & TYPE_STREAM)
    {
        CXNode* node = n->GetNodeByName(Name);
        if (node)
        {
            //t = XReadClass(node, wri, this);
            i.xread(node, wri);
            dynamic_cast<CReadInfo*>(wri)->AddObject(&i, i.GetCode());

        };
    }
}

void CXReadInterface::RObjectOwns(CUtiOB* &i,  int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a)
{
   if (flags & TYPE_STREAM)
   {
      CXNode* node = n->GetNodeByName(Name);
      if (node)
      {
         if (i) delete i;
         i = NULL;
          i = XReadClass(node, wri, this);
         //i.xread(node, wri);
          if (i)
         dynamic_cast<CReadInfo*>(wri)->AddObject(i, i->GetCode());

      };
   }
}

void CXReadInterface::RBool(bool &i, bool std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a)
{
    if (flags & TYPE_STREAM)
    {
        i = n->getPropBool(Name, std);
    }
}
void CXReadInterface::RString(CUtiString &i, TCHAR* std, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a)
{
    if (flags & TYPE_STREAM)
    {
        i = n->getPropString(Name, std);
    }
}
void CXReadInterface::RObjectList(CCacheList &i, int flags, TCHAR* Name, TCHAR* Beschreibung, CUtiOB* a)
{
    if (flags & TYPE_STREAM)
    {
        i.Clear();
        CXNode* node = n->GetNodeByName(Name);
        if (node)
        {
            int c = node->getPropInt(Name, 0);
            for (int l = 0; l < c; l++)
            {
                CXNode* subnode = node->GetChild(l);
                CUtiOB* ob = XReadClass(subnode, wri, this);
                dynamic_cast<CReadInfo*>(wri)->AddObject(ob, ob->GetCode());
                i.Add(ob);
            };
        };
    };
}

CReadInfo::CReadInfo()
{
    links.deleteItems = true;
  //  ObjList.deleteItems = true;
}

void CReadInfo::Link()
{
    for (int i = 0; i < links.count; i++)
    {
        CLinkInfo* info = (CLinkInfo*)links[i];
        map<SCode, CUtiOB*>::iterator iter = objmap.find(info->code);
        if (iter == objmap.end()) {
           *info->obj = NULL; 
           wcout << L"Link nicht gefunden" << endl;
        } else {
           *info->obj = iter->second;
        };/*
        for (int j = 0; j < ObjList.count; j++)
        {
            CObjInfo* obj = (CObjInfo*)ObjList[i];
            if (compareCode(obj->code, info->code))
            {
                *info->obj = obj->obj;
                break;
            };
       };*/
    };
}

CReadInfo::~CReadInfo()
{
}

void CReadInfo::AddLink(CUtiOB** obj, SCode code)
{
    CLinkInfo* obj1 = new CLinkInfo();
    obj1->obj = obj;
    obj1->code = code;
    links.Add(obj1);

}

void CReadInfo::AddObject(CUtiOB* obj, SCode code)
{
  /*  CObjInfo* obj1 = new CObjInfo();
    obj1->obj = obj;
    obj1->code = code;
   ObjList.Add(obj1);*/
    objmap[code] = obj;
}

CXNode::CXNode(CXNode* parent, CXDocument* doc) : CUtiOB()
{
    this->parent = parent;
    this->doc = doc;
};

CDataProp::CDataProp() : CBaseProp()
{
    data = NULL;
    size = 0;
}

CDataProp::~CDataProp()
{
    delete [] data;
}

CXUtiNode::CXUtiNode(CXNode* parent, CXDocument* doc) : CXNode(parent, doc)
{
    Nodes.deleteItems = true;
    Properties.deleteItems = true;
    Name = -1;
}
void CXUtiNode::setName(TCHAR* name)
{
    ((CXUtiDocument*)doc)->RemoveIndex(this->Name);
    this->Name = ((CXUtiDocument*)doc)->AddString(name);
}
const CUtiString CXUtiNode::getName()
{
    return ((CXUtiDocument*)doc)->GetString(Name);
}

//#define XUTITYPE(
/*var
   index: integer;
   prop: TBaseProp;
begin
   index := TXUtiDocument(doc).FindString(name);
   if index = -1 then begin
      Result := std;
   end else begin
      if prophash.Find(Pointer(index), Pointer(prop)) then begin
         if not (prop is TBoolProp) then begin
            raise Exception.Create(name + UTEXT(' ist keine Bool Eigenschaft.'));
         end else begin
            Result := TBoolProp(prop).value;
         end;   
      end else begin
 
 Result := std;
      end;             
   end; */

CBaseProp* CXUtiNode::FindPropByIndex(int x)
{
    if (this->prophash.find(x) != this->prophash.end())
    {
        return this->prophash.find(x)->second ;

    }
    else
    {
        /*for (int i = 0; i < Properties.count; i++) {
        	CBaseProp* prop = (CBaseProp*)Properties[i];
        	if (prop->id == x) return prop;

        };*/
        return NULL;
    }
}



void CXUtiNode::setPropBool(TCHAR* name, const bool b)
{
#define PROP CBoolProp
    int index;
    //PROP* prop;
    index = ((CXUtiDocument*)doc)->FindString(name);
    if (index == -1)
    {
        PROP* p = new PROP();
        index = ((CXUtiDocument*)doc)->AddString(name);
        p->id = index;
        p->b = b;
        prophash[p->id] = p;
        Properties.Add(p);
    }
    else
    {
        CBaseProp* prop = FindPropByIndex(index);
        if (prop)
        {
            PROP* p = dynamic_cast<PROP*>(prop);
           if (!p)
               throw CUtiTypeException();
            p->b = b;
        }
        else
        {
            PROP* p = new PROP();
            p->id = index;
            p->b = b;
            prophash[p->id] = p;
            Properties.Add(p);
        };
    };
#undef PROP
}
const bool CXUtiNode::getPropBool(TCHAR* name, const bool std)
{
#define PROP CBoolProp
    int index;

    index = ((CXUtiDocument*)doc)->FindString(name);
    if (index == -1)
    {
        return std;
    }
    else
    {
        CBaseProp*prop = FindPropByIndex(index);
        if (prop)
        {
            PROP* p = dynamic_cast<PROP*>(prop);
            if (!p)
                throw CUtiTypeException();
            return p->b;
        }
        else
        {
            return std;
        };
    };
#undef PROP
}
void CXUtiNode::setPropInt(TCHAR* name, const int b)
{
#define PROP CIntProp
    int index;

    index = ((CXUtiDocument*)doc)->FindString(name);
    if (index == -1)
    {
        PROP* p = new PROP();
        index = ((CXUtiDocument*)doc)->AddString(name);
        p->id = index;
        p->b = b;
        prophash[p->id] = p;
        Properties.Add(p);
    }
    else
    {
        CBaseProp*prop = FindPropByIndex(index);
        if (prop)
        {
            PROP* p = dynamic_cast<PROP*>(prop);
            if (!p)
                throw CUtiTypeException();
            p->b = b;
        }
        else
        {
            PROP* p = new PROP();
            p->id = index;
            p->b = b;
            prophash[p->id] = p;
            Properties.Add(p);
        };
    };
#undef PROP
}
const int CXUtiNode::getPropInt(TCHAR* name, const int std)
{
#define PROP CIntProp
    int index;

    index = ((CXUtiDocument*)doc)->FindString(name);
    if (index == -1)
    {
        return std;
    }
    else
    {
        CBaseProp*prop = FindPropByIndex(index);
        if (prop)
        {
            PROP* p = dynamic_cast<PROP*>(prop);
            if (!p)
                throw CUtiTypeException();
            return p->b;
        }
        else
        {
            return std;
        };
    };
#undef PROP
}
void CXUtiNode::setPropFloat(TCHAR* name, const float b)
{
#define PROP CFloatProp
    int index;

    index = ((CXUtiDocument*)doc)->FindString(name);
    if (index == -1)
    {
        PROP* p = new PROP();
        index = ((CXUtiDocument*)doc)->AddString(name);
        p->id = index;
        p->b = b;
        prophash[p->id] = p;
        Properties.Add(p);
    }
    else
    {
        CBaseProp*prop = FindPropByIndex(index);
        if (prop)
        {
            PROP* p = dynamic_cast<PROP*>(prop);
            if (!p)
                throw CUtiTypeException();
            p->b = b;
        }
        else
        {
            PROP* p = new PROP();
            p->id = index;
            p->b = b;
            prophash[p->id] = p;
            Properties.Add(p);
        };
    };
#undef PROP
}
const float CXUtiNode::getPropFloat(TCHAR* name, const float std)
{
#define PROP CFloatProp
    int index;

    index = ((CXUtiDocument*)doc)->FindString(name);
    if (index == -1)
    {
        return std;
    }
    else
    {
        CBaseProp*prop = FindPropByIndex(index);
        if (prop)
        {
            PROP* p = dynamic_cast<PROP*>(prop);
            if (!p)
                throw CUtiTypeException();
            return p->b;
        }
        else
        {
            return std;
        };
    };
#undef PROP
}
void CXUtiNode::setPropDouble(TCHAR* name, const double b)
{
#define PROP CDoubleProp
    int index;

    index = ((CXUtiDocument*)doc)->FindString(name);
    if (index == -1)
    {
        PROP* p = new PROP();
        index = ((CXUtiDocument*)doc)->AddString(name);
        p->id = index;
        p->b = b;
        prophash[p->id] = p;
        Properties.Add(p);
    }
    else
    {
        CBaseProp*prop = FindPropByIndex(index);
        if (prop)
        {
            PROP* p = dynamic_cast<PROP*>(prop);
            if (!p)
                throw CUtiTypeException();
            p->b = b;
        }
        else
        {
            PROP* p = new PROP();
            p->id = index;
            p->b = b;
            prophash[p->id] = p;
            Properties.Add(p);
        };
    };
#undef PROP
}
const double CXUtiNode::getPropDouble(TCHAR* name, const double std)
{
#define PROP CDoubleProp
    int index;

    index = ((CXUtiDocument*)doc)->FindString(name);
    if (index == -1)
    {
        return std;
    }
    else
    {
        CBaseProp*prop = FindPropByIndex(index);
        if (prop)
        {
            PROP* p = dynamic_cast<PROP*>(prop);
            if (!p)
                throw CUtiTypeException();
            return p->b;
        }
        else
        {
            return std;
        };
    };
#undef PROP
}
void CXUtiNode::setPropCode(TCHAR* name, const SCode b)
{
#define PROP CCodeProp
    int index;

    index = ((CXUtiDocument*)doc)->FindString(name);
    if (index == -1)
    {
        PROP* p = new PROP();
        index = ((CXUtiDocument*)doc)->AddString(name);
        p->id = index;
        p->b = b;
        prophash[p->id] = p;
        Properties.Add(p);
    }
    else
    {
        CBaseProp*prop = FindPropByIndex(index);
        if (prop)
        {
            PROP* p = dynamic_cast<PROP*>(prop);
            if (!p)
                throw CUtiTypeException();
            p->b = b;
        }
        else
        {
            PROP* p = new PROP();
            p->id = index;
            p->b = b;
            prophash[p->id] = p;
            Properties.Add(p);
        };
    };
#undef PROP
}
const SCode CXUtiNode::getPropCode(TCHAR* name, const SCode std)
{
#define PROP CCodeProp
    int index;

    index = ((CXUtiDocument*)doc)->FindString(name);
    if (index == -1)
    {
        return std;
    }
    else
    {
        CBaseProp*prop = FindPropByIndex(index);
        if (prop)
        {
            PROP* p = dynamic_cast<PROP*>(prop);
            if (!p)
                throw CUtiTypeException();
            return p->b;
        }
        else
        {
            return std;
        };
    };
#undef PROP
}
void CXUtiNode::setPropVector(TCHAR* name, const CVector b)
{
#define PROP CVectorProp
    int index;

    index = ((CXUtiDocument*)doc)->FindString(name);
    if (index == -1)
    {
        PROP* p = new PROP();
        index = ((CXUtiDocument*)doc)->AddString(name);
        p->id = index;
        p->b = b;
        prophash[p->id] = p;
        Properties.Add(p);
    }
    else
    {
        CBaseProp*prop = FindPropByIndex(index);
        if (prop)
        {
            PROP* p = dynamic_cast<PROP*>(prop);
            if (!p)
                throw CUtiTypeException();
            p->b = b;
        }
        else
        {
            PROP* p = new PROP();
            p->id = index;
            p->b = b;
            prophash[p->id] = p;
            Properties.Add(p);
        };
    };
#undef PROP
}
const CVector CXUtiNode::getPropVector(TCHAR* name, const CVector std)
{
#define PROP CVectorProp
    int index;

    index = ((CXUtiDocument*)doc)->FindString(name);
    if (index == -1)
    {
        return std;
    }
    else
    {
        CBaseProp*prop = FindPropByIndex(index);
        if (prop)
        {
            PROP* p = dynamic_cast<PROP*>(prop);
            if (!p)
                throw CUtiTypeException();
            return p->b;
        }
        else
        {
            return std;
        };
    };
#undef PROP
}
void CXUtiNode::setPropColor(TCHAR* name, const SVector4 b)
{
#define PROP CColorProp
    int index;

    index = ((CXUtiDocument*)doc)->FindString(name);
    if (index == -1)
    {
        PROP* p = new PROP();
        index = ((CXUtiDocument*)doc)->AddString(name);
        p->id = index;
        p->b = b;
        prophash[p->id] = p;
        Properties.Add(p);
    }
    else
    {
        CBaseProp*prop = FindPropByIndex(index);
        if (prop)
        {
            PROP* p = dynamic_cast<PROP*>(prop);
            if (!p)
                throw CUtiTypeException();
            p->b = b;
        }
        else
        {
            PROP* p = new PROP();
            p->id = index;
            p->b = b;
            prophash[p->id] = p;
            Properties.Add(p);
        };
    };
#undef PROP
}
const SVector4 CXUtiNode::getPropColor(TCHAR* name, const SVector4 std)
{
#define PROP CColorProp
    int index;

    index = ((CXUtiDocument*)doc)->FindString(name);
    if (index == -1)
    {
        return std;
    }
    else
    {
        CBaseProp*prop = FindPropByIndex(index);
        if (prop)
        {
            PROP* p = dynamic_cast<PROP*>(prop);
            if (!p)
                throw CUtiTypeException();
            return p->b;
        }
        else
        {
            return std;
        };
    };
#undef PROP
}
void CXUtiNode::setPropString(TCHAR* name, TCHAR* b)
{
#define PROP CStringProp
    int index;

    index = ((CXUtiDocument*)doc)->FindString(name);
    if (index == -1)
    {
        PROP* p = new PROP();
        index = ((CXUtiDocument*)doc)->AddString(name);
        p->id = index;
        p->b = b;
        prophash[p->id] = p;
        Properties.Add(p);
    }
    else
    {
        CBaseProp*prop = FindPropByIndex(index);
        if (prop)
        {
            PROP* p = dynamic_cast<PROP*>(prop);
            if (!p)
                throw CUtiTypeException();
            p->b = b;
        }
        else
        {
            PROP* p = new PROP();
            p->id = index;
            p->b = b;
            prophash[p->id] = p;
            Properties.Add(p);
        };
    };
#undef PROP
}
const CUtiString CXUtiNode::getPropString(TCHAR* name, const TCHAR* std)
{
#define PROP CStringProp
    int index;

    index = ((CXUtiDocument*)doc)->FindString(name);
    if (index == -1)
    {
        return std;
    }
    else
    {
        CBaseProp*prop = FindPropByIndex(index);
        if (prop)
        {
            PROP* p = dynamic_cast<PROP*>(prop);
            if (!p)
                throw CUtiTypeException();
            return p->b;
        }
        else
        {
            return std;
        };
    };
#undef PROP
}
void CXUtiNode::setPropData(TCHAR* name, unsigned char* Data, size_t size)
{
#define PROP CDataProp
    int index;

    index = ((CXUtiDocument*)doc)->FindString(name);
    if (index == -1)
    {
        PROP* p = new PROP();
        index = ((CXUtiDocument*)doc)->AddString(name);
        p->id = index;
        p->data = new unsigned char[size];
        memcpy(p->data, Data, size);
        p->size = (int)size;
        prophash[p->id] = p;
        Properties.Add(p);
    }
    else
    {
        CBaseProp*prop = FindPropByIndex(index);
        if (prop)
        {
            PROP* p = dynamic_cast<PROP*>(prop);
            if (!p)
                throw CUtiTypeException();
            if (p->data)
                delete [] p->data;
            p->data = new unsigned char[size];
            memcpy(p->data, Data, size);
            p->size = (int)size;
        }
        else
        {
            PROP* p = new PROP();
            p->id = index;
            p->data = new unsigned char[size];
            memcpy(p->data, Data, size);
            p->size = (int)size;
            prophash[p->id] = p;
            Properties.Add(p);
        };
    };
#undef PROP
}
bool CXUtiNode::getPropData(TCHAR* name, unsigned char* &Data, size_t &size)
{
#define PROP CDataProp
    int index;

    index = ((CXUtiDocument*)doc)->FindString(name);
    if (index == -1)
    {
        return false;
    }
    else
    {
        CBaseProp*prop = FindPropByIndex(index);
        if (prop)
        {
            PROP* p = dynamic_cast<PROP*>(prop);
            if (!p)
                throw CUtiTypeException();
            //return p->b;
            Data = new unsigned char[p->size];
            memcpy(Data, p->data, size);
            return true;
        }
        else
        {
            return false;
        };
    };
#undef PROP
}
bool CXUtiNode::PropExists(TCHAR* name)
{
    int index = ((CXUtiDocument*)doc)->FindString(name);
    if (index == -1)
    {
        return false;
    }
    else
    {
        CBaseProp* prop = FindPropByIndex(index);
        if (prop)
            return true;
    };
    return false;
}
HResult CXUtiNode::Read(CStream & Stream, int Flags, int version)
{
    int  c, id, typ;
    CUtiString s;

    ClearNodes();
    ClearProperties();
    Stream.ReadInteger(Name);
    ((CXUtiDocument*)doc)->IncIndex(Name);
    Stream.ReadInteger(c);
    for (int i = 0; i < c; i++)
    {
        Stream.ReadInteger(id);
        typ = id >> 24;
        id = id & 0xFFFFFF;
        ((CXUtiDocument*)doc)->IncIndex(id);
        switch (typ) {
           case X_BOOL: 
        
        {
            CBoolProp* b = new CBoolProp();
            b->id = id;
            Stream.ReadBoolean(b->b);
            prophash[b->id] = b;
            Properties.Add(b);

        } ;break;
           case X_CODE:
        {
            CCodeProp* b = new CCodeProp();
            b->id = id;
            Stream.ReadData(&b->b, sizeof(b->b));
            prophash[b->id] = b;
            Properties.Add(b);
        };break;
           case X_COLOR:
        {
            CColorProp* b = new CColorProp();
            b->id = id;
            Stream.ReadData(&b->b, sizeof(b->b));
            prophash[b->id] = b;
            Properties.Add(b);
        };break;
           case X_DATA:
        {
            CDataProp* b = new CDataProp();
            b->id = id;
            Stream.ReadData(&b->size, sizeof(b->size));
            b->data = new unsigned char [b->size];
            Stream.ReadData(b->data, b->size);
            prophash[b->id] = b;
            Properties.Add(b);
        };break;
           case X_DOUBLE:
        {
            CDoubleProp* b = new CDoubleProp();
            b->id = id;
            Stream.ReadData(&b->b, sizeof(b->b));
            prophash[b->id] = b;
            Properties.Add(b);
        };break;
           case X_SINGLE:
        {
            CFloatProp* b = new CFloatProp();
            b->id = id;
            Stream.ReadData(&b->b, sizeof(b->b));
            prophash[b->id] = b;
            Properties.Add(b);
        };break;
           case X_INT:
        {
            CIntProp* b = new CIntProp();
            b->id = id;
            Stream.ReadData(&b->b, sizeof(b->b));
            prophash[b->id] = b;
            Properties.Add(b);
        };break;
           case X_STRING:
        {
            CStringProp* b = new CStringProp();
            b->id = id;
            //Stream.ReadData(&b->b, sizeof(b->b));
            ReadStringWide(Stream, b->b);
            prophash[b->id] = b;
            Properties.Add(b);
        };break;
           case X_VECTOR:
        {
            CVectorProp* b = new CVectorProp();
            b->id = id;
            b->b.Read(Stream);
            prophash[b->id] = b;
            Properties.Add(b);
        };break;
        };
    };


    Stream.ReadInteger(c);
    for (int i = 0; i < c; i++)
    {
        CXUtiNode* n = new CXUtiNode(this, doc);
        n->Read(Stream, Flags, version);
        Nodes.Add(n);
        nodehash[n->Name] = n;
        
    };
    return 0;
}
HResult CXUtiNode::Write(CStream & Stream, int Flags, int version)
{
    int  c, id;
    CUtiString s;


    Stream.WriteInteger(Name);
    c = Properties.count;
    Stream.WriteInteger(c);
    for (int i = 0; i < c; i++)
    {
        CBaseProp* prop = (CBaseProp*)Properties[i];
        if (dynamic_cast<CBoolProp*>(prop))
        {
            CBoolProp* b = (CBoolProp*)(prop);
            id = (b->id & 0xFFFFFF) | (X_BOOL << 24);
            Stream.WriteInteger(id);
            Stream.WriteBoolean(b->b);
        } else
        if (dynamic_cast<CCodeProp*>(prop))
        {
            CCodeProp* b = (CCodeProp*)(prop);
            id = (b->id & 0xFFFFFF) | (X_CODE << 24);
            Stream.WriteInteger(id);
            Stream.WriteData(&b->b, sizeof(b->b));
        } else
        if (dynamic_cast<CColorProp*>(prop))
        {
            CColorProp* b = (CColorProp*)(prop);
            id = (b->id & 0xFFFFFF) | (X_COLOR << 24);
            Stream.WriteInteger(id);
            Stream.WriteData(&b->b, sizeof(b->b));
        } else
        if (dynamic_cast<CDataProp*>(prop))
        {
            CDataProp* b = (CDataProp*)(prop);
            id = (b->id & 0xFFFFFF) | (X_DATA << 24);
            Stream.WriteInteger(id);
            //Stream.WriteData(&b->b, sizeof(b->b));
            Stream.WriteInteger(b->size);
            Stream.WriteData(b->data, b->size);
        } else
        if (dynamic_cast<CDoubleProp*>(prop))
        {
            CDoubleProp* b = (CDoubleProp*)(prop);
            id = (b->id & 0xFFFFFF) | (X_DOUBLE << 24);
            Stream.WriteInteger(id);
            Stream.WriteData(&b->b, sizeof(b->b));
        } else
        if (dynamic_cast<CFloatProp*>(prop))
        {
            CFloatProp* b = (CFloatProp*)(prop);
            id = (b->id & 0xFFFFFF) | (X_SINGLE << 24);
            Stream.WriteInteger(id);
            Stream.WriteData(&b->b, sizeof(b->b));
        } else
        if (dynamic_cast<CIntProp*>(prop))
        {
            CIntProp* b = (CIntProp*)(prop);
            id = (b->id & 0xFFFFFF) | (X_INT << 24);
            Stream.WriteInteger(id);
            Stream.WriteData(&b->b, sizeof(b->b));
        } else

        if (dynamic_cast<CStringProp*>(prop))
        {
            CStringProp* b = (CStringProp*)(prop);
            id = (b->id & 0xFFFFFF) | (X_STRING << 24);
            Stream.WriteInteger(id);
            //Stream.WriteData(&b->b, sizeof(b->b));
            WriteStringWide(Stream, b->b);
        } else
        if (dynamic_cast<CVectorProp*>(prop))
        {
            CVectorProp* b = (CVectorProp*)(prop);
            id = (b->id & 0xFFFFFF) | (X_VECTOR << 24);
            Stream.WriteInteger(id);
            Stream.WriteData(&b->b, sizeof(b->b));
        };

    };

    c = Nodes.count;
    Stream.WriteInteger(c);
    for (int i = 0; i < c; i++)
    {
        CXUtiNode* n = (CXUtiNode*)Nodes[i];
        n->Write(Stream, Flags, version);

    };

    return 0;
}
CXNode* CXUtiNode::AddNode(TCHAR* name)
{
    CXUtiNode* n = new CXUtiNode(this, doc);
    n->setName(name);
    nodehash[n->Name] = n;
    Nodes.Add(n);
    return n;
}
CXNode* CXUtiNode::GetNodeByName(TCHAR* name)
{
   int nm = static_cast<CXUtiDocument*>(doc)->FindString(name);
   if (nm == -1) return NULL;
   map <int, CXUtiNode*>::iterator iter = nodehash.find(nm);
   if (iter == nodehash.end()) {
      return NULL;
   } else {
      return iter->second;
   };
  /*  for (int i = 0; i < Nodes.count; i++)
    {
        CXUtiNode* n = (CXUtiNode*)Nodes[i];
        if (n->Name == nm)
        {
            return n;
        };

};*/
    return NULL;
}
void CXUtiNode::DeleteNode(TCHAR* name)
{
   int nm = static_cast<CXUtiDocument*>(doc)->FindString(name);
   if (nm == -1) return;
   map <int, CXUtiNode*>::iterator iter = nodehash.find(nm);
   if (iter == nodehash.end()) {
      return;
   }
   nodehash.erase(iter);
    for (int i = 0; i < Nodes.count; i++)
    {
        CXUtiNode* n = (CXUtiNode*)Nodes[i];
        if (n->Name ==  nm)
        {
            Nodes.Delete(i);
            return;

        };

    };
}
void CXUtiNode::Delete(int i)
{
   map <int, CXUtiNode*>::iterator iter = nodehash.find( ((CXUtiNode*)Nodes[i])->Name);
   if (iter == nodehash.end()) {
      return;
   }
   nodehash.erase(iter);
    Nodes.Delete(i);
}
void CXUtiNode::Remove(CXNode* n)
{
   map <int, CXUtiNode*>::iterator iter = nodehash.find( ((CXUtiNode*)n)->Name);
   if (iter == nodehash.end()) {
      return;
   }
   nodehash.erase(iter);
    Nodes.Remove(n);
}

int CXUtiNode::GetChildCount()
{
    return Nodes.count;
}
CXNode* CXUtiNode::GetChild(int i)
{

    return (CXNode*)Nodes[i];
}
void CXUtiNode::ClearNodes()
{
    Nodes.Clear();
    nodehash.clear();
}
void CXUtiNode::ClearProperties()
{
    Properties.Clear();
    prophash.clear();
}

CXDocument::CXDocument() : CUtiOB()
{
}

CXDocument::~CXDocument()
{
}

CXUtiDocument::CXUtiDocument(): CXDocument()
{
    strlist.deleteItems = true;
    root = new CXUtiNode(NULL, this);
    root->setName(L"root");
}
CXUtiDocument::~CXUtiDocument()
{
}
int CXUtiDocument::AddString(TCHAR*s)
{
    int index = FindString(s);
    if (index == -1)
    {
        CXName* n = new CXName();
        n->name = s;
        n->ref = 1;
        listindex[s] = strlist.count;
        strlist.Add(n);
        return strlist.count-1;


    }
    else
    {
        IncIndex(index);
        return index;
    }
}
void CXUtiDocument::RemoveString(TCHAR*id)
{
    int index = FindString(id);
    TCHAR*c = ((CXName*)strlist[index])->name.getString();

    listindex.erase(c);

    RemoveIndex(index);
}
void CXUtiDocument::RemoveIndex(int index)
{
    if (index == -1)
        return;
    if (index >= strlist.count) return;
    CXName* n = (CXName*)strlist[index];
    n->ref--;
    if (n->ref == 0)
    {
        strlist.Delete(index);
    }
}
void CXUtiDocument::IncIndex(int index)
{
    CXName* n = (CXName*)strlist[index];
    n->ref++;
}
int CXUtiDocument::FindString(TCHAR* s)
{
  
    if (listindex.find(s) != listindex.end())
    {
        int index = listindex.find(s)->second;
        return index;
    }
    return -1;
}
const CUtiString CXUtiDocument::GetString(int id)
{
    CXName* n = (CXName*)strlist[id];
    return n->name;
}
void CXUtiDocument::SaveToStream(CStream &Stream)
{
    char code[4];
    int c;
    code[0] = 'U';
    code[1] =('t');
    code[2] = ('i');
    code[3] = 'X';
    Stream.WriteData(code, 4);
    int flags = 0;
    Stream.WriteData(&flags, sizeof(flags));
    int version = 12;
    Stream.WriteData(&version, sizeof(version));

    // node.read(str, 0, currentversion);
    c = strlist.count;
    Stream.WriteData(&c, sizeof(c));
    for (int i = 0; i < c; i++)
    {
        WriteStringWide(Stream, static_cast<CXName*>(strlist[i])->name);
    };
    root->Write(Stream, 0, version);
}
void CXUtiDocument::LoadFromStream(CStream &Stream)
{
    int c;
    CUtiString s;
    int code, flags, version;
    Stream.ReadInteger(code);
    //  flags := 0;
    Stream.ReadInteger(flags);
    // version := currentversion;
    Stream.ReadInteger(version);
    // node.read(str, 0, currentversion);
    //c := hash.Count;
    Stream.ReadInteger(c);
    root->ClearProperties();
    root->ClearNodes();
    strlist.Clear();
    for (int i = 0; i < c; i++)
    {
        ReadStringWide(Stream, s);
        //cout << s.c_str() << endl;
        CXName* n = new CXName();
        n->ref = 0;
        n->name = s;
        listindex[s.getString()] = strlist.count;
        strlist.Add(n);

    };
    root->Read(Stream, 0, version);
}
void CXUtiDocument::SaveToFile(TCHAR* name)
{
    CFileStream* str = new CFileStream(name, S_WRITE);
    SaveToStream(*str);
    delete str;
}
void CXUtiDocument::LoadFromFile(TCHAR* name)
{
    CFileStream* str = new CFileStream(name, S_READ);
    LoadFromStream(*str);
    delete str;

}

CRTTIManager::CRTTIManager()
{
    this->classes.deleteItems = true;
}

CRTTIManager::~CRTTIManager()
{
}

void CRTTIManager::AddRTTI(CClassRTTI* cl, LPVOID Data)
{
    classes.Add(cl);
    clmap[cl->GetCode()] = cl;
}

CUtiOB* CRTTIManager::CreateClass(SCode code, CUtiOB* parent)
{
   /* for (int i = 0; i < classes.count; i++)
    {
        CClassRTTI* cl = (CClassRTTI*)classes[i];
        if (compareCode(cl->GetCode(), code))
        {
            return cl->CreateClass(parent);
        };

};*/
    map<SCode, CClassRTTI*>::iterator it = clmap.find(code);
    if (it == clmap.end()) return NULL;
    CClassRTTI* cl = it->second;
    
    return cl->CreateClass(parent);
}
void XWriteClass(CXNode* n, LPVOID wri, CUtiOB* cl)
{
   if (cl) {
      SCode code= cl->GetTypeCode();
      n->setPropCode(L"@typecode", code);
      cl->xwrite(n,(CWriteReadInterface*) wri);
   } else {
      n->setPropCode(L"@typecode", NULLCODE);
   };
}

CUtiOB* XReadClass(CXNode* n, LPVOID wri, CUtiOB* parent)
{
    SCode code = n->getPropCode(L"@typecode", NULLCODE);
    if (code == NULLCODE) return NULL;
    CUtiOB* result = rttimanager.CreateClass(code, parent);
    if (result == NULL) {
       wcout << L"TypeCode nicht gefunden";
    };
    result->xread(n, (CWriteReadInterface*) wri);
    return result;
};

void XSaveToFile(TCHAR* string, CUtiOB* cl)
{
    CXDocument* xml = new CXUtiDocument();
    XWriteClass(xml->root, NULL, cl);
    xml->SaveToFile(string);
    delete xml;
};

CUtiOB* XLoadFromFile(TCHAR* string, CUtiOB* parent)
{
    CXDocument* xml = new CXUtiDocument();
    xml->LoadFromFile(string);
    CReadInfo * r = new CReadInfo();
    CUtiOB* result = XReadClass(xml->root, r, parent);
    r->AddObject(result, result->GetCode());
    r->Link();
    delete r;

    delete xml;
    return result;
}
