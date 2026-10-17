#include <stdio.h>

#define MAX 100

typedef struct{
    int id;
    int chegada;
    int duracao;
    int prioridade;
}Processo;

int main(){
    Processo processo[MAX];
    int n;
    printf("Quantos processos deseja cadastrar ?");
    scanf("%d", &n);

for(int i=0;i<n;i++){
    printf("\nProcesso %d\n",i+1);

    processo[i].id=i+1;

    printf("Tempo de chegada:");
    scanf("%d",&processo[i].chegada);

    printf("Duração:");
    scanf("%d",&processo[i].duracao);

    printf("Prioridade: ");
    scanf("%d",&processo[i].prioridade);
}
printf("\n--Processos cadastrados---\n");

for(int i=0;i<n;i++){
    printf("\nProcesso: P%d\n",processo[i].id);
    printf("Chegada: %d\n",processo[i].chegada);
    printf("Duração:%d\n",processo[i].duracao);
    printf("Prioridade:%d\n",processo[i].prioridade);
}
return 0;
}