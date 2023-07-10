#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 #ifdef __linux__
    #include <unistd.h>
#elif __WIN32
    #include <Windows.h>
#else

#endif

typedef struct peao{
    int pos;
    int posfin;
    int jogador;
    int ID;
}Peao;

void mostrarTabuleiro();
void mostraMenu();
void definePeao(Peao peao, int ID,int pos, int jogador);
void moverPeao(Peao peao, int quantCasas);
void iniciar(int numJogadores);
int lancarDado();
void limparTela();

char tabuleiro[11][11] = {
    ' ',' ',' ',' ','o','o','o',' ',' ',' ',' ',
    ' ',' ',' ',' ','o','#','o',' ',' ',' ',' ',
    ' ',' ',' ',' ','o','#','o',' ',' ',' ',' ',
    ' ',' ',' ',' ','o','#','o',' ',' ',' ',' ',
    'o','o','o','o','o','#','o','o','o','o','o',
    'o','#','#','#','#',' ','#','#','#','#','o',
    'o','o','o','o','o','#','o','o','o','o','o',
    ' ',' ',' ',' ','o','#','o',' ',' ',' ',' ',
    ' ',' ',' ',' ','o','#','o',' ',' ',' ',' ',
    ' ',' ',' ',' ','o','#','o',' ',' ',' ',' ',
    ' ',' ',' ',' ','o','o','o',' ',' ',' ',' '
};
char regiao[11][11] = {
    ' ',' ',' ',' ','2','2','2',' ',' ',' ',' ',
    ' ',' ',' ',' ','2','2','2',' ',' ',' ',' ',
    ' ',' ',' ',' ','2','2','2',' ',' ',' ',' ',
    ' ',' ',' ',' ','2','2','2',' ',' ',' ',' ',
    '3','3','3','3','o','#','o','4','4','4','4',
    '3','3','3','3','#',' ','#','4','4','4','4',
    '3','3','3','3','o','#','o','4','4','4','4',
    ' ',' ',' ',' ','1','1','1',' ',' ',' ',' ',
    ' ',' ',' ',' ','1','1','1',' ',' ',' ',' ',
    ' ',' ',' ',' ','1','1','1',' ',' ',' ',' ',
    ' ',' ',' ',' ','1','1','1',' ',' ',' ',' '
};

Peao peaoJ1[4];
Peao peaoJ2[4];
Peao peaoJ3[4];
Peao peaoJ4[4];

int main(){
    mostraMenu(0);
    return 0;
}

void limparTela(){
    #ifdef __linux__
        system("clear");
    #elif __WIN32
        system("cls");
    #else

    #endif
}

void mostrarTabuleiro(){
    for(int i = 0; i < 11; i++){
        for(int j = 0; j < 11; j++){
            printf("%3c",tabuleiro[i][j]);
        }
        printf("\n");
    }
}

void mostraMenu(){
    int opc;
    int quantJogadores;
    printf("\n\n\n");
    printf(".##.......##.....##.########...#######.\n");
    printf(".##.......##.....##.##.....##.##.....##\n");
    printf(".##.......##.....##.##.....##.##.....##\n");
    printf(".##.......##.....##.##.....##.##.....##\n");
    printf(".##.......##.....##.##.....##.##.....##\n");
    printf(".##.......##.....##.##.....##.##.....##\n");
    printf(".########..#######..########...#######.\n");
    printf("\n\n\n");


    printf("Escolha uma opção no menu: \n");
    printf("1 - Novo jogo\n");
    printf("0 - Sair\n");
    printf("Sua escolha: ");
    scanf("%d", &opc);
    switch (opc){
    case 1:
        printf("Quantidade de jogadores: ");
        scanf("%d", &quantJogadores);
        limparTela();
        iniciar(quantJogadores);
        break;
    default:
        printf("Opção Inválida\n");
        break;
    }
}

void iniciar(int numJogadores){
    switch (numJogadores){
    case 2:
        //Defini posição inicial dos peões do jogador 1
        tabuleiro[8][1] = '1';
        tabuleiro[8][2] = '1';
        tabuleiro[9][1] = '1';
        tabuleiro[9][2] = '1';

        //Define posição inicial dos peões do jogador 2
        tabuleiro[1][8] = '2';
        tabuleiro[1][9] = '2';
        tabuleiro[2][8] = '2';
        tabuleiro[2][9] = '2';
        
        break;
    case 3:
         //Defini posição inicial dos peões do jogador 1
        tabuleiro[8][1] = '1';
        tabuleiro[8][2] = '1';
        tabuleiro[9][1] = '1';
        tabuleiro[9][2] = '1';

        //Define posição inicial dos peões do jogador 2
        tabuleiro[1][8] = '2';
        tabuleiro[1][9] = '2';
        tabuleiro[2][8] = '2';
        tabuleiro[2][9] = '2';

         //Defini posição inicial dos peões do jogador 3
        tabuleiro[1][1] = '3';
        tabuleiro[1][2] = '3';
        tabuleiro[2][1] = '3';
        tabuleiro[2][2] = '3';
        break;
    case 4:
         //Defini posição inicial dos peões do jogador 1
        tabuleiro[8][1] = '1';
        tabuleiro[8][2] = '1';
        tabuleiro[9][1] = '1';
        tabuleiro[9][2] = '1';

        //Define posição inicial dos peões do jogador 2
        tabuleiro[1][8] = '2';
        tabuleiro[1][9] = '2';
        tabuleiro[2][8] = '2';
        tabuleiro[2][9] = '2';

         //Defini posição inicial dos peões do jogador 3
        tabuleiro[1][1] = '3';
        tabuleiro[1][2] = '3';
        tabuleiro[2][1] = '3';
        tabuleiro[2][2] = '3';

        //Define posição inicial dos peões do jogador 4
        tabuleiro[8][8] = '4';
        tabuleiro[8][9] = '4';
        tabuleiro[9][8] = '4';
        tabuleiro[9][9] = '4';
        break;
    default:
        printf("Não é possível jogar com essa quantidade de jogadores :( \n");
        break;
    }
    mostrarTabuleiro();
}
void moverPeao(Peao peao, int quantCasas){
    peao.pos += quantCasas;
}
void definePeao(Peao peao, int ID, int pos, int jogador){
    peao.ID = ID;
    peao.jogador = jogador;
    peao.pos = pos;
    peao.posfin = 52;
}

int lancarDado(){
    int num = rand() % 7;
    return num;
}