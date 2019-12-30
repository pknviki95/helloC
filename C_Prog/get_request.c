#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<termios.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<arpa/inet.h>

void main(){

char Resource_Name[ ]="Thane_Int2.json";
char IP_Address[ ]="3.105.118.34";
char Port_Number[ ]="8080";
char Get_URL[200]={0};
char recv_data[3048]={0};
printf(" RN : %s\r\n",Resource_Name);
printf(" IP : %s\r\n",IP_Address);
printf(" PN : %s\r\n",Port_Number);
sprintf(Get_URL,"GET /%s HTTP/1.1\r\nHost:%s:%s\r\n\r\n",Resource_Name,IP_Address,Port_Number);
printf("Get Request URL:\r\n%s",Get_URL);
int sd,n,k;

if((sd=socket(AF_INET,SOCK_STREAM,0))>0)
       printf("socket created\n");

    struct sockaddr_in clien;
    memset(&clien,0,sizeof(clien));
    clien.sin_family=AF_INET;
    clien.sin_port=htons(8080);

      if(inet_pton(AF_INET,"3.105.118.34",&clien.sin_addr)>0)
         printf("inet_pton sucess\n");

     if(connect(sd,(struct sockaddr *)&clien,sizeof(clien))==0)
         printf("connect sucess\n");
      
     if(send(sd,Get_URL,strlen(Get_URL),0)>0)
         printf("Send success\r\n");
    if((k=recv(sd,recv_data,3048,0))>0)
       {

         printf("received data:%s\n",recv_data);
         memset(recv_data,0,sizeof(recv_data));
        }

}
