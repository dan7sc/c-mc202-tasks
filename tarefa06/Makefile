CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: sala_de_espera

sala_de_espera: sala_de_espera.c
	gcc $(CFLAGS) -c lista.c $(LDFLAGS)
	gcc $(CFLAGS) -c funcoes_de_ajuda.c $(LDFLAGS)
	gcc $(CFLAGS) -c sala_de_espera.c $(LDFLAGS)
	gcc $(CFLAGS) -o sala_de_espera sala_de_espera.o lista.o funcoes_de_ajuda.o $(LDFLAGS)

clean:
	rm -f sala_de_espera
	rm -f *.o
