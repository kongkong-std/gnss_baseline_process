#include "../include/main.h"

int main(int argc, char **argv)
{
    char *file_baseline = argv[1]; // path of baseline file

    double base_station[3] = {0};
    List_LinkedList *rover_station_data = NULL;

    if ((rover_station_data = (List_LinkedList *)malloc(sizeof(List_LinkedList))) == NULL)
    {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    InitializeLinkedList(rover_station_data);

    SourceDataProcess(file_baseline, base_station, rover_station_data);

    // free memory
    free(rover_station_data);

    return 0;
}
