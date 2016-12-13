#include "utils.h"
#include "tree_operations.h"

int mainMenu();
int addMenu();
void printOptions(tdOptions *);
void optionsMenu(tdOptionsPointer *);
void printTree(tdTree *, FILE *, tdOptions *, int);
void printLines(FILE *, tdOptions *, int *, int, int);
void printTab(int, FILE *, tdOptions *);
void printLayer(tdTree *, FILE *, tdOptions *, int *, int, int, int);
void printController(tdTree *, FILE *, tdOptions *, int *, int);
