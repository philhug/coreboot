/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2018 Jonathan Neuschäfer
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

#include <arch/io.h>
#include <bootblock_common.h>
#include <console/console.h>
#include <console/uart.h>
#include <soc/addressmap.h>

void bootblock_soc_init(void)
{
	printk(BIOS_INFO, "Boot mode: %d\n", read32((uint32_t *)FU540_MSEL));
}

void bootblock_soc_early_init(void)
{
#if (IS_ENABLED(CONFIG_CONSOLE_SERIAL))
        uart_init(CONFIG_UART_FOR_CONSOLE);
#endif
}
