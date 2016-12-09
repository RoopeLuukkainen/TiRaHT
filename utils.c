#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "printing.h"
#include "tree_operations.h"

/****************************PRINT*CONTROLLER**********************************/
void printController(tdTree *pRoot, FILE* pToFile, int toConsol, int vertical, int i) {
    if (vertical) {

    } else {
        printTree(pRoot, pToFile, toConsol, i);
    }
}

/****************************FROM*FILE*ADDING**********************************/
/* Ask filename and read file. Numbers in file are added to the tree in same
order than they appear in file. */

tdTree *addFromFile(tdTree *pRoot, int *tbi, int *options, FILE* pToFile) {
	tdTree *ptr = pRoot;
	FILE* pFile;
	char line[CHAR_MAX], filename[CHAR_MAX];
    int building, vertical, toConsol;

    vertical = *options % 10 == 1 ? 1 : 0;
    building = *options % 100 >= 10 ? 1 : 0;
    toConsol = *options % 1000 >= 100 ? 1 : 0;

    printf("Anna luettavan tiedoston nimi: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strlen(filename) - 1] = '\0';

	if ((pFile = fopen(filename, "r")) != NULL) {
		while (fgets(line, sizeof(line), pFile) != NULL) {
			printf("%s", line);
			ptr = addValue(ptr, atoi(line), tbi); /* CHECKING THE VALUES!!! */

            if (building) {                      /*Print building if set true*/
                printController(pRoot, pToFile, toConsol, vertical, 0);
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
