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
 * examples/examples/sensorbd/examples/gpio_buttons.c
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
#include <tinyara/config.h>

#include <fcntl.h>
#include <poll.h>
#include <sys/types.h>
#include <unistd.h>

#include <tinyara/gpio.h>

void switch_main(int argc, char *argv[])
{
	int i, j, nbtns, prev;
	struct pollfd *poll_list;

	struct {
		char *name;
		char *devpath;
		int fd;
	} buttons[] = {
		{ "XEINT_0", "/dev/gpio57", },
		{ "XEINT_1", "/dev/gpio58", },
		{ "XEINT_2", "/dev/gpio59", },
	};

	nbtns = sizeof(buttons) / sizeof(*buttons);

	poll_list = (struct pollfd *)malloc(sizeof(struct pollfd) * nbtns);

	for (i = 0; i < nbtns; i++) {
		printf("Opening %s(%s)...\n", buttons[i].devpath, buttons[i].name);
		poll_list[i].fd = open(buttons[i].devpath, O_RDWR);
		poll_list[i].events = POLLIN;
	}

	printf("Polling buttons...\n");
	printf("(to terminate, press the same button twice in a row)\n");

	prev = -1;
	while (1) {
		if (poll(poll_list, nbtns, 100)) {
			for (j = 0; j < nbtns; j++) {
				if (poll_list[j].revents & POLLIN) {
					char buf[4];
					lseek(poll_list[j].fd, 0, SEEK_SET);
					read(poll_list[j].fd, buf, sizeof(buf));
					printf("%s is %s\n", buttons[j].name,
						buf[0] == '1' ? "rising" : "falling");

					if (buf[0] == '1') {
						if (prev == j) {
							goto out;
						}
						prev = j;
					}
				}
			}
		}
	}

out:
	for (i = 0; i < nbtns; i++) {
		printf("Closing %s(%s)...\n", buttons[i].devpath, buttons[i].name);
		close(poll_list[i].fd);
	}

	free(poll_list);
}
