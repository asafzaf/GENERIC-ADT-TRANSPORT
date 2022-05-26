#ifndef __station__
#define __station__
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
int compareStationsByName(ListElement elem1, ListElement elem2);
int matchStationsByName(ListElement elem, KeyForListElement key);
int compareStationByTime(ListElement elem1, ListElement elem2);
//============EX4 functions============//
ScheduleStation schedule_station_create(const char *station, int time);
ScheduleStationResult schedule_station_destroy(ScheduleStation station);
ScheduleStationResult schedule_station_get_name(ScheduleStation station, char **station_name);
ScheduleStationResult schedule_station_get_time(ScheduleStation station, int *time);



#endif