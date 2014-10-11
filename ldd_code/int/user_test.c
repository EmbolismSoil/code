#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void test_handler(int sigio)
{
    printf("get signal\n");
}
void main()
{
     int fd,oflags;
    struct sigaction sigact,oldact;
    fd = open("/dev/globalmem",O_RDWR);
    sigact.sa_flags = 0;
    sigact.sa_handler = test_handler;  
    
    if( sigaction(SIGIO, &sigact, &oldact) < 0 )
	printf("set handler filed\n");

    fcntl(fd, F_SETOWN, getpid());   
    oflags = fcntl(fd, F_GETFL);
    fcntl(fd, F_SETFL, oflags|FASYNC);     
    while(1)
	sleep(1000);

}
