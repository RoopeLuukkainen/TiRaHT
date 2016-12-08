#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "utils.h"
#include "printing.h"
#include "tree_operations.h"

/****************************MAIN**********************************************/

int main(void) {
	tdTree *pRoot = NULL, *ptr = NULL;
	char *pTemp =  NULL, *pFree = NULL;
	int addSel, menuSel, options = 1111, num, tbi = 0;
    /*tbi = tree balance indicator*/
    /* Options are toFile, toConsol, building, vertical */

    /*printf("%d %d %d %d\n", options%10, options%100, options%1000, options%10000);*/
	do {
		menuSel = mainMenu();

		switch (menuSel) {
			case 0:                                            /*Clearing tree*/
			case 4:
				if (pRoot != NULL) {
					clearTree(pRoot);
					pRoot = NULL;
				}
				break;

			case 1:                                            /*Adding number*/
				addSel = addMenu();

				if (addSel == 1) {
					pRoot = addFromFile(pRoot, &tbi, &options);

				} else {
					printf("Anna lisättävät luvut: ");
					pTemp = askNumber();
					pFree = strtok(pTemp, " ");

					do {
						num = atoi(pTemp);
						pRoot = addValue(pRoot, num, &tbi);
						pTemp = strtok(NULL, " ");

                        if ((options % 100) >= 10 ) {
                            /*Print building if set true*/
                            printTree(pRoot, 0);
                        }


					} while (pTemp != NULL);
					free(pFree);
				}
				break;

			case 2:                                                 /*Printing*/
				if (pRoot == NULL) {
					printf("Puu on tyhjä!\n");
					break;
				}
				printTree(pRoot, 0);
				printf("\n");
				break;

			case 3:                                                /*Searching*/
				printf("Anna etsittävät luvut: ");
				pTemp = askNumber();
				pFree = strtok(pTemp, " ");

				do {
					num = atoi(pTemp);
					ptr = searchNumber(pRoot, num);

					if (ptr == NULL) {
						printf("Lukua %d ei löytynyt puusta.\n", num);

					} else {
						printf("%d löytyi binääripuusta.\n", ptr->iNum);

					}
					pTemp = strtok(NULL, " ");

				} while (pTemp != NULL);

				printf("\n");
				free(pFree);
				break;

            case 5:
                options = optionsMenu();
                break;

			default:
				printf("Tuntematon valinta.\n");
				break;
		}
	} while (menuSel != 0);

	printf("Kiitos ohjelman käytöstä.\n");
	return 0;
}

/* EOF */
