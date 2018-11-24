//
//  main.c
//  Projekt 2
//
//  Created by Martin Chudik on 24/11/2018.
//  Copyright © 2018 Martin Chudik. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct autopredajca{
    char kategoria[50];
    char znacka[50];
    char predajca[100];
    int cena;
    int rok_vyroby;
    char stav_vozidla[200];
    struct autopredajca *dalsi;
}AUTOPREDAJCA;

int f_N(AUTOPREDAJCA **n_prv,AUTOPREDAJCA **n_akt,FILE **subor){
    int pzaznam = 0,i=0;
    char *pomocna;
    pomocna = (char*) malloc(sizeof(char));
    *n_prv = (AUTOPREDAJCA*) malloc(sizeof(AUTOPREDAJCA));
    *subor = fopen("auta.txt","r");
    while(!feof(*subor)){
        fgets(pomocna,200,*subor);
        if(*pomocna == '$')
            pzaznam++;
    }
    if(*subor == NULL || pzaznam == 0)
        printf("Zaznamy neboli nacitane\n");
    else
        printf("Nacitalo sa %d zaznamov\n",pzaznam);
    rewind(*subor);
    fscanf(*subor,"%s",pomocna);
    fscanf(*subor,"%s",(*n_prv)->kategoria);
    *n_akt = *n_prv;
    for(i=0;i<pzaznam;i++){
        (*n_akt)->dalsi = (AUTOPREDAJCA*) malloc(sizeof(AUTOPREDAJCA));
        *n_akt = (*n_akt)->dalsi;
        fscanf(*subor,"%s",(*n_akt)->znacka);
        *n_akt = (*n_akt)->dalsi;
        fscanf(*subor,"%s",(*n_akt)->predajca);
        *n_akt = (*n_akt)->dalsi;
        fscanf(*subor,"%d",&(*n_akt)->cena);
        *n_akt = (*n_akt)->dalsi;
        fscanf(*subor,"%d",&(*n_akt)->rok_vyroby);
        *n_akt = (*n_akt)->dalsi;
        fscanf(*subor,"%s",(*n_akt)->stav_vozidla);
        *n_akt = (*n_akt)->dalsi;
        fscanf(*subor,"%s",pomocna);
        *n_akt = (*n_akt)->dalsi;
        fscanf(*subor,"%s",(*n_akt)->kategoria);
    }
    return pzaznam;
}

int main(){
    char c;
    int pocetz = 0;
    AUTOPREDAJCA *m_prv=NULL,*m_akt=NULL;
    FILE *subor;
    scanf("%c",&c);
    while(1){
        if(c == 'n'){
            pocetz = f_N(&m_prv,&m_akt,&subor);
        }
        else if(c == 'v'){
            
        }
        else if(c == 'p'){
            
        }
        else if(c == 'z'){
            
        }
        else if(c == 'h'){
            
        }
        else if(c == 'a'){
            
        }
        else if(c == 'k'){
            break;
        }
        return 0;
    }
}
