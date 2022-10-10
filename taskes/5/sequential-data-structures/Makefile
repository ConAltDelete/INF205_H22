sequence-test: singly-linked-list.o dynamic-array.o sequence-test.o doubly_linked_list.o
	g++ -g3 -o sequence-test *.o

%.o: %.cpp
	g++ -g3 -c -o $@ $<

clean:
	rm -f *.o *.zip sequence-test
