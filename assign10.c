
#include <stdio.h>

int main()
{
    int year, i, j, days, firstDay;

    char *months[] = {
        "January", "February", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December"
    };

    int monthDays[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    printf("Enter year: ");
    scanf("%d", &year);

    // Check leap year
    if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
    {
        monthDays[1] = 29;
    }

    // Find first day of the year
    firstDay = (year + (year - 1) / 4
                - (year - 1) / 100
                + (year - 1) / 400) % 7;

    // Print all 12 months
    for (i = 0; i < 12; i++)
    {
        printf("\n\n       %s %d\n", months[i], year);
        printf(" Sun Mon Tue Wed Thu Fri Sat\n");

        days = monthDays[i];

        // Print blank spaces before first date
        for (j = 0; j < firstDay; j++)
        {
            printf("    ");
        }

        // Print dates
        for (j = 1; j <= days; j++)
        {
            printf("%4d", j);

            if ((firstDay + j) % 7 == 0)
            {
                printf("\n");
            }
        }

        // Calculate first day of next month
        firstDay = (firstDay + days) % 7;
    }

    return 0;
}
