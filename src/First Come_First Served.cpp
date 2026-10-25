#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

int main() {
    int n;
    cout << "--- Simulador FCFS ---" << endl;
    cout << "Digite a quantidade de processos: ";
    cin >> n;

    
    int tempo_chegada[100];
    int tempo_execucao[100];
    int tempo_espera[100];
    int tempo_resposta[100];
    int tempo_conclusao[100];
    string processos[100];


    for (int i = 0; i < n; i++) {
        stringstream ss;
        ss << "P" << (i + 1);
        processos[i] = ss.str(); 

        cout << "\nTempo de chegada do " << processos[i] << ": ";
        cin >> tempo_chegada[i];
        cout << "Tempo de execucao (Burst) do " << processos[i] << ": ";
        cin >> tempo_execucao[i];
    }

    int tempo_atual = 0;
    float soma_espera = 0.0;
    float soma_resposta = 0.0;


    for (int i = 0; i < n; i++) {
     
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


    cout << "\n---------------------------------------------------------------------------\n";
    cout << left << setw(12) << "Processo" 
         << setw(12) << "Chegada" 
         << setw(18) << "Execucao (Burst)" 
         << setw(12) << "Espera" 
         << "Resposta (Turnaround)\n";
    cout << "---------------------------------------------------------------------------\n";

    for (int i = 0; i < n; i++) {
        cout << left << setw(12) << processos[i] 
             << setw(12) << tempo_chegada[i] 
             << setw(18) << tempo_execucao[i] 
             << setw(12) << tempo_espera[i] 
             << tempo_resposta[i] << "\n";
    }

    cout << "---------------------------------------------------------------------------\n";
    

    cout << fixed << setprecision(2);
    cout << "Tempo medio de espera: " << (soma_espera / n) << " unidades\n";
    cout << "Tempo medio de resposta: " << (soma_resposta / n) << " unidades\n";

    return 0;
}
