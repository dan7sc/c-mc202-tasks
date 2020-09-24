#include <stdio.h>
#include "professor_carlos.h"

#define MAX_ALUNOS 40
#define MAX_TURMAS 50
#define MAX_OPERACOES 50

void le_string(char str[]) {
    scanf("%s", str);
}

void le_nome_completo(Aluno* aluno) {
    scanf("%s %s", aluno->nome, aluno->sobrenome);
}

void le_data(Data* data) {
    scanf("%d %d %d", &data->dia, &data->mes, &data->ano);
}

void imprime_nome_completo(Aluno aluno) {
    printf("%s %s", aluno.nome, aluno.sobrenome);
}

void imprime_data(Data data) {
    printf("%d %d %d", data.dia, data.mes, data.ano);
}

int main() {
    int num_turmas = 0;
    int num_operacoes = 0;
    int num_alunos = 0;
    int operacao = 0;
    int contador = 0;
    Turma turmas[MAX_TURMAS];

    scanf("%d", &num_turmas);
    scanf("%d", &num_operacoes);

    printf("%d %d\n", num_turmas, num_operacoes);

    for(int k = 0; k < num_turmas; k++) {
        scanf("%d", &num_alunos);
        for(int i = 0; i < num_alunos; i++) {
            le_nome_completo(&turmas[k].alunos[i]);
            le_data(&turmas[k].alunos[i].nascimento);
        }

        printf("%d\n", num_alunos);
        for(int i = 0; i < num_alunos; i++) {
            imprime_nome_completo(turmas[k].alunos[i]);
            printf(" ");
            imprime_data(turmas[k].alunos[i].nascimento);
            printf("\n");
        }
    }

    while(contador < num_operacoes) {
        scanf("%d", &operacao);
        printf("%d\n", operacao);

        contador++;
    }

    return 0;
}
