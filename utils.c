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
    filename[strlen(filename) - 1] = '\0';  /* Changes \n to '\0' so filename is correct.*/

	if ((pFile = fopen(filename, "r")) != NULL) { /* Check if file opening succees. */
		while (fgets(line, sizeof(line), pFile) != NULL) { /* Read file one line at the time. */
			/*printf("Luku: %s", line);*/

			if (strncmp("0", line, 1) == 0) {
				/* Check if string first character is 0 and then assume wanted number is 0 .*/
				temp = 1;
			}

			if (atoi(line) || temp) { /*Atoi("0") = 0 so temp is used to tell number is 0.*/
				if (temp) {
					num = 0;
					temp = 0;

				} else {
					num = atoi(line); /* When line is number but not 0 it's changed normally to integer. */
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

	} else { /* If file opening fails returns to menu with original root node. */
        perror("Tiedostonluku epäonnistui, "
         "ole hyvä ja tarkista että hakemasi tiedosto on olemassa.\n");
		return pRoot;
	}

	fclose(pFile); 										 /* Closes read file. */
	return ptr; 									 /* Return new root node. */
}

/****************************ASKING*NUMBER*************************************/
/*Ask number/numbers input, separator is space. Return pointer to numberlist.*/

char *askNumber() {
	char temp [255];
	char *pTemp = malloc(255 * sizeof(char)); /* Memory allcation to 255 char. */

    fgets(temp, sizeof(temp), stdin);
	strcpy(pTemp, temp);

	return pTemp;
}

/****************************GET*FILE******************************************/
char *getFileName() {
    char name[CHAR_MAX], *pName = malloc(sizeof(name));  /* Memory allcation. */

    printf("Anna kirjoitettavan tiedoston nimi: ");
    fgets(name, sizeof(name), stdin);
    name[strlen(name) - 1] = '\0'; /* Changes \n to '\0' so filename is correct.*/

	strcpy(pName, name); /* Copy string to pointer which is then returned. */
    return pName;
}


/* EOF */
