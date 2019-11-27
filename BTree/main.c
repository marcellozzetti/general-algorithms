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

struct timeval start, end;

double diffTime(struct timeval start, struct timeval end){
    double time_taken; 

    time_taken = (end.tv_sec - start.tv_sec) * 1e6; 
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6; 

    return time_taken;
} 

void action(struct btreeNode *tree, int opt) {

    int value;

    switch (opt) {
        case 1:
            printf("Enter your input element:");
            scanf("%d", &value);
            insertBTreeElement(value);
            break;

        case 2:
            printTraversalBTree(tree);
            break;

        case 3:
            printf("Enter the element to search:");
            scanf("%d", &value);

            // start timer. 
            gettimeofday(&start, NULL); 
            
            searchBTreeElement(value, &opt, tree);

            // stop timer. 
            gettimeofday(&end, NULL); 

            printf("Time elapsed: %f (s) \n", diffTime(start, end));
            
            break;

        case 4:
            printf("Enter the element to delete:");
            scanf("%d", &value);
            deleteBTreeElement(value, tree);

        case 5:
            occupationRateBTree(tree);
            break;

        case 10:
            createDefaultTree(tree);
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

    //Starting the Tree-B
    int firstValue;
    printf(" Please, insert the first value %d \n", firstValue);
    insertBTreeElement(firstValue);

    struct btreeNode* Item = returnRoot();

    if (!Item) {
        printf(" Error on creating the stack! \n");
        return (EXIT_FAILURE);
    
    } else {
        int opt = menu();
        while (opt) {
            action(Item, opt);
            opt = menu();
        }
    }

    printf(" *** END *** ");

    free(Item);

    return (EXIT_SUCCESS);
}