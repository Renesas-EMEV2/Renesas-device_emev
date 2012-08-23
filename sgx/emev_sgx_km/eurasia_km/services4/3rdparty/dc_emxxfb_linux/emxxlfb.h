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

#ifndef __EMXXLFB_H__
#define __EMXXLFB_H__

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

typedef void *       EMXXLFB_HANDLE;

typedef bool EMXXLFB_BOOL, *EMXXLFB_PBOOL;
#define	EMXXLFB_FALSE false
#define EMXXLFB_TRUE true

typedef	atomic_t	EMXXLFB_ATOMIC_BOOL;

typedef atomic_t	EMXXLFB_ATOMIC_INT;

typedef struct EMXXLFB_BUFFER_TAG
{
	struct EMXXLFB_BUFFER_TAG	*psNext;
	struct EMXXLFB_DEVINFO_TAG	*psDevInfo;

	struct work_struct sWork;

	
	unsigned long		     	ulYOffset;

	
	
	IMG_SYS_PHYADDR              	sSysAddr;
	IMG_CPU_VIRTADDR             	sCPUVAddr;
	PVRSRV_SYNC_DATA            	*psSyncData;

	EMXXLFB_HANDLE      		hCmdComplete;
	unsigned long    		ulSwapInterval;
} EMXXLFB_BUFFER;

typedef struct EMXXLFB_SWAPCHAIN_TAG
{
	
	unsigned int			uiSwapChainID;

	
	unsigned long       		ulBufferCount;

	
	EMXXLFB_BUFFER     		*psBuffer;

	
	struct workqueue_struct   	*psWorkQueue;

	
	EMXXLFB_BOOL			bNotVSynced;

	
	int				iBlankEvents;

	
	unsigned int            	uiFBDevID;
} EMXXLFB_SWAPCHAIN;

typedef struct EMXXLFB_FBINFO_TAG
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
}EMXXLFB_FBINFO;

typedef struct EMXXLFB_DEVINFO_TAG
{
	
	unsigned int            uiFBDevID;

	
	unsigned int            uiPVRDevID;

	
	struct mutex		sCreateSwapChainMutex;

	
	EMXXLFB_BUFFER          sSystemBuffer;

	
	PVRSRV_DC_DISP2SRV_KMJTABLE	sPVRJTable;
	
	
	PVRSRV_DC_SRV2DISP_KMJTABLE	sDCJTable;

	
	EMXXLFB_FBINFO          sFBInfo;

	
	EMXXLFB_SWAPCHAIN      *psSwapChain;

	
	unsigned int		uiSwapChainID;

	
	EMXXLFB_ATOMIC_BOOL     sFlushCommands;

	
	struct fb_info         *psLINFBInfo;

	
	struct notifier_block   sLINNotifBlock;

	
	

	
	IMG_DEV_VIRTADDR	sDisplayDevVAddr;

	DISPLAY_INFO            sDisplayInfo;

	
	DISPLAY_FORMAT          sDisplayFormat;
	
	
	DISPLAY_DIMS            sDisplayDim;

	
	EMXXLFB_ATOMIC_BOOL	sBlanked;

	
	EMXXLFB_ATOMIC_INT	sBlankEvents;

#ifdef CONFIG_HAS_EARLYSUSPEND
	
	EMXXLFB_ATOMIC_BOOL	sEarlySuspendFlag;

	struct early_suspend    sEarlySuspend;
#endif

#if defined(SUPPORT_DRI_DRM)
	EMXXLFB_ATOMIC_BOOL     sLeaveVT;
#endif

}  EMXXLFB_DEVINFO;

#define	EMXXLFB_PAGE_SIZE 4096

#ifdef	DEBUG
#define	DEBUG_PRINTK(x) printk x
#else
#define	DEBUG_PRINTK(x)
#endif

#define DISPLAY_DEVICE_NAME "PowerVR EMMA-Mobile Linux Display Driver"
#define	DRVNAME	"emxxlfb"
#define	DEVNAME	DRVNAME
#define	DRIVER_PREFIX DRVNAME

typedef enum _EMXXLFB_ERROR_
{
	EMXXLFB_OK                             =  0,
	EMXXLFB_ERROR_GENERIC                  =  1,
	EMXXLFB_ERROR_OUT_OF_MEMORY            =  2,
	EMXXLFB_ERROR_TOO_FEW_BUFFERS          =  3,
	EMXXLFB_ERROR_INVALID_PARAMS           =  4,
	EMXXLFB_ERROR_INIT_FAILURE             =  5,
	EMXXLFB_ERROR_CANT_REGISTER_CALLBACK   =  6,
	EMXXLFB_ERROR_INVALID_DEVICE           =  7,
	EMXXLFB_ERROR_DEVICE_REGISTER_FAILED   =  8,
	EMXXLFB_ERROR_SET_UPDATE_MODE_FAILED   =  9
} EMXXLFB_ERROR;

typedef enum _EMXXLFB_UPDATE_MODE_
{
	EMXXLFB_UPDATE_MODE_UNDEFINED			= 0,
	EMXXLFB_UPDATE_MODE_MANUAL			= 1,
	EMXXLFB_UPDATE_MODE_AUTO			= 2,
	EMXXLFB_UPDATE_MODE_DISABLED			= 3
} EMXXLFB_UPDATE_MODE;

#ifndef UNREFERENCED_PARAMETER
#define	UNREFERENCED_PARAMETER(param) (param) = (param)
#endif

EMXXLFB_ERROR EMXXLFBInit(void);
EMXXLFB_ERROR EMXXLFBDeInit(void);

EMXXLFB_DEVINFO *EMXXLFBGetDevInfoPtr(unsigned uiFBDevID);
unsigned EMXXLFBMaxFBDevIDPlusOne(void);
void *EMXXLFBAllocKernelMem(unsigned long ulSize);
void EMXXLFBFreeKernelMem(void *pvMem);
EMXXLFB_ERROR EMXXLFBGetLibFuncAddr(char *szFunctionName, PFN_DC_GET_PVRJTABLE *ppfnFuncTable);
EMXXLFB_ERROR EMXXLFBCreateSwapQueue (EMXXLFB_SWAPCHAIN *psSwapChain);
void EMXXLFBDestroySwapQueue(EMXXLFB_SWAPCHAIN *psSwapChain);
void EMXXLFBInitBufferForSwap(EMXXLFB_BUFFER *psBuffer);
void EMXXLFBSwapHandler(EMXXLFB_BUFFER *psBuffer);
void EMXXLFBQueueBufferForSwap(EMXXLFB_SWAPCHAIN *psSwapChain, EMXXLFB_BUFFER *psBuffer);
void EMXXLFBFlip(EMXXLFB_DEVINFO *psDevInfo, EMXXLFB_BUFFER *psBuffer);
EMXXLFB_BOOL EMXXLFBWaitForVSync(EMXXLFB_DEVINFO *psDevInfo);
EMXXLFB_ERROR EMXXLFBUnblankDisplay(EMXXLFB_DEVINFO *psDevInfo);
EMXXLFB_ERROR EMXXLFBEnableLFBEventNotification(EMXXLFB_DEVINFO *psDevInfo);
EMXXLFB_ERROR EMXXLFBDisableLFBEventNotification(EMXXLFB_DEVINFO *psDevInfo);
void EMXXLFBCreateSwapChainLockInit(EMXXLFB_DEVINFO *psDevInfo);
void EMXXLFBCreateSwapChainLockDeInit(EMXXLFB_DEVINFO *psDevInfo);
void EMXXLFBCreateSwapChainLock(EMXXLFB_DEVINFO *psDevInfo);
void EMXXLFBCreateSwapChainUnLock(EMXXLFB_DEVINFO *psDevInfo);
void EMXXLFBAtomicBoolInit(EMXXLFB_ATOMIC_BOOL *psAtomic, EMXXLFB_BOOL bVal);
void EMXXLFBAtomicBoolDeInit(EMXXLFB_ATOMIC_BOOL *psAtomic);
void EMXXLFBAtomicBoolSet(EMXXLFB_ATOMIC_BOOL *psAtomic, EMXXLFB_BOOL bVal);
EMXXLFB_BOOL EMXXLFBAtomicBoolRead(EMXXLFB_ATOMIC_BOOL *psAtomic);
void EMXXLFBAtomicIntInit(EMXXLFB_ATOMIC_INT *psAtomic, int iVal);
void EMXXLFBAtomicIntDeInit(EMXXLFB_ATOMIC_INT *psAtomic);
void EMXXLFBAtomicIntSet(EMXXLFB_ATOMIC_INT *psAtomic, int iVal);
int EMXXLFBAtomicIntRead(EMXXLFB_ATOMIC_INT *psAtomic);
void EMXXLFBAtomicIntInc(EMXXLFB_ATOMIC_INT *psAtomic);

#endif 

