#ifndef TREE_H
#define TREE_H

/****************************TIETORAKENNE**************************************/
/* Number (key) and pointers to left and right. Also balance indicator and
count how many times same number appear in tree. */

struct Node {
	int iNum, iCount;
	short iBalance;
	struct Node *pLeft, *pRight;
};
typedef struct Node tdTree, *tdTreePointer;

/* Functions */
void leftRotation (tdTreePointer *, int *);
void rightRotation (tdTreePointer *, int *);
tdTree *addValue (tdTree *, int, int *, int *, int);
tdTree *searchNumber(tdTree *, int);
void clearTree(tdTree *);

#endif /* TREE_H */
