/* 
 * File:   main.c
 * Author: marcello.ozzetti
 *
 * Created on September 29, 2019, 5:22 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "arrayByArrangementAndSort.h"
//#include "arrayByPointer.h"
//#include "stackByArrangement.h"
//#include "stackByPointer.h"
//#include "queueByArrangement.h"
//#include "queueByPointer.h"

#define MAX_LENGTH 10

/*
 * Main
 */
int main(int argc, char** argv) {
    
    //To be chanced in accordance with option included above: TArray, TStack or TQueue
    TArray *Item = (TArray *) malloc(MAX_LENGTH * sizeof(TArray));
    
    start(Item);
    
    if(!Item){
        printf(" Error on creating the stack! \n");
        return (EXIT_FAILURE);
    } else{
        
        int opt = menu();
        
        while(opt){
            
           action(Item, opt);
           opt = menu();
        }
    }
    
    printf(" *** END *** ");
    
    free(Item);
    
    return (EXIT_SUCCESS);
}


