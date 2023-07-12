#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __linux__
    #include <unistd.h>
#elif __WIN32
    #include <Windows.h>
#else

#endif

#define limite 39

typedef struct peao{
    int pos;
    int posTab[2];
    char simb;
    char direc;
    int sentido;
    int ID;
}Peao;

void mostrarTabuleiro();
void mostraMenu();
void definePeao(Peao *peao, int pos, int posTab[2], char simb, char direct, int ID);
void moverPeao(Peao *peao, int quantCasas);
void iniciar();
void setJogadores();
int lancarDado();
void limparTela();
int jogadorIniciado(Peao peao[]);
void tirardeCasa(Peao *peao);
int estaEmCasa(Peao peao);
void hvDirect(Peao *peao);
int verificaQualPeao(Peao *peao);

char tabuleiro[11][11] = {
    ' ',' ',' ',' ','o','o','o',' ',' ',' ',' ',
    ' ',' ',' ',' ','o','#','#',' ',' ',' ',' ',
    ' ',' ',' ',' ','o','#','o',' ',' ',' ',' ',
    ' ',' ',' ',' ','o','#','o',' ',' ',' ',' ',
    'o','#','o','o','o','#','o','o','o','o','o',
    'o','#','#','#','#',' ','#','#','#','#','o',
    'o','o','o','o','o','#','o','o','o','#','o',
    ' ',' ',' ',' ','o','#','o',' ',' ',' ',' ',
    ' ',' ',' ',' ','o','#','o',' ',' ',' ',' ',
    ' ',' ',' ',' ','#','#','o',' ',' ',' ',' ',
    ' ',' ',' ',' ','o','o','o',' ',' ',' ',' '
};

Peao peaoJ1[4];
Peao peaoJ2[4];
Peao peaoJ3[4];
Peao peaoJ4[4];
int quantJogadores;
int playing = 0;
int turno = 0;

int main(){
    mostraMenu();
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
    limparTela();
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
    playing = 1;
    turno = 1;
    while (playing){
        printf("Turno do Jogador %d \n", turno);
        mostrarTabuleiro();
        int dado = lancarDado();
        printf("Resultado: %d \n", dado);
        int peaoMover;
        switch (turno){
            case 1:
                if(jogadorIniciado(peaoJ1) == 4){
                    if(dado == 6){
                        printf("Mover peão");
                        tirardeCasa(peaoJ1);
                    }
                }else{ 
                    if(jogadorIniciado(peaoJ1) > 0 && dado == 6){
                        char escolha;
                        printf("Você tem peões em casa! Deseja tirar um?(s/n)\n");
                        scanf("%c", &escolha);
                        if (escolha == 's'){
                            tirardeCasa(peaoJ1);
                        }else{
                            peaoMover = verificaQualPeao(peaoJ1);
                            moverPeao(&peaoJ1[0], dado);
                        }
                    }else{
                        verificaQualPeao(peaoJ1);
                        moverPeao(&peaoJ1[0], dado);
                    }
                }
                break;
            case 2:
                if(jogadorIniciado(peaoJ2) == 4){
                    if(dado == 6){
                        printf("Mover peão");
                      moverPeao(&peaoJ2[0], 1);
                    }
                }else{
                    
                }
                break;
            case 3:
               
                break;
            case 4:
                
                break;
            default:
                break;
        }
        printf("Pressione Enter para continuar...\n");
        getchar();
        limparTela();
        if(turno == quantJogadores){
            turno = 1;
        }else{
            turno++;
        }
    }   
}

void setJogadores(){
    int coord[2];
    switch (quantJogadores){
    case 2:
        //Define posição inicial dos peões do jogador 1
        tabuleiro[8][1] = '1';
        coord[0] = 8;
        coord[1] = 1;
        definePeao(&peaoJ1[0], 0, coord, '1', '-', 0);

        tabuleiro[8][2] = '1';
        coord[0] = 8;
        coord[1] = 2;
        definePeao(&peaoJ1[1], 0, coord, '1', '-', 1);

        tabuleiro[9][1] = '1';
        coord[0] = 9;
        coord[1] = 1;
        definePeao(&peaoJ1[2], 0, coord, '1', '-', 2);

        tabuleiro[9][2] = '1';
        coord[0] = 9;
        coord[1] = 2;
        definePeao(&peaoJ1[3], 0, coord, '1', '-', 3);

        //Define posição inicial dos peões do jogador 2

        tabuleiro[1][8] = '2';
        coord[0] = 1;
        coord[1] = 8;
        definePeao(&peaoJ2[0], 0, coord, '2', '-', 0);

        tabuleiro[1][9] = '2';
        coord[0] = 1;
        coord[1] = 9;
        definePeao(&peaoJ2[1], 0, coord, '2', '-', 1);

        tabuleiro[2][8] = '2';
        coord[0] = 2;
        coord[1] = 8;
        definePeao(&peaoJ2[2], 0, coord, '2', '-', 2);

        tabuleiro[2][9] = '2';
        coord[0] = 2;
        coord[1] = 9;
        definePeao(&peaoJ2[3], 0, coord, '2', '-', 3);
        
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
        hvDirect(peao);
        tabuleiro[peao->posTab[0]][peao->posTab[1]] = 'o';
        printf("\nPosição: %d %d\n", peao->posTab[0], peao->posTab[1]);
        if(peao->pos == 0){
            tabuleiro[peao->posTab[0]][peao->posTab[1]] = ' ';
            if(peao->simb == '1'){
                tabuleiro[9][4] = peao->simb;
                peao->posTab[0] = 9;
                peao->posTab[1] = 4;
            }else if(peao->simb == '2'){
                tabuleiro[1][6] = peao->simb;
                peao->posTab[0] = 1;
                peao->posTab[1] = 6;
            }else if(peao->simb == '3'){
                tabuleiro[6][9] = peao->simb;
                peao->posTab[0] = 6;
                peao->posTab[1] = 9;
            }else if(peao->simb == '4'){
                tabuleiro[9][4] = peao->simb;
                peao->posTab[0] = 9;
                peao->posTab[1] = 4;
            }
        }else if(peao->direc == 'v'){
            peao->posTab[1] += peao->sentido;
        }else if(peao->direc == 'h'){
            peao->posTab[0] += peao->sentido;
        }else{
    
        }
        peao->pos++;
        tabuleiro[peao->posTab[0]][peao->posTab[1]] = peao->simb;
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

void definePeao(Peao *peao, int pos, int posTab[2], char simb, char direct, int ID){
    peao->pos = pos;
    peao->posTab[0] = posTab[0];
    peao->posTab[1] = posTab[1];
    peao->simb = simb;
    peao->direc = direct;
    peao->ID = ID;
}

int lancarDado(){
    printf("\nPressione Enter para rolar o dado \n");
    getchar();
    int num = (rand() % 6) + 1;
    return num;
}

int jogadorIniciado(Peao peao[4]){
    int estaEmCasa = 0;
    for(int i = 0; i < 4; i++){
        if(peao[i].pos == 0){
            estaEmCasa++;
        }
    }
    return estaEmCasa;
}

void tirardeCasa(Peao *peao){
    for(int i = 0; i < 4; i++){
        if(peao[i].pos == 0){
            switch (peao->simb){
            case '1':
                peao->sentido = -1;
                peao->direc = 'v';
                break;
            case '2':
                peao->sentido = 1;
                peao->direc = 'v';
                break;
            case '3':
                peao->sentido = 1;
                peao->direc = 'h';
                break;
            case '4':
                peao->sentido = -1;
                peao->direc = 'h';
                break;
            default:
                break;
            }
            moverPeao(&peao[i], 1);
            break;
        }
    }
}

int estaEmCasa(Peao peao){
    if(peao.pos == 0){
        return 1;
    }else{
        return 0;
    }
}

int verificaQualPeao(Peao *peao){
    int escolha;
    printf("Qual peão vc deseja mover?\n");
    for (int i = 0; i < 4; i++){
        if(!estaEmCasa(peao[i])){
            printf("%d - Peão na posição %d %d\n", peao[i].ID, peao[i].pos, estaEmCasa(peao[i]));
        }
    }
    printf("Sua escolha: ");
    scanf("%d", &escolha);
    return escolha;
}