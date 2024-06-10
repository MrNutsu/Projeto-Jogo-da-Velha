/* 24-05-2024
Início do Projeto - Jogo da Velha

- alterações no código dia 27-05-2024 (Joao Ravache)
     - modo de jogo: 1 jogador

- alteracoes no codigo dia 24-05-2024 (Amanda Zotte)
	 - modo de 2 jogadores

- alterações no código dia 04-06-2024 (Todos os membros)
     - integracao do modo de jogo 2 jogadores

- alterações no código dia 06-06-2024 (Joao Ravache)
     - finalização do projeto + correção de bugs
*/

#include <iostream> //biblioteca para usar cout e cin.
#include <string> //bibloteca para usar string, string é um tipo de dado que armazena uma sequência de caracteres.
#include <cstdlib> //biblioteca para usar system("cls") e system("pause").
#include <ctime> //biblioteca para usar time(0) e srand(time(0)), time(0) e srand(time(0)) são funções que geram números aleatórios.
#include <cctype> //biblioteca para usar toupper(), toupper() é uma função que converte caracteres minúsculos em maiúsculos.
#include <limits> //biblioteca que contém constantes que representam os limites de variáveis de tipos numéricos.

using namespace std;

// Variáveis globais
//const define uma constante, ou seja, um valor que não pode ser alterado.
char tabuleiro[3][3];
const char JOGADOR1 = 'X';
const char JOGADOR2 = 'O';
const char COMPUTADOR = 'O';

// Prototipo de funções, prototipo de funções é uma declaração antecipada de uma função, informando ao compilador sobre a existência da função.
//() definem o paramentro da funcao. O () vazio indica que a função não recebe parâmetros.
void resetTabuleiro();//reseta o tabuleiro
void printTabuleiro();//imprime o tabuleiro
int checarEspacosLivres();//checa os espaços livres
void movimentoJogador();//movimento do jogador
void movimentoComputador();//movimento do computador
char checarVencedor();//checa o vencedor
void printVencedor(char);//exibe o vencedor
void movimentoJogadorVsJogador(int jogadorAtual);//movimento do jogador vs jogador
void exibirTabuleiro(char tabuleiro[3][3]);//exibe o tabuleiro
void getEscolha(int& escolha);//pega a escolha do jogador
bool verificarEscolha(char tabuleiro[3][3], int escolha, int& linha, int& coluna);//verifica a escolha do jogador
bool verificarSeHouveVitoria(char tabuleiro[3][3], char jogadorAtual);//verifica se houve vitoria
bool isNumber(const string& s);//verifica se é um número

int main() {

    //modo de jogo que sera escolhido
    int modoJogo;
    cout << "Escolha o modo de jogo:\n1. Jogador vs Computador\n2. Jogador vs Jogador\n";
    while (!(cin >> modoJogo) || (modoJogo != 1 && modoJogo != 2)) {
        cout << "Entrada inválida. Por favor, insira 1 ou 2: ";
        //cin.clear() limpa o estado de erro do fluxo de entrada, fluxo de entrada é o fluxo de dados que entra no programa.
        cin.clear();
        //cin.ignore() extrai e descarta caracteres do buffer de entrada
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    //char e um tipo de dado que armazzena um caractere
    char vencedor = ' ';
    char jogarNovamente;

    //do while é uma estrutura de repetição que executa um bloco de código enquanto a condição for verdadeira.
    do {
        vencedor = ' ';
        jogarNovamente = ' ';
        resetTabuleiro();

        //jogador vs computador
        if (modoJogo == 1) {

            //loop principal do jogo, (!=) significa diferente
            while (vencedor == ' ' && checarEspacosLivres() != 0) {
                printTabuleiro();
                movimentoJogador();
                vencedor = checarVencedor();
                if (vencedor != ' ' || checarEspacosLivres() == 0) {

                    //se hover vencedor ou der velha, o loop é quebrado
                    break;
                }
                movimentoComputador();//movimento do computador
                vencedor = checarVencedor();//checa o vencedor
            }
        } 
        //jogador vs jogador
        else {
            int jogadorAtual = JOGADOR1;//jogador 1 começa
            for (int i = 0; i < 9; i++) {
                cout << "\n\t=============== Jogo da Velha ===============\n" << endl;
                exibirTabuleiro(tabuleiro);
                cout << "O jogador atual eh: " << (jogadorAtual == JOGADOR1 ? 'X' : 'O') << endl;
                while (true) {
                    int escolha;//escolha do jogador
                    getEscolha(escolha);
                    int linha, coluna;
                    if (verificarEscolha(tabuleiro, escolha, linha, coluna)) {
                        tabuleiro[linha][coluna] = jogadorAtual;
                        break;
                    }
                }
                //verifica se houve vitoria, se sim, o loop é quebrado
                if (verificarSeHouveVitoria(tabuleiro, jogadorAtual)) {
                    vencedor = jogadorAtual;
                    break;
                }
                jogadorAtual = (jogadorAtual == JOGADOR1) ? JOGADOR2 : JOGADOR1;
                system("cls");
            }
        }

        printTabuleiro();
        printVencedor(vencedor);

        cout << "\nDeseja jogar novamente? (S/N): ";
        while (!(cin >> jogarNovamente) || (toupper(jogarNovamente) != 'S' && toupper(jogarNovamente) != 'N')) {
            cout << "Entrada inválida. Por favor, insira S ou N: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        //toupper() é uma função que converte caracteres minúsculos em maiúsculos., remove a necessidade de utilizar bool
        jogarNovamente = toupper(jogarNovamente);

    } while (jogarNovamente == 'S');

    cout << "Obrigado por jogar!" << endl;

    return 0;
}

//toda vez que for utilizada, ela ira limpar o tabuleiro
void resetTabuleiro() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tabuleiro[i][j] = ' ';
        }
    }
}

//funcao que exibe o tabuleiro
void printTabuleiro() {
    system("cls");//limpa a tela
    cout << "\n\t=============== Jogo da Velha ===============\n" << endl;
    cout << " " << tabuleiro[0][0] << " | " << tabuleiro[0][1] << " | " << tabuleiro[0][2] << " ";
    cout << "\n---|---|---\n";
    cout << " " << tabuleiro[1][0] << " | " << tabuleiro[1][1] << " | " << tabuleiro[1][2] << " ";
    cout << "\n---|---|---\n";
    cout << " " << tabuleiro[2][0] << " | " << tabuleiro[2][1] << " | " << tabuleiro[2][2] << " ";
    cout << "\n";
}

int checarEspacosLivres() {

    //numero total de espacos livres, faz a leitura antes e depois de cada movimento
    int espacosLivres = 9;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tabuleiro[i][j] != ' ') {

                //caso a posicao nao esteja vazia, reduz o numero de espacos livres
                espacosLivres--;
            }
        }
    }
    return espacosLivres;
}

//funcao que faz o movimento do jogador(jogadorvscomputador)
void movimentoJogador() {
    int x, y;
    do {
        cout << "Insira uma Linha (1-3): ";
        while (!(cin >> x) || x < 1 || x > 3) {
            cout << "Valor invalido. Por favor, insira um número entre 1 e 3: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        //reduz 1 para que o jogador insira a linha de 1 a 3 e nao de 0 a 2
        x--;

        cout << "Insira uma Coluna (1-3): ";
        while (!(cin >> y) || y < 1 || y > 3) {
            cout << "Valor invalido. Por favor, insira um número entre 1 a 3: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        //reduz 1 para que o jogador insira a coluna de 1 a 3 e nao de 0 a 2
        y--;

        if (tabuleiro[x][y] != ' ') {
            cout << "Movimento Invalido, tente novamente" << endl;
        } else {
            tabuleiro[x][y] = JOGADOR1;
            break;
        }
    } while (tabuleiro[x][y] != ' ');
}

void movimentoComputador() {

    //escolhe um valor aleatorio para x e y
    srand(time(0));
    int x, y;
    if (checarEspacosLivres() > 0) {
        do {

            //rand()$3 gera um numero aleatorio de 0 a 2
            x = rand() % 3;
            y = rand() % 3;
        } while (tabuleiro[x][y] != ' ');
        tabuleiro[x][y] = COMPUTADOR;
    } else {

        //em caso de falta de movimentos, o jogo acaba
        printVencedor(' ');
    }
}

char checarVencedor() {
    
    //checagem de linhas
    for (int i = 0; i < 3; i++) {

        //checa se a linha i é igual
        if (tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][0] == tabuleiro[i][2]) {
            //retorna o valor da linha i
            return tabuleiro[i][0];
        }
    }

    //checagem de colunas
    for (int i = 0; i < 3; i++) {

        //checa se a coluna i é igual
        if (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[0][i] == tabuleiro[2][i]) {
            //retorna o valor da coluna i
            return tabuleiro[0][i];
        }
    }

    //checagem de diagonais.
    //diagonal esquerda.
    if (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[0][0] == tabuleiro[2][2]) {
        //retorna 0,0 porque a diagonal começa no canto superior esquerdo.
        return tabuleiro[0][0];
    }
    //diagonal direita.
    if (tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[0][2] == tabuleiro[2][0]) {
        //retorna 0,2 porque a diagonal começa no canto superior direito.
        return tabuleiro[0][2];
    }
    return ' ';
}

//exibicao de mensagem de final de jogo - 1 jogador.
void printVencedor(char vencedor) {
    if (vencedor == JOGADOR1) {
        cout << "VOCE VENCEU!";
    } else if (vencedor == COMPUTADOR) {
        cout << "VOCE PERDEU!";
    } else if (vencedor == JOGADOR2) {
        cout << "JOGADOR 2 VENCEU!";
    } else {
        cout << "DEU VELHA!";
    }
}

//movimento do jogador vs jogador.
void exibirTabuleiro(char tabuleiro[3][3]) {
    cout << " " << tabuleiro[0][0] << " | " << tabuleiro[0][1] << " | " << tabuleiro[0][2] << " ";
    cout << "\n---|---|---\n";
    cout << " " << tabuleiro[1][0] << " | " << tabuleiro[1][1] << " | " << tabuleiro[1][2] << " ";
    cout << "\n---|---|---\n";
    cout << " " << tabuleiro[2][0] << " | " << tabuleiro[2][1] << " | " << tabuleiro[2][2] << " ";
    cout << "\n";
}

//escolha de posicionamento do jogador.
void getEscolha(int& escolha) {
    cout << "\nDigite um numero de 1 a 9 para escolher o espaco: ";
    while (!(cin >> escolha) || escolha < 1 || escolha > 9) {
        cout << "Valor invalido. Por favor, insira um número entre 1 e 9: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

//verifica se a escolha do jogador é valida.
bool verificarEscolha(char tabuleiro[3][3], int escolha, int& linha, int& coluna) {
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

            // posicao invalida caso o jogador escolha um numero diferente de 1 a 9.
            cout << "Escolha invalida." << endl;
            return false;
    }
    if (tabuleiro[linha][coluna] != ' ') {

        //posicao ocupada caso o jogador escolha uma posicao que ja foi preenchida.
        cout << "Espaco ja Ocupado." << endl;
        return false;
    }
    return true;
}

//verifica se houve vitoria.
bool verificarSeHouveVitoria(char tabuleiro[3][3], char jogadorAtual) {
    for (int i = 0; i < 3; i++) {

        //verifica se houve vitoria na linha ou na coluna.
        if ((tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][0] == tabuleiro[i][2] && tabuleiro[i][0] != ' ') ||
            (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[0][i] == tabuleiro[2][i] && tabuleiro[0][i] != ' ')) {

            //exibe o vencedor.
            cout << "Jogador " << jogadorAtual << " venceu o jogo!" << endl;
            return true;
        }
    }

    //verifica se houve vitoria na diagonal.
    if ((tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[0][0] == tabuleiro[2][2] && tabuleiro[0][0] != ' ') ||
        (tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[0][2] == tabuleiro[2][0] && tabuleiro[0][2] != ' ')) {
        
        //exibe o vencedor.
        cout << "Jogador " << jogadorAtual << " venceu o jogo!" << endl;
        return true;
    }
    return false;
}