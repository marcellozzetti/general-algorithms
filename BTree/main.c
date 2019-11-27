/* 
 * File:   main.c
 * Author: marcello.ozzetti
 *
 * Created on November 26, 2019, 8:01 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h> 

#include "BTree.h"

#define MIN 2

#define QTDE_ELEMENTS 1000

/****** Complementary Methods B-Tree *******/

/*
 * Return the root node from B-Tree generated
 */
struct btreeNode* returnRoot() {
    return root;
}

/* 
 * Create new node 
 */
struct btreeNode* createNode(int val, struct btreeNode *child) {
    struct btreeNode *newNode;
    newNode = (struct btreeNode *) malloc(sizeof (struct btreeNode));
    newNode->val[1] = val;
    newNode->count = 1;
    newNode->link[0] = root;
    newNode->link[1] = child;
    return newNode;
}

/* 
 * Put the value in appropriate position 
 */
void addValToNode(int val, int pos, struct btreeNode *node,
        struct btreeNode *child) {
    int j = node->count;
    while (j > pos) {
        node->val[j + 1] = node->val[j];
        node->link[j + 1] = node->link[j];
        j--;
    }
    node->val[j + 1] = val;
    node->link[j + 1] = child;
    node->count++;
}

/* 
 * Split the node 
 */
void splitNode(int val, int *pval, int pos, struct btreeNode *node,
        struct btreeNode *child, struct btreeNode **newNode) {
    int median, j;

    if (pos > MIN)
        median = MIN + 1;
    else
        median = MIN;

    *newNode = (struct btreeNode *) malloc(sizeof (struct btreeNode));
    j = median + 1;
    while (j <= MAX) {
        (*newNode)->val[j - median] = node->val[j];
        (*newNode)->link[j - median] = node->link[j];
        j++;
    }
    node->count = median;
    (*newNode)->count = MAX - median;

    if (pos <= MIN) {
        addValToNode(val, pos, node, child);
    } else {
        addValToNode(val, pos - median, *newNode, child);
    }
    *pval = node->val[node->count];
    (*newNode)->link[0] = node->link[node->count];
    node->count--;
}

/* 
 * Set the val in the node 
 */
int setValueInNode(int val, int *pval,
        struct btreeNode *node, struct btreeNode **child) {

    int pos;
    if (!node) {
        *pval = val;
        *child = NULL;
        return 1;
    }

    if (val < node->val[1]) {
        pos = 0;
    } else {
        for (pos = node->count;
                (val < node->val[pos] && pos > 1); pos--);
        if (val == node->val[pos]) {
            printf("Duplicates not allowed\n");
            return 0;
        }
    }
    if (setValueInNode(val, pval, node->link[pos], child)) {
        if (node->count < MAX) {
            addValToNode(*pval, pos, node, *child);
        } else {
            splitNode(*pval, pval, pos, node, *child, child);
            return 1;
        }
    }
    return 0;
}

/* 
 * Copy successor for the value to be deleted 
 */
void copySuccessor(struct btreeNode *myNode, int pos) {
    struct btreeNode *dummy;
    dummy = myNode->link[pos];

    for (; dummy->link[0] != NULL;)
        dummy = dummy->link[0];
    myNode->val[pos] = dummy->val[1];

}

/* 
 * Remove the value from the given node and rearrange values 
 */
void removeVal(struct btreeNode *myNode, int pos) {
    int i = pos + 1;
    while (i <= myNode->count) {
        myNode->val[i - 1] = myNode->val[i];
        myNode->link[i - 1] = myNode->link[i];
        i++;
    }
    myNode->count--;
}

/* 
 * Shift value from parent to right child 
 */
void doRightShift(struct btreeNode *myNode, int pos) {
    struct btreeNode *x = myNode->link[pos];
    int j = x->count;

    while (j > 0) {
        x->val[j + 1] = x->val[j];
        x->link[j + 1] = x->link[j];
    }
    x->val[1] = myNode->val[pos];
    x->link[1] = x->link[0];
    x->count++;

    x = myNode->link[pos - 1];
    myNode->val[pos] = x->val[x->count];
    myNode->link[pos] = x->link[x->count];
    x->count--;
    return;
}

/* 
 * Shifts value from parent to left child 
 */
void doLeftShift(struct btreeNode *myNode, int pos) {
    int j = 1;
    struct btreeNode *x = myNode->link[pos - 1];

    x->count++;
    x->val[x->count] = myNode->val[pos];
    x->link[x->count] = myNode->link[pos]->link[0];

    x = myNode->link[pos];
    myNode->val[pos] = x->val[1];
    x->link[0] = x->link[1];
    x->count--;

    while (j <= x->count) {
        x->val[j] = x->val[j + 1];
        x->link[j] = x->link[j + 1];
        j++;
    }
    return;
}

/* 
 * Merge nodes 
 */
void mergeNodes(struct btreeNode *myNode, int pos) {
    int j = 1;
    struct btreeNode *x1 = myNode->link[pos], *x2 = myNode->link[pos - 1];

    x2->count++;
    x2->val[x2->count] = myNode->val[pos];
    x2->link[x2->count] = myNode->link[0];

    while (j <= x1->count) {
        x2->count++;
        x2->val[x2->count] = x1->val[j];
        x2->link[x2->count] = x1->link[j];
        j++;
    }

    j = pos;
    while (j < myNode->count) {
        myNode->val[j] = myNode->val[j + 1];
        myNode->link[j] = myNode->link[j + 1];
        j++;
    }
    myNode->count--;
    free(x1);
}

/* 
 * Adjusts the given node 
 */
void adjustNode(struct btreeNode *node, int pos) {
    if (!pos) {
        if (node->link[1]->count > MIN) {
            doLeftShift(node, 1);
        } else {
            mergeNodes(node, 1);
        }
    } else {
        if (node->count != pos) {
            if (node->link[pos - 1]->count > MIN) {
                doRightShift(node, pos);
            } else {
                if (node->link[pos + 1]->count > MIN) {
                    doLeftShift(node, pos + 1);
                } else {
                    mergeNodes(node, pos);
                }
            }
        } else {
            if (node->link[pos - 1]->count > MIN)
                doRightShift(node, pos);
            else
                mergeNodes(node, pos);
        }
    }
}

/* 
 * Delete val from the node 
 */
int delValFromNode(int val, struct btreeNode *node) {
    int pos, flag = 0;
    if (node) {
        if (val < node->val[1]) {
            pos = 0;
            flag = 0;
        } else {
            for (pos = node->count;
                    (val < node->val[pos] && pos > 1); pos--);
            if (val == node->val[pos]) {
                flag = 1;
            } else {
                flag = 0;
            }
        }
        if (flag) {
            if (node->link[pos - 1]) {
                copySuccessor(node, pos);
                flag = delValFromNode(node->val[pos], node->link[pos]);
                if (flag == 0) {
                    printf("Given data is not present in B-Tree\n");
                }
            } else {
                removeVal(node, pos);
            }
        } else {
            flag = delValFromNode(val, node->link[pos]);
        }
        if (node->link[pos]) {
            if (node->link[pos]->count < MIN)
                adjustNode(node, pos);
        }
    }
    return flag;
}

/****** Main Methods B-Tree *******/

/* 
 * Insert Element into B-Tree
 */
void insertBTreeElement(int val) {
    int flag, i;
    struct btreeNode *child;

    flag = setValueInNode(val, &i, root, &child);
    if (flag)
        root = createNode(i, child);
}

/* 
 * Print Traversal B-Tree
 */
void printTraversalBTree(struct btreeNode *node) {
    int i;
    if (node) {
        for (i = 0; i < node->count; i++) {
            printTraversalBTree(node->link[i]);
            printf("%d ", node->val[i + 1]);
        }
        printTraversalBTree(node->link[i]);
    }
}

/* 
 * Search element in B-Tree 
 */
void searchBTreeElement(int val, int *pos, struct btreeNode *node) {
    if (!node) {
        printf("Given data %d is not present in B-Tree", val);
        return;
    }

    if (val < node->val[1]) {
        *pos = 0;
    } else {
        for (*pos = node->count;
                (val < node->val[*pos] && *pos > 1); (*pos)--);
        if (val == node->val[*pos]) {
            printf("Given data %d is present in B-Tree", val);
            return;
        }
    }
    searchBTreeElement(val, pos, node->link[*pos]);
    return;
}

/* 
 * Delete element from B-Tree 
 */
void deleteBTreeElement(int val, struct btreeNode *node) {
    struct btreeNode *tmp;
    if (!delValFromNode(val, node)) {
        printf("Given value is not present in B-Tree\n");
        return;
    } else {
        if (node->count == 0) {
            tmp = node;
            node = node->link[0];
            free(tmp);
        }
    }
    root = node;
    return;
}

/*
 * Calculate Occupation Rate
 */
void occupationRateBTree(struct btreeNode *node) {

    //contar quantas paginas
    //contar quantos elementos por pagina
    //e dividir pela entrada

    int i;
    if (node) {
        for (i = 0; i < node->count; i++) {

            occupationRateBTree(node->link[i]);
            printf("Count node %d: %d ", i, node->count);
        }
        occupationRateBTree(node->link[i]);
    }
}

/*
 * Create B-Tree default with random elements
 */
void createDefaultTree(struct btreeNode *node) {

    for (int i = 0; i < QTDE_ELEMENTS; i++) {

        insertBTreeElement(rand() % (time(NULL)));
    }
}

struct timeval start, end;

double diffTime(struct timeval start, struct timeval end) {
    double time_taken;

    time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;

    return time_taken;
}

void action(int opt) {

    int value;

    switch (opt) {
        case 1:
            printf("Enter your input element:");
            scanf("%d", &value);
            insertBTreeElement(value);
            break;

        case 2:
            printTraversalBTree(root);
            break;

        case 3:
            printf("Enter the element to search:");
            scanf("%d", &value);

            // start timer
            gettimeofday(&start, NULL);

            searchBTreeElement(value, &opt, root);

            // stop timer 
            gettimeofday(&end, NULL);

            printf("Time elapsed: %f (s) \n", diffTime(start, end));

            break;

        case 4:
            printf("Enter the element to delete:");
            scanf("%d", &value);
            deleteBTreeElement(value, root);

        case 5:
            occupationRateBTree(root);
            break;

        case 10:
            createDefaultTree(root);
            break;

        default:
            printf(" Wrong %d option! \n\n ", opt);
            break;
    }
}

int menu(void) {

    int opt;

    printf("\n Select an Option: \n");
    printf(" 0. Exit \n");
    printf(" 1. Insert Node \n");
    printf(" 2. Print Traversal \n");
    printf(" 3. Search \n");
    printf(" 4. Remove \n");
    printf(" 5. Occupation Rate \n");
    printf(" 10. Pre-defined BTree \n");
    printf(" Option: ");
    scanf("%d", &opt);

    return opt;
}

int main(int argc, char** argv) {

    insertBTreeElement(rand() % (time(NULL)));
    
    if (!root) {
        printf(" Error on creating the stack! \n");
        return (EXIT_FAILURE);

    } else {
        int opt = menu();
        while (opt) {
            action(opt);
            opt = menu();
        }
    }

    printf(" *** END *** ");

    free(root);

    return (EXIT_SUCCESS);
}