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

// le string entre aspas e nao armazena as aspas
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

int compara_elementos(const void *elemento_a, const void *elemento_b) {
    Paciente *a = *(Paciente **) elemento_a;
    Paciente *b = *(Paciente **) elemento_b;

    // compara elementos do tipo int
    if(a->ordem_de_chegada <  b->ordem_de_chegada) {
        return -1;
    } else if(a->ordem_de_chegada >  b->ordem_de_chegada) {
        return 1;
    } else {
        return 0;
    }
}

Horario converte_segundos_em_horas_minutos(int segundos) {
    Horario horario;

    segundos += 28800; // adiciona 8 horas
    horario.horas = segundos / 3600;
    horario.minutos = (segundos - (3600 * horario.horas)) / 60;

    return horario;
}

void imprime_lista_saida_pacientes(PLista lista) {
    PNo atual;
    Horario horario;

    atual = lista->inicio;
    while(atual != NULL) {
        horario = converte_segundos_em_horas_minutos(
            atual->dado.paciente.horario_de_saida);
        printf("%.2d:%.2d ", horario.horas, horario.minutos);
        printf("%s ", atual->dado.paciente.nome);
        printf("\n");

        atual = atual->proximo;
    }
}

char *converte_enum_para_string(EPrioridade prior) {
    char *strings[] = { "normal", "preferencial" };

    return strings[prior];
}

EPrioridade converte_string_para_enum(char *str) {
    EPrioridade prioridade = 0;
    char *strings[] = { "normal", "preferencial" };

    if(str[0] == strings[1][0]) {
        prioridade = 1;
    }

    return prioridade;
}
