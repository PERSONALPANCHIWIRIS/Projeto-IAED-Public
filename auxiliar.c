#include "header.h"

int sliceparque(char comandos[]){
    int i = 2; int j = 0;
    char *nomeaux = (char*)malloc(sizeof(char) * BUFSIZ);
    if (comandos[i] == '"'){
        i++;
        while (comandos[i] != '"'){
            nomeaux[j] = comandos[i];
            i++; j++;
        }
        nomeaux[j] = '\0';
        i++; j++;
    }
    else{
        while(comandos[i] != ' '){
            nomeaux[j] = comandos[i];
            i++; j++;
        }
        nomeaux[j] = '\0';
        i++;
    }
    return i;
}

char* slice(const char *indice, int i, int final) {
    int tamanho = final - i;
    char *novo = (char*)malloc(sizeof(char) * (tamanho + 1));
    strncpy(novo, indice + i, tamanho);
    novo[tamanho] = '\0';
    return novo;
}

void imprimeparques(Parque *Lparques, int nparques, Nome *nomesparque){
    int i;
    for (i = 0; i < nparques; i++){
        printf("%s %d %d\n", nomesparque[i].nome, Lparques[i].capa,
        Lparques[i].livres);
    }
}

int adicionaparque(Parque *Lparques, char input[], int nparques, Nome *nomesparque){
    char *indice = input;
    char *nomeaux = (char*)malloc(sizeof(char) * BUFSIZ);
    int capaux; int i = 2; int j = 0;
    float p15aux, h15aux, maxaux;
    if (input[i] == '"'){
        i++;
        while(input[i] != '"'){
            nomeaux[j] = input[i];
            i++; j++;
        }
        nomeaux[j] = '\0';
        i++; i++;
    }
    else{
        while(input[i] != ' '){
            nomeaux[j] = input[i];
            i++; j++;
        }
        nomeaux[j] = '\0';
        i++;
    }
    char *novo = slice(indice, i, strlen(input));
    sscanf(novo, "%d%f%f%f", &capaux, &p15aux, &h15aux, &maxaux);
    free(novo);
    for (j = 0; j < nparques; j++){
        if (strcmp(nomesparque[j].nome, nomeaux) == 0){
            printf("%s: parking already exists.\n", nomeaux);
            free(nomeaux);
            return 0;
        }
    }
    if (capaux <= 0){
        printf("%d: invalid capacity.\n", capaux);
        free(nomeaux);
        return 0;
    }
    if ((p15aux <= 0 || h15aux <= 0 || maxaux <= 0) || 
    ((p15aux >= h15aux) || (h15aux >= maxaux) || (p15aux >= maxaux))){
        printf("invalid cost.\n" );
        free(nomeaux);
        return 0;
    }
    strcpy(nomesparque[nparques].nome, nomeaux);
    Lparques[nparques].capa = capaux;
    Lparques[nparques].p15 = p15aux;
    Lparques[nparques].h15 = h15aux;
    Lparques[nparques].max = maxaux;
    Lparques[nparques].livres = capaux;
    free(nomeaux);
    return 1; 
}

int verifica_capacidade_parque(char comandos[], Nome *nomesparque, int nparques, Parque *Lparques){
    int i = 2; int j = 0;
    char *nomeaux = (char*)malloc(sizeof(char) * BUFSIZ);
    if (comandos[i] == '"'){
        i++;
        while (comandos[i] != '"'){
            nomeaux[j] = comandos[i];
            i++; j++;
        }
        nomeaux[j] = '\0';
        i++; j++;
    }
    else{
        while(comandos[i] != ' '){
            nomeaux[j] = comandos[i];
            i++; j++;
        }
        nomeaux[j] = '\0';
        i++;
    }
    for (j = 0; j < nparques; j++){
        if (strcmp(nomesparque[j].nome, nomeaux) == 0){
            if((Lparques[j].livres) > 0){
                free(nomeaux);
                return 1; //tem capacidade
            }
            else{   //parque esta cheio//
                if (comandos[0] == 's'){
                    free(nomeaux);
                    return 1;
                }
                else{
                    printf("%s: parking is full.\n", nomeaux);
                    free(nomeaux);
                    return 0;
                }
            }
        }
    }
    printf("%s: no such parking.\n", nomeaux);
    free(nomeaux);
    return 0;
}

int matricularegistada(char matricula[], int ncarros, Veiculo *Lveiculos){
    int j;
    for (j = 0; j < ncarros - 1; j++ ){
        if (strcmp(Lveiculos[j].matricula.dados, matricula) == 0){
            if (j == 0){
                return -1;
            }
            else{
                return j;
            }
        }
    }
    return 0;
}

int verifica_data_mat(char comandos[], char matricula[], int dia, int mes, int ano, int hora, int min, Veiculo *Lveiculos, int ncarros, Data *ultimadata, Hora *ultimahora){
    int j;
    int pares = 0;
    int letras = 0;
    int numeros = 0;
    int totalletras = 0; int totalnumeros = 0;
    int diasdomes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int indmat = matricularegistada(matricula, ncarros, Lveiculos);
    for (j = 0; j < 8; j++){
        if (matricula[j] == '-'){
            pares++;
            // Verificar se o par anterior contém pelo menos um caractere de letra e um dígito
            if ((letras == 0 && numeros == 0) ||  (numeros != 0 && letras !=0)) {
                printf("%s: invalid licence plate.\n", matricula);
                return 0;
            }
            letras = 0;
            numeros = 0;
        } 
        else if (matricula[j] >= 'A' && matricula[j] <= 'Z'){
            letras++;
            totalletras++;
        } 
        else if (matricula[j] >= '0' && matricula[j] <= '9'){
            numeros++;
            totalnumeros++;
        } 
        else{
            printf("%s: invalid licence plate.\n", matricula);
            // Se o caractere não for uma letra ou um dígito, a matrícula é inválida
            return 0;
        }
    }
    if (totalletras == 6 || totalnumeros == 6){
        printf("%s: invalid licence plate.\n", matricula);
        return 0;
    }
    if(indmat != 0 && comandos[0] == 'e'){
        if (indmat < 0){
            if ((Lveiculos[0].livre) == 0){
            printf("%s: invalid vehicle entry.\n", matricula);
            return 0;
            }
        }
        else{
            if ((Lveiculos[indmat].livre) == 0){
                printf("%s: invalid vehicle entry.\n", matricula);
                return 0;
            }
        }
    }
    if (indmat != 0 && comandos[0] == 's'){
        if (indmat < 0){
            if ((Lveiculos[0].livre) == 1){
            printf("%s: invalid vehicle exit.\n", matricula);
            return 0;
            }
        }
        else{
            if ((Lveiculos[indmat].livre) == 1){
                printf("%s: invalid vehicle exit.\n", matricula);
                return 0;
            }
        }
    }
    if(ano < ultimadata[0].ano){
        printf("invalid date.\n");
        return 0;
    }
    else{
        if (mes < ultimadata[0].mes){
            printf("invalid date.\n");
            return 0;
        }
        else{
            if(dia < ultimadata[0].dia){
                printf("invalid date.\n");
                return 0;
            }
            else{
                if(hora < ultimahora[0].hora){
                    printf("invalid date.\n");
                    return 0;
                }
                else{
                    if(min < ultimahora[0].min){
                        printf("invalid date.\n");
                        return 0;
                    }
                }
            }
        }
    }

    if (hora < 0 || hora > 24 || min < 0 || min > 59){
        printf("invalid date.\n");
        return 0;
    }
    if (ano < 0 || mes < 1 || mes > 12 || dia < 1 ){
        printf("invalid date.\n");
        return 0;
    }
    if (dia > diasdomes[mes - 1]){
        printf("invalid date.\n");
        return 0;
    }
return 1;
}

int tiraindiceparque(char comandos[], Nome *nomesparque, int nparques){
    int i = 2; int j = 0;
    char *nomeaux = (char*)malloc(sizeof(char) * BUFSIZ);
    if (comandos[i] == '"'){
        i++;
        while (comandos[i] != '"'){
            nomeaux[j] = comandos[i];
            i++; j++;
        }
        nomeaux[j] = '\0';
        i++; j++;
    }
    else{
        while(comandos[i] != ' '){
            nomeaux[j] = comandos[i];
            i++; j++;
        }
        nomeaux[j] = '\0';
        i++;
    }
    for (j = 0; j < nparques; j++){
        if (strcmp(nomesparque[j].nome, nomeaux) == 0){
            free(nomeaux);
            return j;
        }
    }
    free(nomeaux);
    return 0;
}

int verificadados(char comandos[], Nome *nomesparque, Parque *Lparques, Veiculo *Lveiculos, int nparques, int ncarros, Data *ultimadata, Hora *ultimahora){
    int indice, indslice;
    int diaux, mesaux, anoaux, horaux, minaux;
    Matricula matriculaux;
    indslice = sliceparque(comandos);
    char *novo = slice(comandos, indslice, strlen(comandos));
    sscanf(novo, "%s %d-%d-%d %d:%d", matriculaux.dados, &diaux, &mesaux, &anoaux, &horaux, &minaux);
    free(novo);
    indice = verifica_data_mat(comandos, matriculaux.dados, diaux, mesaux, anoaux, horaux, minaux, Lveiculos, ncarros, ultimadata, ultimahora);
    if (indice != 0){
        indice = verifica_capacidade_parque(comandos, nomesparque, nparques, Lparques);
        if (indice != 0){
            return 1;
        }
    }
    else{
        return 0;
    }
    return 0;
}

int atualizahora( int hora, int min, int minutos){
    while(hora != 24){
        if (min == 60){
            min = 0;
            hora++;
        }  //minutos ate o proximo dia
        else{
            min++;
            minutos++;
        }
    }
    return minutos;
}

float faturacao(Veiculo *Lveiculos, int indata, int indcarro, int diaux, int mesaux, int anoaux, int horaux, int minaux, Parque *Lparques, int indparque){
    int dias = 0;
    int diafinal[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int resto;
    Data entrada;
    Hora hentrada;
    entrada.dia = Lveiculos[indcarro].dataentrada[indata].dia;
    entrada.mes = Lveiculos[indcarro].dataentrada[indata].mes;
    entrada.ano = Lveiculos[indcarro].dataentrada[indata].ano;
    hentrada.hora = Lveiculos[indcarro].hentrada[indata].hora;
    hentrada.min = Lveiculos[indcarro].hentrada[indata].min;
    float p15, h15, max;
    p15 = Lparques[indparque].p15;
    h15 = Lparques[indparque].h15;
    max = Lparques[indparque].max;
    float total = 0.0; float minutos = 0.0;
    minutos = atualizahora(hentrada.hora, hentrada.min, minutos);
    entrada.dia++; //passou um dia

    while (entrada.ano < anoaux){
        while ( entrada.dia <= diafinal[entrada.mes - 1]){
        entrada.dia++;
        dias++; //chega ao primeiro dia do proximo mes
        }
        entrada.dia = 1;
        entrada.mes++;
        while (entrada.mes <= 12){
            dias += diafinal[entrada.mes - 1];
            entrada.mes++; //adiciona dias at+e o proximo ano
        }
        entrada.mes = 1;
        entrada.ano++;
    }

    while(entrada.mes < mesaux){
        dias += diafinal[entrada.mes - 1];
        entrada.mes++; //ja no mesmo ano iguala o mes
    }

    if ( entrada.dia != diaux ){
        dias += (diaux - entrada.dia);
    } // no mesmo mes e ano iguala os dias
    minutos += (dias*1440);
    minutos += minaux + (horaux * 60);
    resto = minutos - (dias*1440);
    if(minutos <= 15){
        total = minutos*p15;
    }
    else if(15 < minutos && minutos <= 60){
        total = minutos * h15;
    }
    else{
        total = dias*max;
        if(resto <= 15){
            total += minutos*p15;
        }
        else if(15 < minutos && minutos <= 60){
            total += minutos * h15;
        }
    }
    return total;
}

void adicionacarro(char comandos[], Nome *nomesparque, Parque *Lparques, Veiculo *Lveiculos, int nparques, int ncarros, Data *ultimadata, Hora *ultimahora){
    int ind, indcarro, indslice;
    int diaux, mesaux, anoaux, horaux, minaux;
    Matricula matriculaux;
    ind = tiraindiceparque(comandos, nomesparque, nparques);
    indslice = sliceparque(comandos);
    char *novo = slice(comandos, indslice, strlen(comandos));
    sscanf(novo, "%s %d-%d-%d %d:%d", matriculaux.dados, &diaux, &mesaux, &anoaux, &horaux, &minaux);
    free(novo);
    indcarro = matricularegistada(matriculaux.dados, ncarros, Lveiculos);
    if(indcarro == -1){
        Lveiculos[0].matricula = matriculaux;
        Lveiculos[0].parquesvisitados++;
        Lveiculos[0].nomevisitados = (Nome*)realloc(Lveiculos[0].nomevisitados, sizeof(Nome) * (Lveiculos[0].parquesvisitados));
        Lveiculos[0].nomevisitados[Lveiculos[0].parquesvisitados - 1] = nomesparque[ind];
        Lveiculos[0].dataentrada = (Data*)realloc(Lveiculos[0].dataentrada, sizeof(Data) * (Lveiculos[0].parquesvisitados));
        Lveiculos[0].dataentrada[Lveiculos[0].parquesvisitados - 1].dia = diaux;
        Lveiculos[0].dataentrada[Lveiculos[0].parquesvisitados - 1].mes = mesaux;
        Lveiculos[0].dataentrada[Lveiculos[0].parquesvisitados - 1].ano = anoaux;
        Lveiculos[0].hentrada = (Hora*)realloc(Lveiculos[0].hentrada, sizeof(Hora) * (Lveiculos[0].parquesvisitados));
        Lveiculos[0].hentrada[Lveiculos[0].parquesvisitados - 1].hora = horaux;
        Lveiculos[0].hentrada[Lveiculos[0].parquesvisitados - 1].min = minaux;
        Lveiculos[0].livre = 0;
        Lparques[ind].livres = Lparques[ind].livres - 1;
        ultimadata[0].ano = anoaux;
        ultimadata[0].mes = mesaux;
        ultimadata[0].dia = diaux;
        ultimahora[0].hora = horaux;
        ultimahora[0].min = minaux;
    }
    else if (indcarro == 0){
        Lveiculos[ncarros - 1].matricula = matriculaux;
        Lveiculos[ncarros - 1].parquesvisitados = 1;
        Lveiculos[ncarros -1].nomevisitados = (Nome*)malloc(sizeof(Nome) * (Lveiculos[ncarros -1].parquesvisitados));
        Lveiculos[ncarros -1].nomevisitados[0] = nomesparque[ind];
        Lveiculos[ncarros -1].dataentrada = (Data*)malloc(sizeof(Data) * (Lveiculos[ncarros -1].parquesvisitados));
        Lveiculos[ncarros -1].dataentrada[0].dia = diaux;
        Lveiculos[ncarros -1].dataentrada[0].mes = mesaux;
        Lveiculos[ncarros -1].dataentrada[0].ano = anoaux;
        Lveiculos[ncarros -1].hentrada = (Hora*)malloc(sizeof(Hora) * (Lveiculos[ncarros -1].parquesvisitados));
        Lveiculos[ncarros -1].hentrada[0].hora = horaux;
        Lveiculos[ncarros -1].hentrada[0].min = minaux;
        Lveiculos[ncarros -1].livre = 0;
        Lparques[ind].livres = Lparques[ind].livres - 1;
        ultimadata[0].ano = anoaux;
        ultimadata[0].mes = mesaux;
        ultimadata[0].dia = diaux;
        ultimahora[0].hora = horaux;
        ultimahora[0].min = minaux;
    }
    else{
        Lveiculos[indcarro].matricula = matriculaux;
        Lveiculos[indcarro].parquesvisitados++;
        Lveiculos[indcarro].nomevisitados = (Nome*)realloc(Lveiculos[indcarro].nomevisitados, sizeof(Nome) * (Lveiculos[indcarro].parquesvisitados));
        Lveiculos[indcarro].nomevisitados[Lveiculos[indcarro].parquesvisitados - 1] = nomesparque[ind];
        Lveiculos[indcarro].dataentrada = (Data*)realloc(Lveiculos[indcarro].dataentrada, sizeof(Data) * (Lveiculos[indcarro].parquesvisitados));
        Lveiculos[indcarro].dataentrada[Lveiculos[indcarro].parquesvisitados - 1].dia = diaux;
        Lveiculos[indcarro].dataentrada[Lveiculos[indcarro].parquesvisitados - 1].mes = mesaux;
        Lveiculos[indcarro].dataentrada[Lveiculos[indcarro].parquesvisitados - 1].ano = anoaux;
        Lveiculos[indcarro].hentrada = (Hora*)realloc(Lveiculos[indcarro].hentrada, sizeof(Hora) * (Lveiculos[indcarro].parquesvisitados));
        Lveiculos[indcarro].hentrada[Lveiculos[indcarro].parquesvisitados - 1].hora = horaux;
        Lveiculos[indcarro].hentrada[Lveiculos[indcarro].parquesvisitados - 1].min = minaux;
        Lveiculos[indcarro].livre = 0;
        Lparques[ind].livres = Lparques[ind].livres - 1;
        ultimadata[0].ano = anoaux;
        ultimadata[0].mes = mesaux;
        ultimadata[0].dia = diaux;
        ultimahora[0].hora = horaux;
        ultimahora[0].min = minaux;
    }
}

void retiraveiculo(char comandos[], Nome *nomesparque, Parque *Lparques, Veiculo *Lveiculos, int nparques, int ncarros, Data *ultimadata, Hora *ultimahora){
    int ind, indcarro, indslice;
    int diaux, mesaux, anoaux, horaux, minaux;
    float faturado;
    Matricula matriculaux;
    ind = tiraindiceparque(comandos, nomesparque, nparques);
    indslice = sliceparque(comandos);
    char *novo = slice(comandos, indslice, strlen(comandos));
    sscanf(novo, "%s %d-%d-%d %d:%d", matriculaux.dados, &diaux, &mesaux, &anoaux, &horaux, &minaux);
    free(novo);
    indcarro = matricularegistada(matriculaux.dados, ncarros, Lveiculos);
    if (indcarro == -1){
        Lveiculos[0].datasaida = (Data*)realloc(Lveiculos[0].datasaida, sizeof(Data) * (Lveiculos[0].parquesvisitados));
        Lveiculos[0].datasaida[Lveiculos[0].parquesvisitados - 1].dia = diaux;
        Lveiculos[0].datasaida[Lveiculos[0].parquesvisitados - 1].mes = mesaux;
        Lveiculos[0].datasaida[Lveiculos[0].parquesvisitados - 1].ano = anoaux;
        Lveiculos[0].hsaida = (Hora*)realloc(Lveiculos[0].hsaida, sizeof(Hora) * (Lveiculos[0].parquesvisitados));
        Lveiculos[0].hsaida[Lveiculos[0].parquesvisitados - 1].hora = horaux;
        Lveiculos[0].hsaida[Lveiculos[0].parquesvisitados - 1].min = minaux;
        Lveiculos[0].livre = 1;
        Lparques[ind].livres = Lparques[ind].livres + 1;
        ultimadata[0].ano = anoaux;
        ultimadata[0].mes = mesaux;
        ultimadata[0].dia = diaux;
        ultimahora[0].hora = horaux;
        ultimahora[0].min = minaux;
        faturado = faturacao(Lveiculos, Lveiculos[0].parquesvisitados - 1, 0, diaux, mesaux, anoaux, horaux, minaux, Lparques, ind);
        printf("%s %d-%d-%d %d:%d %d-%d-%d %d:%d %0.2f\n", matriculaux.dados, 
            Lveiculos[0].dataentrada[Lveiculos[0].parquesvisitados - 1].dia, 
            Lveiculos[0].dataentrada[Lveiculos[0].parquesvisitados - 1].mes, 
            Lveiculos[0].dataentrada[Lveiculos[0].parquesvisitados - 1].ano,
            Lveiculos[0].hentrada[Lveiculos[0].parquesvisitados - 1].hora,
            Lveiculos[0].hentrada[Lveiculos[0].parquesvisitados - 1].min,
            diaux, mesaux, anoaux, horaux, minaux, faturado);
    }
    if (indcarro == 0){
        Lveiculos[ncarros -1].datasaida = (Data*)malloc(sizeof(Data) * (Lveiculos[ncarros -1].parquesvisitados));
        Lveiculos[ncarros -1].datasaida[0].dia = diaux;
        Lveiculos[ncarros -1].datasaida[0].mes = mesaux;
        Lveiculos[ncarros -1].datasaida[0].ano = anoaux;
        Lveiculos[ncarros -1].hsaida = (Hora*)malloc(sizeof(Hora) * (Lveiculos[ncarros -1].parquesvisitados));
        Lveiculos[ncarros -1].hsaida[0].hora = horaux;
        Lveiculos[ncarros -1].hsaida[0].min = minaux;
        Lveiculos[ncarros -1].livre = 1;
        Lparques[ind].livres = Lparques[ind].livres + 1;
        ultimadata[0].ano = anoaux;
        ultimadata[0].mes = mesaux;
        ultimadata[0].dia = diaux;
        ultimahora[0].hora = horaux;
        ultimahora[0].min = minaux;
        faturado = faturacao(Lveiculos, 0, ncarros - 1, diaux, mesaux, anoaux, horaux, minaux, Lparques, ind);
        printf("%s %d-%d-%d %d:%d %d-%d-%d %d:%d %0.2f\n", matriculaux.dados, 
            Lveiculos[ncarros - 1].dataentrada[0].dia, 
            Lveiculos[ncarros - 1].dataentrada[0].mes, 
            Lveiculos[ncarros - 1].dataentrada[0].ano,
            Lveiculos[ncarros - 1].hentrada[0].hora,
            Lveiculos[ncarros - 1].hentrada[0].min,
            diaux, mesaux, anoaux, horaux, minaux, faturado); 
    }
    else{
        Lveiculos[indcarro].datasaida = (Data*)realloc(Lveiculos[indcarro].datasaida, sizeof(Data) * (Lveiculos[indcarro].parquesvisitados));
        Lveiculos[indcarro].datasaida[Lveiculos[indcarro].parquesvisitados - 1].dia = diaux;
        Lveiculos[indcarro].datasaida[Lveiculos[indcarro].parquesvisitados - 1].mes = mesaux;
        Lveiculos[indcarro].datasaida[Lveiculos[indcarro].parquesvisitados - 1].ano = anoaux;
        Lveiculos[indcarro].hsaida = (Hora*)realloc(Lveiculos[indcarro].hsaida, sizeof(Hora) * (Lveiculos[indcarro].parquesvisitados));
        Lveiculos[indcarro].hsaida[Lveiculos[indcarro].parquesvisitados - 1].hora = horaux;
        Lveiculos[indcarro].hsaida[Lveiculos[indcarro].parquesvisitados - 1].min = minaux;
        Lveiculos[indcarro].livre = 1;
        Lparques[ind].livres = Lparques[ind].livres + 1;
        ultimadata[0].ano = anoaux;
        ultimadata[0].mes = mesaux;
        ultimadata[0].dia = diaux;
        ultimahora[0].hora = horaux;
        ultimahora[0].min = minaux;
        faturado = faturacao(Lveiculos, Lveiculos[indcarro].parquesvisitados - 1, indcarro, diaux, mesaux, anoaux, horaux, minaux, Lparques, ind);
        printf("%s %d-%d-%d %d:%d %d-%d-%d %d:%d %0.2f\n", matriculaux.dados, 
            Lveiculos[indcarro].dataentrada[Lveiculos[indcarro].parquesvisitados - 1].dia, 
            Lveiculos[indcarro].dataentrada[Lveiculos[indcarro].parquesvisitados - 1].mes, 
            Lveiculos[indcarro].dataentrada[Lveiculos[indcarro].parquesvisitados - 1].ano,
            Lveiculos[indcarro].hentrada[Lveiculos[indcarro].parquesvisitados - 1].hora,
            Lveiculos[indcarro].hentrada[Lveiculos[indcarro].parquesvisitados - 1].min,
            diaux, mesaux, anoaux, horaux, minaux, faturado);
    }
}