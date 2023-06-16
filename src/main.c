#include "../include/main.h"

void DisplayItem(Item_LinkedList);

int main(int argc, char **argv)
{
    char *file_baseline = argv[1]; // path of baseline file

    double base_station[3] = {0};
    double sol_rover_station[3] = {0};
    List_LinkedList *rover_station_data = NULL;

    if ((rover_station_data = (List_LinkedList *)malloc(sizeof(List_LinkedList))) == NULL)
    {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    InitializeLinkedList(rover_station_data);

    SourceDataProcess(file_baseline, base_station, rover_station_data);

#if 0 // linked list display
    TraverseLinkedList(rover_station_data, DisplayItem);
#endif

    BaseLineRREImpl(rover_station_data, base_station, sol_rover_station);

#if 1 // display solution
    puts("======== baseline solution of RRE ========");
    for (int index = 0; index < 3; ++index)
    {
        printf("%.4lf\n", sol_rover_station[index]);
    }

    puts( "======== position solution of RRE ========" );
    for( int index = 0; index < 3; ++index )
    {
        printf( "%.4lf\n", sol_rover_station[index] + base_station[index] );
    }
#endif

    // free memory
    DestroyLinkedList(rover_station_data);
    free(rover_station_data);

    return 0;
}

void DisplayItem(Item_LinkedList item)
{
    printf("%d/%d/%d %d:%d:%.4lf\t%.4lf\t%.4lf%.4lf\t%.4lf",
           item.year, item.month, item.day, item.hour, item.minute, item.second,
           item.x, item.y, item.z, item.ratio);
}
