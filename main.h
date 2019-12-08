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




#endif //SYSPTAKOTHELLO_MAIN