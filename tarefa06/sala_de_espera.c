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

/* int compara_elementos(const void *elemento_a, const void *elemento_b) { */
/*     Paciente *a = *(Paciente **) elemento_a; */
/*     Paciente *b = *(Paciente **) elemento_b; */

/*     return (a->ordem_de_chegada - b->ordem_de_chegada); */
/* } */

int compara_elementos(const void *elemento_a, const void *elemento_b) {
    Paciente *a = *(Paciente **) elemento_a;
    Paciente *b = *(Paciente **) elemento_b;

    if(a->ordem_de_chegada <  b->ordem_de_chegada) return -1;
    else if(a->ordem_de_chegada >  b->ordem_de_chegada) return 1;
    else return 0;
}

int main() {
    PLista fila_pacientes; // fila geral de pacientes que serão atendidos
    PLista filas_atendimentos[9]; // filas para cada um dos 9 tipos de especialidades diferentes de atendimento
    PLista filas_pacientes_em_atendimento[9]; // filas de paciente para cada especialidade
    PLista lista_pacientes_finalizados; // lista com os pacientes que já foram atendidos
    PNo no; // apenas um ponteiro para nó para auxiliar na destruição das listas ligadas
    TDado t_paciente; // union do tipo Paciente para armazenar paciente
    TDado t_atendimento; // union do tipo int para armazenar atendimento do paciente
    TDado *vetor_desempate[NUM_PROFISSIONAIS]; // vetor de pacientes que terminaram o atendimento e serão ordenados segundo a ordem de chegada deles
    TDado *t_paciente_removido; // ponteiro para union do tipo Paciente de paciente que foi removido da fila
    Paciente paciente_removido;
    TDado *t_atendimento_removido; // ponteiro para union do tipo int de atendimento que foi removido da lista de atendimentos do paciente
    int atendimento_removido;
    int ordem_de_chegada = 1; // ordem de chegada do paciente
    int tamanho_fila_entrada = 0; // tamanho da fila geral inicial de entrada dos pacientes
    int tamanho_fila_saida; // tamanho da fila dos pacientes que ja foram atendidos
    int duracao_total = 600; // duração total do atendimento em segundos [equivale a 10 minutos]
    int duracao_atendimento_incremento = 600; // duração do atendimento a ser incrementado em segundos [equivale a 10 minutos]
    int indice_desempate; // indice do vetor_desempate
    int num_pacientes_para_desempate; // número de pacientes que serão ordenados para desempate
    int para_de_ler_entrada = 1; // para de ler atendimento quando maior que 0 e para de ler entrada quando menor que 0
    char str_prioridade[15]; // prioridade em formato string
    int qtde_profissionais_por_id[] = { 10, 2, 5, 3, 4, 7, 2, 1, 4 }; // quantidade total de profissionais disponíveis para cada especialidade
    int qtde_ocupados_por_id[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // quantidade de profissionais ocupados para cada especialidade

    fila_pacientes = cria_lista();
    while(para_de_ler_entrada > -1) {
        t_paciente.paciente.lista_atendimento = cria_lista();
        // lê dados de cada paciente a entrar na fila
        le_string_entre_aspas(t_paciente.paciente.nome);
        le_string(str_prioridade);
        // prioridade de cada paciente é do tipo enum: normal = 0, preferencial = 1
        t_paciente.paciente.prioridade = converte_string_para_enum(str_prioridade);
        // horário de saída em segundos
        t_paciente.paciente.horario_de_saida = 0;

        para_de_ler_entrada = 1;
        // lê a sequencia de atendimentos de cada paciente e armazena-os numa lista
        while(para_de_ler_entrada > 0) {
            para_de_ler_entrada = scanf("%d", &(t_atendimento.id));
            if(para_de_ler_entrada > 0) {
                t_paciente.paciente.lista_atendimento = adiciona_elemento_no_fim(t_paciente.paciente.lista_atendimento, t_atendimento);
            }
        }
        // ordem de chegada do paciente na fila
        t_paciente.paciente.ordem_de_chegada = ordem_de_chegada;
        if(t_paciente.paciente.prioridade == normal) {
            // pacientes normais são armazenados no fim da fila
            fila_pacientes = adiciona_elemento_no_fim(fila_pacientes, t_paciente);
        } else {
            // pacientes preferenciais são armazenados no início da fila
            fila_pacientes = adiciona_elemento_no_inicio(fila_pacientes, t_paciente);
        }
        ordem_de_chegada++;
    }
    // guarda o tamanho da fila de entrada inicial
    tamanho_fila_entrada = fila_pacientes->tamanho;

    // cria filas de atendimento para cada especialista onde o especialista 1 tem indice 0, especialista 2 indice 1 e assim por diante
    for(int i = 0; i < NUM_ESPECIALISTAS; i++) {
        filas_atendimentos[i] = cria_lista();
    }

    // remove paciente da fila geral e o coloca na fila do primeiro especilista indicado na lista de atendimento do paciente
    while(fila_pacientes->inicio != NULL) {
        t_paciente_removido = remove_elemento_no_inicio(fila_pacientes);
        // necessário definir o tipo de dado para acessar a lista de atendimento do paciente
        paciente_removido = *(Paciente *) t_paciente_removido;
        // remove o id do especialista a ser consultado da lista de atendimento do paciente
        t_atendimento_removido = remove_elemento_no_inicio(paciente_removido.lista_atendimento);
        // necessário definir o tipo de dado para poder fazer operações com inteiros
        atendimento_removido = *(int *) t_atendimento_removido;
        if(t_paciente.paciente.prioridade == normal) {
            // pacientes normais são armazenados no fim da fila
            filas_atendimentos[atendimento_removido - 1] = adiciona_elemento_no_fim(filas_atendimentos[atendimento_removido - 1], *t_paciente_removido);
        } else {
            // pacientes preferenciais são armazenados no início da fila
            filas_atendimentos[atendimento_removido - 1] = adiciona_elemento_no_inicio(filas_atendimentos[atendimento_removido - 1], *t_paciente_removido);
        }
        // libera memória dos dados removidos
        free(t_atendimento_removido);
        free(t_paciente_removido);
    }

    // cria fila com pacientes que estão sendo atendidos pelos profissionais
    for(int i = 0; i < NUM_ESPECIALISTAS; i++) {
        filas_pacientes_em_atendimento[i] = cria_lista();
    }

    // cria lista com os pacientes que finalizaram todos os seus atendimentos
    lista_pacientes_finalizados = cria_lista();

    // nenhum paciente ainda terminou seus atendimentos
    tamanho_fila_saida = 0;
    // loop só para quando todos os pacientes tiverem terminado todos os seus respectivos atendimentos
    while(tamanho_fila_saida < tamanho_fila_entrada) {
        for(int i = 0; i < NUM_ESPECIALISTAS; i++) {
            // pacientes são atendidos pelos especialistas até não houver mais profissionais vagos
            // ou não houver pacientes para serem atendidos por determinado especialista
            while(filas_atendimentos[i]->inicio != NULL && qtde_ocupados_por_id[i] < qtde_profissionais_por_id[i]) {
                // paciente é removido da fila dos pacientes que serão atendidos pelo especialista i
                t_paciente_removido = remove_elemento_no_inicio(filas_atendimentos[i]);
                // paciente é inserido na fila dos pacientes que estão em atendimento pelo especialista i
                filas_pacientes_em_atendimento[i] = adiciona_elemento_no_fim(filas_pacientes_em_atendimento[i], *t_paciente_removido);
                // quando um paciente é atendido um profissional para cada especialidade i está ocupado
                qtde_ocupados_por_id[i] += 1;
                free(t_paciente_removido);
            }
        }

        indice_desempate = 0;
        num_pacientes_para_desempate = 0;
        for(int i = 0; i < NUM_ESPECIALISTAS; i++) {
            while(filas_pacientes_em_atendimento[i]->inicio != NULL && qtde_ocupados_por_id[i] > 0) {
                // paciente já atendido é removido do consultório
                t_paciente_removido = remove_elemento_no_inicio(filas_pacientes_em_atendimento[i]);
                // atualiza duração do paciente no hospital
                t_paciente_removido->paciente.horario_de_saida = duracao_total;
                // paciente entra no vetor com pacientes que serão inseridos de novo nas filas de atendimento
                vetor_desempate[indice_desempate] = t_paciente_removido;
                indice_desempate += 1;
                // conta pacientes que foram atendidos e serão ordenados pela função qsort
                num_pacientes_para_desempate += 1;
                // quando um paciente termina de ser atendido um profissional para cada especialidade i está vago
                qtde_ocupados_por_id[i] -= 1;
            }
        }
        // ordena vetor de desempate
        qsort(vetor_desempate, num_pacientes_para_desempate, sizeof(Paciente *), compara_elementos);

        indice_desempate = 0;
        while(indice_desempate < num_pacientes_para_desempate) {
            /* t_paciente_removido = remove_elemento_no_inicio(fila_pacientes_ordenados); */
            t_paciente_removido = vetor_desempate[indice_desempate];
            t_paciente_removido->paciente.horario_de_saida = duracao_total;
            paciente_removido = *(Paciente *) t_paciente_removido;
            t_atendimento_removido = remove_elemento_no_inicio(paciente_removido.lista_atendimento);
            if(t_atendimento_removido != NULL) {
                atendimento_removido = *(int *) t_atendimento_removido;
                if(paciente_removido.prioridade == normal) {
                    // pacientes normais são armazenados no fim da fila
                    filas_atendimentos[atendimento_removido - 1] = adiciona_elemento_no_fim(filas_atendimentos[atendimento_removido - 1], *t_paciente_removido);
                } else {
                    // pacientes preferenciais são armazenados no início da fila
                    filas_atendimentos[atendimento_removido - 1] = adiciona_elemento_no_inicio(filas_atendimentos[atendimento_removido - 1], *t_paciente_removido);                    }
            } else {
                lista_pacientes_finalizados = adiciona_elemento_no_fim(lista_pacientes_finalizados, *t_paciente_removido);
            }
            indice_desempate += 1;

            free(t_atendimento_removido);
            free(t_paciente_removido);
        }
        // incrementa duração no hospital em 10 minutos
        duracao_total += duracao_atendimento_incremento;

        // atualiza o tamanho da fila de saída
        tamanho_fila_saida = lista_pacientes_finalizados->tamanho;
    }

    // imprime, em ordem, os horários e nomes de cada paciente que saiu do hospital
    imprime_lista_saida_pacientes(lista_pacientes_finalizados);

    // destroi todas as filas/listas criadas
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

    destroi_lista(lista_pacientes_finalizados);

    return 0;
}
