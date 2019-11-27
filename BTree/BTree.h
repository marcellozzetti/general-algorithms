/* 
 * File:   BTree.h
 * Author: marcello.ozzetti
 *
 * Created on November 26, 2019, 11:22 PM
 */

#ifndef BTREE_H
#define	BTREE_H

#ifdef	__cplusplus
extern "C" {
#endif

#define MAX 4 /* maximum number of keys in node */
#define MIN 2 /* minimum number of keys in node */

    typedef int Key;

    typedef struct {
        Key key;
        int value; /* values can be of arbitrary type */
    } Treeentry;
    
    typedef struct treenode Treenode;

    struct treenode {
        int count; /* number of keys in node */
        Treeentry entry[MAX + 1];
        Treenode *branch[MAX + 1];
    };

/* PushDown: recursively move down tree searching for newentry.
 Pre: newentry belongs in the subtree to which current points.
 Post: newentry has been inserted into the subtree to which current points; if TRUE
 is returned, then the height of the subtree has grown, and medentry needs
 to be reinserted higher in the tree, with subtree medright on its right.
 Uses: PushDown recursively, SearchNode, Split, PushIn. */
    int PushDown(Treeentry newentry, Treenode *current, Treeentry *medentry, Treenode **medright) {
        int pos; /*branch on which to continues the search */
        if (current == NULL) { /* cannot insert into empty tree; terminates */
            *medentry = newentry;
            *medright = NULL;
            return 1;
        } else { /* Search the current node */
            if (SearchNode(newentry.key, current, &pos))
                printf("Inserting duplicate key into B-tree");
            if (PushDown(newentry, current->branch[pos], medentry, medright))
                if (current->count < MAX) { /*Reinsert median key. */
                    PushIn(*medentry, *medright, current, pos);
                    return 0;
                } else {
                    Split(*medentry, *medright, current, pos, medentry, medright);
                    return 1;
                }
            return 0;
        }
        
/* InsertTree: Inserts entry into the B-tree.
 Pre: The B-tree to which root points has been created, and no entry in the B-tree
 has key equal to newentry key.
 Post: newentry has been inserted into the B-tree, the root is returned.
 Uses: PushDown */
    Treenode *InsertTree(Treeentry newentry, Treenode *root) {
        Treeentry medentry; /* node to be reinserted as new root */
        Treenode *medright; /* subtree on right of medentry */
        Treenode *newroot; /* used when the height of the tree increases */
        if (PushDown(newentry, root, &medentry, &medright)) {
            /* Tree grows in height. Make a new root */
            newroot = (Treenode *) malloc(sizeof (Treenode));
            newroot->count = 1;
            newroot->entry[1] = medentry;
            newroot->branch[0] = root;
            newroot->branch[1] = medright;
            return newroot;
        }
        return root;
    }

    /*typedef struct NodeB{
      int **keys;
      int isLeaf;
      int nNodes;
      struct NodeB** children;
    } NodeB;

    typedef struct BTree{
      NodeB* root;
      int order;
    } BTree;

    #define T_KEY 10

    BTree* initTree(int order){
    
            int i;
            BTree* tree = (BTree*) malloc(sizeof(BTree));
  
            //Alocação da raiz da árvore
            tree->root = (NodeB*) malloc(sizeof(NodeB));
            tree->root->keys = (int**) malloc((order - 1)*sizeof(int*));
            tree->root->isLeaf = 1;
            tree->root->nNodes = 0;
            tree->root->children = (NodeB**) malloc(order*sizeof(NodeB*));

            //Alocação de cada uma das strings das chaves e inicializando os filhos com NULL 
            for(i = 0; i < order - 1; i++){
                    tree->root->keys[i] = (int*) malloc(T_KEY*sizeof(int));
                    tree->root->children[i] = NULL;
            }

            //Inicialização do último filho com NULL
            tree->root->children[i] = NULL;
  
            tree->order = order;
            return tree;
    }

    void insertBTree(BTree* tree, int value){
        NodeB* r = tree->root;

        //Caso em que deseja-se inserir um novo nó em uma raiz vazia
        if(tree->root->nNodes == 0){
            tree->root->keys[0] = value;
            tree->root->nNodes++;
        
        }else{ //Caso em que a raiz não é vazia

            //Caso em que o nó raiz está cheio
            if(r->nNodes == tree->order - 1){

                //Criação de um novo nó que se tornará a nova raiz
                NodeB* s;// = createNode(tree->order);
                tree->root = s;
                s->isLeaf = 0;
                s->nNodes = 0;

                //A antiga raiz se torna filha da nova raiz
                s->keys[0] = r;

                //Reparte-se a raiz para que ela tenha 2 filhos
                //repartir_filho(s, 0, arv->ordem);

                //Insere-se o novo nó
                //insere_arvore_naocheia(s, chave, NRR, arv->ordem);
            } else{//Caso em que a raiz não está cheia
                //insere_arvore_naocheia(r, chave, NRR, arv->ordem);
            }
        }
    }

    void printBTree(NodeB* node){
        if(node != NULL){
            int i;
            for (i = 0; i < node->nNodes; i++) {
                printBTree(node->children[i]);
                printf("Value %d", node->keys[i + 1]);
            }
            printBTree(node->children[i]);
        }
    }

    void searchBTree(BTree* tree, int value);

    void removeBTree(BTree* tree, int value);

    void ocupationRate(BTree* tree);

    NodeB* createNode(int order){
            int i;
            NodeB* newNode = (NodeB*) malloc(sizeof(NodeB));
            newNode->keys = (int**) malloc((order - 1)*sizeof(int*));
            newNode->children = (NodeB**) malloc(order*sizeof(NodeB*));
    
            //Alocação de cada uma das strings das chaves e inicializando os filhos com NULL 
            for(i = 0; i < order - 1; i++){
                    newNode->keys[i] = (int*) malloc(T_KEY*sizeof(int));
                    newNode->children[i] = NULL;
            }
            //Inicizalização do último filho com NULL
            newNode->children[i] = NULL;

            return newNode;
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

    void printInOrder(BTree *tree){
        if(tree != NULL){ 
            printInOrder(tree->left);
            printf(" Node info %d and height %d \n", tree->info, tree->height);
            printInOrder(tree->right);
        }
    }

    void createDefaultTree(BTree *tree){
        for(int i = 0; i < MAX_TAM; i++){
            int info = (rand() % (50 - 1 + 1));
        
            insertNode(&tree, info);
        }
    }*/

#ifdef	__cplusplus
}
#endif

#endif	/* BTREE_H */