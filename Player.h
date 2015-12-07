

typedef struct _player{
    int limiteEsq;
    int posicao;
    int limiteDir;
    float lastVeloc;
    int lastAngulo;
}Player;


void gerarPosicao(Player *,int);
float atirar(int ,float *,Player*);
int verifDeAcerto(Player*,Player*,float *);
void hub(Player*,float *);
int definirTamanhoMuro(void);
int graphic(short, int, int, int, float, float);
