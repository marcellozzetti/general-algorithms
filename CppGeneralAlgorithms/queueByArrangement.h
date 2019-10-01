/* 
 * File:   queueByArrangement.h
 * Author: marcello.ozzetti
 *
 * Created on September 30, 2019, 2:41 PM
 */

#define MAXTAM 4

typedef int TKey;
typedef int TPointer;

typedef struct {
    TKey key;
    
} TItem;

typedef struct{
    TItem item[MAXTAM];
    TPointer front;
    TPointer back;
    
} TQueue;


void start(TQueue *queue){
    
    queue->front = 1;
    queue->back = queue->front;
    
}

int isEmpty(TQueue *queue){
    return (queue->front == queue->back);
}

int toQueue(TQueue *queue, TItem item){
    
    if(queue->back % MAXTAM + 1 == queue->front){
        printf("Queue full! \n");
        return 0;
    }
    
    queue->item[queue->back - 1] = item;
   
    queue->back = queue->back % MAXTAM + 1;
    
    return 1;
}

int deQueue(TQueue *queue){
    if(isEmpty(queue)){
        printf("Queue empty! \n");
        return 0;
    }
    
    printf("Item dequeued: %d \n", queue->item[queue->front - 1]);
    
    queue->front = queue->front % MAXTAM + 1;
    
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

