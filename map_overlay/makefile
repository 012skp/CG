CC = g++
FLAGS = -std=c++11

a:	a.o cgal_basic.o
	$(CC) $(FLAGS) a.o cgal_basic.o -o a
a.o: a.cc cgal_basic.h
	$(CC) $(FLAGS) -c a.cc
cgal_basic.o: cgal_basic.cc cgal_basic.h
	$(CC) $(FLAGS) -c cgal_basic.cc

clean:
	rm *.o a output guifile
