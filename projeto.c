/* iaed24 - ist1109625 - project */
#include "header.h"

int main(){
    int ind; //indice que vai ser utilizado eventualmente
    int nparques = 0; int ncarros = 1;
    Data *ultimadata;
    ultimadata = (Data*)malloc(sizeof(Data)*1);
    Hora *ultimahora; //a memoria alocada para estes
    ultimahora = (Hora*)malloc(sizeof(Hora)*1);//ponteiros guardará a ultima data e hora do sistema 
    Nome *nomesparque; 
    nomesparque = (Nome*)malloc(sizeof(Nome) * nparques);
    Parque *Lparques;
    Lparques = (Parque*)malloc(sizeof(Parque) * nparques);
    Veiculo *Lveiculos; // uma lista para os nomes dos parques, para os parques e para os veiculos
    Lveiculos = (Veiculo*)malloc(sizeof(Veiculo) * ncarros);
    ultimadata[0].ano = 0; ultimadata[0].mes = 0; ultimadata[0].dia = 0;
    ultimahora[0].hora = 0; ultimahora[0].min = 0; //são inicializados os valores para a
    while(1){// um loop infinito                   //ultima data e hora registada
        char *comandos = (char*)malloc(BUFSIZ * sizeof(char));
        fgets(comandos, BUFSIZ, stdin); //o input é obtido pelo fgets
        switch (comandos[0]){ //função switch para comandos[0], isto é, cada comando
        case 'q':
            free(Lparques);
            free(nomesparque);
            free(Lveiculos);
            free(comandos);//liberta toda a memoria alocada
            return 0;
            break; //sai do caso 'p' e quebra o ciclo

        case 'p':
            if (comandos[1] == '\n'){ //caso seja só a letra p
                imprimeparques(Lparques, nparques, nomesparque);
                break;//chama a função auxiliar
            }
            else{
                if (nparques >= MAXPARQ){
                    printf("too many parks.\n");
                    break;
                }
                if(adicionaparque(Lparques, comandos, nparques, nomesparque)){
                    nparques++;//a função auxiliar verifica os dados e adiciona o parque 
                    Parque *temp = (Parque*)realloc(Lparques, sizeof(Parque) * 
                    (nparques + 1));
                    Lparques = temp;//realoca a memoria e aumenta o numero de elementos
                    Nome *temp2 = (Nome*)realloc(nomesparque, sizeof(Nome) * 
                    (nparques + 1));
                    nomesparque = temp2;
                    break;
                }
                break;
            }

        case 'e':
            if(verificadados(comandos, nomesparque, Lparques, Lveiculos, 
            nparques, ncarros, ultimadata, ultimahora)){//esta função auxiliar verifica o input inteiro
                adicionacarro(comandos, nomesparque, Lparques, Lveiculos, 
                nparques, ncarros, ultimadata, ultimahora);//o carro é adicionado
                ncarros++;//a memoria é realocada
                Veiculo *temp3 = (Veiculo*)realloc(Lveiculos, sizeof(Veiculo) * (ncarros));
                Lveiculos = temp3;
                ind = tiraindiceparque(comandos, nomesparque, nparques); //tira o indice do parque para tratar o output
                printf("%s %d\n", nomesparque[ind].nome, Lparques[ind].livres);
            }
            break;
        
        case 's':
            if (verificadados(comandos, nomesparque, Lparques, Lveiculos,
            nparques, ncarros, ultimadata, ultimahora)){
                retiraveiculo(comandos, nomesparque, Lparques, Lveiculos, 
                nparques, ncarros, ultimadata, ultimahora);
            }
            break;

        default:
            break;
        free(comandos); //sempre que sai de um dos casos, liberta a memoria do input
        }               //e o ciclo volta a ler os dados do stdin
    }
    return 0;//acaba o programa
}