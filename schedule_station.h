#ifndef __SCHEDULE_STATION_H__
#define __SCHEDULE_STATION_H__

/*
 * file: schedule_station.h
 *
 * description: Schedule station ADT
 *
 *  Here you need to add functions for schedule station adt and implement them in schedule_station.c file
 * */

#include "pr2ex4.h"

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

ScheduleStation schedule_station_create(const char *station, int time);
ScheduleStationResult schedule_station_destroy(ScheduleStation station);
ScheduleStationResult schedule_station_get_name(ScheduleStation station, char **station_name);
ScheduleStationResult schedule_station_get_time(ScheduleStation station, int *time);

/* Add here more functions as you need to meet the exercise requirements */

#endif /* __SCHEDULE_STATION_H__ */
