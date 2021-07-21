#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/stat.h>

int main()
{
	int temper;
	char buf[50];
	int nread, hwmonfd;

	buf = "/sys/class/hwmon/hwmon0/temp1_input" ;
	hwmonfd = open(buf, O_RDWR);
	if (hwmonfd < 0) {
		fprintf(stderr, "Failed to open hwmon0 temp1\n");
		perror("hwmon failed");
	}

	do {
		nread = read(hwmonfd, temper, 5);
	} while (nread == 0);

	if (nread == -1){
		perror("Temperature Read failed");
		return -1;
	}

	close(hwmonfd);
	printf("Temperature is %d",temper);
	
	return 0;
}
