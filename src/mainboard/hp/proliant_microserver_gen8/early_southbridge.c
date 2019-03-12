#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <timestamp.h>
#include <arch/byteorder.h>
#include <arch/io.h>
#include <device/pci_def.h>
#include <device/pnp_def.h>
#include <cpu/x86/lapic.h>
#include <arch/acpi.h>
#include <console/console.h>
#include "northbridge/intel/sandybridge/sandybridge.h"
#include "northbridge/intel/sandybridge/raminit_native.h"
#include "southbridge/intel/bd82x6x/pch.h"
#include <southbridge/intel/common/gpio.h>
#include <superio/serverengines/pilot/pilot.h>
#include <arch/cpu.h>
#include <cpu/x86/msr.h>

#define SERIAL_DEV PNP_DEV(0x2e, PILOT_SP1)

void pch_enable_lpc(void)
{
	pci_write_config16(PCI_DEV(0, 0x1f, 0), 0x82, 0x340a);
	pci_write_config32(PCI_DEV(0, 0x1f, 0), 0x84, 0x00fc0801);
	pci_write_config32(PCI_DEV(0, 0x1f, 0), 0x88, 0x000c0ca1);
	pci_write_config32(PCI_DEV(0, 0x1f, 0), 0x8c, 0x000c0cd1);
	pci_write_config32(PCI_DEV(0, 0x1f, 0), 0x90, 0x001c0311);
	pci_write_config16(PCI_DEV(0, 0x1f, 0), 0x80, 0x0010);
	pci_write_config32(PCI_DEV(0, 0x1f, 0), 0xac, 0x40000300);
}

void mainboard_rcba_config(void)
{
	/* Disable devices.  */
	RCBA32(0x3414) = 0x00000020;
	//RCBA32(0x3418) = 0x1f2e1ff9;

}
const struct southbridge_usb_port mainboard_usb_ports[] = {
	{ 1, 0, 0 },
	{ 1, 0, 0 },
	{ 1, 0, 1 },
	{ 1, 0, 1 },
	{ 1, 0, 2 },
	{ 1, 0, 2 },
	{ 1, 0, 3 },
	{ 1, 0, 3 },
	{ 1, 0, 4 },
	{ 1, 0, 4 },
	{ 1, 0, 5 },
	{ 1, 0, 5 },
	{ 1, 0, 6 },
	{ 1, 0, 6 },
};

void mainboard_early_init(int s3resume)
{
}

void mainboard_config_superio(void)
{
	pilot_early_init(SERIAL_DEV); //config port is being taken from SERIAL_DEV
}

