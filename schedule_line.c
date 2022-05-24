#include "schedule_line.h"
#include "schedule_station.h"

typedef struct schedule_line{

int number;
double price;
LinkedList stations;
ScheduleLineType type;
char *description;

}schedule_line;

//===========Basic ADT functions===========//

 ListElement copyListLine(ListElement elem){
scheduleline temp = (scheduleline)elem;
if(temp == NULL){
    return NULL;
}
scheduleline new_line = (scheduleline)malloc(sizeof(schedule_line));
if(new_line == NULL){
    return NULL; 
}
new_line->description = (char*)malloc(strlen(temp->description)+1);

strcpy(new_line->description ,new_line->description);
new_line->number = temp->number;
new_line->price  = temp->price;
new_line->type   = temp->type;
linkedListCreate(&(new_line->stations), copyListStation, freeListStation, printListStation);


return new_line;
 } /*should return NULL if fails*/
 void freeListLine(ListElement elem){

    if(elem == NULL)
        return;

     scheduleline line = (scheduleline)elem;
    linkedListDestroy(line->stations);
    free(line->description);
    free(line);
    return;
 }
 void printListLine(FILE *file, ListElement elem){

    if(file == NULL || elem == NULL)
        return;

     scheduleline line =(scheduleline)elem;

    fprintf(file, "%d||\t%s||\t%.2f\n",line->number, line->description, line->price );
    return;
 }

//===========match functions===========//

int match_by_number(ListElement line_element, KeyForListElement elem ){
    scheduleline line;
    int number;

    if(line_element == NULL || elem == NULL){
        return 0;
    }
    line = (scheduleline)line_element;
    number = *(int*)elem; //function asks for a void* elem meaning we need to dereferance a pionter
    return line->number == number; //returns a binary answer
}


 //===========EX4 functions===========//

 scheduleline schedule_line_create(ScheduleLineType type, int number,
                                  const char *description, double price) {

  scheduleline new_line;
  new_line = (scheduleline)malloc(sizeof(schedule_line));
  if (new_line == NULL) {
    printf("NULL\n");
    return NULL;
  }
  new_line->description = (char *)malloc(strlen(description) + 1);
  if (new_line->description == NULL) {
    printf("NULL\n");
    return NULL;
  }
  strcpy(new_line->description, description);
  new_line->price = price;
  new_line->type = type;
  new_line->number = number;
  if(linkedListCreate(&(new_line->stations), copyListStation, freeListStation, printListStation) == LIST_OUT_OF_MEMORY){
        return NULL;
  }

  return new_line;
}

// ScheduleLineResult schedule_line_destroy(ScheduleLine line){

// ScheduleStation curr_station;
//   if(line == NULL) {
//     return SCHEDULE_LINE_BAD_ARGUMENTS;
//   }
// if(line->stations_list != NULL){

// do{
//   stationListGotoHead(line->stations_list);
//   stationListGetCurrent(line->stations_list, &curr_station);
//   stationListRemoveCurrent(line->stations_list);
//   schedule_station_destroy(curr_station);
// }
// while(stationListGotoNext(line->stations_list) == STATION_LIST_SUCCESS);
// }

// free(line->description);
// free(line);

//   return SCHEDULE_LINE_SUCCESS;
// }

// ScheduleLineResult schedule_line_get_stations(ScheduleLine line, ScheduleStationList *stations){
//   if(line == NULL || stations == NULL) {
//     return SCHEDULE_LINE_BAD_ARGUMENTS;
//   }
//   *stations = line->stations_list;
//    return SCHEDULE_LINE_SUCCESS;
// }

// ScheduleLineResult schedule_line_add_station(ScheduleLine line, ScheduleStation station){
//   ScheduleLineResult line_result = SCHEDULE_LINE_SUCCESS;
//   StationListResult station_result = STATION_LIST_SUCCESS;
//   ScheduleStationList curr_station;
//   int list_length;

//   curr_station = line->stations_list;

//   list_length =  stationListGetNumElements(curr_station);
//    if(list_length == 0) {
//     stationListGotoHead(line->stations_list);
//     stationListInsertFirst(line->stations_list, station);
//     return SCHEDULE_LINE_SUCCESS;
//   }
//   for(int i = 0; i < list_length; i++) {
//     stationListGotoNext(curr_station);
//   } 
  
//   station_result = stationListInsertLast(curr_station, station);
//   if(station_result != STATION_LIST_SUCCESS ) {
//     return line_result;
//   }

  
//   return SCHEDULE_LINE_SUCCESS;

// }


// ScheduleLineResult schedule_line_get_details(ScheduleLine line,
//                                              ScheduleLineType *type /* out */,
//                                              int *number /* out */,
//                                              char **description /* out */,
//                                              double *price /* out */){

                                          
//   if(line == NULL){
//     return SCHEDULE_LINE_BAD_ARGUMENTS;
//   }

//   *type = line->type;
//   *number = line->number;
//   *description = line->description;
//   *price = line->price;


//   return 0;
// }