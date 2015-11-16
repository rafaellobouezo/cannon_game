

typedef struct _player{
    int limiteEsq;
    int posicao;
    int limiteDir;
    float lastVeloc;
    int lastAngulo;
}Player;


void gerarPosicao(Player *jogador,int x);
float atirar(int teta,float *velocInic,Player* atirador);
int verifDeAcerto(Player* vitima,Player* atirador,float *posicaoTiro);
