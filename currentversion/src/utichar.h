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
#ifndef _UTICHAR_
#define _UTICHAR_

#define TCHAR wchar_t
#define TEXT(x) L ## x

/* Formatted i/o */

#define _tprintf    wprintf
#define _tcprintf   _cwprintf
#define _ftprintf   fwprintf
#define _stprintf   swprintf
#define _sctprintf  _scwprintf
#define _sntprintf  _snwprintf
#define _vtprintf   vwprintf
#define _vftprintf  vfwprintf
#define _vstprintf  vswprintf
#define _vsctprintf _vscwprintf
#define _vsntprintf _vsnwprintf
#define _tscanf     wscanf
#define _tcscanf    _cwscanf
#define _ftscanf    fwscanf
#define _stscanf    swscanf
#define _sntscanf   _snwscanf


/* Unformatted i/o */

#define _fgettc     fgetwc
#define _fgettchar  _fgetwchar
#define _fgetts     fgetws
#define _fputtc     fputwc
#define _fputtchar  _fputwchar
#define _fputts     fputws
#define _cputts     _cputws
#define _cgetts     _cgetws
#define _gettc      getwc
#define _gettch     _getwch
#define _gettche    _getwche
#define _gettchar   getwchar
#define _getts      _getws
#define _puttc      putwc
#define _puttchar   putwchar
#define _puttch     _putwch
#define _putts      _putws
#define _ungettc    ungetwc
#define _ungettch   _ungetwch


/* String conversion functions */

#define _tcstod     wcstod
#define _tcstol     wcstol
#define _tcstoul    wcstoul
#define _tcstoi64   _wcstoi64
#define _tcstoui64  _wcstoui64
#define _tstof      _wtof
#define _tstol      _wtol
#define _tstoi      _wtoi
#define _tstoi64    _wtoi64

#define _itot       _itow
#define _ltot       _ltow
#define _ultot      _ultow
#define _ttoi       _wtoi
#define _ttol       _wtol

#define _ttoi64     _wtoi64
#define _i64tot     _i64tow
#define _ui64tot    _ui64tow

/* String functions */

#define _tcscat     wcscat
#define _tcschr     wcschr
#define _tcscpy     wcscpy/* Formatted i/o */

#define _tprintf    wprintf
#define _tcprintf   _cwprintf
#define _ftprintf   fwprintf
#define _stprintf   swprintf
#define _sctprintf  _scwprintf
#define _sntprintf  _snwprintf
#define _vtprintf   vwprintf
#define _vftprintf  vfwprintf
#define _vstprintf  vswprintf
#define _vsctprintf _vscwprintf
#define _vsntprintf _vsnwprintf
#define _tscanf     wscanf
#define _tcscanf    _cwscanf
#define _ftscanf    fwscanf
#define _stscanf    swscanf
#define _sntscanf   _snwscanf


/* Unformatted i/o */

#define _fgettc     fgetwc
#define _fgettchar  _fgetwchar
#define _fgetts     fgetws
#define _fputtc     fputwc
#define _fputtchar  _fputwchar
#define _fputts     fputws
#define _cputts     _cputws
#define _cgetts     _cgetws
#define _gettc      getwc
#define _gettch     _getwch
#define _gettche    _getwche
#define _gettchar   getwchar
#define _getts      _getws
#define _puttc      putwc
#define _puttchar   putwchar
#define _puttch     _putwch
#define _putts      _putws
#define _ungettc    ungetwc
#define _ungettch   _ungetwch


/* String conversion functions */

#define _tcstod     wcstod
#define _tcstol     wcstol
#define _tcstoul    wcstoul
#define _tcstoi64   _wcstoi64
#define _tcstoui64  _wcstoui64
#define _tstof      _wtof
#define _tstol      _wtol
#define _tstoi      _wtoi
#define _tstoi64    _wtoi64

#define _itot       _itow
#define _ltot       _ltow
#define _ultot      _ultow
#define _ttoi       _wtoi
#define _ttol       _wtol

#define _ttoi64     _wtoi64
#define _i64tot     _i64tow
#define _ui64tot    _ui64tow

/* String functions */

#define _tcscat     wcscat
#define _tcschr     wcschr
#define _tcscpy     wcscpy
#define _tcscspn    wcscspn
#define _tcslen     wcslen
#define _tcsncat    wcsncat
#define _tcsncpy    wcsncpy
#define _tcspbrk    wcspbrk
#define _tcsrchr    wcsrchr
#define _tcsspn     wcsspn
#define _tcsstr     wcsstr
#define _tcstok     wcstok
#define _tcserror   _wcserror
#define __tcserror  __wcserror

#define _tcsdup     _wcsdup
#define _tcsnset    _wcsnset
#define _tcsrev     _wcsrev
#define _tcsset     _wcsset

#define _tcscmp     wcscmp
#define _tcsicmp    _wcsicmp
#define _tcsnccmp   wcsncmp
#define _tcsncmp    wcsncmp
#define _tcsncicmp  _wcsnicmp
#define _tcsnicmp   _wcsnicmp

#define _tcscoll    wcscoll
#define _tcsicoll   _wcsicoll
#define _tcsnccoll  _wcsncoll
#define _tcsncoll   _wcsncoll
#define _tcsncicoll _wcsnicoll
#define _tcsnicoll  _wcsnicoll


/* Execute functions */

#define _texecl     _wexecl
#define _texecle    _wexecle
#define _texeclp    _wexeclp
#define _texeclpe   _wexeclpe
#define _texecv     _wexecv
#define _texecve    _wexecve
#define _texecvp    _wexecvp
#define _texecvpe   _wexecvpe

#define _tspawnl    _wspawnl
#define _tspawnle   _wspawnle
#define _tspawnlp   _wspawnlp
#define _tspawnlpe  _wspawnlpe
#define _tspawnv    _wspawnv
#define _tspawnve   _wspawnve
#define _tspawnvp   _wspawnvp
#define _tspawnvp   _wspawnvp
#define _tspawnvpe  _wspawnvpe

#define _tsystem    _wsystem


/* Time functions */

#define _tasctime   _wasctime
#define _tctime     _wctime
#define _tctime64   _wctime64
#define _tstrdate   _wstrdate
#define _tstrtime   _wstrtime
#define _tutime     _wutime
#define _tutime64   _wutime64
#define _tcsftime   wcsftime


/* Directory functions */

#define _tchdir     _wchdir
#define _tgetcwd    _wgetcwd
#define _tgetdcwd   _wgetdcwd
#define _tmkdir     _wmkdir
#define _trmdir     _wrmdir


/* Environment/Path functions */

#define _tfullpath  _wfullpath
#define _tgetenv    _wgetenv
#define _tmakepath  _wmakepath
#define _tpgmptr    _wpgmptr
#define _tputenv    _wputenv
#define _tsearchenv _wsearchenv
#define _tsplitpath _wsplitpath


/* Stdio functions */

#define _tfdopen    _wfdopen
#define _tfsopen    _wfsopen
#define _tfopen     _wfopen
#define _tfreopen   _wfreopen
#define _tperror    _wperror
#define _tpopen     _wpopen
#define _ttempnam   _wtempnam
#define _ttmpnam    _wtmpnam


/* Io functions */

#define _taccess    _waccess
#define _tchmod     _wchmod
#define _tcreat     _wcreat
#define _tfindfirst _wfindfirst
#define _tfindfirst64   _wfindfirst64
#define _tfindfirsti64  _wfindfirsti64
#define _tfindnext  _wfindnext
#define _tfindnext64    _wfindnext64
#define _tfindnexti64   _wfindnexti64
#define _tmktemp    _wmktemp
#define _topen      _wopen
#define _tremove    _wremove
#define _trename    _wrename
#define _tsopen     _wsopen
#define _tunlink    _wunlink

#define _tfinddata_t    _wfinddata_t
#define _tfinddata64_t  __wfinddata64_t
#define _tfinddatai64_t _wfinddatai64_t


/* Stat functions */

#define _tstat      _wstat
#define _tstat64    _wstat64
#define _tstati64   _wstati64


/* Setlocale functions */

#define _tsetlocale _wsetlocale


/* Redundant "logical-character" mappings */

#define _tcsclen    wcslen
#define _tcsnccat   wcsncat
#define _tcsnccpy   wcsncpy
#define _tcsncset   _wcsnset

#define _tcsdec     _wcsdec
#define _tcsinc     _wcsinc
#define _tcsnbcnt   _wcsncnt
#define _tcsnccnt   _wcsncnt
#define _tcsnextc   _wcsnextc
#define _tcsninc    _wcsninc
#define _tcsspnp    _wcsspnp

#define _tcslwr     _wcslwr
#define _tcsupr     _wcsupr
#define _tcsxfrm    wcsxfrm
#define _tcscspn    wcscspn
#define _tcslen     wcslen
#define _tcsncat    wcsncat
#define _tcsncpy    wcsncpy
#define _tcspbrk    wcspbrk
#define _tcsrchr    wcsrchr
#define _tcsspn     wcsspn
#define _tcsstr     wcsstr
#define _tcstok     wcstok
#define _tcserror   _wcserror
#define __tcserror  __wcserror

#define _tcsdup     _wcsdup
#define _tcsnset    _wcsnset
#define _tcsrev     _wcsrev
#define _tcsset     _wcsset

#define _tcscmp     wcscmp
#define _tcsicmp    _wcsicmp
#define _tcsnccmp   wcsncmp
#define _tcsncmp    wcsncmp
#define _tcsncicmp  _wcsnicmp
#define _tcsnicmp   _wcsnicmp

#define _tcscoll    wcscoll
#define _tcsicoll   _wcsicoll
#define _tcsnccoll  _wcsncoll
#define _tcsncoll   _wcsncoll
#define _tcsncicoll _wcsnicoll
#define _tcsnicoll  _wcsnicoll


/* Execute functions */

#define _texecl     _wexecl
#define _texecle    _wexecle
#define _texeclp    _wexeclp
#define _texeclpe   _wexeclpe
#define _texecv     _wexecv
#define _texecve    _wexecve
#define _texecvp    _wexecvp
#define _texecvpe   _wexecvpe

#define _tspawnl    _wspawnl
#define _tspawnle   _wspawnle
#define _tspawnlp   _wspawnlp
#define _tspawnlpe  _wspawnlpe
#define _tspawnv    _wspawnv
#define _tspawnve   _wspawnve
#define _tspawnvp   _wspawnvp
#define _tspawnvp   _wspawnvp
#define _tspawnvpe  _wspawnvpe

#define _tsystem    _wsystem


/* Time functions */

#define _tasctime   _wasctime
#define _tctime     _wctime
#define _tctime64   _wctime64
#define _tstrdate   _wstrdate
#define _tstrtime   _wstrtime
#define _tutime     _wutime
#define _tutime64   _wutime64
#define _tcsftime   wcsftime


/* Directory functions */

#define _tchdir     _wchdir
#define _tgetcwd    _wgetcwd
#define _tgetdcwd   _wgetdcwd
#define _tmkdir     _wmkdir
#define _trmdir     _wrmdir


/* Environment/Path functions */

#define _tfullpath  _wfullpath
#define _tgetenv    _wgetenv
#define _tmakepath  _wmakepath
#define _tpgmptr    _wpgmptr
#define _tputenv    _wputenv
#define _tsearchenv _wsearchenv
#define _tsplitpath _wsplitpath


/* Stdio functions */

#define _tfdopen    _wfdopen
#define _tfsopen    _wfsopen
#define _tfopen     _wfopen
#define _tfreopen   _wfreopen
#define _tperror    _wperror
#define _tpopen     _wpopen
#define _ttempnam   _wtempnam
#define _ttmpnam    _wtmpnam


/* Io functions */

#define _taccess    _waccess
#define _tchmod     _wchmod
#define _tcreat     _wcreat
#define _tfindfirst _wfindfirst
#define _tfindfirst64   _wfindfirst64
#define _tfindfirsti64  _wfindfirsti64
#define _tfindnext  _wfindnext
#define _tfindnext64    _wfindnext64
#define _tfindnexti64   _wfindnexti64
#define _tmktemp    _wmktemp
#define _topen      _wopen
#define _tremove    _wremove
#define _trename    _wrename
#define _tsopen     _wsopen
#define _tunlink    _wunlink

#define _tfinddata_t    _wfinddata_t
#define _tfinddata64_t  __wfinddata64_t
#define _tfinddatai64_t _wfinddatai64_t


/* Stat functions */

#define _tstat      _wstat
#define _tstat64    _wstat64
#define _tstati64   _wstati64


/* Setlocale functions */

#define _tsetlocale _wsetlocale


/* Redundant "logical-character" mappings */

#define _tcsclen    wcslen
#define _tcsnccat   wcsncat
#define _tcsnccpy   wcsncpy
#define _tcsncset   _wcsnset

#define _tcsdec     _wcsdec
#define _tcsinc     _wcsinc
#define _tcsnbcnt   _wcsncnt
#define _tcsnccnt   _wcsncnt
#define _tcsnextc   _wcsnextc
#define _tcsninc    _wcsninc
#define _tcsspnp    _wcsspnp

#define _tcslwr     _wcslwr
#define _tcsupr     _wcsupr
#define _tcsxfrm    wcsxfrm

#endif

