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
	tdOptions *pOpt = NULL;
	char *pTemp =  NULL, *pFree = NULL, *pFilename;
    FILE* pToFile = NULL;
	int iAddSel, iMenuSel, iNum, temp = 0, tbi = 0, iHeight = 0, fileChange = 0;
	/*tbi = tree balance indicator*/

	pOpt = setUpOptions(pOpt);

    do {
        iMenuSel = mainMenu();
		switch (iMenuSel) {
			case 0:                                            /*Clearing tree*/
			case 4:
				if (pRoot != NULL) {
					clearTree(pRoot);
					pRoot = NULL;
					printf("%s\n", "Muisti vapautettu puusta!");
				}
				iHeight = 0;
				break;

			case 1:                                            /*Adding number*/
				iAddSel = addMenu();

				if (iAddSel == 1) {
					pRoot = addFromFile(pRoot, &tbi, &iHeight, pOpt, pToFile);

				} else {

					printf("Anna lisättävät luvut: ");
					pTemp = askNumber();
					pFree = strtok(pTemp, " ");
					do {

						if (strncmp("0", pTemp, 1) == 0) {
							temp = 1;
						}

						if (atoi(pTemp) || temp) {
							if (temp) {
								iNum = 0;
								temp = 0;

							} else {
								iNum = atoi(pTemp);
							}
							pRoot = addValue(pRoot, pOpt, iNum, &tbi, &iHeight, 0);

							if (pOpt->bBuilding) {/*Print building if set true*/
				                if (pOpt->bConsol) {
				                    printf("%d:\n", iNum);
				                }
				                if (pOpt->bFile) {
				                    fprintf(pToFile, "%d:\n", iNum);
				                }

				                printController(pRoot, pToFile, pOpt, &iHeight, 0);
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

                } else if (!(pOpt->bFile) && !(pOpt->bConsol)) {
                    printf("Valitse ensin mihin printataan.!\n");
					break;
                }

                printController(pRoot, pToFile, pOpt, &iHeight, 0);
				printf("\n");
				break;

			case 3:                                                /*Searching*/
				printf("Anna etsittävät luvut: ");
				pTemp = askNumber();
				pFree = strtok(pTemp, " ");
				do {
					if (strncmp("0", pTemp, 1) == 0) {
						temp = 1;
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
                optionsMenu(&pOpt);

                fileChange = pOpt->bFile == 1 ? 0 : 1;

                if (pOpt->bFile && !fileChange) {
                    pFilename = getFileName();

                    if ((pToFile = fopen(pFilename, "w")) == NULL) {  /*Open file for writing*/
                        perror("Opening the file failed.\n");
                        pToFile = NULL;
                    }
					fprintf(pToFile, "BINÄÄRIPUU\n");
                }
				if (!(pOpt->bFile)) {
					if (pToFile) {
						fclose(pToFile);
						pToFile = NULL;
						free(pFilename);
					}
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

	free(pOpt);

	printf("Kiitos ohjelman käytöstä.\n");
	return 0;
}

/* EOF */
