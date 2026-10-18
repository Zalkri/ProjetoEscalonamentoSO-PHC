#include <stdio.h>    // Biblioteca padrao para entrada e saida (printf)
#include <stdbool.h>  // Biblioteca para usar tipo booleano (verdadeiro/falso)
#include <limits.h>   // Biblioteca para usar o maior valor inteiro (INT_MAX)

// Estrutura que guarda os dados de cada processo
typedef struct {
    int id;               // Identificador do processo (ex: 1 para P1)
    int tempo_chegada;     // Momento em que o processo chega a fila de prontos
    int tempo_execucao;    // Tempo total de CPU necessario (Burst)
    int tempo_restante;    // Tempo de CPU que AINDA FALTA para concluir
    int tempo_conclusao;   // Momento em que o processo finaliza 100%
    int tempo_espera;      // Tempo total que o processo passou esperando na fila
    int tempo_retorno;     // Tempo total do processo no sistema (Turnaround)
} Processo;

// Funcao que executa o escalonamento SRTF
void executar_SRTF(Processo processos[], int total_processos) {
    int tempo_atual = 0;              // Relogio/cronometro central do sistema
    int concluidos = 0;               // Contador de processos finalizados
    int menor_tempo_restante;         // Guarda o menor tempo restante encontrado
    int indice_menor = -1;            // Guarda a posicao do processo escolhido
    bool encontrou_processo = false;  // Sinaliza se algum processo esta pronto

    // Passo 1: Inicializa o tempo restante de cada processo igual ao tempo de execucao
    for (int i = 0; i < total_processos; i++) {
        processos[i].tempo_restante = processos[i].tempo_execucao;
    }

    printf("\n--- ORDEM DE EXECUCAO DO SRTF ---\n");

    // Passo 2: Executa o relogio ate todos os processos concluirem
    while (concluidos != total_processos) {
        menor_tempo_restante = INT_MAX;
        indice_menor = -1;
        encontrou_processo = false;

        // Procura o processo pronto com MENOR tempo restante
        for (int i = 0; i < total_processos; i++) {
            if (processos[i].tempo_chegada <= tempo_atual && processos[i].tempo_restante > 0) {
                if (processos[i].tempo_restante < menor_tempo_restante) {
                    menor_tempo_restante = processos[i].tempo_restante;
                    indice_menor = i;
                    encontrou_processo = true;
                }
            }
        }

        // Se nenhum processo chegou no tempo atual (CPU ociosa)
        if (!encontrou_processo) {
            tempo_atual++;
            continue;
        }

        // Passo 3: Executa 1 unidade de tempo do processo selecionado (Preempcao)
        processos[indice_menor].tempo_restante--;
        printf("[Tempo %d-%d] Executando Processo P%d\n", tempo_atual, tempo_atual + 1, processos[indice_menor].id);

        // Se o processo terminou sua execucao
        if (processos[indice_menor].tempo_restante == 0) {
            concluidos++;
            processos[indice_menor].tempo_conclusao = tempo_atual + 1;
            processos[indice_menor].tempo_retorno = processos[indice_menor].tempo_conclusao - processos[indice_menor].tempo_chegada;
            processos[indice_menor].tempo_espera = processos[indice_menor].tempo_retorno - processos[indice_menor].tempo_execucao;
        }

        tempo_atual++; // Avanca o relogio em 1 unidade
    }

    // Passo 4: Imprime a tabela final de resultados
    printf("\n-----------------------------------------------------\n");
    printf("%-6s %-10s %-11s %-11s %-9s %s\n", "ID", "Chegada", "Execucao", "Conclusao", "Espera", "Retorno");
    printf("-----------------------------------------------------\n");
    for (int i = 0; i < total_processos; i++) {
        printf("P%-5d %-10d %-11d %-11d %-9d %d\n", 
            processos[i].id, 
            processos[i].tempo_chegada, 
            processos[i].tempo_execucao,
            processos[i].tempo_conclusao, 
            processos[i].tempo_espera, 
            processos[i].tempo_retorno);
    }
}

int main() {
    // Vetor com os dados de teste dos processos
    Processo lista_processos[] = {
        {1, 0, 8, 0, 0, 0, 0}, // P1: Chegada = 0, Execucao = 8
        {2, 1, 4, 0, 0, 0, 0}, // P2: Chegada = 1, Execucao = 4
        {3, 2, 9, 0, 0, 0, 0}, // P3: Chegada = 2, Execucao = 9
        {4, 3, 5, 0, 0, 0, 0}  // P4: Chegada = 3, Execucao = 5
    };
    
    int quantidade = sizeof(lista_processos) / sizeof(lista_processos[0]);

    // Executa a simulacao do SRTF
    executar_SRTF(lista_processos, quantidade);

    return 0;
}
