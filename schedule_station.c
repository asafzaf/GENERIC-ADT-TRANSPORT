
/*
========ASSIGNED BY======== 
  Rony Zrihen 318917549
  Asaf Zafrir 205929029
 */

#include "schedule_station.h"

typedef struct schedule_station_s
{

    int time;
    char *name;

} schedule_station;

ListElement copyListStation(ListElement elem)
{
    ScheduleStation temp = (ScheduleStation)elem;
    if (temp == NULL)
    {
        return NULL;
    }
    ScheduleStation new_station = (ScheduleStation)malloc(sizeof(schedule_station));
    if (elem == NULL)
    {
        return NULL;
    }

    new_station->name = (char*)malloc(strlen(temp->name)+1);
    if(new_station->name == NULL){
        free(new_station);
        return NULL;
    }
    strcpy(new_station->name, temp->name);
    new_station->time = temp->time;

    return new_station;
} /*should return NULL if fails*/

void freeListStation(ListElement elem)
{
    ScheduleStation station = (ScheduleStation)elem;
    if (elem == NULL)
        return;

    free(station->name);
    free(station); 

    return;
}
void printListStation(FILE *file, ListElement elem)
{

    ScheduleStation station = (ScheduleStation)elem;
    if (file == NULL || elem == NULL)
        return;

    fprintf(file, "%-5d||\t%-21s|\n", station->time, station->name);

    return;
}

int compareStationsByName(ListElement elem1, ListElement elem2)
{
    ScheduleStation station1 = (ScheduleStation)elem1;
    ScheduleStation station2 = (ScheduleStation)elem2;
    if (station1 == NULL || station2 == NULL)
        return 0;
    return strcmp(station1->name, station2->name);
}

int compareStationByTime(ListElement elem1, ListElement elem2){
    ScheduleStation station1 = (ScheduleStation)elem1;
    ScheduleStation station2 = (ScheduleStation)elem2;

    if (station1 == NULL || station2 == NULL){
        return 0;
    }

    if(station1->time == station2->time){

        printf("hello\n");
        return 0;
    }

    if(station1->time < station2->time){
        return -1;
}    
    return 1;
}
int matchStationsByName(ListElement elem, KeyForListElement key)
{
    ScheduleStation station = (ScheduleStation)elem;
    char *name = (char *)key;
    if (station == NULL || name == NULL)
        return 0;
    return strcmp(station->name, name);
}

//=============EX4 functions=============//

ScheduleStation schedule_station_create(const char *station, int time)
{

    ScheduleStation new_station;

    if (station == NULL){
        return NULL;
    }

    new_station = (ScheduleStation)malloc(sizeof(station)); // list
    if (new_station == NULL)
    {
        return NULL;
    }
    new_station->name = (char *)malloc(strlen(station) + 1);
    if (new_station->name == NULL)
    {
        free(new_station);
        return NULL;
    }
    strcpy(new_station->name, station);
    new_station->time = time;
    return new_station;
}

ScheduleStationResult schedule_station_destroy(ScheduleStation station)
{
    if (station == NULL)
    {
        return SCHEDULE_STATION_BAD_ARGUMENTS;
    }
    free(station->name);
    free(station);
    return SCHEDULE_STATION_SUCCESS;
}

ScheduleStationResult schedule_station_get_name(ScheduleStation station, char **station_name)
{
    if (station == NULL || station->name == NULL)
    {
        return SCHEDULE_STATION_NULL_ARG;
    }

    *station_name = station->name;
    return SCHEDULE_STATION_SUCCESS;
}
ScheduleStationResult schedule_station_get_time(ScheduleStation station, int *time)
{
    if (station == NULL)
    {
        return SCHEDULE_STATION_BAD_ARGUMENTS;
    }
    *time = station->time;
    return SCHEDULE_STATION_SUCCESS;
}