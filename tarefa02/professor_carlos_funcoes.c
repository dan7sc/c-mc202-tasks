#include <stdio.h>
#include "professor_carlos.h"

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
