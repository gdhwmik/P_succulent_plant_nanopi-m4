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

    con_hwmon_temp.dev = 0;
    con_hwmon_temp.hwmon_buf = &hwmon_con_buf[0];

    sprintf(hwmon_temp_path, "%s/%s/%s", HWMON_SYS_DEV, HWMON_DEV, HWMON_TEMP);
    con_hwmon_temp.hwmon_path = hwmon_temp_path;
	printf("%s\n",hwmon_temp_path);

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

/*		i = 0;
		while (1) {
			if (str_temp[i] == 0x0a) {
				str_temp[i] = 0;
				str_temp[i + 1] = 0;
				break;
			}
			i++;
		}
*/		int_temp = atoi(str_temp);
		printf("Temp %d\r\n", int_temp);

		close(fd);
		usleep(1000000);
	};

    return 0;
}
