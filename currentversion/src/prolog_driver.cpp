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
#include "prolog_driver.h"
//#include "plparse.tab.h"
#include "parsersystem.h"
#include <fstream>



prolog_driver::prolog_driver() {
    //prog = pr;
   // cf = _cf;
    //cfex = cf;
    trace_scanning = false;
    trace_parsing = false;
}


prolog_driver::~prolog_driver() {}

void prolog_driver::parse(const std::string & f) {
    file = f;//cfex = cf;
//    scan_begin();
    wifstream str1;
    str1.open(f.c_str());
    if (!str1.good()) {
       wcout << L"Die Datei " << f.c_str() << L" konnte nicht geöffnet werden." << endl;
       return;
    };
    ParserSystem* ps = new ParserSystem(this, &str1);
    ps->pProgram();
    /*lexer = new yyFlexLexer(&str1);
    yy::prologxx_parser parser(*this);
    parser.set_debug_level(trace_parsing);
    parser.parse();
    delete lexer;
    lexer = NULL;*/
    delete ps;
 //   scan_end();
    //cfex = NULL;
}

void prolog_driver::parse(std::wistream & f) {
   ParserSystem* ps = new ParserSystem(this, &f);
   newstr = ps->pSTerm();
   delete ps;
    
}



void prolog_driver::error(const PositionInfo* l, const std::wstring& m)
{
#ifndef __BASEPREDICATES__
    Program::getInstance()->haserror = true;
#endif
    std::wcout << l->beginline << "/" << l->begincolumn << ": " << m.c_str() <<  std::endl;
};

void prolog_driver::error(const std::string&m) {
#ifndef __BASEPREDICATES__
    Program::getInstance()->haserror = true;
#endif
    std::wcout << m.c_str()  <<  std::endl;
}

/*
int yylex(YYSTYPE* yylval, yy::location* yylloc, prolog_driver&driver) {
    flex_yylval = yylval;
    flex_yylloc = yylloc;
    flex_driver = &driver;
    lexer->yylex();
}*/

