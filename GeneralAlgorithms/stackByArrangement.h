/* 
 * File:   stackByArrangement.h
 * Author: marcello.ozzetti
 *
 * Created on September 30, 2019, 2:41 PM
 */

#define MAXTAM 100

typedef int TKey;
typedef int TTop;

typedef struct {
    TKey key;
    
} TItem;

typedef struct{
    TItem item[MAXTAM];
    TTop top;
    
} TStack;


void start(TStack *stack){
    stack->top = 0;
}

int isEmpty(TStack *stack){
    return (stack->top == 0);
}

int push(TStack *stack, TItem item){
    if(stack->top == MAXTAM){
        printf(" Stack full! \n");
        return 0;
    }
    
    stack->item[stack->top] = item;
    stack->top++;
    
    return 1;
}

int pull(TStack *stack){
    if(isEmpty(stack)){
        printf("Stack empty! \n");
        return 0;
    }
    
    stack->top--;
    printf("Item pulled: %d \n", stack->item[stack->top]);
    return 1;
}

void size(TStack *stack){
    printf("Size: %d \n", stack->top);
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