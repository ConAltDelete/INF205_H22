
./bin/python2cpp.exe: ./obj/python2cpp.o
	g++ ./obj/python2cpp.o -o ./bin/python2cpp.exe

./obj/python2cpp.o: ./src/python2cpp.cpp
	g++ -c ./src/python2cpp.cpp -o ./obj/python2cpp.o
	
clear:
	rm ./bin/*
	rm ./obj/*
