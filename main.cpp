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

//variaveis globais
char tabuleiro[3][3]; //matriz 3x3 que representa o tabuleiro do jogo da velha.
const char JOGADOR = 'X'; //connstante que representa o jogador.
const char COMPUTADOR = 'O'; //constante que representa o computador.

//prototipo de funções
//() definem o paramentro da funcao. O () vazio indica que a função não recebe parâmetros.
void resetTabuleito(); //reseta o tabuleiro.
void printTabuleiro(); //exibe o tabuleiro.
int checarespacoslivres(); //verifica se ha espaços livres no tabuleiro.
void movimentoJogador(); //movimento do jogador.
void movimentoComputador(); //movimneto do computador;
char ChecarVencedor(); //verifica se ha vencedor.
void printVencedor(char); //exibe o vencedor.

int main(){

    //char é um tipo de dado que armazena um caractere.
    char vencedor = ' '; //armazena quem sera o vencedor.
    char jogarNovamente; //se o jogador desejar jogar novamente.

    do{

        vencedor = ' ';
        jogarNovamente = ' ';
        resetTabuleito();

        // loop pricipal do jogo, (!=) significa diferente.
        while(vencedor == ' ' && checarespacoslivres() !=0){

            printTabuleiro();

            movimentoJogador();
            vencedor = ChecarVencedor();
            if(vencedor !=' ' || checarespacoslivres() ==0){

                //forca parada.
                break;
            }

            movimentoComputador();
            vencedor = ChecarVencedor();
            if(vencedor !=' ' || checarespacoslivres() ==0){

                //forca parada.
                break;
            }
        }

        printTabuleiro();
        printVencedor(vencedor);

        cout << "\nDeseja jogar novamente? (S/N): ";
        cin>>jogarNovamente;
        //toupper() converte caracteres minúsculos em maiúsculos.
        jogarNovamente = toupper(jogarNovamente);

    } while(jogarNovamente == 'S');

    cout<<"Obrigado por jogar!"<<endl;

    return 0;
}

//toda vez que a funcao for utilizada, ela ira limpar o tabuleiro.
void resetTabuleito(){

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            tabuleiro[i][j] = ' ';
        }
    }
}

//funcao rewsponsavel por exibir o tabuleiro.
void printTabuleiro(){

     system("cls"); //limpa a tela do console.
     /*printf exibe uma mensagem na tela.
     %c possui a funcao de exibir um caractere especifico.
     \n faz quebra de linha.(uma nova linha)
     */ 
    cout << " " << tabuleiro[0][0] << " | " << tabuleiro[0][1] << " | " << tabuleiro[0][2] << " ";
    cout << "\n---|---|---\n";
    cout << " " << tabuleiro[1][0] << " | " << tabuleiro[1][1] << " | " << tabuleiro[1][2] << " ";
    cout << "\n---|---|---\n";
    cout << " " << tabuleiro[2][0] << " | " << tabuleiro[2][1] << " | " << tabuleiro[2][2] << " ";
    cout << "\n";
}

int checarespacoslivres(){

    //numero total de casas do tabuleiro.
    int EspacosLivres = 9;

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(tabuleiro[i][j] !=' '){
                
                //caso a casa do tabuleiro seja diferente de vazio, reduz o numero de casas livres.
                EspacosLivres--;
            }
        }
    }
    return EspacosLivres;
}

void movimentoJogador(){

    int x, y;

    do{
        //cout exibe uma mensagem na tela.
        cout << "Insira uma Linha (1-3): ";
        //cin recebe um valor digitado pelo usuario.
        cin >> x;
        x--;

        cout << "Insira uma Coluna (1-3): ";
        cin >> y;
        y--;

        if(tabuleiro[x][y] !=' '){

            cout<<"Movimento Invalido, tente novamente"<<endl;
        }else{
            tabuleiro[x][y] = JOGADOR;
            //brak interrompe a execução do loop.
            break;
        }
    }while(tabuleiro[x][y] != ' ');
}

void movimentoComputador(){

    //cria um numero aleatorio.
    srand(time(0));
    int x, y;

    //caso tenha espaco livre
    if(checarespacoslivres() >0){

        do{

            //(%3) gera um numero aleatorio entre 0 e 2.
            x=rand()%3;
            y=rand()%3;
        } while (tabuleiro[x][y] !=' ');

        tabuleiro[x][y] = COMPUTADOR;
    }else{

        //espaço livre e empate.
        printVencedor(' ');
    }

}

char ChecarVencedor(){

    //checagem de linhas
    for(int i=0; i<3; i++){
        
        //checar se a linhas sao iguais.
        if(tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][0] == tabuleiro[i][2]){

            return tabuleiro[i][0];
        }
    }

    //checagem de colunas
    for(int i=0; i<3; i++){

        //checar se as colunas sao iguais.
        if(tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[0][i] == tabuleiro[2][i]){

            return tabuleiro[0][i];
        }
    }

    //checagem de diagonais.
    if(tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[0][0] == tabuleiro[2][2]){

            //retorna 0,0 porque a diagonal começa no canto superior esquerdo.
            return tabuleiro[0][0];
        }
    if(tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[0][2] == tabuleiro[2][0]){

            //retorna 0,2 porque a diagonal começa no canto superior direito.
            return tabuleiro[0][2];
        }

    return ' ';
}

void printVencedor(char vencedor){

    if(vencedor == JOGADOR){
        cout<<"VOCE VENCEU!";
    }
    else if(vencedor == COMPUTADOR){
        cout<<"VOCE PERDEU!";
    }
    else{
        cout<<"DEU VELHA!";
    }
}
