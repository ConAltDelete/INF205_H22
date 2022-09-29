./bin/task2.exe: ./obj/PNG.obj  ./obj/timing.obj ./obj/task2.obj
	g++ -I./h_files/ $^ -o $@

./obj/%.obj: ./src/%.cpp
	g++ -I./h_files/ -c $^ -o $@

./bin/datastruct.exe: ./obj/datatype-size.obj
	g++ -iquotedir../h_files/ ./obj/datatype-size.obj -o ./bin/datastruct.exe 

test:
	g++ -o ./bin/test.exe ./obj/*.obj

clean:
	rm -f ./obj/*
	rm -f ./bin/*

full:
	echo "Not implemented"
