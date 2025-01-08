#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <string.h>


typedef struct{
    int sirka, vyska;
    int maxKroky;
    int replikacie;
    bool multiplayer;
    double pravdepodobnosti[4];
    char vysledkySub[256];
    char svetSub[256];
    bool prekazky;
}ParametreSimulacie;

typedef struct{
    int x,y;
}Chodec;

typedef struct{
    bool **svet;
    int sirka, vyska;
}Svet;


int novaSimulacia(){
    ParametreSimulacie param;
    Svet svet;

    printf("Rozmery sveta (sirka, vyska");
    scanf("%d %d", &param.sirka, &param.vyska);
    printf("Max pocet krokov");
    scanf("%d", &param.maxKroky);
    printf("Replikacie");
    scanf("%d", &param.replikacie);
    printf("Pravdepodobnosti (hore, dole, vlavo, vpravo)");
    for(int i = 0; i < 4; i++){
<------>scanf("%lf", &param.pravdepodobnosti[i]);
    }
    double prav = 0;
    for(int i = 0; i < 4; i++){
<------>prav += param.pravdepodobnosti[i];
    }
    if(prav != 1.0){
<------>printf("Prav. nie su 1");
<------>return 4;
    }
    printf("S Prekazkami? (1 ano 0 nie");
    int p = 0;
    scanf("%d", &p);
    param.prekazky = (p == 0) ? false : true;

    printf("viac hracov? (1 ano 0 nie)");
    int h = 0;
    scanf("%d", &h);
    param.multiplayer = (h == 0) ? false : true;

    printf("Nazov suboru pre ulozenie");
    scanf("%s", &param.vysledkySub);

    svet.sirka = param.sirka;
	svet.vyska = param.vyska;
    inicializuj(&svet, &param);
    uloz(&svet, &param);
    spust(&svet, &param);
....
    for(int i = 0; i < svet.vyska; i++){
<------>free(svet.svet[i]);
    }
    free(svet.svet);

    printf("Simulacia ukončená a uložená do '%s'.\n", param.vysledkySub);
    return 0;
}

int inicializuj(Svet *svet, ParametreSimulacie *parametre){
    int val;
    svet->svet = (bool **)malloc(svet->vyska * sizeof(bool *));
    for(int i = 0; i < svet->vyska; i++){
<------>svet->svet[i] = (bool *)calloc(svet->sirka, sizeof(bool));
    }

    if (parametre->prekazky){
<------>val = vytvorSvetS(svet);
    } else {
<------>val = vytvorSvetBez(svet);
    }
    printf("Svet inicializovany!");
    return val;
}

int spust(Svet *svet, ParametreSimulacie *parametre){
    printf("Pocet replikacii: %d\n", parametre->replikacie);

    for(int k = 0; k < parametre->replikacie; k++){
<------>printf("Replikacia %d z %d\n", k+1, parametre->replikacie);
<------>
<------>for(int i = 0; i < svet->vyska; i++){
<------>    for(int j = 0; j < svet->sirka; j++){
<------><------>if(!svet->svet[i][j]){
<------><------>    printf("Pohol som sa, pozor ma mňa\n");
<------><------>}
<------>    }
<------>}
    }
    printf("Simulacia ukončená \n");
    return 0;
}

int uloz(Svet *svet, ParametreSimulacie *parametre){
    FILE *subor = fopen(parametre->vysledkySub, "w");
    if(!subor){
<------>fprintf(stderr,"Neotvoril sa subor");
<------>return 9;
    }
    fprintf(subor, "x,y,hod\n");
    for(int i = 0; i < svet->vyska; i++){
<------>for(int j = 0; j < svet->sirka; j++){
<------>    if(svet->svet[i][j]){
<------><------>fprintf(subor,"%d,%d,%d\n", i,j, 1);
<------>    } else {
<------><------>fprintf(subor,"%d,%d,%d\n", i,j, 0);
<------>    }
<------>}
    }
    fclose(subor);
    printf("Ulozene do suboru %s\n", parametre->vysledkySub);
}

int vytvorSvetS(Svet *svet){
    if (svet == NULL){
<------>fprintf(stderr,"Svet je null pri vytvor svet s");
<------>return 5;
    }
    for(int i = 0; i < svet->vyska; i++){
<------>for(int j = 0; j < svet->sirka; j++){
<------>    svet->svet[i][j] = (rand() % 5 == 0) ? true : false;
<------>}
    }
    svet->svet[0][0] = false;
    printf("Svet vytvoreny");
    return 0;
}

int vytvorSvetBez(Svet *svet){
    if (svet == NULL){
<------>fprintf(stderr,"Svet je null pri vytvor svet bez");
<------>return 5;
    }
    for(int i = 0; i < svet->vyska; i++){
<------>for(int j = 0; j < svet->sirka; j++){
<------>    svet->svet[i][j] = false;
<------>}
    }
    printf("Svet vytvoreny");
    return 0;
}

//int vytvorSvetSubor(Svet *svet, char[] sub){
//    FILE *subor = fopen(sub, r);
//    if(subor == NULL){
//<---->fprintf(stderr, "Nepodarilo sa otvorit subor pri vytvarani");
//<---->return 6;
//    }
//    int var = 0;
//    for(int i = 0; i < svet->vyska; i++){
//<---->for(int j = 0; j < svet->sirka; j++){
//<---->    fscanf(subor, "%d", var);
//<---->    if (var < 0 || var > 1){
//<----><------>fprintf(stderr, "Chyba pri citani suboru!");
//<----><------>return 7;
//<---->    }
//<---->    svet->svet[i][j] = (var == 0) ? false : true;
//<---->}
//    }
//    printf("Svet vytvoreny");
//    return 0;
//}


int main(int argc, char* argv[]){
    srand(time(NULL));
    int sockfd, newsockfd;
    socklen_t cli_length;
    struct sockaddr_in serv_addr, cli_addr;

    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(atoi(argv[1]));

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
<------>perror("Err create");
<------>return 1;
    }
    int binding =  bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
if (binding < 0){
<------>perror("Err binding");
<------>return 2;
    }
    listen(sockfd, 5);
    cli_length = sizeof(cli_addr);
    printf("Server connected sukesfuly\n");
    int vyber = 0;
    while(1){
<------>newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &cli_length);
<------>if(newsockfd < 0){
<------>    printf("nie\n");
<------>}
<------>pthread_t vlakno;

<------>printf("1 - Nova simulacia\n");
<------>printf("2 - Ukoncit\n");
<------>printf("Zadaj moznost\n");
<------>scanf("%d", &vyber);
<------>if(vyber == 1){
<------>    novaSimulacia();
<------>} else if (vyber == 2){
<------>    printf("Koniec");
<------>    break;
<------>} else {
<------>    printf("nespravna volba");
<------>}
    }
    close(sockfd);
    return 0;
}
