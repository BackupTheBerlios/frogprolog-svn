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
#include "scanner.h"
#include "plparser.h"
#include "enginefactory.h"
#include "cppengine.h"
#include "wamengine.h"
#include "cppfactory.h"
#include "wamfactory.h"
#include "prolog_driver.h"
#include "utisystem.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <set>
using namespace std;

using namespace UtiFramework;

//#define USE_WAM

time_t tt;
//char* basedir;

void RegisterPredicates() {
   wcout << L"Basisbibliothek wird generiert" << endl;
    CallInfo p1[2];
    p1[0].type = ci_in_Integer;
    p1[1].type = ci_out_Integer;
    Program* p = Program::getInstance();
    p->ForeignPredicate(L"sqr", L"pl_foreign_sqrt", p1, 2, L"basepredicates");
    p->ForeignPredicate(L"assert", L"pl_foreign_assertz", 1, L"basepredicates");
    p->ForeignPredicate(L"asserta", L"pl_foreign_asserta", 1, L"basepredicates");
    p->ForeignPredicate(L"assertz", L"pl_foreign_assertz", 1, L"basepredicates");
    p->ForeignPredicate(L"assert", L"pl_foreign_assert2z", 2, L"basepredicates");
    p->ForeignPredicate(L"asserta", L"pl_foreign_assert2a", 2, L"basepredicates");
    p->ForeignPredicate(L"assertz", L"pl_foreign_assert2z", 2, L"basepredicates");
    
    p->ForeignPredicate(L"retract", L"pl_foreign_retract2", 2, L"basepredicates");
    p->ForeignPredicate(L"retract", L"pl_foreign_retract", 1, L"basepredicates");
    p->ForeignPredicate(L"retractall", L"pl_foreign_retractall", 1, L"basepredicates");
    p->ForeignPredicate(L"abolish", L"pl_foreign_abolish", 2, L"basepredicates");
    p->ForeignPredicate(L"=", L"pl_foreign_equal", 2, L"basepredicates");
    p->ForeignPredicate(L"\\=", L"pl_foreign_nonequal", 2, L"basepredicates");
    p->ForeignPredicate(L"is", L"pl_foreign_is", 2, L"basepredicates");
    p->ForeignPredicate(L"=:=", L"pl_foreign_arithequal", 2, L"basepredicates");
    p->ForeignPredicate(L"=\\=", L"pl_foreign_arithnonequal", 2, L"basepredicates");
    p->ForeignPredicate(L"<", L"pl_foreign_arithless", 2, L"basepredicates");
    p->ForeignPredicate(L"=<", L"pl_foreign_aritheqless", 2, L"basepredicates");
    p->ForeignPredicate(L">", L"pl_foreign_arithgreater", 2, L"basepredicates");
    p->ForeignPredicate(L">=", L"pl_foreign_aritheqgreater", 2, L"basepredicates");
    
    p->ForeignPredicate(L"fail", L"pl_foreign_fail", 0, L"basepredicates");
    p->ForeignPredicate(L"false", L"pl_foreign_fail", 0, L"basepredicates");
    p->ForeignPredicate(L"true", L"pl_foreign_true", 0, L"basepredicates");
    
    p->ForeignPredicate(L"==", L"pl_foreign_instequal", 2, L"basepredicates");
    p->ForeignPredicate(L"\\==", L"pl_foreign_instnonequal", 2, L"basepredicates");
    
    p->ForeignPredicate(L"@<", L"pl_foreign_instless", 2, L"basepredicates");
    p->ForeignPredicate(L"@=<", L"pl_foreign_insteqless", 2, L"basepredicates");
    p->ForeignPredicate(L"@>", L"pl_foreign_instgreater", 2, L"basepredicates");
    p->ForeignPredicate(L"@>=", L"pl_foreign_insteqgreater", 2, L"basepredicates");
    
    p->ForeignPredicate(L"bye", L"pl_foreign_bye", 0, L"basepredicates");
    p->ForeignPredicate(L"halt", L"pl_foreign_halt", 0, L"basepredicates");
    p->ForeignPredicate(L"repeat", L"pl_foreign_repeat", 0, L"basepredicates");
    
    //Meta Logic
    p->ForeignPredicate(L"var", L"pl_foreign_var", 1, L"basepredicates");
    p->ForeignPredicate(L"nonvar", L"pl_foreign_nonvar", 1, L"basepredicates");
    p->ForeignPredicate(L"ground", L"pl_foreign_ground", 1, L"basepredicates");
    p->ForeignPredicate(L"atom", L"pl_foreign_atom", 1, L"basepredicates");
    p->ForeignPredicate(L"float", L"pl_foreign_float", 1, L"basepredicates");
    p->ForeignPredicate(L"integer", L"pl_foreign_integer", 1, L"basepredicates");
    p->ForeignPredicate(L"number", L"pl_foreign_number", 1, L"basepredicates");
    p->ForeignPredicate(L"atomic", L"pl_foreign_atomic", 1, L"basepredicates");
    p->ForeignPredicate(L"simple", L"pl_foreign_simple", 1, L"basepredicates");
    p->ForeignPredicate(L"compound", L"pl_foreign_compound", 1, L"basepredicates");
    p->ForeignPredicate(L"write", L"pl_foreign_write", 1, L"basepredicates");
    p->ForeignPredicate(L"writeq", L"pl_foreign_writeq", 1, L"basepredicates");
    p->ForeignPredicate(L"nl", L"pl_foreign_nl", 0, L"basepredicates");
    p->ForeignPredicate(L"put", L"pl_foreign_put", 1, L"basepredicates");
    p->ForeignPredicate(L"tab", L"pl_foreign_tab", 1, L"basepredicates");
    p->ForeignPredicate(L"tell", L"pl_foreign_tell", 1, L"basepredicates");
    p->ForeignPredicate(L"telling", L"pl_foreign_telling", 1, L"basepredicates");
    p->ForeignPredicate(L"told", L"pl_foreign_told", 0, L"basepredicates");

    p->ForeignPredicate(L"read", L"pl_foreign_read", 1, L"basepredicates");
    //p->ForeignPredicate(L"call", L"pl_foreign_var", 1, L"basepredicates");
    p->ForeignPredicate(L"see", L"pl_foreign_see", 1, L"basepredicates");
    p->ForeignPredicate(L"seeing", L"pl_foreign_seeing", 1, L"basepredicates");
    p->ForeignPredicate(L"seen", L"pl_foreign_seen", 0, L"basepredicates");
    p->ForeignPredicate(L"at_end_of_stream", L"pl_foreign_at_end_of_stream", 0, L"basepredicates");

    p->ForeignPredicate(L"put_byte", L"pl_foreign_put_byte", 1, L"basepredicates");
    p->ForeignPredicate(L"put_char", L"pl_foreign_put_char", 1, L"basepredicates");
    p->ForeignPredicate(L"put_code", L"pl_foreign_put_code", 1, L"basepredicates");

    p->ForeignPredicate(L"flush_output", L"pl_foreign_flush_output", 0, L"basepredicates");
    p->ForeignPredicate(L"get_byte", L"pl_foreign_get_byte", 1, L"basepredicates");
    p->ForeignPredicate(L"get_code", L"pl_foreign_get_code", 1, L"basepredicates");
    p->ForeignPredicate(L"get_char", L"pl_foreign_get_char", 1, L"basepredicates");
    p->ForeignPredicate(L"get", L"pl_foreign_get_char", 1, L"basepredicates");
    p->ForeignPredicate(L"peek_byte", L"pl_foreign_peek_byte", 1, L"basepredicates");
    p->ForeignPredicate(L"peek_code", L"pl_foreign_peek_code", 1, L"basepredicates");
    p->ForeignPredicate(L"peek_char", L"pl_foreign_peek_char", 1, L"basepredicates");
    p->ForeignPredicate(L"skip", L"pl_foreign_skip", 1, L"basepredicates");

    p->ForeignPredicate(L"functor", L"pl_foreign_functor", 3, L"basepredicates");
    p->ForeignPredicate(L"arg", L"pl_foreign_arg", 3, L"basepredicates");
    p->ForeignPredicate(L"char_type", L"pl_foreign_char_type", 2, L"basepredicates");

    p->ForeignPredicate(L"atom_codes", L"pl_foreign_atom_codes", 2, L"basepredicates");
    p->ForeignPredicate(L"atom_chars", L"pl_foreign_atom_chars", 2, L"basepredicates");
    p->ForeignPredicate(L"char_code", L"pl_foreign_char_code", 2, L"basepredicates");
    p->ForeignPredicate(L"number_chars", L"pl_foreign_number_chars", 2, L"basepredicates");
    p->ForeignPredicate(L"number_codes", L"pl_foreign_number_codes", 2, L"basepredicates");
    p->ForeignPredicate(L"atom_number", L"pl_foreign_atom_number", 2, L"basepredicates");
    p->ForeignPredicate(L"name", L"pl_foreign_name", 2, L"basepredicates");
    p->ForeignPredicate(L"term_to_atom", L"pl_foreign_term_to_atom", 2, L"basepredicates");
    p->ForeignPredicate(L"atom_to_term", L"pl_foreign_atom_to_term", 3, L"basepredicates");
    p->ForeignPredicate(L"atom_concat", L"pl_foreign_atom_concat", 3, L"basepredicates");
    p->ForeignPredicate(L"concat_atom", L"pl_foreign_concat_atom2", 2, L"basepredicates");
    p->ForeignPredicate(L"concat_atom", L"pl_foreign_concat_atom3", 3, L"basepredicates");
    p->ForeignPredicate(L"atom_length", L"pl_foreign_atom_length", 2, L"basepredicates");
    p->ForeignPredicate(L"atom_prefix", L"pl_foreign_atom_prefix", 2, L"basepredicates");
    p->ForeignPredicate(L"sub_atom", L"pl_foreign_sub_atom", 5, L"basepredicates");


};

void createMain(const string &oscname, const string &output, const string &outputname) {
    wofstream osc;
    osc.open(oscname.c_str());
    osc << L"#include \"" << outputname.c_str() << L".h\"" << endl << endl;
    osc << L"#include <iostream>" << endl << endl;
    osc << L"using namespace std;" << endl;
    osc << L"using namespace PrologSystem;" << endl << endl;
    osc << L"int main() {" << endl;
    osc << L"   pl_Initialize();" << endl;
    osc << L"   pl_initModule_" << outputname.c_str() << "();" << endl << endl;
    // osc << L"   " << outputname.c_str() << L"* prog = new " << outputname.c_str() << L"();" << endl;
    osc << L"   plr_init();" << endl<<endl;
    //osc << L"   delete prog;" << endl;
    osc << L"   pl_Free();" << endl;
    osc << L"   return 0;" << endl;
    osc << L"};" << endl;
    osc.close();
}

enum TParamMode {pmNone,pmOutput};

int docompile(string sourcefile, string output, bool isModule, bool makeNative, bool baselib)
{
   //Program::init();
   string outputname;
   CUtiString sin;
   sin.LoadAnsi(output.c_str());
   sin.ExtractFileName();
   char* c2 = sin.GetAnsi();
   outputname = c2;
   delete [] c2;

    
    /*    UtiProlog::EngineFactory* cf = NULL;
    #ifdef USE_WAM
        cf = new WAM::WAMFactory();
        Program* prog = new WAM::WAMProgram(cf);
        BaseTarget* t = new WAM::WAMTarget();
    #else
        cf = new Cpp::CppFactory();
        Program* prog = new Cpp::CppProgram(cf);
        ((Cpp::CppProgram*)prog)->progname.LoadAnsi(output.c_str());
        BaseTarget* t = new Cpp::CppTarget(&outstreamcpp, &outstreamh);
    #endif
    */
    BaseTarget* t= NULL;
    
    Program::getInstance()->progname.LoadAnsi(outputname.c_str());
    if (isModule/* && (output == "bip" || output == "modules/bip" || output == "./modules/bip")*/ && baselib) {
       RegisterPredicates();
    } else {
       //Standardmodul laden
       CUtiString bd;
      // bd.LoadAnsi(basedir);
       bd = L"bip";
       Program::getInstance()->loadModule(bd.c_str());
    };
    
    prolog_driver* driver = new prolog_driver();
    driver->parse(sourcefile);
    if (Program::getInstance()->haserror) return 2;

    wofstream outstreamcpp;
    wofstream outstreamh;
    string outputcpp = output+".cpp";
    outstreamcpp.open(outputcpp.c_str());
    if (!outstreamcpp.good()) {
        wcout << L"Error: Die Datei " << outputcpp.c_str() << L" konnte nicht erzeugt werden\n";
        return 2;
    };

    outstreamcpp << L"//FrogProlog generated: " <<asctime(localtime(&tt)) <<endl;
    outputcpp = outputname+".h";

    outstreamcpp << L"#include \"" << outputcpp.c_str() << L"\""<< endl;
    outputcpp = output+".h";
    outstreamh.open(outputcpp.c_str());
    outstreamh << L"//FrogProlog generated: " <<asctime(localtime(&tt))<<endl;

    char*c = getenv("FP_BACKEND");
    if (c == NULL || (strcmp(c, "CPP")==0)) {
        t = new Cpp::CppTarget(&outstreamcpp, &outstreamh);
    } else if (strcmp(c, "WAM")==0) {
        t = new WAM::WAMTarget();
    };

    if (!Program::getInstance()->haserror)
        Program::getInstance()->perform(t);
    if (isModule) {
       string outputmod= output+".module";
       
       Program::getInstance()->performModule(converttowide(outputmod.c_str()));
    };
#ifdef USE_WAM

    ((WAMTarget)t)->container->SaveToFile(L"test.obj");
#endif

    bool er = Program::getInstance()->haserror;
   if (er) return 2;
    delete t;
    //    delete cf;
    //   delete prog;
    wcout << "Fertig: Programmerstellung" << endl;
    c = getenv("FP_BACKEND");

    if (c == NULL || (strcmp(c, "CPP")==0)) {
        //outputname
        if (er == false && makeNative) {
            if (isModule) {
	       bool isStatic = true;
	       if (isStatic) {
		  outputcpp = output+".cpp";
		  string outputobject = output+".o";
		  char* command = new char[2048];
		  CUtiString woutputfile = converttowide(output.c_str());
		  CUtiString woutputdir = woutputfile;
		  woutputdir.ExtractFilePath();
		  woutputfile.ExtractFileName();
		  string popt = converttomulti(woutputfile.c_str());
		  woutputfile = woutputdir+ L"/lib"+woutputfile;
		  
		  string opt = converttomulti(woutputfile.c_str());
		  //snprintf(command, 2048, "g++ -g -I\"%s/src\" -L\"%s/debug/src\" -L\"%s/src\" -c \"%s\" \n", basedir, basedir, basedir, outputcpp.c_str());
		  

                  snprintf(command, 2048, "g++ -g -c -L./ -I./ \"%s\" \n", outputcpp.c_str());
		  
		  wcout << command;
		  int i = system(command);
		  if (i != 0) {
		     er = true;
		  } else {
		     snprintf(command, 2048, "ar crs \"%s.a\" \"%s.o\"\n", opt.c_str(), popt.c_str());
		     wcout << command;
		     i = system(command);
		     snprintf(command, 2048, "ranlib \"%s.a\"\n", opt.c_str());
		     wcout << command;
		     i = system(command);
		  };
		  delete command;
	       } else {
                outputcpp = output+".cpp";
                char* command = new char[2048];
		CUtiString woutputfile = converttowide(output.c_str());
		CUtiString woutputdir = woutputfile;
		woutputdir.ExtractFilePath();
		woutputfile.ExtractFileName();
		woutputfile = woutputdir+ L"/lib"+woutputfile;
		string opt = converttomulti(woutputfile.c_str());
		//snprintf(command, 2048, "g++ -g -I\"%s/src\" -L\"%s/debug/src\" -L\"%s/src\" \"%s\" -shared -o \"%s.so\"\n", basedir, basedir, basedir, outputcpp.c_str(),opt.c_str());

                snprintf(command, 2048, "g++ -g  -L./ -I./ \"%s\" -shared -o \"%s.so\"\n", outputcpp.c_str(),opt.c_str());
                wcout << command;
                int i = system(command);
                if (i != 0)
                    er = true;
                delete command;
	       };

            } else {
                string oscname = output+"_main_file.cpp";
                createMain(oscname, output, outputname);
                outputcpp = output+".cpp";
		string command;
		command = "g++ -g -L./ -I./ ";
                 // command += " -I\"";
		//command += basedir+string("/src\" ");
		set<string> paths;
		//command += " -L\"";
		//command += basedir+string("/debug/src\" -L\"");
		//command += basedir+string("/src\" ");
                command += string(" \"");
		command += outputcpp+string("\" \"");
		command += oscname+string("\" ");
		for (int i = 0; i < Program::getInstance()->modules.count; i++) {
		   Module* m = (Module*)Program::getInstance()->modules[i];
		   CUtiString s = m->Path;
		   s.ExtractFilePath();
		   string p = converttomulti(s.c_str());
		   if (paths.find(p) == paths.end()) {
		   command += " -I\"";
		   command += p;
		   command += "\" ";
		   command += " -L\"";
		   command += p;
		   command += "\" ";
		   p = converttomulti(m->Name.c_str());
		   command += " -l";
		   command += p;
		   command += " ";
		   paths.insert(p);
		   };
		};
		
		command += string(" -lfrog -o \"");
		command += output+string("\"\n");
	        
		wcout << command.c_str();
		int i = system(command.c_str());
                if (i != 0)
                    er = true;
               // delete command;
            };
            wcout << "Fertig: Compilieren" << endl;
        } else {
           //   if(!makeNative)
           //  wcout << "Aufgrund von Fehlern wird die native Kompilierung nicht gestartet." << endl;
        }
    } else if (strcmp(c, "WAM")==0) {
    }
    ;
    delete driver;
    return er ? 2 : 0;
}


int main(int argc, char* argv[]) {
   
    time(&tt);
    char* c;

    if (argc < 2) {
        wcout << L"FrogProlog 0.2 " << __DATE__ << endl;
        wcout << L"   (c) Staud" << endl;
        wcout << L"------------------------------" << endl;
        wcout << L"Verwendung: " << argv[0] << " eingabedatei [-o ausgabedatei] [-m] [-c] [-n] [-Ldir]" << endl;
        return 1;
    };
    string output="a";
    string outputname="a";
    string sourcefile="test.pl";
    bool hasOutput=false;
    bool hasSource = false;
    bool isModule = false;
    bool makeNative = true;
    Program::getInstance()->addLibDir(L"/usr/include");
    Program::getInstance()->addLibDir(L"/usr/local/include");
    Program::getInstance()->addLibDir(L"./");
    for (int i = 1; i < argc; i++) {
        string com = argv[i];
        if (com.length() == 0)
            continue;
        /*if (com == "-include") {
           wcout << L" -I" << basedir << "/src " << L" -I" << basedir << "/modules ";
           return 0;
        }
        if (com == "-lib") {
           wcout << L" -L" << basedir << "/modules "<< L" -L" << basedir << "/debug/src "<< L" -L" << basedir << "/src ";
         return 0;
        }*/
        if (com[0] == '-') {
            //Command
            if (com.length() == 1) {
                wcout << L"Ungültiger Parameter." << endl;
                return 1;
            };
            TParamMode mode = pmNone;
            if (com[1] == '-') {
                //complexer Parameter
            } else {
                switch (com[1]) {
                case 'o': {
                        mode = pmOutput;
                    };
                    break;
                case 'm': {
                        isModule = true;
                    };
                    break;
		case 'n': {
		       makeNative = true;
		    };
		    break;
		case 'c': {
		       makeNative = false;
		    }; break;
                case 'L': {
                       com.erase(0, 2);
                       CUtiString str;
                       str.LoadAnsi(com.c_str());
                       Program::getInstance()->addLibDir(str);
                    };  break;
                default: {
                        wcout << L"Ungültiger Parameter." << endl;
                        return 1;
                    };

                };
            };
            switch (mode) {
            case pmOutput: {
                    if (i == argc-1) {
                        wcout << L"Ausgabedatei erwarten" << endl;
                        return 1;
                    };
                    if (!hasOutput) {
                        output = argv[i+1];
                        i++;
                    } else {
                        wcout << L"Es können nicht mehrere Zieldateien definiert werden." << endl;
                        return 1;
                    }
                }
                ;
                break;
            };
        } else {
            if (!hasSource) {
                sourcefile = com;
                hasSource = true;
            } else {
                wcout << L"Es können nicht mehrere Quelldateien definiert werden." << endl;
                return 1;
            }
        };

    };
    wcout << L"FrogProlog 0.2 " << __DATE__ << endl;
    if (!hasSource) {
        wcout << L"Bitte geben Sie eine Quelldatei an." << endl;
        return 1;
    };
    
   /* CUtiString bd;
       bd.LoadAnsi(basedir);
       bd += L"/modules/bip.module";
     CUtiString bd1;
       bd1.LoadAnsi(basedir);
       bd1 += L"/modules/libbip.a";
     if (!FileExists(bd.c_str()) || !FileExists(bd1.c_str())) {
       wcout << L"Versuche Basisbibliothek zu kompilieren" << endl;
       string strfile = basedir;
       strfile += "/modules/base.pl";
       string outputfile = basedir;
       outputfile += "/modules/bip";
       docompile(strfile, outputfile, true, true, true);
    };
    if (!FileExists(bd.c_str()) || !FileExists(bd1.c_str())) {
       wcout << L"Basisbibliothek nicht gefunden" << endl;
       return 2;
    };*/
    return docompile(sourcefile, output, isModule, makeNative, false);
};

