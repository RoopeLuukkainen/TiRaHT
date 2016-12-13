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
	char *pTemp =  NULL, *pFree = NULL, *pFilename;
    FILE* pToFile = NULL;
	int iAddSel, iMenuSel = 5, options = 111, iNum, temp = 0, tbi = 0, iHeight = 0,
	fileChange = 0, building = 1, vertical = 1, toFile = 0, toConsol = 1;
    /*tbi = tree balance indicator*/
    /* Options are toFile 1***, toConsol *1**, building **1*, vertical ***1 */

    /*printf("%d %d %d %d\n", options%10, options%100, options%1000, options%10000);*/

    do {
        iMenuSel = mainMenu();
		switch (iMenuSel) {
			case 0:                                            /*Clearing tree*/
			case 4:
				if (pRoot != NULL) {
					clearTree(pRoot);
					pRoot = NULL;
					printf("%s\n", "Muisti vapautettu!");
				}
				iHeight = 0;
				break;

			case 1:                                            /*Adding number*/
				iAddSel = addMenu();

				if (iAddSel == 1) {
					pRoot = addFromFile(pRoot, &tbi, &iHeight, &options, pToFile);

				} else {

					printf("Anna lisättävät luvut: ");
					pTemp = askNumber();
					pFree = pTemp;

					do {
						if (strncmp("0", pTemp, 1) == 0) {
							temp = 1;
							printf("%s %s\n", "PÖÖ", pTemp);
						}

						if (atoi(pTemp) || temp) {
							if (temp) {
								iNum = 0;
								temp = 0;

							} else {
								iNum = atoi(pTemp);
							}
							pRoot = addValue(pRoot, iNum, &tbi, &iHeight, 0);

							if (building) {       /*Print building if set true*/
				                if (toConsol) {
				                    printf("%d:\n", iNum);
				                }
				                if (toFile) {
				                    fprintf(pToFile, "%d:\n", iNum);
				                }

				                printController(pRoot, pToFile, toConsol, vertical, &iHeight, 0);
				            }
						}

						pTemp = strtok(NULL, " ");

					} while (pTemp != NULL);

					if (pFree) {
						free(pFree);
					}
				}
				break;

			case 2:                                                 /*Printing*/
				if (pRoot == NULL) {
					printf("Puu on tyhjä!\n");
					break;

                } else if (!toFile && !toConsol) {
                    printf("Valitse ensin mihin printataan.!\n");
					break;
                }

                printController(pRoot, pToFile, toConsol, vertical, &iHeight, 0);
				printf("\n");
				break;

			case 3:                                                /*Searching*/
				printf("Anna etsittävät luvut: ");
				pTemp = askNumber();
				pFree = strtok(pTemp, " ");

				do {
					if (strncmp("0", pTemp, 1) == 0) {
						temp = 1;
						printf("%s %s\n", "PÖÖ", pTemp);
					}

					if (atoi(pTemp) || temp) {
						if (temp) {
							iNum = 0;
							temp = 0;

						} else {
							iNum = atoi(pTemp);
						}
						ptr = searchNumber(pRoot, iNum);

						if (ptr == NULL) {
							printf("Lukua %d ei löytynyt puusta.\n\n", iNum);

						} else {
							printf("\n%d löytyi binääripuusta. Se on esiintynyt: %d kertaa.\n\n",
							 ptr->iNum, ptr->iCount);

						}
					}

					pTemp = strtok(NULL, " ");

				} while (pTemp != NULL);

				printf("\n");
				if (pFree) {
					free(pFree);
				}
				break;

            case 5:
                options = optionsMenu();
                vertical = options % 10 == 1 ? 1 : 0;
                building = options % 100 >= 10 ? 1 : 0;
                toConsol = options % 1000 >= 100 ? 1 : 0;
                toFile = options % 10000 >= 1000 ? 1 : 0;

                fileChange = toFile == 1 ? 0 : 1;

                if (toFile && !fileChange) {
                    pFilename = getFileName();

printf("%s\n", pFilename);

                    if ((pToFile = fopen(pFilename, "w")) == NULL) {  /*Open file for writing*/
                        perror("Opening the file failed.\n");
                        pToFile = NULL;
                    }
                }
				if (!toFile) {
					pToFile = NULL;
				}

                break;

			default:
				printf("Tuntematon valinta.\n");
				break;
		}

	} while (iMenuSel != 0);

    if (pToFile) {
        fclose(pToFile);
		free(pFilename);
    }

	printf("Kiitos ohjelman käytöstä.\n");
	return 0;
}

/* EOF */
