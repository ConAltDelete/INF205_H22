./bin/task2.exe: ./obj/PNG.obj  ./obj/timing.obj ./obj/task2.obj
	g++ -I./src/ $^ -o $@

./obj/%.obj: ./src/%.cpp
	g++ -I./src/ -c $^ -o $@

./bin/datastruct.exe: ./obj/datatype-size.obj
	g++ -iquotedir../h_files/ ./obj/datatype-size.obj -o ./bin/datastruct.exe 

test:
	g++ ./h_files/PNG.h ./h_files/PNG.cpp ./src/test.cpp -o ./bin/test.exe

clean:
	rm -f ./obj/*
	rm -f ./bin/*

full:
	echo "Not implemented"
