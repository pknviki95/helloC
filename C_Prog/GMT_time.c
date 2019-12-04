#include <stdio.h>
#include <time.h>
int main(){

struct tm *info;
time_t raw_time;

time(&raw_time);

printf("local time: %s\r\n",ctime(&raw_time)); 

info =gmtime(&raw_time);

printf("UTC Time: %02d/%02d/%04d,%02d:%02d:%02d\r\n",info->tm_mday,info->tm_mon,(info->tm_year + 1900),info->tm_hour,info->tm_min,info->tm_sec);

//printf("UTC time: %s\r\n",gmttime(&raw_time));
}
