/* 
 * File:   arrayByArrangement.h
 * Author: marcello.ozzetti
 *
 * Created on September 30, 2019, 2:41 PM
 */

#include <stdbool.h>
#define MAXTAM 100

typedef int TKey;
typedef int TPointer;

typedef struct {
    TKey key;
    
} TItem;

typedef struct{
    TItem item[MAXTAM];
    TPointer first, last;
    
} TArray;


void start(TArray *array){
    array->first = 1;
    array->last = array->first;
    
}

int isEmpty(TArray *array){
    return (array->first == array->last);
}

int insertItem(TArray *array, TItem item){
    if(array->last == MAXTAM){
        printf(" Stack full! \n");
        return 0;
    }
    
    array->item[array->last - 1] = item;
    array->last++;
    
    return 1;
}

int removeItem(TArray *array, TItem item){
    
    TPointer aux;
    bool foundItem = false;
    
    if(isEmpty(array)){
        printf("Array empty! \n");
        return 0;
    }
    
    for(aux = array->first - 1; aux < array->last; aux++){
        
        if(array->item[aux - 1].key == item.key || foundItem ){
            array->item[aux - 1] = array->item[aux];
            foundItem = true;
        }
    }
    
    array->last = aux - 1;
    
    return 1;
}

int printArray(TArray *array){
    
    printf(" Printing: \n");
    
    TPointer aux;
    
    if(isEmpty(array)){
        printf("Array empty! \n");
        return 0;
    }
    
    for(aux = array->first - 1; aux < array->last - 1; aux++){
        printf(" | %d \n", array->item[aux].key);
        
    }
    
    return 1;
}

void linearSort(TArray *array){
    
    int i, j;
    TItem aux;
    
    for(i = 1; i < array->last - 1; i++){
        
        aux = array->item[i];
        
        j = i - 1;
        
        while( j >= 0 && aux.key < array->item[j].key ){
            
            array->item[j + 1] = array->item[j];
            j--;
            
        }
        
        array->item[j + 1] = aux;
    }
}

int menu(void){
    
    int opt;
    
    printf("\n Select an option: \n");
    printf(" 0. Exit \n");
    printf(" 1. Insert \n");
    printf(" 2. Remove \n");
    printf(" 3. Print \n");
    printf(" 4. Linear Sort \n");
    printf(" Option: ");
    scanf("%d", &opt);
    
    return opt;

}

void action(TArray *array, int opt){
    
    TItem value;
    
    switch(opt){
        case 1:
            printf(" Insert a value: ");
            scanf("%d", &value);
            insertItem(array, value);
            break;
          
        case 2:
            printf(" Insert the value to be removed: ");
            scanf("%d", &value);
            removeItem(array, value);
            break;

        case 3:
            printArray(array);
            break;
          
        case 4:
            linearSort(array);
            break;
            
        default:
            printf(" Wrong %d option! \n\n ", opt);
            break;
         
    }
}