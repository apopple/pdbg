/* Copyright 2016 IBM Corp.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * 	http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 * implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <backend.h>
#include <operations.h>
#include <target.h>
#include <device.h>

#include <config.h>

#include "bitutils.h"

/* TODO: It would be nice to have a more dynamic way of doing this */
extern unsigned char _binary_fake_dtb_o_start;
extern unsigned char _binary_fake_dtb_o_end;

static int putscom(struct target *target, uint32_t index, uint64_t *unused, uint64_t *unused1)
{
	pib_write(target, 0x10012200, 0xdeadbeef);
	pib_write(target, 0x11012200, 0xdeadbeef);

	return 1;
}

int main(int argc, char *argv[])
{
	targets_init(&_binary_fake_dtb_o_start);
	target_probe();

	return for_each_child_target("pib", NULL, putscom, NULL, NULL);
}
