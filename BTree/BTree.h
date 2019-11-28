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

#include <stdio.h>
#include <stdlib.h>

#define MAX 10

    /****** Definitions B-Tree *******/

    struct btreeNode {
        int val[MAX + 1];
        int count;
        struct btreeNode *link[MAX + 1];
    };

    struct btreeNode *root;

#ifdef	__cplusplus
}
#endif

#endif	/* BTREE_H */