#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <string.h>
void main(int argc, char *argv[])
{
	int fd;
	char *pdata;
	fd = open("/dev/mmap",O_RDWR|O_NDELAY);
	printf("the fd is : %d\n",fd);	
	pdata = (char *)mmap(0,4096,PROT_READ | PROT_WRITE, MAP_SHARED,
							 fd, 772128768);
                                 
    printf("the phys_addr = 0x%X\n",(int)(*pdata));
    printf("date from kernel : %s\n",pdata);
	printf("Writing a string to kernel space ......\n");
	strcpy(pdata,argv[1]);
		

	munmap(pdata,4096);
	printf("finished\n");		
	close(fd);
}

