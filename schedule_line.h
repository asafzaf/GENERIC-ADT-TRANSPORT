#ifndef __SCHEDULE_LINE_H__
#define __SCHEDULE_LINE_H__

/*
 * file: schedule_line.h
 *
 * description: Schedule line ADT
 *
 *  Here you need to add functions for schedule line adt and implement them in schedule_line.c file
 * */

#include "pr2ex4.h"
#include "schedule_station_list.h"

typedef struct schedule_line_s *ScheduleLine;

typedef enum
{
    SCHEDULE_LINE_SUCCESS,
    SCHEDULE_LINE_FAIL,
    SCHEDULE_LINE_BAD_ARGUMENTS,
    SCHEDULE_LINE_OUT_OF_MEMORY,
    SCHEDULE_LINE_NULL_ARG,
    SCHEDULE_LINE_NO_MATCH,
    SCHEDULE_LINE_STATION_DOESNT_EXIST,
    
    /* add here more errorcodes */
} ScheduleLineResult;

ScheduleLine schedule_line_create(ScheduleLineType type, int number, const char *description, double price);
ScheduleLineResult schedule_line_destroy(ScheduleLine line);
ScheduleLineResult schedule_line_get_stations(ScheduleLine line, ScheduleStationList *stations);
ScheduleLineResult schedule_line_add_station(ScheduleLine line, ScheduleStation station);
ScheduleLineResult schedule_line_get_details(ScheduleLine line,
                                             ScheduleLineType *type /* out */,
                                             int *number /* out */,
                                             char **description /* out */,
                                             double *price /* out */);
ScheduleLineResult get_first_and_last_stations(ScheduleLine line , char **first_station, char **last_station);
ScheduleLineResult checkRoute(ScheduleLine line, const char *from, const char *to);
int is_price_valid(float price);

/* Add here more functions as you need to meet the exercise requirements */

#endif /* __SCHEDULE_LINE_H__ */
