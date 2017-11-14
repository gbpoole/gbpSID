#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <gbpSID.h>

void SID_seconds2ascii(int n_secs, char *string);
void SID_seconds2ascii(int n_secs, char *string) {
    int  n_mins;
    int  n_hrs;
    int  n_days;
    char days_plural_string[2];
    char hrs_plural_string[2];
    char mins_plural_string[2];
    char secs_plural_string[2];
    n_mins = n_secs / 60;
    n_secs -= 60 * n_mins;
    n_hrs = n_mins / 60;
    n_mins -= 60 * n_hrs;
    n_days = n_hrs / 24;
    n_hrs -= 24 * n_days;
    if(n_days == 0 || n_days > 1)
        sprintf(days_plural_string, "s");
    else
        sprintf(days_plural_string, "s");
    if(n_hrs == 0 || n_hrs > 1)
        sprintf(hrs_plural_string, "s");
    else
        sprintf(hrs_plural_string, "s");
    if(n_mins == 0 || n_mins > 1)
        sprintf(mins_plural_string, "s");
    else
        sprintf(mins_plural_string, "s");
    if(n_secs == 0 || n_secs > 1)
        sprintf(secs_plural_string, "s");
    else
        sprintf(secs_plural_string, "s");
    if(n_days > 0)
        sprintf(string,
                "%d day%s, %d hour%s, %d minute%s and %d second%s",
                n_days,
                days_plural_string,
                n_hrs,
                hrs_plural_string,
                n_mins,
                mins_plural_string,
                n_secs,
                secs_plural_string);
    else if(n_hrs > 0)
        sprintf(string, "%d hour%s, %d minute%s and %d second%s", n_hrs, hrs_plural_string, n_mins, mins_plural_string, n_secs, secs_plural_string);
    else if(n_mins > 0)
        sprintf(string, "%d minute%s and %d second%s", n_mins, mins_plural_string, n_secs, secs_plural_string);
    else
        sprintf(string, "%d second%s", n_secs, secs_plural_string);
}
