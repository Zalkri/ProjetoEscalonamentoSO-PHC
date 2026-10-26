#include <stdio.h>

int main() {
    int n;
    printf("--- Simulador FCFS ---\n");
    printf("Digite a quantidade de processos: ");
    scanf("%d", &n);


    int tempo_chegada[100];
    int tempo_execucao[100];
    int tempo_espera[100];
    int tempo_resposta[100];
    int tempo_conclusao[100];

    int i;
 
    for (i = 0; i < n; i++) {
        printf("\nTempo de chegada do P%d: ", i + 1);
        scanf("%d", &tempo_chegada[i]);
        
        printf("Tempo de execucao (Burst) do P%d: ", i + 1);
        scanf("%d", &tempo_execucao[i]);
    }

    int tempo_atual = 0;
    float soma_espera = 0.0;
    float soma_resposta = 0.0;


    for (i = 0; i < n; i++) {
    
        if (tempo_atual < tempo_chegada[i]) {
            tempo_atual = tempo_chegada[i];
        }

        tempo_espera[i] = tempo_atual - tempo_chegada[i];
        soma_espera += tempo_espera[i];

        tempo_atual += tempo_execucao[i];
        tempo_conclusao[i] = tempo_atual;

        tempo_resposta[i] = tempo_conclusao[i] - tempo_chegada[i];
        soma_resposta += tempo_resposta[i];
    }

    printf("\n---------------------------------------------------------------------------\n");
    printf("%-12s %-12s %-18s %-12s %-20s\n", "Processo", "Chegada", "Execucao (Burst)", "Espera", "Resposta (Turnaround)");
    printf("---------------------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
       
        printf("P%-11d %-12d %-18d %-12d %-20d\n", i + 1, tempo_chegada[i], tempo_execucao[i], tempo_espera[i], tempo_resposta[i]);
    }

    printf("---------------------------------------------------------------------------\n");
    
  
    printf("Tempo medio de espera: %.2f unidades\n", soma_espera / n);
    printf("Tempo medio de resposta: %.2f unidades\n", soma_resposta / n);

    return 0;
}

