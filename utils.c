#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "printing.h"
#include "tree_operations.h"

/****************************FROM*FILE*ADDING**********************************/
/* Ask filename and read file. Numbers in file are added to the tree in same
order than they appear in file. */

tdTree *addFromFile(tdTree *pRoot, int *tbi, int *options) {
	tdTree *ptr = pRoot;
	FILE* pFile, pToFile;
	char line[CHAR_MAX], filename[CHAR_MAX], toFile[CHAR_MAX];

    printf("Anna luettavan tiedoston nimi: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strlen(filename) - 1] = '\0';

    if ((*options % 10000) >= 1000) {
        printf("Anna kirjoitettavan tiedoston nimi: ");
        fgets(toFile, sizeof(toFile), stdin);
        toFile[strlen(toFile) - 1] = '\0';

        if ((pToFile = fopen(toFile, "w")) == NULL) {  /*Open file for writing*/
            perror("Opening the file failed.\n");
            return pRoot;
        }
    }

	if ((pFile = fopen(filename, "r")) != NULL) {
		while (fgets(line, sizeof(line), pFile) != NULL) {
			printf("%s", line);
			ptr = addValue(ptr, atoi(line), tbi); /* CHECKING THE VALUES!!! */

            if ((*options % 100) >= 10) {         /*Print building if set true*/
                if ((*options % 10) == 1) {
                 /*Check selection for vertical or horizontal printing*/
                    /* VERTICAL PRINT */
                } else {
                    printTree(pRoot, pToFile, 0);
                }
            }
		}

	} else {
		perror("Reading the file failed.\n");
		return pRoot;
	}

	fclose(pFile);
    fclose(pToFile);
	return ptr;
}

/****************************ASKING*NUMBER*************************************/
/*Ask number/numbers input, separator is space. Return pointer to numberlist.*/

char *askNumber() {
	char temp [255];
	char *pTemp = malloc(255 * sizeof(char));

    fgets(temp, sizeof(temp), stdin);
	strcpy(pTemp, temp);

	return pTemp;
}


/* EOF */
