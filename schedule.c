/* 
reuploaded after fixing the program 
Rony Zrihen 318317549 || Asaf Zafrir 205929029
 */
#include "schedule.h"

#include "schedule_station.h"

typedef struct schedule_s
{
  ScheduleLineList line_list;
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

  lineListCreate(&(new_schedule->line_list));
  return new_schedule;
}

void scheduleDestroy(Schedule schedule)
{
  ScheduleLine curr_line;
  if (lineListGetNumElements(schedule->line_list) != 0)
  {
    do
    {
      lineListGotoHead(schedule->line_list);
      lineListGetCurrent(schedule->line_list, &curr_line);
      lineListRemoveCurrent(schedule->line_list);
      schedule_line_destroy(curr_line);
    } while (lineListGotoNext(schedule->line_list) == LINE_LIST_SUCCESS);
  }
  free(schedule);
}
ScheduleResult scheduleAddLine(Schedule schedule, ScheduleLineType type,
                               int number, const char *description,
                               double price)
{

  ScheduleLine new_line;
  char desc1[] = "Saburban";
  char desc2[] = "Intercity";
  char desc3[] = "Direct";

  ScheduleLine curr_line;
  ScheduleLineType curr_type;
  int curr_number;
  char *curr_description;
  double curr_price;
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

  if (lineListFind(schedule->line_list, number) == LINE_LIST_SUCCESS)
  {
    return SCHEDULE_LINE_ALREADY_EXISTS;
  }

  // good to go
  new_line = schedule_line_create(type, number, description, price);
  if (new_line == NULL)
  {
    return SCHEDULE_OUT_OF_MEMORY;
  }

  if (lineListGetNumElements(schedule->line_list) == 0)
  {

    lineListGotoHead(schedule->line_list);
    lineListInsertFirst(schedule->line_list, new_line);
    return SCHEDULE_SUCCESS;
  }
  lineListGotoHead(schedule->line_list);
  do
  {
    lineListGetCurrent(schedule->line_list, &curr_line);
    schedule_line_get_details(curr_line, &curr_type, &curr_number, &curr_description,
                              &curr_price);

    if (price <= curr_price)
    {
      lineListInsertBeforeCurrent(schedule->line_list, new_line);
      return SCHEDULE_SUCCESS;
    }
  } while (lineListGotoNext(schedule->line_list) == LINE_LIST_SUCCESS);
  lineListInsertLast(schedule->line_list, new_line);
  return SCHEDULE_SUCCESS;
}

ScheduleResult scheduleRemoveLine(Schedule schedule, int number)
{
  ScheduleLine curr_line = NULL;
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
  }
  return SCHEDULE_LINE_DOESNT_EXIST;
}

ScheduleResult scheduleAddStationToLine(Schedule schedule, int number,
                                        const char *station, int time)
{

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

  schedule_line_add_station(curr_line, curr_station);

  return SCHEDULE_SUCCESS;
}

ScheduleResult scheduleRemoveStationFromLine(Schedule schedule, int number,
                                             int index)
{
  ScheduleLine line;
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
  lineListGotoHead(schedule->line_list);
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
  stationListRemoveCurrent(station_list);
  return SCHEDULE_SUCCESS;
}

ScheduleResult scheduleReportStationsForLine(Schedule schedule, int number)
{

  ScheduleLine line;
  ScheduleStationList station_list;
  ScheduleStation station;
  char *station_name;
  int station_time;

  ScheduleLineType type;
  int line_number;
  char *line_description;
  double line_price;
  char *first_station;
  char *last_station;

  if (schedule == NULL)
  {
    return SCHEDULE_NULL_ARG;
  }
  if (number < 0 || number > 9999)
  {
    return SCHEDULE_INVALID_LINE_NUMBER;
  }
  lineListGotoHead(schedule->line_list);
  if (lineListFind(schedule->line_list, number) != LINE_LIST_SUCCESS)
    return SCHEDULE_LINE_DOESNT_EXIST;

  lineListGetCurrent(schedule->line_list, &line);
  schedule_line_get_stations(line, &station_list);
  stationListGotoHead(station_list);

  if (stationListGetNumElements(station_list) == 0)
    return SCHEDULE_STATION_DOESNT_EXIST;

  schedule_line_get_details(line, &type, &line_number, &line_description, &line_price);
  get_first_and_last_stations(line, &first_station, &last_station);
  schedulePrintLine(stdout, type, line_number, line_description, first_station, last_station, line_price);

  stationListGotoHead(station_list);
  stationListSortBy(station_list, STATION_LIST_SORT_BY_TIME);
  do
  {

    stationListGetCurrent(station_list, &station);
    schedule_station_get_name(station, &station_name);
    schedule_station_get_time(station, &station_time);
    schedulePrintStation(stdout, station_name, station_time);

  } while (stationListGotoNext(station_list) == STATION_LIST_SUCCESS);
  
  return SCHEDULE_SUCCESS;
}

ScheduleResult scheduleReportLines(Schedule schedule, ScheduleLineType type)
{
  ScheduleLine line;

  ScheduleLineType line_type;
  int number;
  char *description;
  char *first = NULL;
  char *last = NULL;
  char NA[] = "N/A";
  double price;

  if (schedule == NULL)
    return SCHEDULE_NULL_ARG;

  if (lineListGetNumElements(schedule->line_list) == 0)
  {
    return SCHEDULE_NO_LINES;
  }

  if (type < SCHEDULE_LINE_BUS || type > SCHEDULE_LINE_ALL)
    return SCHEDULE_INVALID_LINE_TYPE;

  if (lineListGotoHead(schedule->line_list) == LINE_LIST_BAD_ARGUMENTS)
  {
    return SCHEDULE_NO_LINES;
  }
  do
  {
    if (lineListGetCurrent(schedule->line_list, &line) == LINE_LIST_FAIL)
    {
      return SCHEDULE_NULL_ARG;
    }
    schedule_line_get_details(line, &line_type, &number, &description, &price);
    if (type == SCHEDULE_LINE_ALL || type == line_type)
    {

      if (get_first_and_last_stations(line, &first, &last) == SCHEDULE_LINE_STATION_DOESNT_EXIST)
      {
        schedulePrintLine(stdout, line_type, number, description, NA, NA, price);
        continue;
      }
      schedulePrintLine(stdout, line_type, number, description, first, last, price);
    }
  } while (lineListGotoNext(schedule->line_list) == LINE_LIST_SUCCESS);

  return SCHEDULE_SUCCESS;
}

ScheduleResult scheduleReportLinesBetweenStations(Schedule schedule,
                                                  const char *from,
                                                  const char *to)
{
  ScheduleLine curr_line;
  ScheduleLineType line_type;
  int number;
  char *description;
  double price;
  char *first_station = NULL;
  char *last_station = NULL;

  lineListGotoHead(schedule->line_list);
  do
  {
    lineListGetCurrent(schedule->line_list, &curr_line);
    if (checkRoute(curr_line, from, to) == SCHEDULE_LINE_SUCCESS)
    {
      get_first_and_last_stations(curr_line, &first_station, &last_station);
      schedule_line_get_details(curr_line, &line_type, &number, &description, &price);
      schedulePrintLine(stdout, line_type, number, description, first_station, last_station, price);
    }

  } while (lineListGotoNext(schedule->line_list) == LINE_LIST_SUCCESS);
  return SCHEDULE_SUCCESS;
}

/* void test(Schedule schedule)
{

  ScheduleLine line;
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
    schedule_line_get_stations(line, &stations);
    testStation(stations);

  } while (lineListGotoNext(schedule->line_list) == LINE_LIST_SUCCESS);
}

void testStation(ScheduleStationList line_list)
{
  ScheduleStation station;
  char *name;
  int time;
  stationListGotoHead(line_list);
  printf("||%d||\n", stationListGetNumElements(line_list));
  do
  {
    stationListGetCurrent(line_list, &station);
    schedule_station_get_name(station, &name);
    schedule_station_get_time(station, &time);
    printf("%s %d\n", name, time);
  } while (stationListGotoNext(line_list) == STATION_LIST_SUCCESS);
} */