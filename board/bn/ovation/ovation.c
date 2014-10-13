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
#include <video_fb.h>
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

#define DISPC_CONTROL1_REG_ADDR		0x48041040
#define DISPC_CONTROL1_GOLCD		(1 << 5)

#define DISPC_GFX_SIZE_REG_ADDR		0x4804108C
#define DISPC_GFX_SIZE_SIZEX(x)		(((x) - 1) & 0x7FF)
#define DISPC_GFX_SIZE_SIZEY(y)		((((y) - 1) & 0x7FF) << 16)
#define DISPC_GFX_SIZE_SIZEX_MASK	(0x7FF)
#define DISPC_GFX_SIZE_SIZEY_MASK	(0x7FF << 16)

#define DISPC_GFX_POSITION_REG_ADDR	0x48041088
#define DISPC_GFX_POSITION_POSX(x)	((x) & 0x7FF)
#define DISPC_GFX_POSITION_POSY(y)	(((y) & 0x7FF) << 16)
#define DISPC_GFX_POSITION_POSX_MASK	(0x7FF)
#define DISPC_GFX_POSITION_POSY_MASK	(0x7FF << 16)

#define DISPC_GFX_ATTRIBUTES_REG_ADDR	0x480410A0
#define DISPC_GFX_ATTRIBUTES_ENABLE	(1)
#define DISPC_GFX_ATTRIBUTES_FORMAT_XRGB24_8888	((0x08) << 1)
#define DISPC_GFX_ATTRIBUTES_FORMAT_MASK (0x0F << 1)

GraphicDevice gdev;

void *video_hw_init(void)
{
	/* Since the display subsystems are already initialized, we only change what we need. */

	/* Stop display controller */
	clrbits_le32(DISPC_GFX_ATTRIBUTES_REG_ADDR, DISPC_GFX_ATTRIBUTES_ENABLE);

	/* Set display size */
	clrbits_le32(DISPC_GFX_SIZE_REG_ADDR, DISPC_GFX_SIZE_SIZEX_MASK);
	clrbits_le32(DISPC_GFX_SIZE_REG_ADDR, DISPC_GFX_SIZE_SIZEY_MASK);
	setbits_le32(DISPC_GFX_SIZE_REG_ADDR, DISPC_GFX_SIZE_SIZEX(OVATION_LCD_SIZEX));
	setbits_le32(DISPC_GFX_SIZE_REG_ADDR, DISPC_GFX_SIZE_SIZEY(OVATION_LCD_SIZEY));

	/* Set window position */
	clrbits_le32(DISPC_GFX_POSITION_REG_ADDR, DISPC_GFX_POSITION_POSX_MASK);
	clrbits_le32(DISPC_GFX_POSITION_REG_ADDR, DISPC_GFX_POSITION_POSY_MASK);
	setbits_le32(DISPC_GFX_POSITION_REG_ADDR, DISPC_GFX_POSITION_POSX(OVATION_LCD_POSX));
	setbits_le32(DISPC_GFX_POSITION_REG_ADDR, DISPC_GFX_POSITION_POSY(OVATION_LCD_POSY));

	if(OVATION_LCD_GDF == GDF_32BIT_X888RGB){
	/* Set framebuffer pixel format */
	clrbits_le32(DISPC_GFX_ATTRIBUTES_REG_ADDR, DISPC_GFX_ATTRIBUTES_FORMAT_MASK);
	setbits_le32(DISPC_GFX_ATTRIBUTES_REG_ADDR, DISPC_GFX_ATTRIBUTES_FORMAT_XRGB24_8888);
	}

	/* Validate regs & start display controller */
	setbits_le32(DISPC_CONTROL1_REG_ADDR, DISPC_CONTROL1_GOLCD);
	setbits_le32(DISPC_GFX_ATTRIBUTES_REG_ADDR, DISPC_GFX_ATTRIBUTES_ENABLE);

	gdev.frameAdrs = OVATION_LCD_FB_ADDR;
	gdev.winSizeX = OVATION_LCD_SIZEX;
	gdev.winSizeY = OVATION_LCD_SIZEY;
	gdev.gdfBytesPP = OVATION_LCD_BPP;
	gdev.gdfIndex = OVATION_LCD_GDF;

	return (void *) &gdev;
}
