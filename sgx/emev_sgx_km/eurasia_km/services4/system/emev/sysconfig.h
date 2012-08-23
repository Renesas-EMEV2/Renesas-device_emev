/**********************************************************************
 *
 * Copyright(c) 2008 Imagination Technologies Ltd. All rights reserved.
 * 
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope it will be useful but, except 
 * as otherwise stated in writing, without any warranty; without even the 
 * implied warranty of merchantability or fitness for a particular purpose. 
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 * 
 * The full GNU General Public License is included in this distribution in
 * the file called "COPYING".
 *
 * Contact Information:
 * Imagination Technologies Ltd. <gpl-support@imgtec.com>
 * Home Park Estate, Kings Langley, Herts, WD4 8LZ, UK 
 *
 ******************************************************************************/

#if !defined(__SOCCONFIG_H__)
#define __SOCCONFIG_H__

#include "syscommon.h"

#define VS_PRODUCT_NAME	"EMEV"

#define SYS_SGX_CLOCK_SPEED 177000000

#define SYS_SGX_HWRECOVERY_TIMEOUT_FREQ		(100)	
#define SYS_SGX_PDS_TIMER_FREQ				(1000)	

#if !defined(SYS_SGX_ACTIVE_POWER_LATENCY_MS)
#define SYS_SGX_ACTIVE_POWER_LATENCY_MS		(1)
#endif

#define SYS_EMEV_SGX_REGS_SYS_PHYS_BASE 0xE8000000
#define SYS_EMEV_SGX_REGS_SIZE (0x4000)

#define SYS_EMEV_SGX_IRQ 62

#define EMXX_SMU_CLK_DIV_A3D		0x00000202
#define EMXX_SMU_CLK_DIV_HW_INI		0x00000000

#define EMXX_SMU_PG_SWON_PD_ON		0x00000101
#define EMXX_SMU_PG_SWON_PD_OFF		0x00000100

#define EMXX_SMU_PG_SWON_RFF_ON		0x00000001
#define EMXX_SMU_PG_SWON_RFF_OFF	0x00000000

#define EMXX_SMU_PG_SEQ_BUSY		0x00000100

#define EMXX_SMU_PD					0
#define EMXX_SMU_RFF				1
 
#endif	
