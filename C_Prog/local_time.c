#include<stdio.h>
#include<string.h>
#include<time.h>
int main(){
printf("Helloworld\r\n");
time_t t;   // not a primitive datatype
    time(&t);

    printf("\nThis program has been writeen at (date and time): %s", ctime(&t));
}
