#ifndef SYSPRAKOTHELLO_MAIN
#define SYSPTAKOTHELLO_MAIN

#define MAX_EVENTS 5
#define READ_SIZE 10

#include <stdio.h>     // for fprintf()
#include <unistd.h>    // for close()
#include <sys/epoll.h> // for epoll_create1()


#include <string.h>

#include <sys/types.h>
/*File-deskriptor für die Pipe*/
int pd[2];
pid_t thinker;
pid_t connector;
int shmid;
void mysighandler(int sig);
int main(int argc, char *argv[]);


//int running = 1;
int event_count, i;
size_t bytes_read;
char read_buffer[READ_SIZE + 1];
struct epoll_event event, events[MAX_EVENTS];

int epoll_fd;

#endif //SYSPTAKOTHELLO_MAIN