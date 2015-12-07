#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Player.h"
#include <graphics.h>
#include <time.h>
#include <unistd.h>

#define LIM_MAX_MURO 120
#define PI 3.1415926535897932384626433832795

int graphic(short esquerda ,int tamanho_muro, int pos_1, int pos_2, int vel_x, int vel_y){
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI");

// ALTERA��O DOS VALORES PARA A ESCALA DA JANELA
    pos_1 *= 6,4;
    pos_2 *= 6,4;

    /**
    * O tamanho total da tela � = 640, 480
    * A posi��o do muro em x � = 320
    **/

// CONSTRU��O DO T�RREO
    line(0, 400, 640, 400);

// CONSTRU��O DO MURO
    line(320, 480 - tamanho_muro, 320, 480);

// INSER��O DOS CANH�ES
    outtextxy(25, 10, "Jogador Atacante");
    circle(pos_1, 392, 8);
    line(pos_1, 384, pos_1 + 20, 380);
    line(pos_1 + 8, 392, pos_1 + 20, 388);
    line(pos_1 + 20, 380, pos_1 + 20, 388);

    outtextxy(345, 10, "Jogador Defensor");
    circle(pos_2, 392, 8);
    line(pos_2, 384, pos_2 - 20, 380);
    line(pos_2 - 8, 392, pos_2 - 20, 388);
    line(pos_2 - 20, 380, pos_2 - 20, 388);

// TRAJET�RIA
    int t, y, x = 0, i;
    for(t = 0; t < 9999; t++){
        usleep(100);
        x = pos_1 + vel_x * t;
            y = 400 + vel_y * t + 10 * t / 2;

            setcolor(RED);
            line(x, y, x + 5, y - 5);

            if(x > 401){
                break;
            }
    }

    getch();
    closegraph();
    return 0;
}

void gerarPosicao(Player *jogador,int x){

    /**
    * x deve ser 0 ou 1, sendo 0 ele determina uma posi��o
    * uma posi��o qualquer que varia de 0 a 50 metros.

    * sendo 1 ele determina uma posi��o
    * uma posi��o qualquer que varia de 50 a 100 metros.
    */

    int posicao;
    srand(time(NULL));
    posicao = rand()%50 + 50*x;
    jogador->limiteEsq= posicao -3;
    jogador->posicao= posicao;
    jogador->limiteDir= posicao +3;
    jogador->lastAngulo=0;
    jogador->lastVeloc=0.0;

}

float atirar(int teta,float *velocInic,Player* atirador){

    /*
        Esta fun��o recebe o angulo teta (inteiro) e a velocidade Inicial (velocInic)
        e calcula a dist�ncia que a "bala" � lan�ada.

        fun��es sen e cos recebem como par�metro angulos em radianos, logo � necess�rio
        fazer a convers�o. A vari�vel "rads" recebe o valor resultante da convers�o de graus
        para radianos.

        For�a da Gravidade = 9,8

        Unidades:
        Velocidade Inicial : m/s ( metros por segundo)
        �ngulo : � ( graus)
        Gravidade: m/s� (metros por segundo ao quadrado)
        Deslocamento : m ( metros)


        --

        Essa fun��o recebe o endere�o do atirador apenas para armazenar alguns dados
        em seus atributos, como last angulo e last veloc;

    */

    //Calculo do deslocamento do tiro no eixo X;
    float seno,cosseno,rads,deslocamento;
    rads = PI/180*teta;
    seno = sin(rads);
    cosseno = cos(rads);
    deslocamento = 2*pow( (*velocInic),2)*seno*cosseno/9.8;

    //Atribui��o de alguns dados;
    atirador->lastAngulo = teta;
    atirador->lastVeloc = *velocInic;

    return deslocamento;

}

void hub(Player* jogador,float *alcanceTiro){
    printf("\n--->> SEU TIRO PERCORREU %.2f METROS;",*alcanceTiro);
    printf("\n--->> POSICAO DO JOGADOR: %i <- %i -> %i",jogador->limiteEsq,jogador->posicao,jogador->limiteDir);
    printf("\n--->> ULTIMO ANGULO: %i",jogador->lastAngulo);
    printf("\n--->> ULTIMA VELOCIDADE: %.2f",jogador->lastVeloc);
    printf("\n[ VER ANIMA��O - PRESSIONE ENTER ] ");
    fflush(stdin);
    getchar();
    fflush(stdin);
}
int verifDeAcerto(Player* vitima,Player* atirador,float *posicaoTiro){
    float tiro;
    /*
        -> VITIMA recebe o endere�o de estrutura do jogador que est� sendo o alvo.
        ( Quem ir� levar "chumbo grosso" )

        -> ATIRADOR: nem precisa explicar;

        -> posicaoTiro recebe por referencia o alcance do tiro.


    */
    if(atirador->posicao >= 50 && atirador->posicao <= 100){
        tiro= atirador->posicao - *posicaoTiro ;
        return ( tiro  >= vitima->limiteEsq)&& (tiro <= vitima->limiteDir) ;
    }else{
        tiro = *posicaoTiro + atirador->posicao;
        return ( tiro  >= vitima->limiteEsq)&& ( tiro<= vitima->limiteDir) ;
    }
}
int definirTamanhoMuro(){
    int tam = rand() % LIM_MAX_MURO + 180;
    printf("Tamanho do muro: %d", tam);
    return tam;
}
