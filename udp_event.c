
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <event.h>

int recv_count = 0;
void read_event(int fd,short event,void* arg) {
  char buf[1024];
  int len;
  struct event *ev = arg;
  struct sockaddr_in addr;
  int addr_len = sizeof(struct sockaddr) ;
  event_add(ev,NULL);
  int value = 0;

  len = recvfrom(fd, buf, sizeof(buf),0,
		 (struct sockaddr*)&addr,&addr_len);
  
  if (len == 0) {
    return;
  }

  if (len == -1) {
    return;
  }
  
  value = atoi(buf);

  if (recv_count != value) {
    printf("%d %d\n",recv_count,value);
  }
    
  ++recv_count;
  //printf("%s\n",buf);
    
}

int
main()
{
  int sock;
  struct sockaddr_in addr;
  struct event ev;

  char buf[2048];
  sock = socket(AF_INET, SOCK_DGRAM, 0);

  addr.sin_family = AF_INET;
  addr.sin_port = htons(12345);
  addr.sin_addr.s_addr = INADDR_ANY;

  bind(sock, (struct sockaddr *)&addr, sizeof(addr));

  event_init();
  event_set(&ev,sock,EV_READ|EV_PERSIST,read_event,&ev);
  event_add(&ev,NULL);
  event_dispatch();


  close(sock);

  return 0;
}
