/* 
 * File:   stackByPointer.h
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
    TPointer top;
    TPointer ground;
    int size;
    
} TStack;


void start(TStack *stack){
    stack->top = (TPointer) malloc(sizeof(TCell));
    stack->ground = stack->top;
    stack->top->next = NULL;
    stack->size = 0;
}

int isEmpty(TStack *stack){
    return (stack->top == stack->ground);
}

int push(TStack *stack, TItem item){
    
    TPointer newCell = (TPointer) malloc(sizeof(TCell));
    stack->top->item = item;
    newCell->next = stack->top;
    stack->top = newCell;
    stack->size++;
    
    return 1;
}

int pull(TStack *stack){
    if(isEmpty(stack)){
        printf("Stack empty! \n");
        return 0;
    }
    
    TPointer oldCell = (TPointer) malloc(sizeof(TCell));
    
    oldCell = stack->top;
    stack->top = oldCell->next;
            
    free(oldCell);
    stack->size--;
    printf("Item pulled: %d \n", oldCell->next->item);
    
    return 1;
}

void size(TStack *stack){
    printf("Size: %d \n", stack->size);
}
int menu(void){
    
    int opt;
    
    printf("\n Select an option: \n");
    printf(" 0. Exit \n");
    printf(" 1. Push \n");
    printf(" 2. Pull \n");
    printf(" 3. Size \n");
    printf(" Option: ");
    scanf("%d", &opt);
    
    return opt;

}

void action(TStack *stack, int opt){
    
    TItem value;
    
    switch(opt){
        case 1:
            printf(" Insert a value: ");
            scanf("%d", &value);
            push(stack, value);
            break;
          
        case 2:
            pull(stack);
            break;

        case 3:
            size(stack);
            break;
   
        default:
            printf(" Wrong %d option! \n\n ", opt);
            break;
         
    }
}

