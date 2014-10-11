#include <stdio.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
void main()
{
   int fd ; 
   long long unsigned int buf;
   fd = open("/dev/mmap",O_RDWR);
   read(fd, &buf, 100);
   printf(" 0x%X", buf);
   close(fd);
}
