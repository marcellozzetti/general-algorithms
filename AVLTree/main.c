/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: marcello.ozzetti
 *
 * Created on 10 de Novembro de 2019, 19:27
 */

#include <stdio.h>
#include <stdlib.h>

#include "AVLTree.h"

#define MAX_LENGTH 10

void action(TTreeAVL *tree, int opt){
    
    int value, valueAux;
    
    switch(opt){
        case 1:
            printf(" Insert a node value: ");
            scanf("%d", &value);
            controlInsertNode(&tree, value);
            break;

        case 2:
            printInOrder(tree);
            break;
        
        case 3:
            printf(" Insert a node value to be find: ");
            scanf("%d", &value);
            searchNode(tree, value);
            break;
        
        case 4:
            printf(" Insert a node value to be removed: ");
            scanf("%d", &value);
            removeNode(&tree, value);
            break;
        
        case 10:
            createDefaultTree(tree);
            break;
            
        default:
            printf(" Wrong %d option! \n\n ", opt);
            break;         
    }
}

int menu(void){
    
    int opt;
    
    printf("\n Select an option: \n");
    printf(" 0. Exit \n");
    printf(" 1. Insert Node \n");
    printf(" 2. Print Pre-Order \n");
    printf(" 3. Search \n");
    printf(" 4. Remove \n");
    printf(" 10. Pre-defined Tree \n");
    printf(" Option: ");
    scanf("%d", &opt);
    
    return opt;
}

/*
 * 
 */
int main(int argc, char** argv) {

    //To be chanced in accordance with option included above: TArray, TStack or TQueue
    TTreeAVL* Item = (TTreeAVL *) malloc(MAX_LENGTH * sizeof(TTreeAVL));
    
    init(Item, (rand() % (50 - 1 + 1)));
    
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