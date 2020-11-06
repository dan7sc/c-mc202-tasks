#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int le_int(int *num) {
    int n;

    n = scanf("%d", num);

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
        scanf("%c", &ch);
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
    PLista fila_atendimentos_finalizados;
    PNo no;
    TDado t_paciente;
    TDado t_atendimento;
    TDado t_especialista;
    int x = 1;
    char nome[15];
    int qtde_profissionais_por_id[] = { 10, 2, 5, 3, 4, 7, 2, 1, 4 };

    fila_pacientes = cria_lista();
    while(x > -1) {
        t_paciente.paciente.lista_atendimento = cria_lista();

        le_string_entre_aspas(t_paciente.paciente.nome);
        le_string(nome);
        t_paciente.paciente.prioridade = converte_string_para_enum(nome);

        x = 1;
        while(x > 0) {
            x = scanf("%d", &(t_atendimento.id));
            if(x > 0) {
                t_paciente.paciente.lista_atendimento = adiciona_elemento_no_fim(
                    t_paciente.paciente.lista_atendimento, t_atendimento);
            }
        }

        if(t_paciente.paciente.prioridade == 0) {
            fila_pacientes = adiciona_elemento_no_fim(fila_pacientes, t_paciente);
        } else {
            fila_pacientes = adiciona_elemento_no_inicio(fila_pacientes, t_paciente);
        }
    }

    imprime_lista_paciente(fila_pacientes);

    fila_atendimentos = cria_lista();
    for(int i = 0; i < NUM_ESPECIALISTAS; i++) {
        t_especialista.atendimento.id = i + 1;
        t_especialista.atendimento.num_especialistas = qtde_profissionais_por_id[i];
        t_especialista.atendimento.num_ocupados = 0;
        t_especialista.atendimento.pacientes_em_atendimento = cria_lista();

        adiciona_elemento_no_fim(fila_atendimentos, t_especialista);
    }

    fila_atendimentos_finalizados = cria_lista();
    while(fila_pacientes->inicio != NULL) {
        fila_pacientes = remove_elemento_no_inicio(fila_pacientes);
    }

    imprime_lista_paciente(fila_pacientes);

    no = fila_pacientes->inicio;
    while(no != NULL) {
        destroi_lista(no->dado.paciente.lista_atendimento);
        no = no->proximo;
    }

    no = fila_atendimentos->inicio;
    while(no != NULL) {
        destroi_lista(no->dado.atendimento.pacientes_em_atendimento);
        no = no->proximo;
    }

    no = fila_atendimentos_finalizados->inicio;
    while(no != NULL) {
        destroi_lista(no->dado.atendimento.pacientes_em_atendimento);
        no = no->proximo;
    }

    destroi_lista(fila_pacientes);
    destroi_lista(fila_atendimentos);
    destroi_lista(fila_atendimentos_finalizados);

    return 0;
}
