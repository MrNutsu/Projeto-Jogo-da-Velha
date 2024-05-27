/* 24-05-2024
Início do Projeto - Jogo da Velha

- alterações no código dia 27-05-2024 (Joao Ravache)
     - modo de jogo: 1 jogador
*/

#include <iostream> //biblioteca para usar cout e cin.
#include <string> //bibloteca para usar string, string é um tipo de dado que armazena uma sequência de caracteres.
#include <cstdlib> //biblioteca para usar system("cls") e system("pause").
#include <ctime> //biblioteca para usar time(0) e srand(time(0)), time(0) e srand(time(0)) são funções que geram números aleatórios.
#include <cctype> //biblioteca para usar toupper(), toupper() é uma função que converte caracteres minúsculos em maiúsculos.

using namespace std; 

char board[3][3];
const char Jogador = 'X';// Constante que representa o jogador.
const char Computador = 'O';// Constante que representa o computador.

void resetBoard();// Função que reseta o tabuleiro.
void printBoard();// Função que imprime o tabuleiro.
int checarespacoslivres();// Função que verifica se há espaços livres no tabuleiro.
void movimentojogador();// Função que permite ao jogador fazer uma jogada.
void movimentopc();// Função que permite ao computador fazer uma jogada.
char checarVencedor();// Função que verifica se há um vencedor.
void printWinner(char);// Função que imprime o vencedor.

int main(){

    char vencedor = ' ';
    char response = ' ';

    // Loop principal do jogo
    do
    {
        vencedor = ' ';
        response = ' ';
        resetBoard();

        while (vencedor == ' ' && checarespacoslivres() != 0)
        {
            printBoard();

            movimentojogador();
            vencedor = checarVencedor();
            if (vencedor != ' ' || checarespacoslivres() == 0)
            {
                break;
            }

            movimentopc();
            vencedor = checarVencedor();
            if (vencedor != ' ' || checarespacoslivres() == 0)
            {
                break;
            }
        }

        printBoard();
        printWinner(vencedor);

        cout << "\nGostaria de jogar novamente? (S/N): ";// \n quebra de linha
        cin >> response;
        response = toupper(response);//toupper() é uma função que converte caracteres minúsculos em maiúsculos.
    } while (response == 'S');

    cout << "Obrigado por Jogar!";

    return 0;
}

void resetBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}

//exibicao do tabuleiro
void printBoard()
{
    cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << " ";
    cout << "\n---|---|---\n";
    cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << " ";
    cout << "\n---|---|---\n";
    cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << " ";
    cout << "\n";
}

// Verifica se ha espacos livres no tabuleiro
int checarespacoslivres()
{
    int espacolivre = 9;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != ' ')
            {
                espacolivre--;
            }
        }
    }
    return espacolivre;
}

/* Função que permite ao jogador fazer uma jogada.
Faz isso verificando se a posição escolhida está vazia, e depois atribuindo a posição escolhida pelo jogador ao tabuleiro. 
*/
void movimentojogador()
{
    int x;
    int y;

    do
    {
        cout << "Insira fileira #(1-3): ";
        cin >> x;
        x--;
        cout << "Enter coluna #(1-3): ";
        cin >> y;
        y--;

        if (board[x][y] != ' ')
        {
            cout << "Movimento Invalido!\n";
        }
        else
        {
            board[x][y] = Jogador;
            break;
        }
    } while (board[x][y] != ' ');
}

/* Função que permite o pc fazer uma jogada.
Faz isso verificando se a posição escolhida está vazia, e depois atribuindo a posição escolhida pelo pc ao tabuleiro. 
*/
void movimentopc()
{
    srand(time(0));
    int x;
    int y;

    if (checarespacoslivres() > 0)
    {
        do
        {
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');

        board[x][y] = Computador;
    }

}