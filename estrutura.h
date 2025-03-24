#ifndef _ESTRUTURA_H_
#define _ESTRUTURA_H_
#define BUFSIZ 8192

typedef struct nome{
    char nome[BUFSIZ]; //o tamanho maximo possivel do input
} Nome;

typedef struct hora{
    int hora;
    int min;
} Hora; //uma estrutura para as horas

typedef struct data{
    int dia;
    int mes;
    int ano;
} Data;//uma estrutura para as datas

typedef struct parque{
    int capa;
    float p15;
    float h15;
    float max;
    int livres;
    float totalfaturado;
} Parque; //uma estrutura para os parques

typedef struct matricula{
    char dados[9];
} Matricula;//uma estrutura para a matricula

typedef struct veiculo{
    Nome *nomevisitados;
    int parquesvisitados;
    Matricula matricula;
    Hora *hentrada;//o veiculo tem ponteiros na sua estrutura
    Data *dataentrada;// que serão eventualmente utilizados
    Hora *hsaida;    //para apontar a memoria que guarda dados dinamicos
    Data *datasaida;
    int livre;
} Veiculo;//uma estrutura para os veiculos

int sliceparque(char comandos[]);
char* slice(const char *indice, int i, int final);
void imprimeparques(Parque *Lparques, int nparques, Nome *nomesparque);
int adicionaparque(Parque *Lparques, char input[], int nparques, Nome *nomesparque);
int verifica_capacidade_parque(char comandos[], Nome *nomesparque, int nparques, Parque *Lparques);
int matricularegistada(char matricula[], int ncarros, Veiculo *Lveiculos);
int verifica_data_mat(char comandos[], char matricula[], int dia, int mes, int ano, int hora, int min, Veiculo *Lveiculos, int ncarros, Data *ultimadata, Hora *ultimahora);
int tiraindiceparque(char comandos[], Nome *nomesparque, int nparques);
int verificadados(char comandos[], Nome *nomesparque, Parque *Lparques, Veiculo *Lveiculos, int nparques, int ncarros, Data *ultimadata, Hora *ultimahora);
int atualizahora( int hora, int min, int minutos);
float faturacao(Veiculo *Lveiculos, int indata, int indcarro, int diaux, int mesaux, int anoaux, int horaux, int minaux, Parque *Lparques, int indparque);
void adicionacarro(char comandos[], Nome *nomesparque, Parque *Lparques, Veiculo *Lveiculos, int nparques, int ncarros, Data *ultimadata, Hora *ultimahora);
void retiraveiculo(char comandos[], Nome *nomesparque, Parque *Lparques, Veiculo *Lveiculos, int nparques, int ncarros, Data *ultimadata, Hora *ultimahora);

#endif

