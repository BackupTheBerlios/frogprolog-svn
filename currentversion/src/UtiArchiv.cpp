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
#include "UtiArchiv.h"
#include "UtiString.h"
#include <fstream>
//#include <windows.h>
#include "utisystem.h"
#include <math.h>
#include <iostream>

using namespace UtiFramework;

using namespace std;

CUtiArchiv* MainArchive=NULL;
bool uti_inarchiv = true;

void InitArchive(TCHAR* name)
{
    MainArchive = new CUtiArchiv(name);
}

void FreeArchive()
{
    delete MainArchive;
}

CFileStream* UtiOpenFile(TCHAR* name)
{
    // MessageBox(0, UTEXT("n"), name, 0);
    if (MainArchive && uti_inarchiv)
    {
        return MainArchive->OpenFile(name);

    }
    else
    {
        return new CFileStream(name, S_READ);

    }
}

INT64 UtiFileSize(U_CHAR*name)
{
    if (MainArchive && uti_inarchiv)
    {
        return MainArchive->UFileSize(name);

    }
    else
    {
        return FileSize(name);

    }
}

bool UtiFileExists(TCHAR* name)
{
    if (MainArchive && uti_inarchiv)
    {
        return MainArchive->DoesFileExists(name);

    }
    else
    {
        return FileExists(name);

    }
}

CUtiArchiv::CUtiArchiv(CUtiString _Name)
{
    Name = _Name;
    Files.deleteItems = true;
    Directories.deleteItems= true;
    //str = NULL;
    if (FileExists(Name.getString()))
    {
        Load();
    }
    else
    {
        Init();
    };
    //	FileList = NULL;
    LastExists = NULL;
    StartPath = UTEXT("");
    //	rseed = time();
}

CUtiArchiv::~CUtiArchiv()
{
    //if (str) delete str;
}

CMinMaxFileStream::~CMinMaxFileStream()
{}

bool CMinMaxFileStream::eof()
{
    fstream* str = (fstream*)strm;
    return(str->eof()!=0|| getReadPosition() >= Max);
};

CMinMaxFileStream::CMinMaxFileStream(TCHAR *name, int i, bool trunc, INT64 Min,INT64 Max) : CFileStream(name,i,trunc)
{
    this->Min = Min;
    this->Max = Max;
    setPosition(0);
}

void CMinMaxFileStream::setPosition(UINT i)
{
    CFileStream::setPosition(i+Min);
}

void CMinMaxFileStream::ReadData(void* data, unsigned int size)
{
    int pos = getReadPosition();
    utiassert((pos >= Min));
    utiassert(pos+size <= Max);
    CFileStream::ReadData(data, size);
}

INT64 CUtiArchiv::GetFileSize()
{
    INT64 s=0;
    for (int i = 0; i < Files.count; i++)
    {
        CUtiAFile* d = (CUtiAFile*)Files[i];
        s += d->Info.OriginalSize;

    };
    return s;
}

int CUtiArchiv::GetFileCount()
{
    return Header.FileCount;
}

int CUtiArchiv::GetDirCount()
{
    return Header.DirCount;
}

void CUtiAFile::GetFileName(CUtiString &fn)
{
    fn = UTEXT("");
    CUtiADirectory* p = Parent;
    while (p)
    {
        fn += p->Name + UTEXT("/");
        p = p->Parent;
    };
    fn += Name.getString();
}
/*
void CUtiArchiv::AddFileToList(CUtiAFile* f)
{
   if (!FileList) return;
   CUtiString fn;
   f->GetFileName(fn);
   FileList->Add(fn.getString());
}*/

/*void CUtiArchiv::FillList()
{
   if (!FileList) return;
   for (int i = 0; i < Files.count; i++) {
	   CUtiAFile* d = (CUtiAFile*)Files[i];
	   AddFileToList(d);
 
   };
}*/

CUtiADirectory* CUtiArchiv::FindDir(INT64 ID)
{
    if (ID == -1)
        return NULL;
    for (int i = 0; i < Directories.count; i++)
    {
        CUtiADirectory* d = (CUtiADirectory*)Directories[i];
        if (d->Info.DirID == ID)
        {
            return d;

        };
    };
    return NULL;
}

CUtiADirectory* CUtiArchiv::GetDir(CUtiString Path)
{
    if (Path == UTEXT(""))
    {
        return NULL;
    };
    CUtiString paths[16];
    int p = Path.Pos(UTEXT("/"));
    int c = 0;
    if (p != -1)
    {
        while (p != -1)
        {
            Path.Copy(&paths[c], 0, p);
            c++;
            Path.Delete(0, p+1);
            p = Path.Pos(UTEXT("/"));
        }
        paths[c] = Path;
        c++;
    }
    else
    {
        c = 1;
        paths[0] = Path;
    };
    for (int i = 0; i < Directories.count; i++)
    {
        CUtiADirectory* d = (CUtiADirectory*)Directories[i];
        if (paths[c-1] != d->Name)
            continue;
        CUtiADirectory* p = d->Parent;
        bool fail= false;
        for (int j = c-2; j >= 0; j--)
        {
            if (p == NULL)
            {
                fail = true;
                break;
            };
            if (paths[j] != d->Name)
            {
                fail = true;
                break;
            };
            p = p->Parent;

        };
        if (fail)
            continue;
        return d;

    };
    return NULL;
}

CStream* CUtiArchiv::GetReadStream()
{
    return new CFileStream(Name.getString(), S_READ);
}

CStream* CUtiArchiv::GetWriteStream()
{
    CStream* str;
    if (FileExists(Name.getString()))
    {
        str = new CFileStream(Name.getString(), S_WRITE, false);
    }
    else
    {
        str = new CFileStream(Name.getString(), S_WRITE);
    }
    return str;
}

void CUtiArchiv::DeleteStream(CStream* *str)
{
    delete *(CFileStream**)str;
}

void CUtiArchiv::Init()
{
    CFileStream* str = (CFileStream*)GetWriteStream();
    //CFileStream* str = new CFileStream(Name.getString(), S_WRITE);

    Directories.Clear();
    Files.Clear();
    Header.DirCount = 0;
    Header.FileCount = 0;
    Header.FilterCount = 0;
    Header.Flags = 0;
    Header.ID =0xA046B476;
    Header.MajorVersion = 1;
    Header.MinorVersion = 0;
    str->WriteData(&Header, sizeof Header);
    //delete str;
    DeleteStream((CStream**)&str);
}

void CUtiArchiv::Load()
{
    CStream* str = GetReadStream();
    str->setPosition(0);
    Directories.Clear();
    Files.Clear();
    str->ReadData(&Header, sizeof Header);
    ArchivDirectory Dir;
    ArchivFile File;
    int pos;
    int count = Header.DirCount + Header.FileCount;
    for (int i = 0; i < count; i++)
    {
        UINT id;
        pos = str->getReadPosition();
        str->ReadData(&id, sizeof(UINT));
        str->setPosition(str->getReadPosition()-sizeof(UINT));
        if (id == 1 || id == 3)
        {
            File.ID = id;
            str->ReadData(&File, sizeof File);
            if (id == 1)
            {
                CUtiAFile* f = new CUtiAFile();
                f->Info = File;
                f->Position = pos;
                f->Name = File.name;
                Files.Add(f);
            };
            str->setPosition(str->getReadPosition()+File.Size);
        }
        if (id == 2 || id == 4)
        {
            Dir.ID = id;
            str->ReadData(&Dir, sizeof Dir);
            if (id == 2)
            {
                CUtiADirectory* d = new CUtiADirectory();
                d->Info = Dir;
                d->Position = pos;
                d->Name = Dir.name;
                Directories.Add(d);

            }
        }
    }
    DeleteStream((CStream**)&str);
    for (int i = 0; i < Directories.count; i++)
    {
        CUtiADirectory* d = (CUtiADirectory*)Directories[i];
        d->Parent = FindDir(d->Info.Directory);

    };
    for (int i = 0; i < Files.count; i++)
    {
        CUtiAFile* d = (CUtiAFile*)Files[i];
        d->Parent = FindDir(d->Info.Directory);

    };
}

CUtiADirectory* CUtiArchiv::CreateDir(CUtiADirectory* Pos, TCHAR* name)
{
    CStream* str = GetWriteStream();
    ArchivDirectory Dir;
    CUtiADirectory* d = new CUtiADirectory();
    d->Position = str->getWritePosition();
    d->Parent = Pos;
    if (d->Parent)
    {
        Dir.Directory = d->Parent->Info.DirID;
        d->Parent->Info.ChildrenCount++;
    }
    else
        Dir.Directory = -1;
    Dir.ChildrenCount = 0;
    Dir.ID = 2;
    d->Name = name;
    wcscpy(Dir.name, name);

    Dir.DirID = urandom(65536) | (INT64)(urandom(65536)) << 16 | (INT64)(urandom(65536)) << 32;
    Dir.Size = 0;
    d->Info = Dir;
    Directories.Add(d);
    str->WriteData(&Dir, sizeof Dir);
    //Header
    str->setPosition(0);

    Header.DirCount++;
    str->WriteData(&Header, sizeof Header);
    //Parentdir;
    if (d->Parent)
    {
        str->setPosition(d->Parent->Position);
        str->WriteData(&d->Parent->Info, sizeof d->Parent->Info);
    }
    DeleteStream((CStream**)&str);
    return d;
}

void CUtiArchiv::AddFile(TCHAR* FileName, TCHAR* Name, CUtiADirectory* Pos)
{
    if (!FileExists(FileName))
        return;
    CStream* str = GetWriteStream();
    ArchivFile File;
    CUtiAFile* f = new CUtiAFile();
    f->Position = str->getWritePosition();
    f->Parent = Pos;
    if (f->Parent)
    {
        File.Directory = f->Parent->Info.DirID;
        f->Parent->Info.ChildrenCount++;
    }
    else
        File.Directory = -1;
    File.Filter = 0;
    File.ID = 1;

    f->Name = Name;
    wcscpy(File.name, Name);

    File.Size = FileSize(FileName);
    File.OriginalSize = File.Size;
    //Gr�e ermitteln!

    f->Info = File;
    Files.Add(f);
    str->WriteData(&File, sizeof File);

    //Datei schreiben
    CFileStream* sf = new CFileStream(FileName, S_READ);
    INT64 size = f->Info.Size;
    INT64 PufferSize = 65536;
    TCHAR* Puffer = new TCHAR[PufferSize];
    while (size > 0)
    {
        sf->ReadData(Puffer, min(size, PufferSize));
        str->WriteData(Puffer, min(size, PufferSize));

        size -= PufferSize;
    };
    delete []Puffer;
    delete sf;
    //Header
    str->setPosition(0);

    Header.FileCount++;
    str->WriteData(&Header, sizeof Header);
    //Parentdir;
    if (f->Parent)
    {
        str->setPosition(f->Parent->Position);
        str->WriteData(&f->Parent->Info, sizeof f->Parent->Info);
    }
    DeleteStream((CStream**)&str);
    // AddFileToList(f);
}

void CUtiArchiv::UtiDeleteFile(TCHAR* name)
{}

void CUtiArchiv::Pack()
{}

CUtiAFile* CUtiArchiv::GetFile(CUtiString Path)
{
    CUtiString fn;
    CUtiAFile* f = LastExists;
    if (f)
    {
        f->GetFileName(fn);
        if (fn == Path)
        {
            return f;
        }
    }
    CUtiString name;
    name = Path;
    name.ExtractFileName();
    for (int i = 0; i < Files.count; i++)
    {
        f = (CUtiAFile*)Files[i];
        if (f->Name == name)
        {
            f->GetFileName(fn);
            if (fn == Path)
            {
                LastExists = f;
                return f;
            }
        }

    };
    return NULL;
}

void CUtiArchiv::AddRecursiv(TCHAR* dir, CUtiADirectory* Subdir,TCHAR* PathSubdir, TCHAR* types)
{
    CUtiString Dir(dir);
    Dir += PathSubdir;
    Dir += UTEXT("/");
    Dir += types;
    Dir_FileInfo FindFileData;

    if (!FindFirst(Dir, &FindFileData))
        return; //Da ist nichts

    do
    {
        if (FindFileData.name==UTEXT(".."))
            continue;
        if (FindFileData.name==UTEXT("."))
            continue;
        if (FindFileData.dir)
        {
            CUtiString sdir(PathSubdir);
            sdir += UTEXT("/");
            sdir += FindFileData.name;


            CUtiADirectory* newsub = CreateDir(Subdir, FindFileData.name.getString());
            AddRecursiv(dir, newsub, sdir.getString(), types);

        }
        else
        {
            CUtiString fname(dir);
            fname += PathSubdir;
            fname += UTEXT("/");
            fname += FindFileData.name;
            AddFile(fname.getString(), FindFileData.name.getString(), Subdir);

        }

    }
    while(FindNext(&FindFileData));
    FindClose(&FindFileData);
}

void CUtiArchiv::AddDir(TCHAR* dir, TCHAR* types, bool recursiv)
{

    CUtiString Dir(dir);
    Dir += types;

    Dir_FileInfo FindFileData;
    if (!FindFirst(Dir, &FindFileData))
        return; //Da ist nichts

    do
    {
        if (FindFileData.name==UTEXT(".."))
            continue;
        if (FindFileData.name==UTEXT("."))
            continue;
        if (FindFileData.dir)
        {
            if (recursiv)
            {
                CUtiADirectory* newsub = CreateDir(NULL, FindFileData.name.getString());
                AddRecursiv(dir, newsub, FindFileData.name.getString(), types);
            };
        }
        else
        {
            CUtiString fname(dir);
            fname += FindFileData.name;
            AddFile(fname.getString(), FindFileData.name.getString(), NULL);

        }

    }
    while(FindNext(&FindFileData));
    FindClose(&FindFileData);
}

bool CUtiArchiv::DoesFileExists(TCHAR* name)
{
    CUtiString RealPos;
    RealPos = StartPath+name;
    bool b = FileExists(RealPos.getString());

    if (b)
        return true;

    CUtiAFile* f = GetFile(name);
    if (f)
    {
        return true;
    }
    else
    {
        // MessageBox(0, name, UTEXT("Datei nicht gefunden"), 0);
        return false;
    }
}

INT64 CUtiArchiv::UFileSize(TCHAR* name)
{
    CUtiString RealPos;
    RealPos = StartPath+name;
    bool b = FileExists(RealPos.getString());

    if (b)
    {
        return FileSize(name);
    }

    CUtiAFile* f = GetFile(name);
    if (f)
    {
        return f->Info.OriginalSize;
    }
    else
    {
        // MessageBox(0, name, UTEXT("Datei nicht gefunden"), 0);
        return 0;
    }
}

CFileStream* CUtiArchiv::OpenFile(TCHAR* name)
{
    //MessageBox(0, name, UTEXT("Datei nicht gefunden"), 0);
    CUtiString RealPos;
    RealPos = StartPath+name;
    bool b = FileExists(RealPos.getString());

    if (b)
    {
        return new CFileStream(name, S_READ);
    }
    CUtiAFile* f = GetFile(name);
    if (f)
    {
        return new CMinMaxFileStream(Name.getString(), S_READ, true, f->Position+sizeof(ArchivFile),f->Position+sizeof(ArchivFile)+f->Info.Size);
    }
    else
    {
        // MessageBox(0, name, UTEXT("Datei nicht gefunden"), 0);
        return NULL;

    }

    /*CUtiAFile* f = GetFile(name);
      if (f) {
       return new CMinMaxFileStream(Name.getString(), S_READ, true, f->Position+sizeof(ArchivFile),f->Position+sizeof(ArchivFile)+f->Info.Size);
      } else {
       CUtiString RealPos;
    RealPos = StartPath+name;
    bool b = FileExists(RealPos.getString());
    if (b) {
    	return new CFileStream(name, S_READ);
    }
       return NULL;
      }*/

}

void CUtiArchiv::ExtractFileDirect(CUtiAFile* f, TCHAR* target)
{

    if (!f)
        return;
    CUtiString fpath(target);
    CUtiString subpath;
    f->GetFileName(subpath);
    fpath += UTEXT("/");
    fpath += subpath;
    fpath.ExtractFilePath();
    if (!FileExists(fpath.getString()))
    {
        ForceDir(fpath.getString());
    };

    CStream* str = GetReadStream();
    ArchivFile file;
    str->setPosition(f->Position);
    str->ReadData(&file, sizeof file);

    //Schreiben
    CUtiString FileName(target);
    FileName +=UTEXT("/");
    FileName += subpath;
    /*FileName +=UTEXT("/");
       FileName += name;*/
    CFileStream* sf = new CFileStream(FileName.getString(), S_WRITE);
    INT64 size = f->Info.Size;
    INT64 PufferSize = 65536;
    TCHAR* Puffer = new TCHAR[PufferSize];
    while (size > 0)
    {
        str->ReadData(Puffer, min(size, PufferSize));
        sf->WriteData(Puffer, min(size, PufferSize));
        size -= PufferSize;


    };
    delete []Puffer;
    delete sf;


    DeleteStream((CStream**)&str);
}

void CUtiArchiv::GetFilesInDir(TCHAR* dir, TCHAR* type, CCacheList * result)
{
  //  wcout << UTEXT("GetFilesInDir(") << dir << "," << type << endl;
    CUtiADirectory* Parent = GetDir(dir);
    result->deleteItems = true;
    for (int i = 0; i < Files.count; i++)
    {
        CUtiAFile* f = (CUtiAFile*)Files[i];
        if (f->Parent != Parent)
            continue;

        CUtiString RealPos;
        RealPos = StartPath+dir + UTEXT("/")+f->Name;
        bool b = FileExists(RealPos.getString());
        if (b)
            continue;

        CUtiString k;
        k = f->Name;
        k.ExtractFileExt();
        k= UTEXT('.')+k;
        if (k == type)
        {
            CUtiString *t = new CUtiString(f->Name);
            result->Add(t);
        }
    };
    CUtiString RealPos;
    RealPos = StartPath+dir + UTEXT("");
    Dir_FileInfo data;
    bool h = FindFirst(RealPos.getString(), &data);
    CUtiString* name;
    //wcout << h;
    if (h != false)
    {
        CUtiString k;
        k = data.name;
        k.ExtractFileExt();
        k= UTEXT('.')+k;
        if (k == type)
        {
            name = new CUtiString(data.name);
            result->Add(name);
        }
        while(FindNext(&data))
        {
            CUtiString k;
            k = data.name;
            k.ExtractFileExt();
            k= UTEXT('.')+k;
            if (k == type)
            {
                name = new CUtiString(data.name);
                result->Add(name);
            }

        }
    }
    FindClose(&data);
}

void CUtiArchiv::ExtractFile(TCHAR* name, TCHAR* target)
{
    CUtiAFile* f = GetFile(name);
    ExtractFileDirect(f, target);
}

int CUtiArchiv::GetDirSize(TCHAR* name)
{
    CUtiADirectory* dir = GetDir(name);
    if (!dir)
        return 0;
    return dir->Info.ChildrenCount;
}
