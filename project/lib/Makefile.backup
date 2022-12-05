.PHONY: clean
do_everything: do_everything.cpp read_image2.o contour.o ARCDIC.o view_circles.o
read_image2.o: read_image2.cpp
contour.o: contour.cpp
ARCDIC.o: ARCDIC.cpp ARCDIC.h
view_circles.o: view_circles.cpp
clean:
	-rm -f *.o
