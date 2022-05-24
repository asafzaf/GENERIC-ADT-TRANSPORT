
#include <stdio.h>
#include <stdlib.h>
#include "schedule.h"
#include "pr2ex5.h"
#include "linked_list.h"

#define ERROR_STREAM stderr
#define OUT_STREAM stdout
#define SCHEDULE_RESULT_AS_STRING(result) #result,
#define NUM_OF_LINES

typedef enum
{
    SUCCESS,
    FAIL
} test_result_t;

typedef test_result_t (*test_func)();

const char *
    schedule_result_strings[] = {SCHEDULE_RESULT_TABLE(SCHEDULE_RESULT_AS_STRING)};

void schedule_app_print_error_message(FILE *err_channel, ScheduleResult result)
{
    if (result > SCHEDULE_SUCCESS || result < 0)
        fprintf(err_channel, " ***** Error: Unknown Error *****\n");
    else
        fprintf(err_channel, " ***** Error: %s *****\n", schedule_result_strings[result]);
}

test_result_t schedule_handle_result(ScheduleResult result)
{
    if (result != SCHEDULE_SUCCESS)
        schedule_app_print_error_message(ERROR_STREAM, result);

    if (result != SCHEDULE_OUT_OF_MEMORY)
        return SUCCESS;

    return FAIL;
}

test_result_t test1()
{
    printf("--------------\n");
    printf("Starting test1\n");
    printf("--------------\n");

    Schedule schedule = scheduleCreate();
    if (schedule == NULL)
    {
        schedule_app_print_error_message(stderr, SCHEDULE_OUT_OF_MEMORY);
        return FAIL;
    }

    printf("\nAdd lines\n");
    if (schedule_handle_result(scheduleAddLine(schedule, SCHEDULE_LINE_BUS, 37, "Egged", 5.4)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }

    if (schedule_handle_result(scheduleAddLine(schedule, SCHEDULE_LINE_TRAIN, 4000, "Direct", 20.7)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleAddLine(schedule, SCHEDULE_LINE_BUS, 24, "Egged", 5.6)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    test(schedule);
/* 
    printf("\nAdd stations to bus line #37...\n");
    if (schedule_handle_result(scheduleAddStationToLine(schedule, 37, "Bay_Central", 0)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleAddStationToLine(schedule, 37, "Horev Center", 22)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleAddStationToLine(schedule, 37, "Haifa University", 32)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleAddStationToLine(schedule, 37, "Hadar", 15)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }

    printf("\nAdd stations to train line #4000\n");
    if (schedule_handle_result(scheduleAddStationToLine(schedule, 4000, "Carmel_Beach", 0)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleAddStationToLine(schedule, 4000, "Binyamina", 22)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleAddStationToLine(schedule, 4000, "Tel-Aviv_University", 48)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleAddStationToLine(schedule, 4000, "Beer-Sheva_North", 148)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }

    printf("\nAdd stations to bus line #24\n");
    if (schedule_handle_result(scheduleAddStationToLine(schedule, 24, "Bay_Central", 0)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleAddStationToLine(schedule, 24, "Old_Romema", 27)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleAddStationToLine(schedule, 24, "Haifa University", 38)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }

    printf("\nRemove a station from the train.\n");
    if (schedule_handle_result(scheduleRemoveStationFromLine(schedule, 4000, 0)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }

    printf("\nReport all lines...\n");
    if (schedule_handle_result(scheduleReportLines(schedule, SCHEDULE_LINE_ALL)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    printf("\nReport BUS lines...\n");

    if (schedule_handle_result(scheduleReportLines(schedule, SCHEDULE_LINE_BUS)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    printf("\nReport lines between certain stations...\n");
    if (schedule_handle_result(scheduleReportLinesBetweenStations(schedule, "Bay_Central", "Haifa University")))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    printf("\nReport stations for line\n");
    if (schedule_handle_result(scheduleReportStationsForLine(schedule, 4000)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    printf("\nReport stations for line\n");
    if (schedule_handle_result(scheduleReportStationsForLine(schedule, 37)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    printf("\nReport stations for line\n");
    if (schedule_handle_result(scheduleReportStationsForLine(schedule, 24)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }

    scheduleDestroy(schedule); */
    return SUCCESS;
}

test_result_t test2()
{

    printf("--------------\n");
    printf("Starting test2\n");
    printf("--------------\n");

    Schedule schedule = scheduleCreate();
    printf("\nAdd bus line\n");
    if (schedule_handle_result(scheduleReportLines(schedule, SCHEDULE_LINE_ALL)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleAddLine(schedule, SCHEDULE_LINE_BUS, 901, "E g  g   e    d", 22)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleReportLines(schedule, SCHEDULE_LINE_ALL)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }

    printf("\nAdd stations to bus line\n");
    if (schedule_handle_result(scheduleReportStationsForLine(schedule, 901)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleAddStationToLine(schedule, 901, "Carmel Beach", 0)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleAddStationToLine(schedule, 901, "Tel Aviv Savidor", 80)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleAddStationToLine(schedule, 901, "Tel Aviv Central", 100)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleReportStationsForLine(schedule, 901)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }

    printf("\nAdd train line\n");
    if (schedule_handle_result(scheduleAddLine(schedule, SCHEDULE_LINE_TRAIN, 10200, "Direct", 24.0)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleAddLine(schedule, SCHEDULE_LINE_TRAIN, 8500, "Intercity", 24.0)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleReportLines(schedule, SCHEDULE_LINE_ALL)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }

    printf("\nAdd stations to train line\n");
    if (schedule_handle_result(scheduleReportStationsForLine(schedule, 8500)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleAddStationToLine(schedule, 8500, "Carmel Beach", 0)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleAddStationToLine(schedule, 8500, "Tel Aviv Savidor", 20)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleReportStationsForLine(schedule, 8500)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleRemoveStationFromLine(schedule, 8500, -1)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleReportStationsForLine(schedule, 8500)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleAddStationToLine(schedule, 8500, "Binyamina", 22)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleReportStationsForLine(schedule, 8500)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleAddStationToLine(schedule, 8500, "Tel Aviv Savidor", 20)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleAddStationToLine(schedule, 8500, "Tel Aviv Savidor", 58)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleReportStationsForLine(schedule, 8500)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }

    printf("\nReport lines\n");
    if (schedule_handle_result(scheduleReportLines(schedule, SCHEDULE_LINE_TRAIN)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleReportLines(schedule, SCHEDULE_LINE_BUS)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    printf("\nReport stations for line\n");
    if (schedule_handle_result(scheduleReportStationsForLine(schedule, 4000)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleReportStationsForLine(schedule, 8500)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }

    printf("\nRemove 1st line\n");
    if (schedule_handle_result(scheduleRemoveLine(schedule, 8500)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleRemoveLine(schedule, 8500)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }

    printf("\nRemove 2nd line\n");
    if (schedule_handle_result(scheduleRemoveLine(schedule, 901)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }

    scheduleDestroy(schedule);

    return SUCCESS;
}

test_result_t test3()
{
    printf("--------------\n");
    printf("Starting test3\n");
    printf("--------------\n");

    Schedule schedule = scheduleCreate();

    printf("\nAdd bus lines\n");
    if (schedule_handle_result(scheduleAddLine(schedule, SCHEDULE_LINE_BUS, 58, "Egged", 9.2)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleAddLine(schedule, SCHEDULE_LINE_BUS, 58, "egged", 9.20)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleAddLine(schedule, SCHEDULE_LINE_BUS, 59, "egged", 9.20)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleAddLine(schedule, SCHEDULE_LINE_BUS, 60, "Metropolin", 9.0)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleAddLine(schedule, SCHEDULE_LINE_BUS, 61, "Metropolin", 8.9)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleAddLine(schedule, SCHEDULE_LINE_BUS, 58, "Kavim", 11.5)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleAddLine(schedule, SCHEDULE_LINE_BUS, 54, "Kavim", 11.5)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }

    printf("\nAdd train lines\n");
    if (schedule_handle_result(scheduleAddLine(schedule, SCHEDULE_LINE_TRAIN, 2000, "Intercity", 33)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleAddLine(schedule, SCHEDULE_LINE_TRAIN, 3000, "unknown", 33)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleAddLine(schedule, SCHEDULE_LINE_TRAIN, 3000, "Suburban", 33)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleAddLine(schedule, SCHEDULE_LINE_TRAIN, 4000, "Direct", 33)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleAddLine(schedule, SCHEDULE_LINE_TRAIN, -7, "Intercity", 33)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }

    printf("\nReport lines\n");
    if (schedule_handle_result(scheduleReportLines(schedule, SCHEDULE_LINE_BUS)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleReportLines(schedule, SCHEDULE_LINE_TRAIN)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }

    printf("\nReport stations for line\n");
    if (schedule_handle_result(scheduleReportStationsForLine(schedule, 2000)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }

    printf("\nAdd stations to bus\n");
    if (schedule_handle_result(scheduleAddStationToLine(schedule, 58, "Carmel Center", 1)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleAddStationToLine(schedule, 58, "Stellamaris", 5)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleAddStationToLine(schedule, 58, "Stellamaris", 14)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleAddStationToLine(schedule, 58, "London", 7)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleAddStationToLine(schedule, 58, "Kiryat Eliezer", 10)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleAddStationToLine(schedule, 158, "Kiryat Eliezer", 10)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleReportStationsForLine(schedule, 58)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }

    printf("\nReport lines between stations\n");
    if (schedule_handle_result(scheduleReportLinesBetweenStations(schedule, "Kiryat Eliezer", "Carmel Center")))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleReportLinesBetweenStations(schedule, "Carmel Center", "Kiryat Eliezer")))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }

    printf("\nRemove stations from line\n");
    if (schedule_handle_result(scheduleRemoveStationFromLine(schedule, 58, 1)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleReportStationsForLine(schedule, 58)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleRemoveStationFromLine(schedule, 58, -1)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleReportStationsForLine(schedule, 58)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleRemoveStationFromLine(schedule, 58, 0)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }
    if (schedule_handle_result(scheduleReportStationsForLine(schedule, 58)))
    {
        scheduleDestroy(schedule);
        return FAIL;
    }

    scheduleDestroy(schedule);

    return SUCCESS;
}

/***/

int main()
{
    const test_func tests[] = {test1, test2, test3};
    return tests[0]();
}
