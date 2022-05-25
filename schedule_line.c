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
if (new_line->description == NULL){
    free(new_line);
    return NULL;
}
strcpy(new_line->description ,temp->description);
new_line->number = temp->number;
new_line->price  = temp->price;
new_line->type   = temp->type;
linkedListCreate(&(new_line->stations), copyListStation, freeListStation, printListStation);

return new_line;
 } 
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
     

    fprintf(file, "%-5d||\t%-10s||%.2f\n",line->number, line->description, line->price );
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

ScheduleLineResult schedule_line_destroy(scheduleline line){

  if(line == NULL) {
    return SCHEDULE_LINE_BAD_ARGUMENTS;
  }

if(linkedListGetNumElements(line->stations) != 0)
  linkedListDestroy(line->stations);

free(line->description);
free(line);

  return SCHEDULE_LINE_SUCCESS;
}

ScheduleLineResult schedule_line_get_stations(ListElement elem, LinkedList *stations){
  scheduleline line;
  
  if(elem == NULL || stations == NULL) {
    return SCHEDULE_LINE_BAD_ARGUMENTS;
  }

  line = (scheduleline)elem;
  *stations = (LinkedList)line->stations;
   return SCHEDULE_LINE_SUCCESS;
}

ScheduleLineResult schedule_line_add_station(ListElement elem1, ListElement elem2){
  scheduleline line;
  ScheduleStation station;
if(elem1 == NULL || elem2 == NULL){
  return SCHEDULE_LINE_BAD_ARGUMENTS;
}

line = (scheduleline)elem1;
station = (ScheduleStation)elem2;
    linkedListGoToHead(line->stations);
    while(linkedListGoToNext(line->stations) == LIST_SUCCESS);
    linkedListInsertLast(line->stations, station);
  return SCHEDULE_LINE_SUCCESS;

}


ScheduleLineResult schedule_line_get_details(scheduleline line,
                                             ScheduleLineType *type /* out */,
                                             int *number /* out */,
                                             char **description /* out */,
                                             double *price /* out */){

                                          
  if(line == NULL){
    return SCHEDULE_LINE_BAD_ARGUMENTS;
  }

  *type = line->type;
  *number = line->number;
  *description = line->description;
  *price = line->price;


  return 0;
}

  int is_price_valid(float price)
  {
    price *= 1000;
    if ((int)price % 10)
    {
      return 0;
    }
    return 1;
  }


void printstat(scheduleline line){
    linkedListPrint(line->stations, stdout, 10);
    return;
}
 