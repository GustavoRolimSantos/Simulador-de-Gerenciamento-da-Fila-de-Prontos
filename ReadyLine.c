#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>

typedef struct {
    int pId;
    int cpu;
    char nome[80];
} BCP;

BCP prontos[7];
BCP prontosBackup[7];
BCP chegou[7];

int nextBCP = 0;

void criarProcesso(int cpus, char nomeP[80]) {
    prontos[nextBCP].pId = nextBCP + 100;
    prontos[nextBCP].cpu = cpus;
    strcpy(prontos[nextBCP].nome, nomeP);
    nextBCP++;
    printf("\n[FILA DE PRONTOS] Processo %s [%i] com %i ciclos criado!", nomeP, prontos[nextBCP].pId, cpus);
}

void executar() {
    memcpy(prontosBackup, prontos, 1024);

    system("cls");
    int maxCPU = -1;
    int chegouId = 1;

    while(maxCPU != 0) {
        maxCPU = 0;
        for (int i = 0; i < nextBCP; i++) {
            if (prontos[i].pId == -99)
                continue;

            if (prontos[i].cpu == 1) {

                bool bypass = false;

                for (int j = 0; j < nextBCP; j++) {
                    if (chegou[j].pId == -99)
                        continue;


                }

                if (!bypass) {
                    chegou[chegouId] = prontos[i];
                    chegouId++;
                }

            }

            if (prontos[i].cpu > 0) {
                printf("Executando processo %s [%i]\n", prontos[i].nome, prontos[i].pId);
                prontos[i].cpu = prontos[i].cpu - 1;
                maxCPU += prontos[i].cpu;
            }
        }
    }

    printf("\n\n------------------- TABELA DE FINALIZA��O -------------------\n");

    for (int i = 1; i < nextBCP+1; i++) {
        printf("\n%i� %s [%i]", i, chegou[i].nome, chegou[i]);
    }

    printf("\n\n-------------------------------------------------------------\n");
    printf("\n");
    printf("\nOp��es:\n");
    printf("\n[1] Manipular Tabela de Processos");
    printf("\n[2] Executar a Simula��o");
    printf("\n[3] Copyright");
    printf("\n[4] Encerrar\n\nInforme o c�digo da opera��o para executa-la. (1, 2, 3 ou 4): ");

    // Reset variables

    for (int i = 0; i < nextBCP; i++) {
        chegou[i].pId = -99;

        prontos[i].cpu = prontosBackup[i].cpu;
    }

    chegouId = 1;
}

void manipulate() {
    system("cls");

    int op = 0;
    bool display = true;

    printf("-------------------- MANIPULAR PROCESSOS --------------------\n");
    printf("\n");
    printf("\nInforme o c�digo da opera��o para executa-la:\n");
    printf("\n[1] Incluir");
    printf("\n[2] Alterar");
    printf("\n[3] Remover");
    printf("\n[4] Listar");
    printf("\n[5] Voltar ao menu principal");
    printf("\n------------------------------------------------------------");

    char pName[80];
    int pCPUs = 0, currentPID = 0;
    bool found = false;

    while(display) {
        printf("\n\nOpera��o: ");

        memset(pName, 0, 80);

        found = false;
        pCPUs = 0;

        scanf("%i", &op);
        fflush(stdin);

        switch(op) {
        default:
            printf("\n[FILA DE PRONTOS] O comando digitado � inv�lido!");
            break;
        case 1:
            printf("\nDigite o nome do processo: ");
            scanf("%s", &pName);
            fflush(stdin);

            ciclos:
            printf("Digite a quantidade de ciclos na CPU: ");
            scanf("%i", &pCPUs);
            fflush(stdin);

            while (pCPUs < 0) {
                printf("\n[FILA DE PRONTOS] N�mero de ciclos deve ser positivo.\n\n");
                goto ciclos;
            }

            criarProcesso(pCPUs, pName);

            break;
        case 2:
            printf("\nDigite o PID do processo que deseja editar: ");
            scanf("%i", &currentPID);
            fflush(stdin);

            int bcpId = 0, newCicles = 0;
            char newName[80];

            for (int i = 0; i < nextBCP; i++) {
                if (prontos[i].pId == -99)
                    continue;
                if (prontos[i].pId == currentPID) {
                    bcpId = i;
                    found = true;
                }
            }

            if (!found) {
                printf("\n[FILA DE PRONTOS] N�o foi possivel localizar o processo com o PID informado.");
                return;
            }

            printf("\nDigite o novo Nome do processo: ");
            scanf("%s", &newName);

            ciclos_edit:
            printf("\nDigite a nova Quantidade de ciclos na CPU: ");
            scanf("%i", &newCicles);

            while (newCicles < 0) {
                printf("\n[FILA DE PRONTOS] N�mero de ciclos deve ser positivo.\n\n");
                goto ciclos_edit;
            }

            sprintf(prontos[bcpId].nome, "%s", newName);
            prontos[bcpId].cpu = newCicles;

            printf("\n[FILA DE PRONTOS] Processo %s [%i] com %i ciclos atualizado!", newName, prontos[bcpId].pId, newCicles);

            break;
        case 3:

            printf("\nDigite o PID do processo que deseja remover: ");
            scanf("%i", &currentPID);
            fflush(stdin);

            char rmvName[80];

            for (int i = 0; i < nextBCP; i++) {
                if (prontos[i].pId == -99)
                    continue;
                if (prontos[i].pId == currentPID) {
                    prontos[i].pId = -99;
                    found = true;
                }
            }

            if (!found) {
                printf("\n[FILA DE PRONTOS] N�o foi possivel localizar o processo com o PID informado.");
            }

            printf("\n[FILA DE PRONTOS] Processo %s [%i] removido com sucesso!", rmvName, currentPID);
            break;
        case 4:
            system("cls");
            printf("\n-------------------- PROCESSOS EXISTENTES --------------------\n");
            printf("\nNOME  |    PID   |    CPU");
            for (int i = 0; i < nextBCP; i++) {
                if (prontos[i].pId == -99)
                    continue;
                /*char* nameP;

                char apoio[80];
                strcpy(apoio, prontos[i].nome);

                memcpy(nameP, apoio, 10);

                for (int j = 0; j < 10; j++) {
                    if (nameP[j] == NULL) {
                        nameP[j] = ' ';
                    }
                }*/

                printf("\n%s     %i         %i", prontos[i].nome, prontos[i].pId, prontos[i].cpu);
            }
            printf("\n\n--------------------------------------------------------------");

            printf("\n\nInforme o c�digo da opera��o para executa-la. (1, 2, 3 ou 4):\n");
            printf("\n[1] Incluir");
            printf("\n[2] Alterar");
            printf("\n[3] Remover");
            printf("\n[4] Listar");
            printf("\n[5] Voltar ao menu principal");
            break;
        case 5:
            display = false;
            break;
        }
    }
    controller();
}

void copyright() {
    printf("\nEquipe de Desenvolvedores: \n");
    printf("- Andr� Nicola Nunes \n");
    printf("- Gustavo Rolim dos Santos \n");
    printf("- Maicon Gabriel de S� \n");
    printf("- Vinicius Penachioni Tenomaro \n\n");
}

void controller() {
    system("cls");
    int op = 0;
    bool display = true;

    printf("------------------------------------------------------------\n");
    printf("\n");
    printf(" Simulador de Gerenciamento da Fila de Prontos\n");
    printf(" Projeto de Sistemas Operacionais I - 2� Semestre\n");
    printf(" Fatec Americana\n");
    printf("\n");
    printf("\n Informe o c�digo da opera��o para executa-la. (1, 2, 3 ou 4):\n");
    printf("\n [1] Manipular Tabela de Processos");
    printf("\n [2] Executar a Simula��o");
    printf("\n [3] Copyright");
    printf("\n [4] Encerrar\n");
    printf("\n------------------------------------------------------------\n");

    while(display) {
        printf("\nOp��o: ");
        scanf("%i", &op);
        fflush(stdin);

        switch(op) {
        default:
            printf("\n[FILA DE PRONTOS] O comando digitado � inv�lido!");
            break;
        case 1:
            manipulate();
            break;
        case 2:
            executar();
            break;
        case 3:
            copyright();
            break;
        case 4:
            printf("\nFechando o programa...\n");
            display = false;
            break;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    controller();

    return 0;
}
