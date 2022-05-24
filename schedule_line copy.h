#ifndef __SCHEDULE_LINE__
#define __SCHEDULE_LINE__
#include "linked_list.h"
#include "pr2ex5.h"
#include <stdlib.h>
#include <string.h>

typedef struct schedule_line *scheduleline;

ListElement copyListLine(ListElement elem);
void freeListLine(ListElement elem);
void printListLine(FILE *file, ListElement elem);
int match_by_number(ListElement list, ListElement elem );
int is_price_valid(float price);


#endif
