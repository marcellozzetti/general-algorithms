/* 
 * File:   binaryTree.h
 * Author: marcello.ozzetti
 *
 * Created on 3 de Novembro de 2019, 15:04
 */

#ifndef BINARYTREE_H
#define BINARYTREE_H

#define MAX_TAM 5

#define MAX(a, b) ((a) > (b) ? (a) : (b))

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

int isEmpty(TTree *tree){
    return tree->root == NULL;
}

int heightTree(TNode *node){
    
    if(node == NULL){
        return -1;
    }
    
    return MAX(1 + heightTree(node->left), 1 + heightTree(node->right));
}

int depthTree(TNode *node, int info){  
    if(node == NULL ){
        return -1;
    }
    
    if(node->info == info){
        return 0;
    } else {
        return MAX(1 + depthTree(node->left, info), 1 + depthTree(node->right, info));
    }
}

int parent(TNode *node, int info1, int info2){
    
    if(node == NULL){
        return -1;
    }
    
    return (depthTree(node, info1) - depthTree(node, info2));
}

int checkComplete(TNode *node){
    
    //Contar quantos nos
    // Verificar se satisfaz a formla 
    return node == NULL ? 0 : (checkComplete(node->left) + checkComplete(node->right) + 1);
}

int checkBinary(TNode *node) {
    return (!node->left && !node->right)
            || (node->left && node->right && checkBinary(node->left) && checkBinary(node->right));
}

void createRoot(TTree *tree, int info){
    TNode *nodeNew = (TNode *) malloc(sizeof(TNode));
        
    nodeNew->info = info;
    nodeNew->left = NULL;
    nodeNew->right = NULL;
    tree->root = nodeNew;
    
    printf("\n Generated root value: %d \n", tree->root->info);
}

void insertNode(TNode** node, int info){
     
     if(*node == NULL){
         
         *node = (TNode *) malloc(sizeof(TNode));
         
         (*node)->info = info;  
         (*node)->left = NULL;
         (*node)->right = NULL;
         
     } else {          
        if(info < (*node)->info){
            printf(" Left node %d \n ", (*node)->info);
            insertNode(&(*node)->left, info);
        } else {
            printf(" Right node %d \n", (*node)->info);
           insertNode(&(*node)->right, info); 
        }
     }
}

void printTreePreOrder(TNode *node){  
    if(node != NULL){
        printf("%d(", node->info);
        printTreePreOrder(node->left);
        printf(",");
        printTreePreOrder(node->right);
        printf(")");
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

void createDefaultTree(TTree *tree){
    
    if(isEmpty(tree)){
        createRoot(tree, (rand() % (50 - 1 + 1)) + 1);
    }
    
    for(int i = 0; i < MAX_TAM; i++){
        
        int random = (rand() % (50 - 1 + 1)) + 1; 
        
        printf("\n Generated value: %d \n", random);
        
        insertNode(&tree->root, random);
    }
}
#endif	// BINARYTREE_H

