#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>

typedef struct {
    int pId;
    int cpu;
    char nome[80];
} BCP;

BCP prontos[1024];
BCP prontosBackup[1024];
BCP chegou[1024];

int nextBCP = 0;

void criarProcesso(int cpus, char nomeP[80]) {
    prontos[nextBCP].pId = nextBCP + 100;
    prontos[nextBCP].cpu = cpus;
    strcpy(prontos[nextBCP].nome, nomeP);
    printf("\n[FILA DE PRONTOS] Processo %s [%i] com %i ciclos criado!", nomeP, prontos[nextBCP].pId, cpus);
    nextBCP++;
}

bool canExecute() {
    int real = 0;

    for (int i = 0; i < nextBCP; i++) {
        if (prontos[i].pId == -99)
            continue;

        real++;
    }

    return real > 0;
}

void executar() {

    if (!canExecute()) {
        printf("\n[FILA DE PRONTOS] Para iniciar a execução é necessário existir pelo menos 1 processo.");
        return;
    }


    memcpy(prontosBackup, prontos, 10000);

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

            /*if ((i+1) >= 7 && (i+1) % 7 == 0 && i < (nextBCP -1)) {
                printf("\n[FILA DE PRONTOS] Aguardando a próxima fila...\n");
            }*/
        }
    }

    printf("\n------------------- TABELA DE FINALIZAÇÃO -------------------\n");

    for (int i = 1; i < nextBCP+1; i++) {
        if (chegou[i].pId != -99)
            printf("\n %iº %s [%i]", i, chegou[i].nome, chegou[i]);
    }

    printf("\n\n-------------------------------------------------------------\n");
    printf("\nOpções:\n");
    printf("\n[1] Manipular Tabela de Processos");
    printf("\n[2] Executar a Simulação");
    printf("\n[3] Copyright");
    printf("\n[4] Encerrar\n\nInforme o código da operação para executa-la. (1, 2, 3 ou 4): ");

    // Reset variables

    for (int i = 0; i < nextBCP; i++) {
        chegou[i].pId = -99;

        prontos[i].cpu = prontosBackup[i].cpu;
    }

    chegouId = 1;
}

bool canCreate() {
    int real = 0;

    for (int i = 0; i < nextBCP; i++) {
        if (prontos[i].pId == -99)
            continue;

        real++;
    }

    return real < 7;
}

void manipulate() {
    system("cls");

    int op = 0;
    bool display = true;

    printf("-------------------- MANIPULAR PROCESSOS --------------------\n");
    printf("\n");
    printf("\nInforme o código da operação para executa-la:\n");
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
        printf("\n\nOperação: ");

        memset(pName, 0, 80);

        found = false;
        pCPUs = 0;

        scanf("%i", &op);
        fflush(stdin);

        switch(op) {
        default:
            printf("\n[FILA DE PRONTOS] O comando digitado é inválido!");
            break;
        case 1:

            if (!canCreate()) {
                printf("\n[FILA DE PRONTOS] Limite de processos atingido. Máximo: 7");
                break;
            }

            printf("\nDigite o nome do processo: ");
            scanf("%s", &pName);
            fflush(stdin);

            ciclos:
            printf("Digite a quantidade de ciclos na CPU: ");
            scanf("%i", &pCPUs);
            fflush(stdin);

            while (pCPUs < 0) {
                printf("\n[FILA DE PRONTOS] Número de ciclos deve ser positivo.\n\n");
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
                printf("\n[FILA DE PRONTOS] Não foi possivel localizar o processo com o PID informado.");
                break;
            }

            printf("\nDigite o novo Nome do processo: ");
            scanf("%s", &newName);

            ciclos_edit:
            printf("\nDigite a nova Quantidade de ciclos na CPU: ");
            scanf("%i", &newCicles);

            while (newCicles < 0) {
                printf("\n[FILA DE PRONTOS] Número de ciclos deve ser positivo.\n\n");
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
                    prontosBackup[i].pId = -99;
                    strcpy(rmvName, prontos[i].nome);
                    found = true;
                }
            }

            if (!found) {
                printf("\n[FILA DE PRONTOS] Não foi possivel localizar o processo com o PID informado.");
                break;
            }

            nextBCP--;
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

            printf("\n\nInforme o código da operação para executa-la. (1, 2, 3 ou 4):\n");
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
    printf("</> André Nicola Nunes \n");
    printf("</> Gustavo Rolim dos Santos \n");
    printf("</> Maicon Gabriel de Sá \n");
    printf("</> Vinicius Penachioni Tenomaro \n\n");
}

bool displayController = true;

void controller() {
    system("cls");
    int op = 0;

    printf("------------------------------------------------------------\n");
    printf("\n");
    printf(" Simulador de Gerenciamento da Fila de Prontos\n");
    printf(" Projeto de Sistemas Operacionais I - 2º Semestre\n");
    printf(" Fatec Americana\n");
    printf("\n");
    printf("\n Informe o código da operação para executa-la. (1, 2, 3 ou 4):\n");
    printf("\n [1] Manipular Tabela de Processos");
    printf("\n [2] Executar a Simulação");
    printf("\n [3] Copyright");
    printf("\n [4] Encerrar\n");
    printf("\n------------------------------------------------------------\n");

    while(displayController) {
        printf("\nOpção: ");
        scanf("%i", &op);
        fflush(stdin);

        switch(op) {
        default:
            printf("\n[FILA DE PRONTOS] O comando digitado é inválido!");
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
            displayController = false;
            break;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    controller();

    return 0;
}
