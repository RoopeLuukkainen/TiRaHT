#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

#include "utils.h"
#include "printing.h"

/****************************LEFT*ROTATION*************************************/
/*Execute LL or LR rotation depending on tree balance indicator and child nodes
iBalance number.*/

void leftRotation (tdTreePointer *pParent, int *tbi) {
    tdTreePointer pChild, pGrandChild;
    pChild = (*pParent)->pLeft;

    if (pChild->iBalance == 1) {                               /* LL-rotation */
		printf("LL\t Vanhempi: %d, lapsi: %d\n", (*pParent)->iNum, pChild->iNum);
        (*pParent)->pLeft = pChild->pRight;
        pChild->pRight = *pParent;
        (*pParent)->iBalance = 0;
        (*pParent) = pChild;

    } else {                                                   /* LR-rotation */
        pGrandChild = pChild->pRight;

		printf("LR\t Vanhempi: %d, lapsi: %d, lapsenlapsi: %d\n",
        (*pParent)->iNum, pChild->iNum, pGrandChild->iNum);

        pChild->pRight = pGrandChild->pLeft;
        (*pParent)->pLeft = pGrandChild->pRight;
        pGrandChild->pLeft = pChild;
        pGrandChild->pRight = *pParent;

        switch (pGrandChild->iBalance) {
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
        *pParent = pGrandChild;
    }
    (*pParent)->iBalance = 0;
    *tbi = 0;
}

/****************************RIGHT*ROTATION************************************/
/*Execute RR or RL rotation depending on tree balance indicator and child nodes
iBalance number.*/

void rightRotation (tdTreePointer *pParent, int *tbi) {
    tdTreePointer pChild, pGrandChild;
    pChild = (*pParent)->pRight;

    if (pChild->iBalance == -1) {                              /* RR-rotation */
		printf("RR\t Vanhempi: %d, lapsi: %d\n", (*pParent)->iNum, pChild->iNum);
        (*pParent)->pRight = pChild->pLeft;
        pChild->pLeft = *pParent;
        (*pParent)->iBalance = 0;
        (*pParent) = pChild;

    } else {                                                   /* RL-rotation */
        pGrandChild = pChild->pLeft;

        printf("RL\t Vanhempi: %d, lapsi: %d, lapsenlapsi: %d\n",
        (*pParent)->iNum, pChild->iNum, pGrandChild->iNum);

        pChild->pLeft = pGrandChild->pRight;
        (*pParent)->pRight = pGrandChild->pLeft;
        pGrandChild->pLeft = (*pParent);
        pGrandChild->pRight = pChild;

        switch (pGrandChild->iBalance) {
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
        *pParent = pGrandChild;
    }
    (*pParent)->iBalance = 0;
    *tbi = 0;
}

/****************************ADDING********************************************/
/* Move recursively along tree and compare current number of node to number
being added. Allocate memory when find node which == NULL. */

tdTree *addValue (tdTree *pParent, int num, int *tbi, int *height, int current) {
	tdTree *ptr = NULL;

    *height = *height < current ? current : *height;
    /* Height keeps track how many layers binary tree has. */
    current++;

	if (pParent == NULL) {
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
		pParent->pRight = addValue(pParent->pRight, num, tbi, height, current);

		if (*tbi) {
			switch (pParent->iBalance) {
				case 1:
					pParent->iBalance = 0;
					*tbi = 0;
					break;

				case 0:
					pParent->iBalance = -1;
					break;

				case -1:
					rightRotation(&pParent, tbi);
			}
		}

/*Recursively call function using pLeft pointer when current number < new num */

	} else if (num < pParent->iNum) {
		pParent->pLeft = addValue(pParent->pLeft, num, tbi,  height, current);

		if (*tbi) {
			switch (pParent->iBalance) {
				case -1:
					pParent->iBalance = 0;
					*tbi = 0;
					break;

				case 0:
					pParent->iBalance = 1;
					break;

				case 1:
					leftRotation(&pParent, tbi);
			}
		}
	} else {
		*tbi = 0;
        pParent->iCount += 1;
		printf("Luku %d on jo puussa, se on esiintynyt %d kertaa.\n", num, pParent->iCount);
	}
	return pParent;
}

/****************************SEARCHING*****************************************/
/* Move along tree comparing current node->iNum to number being seach. If
iNum > num go to right, if iNum < num go to left and if finds number return
pointer to that node. If reach node which is NULL it means there is no seached
number in tree and return NULL. */

tdTree *searchNumber(tdTree *pRoot, int num) {
	tdTree *ptr = pRoot;

	while (ptr != NULL)	 {
		if (num == ptr->iNum) {
			return ptr;

		} else if (num > pRoot->iNum) {
			ptr = ptr->pRight;

		} else if (num < pRoot->iNum) {
			ptr = ptr->pLeft;
		}
	}
	return NULL;
}

/****************************CLEARING******************************************/
/* Free nodes of tree one by one recursively from leaf node to root node. */

void clearTree(tdTree *pRoot) {
	if (pRoot != NULL) {
		clearTree(pRoot->pRight);
		clearTree(pRoot->pLeft);
		pRoot->pLeft = pRoot->pRight = NULL;
		free(pRoot);
	}
}

/* EOF */
