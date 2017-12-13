CC=gcc
CFLAGS=-lcurl -Wall -O
LDFLAGS=-lcurl
EXEC=exec
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

all: $(EXEC)

exec: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean: 
	rm -f *.o core

mrproper: clean
	rm -f $(EXEC)

