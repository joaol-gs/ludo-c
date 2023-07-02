#include <stdio.h>

void mostraMenu(int *opc){
    printf("Escolha uma opção no menu: \n");
    printf("1 - Novo jogo\n");
    printf("0 - Sair\n");
    printf("Sua escolha: ");
    scanf("%d", opc);
}

int main(){
    int opc;
    printf("===Bem vindo ao Ludo=== \n");
    mostraMenu(&opc);
    while(opc != 0){
        switch (opc){
        case 1:
            break;
        case 2:
            break;
        default:
            printf("A opção selecionada é inválida! \n");
            mostraMenu(&opc);
            break;
        }
    }
    return 0;
}