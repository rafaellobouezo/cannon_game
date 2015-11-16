#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Player.h"
#define PI 3.1415926535897932384626433832795


void gerarPosicao(Player *jogador,int x){

    /* x deve ser 0 ou 1, sendo 0 ele determina uma posição
    uma posição qualquer que varia de 0 a 50 metros.

    sendo 1 ele determina uma posição
    uma posição qualquer que varia de 50 a 100 metros.

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
        Esta função recebe o angulo teta (inteiro) e a velocidade Inicial (velocInic)
        e calcula a distância que a "bala" é lançada.

        funções sen e cos recebem como parâmetro angulos em radianos, logo é necessário
        fazer a conversão. A variável "rads" recebe o valor resultante da conversão de graus
        para radianos.

        Força da Gravidade = 9,8

        Unidades:
        Velocidade Inicial : m/s ( metros por segundo)
        Ângulo : ° ( graus)
        Gravidade: m/s² (metros por segundo ao quadrado)
        Deslocamento : m ( metros)


        --

        Essa função recebe o endereço do atirador apenas para armazenar alguns dados
        em seus atributos, como last angulo e last veloc;

    */

    //Calculo do deslocamento do tiro no eixo X;
    float seno,cosseno,rads,deslocamento;
    rads = PI/180*teta;
    seno = sin(rads);
    cosseno = cos(rads);
    deslocamento = 2*pow( (*velocInic),2)*seno*cosseno/9.8;

    //Atribuição de alguns dados;
    atirador->lastAngulo = teta;
    atirador->lastVeloc = *velocInic;

    return deslocamento;

}

void hub(Player* jogador,float *alcanceTiro){
    printf("\n--->> SEU TIRO PERCORREU %.2f METROS;",*alcanceTiro);
    printf("\n--->> POSICAO DO JOGADOR: %i <- %i -> %i",jogador->limiteEsq,jogador->posicao,jogador->limiteDir);
    printf("\n--->> ULTIMO ANGULO: %i",jogador->lastAngulo);
    printf("\n--->> ULTIMA VELOCIDADE: %.2f",jogador->lastVeloc);
    printf("\n[ CONTINUAR ? PRESSIONE ENTER ] ");
    fflush(stdin);
    getchar();
    fflush(stdin);
}
int verifDeAcerto(Player* vitima,Player* atirador,float *posicaoTiro){
    float tiro;
    /*
        -> VITIMA recebe o endereço de estrutura do jogador que está sendo o alvo.
        ( Quem irá levar "chumbo grosso" )

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
