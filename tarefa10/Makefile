CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: corretor

corretor: corretor.c
	gcc $(CFLAGS) -c hash.c $(LDFLAGS)
	gcc $(CFLAGS) -c funcoes_auxiliares.c $(LDFLAGS)
	gcc $(CFLAGS) -c corretor.c $(LDFLAGS)
	gcc $(CFLAGS) -o corretor corretor.o hash.o funcoes_auxiliares.o $(LDFLAGS)

clean:
	rm -f corretor
	rm -f *.o
