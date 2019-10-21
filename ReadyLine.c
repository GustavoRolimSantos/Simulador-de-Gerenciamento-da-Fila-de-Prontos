#include <stdio.h>

typedef struct {
     int pId;
    int cpu;
    char* nome;
} BCP;

BCP processos[10];

int main()
{
   for (int i = 0; i < 5; i++) {
        processos[i].pId = i;
   }
   
   for (int i = 0; i < 5; i++) {
        printf("%i", processos[i].pId);
   }

    return 0;
}
