#include <stdio.h>
#include <apps/shell/tash.h>

#include <fcntl.h>
#include <tinyara/gpio.h>

#include <errno.h>
#include <fcntl.h>
#include <tinyara/analog/adc.h>
#include <tinyara/analog/ioctl.h>

int gpio_read(int port)
{
	char buf[4];
	char devpath[16];
	snprintf(devpath, 16, "/dev/gpio%d", port);
	int fd = open(devpath, O_RDWR);

	read(fd, buf, sizeof(buf));
	close(fd);

	return buf[0] == '1';
}

void gpio_write(int port, int value)
{
	char buf[4];
	char devpath[16];
	snprintf(devpath, 16, "/dev/gpio%d", port);
	int fd = open(devpath, O_RDWR);

	ioctl(fd, GPIOIOC_SET_DIRECTION, GPIO_DIRECTION_OUT);
	write(fd, buf, snprintf(buf, sizeof(buf), "%d", !!value));
	close(fd);
}

int main(int argc, FAR char *argv[]){
	int fd, ret;
	struct adc_msg_s sample;
	size_t readsize;
	ssize_t nbytes;

	fd=open("/dev/adc0", O_RDONLY);

	printf("ADC Data:\n");

	while(1){

		ret=ioctl(fd,ANIOC_TRIGGER, 0);

		readsize=sizeof(struct adc_msg_s);
		nbytes=read(fd, &sample, readsize);

		int nsamples=sizeof(struct adc_msg_s);//?
		if(sample.am_channel==0){
			printf("ADC Channel: %d, value: %d\n", sample.am_channel, sample.am_data);
		}
		usleep(1000);
	}
	close(fd);
}
