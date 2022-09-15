./bin/datastruct.exe: ./obj/datatype-size.o
	g++ ./obj/datatype-size.o -o ./bin/datastruct.exe 
./obj/datatype-size.o: ./src/datatype-size.cpp
	g++ -c ./src/datatype-size.cpp -o ./obj/datatype-size.o

clean:
	rm -f ./obj/*
	rm -f ./bin/*

full:
	echo "Not implemented"
