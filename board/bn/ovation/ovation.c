/*
 * (C) Copyright 2014
 * Ahmad Draidi <ar2000jp@gmail.com>
 *
 * (C) Copyright 2010
 * Texas Instruments Incorporated, <www.ti.com>
 * Aneesh V       <aneesh@ti.com>
 * Steve Sakoman  <steve@sakoman.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#include <common.h>
#include <asm/gpio.h>
#include <asm/arch/sys_proto.h>
#include <asm/arch/mmc_host_def.h>

#define GPIO_HW_ID5	49
#define GPIO_HW_ID6	50
#define GPIO_HW_ID7	51

DECLARE_GLOBAL_DATA_PTR;

const struct omap_sysinfo sysinfo = {
	"Board: OMAP4 BN Ovation\n"
};

int board_init(void)
{
	gd->bd->bi_boot_params = (0x80000000 + 0x100); /* boot param addr */

	return 0;
}

void set_muxconf_regs_essential(void)
{
	return;
}

int misc_init_r(void)
{
	return 0;
}

#if !defined(CONFIG_SPL_BUILD) && defined(CONFIG_GENERIC_MMC)
int board_mmc_init(bd_t *bis)
{
	omap_mmc_init(0, 0, 0, -1, -1);
	omap_mmc_init(1, 0, 0, -1, -1);
	return 0;
}
#endif

u32 get_board_rev(void)
{
	u8 hw_id5, hw_id6, hw_id7;

	hw_id5 = gpio_get_value(GPIO_HW_ID5);
	hw_id6 = gpio_get_value(GPIO_HW_ID6);
	hw_id7 = gpio_get_value(GPIO_HW_ID7);

	return ((hw_id5 << 2) + (hw_id6 << 1) + (hw_id7));
}

void get_board_serial(struct tag_serialnr *serialnr){
	/* Stub, for now. */
	serialnr->low = 123;
	serialnr->high = 456;
}

phys_size_t get_effective_memsize(void){
	return 0x40000000;
}

void dram_init_banksize(void)
{
	gd->bd->bi_dram[0].start = CONFIG_SYS_SDRAM_BASE;
	gd->bd->bi_dram[0].size = 0x40000000;
	gd->ram_size = 0x40000000;
}
