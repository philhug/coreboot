/*
 * This file is part of the coreboot project.
 * Copyright (C) 2017 Alexander Couzens <lynxis@fe80.eu>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <stdint.h>
#include <string.h>
#include <lib.h>

#include <arch/byteorder.h>
#include <cbfs.h>
#include <console/console.h>
#include <northbridge/intel/sandybridge/raminit_native.h>

void mainboard_get_spd(spd_raw_data *spd, bool id_only)
{
        uint8_t *spd_file;
        size_t spd_file_len;

        spd_file = cbfs_boot_map_with_leak("spd.bin", CBFS_TYPE_SPD,
                                                &spd_file_len);
        if (!spd_file)
                die("SPD data not found.");

        if (spd_file_len < 256)
                die("Missing SPD data.");

	memcpy(&spd[0], spd_file, 256);
	//memcpy(&spd[1], spd_file, 256);
	//memcpy(&spd[2], spd_file, 256);
	//memcpy(&spd[3], spd_file, 256);
}

