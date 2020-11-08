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

int ordena_elementos(const void *elemento_a, const void *elemento_b) {
    Paciente *a = *(Paciente **) elemento_a;
    Paciente *b = *(Paciente **) elemento_b;

    return (a->ordem_de_chegada - b->ordem_de_chegada);
}

int main() {
    PLista fila_pacientes;
    PLista filas_atendimentos[9];
    PLista filas_pacientes_em_atendimento[9];
    PLista lista_pacientes_finalizados;
    PLista fila_do_desempate;
    PNo no;
    TDado t_paciente;
    TDado t_atendimento;
    TDado *v_desempate[NUM_PROFISSIONAIS];
    TDado *t_paciente_removido;
    Paciente *paciente_removido;
    TDado *t_atendimento_removido;
    int *atendimento_removido;
    int ordem_de_chegada = 1;
    int tamanho_fila_entrada = 0;
    int tamanho_fila_saida;
    int duracao_total = 600; // em segundos
    int duracao_atendimento_incremento = 600; // em segundos
    int j, n;
    int x = 1;
    char nome[15];
    int qtde_profissionais_por_id[] = { 10, 2, 5, 3, 4, 7, 2, 1, 4 };
    int qtde_ocupados_por_id[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    fila_pacientes = cria_lista();
    while(x > -1) {
        t_paciente.paciente.lista_atendimento = cria_lista();

        le_string_entre_aspas(t_paciente.paciente.nome);
        le_string(nome);
        t_paciente.paciente.prioridade = converte_string_para_enum(nome);
        t_paciente.paciente.horario_de_saida = 0;

        x = 1;
        while(x > 0) {
            x = scanf("%d", &(t_atendimento.id));
            if(x > 0) {
                t_paciente.paciente.lista_atendimento = adiciona_elemento_no_fim(t_paciente.paciente.lista_atendimento, t_atendimento);
            }
        }

        t_paciente.paciente.ordem_de_chegada = ordem_de_chegada;
        if(t_paciente.paciente.prioridade == normal) {
            fila_pacientes = adiciona_elemento_no_fim(fila_pacientes, t_paciente);
        } else {
            fila_pacientes = adiciona_elemento_no_inicio(fila_pacientes, t_paciente);
        }
        ordem_de_chegada++;
    }
    tamanho_fila_entrada = fila_pacientes->tamanho;

    for(int i = 0; i < NUM_ESPECIALISTAS; i++) {
        filas_atendimentos[i] = cria_lista();
    }

    while(fila_pacientes->inicio != NULL) {
        t_paciente_removido = remove_elemento_no_inicio(fila_pacientes);
        paciente_removido = (Paciente *) t_paciente_removido;
        t_atendimento_removido = remove_elemento_no_inicio(paciente_removido->lista_atendimento);
        atendimento_removido = (int *) t_atendimento_removido;
        if(t_paciente.paciente.prioridade == normal) {
            filas_atendimentos[*atendimento_removido - 1] = adiciona_elemento_no_fim(filas_atendimentos[*atendimento_removido - 1], *t_paciente_removido);
        } else {
            filas_atendimentos[*atendimento_removido - 1] = adiciona_elemento_no_inicio(filas_atendimentos[*atendimento_removido - 1], *t_paciente_removido);
        }
        free(atendimento_removido);
        free(paciente_removido);
    }

    for(int i = 0; i < NUM_ESPECIALISTAS; i++) {
        filas_pacientes_em_atendimento[i] = cria_lista();
    }
    lista_pacientes_finalizados = cria_lista();
    tamanho_fila_saida = lista_pacientes_finalizados->tamanho;
    while(tamanho_fila_saida < tamanho_fila_entrada) {
        for(int i = 0; i < NUM_ESPECIALISTAS; i++) {
            while(filas_atendimentos[i]->inicio != NULL && qtde_ocupados_por_id[i] < qtde_profissionais_por_id[i]) {
                t_paciente_removido = remove_elemento_no_inicio(filas_atendimentos[i]);
                paciente_removido = (Paciente *) t_paciente_removido;
                filas_pacientes_em_atendimento[i] = adiciona_elemento_no_fim(filas_pacientes_em_atendimento[i], *t_paciente_removido);
                qtde_ocupados_por_id[i] += 1;
                free(paciente_removido);
            }
        }

        j = 0;
        n = 0;
        for(int i = 0; i < NUM_ESPECIALISTAS; i++) {
            while(filas_pacientes_em_atendimento[i]->inicio != NULL && qtde_ocupados_por_id[i] > 0) {
                t_paciente_removido = remove_elemento_no_inicio(filas_pacientes_em_atendimento[i]);
                t_paciente_removido->paciente.horario_de_saida = duracao_total;
                v_desempate[j] = t_paciente_removido;
                j++;
                n++;
                qtde_ocupados_por_id[i] -= 1;
            }
        }
        qsort(v_desempate, n, sizeof(Paciente **), ordena_elementos);

        fila_do_desempate = cria_lista();
        for(int i = 0; i < n; i++) {
            fila_do_desempate = adiciona_elemento_no_fim(fila_do_desempate, *v_desempate[i]);
        }

        while(fila_do_desempate->inicio != NULL) {
            t_paciente_removido = remove_elemento_no_inicio(fila_do_desempate);
            t_paciente_removido->paciente.horario_de_saida = duracao_total;
            paciente_removido = (Paciente *) t_paciente_removido;
            t_atendimento_removido = remove_elemento_no_inicio(paciente_removido->lista_atendimento);
            if(t_atendimento_removido != NULL) {
                atendimento_removido = (int *) t_atendimento_removido;
                if(paciente_removido->prioridade == normal) {
                    filas_atendimentos[*atendimento_removido - 1] = adiciona_elemento_no_fim(filas_atendimentos[*atendimento_removido - 1], *t_paciente_removido);
                } else {
                    filas_atendimentos[*atendimento_removido - 1] = adiciona_elemento_no_inicio(filas_atendimentos[*atendimento_removido - 1], *t_paciente_removido);                    }
            } else {
                lista_pacientes_finalizados = adiciona_elemento_no_fim(lista_pacientes_finalizados, *t_paciente_removido);
            }
            free(t_atendimento_removido);
            free(paciente_removido);
        }
        duracao_total += duracao_atendimento_incremento;

        tamanho_fila_saida = lista_pacientes_finalizados->tamanho;
    }

    imprime_lista_saida_pacientes(lista_pacientes_finalizados);

    no = fila_pacientes->inicio;
    while(no != NULL) {
        destroi_lista(no->dado.paciente.lista_atendimento);
        no = no->proximo;
    }
    destroi_lista(fila_pacientes);

    for(int i = 0; i < NUM_ESPECIALISTAS; i++) {
        destroi_lista(filas_atendimentos[i]);
    }

    for(int i = 0; i < NUM_ESPECIALISTAS; i++) {
        destroi_lista(filas_pacientes_em_atendimento[i]);
    }

    destroi_lista(fila_do_desempate);
    destroi_lista(lista_pacientes_finalizados);

    return 0;
}
