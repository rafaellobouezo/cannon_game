#include <stdio.h>
#include <stdlib.h>
#include "Player.h"
#include <windows.h>
#include <math.h>
#define PI 3.14159265


/*
    TRABALHO DE FISICA 1

    DATA: 10/11/2015

    ALUNOS :    RAFAEL ANDERSON LOBO DA SILVA, UEZO: 1423331065
                CARLOS ALBERTO COSTA DE OLIVEIRA J�NIOR, UEZO: 1423331068
                IGOR GON�ALVEZ SILVA, UEZO: 142333

            EQUA��O QUE REGE ESTE PROGRAMA:

            X = 2.V��.SEN.COS/G

            X = POSI��O ALCANCE;
            V� = VELOCIDADE INICIAL
            G = FOR�A DA GRAVIDADE = 9,8M/S�


            PROFESSOR : MAUR�CIO.
*/

int main()
{
    int angulo;
    float velocInicial,posicao;
    Player* jogador1 = (Player*) malloc( sizeof(Player) );
    Player* jogador2 =  (Player*) malloc( sizeof(Player) );

    gerarPosicao(jogador1,0);
    gerarPosicao(jogador2,1);
    int muro = definirTamanhoMuro();

    while(1){
        printf("\n\n\nVEZ DA PARTIDA: JOGADOR 1 \n\n\n \nDigite um angulo: ");
        scanf("%i",&angulo);
        printf("\nDigite a Velocidade Inicial: ");
        scanf("%f",&velocInicial);
    // ENTRAR COM AS VELOCIDADES
        int vel_x, vel_y;
        posicao = atirar(angulo,&velocInicial,jogador1);
        hub(jogador1,&posicao);

        // CARLOS MODIFICA��O
        graphic(1, muro, jogador1->posicao, jogador2->posicao, velocInicial * cos( angulo * PI / 180) , velocInicial * sin( angulo * PI / 180));
        // CARLOS MODIFICA��O

        // VERIFICAR SE BATEU NO MURO!!!!!!!!!

        if(verifDeAcerto(jogador2,jogador1,&posicao)){
            printf("\n\n JOGADOR 1 VENCEU !");
            break;
        }
        printf("\n [JOGADOR 1 ERROU O TIRO !!!]");
        _sleep(3);
        system("cls");
        fflush(stdin);


        printf("\n\n\nVEZ DA PARTIDA: JOGADOR 2 \n\n\n \nDigite um angulo: ");
        scanf("%i",&angulo);
        printf("\nDigite a Velocidade Inicial: ");
        scanf("%f",&velocInicial);
        posicao = atirar(angulo,&velocInicial,jogador2);
        hub(jogador2,&posicao);

        // CARLOS MODIFICA��O
        graphic(0, muro, jogador1->posicao, jogador2->posicao, velocInicial * cos(angulo), velocInicial * sin(angulo));
        // CARLOS MODIFICA��O

        if(verifDeAcerto(jogador1,jogador2,&posicao)){
            printf("\n\n JOGADOR 2 VENCEU !");
            break;
        }
        printf("\n [JOGADOR 2 ERROU O TIRO !!!]");
        _sleep(3);
        system("cls");
        fflush(stdin);
    }
}
