/* 
 * File:   binaryTree.h
 * Author: marcello.ozzetti
 *
 * Created on 3 de Novembro de 2019, 15:04
 */

#ifndef BINARYTREE_H
#define BINARYTREE_H

#define MAX_TAM 10

typedef struct TNode{
    int info;
    struct TNode *left, *right;
} TNode;

typedef struct{
    TNode *root;
}TTree;

void start(TTree *tree){
    tree->root = NULL;
    
}

void createNode(TNode *node, int info){
     TNode *nodeNew = (TNode *) malloc(sizeof(TNode));
     
     if(node == NULL){
         nodeNew->info = info;
         nodeNew->left = NULL;
         nodeNew->right = NULL;
         
         node = nodeNew;
         printf(" Criou novo node com valor %d \n ", node->info);
     } else {
              
        if(node->info > info){
            printf(" Chamou esquerda \n ");
            createNode(node->left, info);
        } else {
            printf(" Chamou direita \n");
           createNode(node->right, info); 
        }
     }
}

void printTreePreOrder(TNode *node){
    if(node != NULL){
        printf(" Node info: %d \n ", node->info);
        printTreePreOrder(node->left);
        printTreePreOrder(node->right);
    }
}

void printTreeInOrder(TNode *node){
    if(node != NULL){ 
        printTreeInOrder(node->left);
        printf(" Node info: %d \n ", node->info);
        printTreeInOrder(node->right);
    }
}

void printTreePostOrder(TNode *node){
    if(node != NULL){
        printTreePostOrder(node->left);
        printTreePostOrder(node->right);
        printf(" Node info: %d \n ", node->info);
    }
}

void printTreeWidth(TNode *node){
    if(node != NULL){
        //Usar uma fila para pegar os nos e colocar na ordem de impressao
    }
}

int menu(void){
    
    int opt;
    
    printf("\n Select an option: \n");
    printf(" 0. Exit \n");
    printf(" 1. Insert \n");
    printf(" 2. Print Pre-Order \n");
    printf(" 3. Print In-Order \n");
    printf(" 4. Print Post-Order \n");
    printf(" 5. Print Width \n");
    printf(" 10. Pre-defined Tree \n");
    printf(" Option: ");
    scanf("%d", &opt);
    
    return opt;

}

void createDefaultTree(TNode *node){
    
    for(int i = 0; i < MAX_TAM; i++){
        
        int random = (rand() % (20 - 1 + 1)) + 1; 
        
        printf("\n Generated value: %d \n", random);
        
        createNode(node, random);
    }
}

void action(TTree *tree, int opt){
    
    int value;
    
    switch(opt){
        case 1:
            printf(" Insert a value: ");
            scanf("%d", &value);
            createNode(tree->root, value);
            break;
          
        case 2:
            printTreePreOrder(tree);
            break;

        case 3:
            printTreeInOrder(tree);
            break;
            
        case 4:
            printTreePostOrder(tree);
            break;
            
        case 5:
            printTreeWidth(tree);
            break;
            
        case 10:
            createDefaultTree(tree->root);
            break;
            
        default:
            printf(" Wrong %d option! \n\n ", opt);
            break;         
    }
}
#endif	// BINARYTREE_H

