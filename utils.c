#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "printing.h"
#include "tree_operations.h"

/****************************FROM*FILE*ADDING**********************************/
/* Ask filename and read file. Numbers in file are added to the tree in same
order than they appear in file. */

tdTree *addFromFile(tdTree *pRoot, int *tbi, int *height, int *options, FILE* pToFile) {
	tdTree *ptr = pRoot;
	FILE* pFile;
	char line[CHAR_MAX], filename[CHAR_MAX];
    int building, vertical, toConsol, num = 0, temp = 0;

    vertical = *options % 10 == 1 ? 1 : 0;
    building = *options % 100 >= 10 ? 1 : 0;
    toConsol = *options % 1000 >= 100 ? 1 : 0;


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
				ptr = addValue(ptr, num, tbi, height, 0);

				if (building) {       /*Print building if set true*/
					if (toConsol) {
						printf("%d:\n", num);
					}
					if (pToFile) {
						fprintf(pToFile, "%d:\n", num);
					}

					printController(ptr, pToFile, toConsol, vertical, height, 0);
				}
			}
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
