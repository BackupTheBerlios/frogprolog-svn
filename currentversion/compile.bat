g++ -D__BASEPREDICATES__ -g -I./tmp/ -I./src/ ./tmp/test.cpp ./src/testcode.cpp ./src/prologenvironment.cpp ./src/prolognames.cpp ./src/basepredicates.cpp ./src/frogprolog.cpp ./src/lex.yy.cc ./src/externparser.cpp ./src/plparse.tab.cpp ./src/prolog_driver.cpp ./src/enginefactory.cpp -o ./tmp/test && gdb ./tmp/test