#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <getopt.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

#define HWMON_SYS_DEV "/sys/class/hwmon/"
#define HWMON_DEV "hwmon0"
#define HWMON_TEMP "temp1_input"
#define UPPER_TEMP 34000
#define LOWER_TEMP 32750


int gpio_direction(int gpio, int dir)
{
	int ret = 0;
	char buf[50];

	sprintf(buf, "/sys/class/gpio/gpio%d/direction", gpio);
	int gpiofd = open(buf, O_WRONLY);
	if (gpiofd < 0) {
		perror("Couldn't open IRQ file");
		ret = -1;
	}

	if (dir == 2 && gpiofd){
		if (3 != write(gpiofd, "high", 3)) {
			perror("Couldn't set GPIO direction to out");
			ret = -2;
		}
	}

	if (dir == 1 && gpiofd){
		if (3 != write(gpiofd, "out", 3)) {
			perror("Couldn't set GPIO direction to out");
			ret = -3;
		}
	} else if (gpiofd) {
		if(2 != write(gpiofd, "in", 2)) {
			perror("Couldn't set GPIO directio to in");
			ret = -4;
		}
	}

	close(gpiofd);
	return ret;
}

int gpio_export(int gpio)
{
	int efd;
	char buf[50];
	int gpiofd, ret;

	/* Quick test if it has already been exported */
	sprintf(buf, "/sys/class/gpio/gpio%d/value", gpio);
	efd = open(buf, O_WRONLY);
	if (efd != -1) {
		close(efd);
		return 0;
	}

	efd = open("/sys/class/gpio/export", O_WRONLY);
	if (efd != -1) {
		sprintf(buf, "%d", gpio);
		ret = write(efd, buf, strlen(buf));
		if(ret < 0) {
			perror("Export failed");
			return -2;
		}
		close(efd);
	} else {
		// If we can't open the export file, we probably
		// dont have any gpio permissions
		return -1;
	}

	return 0;
}

int gpio_read(int gpio)
{
	char in[3] = {0, 0, 0};
	char buf[50];
	int nread, gpiofd;

	sprintf(buf, "/sys/class/gpio/gpio%d/value", gpio);
	gpiofd = open(buf, O_RDWR);
	if (gpiofd < 0) {
		fprintf(stderr, "Failed to open gpio %d value\n", gpio);
		perror("gpio failed");
	}

	do {
		nread = read(gpiofd, in, 1);
	} while (nread == 0);

	if (nread == -1){
		perror("GPIO Read failed");
		return -1;
	}

	close(gpiofd);
	return atoi(in);
}

int gpio_write(int gpio, int val)
{
	char buf[50];
	int nread, ret, gpiofd;

	sprintf(buf, "/sys/class/gpio/gpio%d/value", gpio);  
	gpiofd = open(buf, O_RDWR);							 
	if (gpiofd > 0) {
		snprintf(buf, 2, "%d", val);					 
		ret = write(gpiofd, buf, 2);					 
		if (ret < 0) {
			perror("failed to set gpio");
			return 1;
		}

		close(gpiofd);
		if (ret == 2) return 0;							 
	}

	return 1;
}



struct sys_hwmon {
	int dev;
	char *hwmon_buf;
    char *hwmon_path;
};

int main()
{
    int fd;
    int port, duty = -1, period;
    int set_duty = 0, set_period = 0;
    char hwmon_temp_path[50];
    char hwmon_con_buf[50];
    int i, ret, readbuf_cnt;
    struct sys_hwmon con_hwmon_temp;
    char str_temp[10];
    int int_temp;
    size_t count;
	int gpio_on, gpio_off;
	int gpio_k1, gpio_k4;
	
    con_hwmon_temp.dev = 0;
    con_hwmon_temp.hwmon_buf = &hwmon_con_buf[0];

    sprintf(hwmon_temp_path, "%s/%s/%s", HWMON_SYS_DEV, HWMON_DEV, HWMON_TEMP);
    con_hwmon_temp.hwmon_path = hwmon_temp_path;

    ret = access(hwmon_temp_path, R_OK | W_OK);
    if (ret) {
        printf("access hwmon_temp_path fail\r");
		exit(1);
	}

	count = 10;

	while (1) 
	{

		fd = open(hwmon_temp_path, O_ASYNC, S_IRUSR | S_IRGRP | S_IROTH);
		if (fd < 0) {
			printf("open %s fail\r\n", hwmon_temp_path);
			exit(1);
		}

		readbuf_cnt = read(fd, str_temp, count);
		if (readbuf_cnt >= count || readbuf_cnt < 0) {
			printf("read temp fail\n");
			exit(1);
		}

		int_temp = atoi(str_temp);
		printf("Temp %d\r\n", int_temp);

		close(fd);
		
		gpio_k1 = 144; gpio_k4 = 50;
		gpio_k1 = gpio_read (gpio_k1);
		printf("gpio_k1 = %d", gpio_k1 );
		
		if (int_temp > UPPER_TEMP )
		{
			printf("on 33");
			gpio_on = 33;
			gpio_export(gpio_on);
			gpio_direction(gpio_on, 1);
			gpio_write(gpio_on, 0);
			gpio_off = 32;
			gpio_export(gpio_off);
			gpio_write(gpio_off, 1);
		}
		if (int_temp < LOWER_TEMP)
		{
			printf("on 32");
			gpio_on = 32;
			gpio_export(gpio_on);
			gpio_direction(gpio_on, 1);
			gpio_write(gpio_on, 0);
			gpio_off = 33;
			gpio_export(gpio_off);
			gpio_write(gpio_off, 1);
		}
		sleep(4);
	};

    return 0;
}
