./bin/datastruct.exe: ./obj/datatype-size.o
	g++ -iquotedir../h_files/ ./obj/datatype-size.o -o ./bin/datastruct.exe 
./obj/datatype-size.o: ./src/datatype-size.cpp
	g++ -c ./src/datatype-size.cpp -o ./obj/datatype-size.o

test:
	g++ ./h_files/PNG.h ./h_files/PNG.cpp ./src/test.cpp -o ./bin/test.exe

clean:
	rm -f ./obj/*
	rm -f ./bin/*

full:
	echo "Not implemented"
