#include <stdio.h>
#include "professor_carlos.h"

#define MAX_STRING 15
#define FALSE 0
#define TRUE 1

Aluno procura_novo_na_turma(Turma t[], int qtd_turmas, int j) {
    int mais_novo = 0;

    for(int i = 0; i < qtd_turmas; i++) {
        if(i == j) {
            for(int k = 0; k < t[j].qtd; k++) {
                if(t[j].alunos[mais_novo].nascimento.ano <= t[j].alunos[k].nascimento.ano) {
                    mais_novo = k;
                }
            }
        }
    }

    return t[j].alunos[mais_novo];
}

Aluno procura_velho_na_turma(Turma t[], int qtd_turmas, int j) {
    int mais_velho = 0;

    for(int i = 0; i < qtd_turmas; i++) {
        if(i == j) {
            for(int k = 0; k < t[j].qtd; k++) {
                if(t[j].alunos[mais_velho].nascimento.ano >= t[j].alunos[k].nascimento.ano) {
                    mais_velho = k;
                }
            }
        }
    }

    return t[j].alunos[mais_velho];
}

Aluno procura_velho_todas_turmas(Turma t[], int qtd_turmas) {
    int mais_velho = 0;
    int turma = 0;

    for(int i = 0; i < qtd_turmas; i++) {
        for(int k = 0; k < t[i].qtd; k++) {
            if(t[turma].alunos[mais_velho].nascimento.ano >= t[i].alunos[k].nascimento.ano) {
                mais_velho = k;
                turma = i;
            }
        }
    }

    return t[turma].alunos[mais_velho];
}

Aluno procura_novo_todas_turmas(Turma t[], int qtd_turmas) {
    int mais_novo = 0;
    int turma = 0;

    for(int i = 0; i < qtd_turmas; i++) {
        for(int k = 0; k < t[i].qtd; k++) {
            if(t[turma].alunos[mais_novo].nascimento.ano <= t[i].alunos[k].nascimento.ano) {
                mais_novo = k;
                turma = i;
            }
        }
    }

    return t[turma].alunos[mais_novo];
}

int add_aluno(Turma t[], Aluno A, int j) {
    int qtd_alunos = 0;
    int tam_alunos = t[j].qtd;

    t[j].alunos[tam_alunos] = A;
    qtd_alunos = ++t[j].qtd;

    return qtd_alunos;
}

int remove_aluno(Turma t[], int j) {
    int qtd_alunos = 0;
    int indice = t[j].qtd - 1;

    for(int i = 0; i < MAX_STRING; i++) {
        t[j].alunos[indice].nome[i] = '\0';
        t[j].alunos[indice].sobrenome[i] = '\0';
    }

    t[j].alunos[indice].nascimento.dia = 0;
    t[j].alunos[indice].nascimento.mes = 0;
    t[j].alunos[indice].nascimento.ano = 0;

    qtd_alunos = --t[j].qtd;

    return qtd_alunos;
}

int conta_substrings(Turma t[], int qtd_turmas, char *padrao) {
    int contador_letras = 0;
    int tam_padrao = 0;
    int contador_alunos = 0;
    int indice = 0;
    int eh_substring = FALSE;

    for(int i = 0; padrao[i] != '\0'; i++) {
        tam_padrao++;
    }

    for(int i = 0; i < qtd_turmas; i++) {
        for(int j = 0; j < t[i].qtd; j++) {
            indice = 0;
            contador_letras = 0;
            eh_substring = FALSE;
            for(int k = 0; eh_substring == FALSE && t[i].alunos[j].nome[k] != '\0'; k++) {
                if(t[i].alunos[j].nome[k] == padrao[indice]) {
                    contador_letras++;
                    while(indice < tam_padrao && contador_letras != tam_padrao) {
                        if(t[i].alunos[j].nome[k+1] == padrao[indice+1]) {
                            contador_letras++;
                            indice++;
                        } else {
                            contador_letras--;
                            break;
                        }
                    }
                }
                if(contador_letras == tam_padrao) {
                    contador_alunos++;
                    eh_substring = TRUE;
                }
            }
        }
    }

    return contador_alunos;
}
