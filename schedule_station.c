#include "schedule_station.h"
#include "schedule_station_list.h"

typedef struct schedule_station_s{

    int time;
    char *name;

}station;

ScheduleStation schedule_station_create(const char *station, int time)
{
    
    ScheduleStation new_station;
    

    new_station = (ScheduleStation)malloc(sizeof(station)); //list
    if(new_station == NULL)
    {
        return NULL;
    }
    new_station->name = (char *)malloc(strlen(station) + 1);
    if(new_station->name == NULL)
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
    if(station == NULL)
    {
        return SCHEDULE_STATION_BAD_ARGUMENTS;
    }
    free(station->name);
    free(station);
    return SCHEDULE_STATION_SUCCESS;
}

ScheduleStationResult schedule_station_get_name(ScheduleStation station, char **station_name)
{
    if(station == NULL) {
        return SCHEDULE_STATION_NULL_ARG;
    }
    
    *station_name = station->name;
    return SCHEDULE_STATION_SUCCESS;
}
ScheduleStationResult schedule_station_get_time(ScheduleStation station, int *time)
{
    if ( station == NULL ){
        return SCHEDULE_STATION_BAD_ARGUMENTS;
    }
    *time = station->time;
    return SCHEDULE_STATION_SUCCESS;
}