#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *fp = NULL;
    fp = fopen(argv[1], "rb");

    int cnt = 0;
    while (!feof(fp))
    {
        char buffer[1024];
        fgets(buffer, 1024, fp);
        if (strstr(buffer, "% ref pos"))
        {
            double a[3];
            sscanf(buffer, "%*s%*s%*s%*s\
            %lf%*s\
            %lf%*s\
            %lf%*s",
                   a, a + 1, a + 2);
            for (int index = 0; index < 3; ++index)
            {
                printf("%.4lf\t", a[index]);
            }
        }
        else if (strstr(buffer, "/") && strstr(buffer, ":"))
        {
            ++cnt;
            // 2023/05/18 10:15:02.000| -2843617.0505|  4805398.7558|  3073090.7199|  2| 34|  0.4407|  0.4999|  0.3170| -0.3838|  0.3049| -0.2976|  0.00|   1.3
            int b1[5];
            double b2[5];
            sscanf(buffer, "%d/%d/%d %d:%d:%lf%*s\
            %lf%*s\
            %lf%*s\
            %lf%*s\
            %*s%*s%*s%*s%*s%*s%*s%*s%*s\
            %lf",
                   b1, b1 + 1, b1 + 2, b1 + 3, b1 + 4,
                   b2, b2 + 1, b2 + 2, b2 + 3, b2 + 4);
            for (int index = 0; index < 5; ++index)
            {
                printf("%d ", b1[index]);
            }
            for (int index = 0; index < 5; ++index)
            {
                printf("%.4lf ", b2[index]);
            }
            putchar('\n');
        }
    }

    printf(">>>> cnt = %d\n", cnt);

    fclose(fp);

    return 0;
}