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
}AUTOPREDAJCA;

int main(){
    char c;
    scanf("%c",&c);
    while(1){
        if(c == 'n'){
            
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
