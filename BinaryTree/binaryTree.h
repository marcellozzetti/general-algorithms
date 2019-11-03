/* 
 * File:   binaryTree.h
 * Author: marcello.ozzetti
 *
 * Created on 3 de Novembro de 2019, 15:04
 */

#ifndef BINARYTREE_H
#define BINARYTREE_H

typedef struct TNode{
    char info;
    struct TNode *left, *right;
} TNode;

typedef struct{
    TNode * root;
}TTree;

void start(TTree *tree){
    tree->root = NULL;
    
}

void createNode(TNode *nodeLeft, TNode *nodeRight, char info){
     TNode *node = (TNode *) malloc(sizeof(TNode));
     
     node->info = info;
     node->left = nodeLeft;
     node->right = nodeRight;
}

void printTreePreOrder(TTree *tree){
    if(tree != NULL){
        printf(" Node info: %c \n ", tree->root->info);
        printTreePreOrder(tree->root->left);
        printTreePreOrder(tree->root->right);
    }
}

void printTreeInOrder(TTree *tree){
    if(tree != NULL){
        printTreePreOrder(tree->root->left);
        printf(" Node info: %c \n ", tree->root->info);
        printTreePreOrder(tree->root->right);
    }
}

void printTreePostOrder(TTree *tree){
    if(tree != NULL){
        printTreePreOrder(tree->root->left);
        printTreePreOrder(tree->root->right);
        printf(" Node info: %c \n ", tree->root->info);
    }
}

void printTreeWidth(TTree *tree){
    if(tree != NULL){
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

void action(TTree *tree, int opt){
    
    char infoLeft;
    char infoRight;
    
    switch(opt){
        case 1:
            printf(" Insert a value in the left node: ");
            scanf("%d", &infoLeft);
            printf(" Insert a value in the right node: ");
            scanf("%d", &infoRight);
            //createNode(tree->root->left, tree->root->right, infoLeft, infoRight);
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
            printTreeWidth(tree);
            break;
            
        default:
            printf(" Wrong %d option! \n\n ", opt);
            break;         
    }
}
#endif	// BINARYTREE_H

