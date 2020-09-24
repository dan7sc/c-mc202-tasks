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
    int operacao = 0;
    int contador = 0;
    int turma = 0;
    Turma turmas[MAX_TURMAS];

    Aluno aluno;

    scanf("%d", &num_turmas);
    scanf("%d", &num_operacoes);

    for(int k = 0; k < num_turmas; k++) {
        scanf("%d", &turmas[k].qtd);
        for(int i = 0; i < turmas[k].qtd; i++) {
            le_nome_completo(&turmas[k].alunos[i]);
            le_data(&turmas[k].alunos[i].nascimento);
        }
    }

    while(contador < num_operacoes) {
        scanf("%d", &operacao);

        switch(operacao) {
        case 1:
            /* printf("operacao 1\n"); */
            scanf("%d", &turma);
            aluno = procura_novo_na_turma(turmas, num_turmas, turma);
            printf("%s\n", aluno.nome);
            break;
        case 2:
            /* printf("operacao 2\n"); */
            scanf("%d", &turma);
            aluno = procura_velho_na_turma(turmas, num_turmas, turma);
            printf("%s\n", aluno.sobrenome);
            break;
        case 3:
            printf("operacao 3\n");
            break;
        case 4:
            printf("operacao 4\n");
            break;
        case 5:
            printf("operacao 5\n");
            break;
        case 6:
            printf("operacao 6\n");
            break;
        case 7:
            printf("operacao 7\n");
            break;
        }

        contador++;
    }

    return 0;
}
