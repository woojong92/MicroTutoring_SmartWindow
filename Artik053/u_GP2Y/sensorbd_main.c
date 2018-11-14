/*
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
*/

/*
int main(int argc, FAR char *argv[]){
	int fd, ret;
	struct adc_msg_s sample;
	size_t readsize;
	ssize_t nbytes;

	int V_LED=51;//led port번호

	fd=open("/dev/adc0", O_RDONLY);

	printf("ADC Data:\n");

	while(1){


		gpio_write(V_LED, 0);
		usleep(280);
		ret=ioctl(fd,ANIOC_TRIGGER, 0);
		readsize=sizeof(struct adc_msg_s);
		nbytes=read(fd, &sample, sizeof(sample));
		usleep(40);
		gpio_write(V_LED, 1);
		usleep(9680);
		//int nsamples=sizeof(struct adc_msg_s);//?
		if(sample.am_channel==0){
			printf("ADC Channel: %d, value: %d\n", sample.am_channel, sample.am_data);
		}

		//usleep(1000);
	}
	close(fd);
}
*/
/****************************************************************************
 *
 * Copyright 2017 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 *
 ****************************************************************************/
/****************************************************************************
 * examples/examples/sensorbd/examples/adc_test.c
 *
 *   Copyright (C) 2012 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/
#include <stdio.h>
#include <apps/shell/tash.h>

#include <fcntl.h>
#include <tinyara/gpio.h>

#include <errno.h>
#include <fcntl.h>
#include <tinyara/analog/adc.h>
#include <tinyara/analog/ioctl.h>

#define ADC_MAX_SAMPLES	4

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

void main(int argc, char *argv[])
{
	int fd, ret;
	struct adc_msg_s samples;
	size_t readsize;
	ssize_t nbytes;
	int V_LED=51;//led port번호
	float voMeasured=0.0;
	float calcVoltage=0.0;
	float dustDensity=0.0;

	fd = open("/dev/adc0", O_RDONLY);
	if (fd < 0) {
		printf("%s: open failed: %d\n", __func__, errno);
		return;
	}

	ret = ioctl(fd, ANIOC_TRIGGER, 0);
	if (ret < 0) {
		printf("%s: ioctl failed: %d\n", __func__, errno);
		close(fd);
		return;
	}

	for (;;) {
//		ret = ioctl(fd, ANIOC_TRIGGER, 0);
//		if (ret < 0) {
//			printf("%s: ioctl failed: %d\n", __func__, errno);
//			close(fd);
//			return;
//		}
		readsize=sizeof(struct adc_msg_s);

		gpio_write(V_LED, 0);
		usleep(280);

		nbytes = read(fd, &samples, readsize);
		if(samples.am_channel==0){
			voMeasured=samples.am_data;
			printf("channel: %d, value: %d\n",  samples.am_channel, samples.am_data);
		}

		usleep(40);
		gpio_write(V_LED, 1);
		usleep(9680);

		/*
		if (nbytes < 0) {
			if (errno != EINTR) {
				printf("%s: read failed: %d\n", __func__, errno);
				close(fd);
				return;
			}
		} else if (nbytes == 0) {
			printf("%s: No data read, Ignoring\n", __func__);
		} else {
			int nsamples = nbytes / sizeof(struct adc_msg_s);
			if (nsamples * sizeof(struct adc_msg_s) != nbytes) {
				printf("%s: read size=%ld is not a multiple of sample size=%d, Ignoring\n", __func__, (long)nbytes, sizeof(struct adc_msg_s));
			} else {
				printf("Sample:\n");
				int i=0;
				//printf("channel: %d, value: %d\n", samples[i].am_channel, samples[0].am_data);

				for (i = 0; i < nsamples; i++) {
		//			gpio_write(V_LED, 0);
		//			usleep(280);
					if(samples.am_channel==0){
						voMeasured=samples.am_data;
						printf("%d: channel: %d, value: %d\n", i + 1, samples.am_channel, samples.am_data);
					}
		//			usleep(40);
		//			gpio_write(V_LED, 1);
		//			usleep(9680);
				}
			}
		}

		calcVoltage=voMeasured*(0.5/1024.0)*1000;
		dustDensity=(0.17*calcVoltage-0.1);

		printf("dustDensity: %f", dustDensity);
		printf("calcVotage: %f", calcVoltage );
		printf("voMeasured: %f", voMeasured);
		printf("\n\n");
	*/
		usleep(100);
	}

	close(fd);
}

