/* 
 * File:   queueByPointer.h
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
    TPointer front;
    TPointer back;
    
} TQueue;


void start(TQueue *queue){
    
    queue->front = (TPointer) malloc(sizeof(TCell));
    queue->back = queue->front;
    queue->front->next = NULL;
    
}

int isEmpty(TQueue *queue){
    return (queue->front == queue->back);
}

int toQueue(TQueue *queue, TItem item){
    
    queue->back->next = (TPointer) malloc(sizeof(TCell));
    queue->back = queue->back->next;
    queue->back->item = item;
    queue->back->next = NULL;
    
    return 1;
}

int deQueue(TQueue *queue){
    if(isEmpty(queue)){
        printf("Queue empty! \n");
        return 0;
    }
    
    printf("Item dequeued: %d \n", queue->front->item);
    TPointer oldCell = queue->front;
    
    queue->front = queue->front->next;
    free(oldCell);
    
    return 1;
}

int menu(void){
    
    int opt;
    
    printf("\n Select an option: \n");
    printf(" 0. Exit \n");
    printf(" 1. TO Queue \n");
    printf(" 2. DE Queue \n");
    printf(" Option: ");
    scanf("%d", &opt);
    
    return opt;

}

void action(TQueue *queue, int opt){
    
    TItem value;
    
    switch(opt){
        case 1:
            printf(" Insert a value: ");
            scanf("%d", &value);
            toQueue(queue, value);
            break;
          
        case 2:
            deQueue(queue);
            break;
   
        default:
            printf(" Wrong %d option! \n\n ", opt);
            break;
         
    }
}

