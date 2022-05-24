#include "schedule.h"
#include "linked_list.h"
#include "schedule_line.h"

typedef struct schedule_s
{
  LinkedList line_list;
} schedule;

Schedule scheduleCreate()
{

  Schedule new_schedule;
  // creating a new transport system
  new_schedule = (Schedule)malloc(sizeof(schedule));
  if (new_schedule == NULL)
  {
    printf("ERROR\n");
    return NULL;
  }

  linkedListCreate(&(new_schedule->line_list), copyListLine, freeListLine, printListLine);
  return new_schedule;
}

void scheduleDestroy(Schedule schedule)
{
/*   scheduleline curr_line;
  if (schedule->line_list != NULL)
  {
    do
    {
      lineListGotoHead(schedule->line_list);
      lineListGetCurrent(schedule->line_list, &curr_line);
      lineListRemoveCurrent(schedule->line_list);
      linkedListDestroy(curr_line);
    } while (linkedListGoToNext(schedule->line_list) == LIST_SUCCESS);
  }
  free(schedule); */
  return ;
}
ScheduleResult scheduleAddLine(Schedule schedule, ScheduleLineType type,
                               int number, const char *description,
                               double price)
{

  scheduleline new_line;
  char desc1[] = "Saburban";
  char desc2[] = "Intercity";
  char desc3[] = "Direct";

  scheduleline curr_line;
  //ScheduleLineType curr_type;
  //int curr_number;
  //char *curr_description;
  //double curr_price;
  if (schedule == NULL)
  {
    return SCHEDULE_NULL_ARG;
  }

  if (type < 0 || type > 2)
  {
    return SCHEDULE_INVALID_LINE_TYPE;
  }

  if (number < 0 || number > 9999)
  {
    return SCHEDULE_INVALID_LINE_NUMBER;
  }

  if (type > 0 && (!strcmp(description, desc1) && !strcmp(description, desc2) &&
                   !strcmp(description, desc3)))
  {
    return SCHEDULE_INVALID_TRAIN_TYPE;
  }

  if (!is_price_valid(price))
  {
    return SCHEDULE_INVALID_PRICE;
  }

  if (linkedListFind(schedule->line_list, &number, match_by_number) == LIST_SUCCESS) //void8 means i have to sand in a pointer var
  {
    return SCHEDULE_LINE_ALREADY_EXISTS;
  }
  printf("here\n");

  // good to go
   new_line = schedule_line_create(type, number, description, price);
  if (new_line == NULL)
  {
    return SCHEDULE_OUT_OF_MEMORY;
  }


    linkedListGoToHead(schedule->line_list);
    

 /* do
  {
    lineListGetCurrent(schedule->line_list, &curr_line);
    schedule_line_get_details(curr_line, &curr_type, &curr_number, &curr_description,
                              &curr_price);

    if (price <= curr_price)
    {
      lineListInsertBeforeCurrent(schedule->line_list, new_line);
      return SCHEDULE_SUCCESS;
    }
  } while (lineListGotoNext(schedule->line_list) == LIST_SUCCESS);
  lineListInsertLast(schedule->line_list, new_line); */
  return SCHEDULE_SUCCESS;
}

ScheduleResult scheduleRemoveLine(Schedule schedule, int number)
{
/*   ScheduleLine curr_line = NULL;
  if (schedule == NULL)
  {
    return SCHEDULE_NULL_ARG;
  }
  if (number < 0 || number > 9999)
  {
    return SCHEDULE_INVALID_LINE_NUMBER;
  }

  if (lineListFind(schedule->line_list, number) == LINE_LIST_SUCCESS)
  {

    lineListRemoveCurrent(schedule->line_list);
    schedule_line_destroy(curr_line);
    return SCHEDULE_SUCCESS;
  } */
  return SCHEDULE_LINE_DOESNT_EXIST;
}

ScheduleResult scheduleAddStationToLine(Schedule schedule, int number,
                                        const char *station, int time)
{
/* 
  ScheduleLine curr_line;
  ScheduleStation curr_station;



  if (schedule == NULL)
  {
    return SCHEDULE_NULL_ARG;
  }
  if (station == NULL)
  {
    return SCHEDULE_NULL_ARG;
  }

  if (number < 0 || number > 9999)
  {
    return SCHEDULE_INVALID_LINE_NUMBER;
  }

  if (time < 0)
  {
    return SCHEDULE_INVALID_TIME;
  }
  if (lineListGotoHead(schedule->line_list) == LINE_LIST_BAD_ARGUMENTS)
  {
    return SCHEDULE_NO_LINES;
  }

  if (lineListFind(schedule->line_list, number) == LINE_LIST_FAIL)
  {
    return SCHEDULE_LINE_DOESNT_EXIST;
  }

  if (lineListGetCurrent(schedule->line_list, &curr_line) == LINE_LIST_FAIL) // find and get the line
  {
    return SCHEDULE_NO_LINES;
  }

  curr_station = schedule_station_create(station, time);
  if (curr_station == NULL)
  {
    return SCHEDULE_OUT_OF_MEMORY;
  }

  schedule_line_add_station(curr_line, curr_station); */
  
  return SCHEDULE_SUCCESS;
}

ScheduleResult scheduleRemoveStationFromLine(Schedule schedule, int number,
                                             int index)
{
/*   ScheduleLine line;
  ScheduleStationList station_list = NULL;

  int length = 0;
  if (schedule == NULL)
  {
    return SCHEDULE_NULL_ARG;
  }

  if (number < 0 || number > 9999)
  {
    return SCHEDULE_INVALID_LINE_NUMBER;
  }

  if (lineListFind(schedule->line_list, number) == LINE_LIST_FAIL)
  {
    return SCHEDULE_LINE_DOESNT_EXIST;
  }
  lineListGetCurrent(schedule->line_list, &line);
  schedule_line_get_stations(line, &station_list);
  length = stationListGetNumElements(station_list);
  if (index > length)
  {
    return SCHEDULE_STATION_DOESNT_EXIST;
  }

  stationListGotoHead(station_list);

  if (index == -1)
  {
    index = length;
  }

  for (int i = 0; i < index; i++)
  {
    stationListGotoNext(station_list);
  }
  stationListRemoveCurrent(station_list); */
  return SCHEDULE_SUCCESS;
}

ScheduleResult scheduleReportStationsForLine(Schedule schedule, int number)
{

/*   ScheduleLine line;
  ScheduleStationList station_list;
  ScheduleStation station;
  char *station_name;
  int station_time;

  if (schedule == NULL)
  {
    return SCHEDULE_NULL_ARG;
  }
  if (number < 0 || number > 9999)
  {
    return SCHEDULE_INVALID_LINE_NUMBER;
  }
  lineListFind(schedule->line_list, number);
  lineListGetCurrent(schedule->line_list, &line);
  schedule_line_get_stations(line, &station_list);
  stationListGotoHead(station_list);
  do
  {

    stationListGetCurrent(station_list, &station);
    schedule_station_get_name(station, &station_name);
    schedule_station_get_time(station, &station_time);
    schedulePrintStation(stdout, station_name, station_time);

  } while (stationListGotoNext(station_list) == STATION_LIST_SUCCESS); */
  return SCHEDULE_SUCCESS;
}

ScheduleResult scheduleReportLines(Schedule schedule, ScheduleLineType type)
{
  /*   ScheduleLine line;
  ScheduleStationList line_list;
  ScheduleLineType line_type;
  ScheduleStation last_station;
  ScheduleStation first_station;
  int number;
  char *description;
  char *first = NULL;
  char *last = NULL;
  double price;
  if (lineListGotoHead(schedule->line_list) == LINE_LIST_BAD_ARGUMENTS)
  {
    return SCHEDULE_NO_LINES;
  }
  do
  {

    if (lineListGetCurrent(schedule->line_list, &line) == LINE_LIST_FAIL)
    {
      return SCHEDULE_NO_LINES;
    }
    schedule_line_get_details(line, &line_type, &number, &description, &price);
    if (type == SCHEDULE_LINE_ALL || type == line_type)
    {
      schedule_line_get_stations(line, &line_list);
  
      stationListGetCurrent(line_list,&first_station);
      schedule_station_get_name(first_station, &first);
      while((stationListGotoNext(line_list) == STATION_LIST_SUCCESS));
      stationListGetCurrent(line_list,&last_station);
      schedule_station_get_name(first_station, &last);

        
      
      
     
      schedulePrintLine(stdout, line_type, number, description, first, last, price);
    }
  } while (lineListGotoNext(schedule->line_list) == LINE_LIST_SUCCESS);*/
  return 0; 
}

ScheduleResult scheduleReportLinesBetweenStations(Schedule schedule,
                                                  const char *from,
                                                  const char *to)
{
  return 0;
}

void test(Schedule schedule)
{

 /*  ScheduleLine line;
  ScheduleLineType line_type;
  ScheduleStationList stations;
  int number;
  char *description;
  double price;

  lineListGotoHead(schedule->line_list);
  do
  {
    lineListGetCurrent(schedule->line_list, &line);
    schedule_line_get_details(line, &line_type, &number, &description, &price);
    printf("%d %s %s %.2f\n", number, description, line_type == SCHEDULE_LINE_METRO ? "Metro" : "Bus", price);
    schedule_line_get_stations(line,&stations);
    testStation(stations);
    

  } while (lineListGotoNext(schedule->line_list) == LINE_LIST_SUCCESS); */
  return;
}

/* void testStation(ScheduleStationList line_list)
{
  ScheduleStation station;
  char *name;
  int time;
  stationListGotoHead(line_list);
  printf("||%d||\n",stationListGetNumElements(line_list));
  do
  {
    stationListGetCurrent(line_list, &station);
    schedule_station_get_name(station, &name);
    schedule_station_get_time(station, &time);
    printf("%s %d\n", name, time);
  } while (stationListGotoNext(line_list) == STATION_LIST_SUCCESS);
  return ;
} */