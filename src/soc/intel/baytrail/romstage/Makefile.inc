cpu_incs-y += $(src)/soc/intel/baytrail/romstage/cache_as_ram.inc
cpu_incs-y += $(obj)/fmap_config.h
romstage-y += romstage.c
romstage-y += raminit.c
romstage-$(CONFIG_ENABLE_BUILTIN_COM1) += uart.c
romstage-y += gfx.c
romstage-y += pmc.c
romstage-y += early_spi.c
