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

void action(TTree *tree, int opt){
    
    int value, valueAux;
    
    switch(opt){
        case 1:
            printf(" Insert a root value: ");
            scanf("%d", &value);
            createRoot(tree, value);
            break;
            
        case 2:
            printf(" Insert a value: ");
            scanf("%d", &value);
            insertNodeABB(&tree->root, value);
            break;
          
        case 3:
            printTreePreOrder(tree->root);
            break;

        case 4:
            printTreeInOrder(tree->root);
            break;
            
        case 5:
            printTreePostOrder(tree->root);
            break;
        
        case 6:
            printf(" Insert a node value to be find: ");
            scanf("%d", &value);
            searchTreeABB(tree->root, value);
            break;
                      
        case 7:
            printf(" Insert a node value: ");
            scanf("%d", &value);
            printf(" Depth: %d \n", depthTree(tree->root, value));
            break;
            
        case 8:
            printf(" Height: %d \n", heightTree(tree->root));
            break;
            
        case 9:
            printf(" Insert a node 1 value: ");
            scanf("%d", &value);
            printf(" Insert a node 2 value: ");
            scanf("%d", &valueAux);
            printf(" Parent: %d \n", parent(tree->root, value, valueAux));
            break;
            
         case 10:
            printf(" Is Binary: %d \n", checkBinary(tree->root));
            printf(" Is Complete: %d \n", checkComplete(tree->root));
            break;
        
        case 20:
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
    printf(" 1. Insert Root \n");
    printf(" 2. Insert Node \n");
    printf(" 3. Print Pre-Order \n");
    printf(" 4. Print In-Order \n");
    printf(" 5. Print Post-Order \n");
    printf(" 6. Search ABB \n");
    printf(" 7. Depth \n");
    printf(" 8. Height \n");
    printf(" 9. Parents \n");
    printf(" 10. Checks \n");
    printf(" 20. Pre-defined Tree \n");
    printf(" Option: ");
    scanf("%d", &opt);
    
    return opt;

}

/*
 * 
 */
int main(int argc, char** argv) {

    //To be chanced in accordance with option included above: TArray, TStack or TQueue
    TTree* Item = (TTree *) malloc(MAX_LENGTH * sizeof(TTree));
    
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

