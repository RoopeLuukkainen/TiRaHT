#include "tree_operations.h"

/****************************OPSTIONS*STRUCT***************************/
/* Value = 1 if option is selected == it's ON and 0 == OFF */

struct Struct {
    short bConsol, bFile, bBuilding, bVertical;
};
typedef struct Struct tdOptions, *tdOptionsPointer;


/* Functions */
tdTree *addFromFile(tdTree *, int *, int *, int *, FILE*);
char *askNumber();
char *getFileName();
