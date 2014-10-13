/*
 * (C) Copyright 2014
 * Ahmad Draidi <ar2000jp@gmail.com>
 *
 * (C) Copyright 2010
 * Texas Instruments Incorporated.
 * Aneesh V       <aneesh@ti.com>
 * Steve Sakoman  <steve@sakoman.com>
 *
 * Configuration settings for the Barnes & Noble Ovation (Nook HD+) Tablet.
 * See ti_omap4_common.h for OMAP4 common part
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_OVATION_H
#define __CONFIG_OVATION_H

#ifdef CONFIG_ENG_BUILD
#define CONFIG_IDENT_STRING	" EXPERIMENTAL Eng. build"
#else
#define CONFIG_IDENT_STRING	" EXPERIMENTAL"
#endif

#define CONFIG_4430SDP		1
#define CONFIG_MACH_TYPE	3610 /* MACH_TYPE_OMAP4_OVATION */
#define CONFIG_SYS_NO_FLASH

#define CONFIG_SYS_TEXT_BASE	0x88000000
#define CONFIG_SYS_LOAD_ADDR	0x82000000

#define CONFIG_SYS_SDRAM_BASE	0x80000000
#define CONFIG_NR_DRAM_BANKS	1

#define CONFIG_PRE_CONSOLE_BUFFER
#define CONFIG_PRE_CON_BUF_ADDR	0x8A000000
#define CONFIG_PRE_CON_BUF_SZ	8192

#define CONFIG_REVISION_TAG      1
#define CONFIG_SERIAL_TAG        1

#define CONFIG_VIDEO
#define CONFIG_VGA_AS_SINGLE_DEVICE
#define CONFIG_CFB_CONSOLE
#define CONFIG_CFB_CONSOLE_ANSI

#define OVATION_LCD_FB_ADDR	(0xB2200000)
#define OVATION_LCD_SIZEX	(1920)
#define OVATION_LCD_SIZEY	(1280)
#define OVATION_LCD_POSX	(0)
#define OVATION_LCD_POSY	(0)
#define OVATION_LCD_BPP		(4)
#define OVATION_LCD_GDF		(GDF_32BIT_X888RGB)

#include <configs/ti_omap4_common.h>

#define CONFIG_SYS_NS16550_COM1	UART1_BASE

#undef CONFIG_CONS_INDEX
#define CONFIG_CONS_INDEX	1

#define CONFIG_CONSOLE_MUX

#undef CONFIG_BOOTDELAY
#define CONFIG_BOOTDELAY	1

#undef CONFIG_EXTRA_ENV_SETTINGS
#define CONFIG_EXTRA_ENV_SETTINGS \
	"stdin=serial,usbtty\0" \
	"stdout=serial,usbtty\0" \
	"stderr=serial,usbtty\0" \
	"usbtty=cdc_acm\0" \
	"loadaddr=0x82000000"

#undef CONFIG_BOOTCOMMAND
#define CONFIG_BOOTCOMMAND \
	"mmc dev 0; " \
	"if mmc rescan; then " \
		"echo SD found.;" \
		"if fatload mmc 0:1 ${loadaddr} boot.scr; then " \
			"echo Running bootscript from SD.; source ${loadaddr};" \
		"else " \
			"mmc dev 1; " \
			"if mmc rescan; then " \
				"echo eMMC found.;" \
				"if fatload mmc 1:6 ${loadaddr} boot.scr; then " \
					"echo Running bootscript from eMMC.; source ${loadaddr};" \
				"fi;" \
			"fi;" \
		"fi;" \
	"fi"

#define CONFIG_ENV_IS_NOWHERE

#include <config_cmd_default.h>

#define CONFIG_CMDLINE_EDITING

#undef CONFIG_CMD_FPGA
#undef CONFIG_CMD_NET
#undef CONFIG_CMD_NFS

/*
 * Add-ons for engineering build only.
 * Use omap4_ovation_eng config for engineering build.
 */
#ifdef CONFIG_ENG_BUILD
#define CONFIG_CMD_DIAG
#define CONFIG_CMD_ELF
#define CONFIG_CMD_REGINFO
#define CONFIG_CMD_GETTIME
#define CONFIG_CMD_HASH
#define CONFIG_CMD_I2C
#define CONFIG_CMD_INI
#define CONFIG_CMD_MEMINFO
#define CONFIG_CMD_TIME
#define CONFIG_CMD_READ
#endif /* CONFIG_ENG_BUILD */

#define CONFIG_CMD_MMC
#define CONFIG_CMD_FS_GENERIC
#define CONFIG_CMD_FAT
#define CONFIG_CMD_EXT2
#define CONFIG_CMD_EXT4

#define CONFIG_DOS_PARTITION
#define CONFIG_EFI_PARTITION
#define CONFIG_SUPPORT_EMMC_BOOT
#define CONFIG_ANDROID_BOOT_IMAGE

#define CONFIG_MENU
#define CONFIG_CMD_BOOTMENU
#define CONFIG_SILENT_CONSOLE

#endif /* __CONFIG_OVATION_H */
