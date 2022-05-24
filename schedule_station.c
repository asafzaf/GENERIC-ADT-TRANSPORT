
#include "schedule_station.h"

typedef struct schedule_station_s{

    int time;
    char *name;

}schedule_station;

 ListElement copyListLine(ListElement elem){
ScheduleStation temp = (ScheduleStation)elem;
if(temp == NULL){
    return NULL;
}
ScheduleStation new_station = (ScheduleStation)malloc(sizeof(schedule_station));
if(new_station == NULL){
    return NULL; 
}

new_station->time = temp->time;
new_station->name = (char*)malloc(strlen(temp->name)+1);
if(new_station->name == NULL){
    free(new_station);
    return NULL;
}

return new_station;
 } /*should return NULL if fails*/
 void freeListLine(ListElement elem){

    if(elem == NULL)
        return;

     ScheduleStation station = (ScheduleStation)elem;
    free(station->name);
    free(station);
    return;
 }
 void printListLine(FILE *file, ListElement elem){

    if(file == NULL || elem == NULL)
        return;

     ScheduleStation station =(ScheduleStation)elem;
    fprintf(file, "%s||\t%d|\n",station->time, station->name);
    
    return;
 }


