#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<termios.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<arpa/inet.h>

void main()
{
   int sockfd,n;
   unsigned char buf[9]="Message\r\n";

      if((sockfd=socket(AF_INET,SOCK_STREAM,0))>0)
       printf("socket created\n");
    

    struct sockaddr_in servaddr;
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(7777);
    servaddr.sin_addr.s_addr=inet_addr("192.168.1.100");
 
    //  if(inet_pton(AF_INET,"192.168.1.20",&clien.sin_addr)>0)
    //     printf("inet_pton sucess\n");
      
      if(connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr))==0)
         printf("connect sucess\n");
     
       while(1){
        printf("in while\r\n");
            
         send(sockfd,buf,strlen(buf),0);
         
           sleep(3);          
        }
}
