/**
 * @file main.c
 * @author Zikang Qin
 * @brief main function, baseline data process,
 * fusing valid datas within a time period into
 * a data output
 * 
 * @version 0.1
 * @date 2023-06-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../include/main.h"

void DisplayItem(Item_LinkedList);

// int RREFilter( char * post_pos_path/*postpos file path*/, double * rre_solution/*rre filter solution, size = 3*/ )
/**
 * @callgraph
 * @brief process valid baseline source data
 * 
 * @param [in] argc command line parameter 
 * @param [in] argv command line parameter, path of baseline file
 * @return int 
 */
int main(int argc, char **argv)
{
    char *file_baseline = argv[1]; // path of baseline file
    double valid_ratio = 3.;

    double base_station[3] = {0};
    double sol_rover_station[3] = {0};
    List_LinkedList *rover_station_data = NULL;

    if ((rover_station_data = (List_LinkedList *)malloc(sizeof(List_LinkedList))) == NULL)
    {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    InitializeLinkedList(rover_station_data);

    SourceDataProcess(file_baseline, valid_ratio, base_station, rover_station_data);

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

/**
 * @callgraph
 * @brief display struct item
 * 
 * @param [in] item struct variable 
 */
void DisplayItem(Item_LinkedList item)
{
    printf("%d/%d/%d %d:%d:%.4lf\t%.4lf\t%.4lf%.4lf\t%.4lf",
           item.year, item.month, item.day, item.hour, item.minute, item.second,
           item.x, item.y, item.z, item.ratio);
}
