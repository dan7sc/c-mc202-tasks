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
