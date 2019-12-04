#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<time.h>
#define PORT 123
#define SERVER "129.6.15.27"
#define NTP_TIMESTAMP_DELTA 2208988800ull

#define LI(packet)   (uint8_t) ((packet.li_vn_mode & 0xC0) >> 6) // (li   & 11 000 000) >> 6
#define VN(packet)   (uint8_t) ((packet.li_vn_mode & 0x38) >> 3) // (vn   & 00 111 000) >> 3
#define MODE(packet) (uint8_t) ((packet.li_vn_mode & 0x07) >> 0) // (mode & 00 000 111) >> 0

struct clock{
    int sec;         /* seconds */
    int min;         /* minutes */
    int hour;        /* hours */
    int mday;        /* day of the month */
    int mon;         /* month */
    int year;        /* year */
    int wday;        /* day of the week */
    int yday;        /* day in the year */
    int isdst;       /* daylight saving time */
};
struct clock *RTC;
void my_NTP(void);
int main(){

printf("in main\r\n");

my_NTP();

}
void UTC_Time();
void my_NTP(){

int sockfd,n;

struct tm *info;
typedef struct
  {

    uint8_t li_vn_mode;      // Eight bits. li, vn, and mode.
                             // li.   Two bits.   Leap indicator.
                             // vn.   Three bits. Version number of the protocol.
                             // mode. Three bits. Client will pick mode 3 for client.

    uint8_t stratum;         // Eight bits. Stratum level of the local clock.
    uint8_t poll;            // Eight bits. Maximum interval between successive messages.
    uint8_t precision;       // Eight bits. Precision of the local clock.

    uint32_t rootDelay;      // 32 bits. Total round trip delay time.
    uint32_t rootDispersion; // 32 bits. Max error aloud from primary clock source.
    uint32_t refId;          // 32 bits. Reference clock identifier.

    uint32_t refTm_s;        // 32 bits. Reference time-stamp seconds.
    uint32_t refTm_f;        // 32 bits. Reference time-stamp fraction of a second.

    uint32_t origTm_s;       // 32 bits. Originate time-stamp seconds.
    uint32_t origTm_f;       // 32 bits. Originate time-stamp fraction of a second.

    uint32_t rxTm_s;         // 32 bits. Received time-stamp seconds.
    uint32_t rxTm_f;         // 32 bits. Received time-stamp fraction of a second.

    uint32_t txTm_s;         // 32 bits and the most important field the client cares about. Transmit time-stamp seconds.
    uint32_t txTm_f;         // 32 bits. Transmit time-stamp fraction of a second.

  } ntp_packet;              // Total: 384 bits or 48 bytes.

  ntp_packet packet = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

  memset( &packet, 0, sizeof( ntp_packet ) );

  *( ( char * ) &packet + 0 ) = 0x1b; 

  sockfd = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP ); // Create a UDP socket.

  if ( sockfd < 0 )
    printf( "ERROR opening socket" );

    struct sockaddr_in servaddr;
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(PORT);
    servaddr.sin_addr.s_addr=inet_addr(SERVER);

  if(connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr))==0)
         printf("connect sucess\n");
  
  // Send it the NTP packet it wants. If n == -1, it failed.

  n = write( sockfd, ( char* ) &packet, sizeof( ntp_packet ) );

  if ( n < 0 )
    printf( "ERROR writing to socket" );

  // Wait and receive the packet back from the server. If n == -1, it failed.

  n = read( sockfd, ( char* ) &packet, sizeof( ntp_packet ) );

  if ( n < 0 )
    printf( "ERROR reading from socket" );


  packet.txTm_s = ntohl( packet.txTm_s ); // Time-stamp seconds.
  packet.txTm_f = ntohl( packet.txTm_f ); // Time-stamp fraction of a second.
  printf("Secsinc1900:%lu\r\n",packet.txTm_s);

  time_t txTm = ( time_t ) ( packet.txTm_s - NTP_TIMESTAMP_DELTA );
  info = gmtime(&txTm);
  printf("UTC Time: %02d/%02d/%04d,%02d:%02d:%02d\r\n",info->tm_mday,info->tm_mon,(info->tm_year + 1900),info->tm_hour,info->tm_min,info->tm_sec);
  RTC=info;
  UTC_Time();


  
 
  unsigned long epoch= ( packet.txTm_s - NTP_TIMESTAMP_DELTA );
  printf("epoch %lu\r\n",epoch);

  close(sockfd);
}


void UTC_Time(){
   printf("%s: %02d/%02d/%04d,%02d:%02d:%02d\r\n",__func__,RTC->mday,RTC->mon,(RTC->year+1900),RTC->hour,RTC->min,RTC->sec);
}
