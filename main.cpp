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

using namespace std;

// Variáveis globais
char tabuleiro[3][3];
const char JOGADOR1 = 'X';
const char JOGADOR2 = 'O';
const char COMPUTADOR = 'O';

// Prototipo de funções, prototipo de funções é uma declaração antecipada de uma função, informando ao compilador sobre a existência da função.
//() definem o paramentro da funcao. O () vazio indica que a função não recebe parâmetros.
void resetTabuleiro();//reseta o tabuleiro.
void printTabuleiro();//exibe o tabuleiro.
int checarEspacosLivres();//checa os espaços livres no tabuleiro.
void movimentoJogador();//movimento do jogador.
void movimentoComputador();//movimento do computador.
char checarVencedor();//checa o vencedor.
void printVencedor(char);//exibe o vencedor.
void movimentoJogadorVsJogador(int jogadorAtual);//movimento do jogador vs jogador.
void printarTabuleiro(char tabuleiro[3][3]);//exibe o tabuleiro.
void getEscolha(int& escolha);//utiliza a escolha do jogador.
bool verificarEscolha(char tabuleiro[3][3], int escolha, int& linha, int& coluna);//verifica a escolha do jogador.
bool verificarSeHouveVitoria(char tabuleiro[3][3], char jogadorAtual);//verifica se houve vitoria.

int main() {

    //modo de jogo que sera escolhido.
    int modoJogo;
    cout << "Escolha o modo de jogo:\n1. Jogador vs Computador\n2. Jogador vs Jogador\n";
    cin >> modoJogo;

    //char é um tipo de dado que armazena um caractere.
    char vencedor = ' ';//armazena quem sera o vencedor.
    char jogarNovamente;//armazena se o jogador deseja jogar novamente.

    do {
        vencedor = ' ';
        jogarNovamente = ' ';
        resetTabuleiro();

        // Jogador vs Computador
        if (modoJogo == 1) {

            // loop pricipal do jogo, (!=) significa diferente.
            while (vencedor == ' ' && checarEspacosLivres() != 0) {
                printTabuleiro();
                movimentoJogador();
                vencedor = checarVencedor();
                if (vencedor != ' ' || checarEspacosLivres() == 0) {
                    
                    //se o vencedor for diferente de vazio ou se não houver espaços livres, o loop é quebrado.
                    break;
                }
                movimentoComputador();//movimento do computador.
                vencedor = checarVencedor();//checa o vencedor.
            }
        } 
        // Jogador vs Jogador
        else {
            int jogadorAtual = JOGADOR1; // Jogador 1 começa
            for (int i = 0; i < 9; i++) {
                cout << "\n\t=============== Jogo da Velha ===============\n" << endl;
                printarTabuleiro(tabuleiro);
                cout << "O jogador atual eh: " << (jogadorAtual == JOGADOR1 ? 'X' : 'O') << endl;
                while (true) {
                    int escolha;//escolha do jogador.
                    getEscolha(escolha);
                    int linha, coluna;
                    if (verificarEscolha(tabuleiro, escolha, linha, coluna)) {
                        tabuleiro[linha][coluna] = jogadorAtual;
                        break;
                    }
                }
                // Verificar se houve vitoria, se sim, o jogo acaba.
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

        //toupper() é uma função que converte caracteres minúsculos em maiúsculos, remove a necessidade de utilizar bool.
        cout << "\nDeseja jogar novamente? (S/N): ";
        cin >> jogarNovamente;
        jogarNovamente = toupper(jogarNovamente);

    } while (jogarNovamente == 'S');

    cout << "Obrigado por jogar!" << endl;

    return 0;
}

//toda vez que a funcao for utilizada, ela ira limpar o tabuleiro.
void resetTabuleiro() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tabuleiro[i][j] = ' ';
        }
    }
}

//funcao responsavel por exibir o tabuleiro.
void printTabuleiro() {
    system("cls");//limpa a tela.
    cout<<"\n\t=============== Jogo da Velha ===============\n"<<endl;
    cout << " " << tabuleiro[0][0] << " | " << tabuleiro[0][1] << " | " << tabuleiro[0][2] << " ";
    cout << "\n---|---|---\n";
    cout << " " << tabuleiro[1][0] << " | " << tabuleiro[1][1] << " | " << tabuleiro[1][2] << " ";
    cout << "\n---|---|---\n";
    cout << " " << tabuleiro[2][0] << " | " << tabuleiro[2][1] << " | " << tabuleiro[2][2] << " ";
    cout << "\n";
}

int checarEspacosLivres() {

    //numero total de espacos livres.
    int espacosLivres = 9;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tabuleiro[i][j] != ' ') {

                //caso a casa do tabuleiro seja diferente de vazio, reduz o nome de casas livres.
                espacosLivres--;
            }
        }
    }
    return espacosLivres;
}

void movimentoJogador() {
    int x, y;
    do {
        cout << "Insira uma Linha (1-3): ";
        cin >> x;
        //x-- é a mesma coisa que x = x - 1, esta sendo utilizado para que o jogador insira a linha de 1 a 3, mas o vetor começa de 0 a 2.
        x--;
        cout << "Insira uma Coluna (1-3): ";
        cin >> y;
        //y-- é a mesma coisa que y = y - 1, esta sendo utilizado para que o jogador insira a coluna de 1 a 3, mas o vetor começa de 0 a 2.
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

    //escolhe um valor aleatorio para x e y.
    srand(time(0));
    int x, y;
    if (checarEspacosLivres() > 0) {
        do {

            //(%3) gera um numero aleatorio entre 0 e 2.
            x = rand() % 3;
            y = rand() % 3;
        } while (tabuleiro[x][y] != ' ');
        tabuleiro[x][y] = COMPUTADOR;
    } else {

        //em caso de falta de movimentos, o jogo acaba.
        printVencedor(' ');
    }
}

char checarVencedor() {

    //checagem de linha.
    for (int i = 0; i < 3; i++) {

        //checa se as linhas sao iguais.
        if (tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][0] == tabuleiro[i][2]) {
            return tabuleiro[i][0];
        }
    }

    //checagem de coluna.
    for (int i = 0; i < 3; i++) {

        //checa se as colunas sao iguais.
        if (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[0][i] == tabuleiro[2][i]) {
            return tabuleiro[0][i];
        }
    }

    //checagem de diagonais.
    if (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[0][0] == tabuleiro[2][2]) {

        //retorna 0,0 porque a diagonal começa no canto superior esquerdo.
        return tabuleiro[0][0];
    }
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
void printarTabuleiro(char tabuleiro[3][3]) {
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
    cin >> escolha;
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
            cout << "Escolha inválida." << endl;
            return false;
    }
    if (tabuleiro[linha][coluna] != ' ') {

        //posicao ocupada caso o jogador escolha uma posicao que ja foi preenchida.
        cout << "Você não pode colocar nesse espaço." << endl;
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
