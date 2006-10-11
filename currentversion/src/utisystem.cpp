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

 #include <sys/timex.h>
 #include <unistd.h>
 #include <dirent.h>
 #include <wchar.h>
 #include <iostream>
 #include "utisystem.h"
 #include <sys/stat.h>
 #include <dlfcn.h>
 
 namespace UtiFramework {
 
 long int SubtractSecounds = 0;
 
 void initTime()
 {
    ntptimeval time;
    ntp_gettime(&time);
    SubtractSecounds = time.time.tv_sec;
    
    
 }
 
 double getCurrentTime()
 {
 
    ntptimeval time;
    ntp_gettime(&time);
    time.time.tv_sec -= SubtractSecounds;
    return time.time.tv_sec + (double)time.time.tv_usec/1000000.0;
 }
 
 
const CUtiString converttowide(const char*c)
{
  
   size_t len = strlen(c);
   wchar_t tmp[1];
   mbstate_t state;
   memset(&state, 0, sizeof(state));
   size_t nbytes;
   CUtiString result;
   while((nbytes = mbrtowc(tmp, c, len, &state)) > 0) {
       if (nbytes >= (size_t) -2) {
          nbytes = 1;
          tmp[0] = *c;
       };
       result += tmp[0];
       len -= nbytes;
       c += nbytes;      
   
   }
   return result;
   
}

const string converttomulti(const wchar_t * c)
{
   mbstate_t state;
   memset(&state, 0, sizeof(state));
   int buffersize = wcslen(c)*2+3;
   int currentsize = 0;
   char* wp = new char[buffersize]; 
   char* start = wp; 
   do {
      size_t nbytes;
      nbytes = wcrtomb(wp, *c, &state);
      if (nbytes == (size_t)-1) {
         return "";      
      }
      wp += nbytes;
      currentsize += nbytes;
      if (currentsize >= buffersize) {
         cerr << "converttomulti: Fehler Buffer ist zu klein für den String";
	 delete [] wp;
         return "";
      
      }
      
      c++;
   } while(*c != L'\0');
   *wp = 0;
   string result = start;
   delete [] start;
   return result;

}

const CUtiString getCurrentDir()
{

   char*c =  getcwd(NULL, 0);
   CUtiString s = converttowide(c);
   return s;
}

void ChangeDir(CUtiString str)
{
   string k = converttomulti(str.c_str());
   chdir(k.c_str());
}

bool FindFirst(CUtiString path, Dir_FileInfo *fi)
{
   fi->Dir = NULL;
   fi->entity = NULL;
   DIR *dp;
   dirent *ep;
   dirent direntity;
   string k = converttomulti(path.c_str());
   dp = opendir (k.c_str());
    if (dp != NULL)
    {
            readdir_r(dp, &direntity, &ep);
	    if (!ep) {
	       closedir(dp);
	       return false;
	    
	    };
	    fi->dir = false;
	    fi->Dir = dp;
	    fi->entity = ep;
	    fi->name = converttowide(ep->d_name);
	    fi->size = getFileSize(fi->name);
	    return true;
   } else {
      return false;
   }
};

int getFileSize(CUtiString path) 
{
        //wcout << "getFileSize: " << path.getString() << "\n";
        struct stat file;    
	string k = converttomulti(path.c_str());  
       // wcout << k <<endl;
        if(!stat(k.c_str(), &file))
        {
           return file.st_size;
        }
           
        return -1;
}

double getFileDate(CUtiString path, TFileDateType type)
{
   struct stat file;    
   string k = converttomulti(path.c_str());  
       // wcout << k <<endl;
   if(!stat(k.c_str(), &file))
   {
      if (type == dtAccess) {
         return file.st_atime;
      } else if (type == dtModification) {
         return file.st_mtime;
      } else {
         return file.st_ctime;
      };
   }
   return 0;
};

bool FindNext(Dir_FileInfo*fi)
{
   DIR *dp= (DIR*)fi->Dir;
   dirent *ep;
   dirent direntity;
   readdir_r(dp, &direntity, &ep);
   if(!ep)return false;
  
   fi->Dir = dp;
   fi->entity = ep;
   fi->name = converttowide(ep->d_name);
   fi->size = getFileSize(fi->name);
   fi->dir = false;
   
   return true;
   
};

void FindClose(Dir_FileInfo*fi)
{
   DIR *dp= (DIR*)fi->Dir;
   if (dp) {
      closedir(dp);   
   };
};



void sleep(int ms)
{

}

LPVOID UtiLoadLibrary(wchar_t* name)
{

   string s = converttomulti(name);
   //s = "lib"+s;
   //s += ".so";
   if (s == "/home/Staud/Programme/spacedata/ecool/game/libecool.0") {
    s = "/home/Staud/Programme/ecool/debug/src/.libs/libecool.0";
   
   }
   LPVOID m = NULL;//dlopen(s.c_str(), RTLD_NOW);
   if (!m) {
      wcout << "Die Bibliothek " << name << " wurde nicht gefunden." << endl;
   
   }
   return m;
}

void UtiFreeLibrary(LPVOID module)
{
  // dlclose(module);
}

LPVOID UtiGetProcAddress(LPVOID module, char* name)
{
  // LPVOID m = dlsym(module, name);
   LPVOID m = NULL;
   if (!m) {
      wcout << "Die Funktion " << name << " wurde in der Bibliothek nicht gefunden" << endl;
   
   }
   return m;
}

 
 
};
