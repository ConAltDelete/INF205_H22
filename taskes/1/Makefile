
./bin/python2cpp.exe: ./obj/python2cpp.o
	g++ -g ./obj/python2cpp.o -o ./bin/python2cpp.exe

./obj/python2cpp.o: ./src/python2cpp.cpp
	g++ -c -g ./src/python2cpp.cpp -o ./obj/python2cpp.o

full:
	make clear
	make
	./bin/python2cpp.exe > output.txt
	xelatex -output-directory=./doc/ ./src/task1.tex
	rm output.txt

clear:
	rm -f ./doc/*
	rm -f ./bin/*
	rm -f ./obj/*
