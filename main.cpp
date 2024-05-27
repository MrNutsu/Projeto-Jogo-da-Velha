/* 24-05-2024
Início do Projeto - Jogo da Velha
*/

//   atualizacao 25/05/2024 

//1°versao do "player 1 vs player 2". 
//bem feinha mas vou melhorar ate terca-feira!!


#include <iostream>
#include <string>
using namespace std;

int main (){
    char board [3][3] = {{ ' ', ' ',' '}, {' ', ' ',' ' }, {' ', ' ',' ' }};

//declaracao de variaveis
    const char playerX = 'X';
    const char playerO = 'O';
    char currentPlayer = playerX;
    int choice ;
    int row;
    int column;
    bool win = false;

//printando tabuleiro
    for (int i = 0; i < 9; i++){
    cout << "   |   |   " << endl;
    cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "___|___|___" << endl;
    cout << "   |   |   " << endl;
    cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "___|___|___" << endl;
    cout << "   |   |   " << endl;
    cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
    cout << "   |   |   " << endl;
    
//demonstrando jogador atual
    cout<<"The current player is " << currentPlayer << endl;


//escolha do local onde o jogador ira inserir X ou O;
    while(true){
    cout << "Enter a number from 1-9 to choose the space: ";
    cin >> choice;

   

        switch (choice){

            case 1: row = 0; column = 0; break;
            case 2: row = 0; column = 1; break;
            case 3: row = 0; column = 2; break;
            case 4: row = 1; column = 0; break;
            case 5: row = 1; column = 1; break;
            case 6: row = 1; column = 2; break;
            case 7: row = 2; column = 0; break;
            case 8: row = 2; column = 1; break;
            case 9: row = 2; column = 2; break;

            default: 
            cout<<"Invalid choice."<<endl;
            continue;
        
        }

        if ( board [row][column] != ' '){
                cout<<"You can't put on this space." << endl;
            }

        else { break;
        }
        
    }

//setando as lacunas do tabuleiro com a peca do jogador atual 
        board[row][column] = currentPlayer;


// Verificação de vitória nas linhas e colunas, se o jogador atual ganhar, o jogo acaba
        for (int i = 0; i < 3; i++) {
            if ((board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != ' ') ||
                (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != ' ')) {
                cout << "Player " << currentPlayer << " Won the game!" << endl;
                win = true;
                break;
            }
        }

//verificacao de vitorias na diagonais
        if ((board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != ' ') ||
            (board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] != ' ')) {
            cout << "Player " << currentPlayer << " Won the game!" << endl;
            win = true;
        }
//caso as verificacoes acima se tornem true, o jogo acaba
        if (win) {
            break;
        }
//mudando de jogador apos as verificacoes, neh
        currentPlayer = (currentPlayer == playerX) ? playerO : playerX;
        system("cls");

    }
//se todas as verificacoes anteriores nao se tornarem verdadeiras, eh um empate no jogo
        if (!win) {
            cout << "It's a draw." << endl;
        }

    return 0;
}
    
    
            

     





                          