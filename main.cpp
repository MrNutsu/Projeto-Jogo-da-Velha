#include <iostream>
using namespace std;

// Declaração das funções
void printarTabuleiro(char tabuleiro[3][3]);
void getEscolha(int& escolha);
bool verificarEscolha(char tabuleiro[3][3], int escolha, int& linha, int& coluna);
bool verificarSeHouveVitoria(char tabuleiro[3][3], char jogadorAtual);

int main() {
    // Inicialização do tabuleiro
    char tabuleiro[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    
    // Definição dos jogadores
    const char jogadorX = 'X';
    const char jogadorO = 'O';
    char jogadorAtual = jogadorX;
    
    // Variáveis para controlar o estado do jogo
    int linha, coluna, escolha;
    bool vitoria = false;

    // Loop principal do jogo, máximo de 9 rodadas (para cada espaço do tabuleiro)
    for (int i = 0; i < 9; i++) {

        cout<<"\n\t=============== Jogo da Velha ===============\n"<<endl;

        // Imprime o tabuleiro atual
        printarTabuleiro(tabuleiro);


        cout <<"O jogador atual eh: " << jogadorAtual << endl;

        // Loop para obter uma escolha válida do jogador
        while (true) {
            // Solicita ao jogador que escolha uma posição no tabuleiro
            getEscolha(escolha);
            // Verifica se a escolha é válida e obtém a linha e coluna correspondentes
            if (verificarEscolha(tabuleiro, escolha, linha, coluna)) {
                break; // Sai do loop se a escolha for válida
            }
        }

        // Atualiza o tabuleiro com a jogada do jogador atual
        tabuleiro[linha][coluna] = jogadorAtual;

        // Verifica se a jogada resultou em uma vitória
        if (verificarSeHouveVitoria(tabuleiro, jogadorAtual)) {
            vitoria = true; // Marca que houve uma vitória
            break; // Sai do loop principal porque o jogo terminou
        }

        // Alterna para o próximo jogador
        jogadorAtual = (jogadorAtual == jogadorX) ? jogadorO : jogadorX;

        // Limpa a tela para o próximo turno
        system("cls");
    }

    // Imprime o tabuleiro final
    printarTabuleiro(tabuleiro);

    // Verifica se o jogo terminou em empate
    if (!vitoria) {
        cout << "O jogo empatou." << endl;
    }

    return 0;
}

// Função para imprimir o tabuleiro
void printarTabuleiro(char tabuleiro[3][3]) {
    cout << "\t\t\t   |   |   " << endl;
    cout << "\t\t\t " << tabuleiro[0][0] << " | " << tabuleiro[0][1] << " | " << tabuleiro[0][2] << endl;
    cout << "\t\t\t___|___|___" << endl;
    cout << "\t\t\t   |   |   " << endl;
    cout << "\t\t\t " << tabuleiro[1][0] << " | " << tabuleiro[1][1] << " | " << tabuleiro[1][2] << endl;
    cout << "\t\t\t___|___|___" << endl;
    cout << "\t\t\t   |   |   " << endl;
    cout << "\t\t\t " << tabuleiro[2][0] << " | " << tabuleiro[2][1] << " | " << tabuleiro[2][2] << endl;
    cout << "\t\t\t   |   |   " << endl;
}

// Função para obter a escolha do jogador
void getEscolha(int& escolha) {
    cout << "\nDigite um numero de 1 a 9 para escolher o espaco: ";
    cin >> escolha;
}

// Função para verificar se a escolha é válida e obter a linha e coluna correspondentes
bool verificarEscolha(char tabuleiro[3][3], int escolha, int& linha, int& coluna) {
    // Converte a escolha em linha e coluna do tabuleiro
    switch (escolha) {
        case 1: linha = 0; coluna = 0; break;
        case 2: linha = 0; coluna = 1; break;
        case 3: linha = 0; coluna = 2; break;
        case 4: linha = 1; coluna = 0; break;
        case 5: linha = 1; coluna = 1; break;
        case 6: linha = 1; coluna = 2; break;
        case 7: linha = 2; coluna = 0; break;
        case 8: linha = 2; coluna = 1; break;
        case 9: linha = 2; coluna = 2; break;
        default:
            cout << "Escolha inválida." << endl;
            return false; // Retorna false se a escolha for inválida
    }
    // Verifica se o espaço escolhido já está ocupado
    if (tabuleiro[linha][coluna] != ' ') {
        cout << "Você não pode colocar nesse espaço." << endl;
        return false; // Retorna false se o espaço já estiver ocupado
    }
    return true; // Retorna true se a escolha for válida
}

// Função para verificar se houve uma vitória
bool verificarSeHouveVitoria(char tabuleiro[3][3], char jogadorAtual) {
    // Verifica linhas e colunas para uma condição de vitória
    for (int i = 0; i < 3; i++) {
        if ((tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][0] == tabuleiro[i][2] && tabuleiro[i][0] != ' ') ||
            (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[0][i] == tabuleiro[2][i] && tabuleiro[0][i] != ' ')) {
            cout << "Jogador " << jogadorAtual << " venceu o jogo!" << endl;
            return true; // Retorna true se houver uma condição de vitória
        }
    }
    // Verifica as diagonais para uma condição de vitória
    if ((tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[0][0] == tabuleiro[2][2] && tabuleiro[0][0] != ' ') ||
        (tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[0][2] == tabuleiro[2][0] && tabuleiro[0][2] != ' ')) {
        cout << "Jogador " << jogadorAtual << " venceu o jogo!" << endl;
        return true; // Retorna true se houver uma condição de vitória
    }
    return false; // Retorna false se não houver condição de vitória
}
