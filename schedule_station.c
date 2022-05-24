
#include "schedule_station.h"

typedef struct schedule_station_s{

    int time;
    char *name;

}schedule_station;

ListElement copyListStation(ListElement elem){
ScheduleStation temp = (ScheduleStation)elem;
if(temp == NULL){
    return NULL;
}
ScheduleStation new_station = (ScheduleStation)malloc(sizeof(schedule_station));
if(elem == NULL){
    return NULL; 
}
new_station->time = temp->time;
strcpy( new_station->name, temp->name );

/*new_station->name = (char*)malloc(strlen(temp->name)+1);
if(new_station->name == NULL){
    free(new_station);
    return NULL; 
} */
return new_station;
 } /*should return NULL if fails*/

void freeListStation(ListElement elem){

    if(elem == NULL)
        return;
    free(elem); //what about the name?

    return;
 }
void printListStation(FILE *file, ListElement elem){

    ScheduleStation station = (ScheduleStation)elem;
    if(file == NULL || elem == NULL)
        return;

    fprintf(file, "%d||\t%s|\n",station->time, station->name);
    
    return;
 }

int compareStationsByName(ListElement elem1, ListElement elem2){
    ScheduleStation station1 = (ScheduleStation)elem1;
    ScheduleStation station2 = (ScheduleStation)elem2;
    if (station1 == NULL || station2 == NULL)
        return 0;
    return strcmp(station1->name, station2->name);
}

int matchStationsByName(ListElement elem, KeyForListElement key){
    ScheduleStation station = (ScheduleStation)elem;
    char *name = (char *)key;
    if (station == NULL || name == NULL )
        return 0;
    return strcmp( station->name , name );
}

ScheduleStationResult StationCreate(ScheduleStation *station) //wtf
{
    // if (station == NULL)
    //     return SCHEDULE_STATION_BAD_ARGUMENTS;

    // ScheduleStation new_station = (ScheduleStation)malloc(sizeof(schedule_station))); // fixed the types, please test run the program befor uploading!!!!
    // if (new_station == NULL)
    //     return SCHEDULE_STATION_OUT_OF_MEMORY;

    // //sprintf(new_station->description, "%s", GROUP_DESCRIPTION); //this is not needed
    // if (linkedListCreate(&(new_station->list), copyListStation, freeListStation, printListStation) != LIST_SUCCESS)
    // {
    //     free(new_station);
    //     return SCHEDULE_STATION_OUT_OF_MEMORY;
    // }

    // *station = new_station;
    return SCHEDULE_STATION_SUCCESS;
}