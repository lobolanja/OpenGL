# fichero Makefile
#
# nombre del fichero ejecutable
#
TARGETS= practica4

# banderas para el compilador (C y C++). Se indican los directorios donde se puenden
# encontrar ficheros para incluir mediante la opcion -I
# la opcion -g sirve para permitir la depuración
#
CFLAGS=    -g -DXWINDOWS -DSHM -I/usr/include -I.
CXXFLAGS=  -g -DXWINDOWS -DSHM -I/usr/include -I. -w

# banderas pra el enlazador
# Se indica directorios donde encontrar las funciontecas con -L. Usando -l seguido del
# nombre se indica la funcionteca que se desea enlazar.
#
LDFLAGS=  -lGLU -lGL -lglut -ljpeg

# definicion del compilador
#
CC = g++

# orden que sera ejecutada por defecto
#
default : $(TARGETS)

# regla de ejecucion
#
$(TARGETS) : practica4.o
	$(CC) -o  $@ $(CXXFLAGS) practica4.o $/camaras.cc $/ovni.cc $/luces.cc $/file_ply_stl.cc $/dibujo.cc $/ovni.cc jpg_imagen.cpp jpg_readwrite.cpp jpg_memsrc.cpp $(LDFLAGS) 

$(TARGETS) : ovni.o
	$(CC) -o  $@ $(CXXFLAGS) practica4.o $/ovni.cc $/camaras.cc $/luces.cc $/file_ply_stl.cc $/dibujo.cc $/ovni.cc jpg_imagen.cpp jpg_readwrite.cpp jpg_memsrc.cpp $(LDFLAGS) 

$(TARGETS) : dibujo.o
	$(CC) -o  $@ $(CXXFLAGS) practica4.o $/ovni.cc $/camaras.cc $/luces.cc $/file_ply_stl.cc $/dibujo.cc $/ovni.cc jpg_imagen.cpp jpg_readwrite.cpp jpg_memsrc.cpp $(LDFLAGS) 

$(TARGETS) : camaras.o
	$(CC) -o  $@ $(CXXFLAGS) practica4.o $/ovni.cc $/camaras.cc $/luces.cc $/file_ply_stl.cc $/dibujo.cc $/ovni.cc jpg_imagen.cpp jpg_readwrite.cpp jpg_memsrc.cpp $(LDFLAGS) 

#
#
clean:
	rm -f *.o
	rm -f $(TARGETS)

#
#
redo:
	touch *.cc
	make

#
#
superclean:
	rm -f *.o
	rm *~
	rm -f $(TARGETS)

#
#
tgz:
	rm -f *.o
	rm *~
	rm -f $(TARGETS)
	tar -zcvf $(TARGETS).tgz *

