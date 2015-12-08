#include <stdio.h>
#include <stdlib.h>
#include "Player.h"
#include <windows.h>
#include <math.h>
#define PI 3.14159265


/*
    TRABALHO DE FISICA 1

    DATA: 10/11/2015

    ALUNOS :    CARLOS ALBERTO COSTA DE OLIVEIRA JÚNIOR, MATRICULA: 1423331068
                JEOSAFÁ MOREIRA, MATRICULA: 1423331074
                DIEGO BATISTA MACHADO, MATRICULA: 1423331058


            EQUAÇÃO QUE REGE ESTE PROGRAMA:

            X = 2.V°².SEN.COS/G

            X = POSIÇÃO ALCANCE;
            V° = VELOCIDADE INICIAL
            G = FORÇA DA GRAVIDADE = 9,8M/S²


            PROFESSOR : MAURÍCIO.
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

        // CARLOS MODIFICAÇÃO
        graphic(1, muro, jogador1->posicao, jogador2->posicao, velocInicial * cos( angulo * PI / 180) , velocInicial * sin( angulo * PI / 180));
        // CARLOS MODIFICAÇÃO

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

        // CARLOS MODIFICAÇÃO
        graphic(0, muro, jogador2->posicao, jogador1->posicao, velocInicial * cos( angulo * PI / 180) , velocInicial * sin( angulo * PI / 180));
        // CARLOS MODIFICAÇÃO

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
