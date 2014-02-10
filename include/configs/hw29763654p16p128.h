/*
 * This file contains the configuration parameters for the dbau1x00 board.
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include <configs/ar7100.h>

#undef CONFIG_JFFS2_CMDLINE

/*-----------------------------------------------------------------------
 * FLASH and environment organization
 */
#define CFG_MAX_FLASH_BANKS     1       /* max number of memory banks */
#define CFG_MAX_FLASH_SECT      256    /* max number of sectors on one chip */
#define CFG_FLASH_SECTOR_SIZE   (64*1024)
#define CFG_FLASH_SIZE          0x01000000 /* Total flash size */


/********************/
/* squashfs &lzma   */
/********************/
#define CONFIG_FS		1
#define CFG_FS_SQUASHFS	1
#define CONFIG_SQUASHFS_LZMA
#define CONFIG_LZMA

#define CFG_FLASH_WORD_SIZE     unsigned short 
#define CFG_FLASH_ADDR0         (0x5555)        
#define CFG_FLASH_ADDR1         (0x2AAA)

/* 
 * We boot from this flash
 */
#define CFG_FLASH_BASE          0xbf000000
#define FIRMWARE_INTEGRITY_CHECK 1
#define FIRMWARE_RECOVER_FROM_TFTP_SERVER 1


#ifdef FIRMWARE_RECOVER_FROM_TFTP_SERVER
/*change image length to 0xe40000, it is consistent with bootargs rootfs mtd partion */
#define CFG_IMAGE_LEN   0xe40000
#define CFG_IMAGE_BASE_ADDR (CFG_FLASH_BASE + 0x70000)
#define CFG_IMAGE_ADDR_BEGIN (CFG_IMAGE_BASE_ADDR)
#define CFG_IMAGE_ADDR_END   (CFG_IMAGE_BASE_ADDR + CFG_IMAGE_LEN)
#define CFG_FLASH_CONFIG_BASE               (CFG_IMAGE_ADDR_END)
#define CFG_FLASH_CONFIG_PARTITION_SIZE     0x10000
#define CFG_STRING_TABLE_LEN 0x19000 /* Each string table takes 100K to save */
#define CFG_STRING_TABLE_NUMBER 10
#define CFG_STRING_TABLE_TOTAL_LEN 0x100000 /* Totally allocate 1024K to save all string tables */
#define CFG_STRING_TABLE_BASE_ADDR (CFG_FLASH_BASE + 0xef0000)
#define CFG_STRING_TABLE_ADDR_BEGIN (CFG_STRING_TABLE_BASE_ADDR)
#define CFG_STRING_TABLE_ADDR_END   (CFG_STRING_TABLE_ADDR_BEGIN + CFG_STRING_TABLE_TOTAL_LEN)
#endif

#define POWER_LED (1<<2)
#define TEST_LED (1<<1)
#define RESET_BUTTON_GPIO (1<<8)

#define CFG_NMRP                1
#define CFG_SINGLE_FIRMWARE 1

#define TFTP_RECOVER_MODE_PINGABLE 1

#undef CONFIG_ROOTFS_RD
#undef CONFIG_ROOTFS_FLASH
#undef CONFIG_BOOTARGS_FL
#undef CONFIG_BOOTARGS_RD
#undef CONFIG_BOOTARGS
#undef  MTDPARTS_DEFAULT
#undef  MTDIDS_DEFAULT

#define CONFIG_ROOTFS_FLASH
#define CONFIG_BOOTARGS CONFIG_BOOTARGS_FL

//#define CONFIG_BOOTARGS_RD     "console=ttyS0,115200 root=01:00 rd_start=0x80600000 rd_size=5242880 init=/sbin/init mtdparts=ar9100-nor0:256k(u-boot),64k(u-boot-env),4096k(rootfs),2048k(uImage)"

/* XXX - putting rootfs in last partition results in jffs errors */

#define CONFIG_BOOTARGS_FL     "console=ttyS0,115200 root=31:02 rootfstype=jffs2 init=/sbin/init mtdparts=ar7100-nor0:256k(uboot),128k(env),6144k(rootfs),64k(caldata),1024k(uImage)"

#define MTDPARTS_DEFAULT    "mtdparts=ar7100-nor0:256k(u-boot),128k(env),6144k(rootfs),64k(caldata),1024k(uImage)"
#define MTDIDS_DEFAULT      "nor0=ar7100-nor0"

/* 
 * The following #defines are needed to get flash environment right 
 */
#define CFG_MONITOR_BASE    TEXT_BASE
#define CFG_MONITOR_LEN     (192 << 10)

#undef CFG_HZ
/*
 * MIPS32 24K Processor Core Family Software User's Manual
 *
 * 6.2.9 Count Register (CP0 Register 9, Select 0)
 * The Count register acts as a timer, incrementing at a constant
 * rate, whether or not an instruction is executed, retired, or
 * any forward progress is made through the pipeline.  The counter
 * increments every other clock, if the DC bit in the Cause register
 * is 0.
 */

#define CFG_HZ	(680000000/2)

/* 
 * timeout values are in ticks 
 */
#define CFG_FLASH_ERASE_TOUT    (2 * CFG_HZ) /* Timeout for Flash Erase */
#define CFG_FLASH_WRITE_TOUT    (2 * CFG_HZ) /* Timeout for Flash Write */

/*
 * Cache lock for stack
 */
#define CFG_INIT_SP_OFFSET  0x1000

#define CFG_ENV_IS_IN_FLASH    1
#undef CFG_ENV_IS_NOWHERE  

/* Address and size of Primary Environment Sector   */
#define CFG_ENV_ADDR        0xbf050000
#define CFG_ENV_SIZE        0x10000

#define CONFIG_BOOTCOMMAND "fsload 80800000 image/uImage;bootm 80800000"

/*
** Extra environmental variables useful for loading the board
*/

#define CONFIG_EXTRA_ENV_SETTINGS \
"clearenv=erase 0xbf050000 +0x10000\0"

#define CONFIG_NR_DRAM_BANKS    		2

/*
** Parameters defining the location of the calibration/initialization
** information for the two Merlin devices.
** NOTE: **This will change with different flash configurations**
*/

#define MERLIN24CAL			0xbfff1000
#define MERLIN50CAL			0xbfff5000
#define BOARDCAL			0xbfff0000
#define ART_SIZE			0x10000
#define ATHEROS_PRODUCT_ID	136
#define CAL_SECTOR                     (CFG_MAX_FLASH_SECT - 1)
#define LAN_MAC_OFFSET		0x00
#define WAN_MAC_OFFSET		0x06
#define WLAN_MAC_OFFSET		0x0c

#define WPSPIN_OFFSET           0x12
#define WPSPIN_LENGTH           8

/*
** Configure the CPU clock settings
*/

#define CFG_PLL_FREQ	CFG_PLL_680_340_170
/*
** These values for DDR configuration came from the
** BDM configuration script
*/
#define CFG_DDR_32BIT	1

#define CFG_DDR_REFRESH_VAL     		0x461b

#ifdef CFG_DDR_32BIT
#define CFG_DDR_CONFIG_VAL      		0x77b8884e
#define CFG_DDR_CONFIG2_VAL             0x812cd6a8
#else
#define CFG_DDR_CONFIG_VAL      		0xefbc8cd0
#define CFG_DDR_CONFIG2_VAL             0x8e7156a2
#endif

#define CFG_DDR_MODE_VAL_INIT   		0x131
#define CFG_DDR_EXT_MODE_VAL    		0x0

#ifdef CFG_DDR_32BIT
#define CFG_DDR_MODE_VAL        		0x33
#else
#define CFG_DDR_MODE_VAL        		0x61
#endif

#define CFG_DDR_TRTW_VAL        		0x1f
#define CFG_DDR_TWTR_VAL        		0x1e

#ifdef CFG_DDR_32BIT
#define CFG_DDR_RD_DATA_THIS_CYCLE_VAL  0xff
#else
#define CFG_DDR_RD_DATA_THIS_CYCLE_VAL  0xffff
#endif

#define CONFIG_NET_MULTI
#define CONFIG_MEMSIZE_IN_BYTES
#define CONFIG_PCI


/*-----------------------------------------------------------------------
 * Cache Configuration
 */
#define CONFIG_COMMANDS (( CONFIG_CMD_DFL        | CFG_CMD_MII   | CFG_CMD_PING  \
   | CFG_CMD_NET | CFG_CMD_PCI     | CFG_CMD_ENV | CFG_CMD_FLASH | CFG_CMD_LOADS \
   | CFG_CMD_RUN | CFG_CMD_LOADB   | CFG_CMD_ELF | CFG_CMD_BSP | CFG_CMD_JFFS2  ))

/*
** Ethernet Configuration
** Set default values, and select the PHY to use
*/

#define CONFIG_IPADDR       		192.168.1.2
#define CONFIG_SERVERIP     		192.168.1.1
//#define CONFIG_ETHADDR      		00:03:7f:ff:ff:fe
#define CFG_FAULT_ECHO_LINK_DOWN    1
#define CONFIG_PHY_GIGE       		0              /* GbE speed/duplex detect */

//#define CFG_ATHRS26_PHY  			1
#define CFG_RTL8366S_PHY			1
#define CFG_AG7100_NMACS 			2
//#define CFG_ATHRHDR_REG 			1
//#define CFG_SWITCH_FREQ				1

//#define CFG_ATHRHDR_EN 				1
//#define ATHRHDR_LEN   				2
//#define ATHRHDR_MAX_DATA  			10

#define CFG_PHY_ADDR				0  /* Port 4 */
#define CFG_GMII     				1
//#define CFG_MII0_RMII				1
#define CFG_MII0_RGMII				1
#define CFG_MII1_RMII				1

/*
** Configure Parser
*/

#define CFG_BOOTM_LEN   (16 << 20) /* 16 MB */
#define DEBUG
#define CFG_HUSH_PARSER
#define CFG_PROMPT_HUSH_PS2 "hush>"

#define CONFIG_JFFS2_PART_OFFSET	0x70040

#include <cmd_confdefs.h>

/*12(lan/wan) + 6 (wlan5g) + 8(wpspin)=26 0x1a */
#define SERIAL_NUMBER_OFFSET        0x1a
#define SERIAL_NUMBER_LENGTH        13

/* WNDR3700 has a MAC address for 5Ghz. */
/* The offset of region number will be 0x27. */
#define REGION_NUMBER_OFFSET        0x27
#define REGION_NUMBER_LENGTH        2

/*
 * hardware's PCB number is 2976365401, 16M Flash, 128M Ram
 * It's HW_ID would be "29763654+16+128".
 * "(8 MSB of PCB number)+(Flash size)+(SDRam size)", length should be 14
 */
#define BOARD_HW_ID_OFFSET          (REGION_NUMBER_OFFSET + REGION_NUMBER_LENGTH)
#define BOARD_HW_ID_LENGTH          15

/*
 * Three different model use WNDR3700v2 hardware, WNDR3700v2, WNDR3800 & WNDRMAC.
 */
#define BOARD_MODEL_ID_OFFSET       (BOARD_HW_ID_OFFSET + BOARD_HW_ID_LENGTH)
#define BOARD_MODEL_ID_LENGTH       10

#define BOARD_SSID_OFFSET           (BOARD_MODEL_ID_OFFSET + BOARD_MODEL_ID_LENGTH)
#define BOARD_SSID_LENGTH           32

#define BOARD_PASSPHRASE_OFFSET     (BOARD_SSID_OFFSET + BOARD_SSID_LENGTH)
#define BOARD_PASSPHRASE_LENGTH     64

#define NETGEAR_BOARD_ID_SUPPORT    1

#undef CONFIG_BOOTDELAY
#define CONFIG_BOOTDELAY	1	/* autoboot after 1 seconds	*/
#endif  /* __CONFIG_H */
