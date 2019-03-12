/*
 * This file is part of the coreboot project.
 * Copyright (C) 2017 Alexander Couzens <lynxis@fe80.eu>
 * Copyright (C) 2019 Philipp Hug <philipp@hug.cx>
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
#include <device/pci_def.h>
#include <device/pci_ops.h>

static DEVTREE_CONST u32 ilo0_base = 0x1000;
static DEVTREE_CONST u32 ilo2_base = 0x1400;

void mainboard_get_spd(spd_raw_data *spd, bool id_only)
{
        pci_devfn_t bridge = PCI_DEV(0, 0x1c, 7);

        /* Setup bus and IO base on bridge */
        pci_write_config32(bridge, PCI_PRIMARY_BUS, 0x10100);
        pci_write_config32(bridge, PCI_IO_BASE, 0x1010); //0x1000-0x1fff

        /* Enable I/O on bridge */
        u16 reg16 = pci_read_config16(bridge, PCI_COMMAND);
        reg16 |= PCI_COMMAND_IO;
        pci_write_config16(bridge, PCI_COMMAND, reg16);


        pci_devfn_t device = PCI_DEV(1, 0, 0);

        u32 id = pci_read_config32(device, PCI_VENDOR_ID);
        switch (id) {
        case 0x3306103c: /* HP Proliant ILO */
                break;
        default:
		printk(BIOS_DEBUG, "wrong device: 0x%x\n", id);
                /* No ILO here. */
                //return -1;
        }

        /* Setup base address on device */
        pci_write_config32(device, PCI_BASE_ADDRESS_0, ilo0_base);
        pci_write_config32(device, PCI_BASE_ADDRESS_2, ilo2_base);

        /* Enable I/O on device */
        reg16 = pci_read_config16(device, PCI_COMMAND);
        reg16 |= PCI_COMMAND_IO;
        pci_write_config16(device, PCI_COMMAND, reg16);

	/* Write 0x10 to register 0xb0 of PCI device 01:00.0 */
	outb(0x10, 0x10b0);

	/* try to read it from the bus */
	read_spd (&spd[0], 0x50, id_only);
	read_spd (&spd[1], 0x51, id_only);
	read_spd (&spd[2], 0x52, id_only);
	read_spd (&spd[3], 0x53, id_only);

	/* Disable I/O on device */
        reg16 = pci_read_config16(device, PCI_COMMAND);
        reg16 &= ~PCI_COMMAND_IO;
        pci_write_config16(device, PCI_COMMAND, reg16);

        /* Disable base address on device */
        pci_write_config32(device, PCI_BASE_ADDRESS_0, 0x00);
        pci_write_config32(device, PCI_BASE_ADDRESS_2, 0x00);

        /* Disable I/O on bridge */
        reg16 = pci_read_config16(bridge, PCI_COMMAND);
        reg16 &= ~PCI_COMMAND_IO;
        pci_write_config16(bridge, PCI_COMMAND, reg16);

        /* Disable I/O on bridge */
        pci_write_config32(bridge, PCI_PRIMARY_BUS, 0x00);
        pci_write_config32(bridge, PCI_IO_BASE, 0x00);
}
