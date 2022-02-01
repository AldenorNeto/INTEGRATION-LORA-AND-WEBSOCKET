#include <stdio.h>
#include <string.h>
void setup() {

  char *lista[5];
int i = 0;
    char frutas[] = "banana,laranja,morango,laranja,morango";
    char *token = strtok(frutas, ",");

    while(token != NULL) {
        printf("%s", token);
        lista[i] = token;
        i++;
        token = strtok(NULL, ",");
        printf("\n");
    }

    printf("\n");
    printf("\n ---");
    printf(lista[0]);
    printf(lista[1]);
    printf(lista[2]);
    printf(lista[3]);
    printf(lista[4]);
}

void loop() {


}
