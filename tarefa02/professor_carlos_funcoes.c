#include <stdio.h>
#include "professor_carlos.h"

#define MAX_STRING 15
#define FALSE 0
#define TRUE 1
#define MENOR -1
#define MAIOR 1
#define IGUAL 0

int compara_strings(char string_a[], char string_b[]) {
    int indice = IGUAL;

    for(int i = 0; indice == IGUAL && (string_a[i] != '\0' && string_b[i] != '\0'); i++) {
        if (string_a[i] < string_b[i]) {
            indice = MENOR;
        } else if (string_a[i] > string_b[i]) {
            indice = MAIOR;
        } else {
            indice = IGUAL;
        }
    }

    return indice;
}

int compara_datas(Data data_a, Data data_b) {
    if(data_a.ano < data_b.ano) {
        return MENOR;
    } else if(data_a.ano == data_b.ano &&
              data_a.mes < data_b.mes) {
        return MENOR;
    } else if(data_a.ano == data_b.ano &&
              data_a.mes == data_b.mes &&
              data_a.dia < data_b.dia) {
        return MENOR;
    } else if(data_a.ano == data_b.ano &&
              data_a.mes == data_b.mes &&
              data_a.dia == data_b.dia) {
        return IGUAL;
    } else {
        return MAIOR;
    }
}

Aluno procura_novo_na_turma(Turma t[], int qtd_turmas, int j) {
    int indice_mais_novo = 0;
    int ordem_string_a = IGUAL;
    Aluno aluno_mais_novo;
    Aluno aluno_atual;
    int eh_data_maior;

    for(int i = 0; i < qtd_turmas; i++) {
        if(i == j) {
            for(int k = 0; k < t[j].qtd; k++) {
                aluno_mais_novo = t[j].alunos[indice_mais_novo];
                aluno_atual = t[j].alunos[k];
                eh_data_maior = compara_datas(
                    aluno_mais_novo.nascimento, aluno_atual.nascimento
                    );
                if(eh_data_maior == MENOR) {
                    indice_mais_novo = k;
                } else if(eh_data_maior == IGUAL) {
                    ordem_string_a = compara_strings(
                        aluno_mais_novo.nome, aluno_atual.nome
                        );
                    if(ordem_string_a == MAIOR) {
                        indice_mais_novo = k;
                    } else if(ordem_string_a == IGUAL) {
                        ordem_string_a = compara_strings(
                            aluno_mais_novo.sobrenome, aluno_atual.sobrenome
                            );
                        if(ordem_string_a == MAIOR) {
                            indice_mais_novo = k;
                        }
                    }
                }
            }
        }
    }
    aluno_mais_novo = t[j].alunos[indice_mais_novo];
    return aluno_mais_novo;
}

Aluno procura_velho_na_turma(Turma t[], int qtd_turmas, int j) {
    int indice_mais_velho = 0;
    int ordem_string_a = IGUAL;
    Aluno aluno_mais_velho;
    Aluno aluno_atual;
    int eh_data_maior;

    for(int i = 0; i < qtd_turmas; i++) {
        if(i == j) {
            for(int k = 0; k < t[j].qtd; k++) {
                aluno_mais_velho = t[j].alunos[indice_mais_velho];
                aluno_atual = t[i].alunos[k];
                eh_data_maior = compara_datas(
                    aluno_mais_velho.nascimento, aluno_atual.nascimento
                    );
                if(eh_data_maior == MAIOR) {
                    indice_mais_velho = k;
                } else if(eh_data_maior == IGUAL) {
                    ordem_string_a = compara_strings(
                        aluno_mais_velho.nome, aluno_atual.nome
                        );
                    if(ordem_string_a == MAIOR) {
                        indice_mais_velho = k;
                    } else if(ordem_string_a == IGUAL) {
                        ordem_string_a = compara_strings(
                            aluno_mais_velho.sobrenome, aluno_atual.sobrenome
                            );
                        if(ordem_string_a == MAIOR) {
                            indice_mais_velho = k;
                        }
                    }
                }
            }
        }
    }
    aluno_mais_velho = t[j].alunos[indice_mais_velho];
    return aluno_mais_velho;
}

Aluno procura_velho_todas_turmas(Turma t[], int qtd_turmas) {
    int indice_mais_velho = 0;
    int turma = 0;
    int ordem_string_a = IGUAL;
    Aluno aluno_mais_velho;
    Aluno aluno_atual;
    int eh_data_maior;

    for(int i = 0; i < qtd_turmas; i++) {
        for(int k = 0; k < t[i].qtd; k++) {
            aluno_mais_velho = t[turma].alunos[indice_mais_velho];
            aluno_atual = t[i].alunos[k];
            eh_data_maior = compara_datas(
                aluno_mais_velho.nascimento, aluno_atual.nascimento
                );
            if(eh_data_maior == MAIOR) {
                indice_mais_velho = k;
                turma = i;
            } else if(eh_data_maior == IGUAL) {
                ordem_string_a = compara_strings(
                    aluno_mais_velho.nome, aluno_atual.nome
                    );
                if(ordem_string_a == MAIOR) {
                    indice_mais_velho = k;
                    turma = i;
                } else if(ordem_string_a == IGUAL) {
                    ordem_string_a = compara_strings(
                        aluno_mais_velho.sobrenome, aluno_atual.sobrenome
                        );
                    if(ordem_string_a == MAIOR) {
                        indice_mais_velho = k;
                        turma = i;
                    }
                }
            }
        }
    }
    aluno_mais_velho = t[turma].alunos[indice_mais_velho];
    return aluno_mais_velho;
}

Aluno procura_novo_todas_turmas(Turma t[], int qtd_turmas) {
    int indice_mais_novo = 0;
    int turma = 0;
    int ordem_string_a = IGUAL;
    Aluno aluno_mais_novo;
    Aluno aluno_atual;
    int eh_data_maior = 0;

    for(int i = 0; i < qtd_turmas; i++) {
        for(int k = 0; k < t[i].qtd; k++) {
            aluno_mais_novo = t[turma].alunos[indice_mais_novo];
            aluno_atual = t[i].alunos[k];
            eh_data_maior = compara_datas(
                aluno_mais_novo.nascimento, aluno_atual.nascimento
                );
            if(eh_data_maior == MENOR) {
                indice_mais_novo = k;
                turma = i;
            } else if(eh_data_maior == IGUAL) {
                ordem_string_a = compara_strings(
                    aluno_mais_novo.nome, aluno_atual.nome
                    );
                if(ordem_string_a == MAIOR) {
                    indice_mais_novo = k;
                    turma = i;
                } else if(ordem_string_a == IGUAL) {
                    ordem_string_a = compara_strings(
                        aluno_mais_novo.sobrenome, aluno_atual.sobrenome
                        );
                    if(ordem_string_a == MAIOR) {
                        indice_mais_novo = k;
                        turma = i;
                    }
                }
            }
        }
    }
    aluno_mais_novo = t[turma].alunos[indice_mais_novo];
    return aluno_mais_novo;
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
