#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 #ifdef __linux__
    #include <unistd.h>
#elif __WIN32
    #include <Windows.h>
#else

#endif

#define limite = 39

typedef struct peao{
    int pos;
    int posTab[2];
    char simb;
    char direc;
    int sentido;
}Peao;

void mostrarTabuleiro();
void mostraMenu();
void definePeao(Peao *peao, int pos, int posTab[2], char simb, char direct);
void moverPeao(Peao *peao, int quantCasas);
void iniciar();
void setJogadores();
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

Peao peaoJ1[4];
Peao peaoJ2[4];
Peao peaoJ3[4];
Peao peaoJ4[4];
int quantJogadores;

int main(){
    int cont = 0;
    for (int i = 0; i < 11; i++){
        for (int j = 0; j < 11; j++){
            if(tabuleiro[i][j] == 'o'){
                cont++;
            }
        }
    }

    printf("Total de casas: %d \n", cont);
    
    //mostraMenu(0);
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
        iniciar();
        break;
    default:
        printf("Opção Inválida\n");
        break;
    }
}

void iniciar(){
    setJogadores();
    lancarDado();    
}

void setJogadores(){
    int coord[2];
    switch (quantJogadores){
    case 2:
        //Define posição inicial dos peões do jogador 1
        tabuleiro[8][1] = '1';
        coord[1] = 8;
        coord[2] = 1;
        definePeao(&peaoJ1[0], 0, coord, '1', '-');

        tabuleiro[8][2] = '1';
        coord[1] = 8;
        coord[2] = 2;
        definePeao(&peaoJ1[1], 0, coord, '1', '-');

        tabuleiro[9][1] = '1';
        coord[1] = 9;
        coord[2] = 1;
        definePeao(&peaoJ1[2], 0, coord, '1', '-');

        tabuleiro[9][2] = '1';
        coord[1] = 9;
        coord[2] = 2;
        definePeao(&peaoJ1[3], 0, coord, '1', '-');

        //Define posição inicial dos peões do jogador 2

        tabuleiro[1][8] = '2';
        coord[1] = 1;
        coord[2] = 8;
        definePeao(&peaoJ1[0], 0, coord, '2', '-');

        tabuleiro[1][9] = '2';
        coord[1] = 1;
        coord[2] = 9;
        definePeao(&peaoJ1[1], 0, coord, '2', '-');

        tabuleiro[2][8] = '2';
        coord[1] = 2;
        coord[2] = 8;
        definePeao(&peaoJ1[2], 0, coord, '2', '-');

        tabuleiro[2][9] = '2';
        coord[1] = 2;
        coord[2] = 9;
        definePeao(&peaoJ1[3], 0, coord, '2', '-');
        
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
}

void moverPeao(Peao *peao, int quantCasas){
    for (int i = 0; i < quantCasas; i++){

        peao->pos++;
    }
    
    
}

void hvDirect(Peao *peao){
    if (peao->posTab[0] == 0 && peao->posTab[1] == 4){
        peao->direc = 'h';
        peao->sentido = 1;
    }else if(peao->posTab[0] == 0 && peao->posTab[1] == 6){
        peao->direc = 'v';
        peao->sentido = 1;
    }else if(peao->posTab[0] == 4 && peao->posTab[1] == 6){
        peao->direc = 'h';
        peao->sentido = 1;
    }else if(peao->posTab[0] == 4 && peao->posTab[1] == 10){
        peao->direc = 'v';
        peao->sentido = 1;
    }else if(peao->posTab[0] == 6 && peao->posTab[1] == 10){
        peao->direc = 'h';
        peao->sentido = -1;
    }else if(peao->posTab[0] == 6 && peao->posTab[1] == 6){
        peao->direc = 'v';
        peao->sentido = 1;
    }else if(peao->posTab[0] == 10 && peao->posTab[1] == 6){
        peao->direc = 'h';
        peao->sentido = -1;
    }else if(peao->posTab[0] == 10 && peao->posTab[1] == 4){
        peao->direc = 'v';
        peao->sentido = -1;
    }else if(peao->posTab[0] == 6 && peao->posTab[1] == 4){
        peao->direc = 'h';
        peao->sentido = -1;
    }else if(peao->posTab[0] == 6 && peao->posTab[1] == 0){
        peao->direc = 'v';
        peao->sentido = -1;
    }else if(peao->posTab[0] == 4 && peao->posTab[1] == 0){
        peao->direc = 'h';
        peao->sentido = 1;
    }else if(peao->posTab[0] == 4 && peao->posTab[1] == 0){
        peao->direc = 'v';
        peao->sentido = -1;
    }else{
        //A direção se mantém
    }
}

void definePeao(Peao *peao, int pos, int posTab[2], char simb, char direct){
    peao->pos = pos;
    peao->posTab[1] = posTab[1];
    peao->posTab[2] = posTab[2];
    peao->simb = simb;
    peao->direc = direct;
}

int lancarDado(){
    char c;
    printf("Pressione enter para rolar o dado");
    scanf("%c", &c);
    int num = rand() % 7;
    return num;
}