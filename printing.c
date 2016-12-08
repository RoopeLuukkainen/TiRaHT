#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "utils.h"
#include "tree_operations.h"

/****************************MAIN*MENU*****************************************/
/*Return number of selection.*/

int mainMenu() {
	int selection;
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
	selection = atoi(temp);
	printf("\n");

	return selection;
}


/****************************ADDING*MENU***************************************/
/*Return adding type selection.*/

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
	printf("Sel: %d\n", sel);

	return sel;
}

/****************************PRINTING*MENU*************************************/
/*Return printing type selections.*/

int optionsMenu() {
	int sel;
	char result[5], toFile[CHAR_MAX], toConsol[CHAR_MAX], building[CHAR_MAX],
    vertical[CHAR_MAX];

    sel = 0000; strcpy(result, "0000");

    printf("Vastausformaatti: [Y/N] tai [K/E] /tai [1/0]\n\n");

    printf("Tulostetaanko tiedostoon? ");
    fgets(toFile, sizeof(toFile), stdin);

    if (strcmp(toFile, "1") || strcmp(toFile, "Y") || strcmp(toFile, "K") ||
    strcmp(toFile, "y") || strcmp(toFile, "k")) {

        result[0] = '1';
    }

    printf("Tulostetaanko konsoliin? ");
    fgets(toConsol, sizeof(toConsol), stdin);

    if (strcmp(toConsol, "1") || strcmp(toConsol, "Y") || strcmp(toConsol, "K")
    || strcmp(toConsol, "y") || strcmp(toConsol, "k")) {

        result[1] = '1';
    }

    printf("Tulostetaanko rakentuminen? ");
	fgets(building, sizeof(building), stdin);

    if (strcmp(building, "1") || strcmp(building, "Y") || strcmp(building, "K")
    || strcmp(building, "y") || strcmp(building, "k")) {

        result[2] = '1';
    }

    printf("Tulostetaanko pystyy(K/Y/1) vai vaakaan (E/N/0)");
    fgets(vertical, sizeof(vertical), stdin);

    if (strcmp(vertical, "1") || strcmp(vertical, "Y") || strcmp(vertical, "K")
    || strcmp(vertical, "y") || strcmp(vertical, "k")) {

        result[3] = '1';
    }

	sel = (atoi(result));
	printf("Sel: %d\n", sel);
    printf("\n");

	return sel;
}

/****************************PRINTING****************************************************/
/*Tulostaa jokaisen solmun arvon järjestyksessä: oikea, keski ja vasen.*/

void printTree(tdTree *pRoot, FILE* toFile, int i) {
	i++;
    printf("%s %d\n", toFile, toFile);
	if (pRoot != NULL) {
		printTree(pRoot->pRight, i);

		printf("%*d", i*6, pRoot->iNum);
		if (pRoot->iBalance == -1) {
			printf("%c%c%c%c%c\n", 0342, 0201, 0273, 0302, 0271);

		} else if (pRoot->iBalance == 1) {
			printf("%c%c\n", 0302, 0271);

		} else {
			printf("%c%c%c\n", 0342, 0201, 0260);
		}

        if (toFile) {
            fprintf(toFile, "%*d", i*6, pRoot->iNum);
            if (pRoot->iBalance == -1) {
                fprintf(toFile, "%c%c%c%c%c\n", 0342, 0201, 0273, 0302, 0271);

            } else if (pRoot->iBalance == 1) {
                fprintf(toFile, "%c%c\n", 0302, 0271);

            } else {
                fprintf(toFile, "%c%c%c\n", 0342, 0201, 0260);
            }
        }

		printTree(pRoot->pLeft, i);
	}
}
