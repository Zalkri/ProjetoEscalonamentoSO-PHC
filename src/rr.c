#include <stdio.h>

int main() {
    int n, quantum;
    int i, tempo = 0;
    int processos[10], restante[10];

    printf("Digite a quantidade de processos (max. 10): ");
    scanf("%d", &n);

    printf("Digite o quantum: ");
    scanf("%d", &quantum);

    for (i = 0; i < n; i++) {
        processos[i] = i + 1;

        printf("Tempo de execucao do processo P%d: ", i + 1);
        scanf("%d", &restante[i]);
    }

    printf("\nOrdem de execucao:\n");

    int concluidos = 0;

    while (concluidos < n) {
        for (i = 0; i < n; i++) {
            if (restante[i] > 0) {
                if (restante[i] > quantum) {
                    printf("P%d executou por %d unidades\n",
                           processos[i], quantum);

                    restante[i] -= quantum;
                    tempo += quantum;
                } else {
                    printf("P%d executou por %d unidades\n",
                           processos[i], restante[i]);

                    tempo += restante[i];
                    restante[i] = 0;
                    concluidos++;

                    printf("P%d finalizado no tempo %d\n",
                           processos[i], tempo);
                }
            }
        }
    }

    printf("\nTodos os processos foram finalizados!\n");

    return 0;
}
