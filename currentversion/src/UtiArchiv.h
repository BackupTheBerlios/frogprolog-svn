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
#ifndef __UTIARCHIV__
#define __UTIARCHIV__
#include <math.h>
#include "Uti3DCore.h"
#include "Uti3DMath.h"
#include "UtiString.h"

class CUtiArchiv;

extern CUtiArchiv* MainArchive;
extern bool uti_inarchiv;

void InitArchive(TCHAR* name);
void FreeArchive();

CFileStream* UtiOpenFile(TCHAR* name);
bool UtiFileExists(TCHAR* name);
INT64 UtiFileSize(U_CHAR*name);

struct ArchivHeader
{
    UINT ID;
    USHORT MajorVersion;
    USHORT MinorVersion;
    UINT FilterCount;
    UINT FileCount;
    UINT DirCount;
    UINT Flags;
};

struct ArchivFile
{
    UINT ID; //Dateisignatur:1 //3: gel�cht
    INT64 Size;
    INT64 OriginalSize;
    INT64 Directory;
    INT64 Filter;
    TCHAR name[64];
};

struct ArchivDirectory
{
    UINT ID; //Directorysignatur:2//4: gel�cht
    INT64 Size;
    INT64 DirID;
    INT64 Directory;
    INT64 ChildrenCount;
    TCHAR name[64];
};


class CMinMaxFileStream : public CFileStream
{
public:
    ~CMinMaxFileStream();
    CMinMaxFileStream(TCHAR *name, int i, bool trunc=true, INT64 Min=0,INT64 Max=0xFFFFFFF);
    INT64 Min;
    INT64 Max;
    bool eof();
    void ReadData(void* data, unsigned int size);
    void setPosition(UINT i);
};

class CUtiADirectory;

class CUtiAFile : public CUtiOB
{
public:
    ArchivFile Info;
    CUtiString Name;
    INT64 Position;
    CUtiADirectory* Parent;
    void GetFileName(CUtiString &fn);
};

class CUtiADirectory : public CUtiOB
{
public:
    ArchivDirectory Info;
    CUtiString Name;
    INT64 Position;
    CUtiADirectory* Parent;
};

class CUtiArchiv : public CUtiOB
{
protected:
    ArchivHeader Header;
    CUtiAFile* LastExists;
    CCacheList Directories;
    void Load();
    void Init();
    CStream* GetReadStream();
    CStream* GetWriteStream();
    void DeleteStream(CStream* *str);
    CUtiADirectory* FindDir(INT64 ID);
    CUtiADirectory* GetDir(CUtiString Path);
    CUtiAFile* GetFile(CUtiString Path);
    //void AddFileToList(CUtiAFile* f);
    void AddRecursiv(TCHAR* dir, CUtiADirectory* Subdir, TCHAR* PathSubdir,TCHAR* types);
public:
    CCacheList Files;
    CUtiString Name;
    CUtiString StartPath;
    //CUtiListBox* FileList;
    //void FillList();
    INT64 GetFileSize();
    int GetFileCount();
    int GetDirCount();
    CUtiArchiv(CUtiString _Name);
    ~CUtiArchiv();
    CUtiADirectory* CreateDir(CUtiADirectory* Pos, TCHAR* name);
    void AddFile(TCHAR* FileName, TCHAR* Name, CUtiADirectory* Pos);
    void AddDir(TCHAR* dir, TCHAR* types, bool recursiv);
    void UtiDeleteFile(TCHAR* name);
    void Pack();
    void ExtractFile(TCHAR* name, TCHAR* target);
    void ExtractFileDirect(CUtiAFile* f, TCHAR* target);
    int GetDirSize(TCHAR* name);
    bool DoesFileExists(TCHAR* name);
    INT64 UFileSize(TCHAR* name);
    CFileStream* OpenFile(TCHAR* name);
    void GetFilesInDir(TCHAR* dir, TCHAR* type, CCacheList * result);
};

#endif
