#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/stat.h>


int temper_read(int temper)
{
	char in[3] = {0, 0, 0};
	char buf[50];
	int nread, hwmonfd;

	sprintf(buf, "/sys/class/hwmon/hwmon0/temp1_input");
	hwmonfd = open(buf, O_RDWR);
	if (hwmonfd < 0) {
		fprintf(stderr, "Failed to open hwmonfd\n");
		perror("hwmon failed");
	}

	do {
		nread = read(hwmonfd, in, 1);
	} while (nread == 0);

	if (nread == -1){
		perror("Temperature Read failed");
		return -1;
	}

	close(hwmonfd);
	return atoi(in);
}

int main()
{
	int temper, i;
	printf("hello world");
	printf("Temperature is %d\n", temper_read(temper));
	
	return 0;		
}
