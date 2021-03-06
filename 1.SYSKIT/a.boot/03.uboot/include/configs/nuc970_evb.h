/*
 * (C) Copyright 2014
 * Nuvoton Technology Corp. <www.nuvoton.com>
 *
 * Configuation settings for the NUC970 EV Board.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __CONFIG_H
#define __CONFIG_H


#define CONFIG_SYS_LOAD_ADDR            0x8000
#define CONFIG_EXT_CLK	                12000000        /* 12 MHz crystal */
#define CONFIG_TMR_DIV                  120             /* timer prescaler */  
#define CONFIG_SYS_HZ			1000
#define CONFIG_SYS_MEMTEST_START         0xA00000
#define CONFIG_SYS_MEMTEST_END           0xB00000

#define CONFIG_ARCH_CPU_INIT
#undef  CONFIG_USE_IRQ               

#define CONFIG_CMDLINE_TAG	1	/* enable passing of ATAGs	*/
#define CONFIG_SETUP_MEMORY_TAGS 1
#define CONFIG_INITRD_TAG	1

#define CONFIG_CMD_TIMER

//#define CONFIG_NUC970_HW_CHECKSUM

#define CONFIG_SYS_USE_SPIFLASH
#define CONFIG_SYS_USE_NANDFLASH
#define CONFIG_SYS_NO_FLASH    // that is, no *NOR* flash 
#define CONFIG_ENV_IS_IN_NAND 
//#define CONFIG_ENV_IS_IN_SPI_FLASH 
//#define CONFIG_ENV_IS_IN_MMC


#define CONFIG_BOARD_EARLY_INIT_F
#define CONFIG_BOARD_LATE_INIT

#define CONFIG_NUC970_WATCHDOG
#define CONFIG_HW_WATCHDOG

#define CONFIG_DISPLAY_CPUINFO

#define CONFIG_BOOTDELAY	3

#define CONFIG_SYS_SDRAM_BASE   0
#define CONFIG_NR_DRAM_BANKS    2     // there are 2 sdram banks for nuc970
#define CONFIG_SYS_INIT_SP_ADDR 0xBC008000

#define CONFIG_BAUDRATE         115200
#define CONFIG_SYS_BAUDRATE_TABLE       {115200, 57600, 38400}

#define CONFIG_NUC970_EMAC0
//#define CONFIG_NUC970_EMAC1
#define CONFIG_CMD_NET		
#define CONFIG_NUC970_ETH
#define CONFIG_NUC970_PHY_ADDR          1
#define CONFIG_ETHADDR                  00:00:00:11:66:88
#define CONFIG_SYS_RX_ETH_BUFFER        16 // default is 4, set to 16 here.
#define CONFIG_NUC970_CONSOLE

//#undef CONFIG_SYS_ICACHE_OFF
//#undef CONFIG_SYS_DCACHE_OFF
//#define CONFIG_SYS_ICACHE_OFF
#define CONFIG_SYS_DCACHE_OFF

/*
 * BOOTP options
 */
#define CONFIG_BOOTP_BOOTFILESIZE	1
#define CONFIG_BOOTP_BOOTPATH		1
#define CONFIG_BOOTP_GATEWAY		1
#define CONFIG_BOOTP_HOSTNAME		1
#define CONFIG_BOOTP_SERVERIP /* tftp serverip not overruled by dhcp server */

/*
 * Command line configuration.
 */
#include <config_cmd_default.h>

#undef CONFIG_CMD_LOADS
#undef CONFIG_CMD_SOURCE

#define CONFIG_CMD_PING		1
#define CONFIG_CMD_DHCP		1
#define CONFIG_CMD_JFFS2        1


#ifdef CONFIG_SYS_USE_SPIFLASH
#undef CONFIG_CMD_IMLS  //====================> SPI only
#undef CONFIG_CMD_JFFS2
#endif

#ifdef CONFIG_SYS_USE_NANDFLASH
#define CONFIG_NAND_NUC970
#define CONFIG_CMD_NAND		1
#define CONFIG_CMD_UBI         1 
#define CONFIG_CMD_UBIFS       1 
#define CONFIG_CMD_MTDPARTS    1 
#define CONFIG_MTD_DEVICE      1 
#define CONFIG_MTD_PARTITIONS  1 
#define CONFIG_RBTREE          1 
#define CONFIG_LZO             1 

#define MTDIDS_DEFAULT "nand0=nand0"
#define MTDPARTS_DEFAULT "mtdparts=nand0:0x200000@0x0(u-boot),0x1400000@0x200000(kernel),-(user)"
#define MTD_ACTIVE_PART "nand0,2"

//#define CONFIG_CMD_NAND_YAFFS2 1
//#define CONFIG_YAFFS2          1
#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_SYS_NAND_BASE	0xB000D000
#define CONFIG_SYS_NAND_ECCBYTES        12
#ifdef CONFIG_ENV_IS_IN_NAND
#define CONFIG_ENV_OFFSET       0x80000
#define CONFIG_ENV_SIZE         0x10000
#define CONFIG_ENV_SECT_SIZE    0x20000
#define CONFIG_ENV_RANGE	        (4 * CONFIG_ENV_SECT_SIZE)  /* Env range : 0x80000 ~ 0x100000 */
#define CONFIG_ENV_OVERWRITE
#endif
#endif

#define CONFIG_SYS_NAND_U_BOOT_OFFS     0x100000   /* Offset to RAM U-Boot image */
/* total memory available to uboot */
#define CONFIG_SYS_UBOOT_SIZE           (1024 * 1024)

#ifdef CONFIG_NAND_SPL
/* base address for uboot */
#define CONFIG_SYS_PHY_UBOOT_BASE       (CONFIG_SYS_SDRAM_BASE + 0xE00000)

#define CONFIG_SYS_NAND_U_BOOT_DST      CONFIG_SYS_PHY_UBOOT_BASE       /* NUB load-addr      */
#define CONFIG_SYS_NAND_U_BOOT_START    CONFIG_SYS_NAND_U_BOOT_DST      /* NUB start-addr     */

#define CONFIG_SYS_NAND_U_BOOT_SIZE     (500 * 1024)    /* Size of RAM U-Boot image   */


/* NAND chip page size          */
#define CONFIG_SYS_NAND_PAGE_SIZE       2048
/* NAND chip block size         */
#define CONFIG_SYS_NAND_BLOCK_SIZE      (128 * 1024)
/* NAND chip page per block count  */
#define CONFIG_SYS_NAND_PAGE_COUNT      64
/* Location of the bad-block label */
#define CONFIG_SYS_NAND_BAD_BLOCK_POS   0
/* Size of the block protected by one OOB (Spare Area in Samsung terminology) */
#define CONFIG_SYS_NAND_ECCSIZE CONFIG_SYS_NAND_PAGE_SIZE
/* Number of ECC-blocks per NAND page */
#define CONFIG_SYS_NAND_ECCSTEPS        (CONFIG_SYS_NAND_PAGE_SIZE / CONFIG_SYS_NAND_ECCSIZE)
/* Size of a single OOB region */
#define CONFIG_SYS_NAND_OOBSIZE 64
/* Number of ECC bytes per page */
#define CONFIG_SYS_NAND_ECCTOTAL        (CONFIG_SYS_NAND_ECCBYTES * CONFIG_SYS_NAND_ECCSTEPS)
/* ECC byte positions */
#define CONFIG_SYS_NAND_ECCPOS          {40, 41, 42, 43, 44, 45, 46, 47, \
                                 48, 49, 50, 51, 52, 53, 54, 55, \
                                 56, 57, 58, 59, 60, 61, 62, 63}
#endif //CONFIG_NAND_SPL


/* SPI flash */
#ifdef CONFIG_SYS_USE_SPIFLASH
#define CONFIG_NUC970_SPI       1
#define CONFIG_CMD_SPI          1
#define CONFIG_CMD_SF           1
#define CONFIG_SPI              1
#define CONFIG_SPI_FLASH        1
#define CONFIG_SPI_FLASH_MACRONIX   1
#define CONFIG_SPI_FLASH_WINBOND   1
#define CONFIG_SPI_FLASH_EON 1
#ifdef CONFIG_ENV_IS_IN_SPI_FLASH
#define CONFIG_ENV_OFFSET       0x80000
#define CONFIG_ENV_SIZE         0x10000
#define CONFIG_ENV_SECT_SIZE    0x10000
#define CONFIG_ENV_OVERWRITE
#endif 
#endif


#define CONFIG_SYS_PROMPT		"U-Boot> "
#define CONFIG_SYS_CBSIZE		256
#define CONFIG_SYS_MAXARGS		16
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_LONGHELP		1
#define CONFIG_CMDLINE_EDITING		1
#define CONFIG_AUTO_COMPLETE
#define CONFIG_SYS_HUSH_PARSER
#define CONFIG_SYS_PROMPT_HUSH_PS2	"> "

/* Following block is for LCD support */
#if 0
#define CONFIG_LCD
#define CONFIG_NUC970_LCD
//#define CONFIG_NUC977_LCD
#define LCD_BPP                         LCD_COLOR16
#define CONFIG_LCD_LOGO
#define CONFIG_LCD_INFO
#define CONFIG_LCD_INFO_BELOW_LOGO
#define CONFIG_SYS_CONSOLE_IS_IN_ENV
#define CONFIG_SYS_CONSOLE_OVERWRITE_ROUTINE
#endif

/* Following block is for MMC support */
#if 1
#define CONFIG_NUC970_MMC
#define CONFIG_CMD_MMC
#define CONFIG_CMD_FAT
#define CONFIG_MMC
#define CONFIG_GENERIC_MMC
#define CONFIG_DOS_PARTITION
//#define CONFIG_MMC_TRACE
#define CONFIG_NUC970_SD_PORT0
//#define CONFIG_NUC970_SD_PORT1
//#define CONFIG_NUC970_EMMC    /* Don't enable eMMC(CONFIG_NUC970_EMMC) and NAND(CONFIG_NAND_NUC970) at the same time! */
#ifdef CONFIG_ENV_IS_IN_MMC
#define CONFIG_SYS_MMC_ENV_DEV  2
#define CONFIG_ENV_OFFSET       0x80000
#define CONFIG_ENV_SIZE         512
#define CONFIG_ENV_SECT_SIZE    512
#define CONFIG_ENV_OVERWRITE
#endif
#endif

/* Following block is for EHCI support*/
#if 1
#define CONFIG_CMD_USB
#define CONFIG_CMD_FAT
#define CONFIG_USB_STORAGE
#define CONFIG_USB_EHCI
#define CONFIG_USB_EHCI_NUC970
#define CONFIG_EHCI_HCD_INIT_AFTER_RESET
#define CONFIG_DOS_PARTITION
#endif

#define CONFIG_NUC970_GPIO

/*
 * Size of malloc() pool
 */
#define CONFIG_SYS_MALLOC_LEN	(1024*1024) //ROUND(3 * CONFIG_ENV_SIZE + 128*1024, 0x1000)

#define CONFIG_STACKSIZE	(32*1024)	/* regular stack */

#endif
