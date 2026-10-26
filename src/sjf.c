#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int id;               
    int arrival_time;     
    int burst_time;       
    int waiting_time;     
    int turnaround_time;  
    int completion_time;  
    int executed;         
} Process;

void calcularSJF(Process p[], int n) {
    int completed = 0, current_time = 0;
    float total_waiting = 0, total_turnaround = 0;

    printf("\n--- Ordem de Execução dos Processos ---\n");

    while (completed < n) {
        int idx = -1;
        int min_burst = 99999; 


        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && !p[i].executed) {
                if (p[i].burst_time < min_burst) {
                    min_burst = p[i].burst_time;
                    idx = i;
                }
            }
        }


        if (idx == -1) {
            current_time++;
        } else {
            
            current_time += p[idx].burst_time;
            p[idx].completion_time = current_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;


            total_waiting += p[idx].waiting_time;
            total_turnaround += p[idx].turnaround_time;

            p[idx].executed = 1; // Marca como concluído
            completed++;

            printf("Tempo %2d -> Processo P%d executado (Conclusão: %d)\n", 
                   current_time - p[idx].burst_time, p[idx].id, p[idx].completion_time);
        }
    }


    printf("\n=================================================================\n");
    printf("ID\tChegada\tBurst\tEspera\tRetorno\tConclusão\n");
    printf("=================================================================\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", 
               p[i].id, p[i].arrival_time, p[i].burst_time, 
               p[i].waiting_time, p[i].turnaround_time, p[i].completion_time);
    }
    printf("=================================================================\n");
    printf("Tempo Médio de Espera: %.2f ms\n", total_waiting / n);
    printf("Tempo Médio de Retorno: %.2f ms\n", total_turnaround / n);
}

int main() {
    int n;

    printf("Digite o número de processos: ");
    scanf("%d", &n);

    Process *p = (Process *)malloc(n * sizeof(Process));

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        p[i].executed = 0;
        printf("\nProcesso P%d:\n", p[i].id);
        printf("  Tempo de Chegada: ");
        scanf("%d", &p[i].arrival_time);
        printf("  Tempo de Execução (Burst): ");
        scanf("%d", &p[i].burst_time);
    }

    calcularSJF(p, n);

    free(p);
    return 0;
}