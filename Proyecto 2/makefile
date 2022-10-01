CC = gcc
%.o: %c
	$(CC) -c -o $@ $<
allProyecto: Proyecto1
all: Proyecto1
Proyecto1.c: Proyecto1.o
	gcc -o Proyecto1
	Proyecto1.o
clean: 
	rm -f *.o Proyecto1