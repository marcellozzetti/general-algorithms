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

void searchTreeABB(TNode *node, int info){
    
    if(node == NULL){
        printf("\n Value not found \n");
        return;
    }
    
    if(node->info == info){
        printf("\n Value %d found \n", info);
    } else {
        if(node->info > info){
            searchTreeABB(node->left, info);
        } else {
            searchTreeABB(node->right, info);
        }
    }
}

int checkComplete(TNode *node){
    
    //TO BE implemented
    //return node == NULL ? 0 : (checkComplete(node->left) + checkComplete(node->right) + 1);
    return 0;
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

void insertNodeABB(TNode** node, int info){
     
     if(*node == NULL){
         
         *node = (TNode *) malloc(sizeof(TNode));
         
         (*node)->info = info;  
         (*node)->left = NULL;
         (*node)->right = NULL;
         
     } else {          
        if(info < (*node)->info){
            printf(" Left node %d \n ", (*node)->info);
            insertNodeABB(&(*node)->left, info);
        } else {
            printf(" Right node %d \n", (*node)->info);
           insertNodeABB(&(*node)->right, info); 
        }
     }
}

TNode* maxNodeRight(TNode **node){
    if((*node)->right != NULL) 
       return maxNodeRight(&(*node)->right);
    else{
       TNode *aux = *node;
       if((*node)->left != NULL)
          *node = (*node)->left;
       else
          *node = NULL;
       return aux;
       }
}

void removeNodeABB(TNode** node, int info){
    
    if(*node == NULL){
        printf(" Remove ended \n");
        return;
    }
    
    if((*node)->info > info){
        removeNodeABB(&(*node)->left, info);
    } else if ((*node)->info < info){
        removeNodeABB(&(*node)->right, info);
    } else{ //found it
        TNode *pAux = *node;
        if((*node)->left == NULL && (*node)->right == NULL){
            free(pAux);
            *node = NULL;
        } else{
            if((*node)->left == NULL){
                *node = (*node)->right;
                pAux->right = NULL;
                free(pAux);
                pAux = NULL;
            } else {
                if((*node)->right == NULL){
                    *node = (*node)->left;
                    pAux->left = NULL;
                    free(pAux);
                    pAux = NULL;
                } else{ //has both nodes
                    pAux = maxNodeRight(&(*node)->left);
                    pAux->left = (*node)->left;
                    pAux->right = (*node)->right;
                    (*node)->left = (*node)->right = NULL;
                    free(*node);  
                    *node = pAux;  
                    pAux = NULL;  
                }
            }
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
        
        insertNodeABB(&tree->root, random);
    }
}
#endif	// BINARYTREE_H

