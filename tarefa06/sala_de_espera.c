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
    PLista filas_atendimentos[9];
    PLista lista_pacientes_finalizados;
    PNo no;
    TDado t_paciente;
    TDado t_atendimento;
    /* TDado t_especialista; */
    TDado *t_paciente_removido;
    Paciente *paciente_removido;
    TDado *t_atendimento_removido;
    int *atendimento_removido;
    int x = 1;
    char nome[15];
    /* int qtde_profissionais_por_id[] = { 10, 2, 5, 3, 4, 7, 2, 1, 4 }; */
    /* int qtde_ocupados_por_id[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 }; */

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
                t_paciente.paciente.lista_atendimento = adiciona_elemento_no_fim(t_paciente.paciente.lista_atendimento, t_atendimento);
            }
        }

        if(t_paciente.paciente.prioridade == 0) {
            fila_pacientes = adiciona_elemento_no_fim(fila_pacientes, t_paciente);
        } else {
            fila_pacientes = adiciona_elemento_no_inicio(fila_pacientes, t_paciente);
        }
    }

    /* imprime_lista_paciente(fila_pacientes); */

    /* fila_atendimentos = cria_lista(); */
    /* for(int i = 0; i < NUM_ESPECIALISTAS; i++) { */
    /*     t_especialista.atendimento.id = i + 1; */
    /*     t_especialista.atendimento.num_especialistas = qtde_profissionais_por_id[i]; */
    /*     t_especialista.atendimento.num_ocupados = 0; */
    /*     t_especialista.atendimento.pacientes_em_atendimento = cria_lista(); */

    /*     fila_atendimentos = adiciona_elemento_no_fim(fila_atendimentos, t_especialista); */
    /* } */

    /* fila_atendimentos = cria_lista(); */
    /* for(int i = 0; i < NUM_ESPECIALISTAS; i++) { */
    /*     t_especialista.atendimento.qtde_profissionais_por_id[i] = qtde_profissionais_por_id[i]; */
    /*     t_especialista.atendimento.qtde_ocupados_por_id[i] = qtde_ocupados_por_id[i]; */
    /*     t_especialista.atendimento.pacientes_em_atendimento = cria_lista(); */

    /*     fila_atendimentos = adiciona_elemento_no_fim(fila_atendimentos, t_especialista); */
    /* } */

    for(int i = 0; i < NUM_ESPECIALISTAS; i++) {
        filas_atendimentos[i] = cria_lista();
    }

    lista_pacientes_finalizados = cria_lista();

    while(fila_pacientes->inicio != NULL) {
        t_paciente_removido = remove_elemento_no_inicio(fila_pacientes);
        /* printf("%s\n", ((Paciente *)(paciente_removido))->nome); */
        paciente_removido = (Paciente *) t_paciente_removido;
        t_atendimento_removido = remove_elemento_no_inicio(paciente_removido->lista_atendimento);
        /* printf("%d\n", *(int *)(atendimento_removido)); */
        atendimento_removido = (int *) t_atendimento_removido;

        if(t_paciente.paciente.prioridade == normal) {
            filas_atendimentos[*atendimento_removido - 1] = adiciona_elemento_no_fim(filas_atendimentos[*atendimento_removido - 1], *t_paciente_removido);
        } else {
            filas_atendimentos[*atendimento_removido - 1] = adiciona_elemento_no_inicio(filas_atendimentos[*atendimento_removido - 1], *t_paciente_removido);
        }
        free(atendimento_removido);
        free(paciente_removido);
    }

    /* imprime_lista_paciente(fila_pacientes); */
    printf("####\n");
    for(int i = 0; i < NUM_ESPECIALISTAS; i++) {
        imprime_lista_paciente(filas_atendimentos[i]);
    }
    /* imprime_lista_paciente(lista_pacientes_finalizados); */

    no = fila_pacientes->inicio;
    while(no != NULL) {
        destroi_lista(no->dado.paciente.lista_atendimento);
        no = no->proximo;
    }

    no = lista_pacientes_finalizados->inicio;
    while(no != NULL) {
        destroi_lista(no->dado.paciente.lista_atendimento);
        no = no->proximo;
    }
    destroi_lista(fila_pacientes);

    for(int i = 0; i < NUM_ESPECIALISTAS; i++) {
        destroi_lista(filas_atendimentos[i]);
    }

    destroi_lista(lista_pacientes_finalizados);
    printf("****\n");
    return 0;
}
