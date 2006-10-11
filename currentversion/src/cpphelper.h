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
#ifndef __CPPHELPER__
#define __CPPHELPER__

#define oout (*((CppTarget*)t)->str)
#define oout_newline ((CppTarget*)t)->newline
#define oout_incdepth ((CppTarget*)t)->incdepth
#define oout_decdepth ((CppTarget*)t)->decdepth
#define idname(A) (idbase.idToIdentifierCode(A))
#define idrealname(A) (idbase.idToIdentifierIdent(A))
#define target ((CppTarget*)t)

#endif
