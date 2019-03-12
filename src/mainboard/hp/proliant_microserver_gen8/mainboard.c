#include <device/device.h>
#include <drivers/intel/gma/int15.h>
#include <southbridge/intel/bd82x6x/pch.h>

static void mainboard_init(struct device *dev)
{
	RCBA32(0x38c8) = 0x00000000;
	RCBA32(0x38c4) = 0x00000000;
}

static void mainboard_enable(struct device *dev)
{
	dev->ops->init = mainboard_init;
}

struct chip_operations mainboard_ops = {
	.enable_dev = mainboard_enable,
};
