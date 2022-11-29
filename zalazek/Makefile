__start__: obj __lines_for_space__ interp __plugin__
	export LD_LIBRARY_PATH="./libs"; ./interp

obj:
	mkdir obj


__lines_for_space__:
	@echo
	@echo
	@echo
	@echo
	@echo


__plugin__:
	cd plugin; make

CPPFLAGS=-Wall -pedantic -std=c++17 -Iinc
LDFLAGS=-Wall




interp: obj/main.o obj/LibInterface.o obj/Set4Libraries.o obj/Scene.o obj/xmlinterp.o  obj/Configuration.o obj/klient.o
	g++ ${LDFLAGS} -o interp  obj/main.o obj/LibInterface.o obj/Set4Libraries.o obj/Scene.o obj/xmlinterp.o obj/Configuration.o obj/klient.o -ldl -lxerces-c -pthread 

obj/main.o: src/main.cpp inc/Interp4Command.hh inc/xmlinterp.hh  inc/AccessControl.hh inc/Configuration.hh inc/Port.hh 
	g++ -c ${CPPFLAGS} -o obj/main.o src/main.cpp

obj/LibInterface.o: src/LibInterface.cpp inc/LibInterface.hh inc/Interp4Command.hh
	g++ -c ${CPPFLAGS} -o obj/LibInterface.o src/LibInterface.cpp

obj/Set4Libraries.o: src/Set4Libraries.cpp inc/Set4Libraries.hh
	g++ -c ${CPPFLAGS} -o obj/Set4Libraries.o src/Set4Libraries.cpp

obj/Scene.o: src/Scene.cpp inc/Scene.hh
	g++ -c ${CPPFLAGS} -o obj/Scene.o src/Scene.cpp

obj/xmlinterp.o: src/xmlinterp.cpp inc/xmlinterp.hh 
	g++ -c ${CPPFLAGS} -o obj/xmlinterp.o src/xmlinterp.cpp

obj/klient.o: src/klient.cpp  inc/AccessControl.hh inc/Port.hh
	g++ -c ${CPPFLAGS} -o obj/klient.o src/klient.cpp

obj/Configuration.o: src/Configuration.cpp inc/Configuration.hh 
	g++ -c ${CPPFLAGS} -o obj/Configuration.o src/Configuration.cpp


clean:
	rm -f obj/* interp core*


clean_plugin:
	cd plugin; make clean

cleanall: clean
	cd plugin; make cleanall
	cd dox; make cleanall
	rm -f libs/*
	find . -name \*~ -print -exec rm {} \;

help:
	@echo
	@echo "  Lista podcelow dla polecenia make"
	@echo 
	@echo "        - (wywolanie bez specyfikacji celu) wymusza"
	@echo "          kompilacje i uruchomienie programu."
	@echo "  clean    - usuwa produkty kompilacji oraz program"
	@echo "  clean_plugin - usuwa plugin"
	@echo "  cleanall - wykonuje wszystkie operacje dla podcelu clean oraz clean_plugin"
	@echo "             oprocz tego usuwa wszystkie kopie (pliki, ktorych nazwa "
	@echo "             konczy sie znakiem ~)."
	@echo "  help  - wyswietla niniejszy komunikat"
	@echo
	@echo " Przykladowe wywolania dla poszczegolnych wariantow. "
	@echo "  make           # kompilacja i uruchomienie programu."
	@echo "  make clean     # usuwa produkty kompilacji."
	@echo
 
