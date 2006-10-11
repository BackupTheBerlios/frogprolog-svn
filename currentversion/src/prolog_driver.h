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
#ifndef PROLOG_DRIVER_H
#define PROLOG_DRIVER_H
#include <string>
#include <fstream>
#include<map>

/*union YYSTYPE;
namespace yy
{
   class location;
   class prologxx_parser;
}
*/
/*namespace UtiProlog
{
   struct PositionInfo;
}
using namespace UtiProlog;*/
#ifdef __BASEPREDICATES__

namespace UtiExternProlog
{
   class Term;
   struct PositionInfo;
}
using namespace UtiExternProlog;

#else

namespace UtiProlog
{
   class Term;
   struct PositionInfo;
}
using namespace UtiProlog;

#endif 

/**
@author Michael Staud
*/
class prolog_driver{
public:
	Term* newstr;
	prolog_driver();
    virtual ~prolog_driver();
    
   // void scan_begin();
   // void scan_end();
    bool trace_scanning;
    void parse(const std::string & f);
    void parse(std::wistream & f);
    std::string file;
    bool trace_parsing;
  //  void error(const yy::location& l, const std::string& m);
    void error(const PositionInfo* l, const std::wstring& m);
    void error(const std::string&m);

};

#endif
