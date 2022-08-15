CC = gcc
%.o: %c
	$(CC) -c -o $@ $<
allremove_list_entry: remove_list_entry1
all: allremove_list_entry
remove_list_entry1.c: remove_list_entry1.o
	gcc -o remove_list_entry1 remove_list_entry1.o
clean: 
	rm -f *.o remove_list_entry1

