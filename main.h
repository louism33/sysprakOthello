#ifndef SYSPRAKOTHELLO_MAIN
#define SYSPTAKOTHELLO_MAIN




#include <sys/types.h>
/*File-deskriptor für die Pipe*/
int pd[2];
pid_t thinker;
pid_t connector;
int shmid;
void mysighandler(int sig);
int main(int argc, char *argv[]);


int running = 1, event_count, i;
size_t bytes_read;
char read_buffer[READ_SIZE + 1];
struct epoll_event event, events[MAX_EVENTS];



#endif //SYSPTAKOTHELLO_MAIN