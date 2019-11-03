/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: marcello.ozzetti
 *
 * Created on 3 de Novembro de 2019, 15:04
 */

#include <stdio.h>
#include <stdlib.h>

#include "binaryTree.h"

#define MAX_LENGTH 10

/*
 * 
 */
int main(int argc, char** argv) {

    //To be chanced in accordance with option included above: TArray, TStack or TQueue
    TTree *Item = (TTree *) malloc(MAX_LENGTH * sizeof(TTree));
    
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

