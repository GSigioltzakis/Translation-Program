CC = gcc
CFLAGS = -Wall -ansi -pedantic -g

translate:
	$(CC) $(CFLAGS) main.c -o $@

clean:
	-rm -f translate
