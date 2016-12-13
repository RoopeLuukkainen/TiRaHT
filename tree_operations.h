#ifndef TREE_H
#define TREE_H

/****************************BINARY*TREE*NODE*STRUCT***************************/
/* Number (key) and pointers to left and right. Also balance indicator and
count how many times same number appear in tree. */

struct Node {
	int iNum, iCount;
	short iBalance;
	struct Node *pLeft, *pRight;
};
typedef struct Node tdTree, *tdTreePointer;

/****************************OPSTIONS*STRUCT***************************/
/* Value = 1 if option is selected == it's ON and 0 == OFF */

struct Struct {
    short bConsol, bFile, bBuilding, bVertical;
};
typedef struct Struct tdOptions, *tdOptionsPointer;

/* Functions */
void leftRotation (tdTreePointer *, int *);
void rightRotation (tdTreePointer *, int *);
tdTree *addValue (tdTree *, tdOptions *, int, int *, int *, int);
tdTree *searchNumber(tdTree *, int);
void clearTree(tdTree *);

#endif /* TREE_H */
