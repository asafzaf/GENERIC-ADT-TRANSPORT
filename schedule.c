/*
========ASSIGNED BY======== 
  Rony Zrihen 318917549
  Asaf Zafrir 205929029
 */

#include "schedule.h"
#include "linked_list.h"
#include "schedule_line.h"
#include "schedule_station.h"

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
  if (linkedListGetNumElements(schedule->line_list) != 0)
  {
  }
  free(schedule);
  return;
}
ScheduleResult scheduleAddLine(Schedule schedule, ScheduleLineType type,
                               int number, const char *description,
                               double price)
{

  scheduleline new_line;
  char desc1[] = "Saburban";
  char desc2[] = "Intercity";
  char desc3[] = "Direct";

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

  if (linkedListFind(schedule->line_list, &number, match_by_number) == LIST_SUCCESS) // void* means i have to send in a pointer var
  {
    return SCHEDULE_LINE_ALREADY_EXISTS;
  }

  // good to go
  new_line = schedule_line_create(type, number, description, price);
  if (new_line == NULL)
  {
    return SCHEDULE_OUT_OF_MEMORY;
  }

  linkedListGoToHead(schedule->line_list);
  linkedListInsertLast(schedule->line_list, new_line);

  return SCHEDULE_SUCCESS;
}

ScheduleResult scheduleRemoveLine(Schedule schedule, int number)
{
  scheduleline curr_line = NULL;
  if (schedule == NULL)
  {
    return SCHEDULE_NULL_ARG;
  }
  if (number < 0 || number > 9999)
  {
    return SCHEDULE_INVALID_LINE_NUMBER;
  }

  if (linkedListFind(schedule->line_list, &number, match_by_number) == LIST_SUCCESS)
  {

    linkedListRemoveCurrent(schedule->line_list);
    schedule_line_destroy(curr_line);
    return SCHEDULE_SUCCESS;
  }
  return SCHEDULE_LINE_DOESNT_EXIST;
}

ScheduleResult scheduleAddStationToLine(Schedule schedule, int number,
                                        const char *station, int time)
{

  scheduleline curr_line;
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
  if (linkedListGoToHead(schedule->line_list) == LIST_BAD_ARGUMENTS)
  {
    return SCHEDULE_NO_LINES;
  }

  if (linkedListFind(schedule->line_list, &number, match_by_number) == LIST_FAIL)
  {
    return SCHEDULE_LINE_DOESNT_EXIST;
  }

  if (linkedListGetCurrent(schedule->line_list, (ListElement)&curr_line) == LIST_FAIL) // find and get the line
  {
    return SCHEDULE_NO_LINES;
  }

  curr_station = schedule_station_create(station, time);
  if (curr_station == NULL)
  {
    return SCHEDULE_OUT_OF_MEMORY;
  }

  schedule_line_add_station(curr_line, curr_station);
  return SCHEDULE_SUCCESS;
}

ScheduleResult scheduleRemoveStationFromLine(Schedule schedule, int number,
                                             int index)
{
  scheduleline line;
  LinkedList station_list;
  int length = 0;

  if (schedule == NULL)
  {
    return SCHEDULE_NULL_ARG;
  }

  if (number < 0 || number > 9999)
  {
    return SCHEDULE_INVALID_LINE_NUMBER;
  }
  linkedListGoToHead(schedule->line_list);
  if (linkedListFind(schedule->line_list, &number, match_by_number) == LIST_FAIL)
  {
    return SCHEDULE_LINE_DOESNT_EXIST;
  }
  linkedListGetCurrent(schedule->line_list, (ListElement)&line);
  schedule_line_get_stations(line, (LinkedList *)&station_list);
  length = linkedListGetNumElements(station_list);
  if (index > length)
  {
    return SCHEDULE_STATION_DOESNT_EXIST;
  }

  linkedListGoToHead(station_list);

  if (index == -1)
  {
    index = length;
  }

  for (int i = 0; i < index; i++)
  {
    linkedListGoToNext(station_list);
  }
  linkedListRemoveCurrent(station_list);
  return SCHEDULE_SUCCESS;
}

ScheduleResult scheduleReportStationsForLine(Schedule schedule, int number)
{
  scheduleline line;
  LinkedList station_list;
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
  linkedListFind(schedule->line_list, &number, match_by_number);
  linkedListGetCurrent(schedule->line_list, (ListElement *)&line);
  schedule_line_get_stations(line, (LinkedList *)&station_list);
  if(linkedListGetNumElements(station_list) == 0)
  {
    return SCHEDULE_STATION_DOESNT_EXIST;
  }

  linkedListGoToHead(station_list);
  do
  {

    linkedListGetCurrent(station_list, (ListElement *)&station);
    schedule_station_get_name(station, &station_name);
    schedule_station_get_time(station, &station_time);
    schedulePrintStation(stdout, station_name, station_time);

  } while (linkedListGoToNext(station_list) == LIST_SUCCESS);

  return SCHEDULE_SUCCESS;
}

ScheduleResult scheduleReportLines(Schedule schedule, ScheduleLineType type)
{
  scheduleline line;
  ScheduleLineType line_type;
  int number;
  char *description;
  char *first = NULL;
  char *last = NULL;
  double price;
  if (linkedListGoToHead(schedule->line_list) == LIST_BAD_ARGUMENTS || linkedListGetNumElements(schedule->line_list) == 0)
  {
    return SCHEDULE_NO_LINES;
  }

  do
  {

   linkedListGetCurrent(schedule->line_list,(ListElement*)&line);

 
    schedule_line_get_details(line, &line_type, &number, &description, &price);
    if (type == SCHEDULE_LINE_ALL || type == line_type)
    {
      if(get_first_and_last_stations(line, &first, &last) == SCHEDULE_LINE_NULL_ARG){
        return SCHEDULE_NO_STATIONS;
      }
      schedulePrintLine(stdout, line_type, number, description, first, last, price);
    }
  } while (linkedListGoToNext(schedule->line_list) == LIST_SUCCESS);
  return SCHEDULE_SUCCESS;
}
ScheduleResult scheduleReportLinesBetweenStations(Schedule schedule,
                                                  const char *from,
                                                  const char *to)
{
  scheduleline curr_line;
  ScheduleLineType line_type;
  int number;
  char *description;
  double price;
  char *first_station = NULL;
  char *last_station = NULL;

  linkedListGoToHead(schedule->line_list);
  do
  {
    linkedListGetCurrent(schedule->line_list, (ListElement *)&curr_line);
    if (checkRoute(curr_line, from, to) == SCHEDULE_LINE_SUCCESS)
    {
      get_first_and_last_stations(curr_line, &first_station, &last_station);
      schedule_line_get_details(curr_line, &line_type, &number, &description, &price);
      schedulePrintLine(stdout, line_type, number, description, first_station, last_station, price);
    }

  } while (linkedListGoToNext(schedule->line_list) == LIST_SUCCESS);
  return SCHEDULE_SUCCESS;
}

//===============testing functions===============//
// void test(Schedule schedule)
// {

//   linkedListPrint(schedule->line_list, stdout, 10);
//   return;
// }

// void testStation(Schedule schedule)
// {
//   scheduleline line;
//   linkedListGoToHead(schedule->line_list);
//   do
//   {
//     linkedListGetCurrent(schedule->line_list, (ListElement)&line);
//     printstat(line);
//   } while (linkedListGoToNext(schedule->line_list) == LIST_SUCCESS);

//   return;
// }