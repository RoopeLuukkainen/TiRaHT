#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#include "utils.h"
#include "tree_operations.h"

/****************************MAIN*MENU*****************************************/
/* Return number of menu selection. */

int mainMenu() {
	int selection = -1;
	char temp[CHAR_MAX];

	printf ("Valitse toiminto valikosta:\n"
			"1) Lisää luku(ja) puuhun\n"
			"2) Tulosta puu\n"
			"3) Etsi luku\n"
			"4) Tyhjennä puu\n"
            "5) Säädä asetuksia\n"
			"0) Lopeta\n"
			"Valintasi: ");

	fgets(temp, sizeof(temp), stdin);

	if (strncmp("0", temp, 1) == 0) {
		selection = 0;

	} else if (atoi(temp)) {
		selection = atoi(temp);

	} else {
		selection = -1;
	}
	printf("\n");

	return selection;
}


/****************************ADDING*MENU***************************************/
/* Return adding type selection. */

int addMenu() {
	int sel = 1;
	char temp[CHAR_MAX];

	printf ("Valitse lisäys metodi:\n"
			"1) Lisää luvut tiedostosta\n"
			"0) Lisää vapaa valintaisia lukuja\n"
			"Valintasi: ");

	fgets(temp, sizeof(temp), stdin);
	/*sel = (atoi(temp) == 1) ? 1 : 0;*/
	sel = (atoi(temp));
	return sel;
}

/****************************PRINTING*MENU*************************************/
/* Return printing type selections. */

int optionsMenu() {
	int sel;
	char result[5], toFile[CHAR_MAX], toConsol[CHAR_MAX], building[CHAR_MAX],
    vertical[CHAR_MAX];

    sel = 0000; strcpy(result, "0000");

    printf("Vastausformaatti: [Y/N] tai [K/E] /tai [1/0]\n\n");

    printf("Tulostetaanko tiedostoon? ");
    fgets(toFile, sizeof(toFile), stdin);

    if (toFile[0] == '1' || toFile[0] == 'Y' || toFile[0] == 'y' ||
    toFile[0] == 'K' || toFile[0] == 'k') {

        result[0] = '1';
    }

    printf("Tulostetaanko konsoliin? ");
    fgets(toConsol, sizeof(toConsol), stdin);

    if (toConsol[0] == '1' || toConsol[0] == 'Y' || toConsol[0] == 'y' ||
    toConsol[0] == 'K' || toConsol[0] == 'k') {

        result[1] = '1';
    }

    printf("Tulostetaanko rakentuminen? ");
	fgets(building, sizeof(building), stdin);

    if (building[0] == '1' || building[0] == 'Y' || building[0] == 'y' ||
    building[0] == 'K' || building[0] == 'k') {

        result[2] = '1';
    }

    printf("Tulostetaanko pystyy (K) vai vaakaan (E)? ");
    fgets(vertical, sizeof(vertical), stdin);

    if (vertical[0] == '1' || vertical[0] == 'Y' || vertical[0] == 'y' ||
    vertical[0] == 'K' || vertical[0] == 'k') {

        result[3] = '1';
    }

	sel = (atoi(result));
	printf("Sel: %d\n", sel);
    printf("\n");

	return sel;
}

/****************************PRINTING*HORIZONTAL*******************************/
/* Print nodes of binary tree postorder, right, node itself and left. */

void printTree(tdTree *pRoot, FILE* pToFile, int toConsol, int i) {
	i++;
	if (pRoot != NULL) {
		printTree(pRoot->pRight, pToFile, toConsol, i);

        if (toConsol) {

    		printf("%*d", i*6, pRoot->iNum);
    		if (pRoot->iBalance == -1) {
    			printf("%c%c%c%c%c\n", 0342, 0201, 0273, 0302, 0271);

    		} else if (pRoot->iBalance == 1) {
    			printf("%c%c\n", 0302, 0271);

    		} else {
    			printf("%c%c%c\n", 0342, 0201, 0260);
    		}
        }

        if (pToFile) {
            fprintf(pToFile, "%*d", i*6, pRoot->iNum);
            if (pRoot->iBalance == -1) {
                fprintf(pToFile, "%c%c%c%c%c\n", 0342, 0201, 0273, 0302, 0271);

            } else if (pRoot->iBalance == 1) {
                fprintf(pToFile, "%c%c\n", 0302, 0271);

            } else {
                fprintf(pToFile, "%c%c%c\n", 0342, 0201, 0260);
            }
        }

		printTree(pRoot->pLeft, pToFile, toConsol, i);

	} /*else {
		if (toConsol) {
			printf("%*s\n", i*6 + 1, "NULL");
		}
	} */
}


/****************************PRINT*TABS****************************************/
void printTab(int tab) {
	int i;
	for(i = 0; i < tab; i++) {
		printf("\t");
	}
}

/****************************PRINT*LINES***************************************/

void printLines(FILE *pToFile, int toConsol, int *height, int layer, int lineCount) {
	int i, k, j;

	if (pToFile) {
		for(i = 0; i < (lineCount-1)/2; i++) {
			fprintf(pToFile, "\t");
		}

		if(layer < *height) {

			for(j = 0; j < pow(2,layer); j++) {
				fprintf(pToFile, "  %c%c%c", 0342, 0224, 0217);			/* ┏ */		/*vasen reuna*/

				for(k = 0; k <= 4 * lineCount + 1; k++) {								/*väliviiva*/
					fprintf(pToFile, "%c%c%c", 0342, 0224, 0201); /* ━ */
				}

				fprintf(pToFile, "%c%c%c", 0342, 0224, 0273); /* ┻ */			/*keskimmäinen*/

				for(k = 0; k <= 4 * lineCount + 1; k++) {								/*väliviiva*/
					fprintf(pToFile, "%c%c%c", 0342, 0224, 0201); /* ━ */
				}

				fprintf(pToFile, "%c%c%c", 0342, 0224, 0223);			/* ┓ */		/*oikea reuna*/

				for(i = 0; i <= lineCount; i++) {
					fprintf(pToFile, "\t");
				}
			}
		}
	}

	if (toConsol) {
		for(i = 0; i < (lineCount-1)/2; i++) {
			printf("\t");
		}

		if(layer + 1 < *height) {

			for(j = 0; j < pow(2,layer); j++) {
				printf("  %c%c%c", 0342, 0224, 0217);			/* ┏ */						/*vasen reuna*/

				for(k = 0; k <= 4 * lineCount + 1; k++) {								/*väliviiva*/
					printf("%c%c%c", 0342, 0224, 0201); /* ━ */
				}

				printf("%c%c%c", 0342, 0224, 0273); /* ┻ */										/*keskimmäinen*/

				for(k = 0; k <= 4 * lineCount + 1; k++) {								/*väliviiva*/
					printf("%c%c%c", 0342, 0224, 0201); /* ━ */
				}

				printf("%c%c%c", 0342, 0224, 0223);			/* ┓ */										/*oikea reuna*/

				for(i = 0; i <= lineCount; i++) {
					printf("\t");
				}
			}
		}
	}
}

/****************************PRINTING*LAYER*******************************/
/* Print one layer of binary tree at the time. Starts at layer 0, the root. */

void printLayer(tdTree *pParent, FILE *pToFile, int toConsol, int *height, int layer, int current, int tabCount) {
	if (pParent && current == layer) {
		if (pToFile) {
    		fprintf(pToFile, "%d", pParent->iNum);

			if (pParent->iBalance == -1) {
				fprintf(pToFile, "%c%c%c%c%c\t", 0342, 0201, 0273, 0302, 0271);

			} else if (pParent->iBalance == 1) {
				fprintf(pToFile, "%c%c\t", 0302, 0271);

			} else {
				fprintf(pToFile, "%c%c%c\t", 0342, 0201, 0260);
			}
		}

		if (toConsol) {
			printTab(tabCount);

			printf("%d", pParent->iNum);

			if (pParent->iBalance == -1) {
				printf("%c%c%c%c%c\t\t", 0342, 0201, 0273, 0302, 0271);

			} else if (pParent->iBalance == 1) {
				printf("%c%c\t\t", 0302, 0271);

			} else {
				printf("%c%c%c\t\t", 0342, 0201, 0260);
			}

			printTab(tabCount);
		}
	} else if (pParent && current < layer) {
        printLayer(pParent->pLeft, pToFile, toConsol, height, layer, current + 1, tabCount);
        printLayer(pParent->pRight, pToFile, toConsol, height, layer, current + 1, tabCount);

	} else if (!pParent && current == layer) {
		if (pToFile) {
			fprintf(pToFile, "%s\t", "NULL");
		}

		if (toConsol) {
			printTab(tabCount);
			printf("%s\t\t", "NULL");
			printTab(tabCount);
		}

	} else if (!pParent && current < layer) {
		if (pToFile) {
			fprintf(pToFile, "\t\t\t\t");
		}

		if (toConsol) {
			printf("|\t\t\t\t|");
		}
	}
}

/****************************PRINT*CONTROLLER**********************************/
void printController(tdTree *pRoot, FILE* pToFile, int toConsol, int vertical, int *height, int i) {
    if (vertical) {
		int layer, help;
		for (layer = 0; layer < *height; layer++) {
			help = (int)pow(2.0, (double)((*height)-layer)) - 1;
        	printLayer(pRoot, pToFile, toConsol, height, layer, i, help);

			if (toConsol) {
				printf("\n");
			}
			if (pToFile) {
				fprintf(pToFile, "\n");
			}

			printLines(pToFile, toConsol, height, layer, help);

			if (toConsol) {
				printf("\n\n");
			}
			if (pToFile) {
				fprintf(pToFile, "\n\n");
			}
		}
    } else {
        printTree(pRoot, pToFile, toConsol, i);
        if (toConsol) {
            printf("_______________________________________________________\n");
        }
        if (pToFile) {
            fprintf(pToFile, "_______________________________________________________\n");
        }
    }
}

/* EOF */
