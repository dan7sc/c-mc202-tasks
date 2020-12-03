CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: diadeuber

diadeuber: *.c
	gcc $(CFLAGS) -c heap.c $(LDFLAGS)
	gcc $(CFLAGS) -c diadeuber.c $(LDFLAGS)
	gcc $(CFLAGS) -o diadeuber diadeuber.o heap.o $(LDFLAGS)

clean:
	rm -f diadeuber
	rm -f *.o
