#include <stdio.h>
#include "professor_carlos.h"

#define MAX_ALUNOS 40
#define MAX_TURMAS 50
#define MAX_OPERACOES 50
#define MAX_STRING 15

void le_string(char str[]) {
    scanf("%s", str);
}

void le_int(int *num) {
    scanf("%d", num);
}

void le_nome_completo(Aluno* aluno) {
    scanf("%s %s", aluno->nome, aluno->sobrenome);
}

void le_data(Data* data) {
    scanf("%d %d %d", &data->dia, &data->mes, &data->ano);
}

void imprime_string(char str[]) {
    printf("%s\n", str);
}

void imprime_int(int num) {
    printf("%d\n", num);
}

int main() {
    int num_turmas = 0;
    int num_operacoes = 0;
    int operacao = 0;
    int contador = 0;
    int turma = 0;
    Turma turmas[MAX_TURMAS];
    char padrao[MAX_STRING];
    int num = 0;

    Aluno aluno;

    le_int(&num_turmas);
    le_int(&num_operacoes);

    for(int k = 0; k < num_turmas; k++) {
        le_int(&turmas[k].qtd);
        for(int i = 0; i < turmas[k].qtd; i++) {
            le_nome_completo(&turmas[k].alunos[i]);
            le_data(&turmas[k].alunos[i].nascimento);
        }
    }

    while(contador < num_operacoes) {
        le_int(&operacao);
        switch(operacao) {
        case 1:
            le_int(&turma);
            aluno = procura_novo_na_turma(turmas, num_turmas, turma);
            imprime_string(aluno.nome);
            break;
        case 2:
            le_int(&turma);
            aluno = procura_velho_na_turma(turmas, num_turmas, turma);
            imprime_string(aluno.sobrenome);
            break;
        case 3:
            aluno = procura_velho_todas_turmas(turmas, num_turmas);
            imprime_string(aluno.nome);
            break;
        case 4:
            aluno = procura_novo_todas_turmas(turmas, num_turmas);
            imprime_string(aluno.sobrenome);
            break;
        case 5:
            le_string(padrao);
            num = conta_substrings(turmas, num_turmas, padrao);
            imprime_int(num);
            break;
        case 6:
            le_int(&turma);
            le_nome_completo(&aluno);
            le_data(&aluno.nascimento);
            turmas[turma].qtd = add_aluno(turmas, aluno, turma);
            imprime_int(turmas[turma].qtd);
            break;
        case 7:
            le_int(&turma);
            turmas[turma].qtd = remove_aluno(turmas, turma);
            imprime_int(turmas[turma].qtd);
            break;
        }
        contador++;
    }

    return 0;
}
