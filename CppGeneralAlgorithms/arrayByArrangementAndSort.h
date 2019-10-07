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


void createGenericArray(TArray *array){
    
    TItem i;
    int j;
    
    for(j = 0; j < 10; j++){
        i.key = 10 - j;
        insertItem(array, i);
    }
}

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
    
    for(aux = array->first; aux < array->last; aux++){
        printf(" | %d | \n", array->item[aux - 1].key);
        
    }
    
    return 1;
}

void linearSort(TArray *array){
    
    int i, j;
    TItem aux;
    
    for(i = array->first; i < array->last - 1; i++){
        
        aux = array->item[i];
        j = i - 1;
        
        while( j>= 0 && aux.key < array->item[j].key ){
            
            array->item[j + 1] = array->item[j];
            j--;
            
        }
        
        array->item[j + 1] = aux;
    }
}

void selectionSort(TArray *array){
    
    int i, j, Min;
    TItem aux;
    
    for(i = array->first - 1; i < array->last - 1; i++){
        Min = i;
        
        for(j = i + 1; j < array->last - 1; j++){
            
            if( array->item[j].key < array->item[Min].key ){
                Min = j;
            }
        }
        
        aux = array->item[Min];
        array->item[Min] = array->item[i];
        array->item[i] = aux;
    }
}

void bubbleSort(TArray *array){
    int i, j;
    TItem aux;
    
    for( i = array->first - 1; i < array->last - 1; i++){
        
        for(j = 1; j < array->last - 1; j++){
            
            if(array->item[j].key < array->item[j - 1].key){
                
                aux = array->item[j];
                array->item[j] = array->item[j - 1];
                array->item[j - 1] = aux;
            }
        }
    }
}

/*void heapSort(TArray *array){
    
    TItem aux = array->item[0];
    int m;
    
    heapBuild(aux, MAXTAM);
    
    m = MAXTAM - 1;
    
    while( m > 0 ){
      aux = array->item[m];
      array->item[m] = array->item[0];
      m = m - 1;
      heapRemake(array->item[0],0, m);
    }
}*/

/*void heapRemake(TItem *item, int left, int right){
    TItem aux;
    int i, j;
    
    i = left;
    j = i * 2 + 1;
    
    if( j <= right ){
        aux = item[j];
        
        if( (j < right) && item[j].key < item[j+1].key){
            j++;
             
        }
        
        if(aux.key < item[j].key){
            item[i] = item[j];
            item[j] = aux;
            heapRemake(item, j, left);
            
        }
    }
}*/

/*void heapBuild(TItem *item, int n){
    int left;
    left = (n / 2) - 1;
    
    while( left >= 0 ){
        heapRemake(item, left, n-1);
        left--;
        
    } 
}*/

int quickSortPart(TArray *array, int ini, int end){
    
    int i, j;
    TItem aux, pivot;
    
    pivot = array->item[end];
    i = ini - 1;
    
    for( j = ini; j <= end - 1; j++)
     
        if(array->item[j].key <= pivot.key){
            i++;
            aux = array->item[i];
            array->item[i] = array->item[j];
            array->item[j] = aux;
            
        }
    
    aux = array->item[i + 1];
    array->item[i + 1] = array->item[end];
    array->item[end] = aux;
    
    return i++;
}

void quickSortOrder(TArray *array, int ini, int end){
    
    int q;
    if( ini < end ){
        
        q = quickSortPart(array, ini, end);

        quickSortOrder(array, ini, q - 1);
        quickSortOrder(array, q + 1, end);
    }
}

void quickSort(TArray *array){
    
    quickSortOrder(array, 0, array->last - 2);
    
}

void mergeSortInterc(TArray *array, int ini, int mid, int end){
    
    int i, j, k;
    TArray *newArray = (TArray*) malloc(MAXTAM * sizeof(TArray));
    
    for(i = ini; i <= mid; i++){
        newArray->item[i] = array->item[i];
        printf("vetor B1: %d %d \n", newArray->item[i].key, i);
        
    }
    
    for(j = mid + 1; j <= end; j++){
        newArray->item[end + mid + 1 - j - ini] = array->item[j];
        printf("vetor B2: %d %d \n", newArray->item[end + mid + 1 - j - ini].key, j);
        
    }
    
    i = ini;
    j = end;
    
    for(k = ini; k <= end; k++)
       
        if(newArray->item[i - ini].key <= newArray->item[j - ini].key){
            array->item[k] = newArray->item[i - ini];
            printf("A: %d %d %d %d %d %d %d %d \n", newArray->item[i - ini].key, newArray->item[j - ini].key, array->item[k].key, i, j, k, ini, end);
            i++;
            
        } else {
            array->item[k] = newArray->item[j - ini];
            printf("B: %d %d %d %d %d %d %d %d \n", newArray->item[i - ini].key, newArray->item[j - ini].key, array->item[k].key, i, j, k, ini, end);
            j--;
            
        }
        //printArray(array);
    
    
    free(newArray);
}

void mergeSortOrder(TArray *array, int ini, int end){
    
    int mid;
    
    if( ini < end ){
        
        mid = (ini + end) / 2;
        
        mergeSortOrder(array, ini, mid);
        mergeSortOrder(array, mid+1, end);
        
        mergeSortInterc(array, ini, mid, end);
        
    }
}

void mergeSort(TArray *array){
    
    mergeSortOrder(array, 0, array->last - 2);
    
}

int menu(void){
    
    int opt;
    
    printf("\n Select an option: \n");
    printf(" 0. Exit \n");
    printf(" 1. Insert \n");
    printf(" 2. Remove \n");
    printf(" 3. Print \n");
    printf(" 4. Linear Sort \n");
    printf(" 5. Selection Sort \n");
    printf(" 6. Bubble Sort \n");
    printf(" 7. Heap Sort \n");
    printf(" 8. Quick Sort \n");
    printf(" 9. Merge Sort \n");
    printf(" 10. Create a Generic Array \n");
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
            
        case 5:
            selectionSort(array);
            break;
            
        case 6:
            bubbleSort(array);
            break;
            
        case 7:
            //heapSort(array);
            break;
            
        case 8:
            quickSort(array);
            break; 
        
        case 9:
            mergeSort(array);
            break; 
            
        case 10:
            createGenericArray(array);
            break;
            
        default:
            printf(" Wrong %d option! \n\n ", opt);
            break;
         
    }
}