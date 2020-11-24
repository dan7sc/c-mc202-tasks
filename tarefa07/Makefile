CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: mensageiro

mensageiro: mensageiro.c
	gcc $(CFLAGS) -c arvore.c $(LDFLAGS)
	gcc $(CFLAGS) -c funcoes_de_ajuda.c $(LDFLAGS)
	gcc $(CFLAGS) -c mensageiro.c $(LDFLAGS)
	gcc $(CFLAGS) -o mensageiro mensageiro.o arvore.o funcoes_de_ajuda.o $(LDFLAGS)

clean:
	rm -f mensageiro
	rm -f *.o
