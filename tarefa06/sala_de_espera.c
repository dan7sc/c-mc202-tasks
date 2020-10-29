#include <stdio.h>

#define TAM_STR 50

void le_int(int *num) {
    scanf("%d", num);
}

void le_char(char *ch) {
    scanf("%c", ch);
}

void le_string(char *str) {
    scanf("%s", str);
}

void le_string_entre_aspas(char *str) {
    char ch;
    int i;
    int contador = 0;

    for(i = 0; contador < 2 && i < TAM_STR; i++) {
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
    char nome[TAM_STR];

    le_string_entre_aspas(nome);
    printf("%s\n", nome);

    return 0;
}
