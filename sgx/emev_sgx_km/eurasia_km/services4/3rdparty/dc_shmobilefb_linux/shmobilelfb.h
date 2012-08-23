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

#ifndef __SHLFB_H__
#define __SHLFB_H__

#include <linux/version.h>

#include <asm/atomic.h>

#include <linux/kernel.h>
#include <linux/console.h>
#include <linux/fb.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/notifier.h>
#include <linux/mutex.h>

#ifdef CONFIG_HAS_EARLYSUSPEND
#include <linux/earlysuspend.h>
#endif

#define unref__ __attribute__ ((unused))

typedef void *       SHLFB_HANDLE;

typedef bool SHLFB_BOOL, *SHLFB_PBOOL;
#define	SHLFB_FALSE false
#define SHLFB_TRUE true

typedef	atomic_t	SHLFB_ATOMIC_BOOL;

typedef atomic_t	SHLFB_ATOMIC_INT;

typedef struct SHLFB_BUFFER_TAG
{
	struct SHLFB_BUFFER_TAG	*psNext;
	struct SHLFB_DEVINFO_TAG	*psDevInfo;

	struct work_struct sWork;

	
	unsigned long		     	ulYOffset;

	
	
	IMG_SYS_PHYADDR              	sSysAddr;
	IMG_CPU_VIRTADDR             	sCPUVAddr;
	PVRSRV_SYNC_DATA            	*psSyncData;

	SHLFB_HANDLE      		hCmdComplete;
	unsigned long    		ulSwapInterval;
} SHLFB_BUFFER;

typedef struct SHLFB_SWAPCHAIN_TAG
{
	
	unsigned int			uiSwapChainID;

	
	unsigned long       		ulBufferCount;

	
	SHLFB_BUFFER     		*psBuffer;

	
	struct workqueue_struct   	*psWorkQueue;

	
	SHLFB_BOOL			bNotVSynced;

	
	int				iBlankEvents;

	
	unsigned int            	uiFBDevID;
} SHLFB_SWAPCHAIN;

typedef struct SHLFB_FBINFO_TAG
{
	unsigned long       ulFBSize;
	unsigned long       ulBufferSize;
	unsigned long       ulRoundedBufferSize;
	unsigned long       ulWidth;
	unsigned long       ulHeight;
	unsigned long       ulByteStride;
	unsigned long       ulPhysicalWidthmm;
	unsigned long       ulPhysicalHeightmm;

	
	
	IMG_SYS_PHYADDR     sSysAddr;
	IMG_CPU_VIRTADDR    sCPUVAddr;

	
	PVRSRV_PIXEL_FORMAT ePixelFormat;
}SHLFB_FBINFO;

typedef struct SHLFB_DEVINFO_TAG
{
	
	unsigned int            uiFBDevID;

	
	unsigned int            uiPVRDevID;

	
	struct mutex		sCreateSwapChainMutex;

	
	SHLFB_BUFFER          sSystemBuffer;

	
	PVRSRV_DC_DISP2SRV_KMJTABLE	sPVRJTable;
	
	
	PVRSRV_DC_SRV2DISP_KMJTABLE	sDCJTable;

	
	SHLFB_FBINFO          sFBInfo;

	
	SHLFB_SWAPCHAIN      *psSwapChain;

	
	unsigned int		uiSwapChainID;

	
	SHLFB_ATOMIC_BOOL     sFlushCommands;

	
	struct fb_info         *psLINFBInfo;

	
	struct notifier_block   sLINNotifBlock;

	
	

	
	IMG_DEV_VIRTADDR	sDisplayDevVAddr;

	DISPLAY_INFO            sDisplayInfo;

	
	DISPLAY_FORMAT          sDisplayFormat;
	
	
	DISPLAY_DIMS            sDisplayDim;

	
	SHLFB_ATOMIC_BOOL	sBlanked;

	
	SHLFB_ATOMIC_INT	sBlankEvents;

#ifdef CONFIG_HAS_EARLYSUSPEND
	
	SHLFB_ATOMIC_BOOL	sEarlySuspendFlag;

	struct early_suspend    sEarlySuspend;
#endif

#if defined(SUPPORT_DRI_DRM)
	SHLFB_ATOMIC_BOOL     sLeaveVT;
#endif

}  SHLFB_DEVINFO;

#define	SHLFB_PAGE_SIZE 4096

#ifdef	DEBUG
#define	DEBUG_PRINTK(x) printk x
#else
#define	DEBUG_PRINTK(x)
#endif

#define DISPLAY_DEVICE_NAME "PowerVR SH-Mobile Linux Display Driver"
#define	DRVNAME	"shmobilelfb"
#define	DEVNAME	DRVNAME
#define	DRIVER_PREFIX DRVNAME

typedef enum _SHLFB_ERROR_
{
	SHLFB_OK                             =  0,
	SHLFB_ERROR_GENERIC                  =  1,
	SHLFB_ERROR_OUT_OF_MEMORY            =  2,
	SHLFB_ERROR_TOO_FEW_BUFFERS          =  3,
	SHLFB_ERROR_INVALID_PARAMS           =  4,
	SHLFB_ERROR_INIT_FAILURE             =  5,
	SHLFB_ERROR_CANT_REGISTER_CALLBACK   =  6,
	SHLFB_ERROR_INVALID_DEVICE           =  7,
	SHLFB_ERROR_DEVICE_REGISTER_FAILED   =  8,
	SHLFB_ERROR_SET_UPDATE_MODE_FAILED   =  9
} SHLFB_ERROR;

typedef enum _SHLFB_UPDATE_MODE_
{
	SHLFB_UPDATE_MODE_UNDEFINED			= 0,
	SHLFB_UPDATE_MODE_MANUAL			= 1,
	SHLFB_UPDATE_MODE_AUTO			= 2,
	SHLFB_UPDATE_MODE_DISABLED			= 3
} SHLFB_UPDATE_MODE;

#ifndef UNREFERENCED_PARAMETER
#define	UNREFERENCED_PARAMETER(param) (param) = (param)
#endif

SHLFB_ERROR SHLFBInit(void);
SHLFB_ERROR SHLFBDeInit(void);

SHLFB_DEVINFO *SHLFBGetDevInfoPtr(unsigned uiFBDevID);
unsigned SHLFBMaxFBDevIDPlusOne(void);
void *SHLFBAllocKernelMem(unsigned long ulSize);
void SHLFBFreeKernelMem(void *pvMem);
SHLFB_ERROR SHLFBGetLibFuncAddr(char *szFunctionName, PFN_DC_GET_PVRJTABLE *ppfnFuncTable);
SHLFB_ERROR SHLFBCreateSwapQueue (SHLFB_SWAPCHAIN *psSwapChain);
void SHLFBDestroySwapQueue(SHLFB_SWAPCHAIN *psSwapChain);
void SHLFBInitBufferForSwap(SHLFB_BUFFER *psBuffer);
void SHLFBSwapHandler(SHLFB_BUFFER *psBuffer);
void SHLFBQueueBufferForSwap(SHLFB_SWAPCHAIN *psSwapChain, SHLFB_BUFFER *psBuffer);
void SHLFBFlip(SHLFB_DEVINFO *psDevInfo, SHLFB_BUFFER *psBuffer);
SHLFB_UPDATE_MODE SHLFBGetUpdateMode(SHLFB_DEVINFO *psDevInfo);
SHLFB_BOOL SHLFBSetUpdateMode(SHLFB_DEVINFO *psDevInfo, SHLFB_UPDATE_MODE eMode);
SHLFB_BOOL SHLFBWaitForVSync(SHLFB_DEVINFO *psDevInfo);
SHLFB_BOOL SHLFBManualSync(SHLFB_DEVINFO *psDevInfo);
SHLFB_BOOL SHLFBCheckModeAndSync(SHLFB_DEVINFO *psDevInfo);
SHLFB_ERROR SHLFBUnblankDisplay(SHLFB_DEVINFO *psDevInfo);
SHLFB_ERROR SHLFBEnableLFBEventNotification(SHLFB_DEVINFO *psDevInfo);
SHLFB_ERROR SHLFBDisableLFBEventNotification(SHLFB_DEVINFO *psDevInfo);
void SHLFBCreateSwapChainLockInit(SHLFB_DEVINFO *psDevInfo);
void SHLFBCreateSwapChainLockDeInit(SHLFB_DEVINFO *psDevInfo);
void SHLFBCreateSwapChainLock(SHLFB_DEVINFO *psDevInfo);
void SHLFBCreateSwapChainUnLock(SHLFB_DEVINFO *psDevInfo);
void SHLFBAtomicBoolInit(SHLFB_ATOMIC_BOOL *psAtomic, SHLFB_BOOL bVal);
void SHLFBAtomicBoolDeInit(SHLFB_ATOMIC_BOOL *psAtomic);
void SHLFBAtomicBoolSet(SHLFB_ATOMIC_BOOL *psAtomic, SHLFB_BOOL bVal);
SHLFB_BOOL SHLFBAtomicBoolRead(SHLFB_ATOMIC_BOOL *psAtomic);
void SHLFBAtomicIntInit(SHLFB_ATOMIC_INT *psAtomic, int iVal);
void SHLFBAtomicIntDeInit(SHLFB_ATOMIC_INT *psAtomic);
void SHLFBAtomicIntSet(SHLFB_ATOMIC_INT *psAtomic, int iVal);
int SHLFBAtomicIntRead(SHLFB_ATOMIC_INT *psAtomic);
void SHLFBAtomicIntInc(SHLFB_ATOMIC_INT *psAtomic);

#endif 

