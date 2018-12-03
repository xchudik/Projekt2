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

typedef struct autobazar{
    char kategoria[51];
    char znacka[51];
    char predajca[101];
    int cena;
    int rok_vyroby;
    char stav_vozidla[201];
    struct autobazar *dalsi;
}AUTOBAZAR;

int f_N(AUTOBAZAR **n_prv){
    int pzaznam = 0,i=0;
    AUTOBAZAR *n_akt = NULL;
    char pomocna[2];
    FILE *subor;
    if((subor = fopen("auta.txt","r")) == NULL){
        printf("Zaznamy neboli nacitane \n");
        return 0;
    }
    subor = fopen("auta.txt","r");
    while(!feof(subor)){
        fgets(pomocna,2,subor);
        if(pomocna[0] == '$')
            pzaznam++;
    }
    rewind(subor);
    if((*n_prv) != NULL){       //Ak bol uz nacitani spajany zoznam uvolni ho
        while(n_akt != NULL){
            n_akt = (*n_prv);
            (*n_prv)=(*n_prv)->dalsi;
            free(n_akt);
        }
        (*n_prv) = NULL;
    }
    (*n_prv) = (AUTOBAZAR*) malloc(sizeof(AUTOBAZAR));
    fscanf(subor," %s",pomocna);                  //Nacitanie znaku '$' do pomocnej premennej
    fscanf(subor," %[^\n]s",(*n_prv)->kategoria);   //Nacitanie prveho zaznamu
    fscanf(subor," %[^\n]s",(*n_prv)->znacka);
    fscanf(subor," %[^\n]s",(*n_prv)->predajca);
    fscanf(subor," %d",&(*n_prv)->cena);
    fscanf(subor," %d",&(*n_prv)->rok_vyroby);
    fscanf(subor," %[^\n]s",(*n_prv)->stav_vozidla);
    
    n_akt = (*n_prv);
    for(i=0;i<pzaznam-1;i++){   //Cyklus pre nacitanie dalsich zaznamov
        n_akt->dalsi = (AUTOBAZAR*) malloc(sizeof(AUTOBAZAR));
        n_akt = n_akt->dalsi;
        fscanf(subor," %s",pomocna);     //Nacitanie znaku '$' do pomocnej premennej
        fscanf(subor," %[^\n]s",n_akt->kategoria);
        fscanf(subor," %[^\n]s",n_akt->znacka);
        fscanf(subor," %[^\n]s",n_akt->predajca);
        fscanf(subor," %d",&n_akt->cena);
        fscanf(subor," %d",&n_akt->rok_vyroby);
        fscanf(subor," %[^\n]s",n_akt->stav_vozidla);
    }
    n_akt->dalsi = NULL; //Ukoncenie spajaneho zaznamu
    printf("Nacitalo sa %d zaznamov\n",pzaznam);
    fclose(subor);
    return 1;
}
void f_V(AUTOBAZAR *v_prv){
    int poradie=1;
    AUTOBAZAR *v_akt;
    v_akt = v_prv;
    while(v_akt != NULL){
        printf("%d. \n",poradie);
        printf("kategoria: %s \n",v_akt->kategoria);
        printf("znacka: %s \n",v_akt->znacka);
        printf("predajca: %s \n",v_akt->predajca);
        printf("cena: %d \n",v_akt->cena);
        printf("rok_vyroby: %d \n",v_akt->rok_vyroby);
        printf("stav_vozidla: %s \n",v_akt->stav_vozidla);
        v_akt = v_akt->dalsi;
        poradie++;
    }
}
void f_P(AUTOBAZAR **p_prv){
    int pozicia,posun=1;
    AUTOBAZAR *p_novy,*p_akt;
    p_novy = (AUTOBAZAR*) malloc(sizeof(AUTOBAZAR));
    p_akt = (*p_prv);
    scanf("%d",&pozicia);
    if(pozicia==1 && (*p_prv) != NULL){   //Pridanie noveho zaznamu ako prvy
        p_novy->dalsi=(*p_prv);
        (*p_prv) = p_novy;
        p_akt = (*p_prv);
    }
    else
        while(p_akt != NULL){      //Pridavanie noveho zaznamu iny ako prvy
            if(posun+1 == pozicia || p_akt->dalsi == NULL){
                p_novy = (AUTOBAZAR*) malloc(sizeof(AUTOBAZAR));
                p_novy->dalsi = p_akt->dalsi;
                p_akt->dalsi = p_novy;
                p_akt = p_novy;
                break;
            }
            else
                p_akt = p_akt->dalsi;
            posun++;
        }
    if((*p_prv) == NULL){   //Ak je spajany zoznam prazdny nacita 1 zaznam
        (*p_prv) = (AUTOBAZAR*) malloc(sizeof(AUTOBAZAR));
        (*p_prv)->dalsi = NULL;
        p_akt = (*p_prv);
    }
        scanf(" %[^\n]s",p_akt->kategoria);
        scanf(" %[^\n]s",p_akt->znacka);
        scanf(" %[^\n]s",p_akt->predajca);
        scanf("%d",&p_akt->cena);
        scanf("%d",&p_akt->rok_vyroby);
        scanf(" %[^\n]s",p_akt->stav_vozidla);
}

void f_Z(AUTOBAZAR **z_prv){
    int pocet = 0;
    AUTOBAZAR *akt,*temp;
    akt = (*z_prv);
    char zauta[51];
    scanf(" %s",zauta);
    while(akt != NULL){
        if(strcasestr(akt->znacka,zauta) && akt == (*z_prv)){ //Podmienka pre zmazanie prveho prvku spajaneho zoznamu
            (*z_prv) = (*z_prv)->dalsi;
            free(akt);
            akt = (*z_prv);
            pocet++;
            continue;
        }
        else if(akt->dalsi != NULL && strcasestr(akt->dalsi->znacka,zauta)){ //Podmienka pre zmazavanie zaznamov (okrem prveho)
            temp = akt->dalsi;
            akt->dalsi = akt->dalsi->dalsi;
            free(temp);
            pocet++;
            continue;
        }
        akt = akt->dalsi;
    }
    printf("Vymazalo sa %d zaznamov \n",pocet);
}

void f_H(AUTOBAZAR *h_prv){
    char zauta[51];
    int ponuka,poradie=1;
    AUTOBAZAR *akt;
    akt = h_prv;
    scanf(" %[^\n]s",zauta);
    scanf("%d",&ponuka);
    while(akt != NULL){
        if(!strcasecmp(akt->znacka,zauta) && akt->cena <= ponuka){
            printf("%d. \n",poradie);
            printf("kategoria: %s \n",akt->kategoria);
            printf("znacka: %s \n",akt->znacka);
            printf("predajca: %s \n",akt->predajca);
            printf("cena: %d \n",akt->cena);
            printf("rok_vyroby: %d \n",akt->rok_vyroby);
            printf("stav_vozidla: %s \n",akt->stav_vozidla);
            poradie++;
        }
        akt = akt->dalsi;
    }
    if(poradie == 1)
        printf("V ponuke nie su pozadovane auta \n");
}

void f_A(AUTOBAZAR **a_prv){
    char zauta[51];
    int rok,pocet=0;
    AUTOBAZAR *akt;
    akt=(*a_prv);
    scanf(" %[^\n]s",zauta);
    scanf("%d",&rok);
    while(akt != NULL){
        if(!strcasecmp(akt->znacka,zauta) && akt->rok_vyroby == rok){
            if((akt->cena = akt->cena-100)<=0)
                akt->cena = 0;
            pocet++;
        }
        akt = akt->dalsi;
    }
    printf("Aktualizovalo sa %d zaznamov \n",pocet);
    
}
void f_K(AUTOBAZAR **k_prv){
    AUTOBAZAR *akt = NULL;
    while(akt != NULL){
        akt = (*k_prv);
        (*k_prv)=(*k_prv)->dalsi;
        free(akt);
    }
    (*k_prv) = NULL;
}

int main(){
    char c;
    AUTOBAZAR *m_prv=NULL;
    while(1){
        scanf("%c",&c);
        if(c == 'n'){
            if(f_N(&m_prv)==0)      //Funkcia pre nacitanie prvkov z textoveho suboru do spajaneho zoznamu
                continue;
        }
        else if(c == 'v'){
            f_V(m_prv);     //Funkcia pre vypis spajaneho zoznamu
        }
        else if(c == 'p'){
            f_P(&m_prv);    //Funkcia pre pridanie zaznamu do spajaheno zoznamu
        }
        else if(c == 'z'){
            f_Z(&m_prv);    //Funkcia pre zmazavanie zaznamov zo spajaneho zoznamu podla znacky
        }
        else if(c == 'h'){
            f_H(m_prv);     //Funkcia pre vyhladanie ponuky podla znacky a ceny
        }
        else if(c == 'a'){
            f_A(&m_prv);    //Funkcia pre znizenie ceny o 100 pre zadanu znacku a rok vyroby
        }
        else if(c == 'k'){
            f_K(&m_prv);    //Funckia pre uvolnenie spajaneho zoznamu a zavretie programu
            break;
        }
    }
    return 0;
}
