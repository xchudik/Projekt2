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

int f_N(AUTOPREDAJCA **n_prv){
    int pzaznam = 0,i=0;
    AUTOPREDAJCA *n_akt;
    char pomocna[3];
    FILE *subor;
    subor = fopen("auta.txt","r");
    while(!feof(subor)){
        fgets(pomocna,2,subor);
        if(pomocna[0] == '$')
            pzaznam++;
    }
    if(pzaznam == 0)
        printf("Zaznamy neboli nacitane\n");
    else
        printf("Nacitalo sa %d zaznamov\n",pzaznam);
    rewind(subor);
    (*n_prv) = (AUTOPREDAJCA*) malloc(sizeof(AUTOPREDAJCA));
    fgets(pomocna,2,subor);
    fscanf(subor," %[^\n]s",(*n_prv)->kategoria);
    fscanf(subor," %[^\n]s",(*n_prv)->znacka);
    fscanf(subor," %[^\n]s",(*n_prv)->predajca);
    fscanf(subor," %d",&(*n_prv)->cena);
    fscanf(subor," %d",&(*n_prv)->rok_vyroby);
    fscanf(subor," %[^\n]s",(*n_prv)->stav_vozidla);
    
    n_akt = (*n_prv);
    for(i=0;i<pzaznam-1;i++){
        n_akt->dalsi = (AUTOPREDAJCA*) malloc(sizeof(AUTOPREDAJCA));
        if(n_akt->dalsi == NULL)
            printf("Malo pamate \n");
        n_akt = n_akt->dalsi;
        fgets(pomocna,2,subor);
        fgets(pomocna,2,subor);
        fscanf(subor," %[^\n]s",n_akt->kategoria);
        fscanf(subor," %[^\n]s",n_akt->znacka);
        fscanf(subor," %[^\n]s",n_akt->predajca);
        fscanf(subor," %d",&n_akt->cena);
        fscanf(subor," %d",&n_akt->rok_vyroby);
        fscanf(subor," %[^\n]s",n_akt->stav_vozidla);
    }
    n_akt->dalsi = NULL;
    return pzaznam;
}
void f_V(AUTOPREDAJCA *v_prv){
    int i=1;
    AUTOPREDAJCA *v_akt;
    v_akt = v_prv;
    while(v_akt != NULL){
        printf("%d. \n",i);
        printf("kategoria: %s \n",v_akt->kategoria);
        printf("znacka: %s \n",v_akt->znacka);
        printf("predajca: %s \n",v_akt->predajca);
        printf("cena: %d \n",v_akt->cena);
        printf("rok_vyroby: %d \n",v_akt->rok_vyroby);
        printf("stav_vozidla: %s \n",v_akt->stav_vozidla);
        v_akt = v_akt->dalsi;
        i++;
    }
}
void f_P(AUTOPREDAJCA **p_prv){
    int k,i=1;
    AUTOPREDAJCA *p_novy,*p_akt;
    p_novy = (AUTOPREDAJCA*) malloc(sizeof(AUTOPREDAJCA));
    p_akt = (*p_prv);
    scanf("%d",&k);
        if(k==1){
            p_novy->dalsi=(*p_prv);
            (*p_prv) = p_novy;
            p_akt = (*p_prv);
        }
        else
            while(p_akt != NULL){
                if(i == k || p_akt->dalsi == NULL){
                    p_novy = (AUTOPREDAJCA*) malloc(sizeof(AUTOPREDAJCA));
                    p_novy->dalsi = p_akt->dalsi;
                    p_akt->dalsi = p_novy;
                    p_akt = p_novy;
                    break;
                }
                else
                    p_akt = p_akt->dalsi;
                i++;
            }
    scanf(" %[^\n]s",p_akt->kategoria);
    scanf(" %[^\n]s",p_akt->znacka);
    scanf(" %[^\n]s",p_akt->predajca);
    scanf(" %d",&p_akt->cena);
    scanf(" %d",&p_akt->rok_vyroby);
    scanf(" %[^\n]s",p_akt->stav_vozidla);
}
int main(){
    char c;
    int pocetz = 0;
    AUTOPREDAJCA *m_prv=NULL;
    while(1){
        scanf("%c",&c);
        if(c == 'n'){
            pocetz = f_N(&m_prv);
        }
        else if(c == 'v'){
            f_V(m_prv);
        }
        else if(c == 'p'){
            f_P(&m_prv);
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
    }
    return 0;
}
