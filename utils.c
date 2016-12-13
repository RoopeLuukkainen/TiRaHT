#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "printing.h"
#include "tree_operations.h"

/****************************SET*UP*OPTIONS************************************/
/* Initialize options at beginning of run. */

tdOptions *setUpOptions(tdOptions *pOpt) {
	tdOptions *tempOpt = NULL;
	if ((tempOpt = (tdOptions*)malloc(sizeof(tdOptions))) == NULL) { /*Memory allocation*/
		perror("Muistinvaraus epäonnistui );\n");
		exit(1);
	}

	tempOpt->bConsol = tempOpt->bBuilding = 1;
	tempOpt->bFile = tempOpt->bVertical = 0;

	pOpt = tempOpt;
	printOptions(pOpt);

	return pOpt;
}

/****************************FROM*FILE*ADDING**********************************/
/* Ask filename and read file. Numbers in file are added to the tree in same
order than they appear in file. */

tdTree *addFromFile(tdTree *pRoot, int *tbi, int *height, tdOptions *pOpt, FILE* pToFile) {
	tdTree *ptr = pRoot;
	FILE* pFile;
	char line[CHAR_MAX], filename[CHAR_MAX];
    int num = 0, temp = 0;

    printf("Anna luettavan tiedoston nimi: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strlen(filename) - 1] = '\0';

	if ((pFile = fopen(filename, "r")) != NULL) {
		while (fgets(line, sizeof(line), pFile) != NULL) {
			/*printf("Luku: %s", line);*/

			if (strncmp("0", line, 1) == 0) {
				temp = 1;

			}

			if (atoi(line) || temp) {
				if (temp) {
					num = 0;
					temp = 0;

				} else {
				num = atoi(line);

				}
				ptr = addValue(ptr, pOpt, num, tbi, height, 0);

				if (pOpt->bBuilding) {       	  /*Print building if set true*/
					if (pOpt->bConsol) {
						printf("%d:\n", num);
					}
					if (pOpt->bFile) {
						fprintf(pToFile, "%d:\n", num);
					}

					printController(ptr, pToFile, pOpt, height, 0);
				}
			}
		}

		if (pOpt->bFile) {
			fprintf(pToFile, "\n\n\n\n");
		}

		if (pOpt->bConsol) {
			printf("\n\n\n");
		}

	} else {
        perror("Tiedostonluku epäonnistui, "
         "ole hyvä ja tarkista että hakemasi tiedosto on olemassa.\n");
		return pRoot;
	}

	fclose(pFile);
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

/****************************GET*FILE******************************************/
char *getFileName() {
    char name[CHAR_MAX], *pName = malloc(sizeof(CHAR_MAX));

    printf("Anna kirjoitettavan tiedoston nimi: ");
    fgets(name, sizeof(name), stdin);
    name[strlen(name) - 1] = '\0';

	strcpy(pName, name);
    return pName;
}


/* EOF */
