.PHONY: all clean
BB = g++ -Wall 

all: bin/main.exe

bin/main.exe: repository build/Labor.o build/mySimpleComputer.o build/myTerminal.o build/myBigChar.o build/myKeyboard.o build/myTimer.o build/alucu.o build/simpleassembler.o libs/libmySimpleComputer.a libs/libmyTerm.a libs/libmyBigChar.a libs/libmyKeyboard.a libs/libTimer.a libs/libAluCu.a libs/libSimpleAssembler.a 1 2 3 4 5 6
	$(BB) build/Labor.o -L./libs -lmySimpleComputer -lmyTerm -lmyKeyboard -lmyBigChar -lTimer -lAluCu -lSimpleAssembler -o bin/main.exe

build/Labor.o: Labor.cpp
	$(BB) -c -o build/Labor.o Labor.cpp 

build/mySimpleComputer.o: mySimpleComputer.cpp
	$(BB) -c -o build/mySimpleComputer.o mySimpleComputer.cpp 
build/myTerminal.o: myTerminal.cpp
	$(BB) -c -o build/myTerminal.o myTerminal.cpp 
build/myBigChar.o: myBigChar.cpp
	$(BB) -c -o build/myBigChar.o myBigChar.cpp
build/myKeyboard.o: myKeyboard.cpp
	$(BB) -c -o build/myKeyboard.o myKeyboard.cpp
build/myTimer.o: myTimer.cpp
	$(BB) -c -o build/myTimer.o myTimer.cpp
build/alucu.o: alucu.cpp
	$(BB) -c -o build/alucu.o alucu.cpp
build/simpleassembler.o: simpleassembler.cpp
	$(BB) -c -o build/simpleassembler.o simpleassembler.cpp

libs/libmySimpleComputer.a: build/mySimpleComputer.o
	ar rc libs/libmySimpleComputer.a build/mySimpleComputer.o
libs/libmyBigChar.a: build/myBigChar.o
	ar rc libs/libmyBigChar.a build/myBigChar.o 
libs/libmyTerm.a: build/myTerminal.o
	ar rc libs/libmyTerm.a build/myTerminal.o
libs/libmyKeyboard.a: build/myKeyboard.o
	ar rc libs/libmyKeyboard.a build/myKeyboard.o
libs/libTimer.a: build/myTimer.o
	ar rc libs/libTimer.a build/myTimer.o
libs/libAluCu.a: build/alucu.o
	ar rc libs/libAluCu.a build/alucu.o
libs/libSimpleAssembler.a: build/simpleassembler.o
	ar rc libs/libSimpleAssembler.a build/simpleassembler.o

1: libs/libmyBigChar.a
	ranlib libs/libmyBigChar.a 
2: libs/libmySimpleComputer.a
	ranlib libs/libmySimpleComputer.a
3: libs/libmyTerm.a
	ranlib libs/libmyTerm.a
4: libs/libmyKeyboard.a
	ranlib libs/libmyKeyboard.a
5: libs/libTimer.a
	ranlib libs/libTimer.a
6: libs/libAluCu.a
	ranlib libs/libAluCu.a
7: libs/libSimpleAssembler.a
	ranlib libs/libSimpleAssembler.a

repository: 
	mkdir -p bin
	mkdir -p build 
	mkdir -p libs
clean: 
	rm -rf -R build 
	rm -rf -R bin

