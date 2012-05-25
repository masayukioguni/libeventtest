#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>


int
main()
{
 int sock;
 struct sockaddr_in addr;
 int n = 0;
 char buf[2048];
 sock = socket(AF_INET, SOCK_DGRAM, 0);

 addr.sin_family = AF_INET;
 addr.sin_port = htons(12345);
 addr.sin_addr.s_addr = inet_addr("127.0.0.1");

 for (n = 0;n < 10000;++n) {
   sprintf(buf,"%d",n+1);
   sendto(sock, buf, sizeof(buf), 0, (struct sockaddr *)&addr, sizeof(addr));
 }


 close(sock);

 return 0;
}
