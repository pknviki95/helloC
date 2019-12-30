//https://stackoverflow.com/questions/22077802/simple-c-example-of-doing-an-http-post-and-consuming-the-response
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<termios.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>
void main(){

char Post_Data[10]="Testing";
char IP_Address[ ]="13.58.100.229";
char Port_Number[ ]="3000";
char Get_URL[200]={0};
char recv_data[3048]={0};
printf(" IP : %s\r\n",IP_Address);
printf(" PN : %s\r\n",Port_Number);
char Header[1000]={0};
int len;



strcpy(Header, "POST ");
strcat(Header, "http://13.58.100.229:3000");
strcat(Header, " HTTP/1.1\r\n");
strcat(Header, "Content-Type: text/plain\r\n");
strcat(Header, "HOST:");
strcat(Header, IP_Address);
strcat(Header, ":");
strcat(Header, Port_Number);
strcat(Header, "\r\n");
strcat(Header, "Content-Length: 7\r\n\r\n");
strcat(Header, Post_Data);
strcat(Header, "\r\n");
//sprintf(Get_URL,"GET /%s HTTP/1.1\r\nHost:%s:%s\r\n\r\n",Resource_Name,IP_Address,Port_Number);
printf("Post Header:\r\n%s",Header);
int sd,n,k;

if((sd=socket(AF_INET,SOCK_STREAM,0))>0)
       printf("socket created\n");

    struct sockaddr_in clien;
    memset(&clien,0,sizeof(clien));
    clien.sin_family=AF_INET;
    clien.sin_port=htons(3000);
    clien.sin_addr.s_addr = inet_addr("13.58.100.229");

     if(connect(sd,(struct sockaddr *)&clien,sizeof(clien))==0)
         printf("connect sucess\n");
      
     if(send(sd,Header,strlen(Header),0)>0)
         printf("Send success\r\n");
    if((k=recv(sd,recv_data,3048,0))>0)
       {

         printf("received data:%s\n",recv_data);
         memset(recv_data,0,sizeof(recv_data));
        }

}
