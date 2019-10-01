/* 
 * File:   arrayByPointer.h
 * Author: marcello.ozzetti
 *
 * Created on September 30, 2019, 2:41 PM
 */

typedef int TKey;

typedef struct {
    TKey key;
    
} TItem;

typedef struct SCell *TPointer;

typedef struct SCell{
    TItem item;
    TPointer next;
    
} TCell;

typedef struct{
    TPointer first, last;
    
} TArray;


void start(TArray *array){
    array->first = NULL;
    array->last = array->first;
    
}

int isEmpty(TArray *array){
    return (array->last == NULL);
}

int insertItem(TArray *array, TItem item){
    
    if(isEmpty(array)){
        array->first = (TPointer) malloc(sizeof(TCell));
        array->last = array->first;
        
    } else {
        array->last->next = (TPointer) malloc(sizeof(TCell));
        array->last = array->last->next;
    }

    array->last->item = item;
    array->last->next = NULL;
    
    return 1;
}

int removeItem(TArray *array, TItem item){
    
    TPointer aux;
    
    if(isEmpty(array)){
        printf("Array empty! \n");
        return 0;
    }
    
    if(array->first->item.key == item.key){
        array->first = array->first->next;
    } else {
        for(aux = array->first; aux < array->last; aux = aux->next){
        
        if(aux->next->item.key == item.key ){
            aux->next = aux->next->next;
            break;
        }
    }
    }
    
    return 1;
}

int printArray(TArray *array){
    
    printf(" Printing: \n");
    
    TPointer aux = array->first;
    
    if(isEmpty(array)){
        printf("Array empty! \n");
        return 0;
    }
    
    while(aux != NULL){
        printf(" | %d \n", aux->item.key);
        aux = aux->next;
        
    }
    
    return 1;
}

int menu(void){
    
    int opt;
    
    printf("\n Select an option: \n");
    printf(" 0. Exit \n");
    printf(" 1. Insert \n");
    printf(" 2. Remove \n");
    printf(" 3. Print \n");
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
            
        default:
            printf(" Wrong %d option! \n\n ", opt);
            break;
         
    }
}