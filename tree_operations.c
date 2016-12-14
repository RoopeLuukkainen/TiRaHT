#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

#include "utils.h"
#include "printing.h"

/****************************LEFT*ROTATION*************************************/
/*Executes LL or LR rotation depending on tree balance indicator and child nodes
iBalance number. Very much like example of week 9 exercise 1 from TiRa-course */

void leftRotation (tdTreePointer *pParent, int *tbi, tdOptions *pOpt) {
    tdTreePointer pChild, pGrandChild; /* Creates child grandchild pointers used in rotations */
    pChild = (*pParent)->pLeft;       /* pParent is node which balance is > 1 */

    if (pChild->iBalance == 1) {                               /* LL-rotation */
        if (pOpt->bBuilding && pOpt->bConsol) {
            printf("LL\t Vanhempi: %d, lapsi: %d\n", (*pParent)->iNum, pChild->iNum);
        }

        (*pParent)->pLeft = pChild->pRight;
        pChild->pRight = *pParent;
        (*pParent)->iBalance = 0;
        (*pParent) = pChild;                     /* Child becomes new parent. */

    } else {                                                   /* LR-rotation */
        pGrandChild = pChild->pRight;

        if (pOpt->bBuilding && pOpt->bConsol) {
    		printf("LR\t Vanhempi: %d, lapsi: %d, lapsenlapsi: %d\n",
            (*pParent)->iNum, pChild->iNum, pGrandChild->iNum);
        }

        pChild->pRight = pGrandChild->pLeft;
        (*pParent)->pLeft = pGrandChild->pRight;
        pGrandChild->pLeft = pChild;
        pGrandChild->pRight = *pParent;     /* Grandchild's left and right are child and parent */

        switch (pGrandChild->iBalance) {    /* After rotation check what is balance situation. */
            case 1:
                (*pParent)->iBalance = -1;
                pChild->iBalance = 0;
                break;

            case 0:
                (*pParent)->iBalance = pChild->iBalance = 0;
                break;

            case -1:
                (*pParent)->iBalance = 0;
                pChild->iBalance = 1;
        }
        *pParent = pGrandChild;             /* Grandchild becomes new parent. */
    }
    (*pParent)->iBalance = 0;
    *tbi = 0;
}

/****************************RIGHT*ROTATION************************************/
/*Execute RR or RL rotation depending on tree balance indicator and child nodes
iBalance number. Very much like example of week 9 exercise 1 from TiRa-course */

void rightRotation (tdTreePointer *pParent, int *tbi, tdOptions *pOpt) {
    tdTreePointer pChild, pGrandChild; /* Create child grandchild pointers used in rotations */
    pChild = (*pParent)->pRight;    /* pParent is node which balance is > -1 */

    if (pChild->iBalance == -1) {                              /* RR-rotation */
        if (pOpt->bBuilding && pOpt->bConsol) {
            printf("RR\t Vanhempi: %d, lapsi: %d\n", (*pParent)->iNum, pChild->iNum);
        }

        (*pParent)->pRight = pChild->pLeft;
        pChild->pLeft = *pParent;
        (*pParent)->iBalance = 0;
        (*pParent) = pChild;                     /* Child becomes new parent. */

    } else {                                                   /* RL-rotation */
        pGrandChild = pChild->pLeft;

        if (pOpt->bBuilding && pOpt->bConsol) {
            printf("RL\t Vanhempi: %d, lapsi: %d, lapsenlapsi: %d\n",
            (*pParent)->iNum, pChild->iNum, pGrandChild->iNum);
        }

        pChild->pLeft = pGrandChild->pRight;
        (*pParent)->pRight = pGrandChild->pLeft;
        pGrandChild->pLeft = (*pParent);
        pGrandChild->pRight = pChild; /* Grandchild's left and right are parent and child */

        switch (pGrandChild->iBalance) { /* After rotation check what is balance situation. */
            case 1:
                (*pParent)->iBalance = 0;
                pChild->iBalance = -1;
                break;

            case 0:
                (*pParent)->iBalance = pChild->iBalance = 0;
                break;

            case -1:
                (*pParent)->iBalance = 1;
                pChild->iBalance = 0;
        }
        *pParent = pGrandChild;             /* Grandchild becomes new parent. */
    }
    (*pParent)->iBalance = 0;
    *tbi = 0;
}

/****************************ADDING********************************************/
/* Move recursively along tree and compare current number of node to number
being added. Allocate memory when find node which == NULL. */

tdTree *addValue (tdTree *pParent, tdOptions *pOpt, int num, int *tbi, int *height, int current) {
	tdTree *ptr;

    current++;
    *height = *height < current ? current : *height;
    /* Height keeps track how many layers binary tree has. */

	if (pParent == NULL) { /* If current node is NULL creates a new one which iNum (key) is added number */
		*tbi = 1;
		if ((ptr = (tdTree*)malloc(sizeof(tdTree))) == NULL) { /*Memory allocation*/
			perror("Muistinvaraus epäonnistui );\n");
			exit(1);
		}
		ptr->iNum = num;
        ptr->iCount = 1;
		ptr->iBalance = 0;
		ptr->pRight = ptr->pLeft = NULL;
		pParent = ptr;

		/*printf("Lisättiin luku %d\n", pParent->iNum);*/

/*Recursively call function using pRight pointer when current number > new num */

	} else if (num > pParent->iNum) {
		pParent->pRight = addValue(pParent->pRight, pOpt, num, tbi, height, current);

		if (*tbi) {                         /* Check if tree is unbalanced... */
			switch (pParent->iBalance) { /*... if it is then check what adding will do to balance */
				case 1:
					pParent->iBalance = 0;
					*tbi = 0;
					break;

				case 0:
					pParent->iBalance = -1;
					break;

				case -1:
					rightRotation(&pParent, tbi, pOpt);
                    /* Added to right and tree is rightly balanced ->
                     need to do RR or RL rotation to balance the tree */
			}
		}

/*Recursively call function using pLeft pointer when current number < new num */

	} else if (num < pParent->iNum) {
		pParent->pLeft = addValue(pParent->pLeft, pOpt, num, tbi,  height, current);

		if (*tbi) {                         /* Check if tree is unbalanced... */
			switch (pParent->iBalance) { /*... if it is then check what adding will do to balance */
				case -1:
					pParent->iBalance = 0;
					*tbi = 0;
					break;

				case 0:
					pParent->iBalance = 1;
					break;

				case 1:
					leftRotation(&pParent, tbi, pOpt);
                    /* Added to left and tree is leftly balanced ->
                     need to do LL or LR rotation to balance the tree */
			}
		}
	} else { /* New number is already in tree so count of that number is increased by one. */
		*tbi = 0;
        pParent->iCount += 1;

        if (pOpt->bBuilding && pOpt->bConsol) { /* Print number which was in the tree and number's count. */
                printf("Luku %d on jo puussa, se on esiintynyt %d kertaa.\n", num, pParent->iCount);
        }
	}
	return pParent;
}

/****************************SEARCHING*****************************************/
/* Moves along the tree comparing current node->iNum to number being seach. If
iNum > num goes to right, if iNum < num goes to left and if finds number returns
pointer to that node. If reaches node which is NULL it means there is no seached
number in tree and return NULL. */

tdTree *searchNumber(tdTree *pRoot, int num) {
	tdTree *ptr = pRoot;
    printf("Etsittävä luku: %d\n", num);

	while (ptr != NULL)	 {
        printf("Solmun luku: %d", ptr->iNum);   /* Prints current node's iNum */
		if (num == ptr->iNum) { /* When node with searched number is found return's pointer to that node. */
			return ptr;

		} else if (num > ptr->iNum) { /* When number is bigger than node goes right. */
            printf(" < %d eli -> oikealle.\n", num);
			ptr = ptr->pRight;

		} else if (num < ptr->iNum) { /* When number is smaller than node goes left. */
            printf(" > %d eli -> vasemmalle.\n", num);
			ptr = ptr->pLeft;
		}
	}
	return ptr; /* PTR is NULL if this part is reached */
}

/****************************CLEARING******************************************/
/* Free nodes of tree one by one recursively from leaf node to root node. */

void clearTree(tdTree *pRoot) {
	if (pRoot != NULL) {      /* If node is NULL there is no need to free it. */
		clearTree(pRoot->pRight);                      /* Free right first... */
		clearTree(pRoot->pLeft);                      /* ...then left node... */
        pRoot->pLeft = pRoot->pRight = NULL; /* ...Just in case makes pointer's NULL...  */
/* printf("%d vapautettu\n", pRoot->iNum); */
		free(pRoot);                          /*...finally free current node. */
	}
}

/* EOF */
