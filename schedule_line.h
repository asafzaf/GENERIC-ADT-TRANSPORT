#ifndef __SCHEDULE_LINE__
#define __SCHEDULE_LINE__
#include "linked_list.h"
#include "pr2ex5.h"
#include <stdlib.h>
#include <string.h>

typedef struct schedule_line *scheduleline;

typedef enum
{
    SCHEDULE_LINE_SUCCESS,
    SCHEDULE_LINE_FAIL,
    SCHEDULE_LINE_BAD_ARGUMENTS,
    SCHEDULE_LINE_OUT_OF_MEMORY,
    SCHEDULE_LINE_NULL_ARG,
    
    /* add here more errorcodes */
} ScheduleLineResult;

scheduleline schedule_line_create(ScheduleLineType type, int number, const char *description, double price);
ScheduleLineResult schedule_line_destroy(scheduleline line);
ScheduleLineResult schedule_line_get_stations(ListElement elem, LinkedList *stations);
ScheduleLineResult schedule_line_add_station(ListElement elem1, ListElement elem2);
ScheduleLineResult schedule_line_get_details(scheduleline line,
                                             ScheduleLineType *type /* out */,
                                             int *number /* out */,
                                             char **description /* out */,
                                             double *price /* out */);

ListElement copyListLine(ListElement elem);
void freeListLine(ListElement elem);
void printListLine(FILE *file, ListElement elem);
int match_by_number(ListElement list, KeyForListElement elem );
int is_price_valid(float price);
void printstat(scheduleline line);

#endif
