/**
 * @file main_function.c
 * @author Zikang Qin
 * @brief post position data process
 * @version 0.1
 * @date 2023-06-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../include/main.h"

/**
 * @callgraph
 * @brief source data file process, e.g. assign values
 * to base station coordinate, assign values to linked list
 * 
 * @param [in] path_file path of source data file
 * @param [in] valid_ratio ratio threshold
 * @param [in,out] base_station coordinate of base station
 * @param [in,out] rover_station_data linked list to store valid data
 */
void SourceDataProcess(char *path_file, double valid_ratio, double *base_station, List_LinkedList *rover_station_data)
{
    FILE *fp_rover = NULL;
    if ((fp_rover = fopen(path_file, "rb")) == NULL)
    {
        fprintf(stderr, "Cannot open file \"%s\"!\n", path_file);
        exit(EXIT_FAILURE);
    }

    Item_LinkedList item_tmp = {0};
    while (!feof(fp_rover))
    {
        char buffer[1024];
        fgets(buffer, 1024, fp_rover);
        if (strstr(buffer, "% ref pos"))
        {
            // % ref pos   : -2843600.8781|  4805405.9568|  3073120.9033
            sscanf(buffer, "%*s%*s%*s%*s"
                           "%lf%*s"
                           "%lf%*s"
                           "%lf%*s",
                   base_station, base_station + 1, base_station + 2);
        }
        else if (strstr(buffer, "/") && strstr(buffer, ":"))
        {
            // 2023/05/18 10:15:02.000| -2843617.0505|  4805398.7558|  3073090.7199|  2| 34|  0.4407|  0.4999|  0.3170| -0.3838|  0.3049| -0.2976|  0.00|   1.3
            sscanf(buffer, "%d/%d/%d %d:%d:%lf%*s"
                           "%lf%*s"
                           "%lf%*s"
                           "%lf%*s"
                           "%*s%*s%*s%*s%*s%*s%*s%*s%*s"
                           "%lf",
                   &(item_tmp.year), &(item_tmp.month), &(item_tmp.day),
                   &(item_tmp.hour), &(item_tmp.minute), &(item_tmp.second),
                   &(item_tmp.x), &(item_tmp.y), &(item_tmp.z), &(item_tmp.ratio));
        }

        if (!(item_tmp.ratio < valid_ratio) && (IsLinkedListFull(rover_station_data) == 0))
        {
            // fixed solution
            AddItemToLinkedList(item_tmp, rover_station_data);
        }
    }

    fclose(fp_rover);
}