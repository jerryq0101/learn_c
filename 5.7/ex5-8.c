#include <stdio.h>

/*
Exercise 5-8. There is no error checking in day_of_year or month_day. Remedy this defect.
*/

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int main(void)
{
        
}

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
        if (year <= 0 || month <= 0 || day <= 0 || month > 12 || year > 2024 || day > 31) {
                return -1;
        }
        int i, leap;
        leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
        for (i = 1; i < month; i++)
                day += daytab[leap][i];
        return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
        if (year <= 0 || year > 2024 || yearday > 366 || yearday <= 0) {
                return -1;
        }

        int i, leap;
        leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
        for (i = 1; yearday > daytab[leap][i]; i++)
                yearday -= daytab[leap][i];
        *pmonth = i;
        *pday = yearday;
}