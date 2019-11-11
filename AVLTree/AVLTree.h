/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AVLTree.h
 * Author: marcello.ozzetti
 *
 * Created on 10 de Novembro de 2019, 19:28
 */

#ifndef AVLTREE_H
#define AVLTREE_H

#include <stdlib.h>

#define MAX_TAM 5

#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct TNode{
    struct TNode *left;
    struct TNode *right;
    int info;
    int height;
    
} TNode;

typedef struct TNode TTreeAVL;

void init(TNode *node, int info){
    node->height = 1;
    node->info = info;
    node->left = NULL;
    node->right = NULL;
}

int height(TNode *node){
    if(node == NULL){
        return -1;
    }   
    return MAX(1 + height(node->left), 1 + height(node->right));
}

// RSE
TNode *rotateSimpleLeft(TNode *node){
    TNode *aux;
    
    aux = node->left;
    node->left = aux->right;
    aux->right = node;
    
    node->height = MAX(height(node->left), height(node->right)) + 1;
    aux->height = MAX(height(aux->left), node->height) + 1;
    
    return aux;
}

// RDE
TNode *rotateSimpleRight(TNode *node){
    TNode *aux;
    
    aux = node->left;
    node->left = aux->right;
    aux->right = node;
    
    node->height = MAX(height(node->left), height(node->right)) + 1;
    aux->height = MAX(height(aux->left), node->height) + 1;
    
    return aux;
}

int calculateBalance(TNode *node){
    if(node == NULL)
        return 0;
    
    return (height(node->right) - height(node->left));
}

void insertNode(TNode **node, int info){
    
    if(*node == NULL){
        
        (*node) = (TNode*) malloc(sizeof(TNode));
        
        init(*node, info);
    } else {
        if((*node)->info > info ){
            printf(" Left node %d \n", (*node)->info);  
            insertNode(&(*node)->left, info);
        } else {
            printf(" Right node %d \n", (*node)->info);
            insertNode(&(*node)->right, info);
        }
    }
}

void controlInsertNode(TNode **node, int info){
    insertNode(&(*node), info);
    
    int balanceOfNode = calculateBalance(*node);
    
    if(balanceOfNode < -1){
        if(calculateBalance((*node)->left) > 0)
            rotateSimpleLeft((*node)->left);
        
        rotateSimpleRight(*node);
        
    } else if(balanceOfNode > 1){
        if(calculateBalance((*node)->right))
            rotateSimpleRight((*node)->right);
        
        rotateSimpleLeft(*node);
    }
}

void removeNode(TNode **node, int info){
    
}

void searchNode(TNode *node, int info){
    if(node == NULL){
        printf(" Value not found \n");
        return;
    }
    
    if(node->info == info){
        printf("\n Value %d found \n", info);
    } else {
        if(node->info > info){
            searchNode(node->left, info);
        } else {
            searchNode(node->right, info);
        }
    }
}

void printInOrder(TTreeAVL *tree){
    if(tree != NULL){ 
        printInOrder(tree->left);
        printf(" Node info %d and height %d \n", tree->info, tree->height);
        printInOrder(tree->right);
    }
}

void createDefaultTree(TTreeAVL *tree){
    for(int i = 0; i < MAX_TAM; i++){
        int info = (rand() % (50 - 1 + 1));
        
        insertNode(&tree, info);
    }
}

#endif /* AVLTREE_H */

