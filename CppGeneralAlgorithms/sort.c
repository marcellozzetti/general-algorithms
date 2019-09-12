/* 
 * File:   main.c
 * Author: marcello.ozzetti
 *
 * Created on September 4, 2019, 2:34 PM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * Definitions
 */
#define MAX_LENGH 10

typedef int TKey;
typedef struct{
    TKey key;
} TItem;

/*
 * Main Methods
 */
void sort(TItem *A){
    int i, j;
    TItem aux;
    
    for(i = 2; i < MAX_LENGH; i++){
     
        aux = A[i];
        A[0] = aux;
        j = i - 1;
        
        while( aux.key < A[j].key ){
            
            A[j + i] = A[j];
            j --;
            
        }
        
        A[j + 1] = aux;
    }
}

void print(TItem *A){
    
    int i = 0;
    
    while(A[i].key != '\0'){
        printf("Content %d: %d \n", i, A[i].key);
        i++;
    }
    
    if(i == 0){
        printf("Empty! \n");
    }
}

void add(TItem *A, int value){
    int i;
    
    for(i = 0; i < MAX_LENGH; i++){
        
        if(A[i].key ==  '\0'){
            break;
        }
    }
    if(i == MAX_LENGH){
        printf("Full!");
    } else {
         A[i].key = value;
    }
}

void delete(TItem *A, int value){
    int i;
    
    for(i = 0; i < MAX_LENGH; i++){
        
        if(A[i].key == value){
            A[i].key = A[i + 1].key;
        }
    }
}

void start(TItem *A){
    A[0].key = '\0';
}

int menu(void){
    
    int o;
    
    printf("\n Select an option: \n");
    printf(" 0. Exit \n");
    printf(" 1. Add \n");
    printf(" 2. Sort \n");
    printf(" 3. Remove \n");
    printf(" 4. Print \n");
    printf(" Option: ");
    scanf("%d", &o);
    
    return o;

}

void action(TItem *TSort, int opt){
    
    int value;
    
    switch(opt){
        case 1:
            printf(" Include a value: ");
            scanf("%d", &value);
            add(TSort, value);
            break;
          
        case 2:
            sort(TSort);
            break;

        case 3:
            printf(" Remove a value: ");
            scanf("%d", &value);
            delete(TSort, value);
            break;

        case 4:
            print(TSort);
            break;
   
        default:
            printf(" Wrong %d option! \n\n ", opt);
            break;
         
    }
}

/*
 * Main
 */
int main(int argc, char** argv) {
    
    TItem *TSort = (TItem *) malloc(MAX_LENGH);
    
    //Inicializa
    start(TSort);
    
    if(!TSort){
        printf(" Error on creating the stack! \n");
        return (EXIT_FAILURE);
    } else{
        
        int opt = menu();
        
        while(opt){
            
           action(TSort, opt);
           opt = menu();
        }
    }
    
    printf(" *** END *** ");
    
    free(TSort);
    
    return (EXIT_SUCCESS);
}

