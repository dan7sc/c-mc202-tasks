#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int le_int(int *num) {
    int n;

    n = scanf("%d", num);
    return n;
}

int le_char(char *ch) {
    int n;

    n = scanf("%c", ch);
    return n;
}

void le_string(char *str) {
    scanf("%s", str);
}

void le_string_entre_aspas(char *str) {
    char ch;
    int i;
    int contador = 0;

    for(i = 0; contador < 2 && i < TAM_NOME - 2; i++) {
        le_char(&ch);
        if(ch != '"') {
            str[i] = ch;
        } else {
            i--;
            contador++;
        }
    }
    str[i] = '\0';
}

int main() {
    PLista fila_pacientes;
    PLista fila_atendimentos;
    TDado t_paciente;
    TDado t_atendimento;
    int x = 1;
    char *str = malloc(sizeof(char *));

    fila_pacientes = malloc(sizeof(Lista));

    while(x > -1) {
        le_string_entre_aspas(t_paciente.paciente.nome);
        le_string(str);
        t_paciente.paciente.prioridade = converte_string_para_enum(str);

        fila_atendimentos = malloc(sizeof(Lista));
        x = 1;
        while(x > 0) {
            x = scanf("%d", &t_atendimento.especialidade.id);
            if(x > 0) {
                fila_atendimentos = adiciona_elemento_no_fim(fila_atendimentos, t_atendimento);
            }
        }
        t_paciente.paciente.lista_atendimento = fila_atendimentos;

        if(t_paciente.paciente.prioridade == 0) {
            fila_pacientes = adiciona_elemento_no_fim(fila_pacientes, t_paciente);
        } else {
            fila_pacientes = adiciona_elemento_no_inicio(fila_pacientes, t_paciente);
        }
    }

    imprime_lista_paciente(fila_pacientes);

    free(str);
    free(fila_atendimentos);
    free(fila_pacientes);

    return 0;
}
