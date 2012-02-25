CC=g++
CFLAGS=-c -Wall
CURLLIBS = $(shell curl-config --libs)
LIBXMLFLAGS = $(shell xml2-config --cflags)
LIBXMLLIBS = $(shell xml2-config --libs)
EXECUTABLE=kitsune

# Libraries is used to build two separate .dll/.so files for dev cycles (to spend less time compiling)
# kitsunelib and striplib/stripexec are meant for dist version, building everything into a single lib
# all also compiles a basic interface -- command line taking two arguments: a url and a dir


all: libkitsune.so $(EXECUTABLE)
	strip --strip-unneeded $(EXECUTABLE)
	strip --strip-unneeded libkitsune.so

stripexec: $(EXECUTABLE)
	strip --strip-unneeded $(EXECUTABLE)

$(EXECUTABLE): interface.o
	$(CC) interface.o -o $(EXECUTABLE) -L. -lkitsune

interface.o: interface.cpp
	$(CC) $(CFLAGS) interface.cpp -o interface.o

striplib: libkitsune.so
	strip --strip-unneeded libkitsune.so

kitsunelib: libkitsune.so

libkitsune.so: MangaGetter.o StringAux.o XMLAux.o UrlGetter.o
	$(CC) -shared -Wl,-soname,libkitsune.so -o libkitsune.so MangaGetter.o StringAux.o XMLAux.o UrlGetter.o $(LIBXMLLIBS) $(CURLLIBS)
	cp MangaGetter.h Kitsune.h

libraries: liburlgetter.so libmangagetter.so

libmangagetter.so: MangaGetter.o liburlgetter.so StringAux.o XMLAux.o
	$(CC) -shared -Wl,-soname,libmangagetter.so -o libmangagetter.so MangaGetter.o StringAux.o XMLAux.o $(LIBXMLLIBS) -L. -lurlgetter

MangaGetter.o: MangaGetter.cpp
	$(CC) $(CFLAGS) -fPIC MangaGetter.cpp -o MangaGetter.o $(LIBXMLFLAGS)

liburlgetter.so: UrlGetter.o StringAux.o
	$(CC) -shared -Wl,-soname,liburlgetter.so -o liburlgetter.so UrlGetter.o StringAux.o $(CURLLIBS)

UrlGetter.o: UrlGetter.cpp
	$(CC) $(CFLAGS) -fPIC UrlGetter.cpp -o UrlGetter.o

XMLAux.o: XMLAux.cpp
	$(CC) $(CFLAGS) $(LIBXMLFLAGS) -fPIC XMLAux.cpp -o XMLAux.o 

StringAux.o: StringAux.cpp
	$(CC) $(CFLAGS) -fPIC StringAux.cpp -o StringAux.o

clean:
	rm *so *o $(EXECUTABLE) Kitsune.h