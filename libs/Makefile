CC=g++
CFLAGS=-c -Wall
CURLLIBS = $(shell curl-config --libs)
LIBXMLFLAGS = $(shell xml2-config --cflags)
LIBXMLLIBS = $(shell xml2-config --libs)
EXECUTABLE=tester

all: library $(EXECUTABLE)

$(EXECUTABLE): library main.o
	$(CC) main.o -o $(EXECUTABLE) -L. -lmangagetter -lurlgetter

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o main.o

library: liburlgetter.dll libmangagetter.dll

libmangagetter.dll: MangaGetter.o liburlgetter.dll StringAux.o XMLAux.o
	$(CC) -shared -Wl,-soname,libmangagetter.dll -o libmangagetter.dll MangaGetter.o StringAux.o XMLAux.o $(LIBXMLLIBS) -L. -lurlgetter

MangaGetter.o: MangaGetter.cpp
	$(CC) $(CFLAGS) -fPIC MangaGetter.cpp -o MangaGetter.o $(LIBXMLFLAGS)

liburlgetter.dll: UrlGetter.o StringAux.o
	$(CC) -shared -Wl,-soname,liburlgetter.dll -o liburlgetter.dll UrlGetter.o StringAux.o $(CURLLIBS)

UrlGetter.o: UrlGetter.cpp
	$(CC) $(CFLAGS) -fPIC UrlGetter.cpp -o UrlGetter.o

XMLAux.o: XMLAux.cpp
	$(CC) $(CFLAGS) $(LIBXMLFLAGS) XMLAux.cpp -o XMLAux.o 

StringAux.o: StringAux.cpp
	$(CC) $(CFLAGS) StringAux.cpp -o StringAux.o

clean:
	rm *o *dll *exe