#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "utils.h"
#include "printing.h"
#include "tree_operations.h"

/****************************MAIN**********************************************/
/* Initialize variables and loops menu until 0 is selected. When it is selected
 free memory, close possibly opened file and closes. */

int main(void) {
	tdTree *pRoot = NULL, *ptr = NULL;
	tdOptions *pOpt = NULL;
	char *pTemp =  NULL, *pFree = NULL, *pFilename;
    FILE* pToFile = NULL;
	int iAddSel, iMenuSel, iNum, temp = 0, tbi = 0, iHeight = 0, fileChange = 0;
	/*tbi = tree balance indicator*/

	pOpt = setUpOptions(pOpt);										/* Optios */

    do {
        iMenuSel = mainMenu();
		switch (iMenuSel) {
			case 0:                                            /*Clearing tree*/
			case 4:		  /* 4 is only clear tree, 0 means also quit program. */
				if (pRoot != NULL) {
					clearTree(pRoot);
					pRoot = NULL;
					printf("%s\n", "Muisti vapautettu puusta!");
				}
				iHeight = 0; /* When tree is emptied also it's height is zeroed. */
				break;

			case 1:                                            /*Adding number*/
				iAddSel = addMenu();

				if (iAddSel == 1) {
					pRoot = addFromFile(pRoot, &tbi, &iHeight, pOpt, pToFile);

				} else {

					printf("Anna lisättävät luvut: ");
					pTemp = askNumber();
					pFree = strtok(pTemp, " "); /* pFree is cathed to free memory afterwards.
					 Also splits pTemp to tokens separator is spacebar. */
					do {

						if (strncmp("0", pTemp, 1) == 0) {
							/* Check if string first character is 0 and then assume wanted number is 0 .*/
							temp = 1;
						}

						if (atoi(pTemp) || temp) { /*Atoi("0") = 0 so temp is used to tell number is 0.*/
							if (temp) {
								iNum = 0;
								temp = 0;

							} else {
								iNum = atoi(pTemp);  /* When pTemp is number but not 0 it's changed normally to integer. */
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

						pTemp = strtok(NULL, " "); /* pTemp goes to next token using strtok. */

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
				pFree = strtok(pTemp, " "); /* pFree is cathed to free memory afterwards.
				Also splits pTemp to tokens separator is spacebar. */
				do {
					if (strncmp("0", pTemp, 1) == 0) {
						/* Check if string first character is 0 and then assume wanted number is 0 .*/
						temp = 1;
					}

					if (atoi(pTemp) || temp) { /*Atoi("0") = 0 so temp is used to tell number is 0.*/
						if (temp) {
							iNum = 0;
							temp = 0;

						} else {
							iNum = atoi(pTemp); /* When pTemp is number but not 0 it's changed normally to integer. */
						}
						ptr = searchNumber(pRoot, iNum);

						if (ptr == NULL) { /* When there is no pointer it means there is no number. */
							printf("Lukua %d ei löytynyt puusta.\n\n", iNum);

						} else {
							printf("\n%d löytyi binääripuusta. Se on esiintynyt: %d kertaa.\n\n",
							 ptr->iNum, ptr->iCount);

						}
					}

					pTemp = strtok(NULL, " "); /* pTemp goes to next token using strtok. */

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

                    if ((pToFile = fopen(pFilename, "w")) == NULL) {
						/*Open file for writing also wipes current one to empty. */
                        perror("Opening the file failed.\n");
                        pToFile = NULL;
                    }
					fprintf(pToFile, "BINÄÄRIPUU\n");
					fclose(pToFile);

					if ((pToFile = fopen(pFilename, "a")) == NULL) {
						/*Open file for appending makes reading file same time possible. */
						perror("Opening the file failed.\n");
						pToFile = NULL;
					}

                }
				if (!(pOpt->bFile)) { /* If file writing is OFF there is no need */
					if (pToFile) { /* for file pointer. */
						fclose(pToFile);
						pToFile = NULL;
						free(pFilename);
					}
				}

                break;

			default: /* In case of invalid or unidentified selection. For example alphabets. */
				printf("Tuntematon valinta.\n");
				break;
		}

	} while (iMenuSel != 0); /* Loops menu until 0 is selected. */

    if (pToFile) {
		fclose(pToFile);
		free(pFilename);
    }

	free(pOpt);

	printf("Kiitos ohjelman käytöstä.\n");
	return 0;
}

/* EOF */
