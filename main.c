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
	char *pTemp =  NULL, *pFree = NULL, *filename;
    FILE* pToFile = NULL;
	int addSel, menuSel = 5, options, num, tbi = 0, fileChange = 0,
    building = 1, vertical = 1, toFile = 1, toConsol = 1;
    /*tbi = tree balance indicator*/
    /* Options are toFile 1***, toConsol *1**, building **1*, vertical ***1 */

    /*printf("%d %d %d %d\n", options%10, options%100, options%1000, options%10000);*/
    do {
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
					pRoot = addFromFile(pRoot, &tbi, &options, pToFile);

				} else {

					printf("Anna lisättävät luvut: ");
					pTemp = askNumber();
					pFree = strtok(pTemp, " ");

					do {
						num = atoi(pTemp);
						pRoot = addValue(pRoot, num, &tbi);
						pTemp = strtok(NULL, " ");

                        if (building) { /*Print building if set true*/
                            printController(pRoot, pToFile, toConsol, vertical, 0);
                        }


					} while (pTemp != NULL);
					free(pFree);
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

                printController(pRoot, pToFile, toConsol, vertical, 0);
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
                vertical = options % 10 == 1 ? 1 : 0;
                building = options % 100 >= 10 ? 1 : 0;
                toConsol = options % 1000 >= 100 ? 1 : 0;
                toFile = options % 10000 >= 1000 ? 1 : 0;

                fileChange = toFile == 1 ? 0 : 1;

                if (toFile && !fileChange) {
                    filename = getFileName();

printf("%s\n", filename);

                    if ((pToFile = fopen(filename, "w")) == NULL) {  /*Open file for writing*/
                        perror("Opening the file failed.\n");
                        pToFile = NULL;
                    }
                }

                break;

			default:
				printf("Tuntematon valinta.\n");
				break;
		}

        menuSel = mainMenu();

	} while (menuSel != 0);

    if (pToFile) {
        fclose(pToFile);
    }
	printf("Kiitos ohjelman käytöstä.\n");
	return 0;
}

/* EOF */
