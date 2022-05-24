#include "linked_list.h"
#include <stdlib.h>
#include <string.h>

typedef struct schedule_station_s *ScheduleStation;

typedef enum
{
    SCHEDULE_STATION_SUCCESS,
    SCHEDULE_STATION_FAIL,
    SCHEDULE_STATION_BAD_ARGUMENTS,
    SCHEDULE_STATION_OUT_OF_MEMORY,
    SCHEDULE_STATION_NULL_ARG,
    /* You may add here more errorcodes */
} ScheduleStationResult;

ListElement copyListStation(ListElement elem);
void freeListStation(ListElement elem);
void printListStation(FILE *file, ListElement elem);
