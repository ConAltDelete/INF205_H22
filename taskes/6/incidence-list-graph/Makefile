run: run-graph-example
	./run-graph-example travel-time.dat

run-graph-example: dijkstra.o run-graph-example.o undir-inclist-graph.o
	g++ -g3 -std=c++17 -o run-graph-example *.o

%.o: %.cpp
	g++ -g3 -c -std=c++17 -o $@ $<

clean:
	rm -f *.o *.zip run-graph-example
