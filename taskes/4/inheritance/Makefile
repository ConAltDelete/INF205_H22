litindex-test: book-index.o journal-article-index.o litindex-test.o
	g++ -g3 -o litindex-test *.o

%.o: %.cpp
	g++ -g3 -c -o $@ $<

clean:
	rm -f *.o *.zip litindex-test

zip: clean
	zip -r u39-problem-3.zip .
