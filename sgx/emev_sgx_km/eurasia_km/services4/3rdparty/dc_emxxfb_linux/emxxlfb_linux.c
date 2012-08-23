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

#ifndef AUTOCONF_INCLUDED
#include <linux/config.h>
#endif

#include <linux/version.h>

#include <asm/atomic.h>

#if defined(SUPPORT_DRI_DRM)
#include <drm/drmP.h>
#else
#include <linux/module.h>
#endif

#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/hardirq.h>
#include <linux/mutex.h>
#include <linux/workqueue.h>
#include <linux/fb.h>
#include <linux/console.h>
#include <linux/mutex.h>

#include "img_defs.h"
#include "servicesext.h"
#include "kerneldisplay.h"
#include "emxxlfb.h"
#include "pvrmodule.h"
#if defined(SUPPORT_DRI_DRM)
#include "pvr_drm.h"
#include "3rdparty_dc_drm_shared.h"
#endif

#if !defined(PVR_LINUX_USING_WORKQUEUES)
#error "PVR_LINUX_USING_WORKQUEUES must be defined"
#endif

MODULE_SUPPORTED_DEVICE(DEVNAME);

void *EMXXLFBAllocKernelMem(unsigned long ulSize)
{
	return kmalloc(ulSize, GFP_KERNEL);
}

void EMXXLFBFreeKernelMem(void *pvMem)
{
	kfree(pvMem);
}

void EMXXLFBCreateSwapChainLockInit(EMXXLFB_DEVINFO *psDevInfo)
{
	mutex_init(&psDevInfo->sCreateSwapChainMutex);
}

void EMXXLFBCreateSwapChainLockDeInit(EMXXLFB_DEVINFO *psDevInfo)
{
	mutex_destroy(&psDevInfo->sCreateSwapChainMutex);
}

void EMXXLFBCreateSwapChainLock(EMXXLFB_DEVINFO *psDevInfo)
{
	mutex_lock(&psDevInfo->sCreateSwapChainMutex);
}

void EMXXLFBCreateSwapChainUnLock(EMXXLFB_DEVINFO *psDevInfo)
{
	mutex_unlock(&psDevInfo->sCreateSwapChainMutex);
}

void EMXXLFBAtomicBoolInit(EMXXLFB_ATOMIC_BOOL *psAtomic, EMXXLFB_BOOL bVal)
{
	atomic_set(psAtomic, (int)bVal);
}

void EMXXLFBAtomicBoolDeInit(EMXXLFB_ATOMIC_BOOL *psAtomic)
{
}

void EMXXLFBAtomicBoolSet(EMXXLFB_ATOMIC_BOOL *psAtomic, EMXXLFB_BOOL bVal)
{
	atomic_set(psAtomic, (int)bVal);
}

EMXXLFB_BOOL EMXXLFBAtomicBoolRead(EMXXLFB_ATOMIC_BOOL *psAtomic)
{
	return (EMXXLFB_BOOL)atomic_read(psAtomic);
}

void EMXXLFBAtomicIntInit(EMXXLFB_ATOMIC_INT *psAtomic, int iVal)
{
	atomic_set(psAtomic, iVal);
}

void EMXXLFBAtomicIntDeInit(EMXXLFB_ATOMIC_INT *psAtomic)
{
}

void EMXXLFBAtomicIntSet(EMXXLFB_ATOMIC_INT *psAtomic, int iVal)
{
	atomic_set(psAtomic, iVal);
}

int EMXXLFBAtomicIntRead(EMXXLFB_ATOMIC_INT *psAtomic)
{
	return atomic_read(psAtomic);
}

void EMXXLFBAtomicIntInc(EMXXLFB_ATOMIC_INT *psAtomic)
{
	atomic_inc(psAtomic);
}

EMXXLFB_ERROR EMXXLFBGetLibFuncAddr (char *szFunctionName, PFN_DC_GET_PVRJTABLE *ppfnFuncTable)
{
	if(strcmp("PVRGetDisplayClassJTable", szFunctionName) != 0)
	{
		return (EMXXLFB_ERROR_INVALID_PARAMS);
	}

	
	*ppfnFuncTable = PVRGetDisplayClassJTable;

	return (EMXXLFB_OK);
}

void EMXXLFBQueueBufferForSwap(EMXXLFB_SWAPCHAIN *psSwapChain, EMXXLFB_BUFFER *psBuffer)
{
	int res = queue_work(psSwapChain->psWorkQueue, &psBuffer->sWork);

	if (res == 0)
	{
		printk(KERN_WARNING DRIVER_PREFIX ": %s: Device %u: Buffer already on work queue\n", __FUNCTION__, psSwapChain->uiFBDevID);
	}
}

static void WorkQueueHandler(struct work_struct *psWork)
{
	EMXXLFB_BUFFER *psBuffer = container_of(psWork, EMXXLFB_BUFFER, sWork);

	EMXXLFBSwapHandler(psBuffer);
}

EMXXLFB_ERROR EMXXLFBCreateSwapQueue(EMXXLFB_SWAPCHAIN *psSwapChain)
{
	
	psSwapChain->psWorkQueue = __create_workqueue(DEVNAME, 1, 1, 1);
	if (psSwapChain->psWorkQueue == NULL)
	{
		printk(KERN_WARNING DRIVER_PREFIX ": %s: Device %u: create_singlethreaded_workqueue failed\n", __FUNCTION__, psSwapChain->uiFBDevID);

		return (EMXXLFB_ERROR_INIT_FAILURE);
	}

	return (EMXXLFB_OK);
}

void EMXXLFBInitBufferForSwap(EMXXLFB_BUFFER *psBuffer)
{
	INIT_WORK(&psBuffer->sWork, WorkQueueHandler);
}

void EMXXLFBDestroySwapQueue(EMXXLFB_SWAPCHAIN *psSwapChain)
{
	destroy_workqueue(psSwapChain->psWorkQueue);
}

void EMXXLFBFlip(EMXXLFB_DEVINFO *psDevInfo, EMXXLFB_BUFFER *psBuffer)
{
	struct fb_var_screeninfo sFBVar;
	int res;
	unsigned long ulYResVirtual;

	acquire_console_sem();

	sFBVar = psDevInfo->psLINFBInfo->var;

	sFBVar.xoffset = 0;
	sFBVar.yoffset = psBuffer->ulYOffset;

	ulYResVirtual = psBuffer->ulYOffset + sFBVar.yres;

	
	if (sFBVar.xres_virtual != sFBVar.xres || sFBVar.yres_virtual < ulYResVirtual)
	{
		sFBVar.xres_virtual = sFBVar.xres;
		sFBVar.yres_virtual = ulYResVirtual;

		sFBVar.activate = FB_ACTIVATE_NOW | FB_ACTIVATE_FORCE;

		res = fb_set_var(psDevInfo->psLINFBInfo, &sFBVar);
		if (res != 0)
		{
			printk(KERN_INFO DRIVER_PREFIX ": %s: Device %u: fb_set_var failed (Y Offset: %lu, Error: %d)\n", __FUNCTION__, psDevInfo->uiFBDevID, psBuffer->ulYOffset, res);
		}
	}
	else
	{
		res = fb_pan_display(psDevInfo->psLINFBInfo, &sFBVar);
		if (res != 0)
		{
			printk(KERN_INFO DRIVER_PREFIX ": %s: Device %u: fb_pan_display failed (Y Offset: %lu, Error: %d)\n", __FUNCTION__, psDevInfo->uiFBDevID, psBuffer->ulYOffset, res);
		}
	}

	release_console_sem();
}

EMXXLFB_BOOL EMXXLFBWaitForVSync(EMXXLFB_DEVINFO *psDevInfo)
{
	UNREFERENCED_PARAMETER(psDevInfo);
	return EMXXLFB_TRUE;
}

static int EMXXLFBFrameBufferEvents(struct notifier_block *psNotif,
                             unsigned long event, void *data)
{
	EMXXLFB_DEVINFO *psDevInfo;
	struct fb_event *psFBEvent = (struct fb_event *)data;
	struct fb_info *psFBInfo = psFBEvent->info;
	EMXXLFB_BOOL bBlanked;

	
	if (event != FB_EVENT_BLANK)
	{
		return 0;
	}

	bBlanked = (*(IMG_INT *)psFBEvent->data != 0) ? EMXXLFB_TRUE: EMXXLFB_FALSE;

	psDevInfo = EMXXLFBGetDevInfoPtr(psFBInfo->node);

#if 0
	if (psDevInfo != NULL)
	{
		if (bBlanked)
		{
			DEBUG_PRINTK((KERN_INFO DRIVER_PREFIX ": %s: Device %u: Blank event received\n", __FUNCTION__, psDevInfo->uiFBDevID));
		}
		else
		{
			DEBUG_PRINTK((KERN_INFO DRIVER_PREFIX ": %s: Device %u: Unblank event received\n", __FUNCTION__, psDevInfo->uiFBDevID));
		}
	}
	else
	{
		DEBUG_PRINTK((KERN_INFO DRIVER_PREFIX ": %s: Device %u: Blank/Unblank event for unknown framebuffer\n", __FUNCTION__, psFBInfo->node));
	}
#endif

	if (psDevInfo != NULL)
	{
		EMXXLFBAtomicBoolSet(&psDevInfo->sBlanked, bBlanked);
		EMXXLFBAtomicIntInc(&psDevInfo->sBlankEvents);
	}

	return 0;
}

EMXXLFB_ERROR EMXXLFBUnblankDisplay(EMXXLFB_DEVINFO *psDevInfo)
{
	int res;

	acquire_console_sem();
	res = fb_blank(psDevInfo->psLINFBInfo, 0);
	release_console_sem();
	if (res != 0 && res != -EINVAL)
	{
		printk(KERN_WARNING DRIVER_PREFIX
			": %s: Device %u: fb_blank failed (%d)\n", __FUNCTION__, psDevInfo->uiFBDevID, res);
		return (EMXXLFB_ERROR_GENERIC);
	}

	return (EMXXLFB_OK);
}

#ifdef CONFIG_HAS_EARLYSUSPEND

static void EMXXLFBBlankDisplay(EMXXLFB_DEVINFO *psDevInfo)
{
	acquire_console_sem();
	fb_blank(psDevInfo->psLINFBInfo, 1);
	release_console_sem();
}

static void EMXXLFBEarlySuspendHandler(struct early_suspend *h)
{
	unsigned uiMaxFBDevIDPlusOne = EMXXLFBMaxFBDevIDPlusOne();
	unsigned i;

	for (i=0; i < uiMaxFBDevIDPlusOne; i++)
	{
		EMXXLFB_DEVINFO *psDevInfo = EMXXLFBGetDevInfoPtr(i);

		if (psDevInfo != NULL)
		{
			EMXXLFBAtomicBoolSet(&psDevInfo->sEarlySuspendFlag, EMXXLFB_TRUE);
			EMXXLFBBlankDisplay(psDevInfo);
		}
	}
}

static void EMXXLFBEarlyResumeHandler(struct early_suspend *h)
{
	unsigned uiMaxFBDevIDPlusOne = EMXXLFBMaxFBDevIDPlusOne();
	unsigned i;

	for (i=0; i < uiMaxFBDevIDPlusOne; i++)
	{
		EMXXLFB_DEVINFO *psDevInfo = EMXXLFBGetDevInfoPtr(i);

		if (psDevInfo != NULL)
		{
			EMXXLFBUnblankDisplay(psDevInfo);
			EMXXLFBAtomicBoolSet(&psDevInfo->sEarlySuspendFlag, EMXXLFB_FALSE);
		}
	}
}

#endif 

EMXXLFB_ERROR EMXXLFBEnableLFBEventNotification(EMXXLFB_DEVINFO *psDevInfo)
{
	int                res;
	EMXXLFB_ERROR         eError;

	
	memset(&psDevInfo->sLINNotifBlock, 0, sizeof(psDevInfo->sLINNotifBlock));

	psDevInfo->sLINNotifBlock.notifier_call = EMXXLFBFrameBufferEvents;

	EMXXLFBAtomicBoolSet(&psDevInfo->sBlanked, EMXXLFB_FALSE);
	EMXXLFBAtomicIntSet(&psDevInfo->sBlankEvents, 0);

	res = fb_register_client(&psDevInfo->sLINNotifBlock);
	if (res != 0)
	{
		printk(KERN_WARNING DRIVER_PREFIX
			": %s: Device %u: fb_register_client failed (%d)\n", __FUNCTION__, psDevInfo->uiFBDevID, res);

		return (EMXXLFB_ERROR_GENERIC);
	}

	eError = EMXXLFBUnblankDisplay(psDevInfo);
	if (eError != EMXXLFB_OK)
	{
		printk(KERN_WARNING DRIVER_PREFIX
			": %s: Device %u: UnblankDisplay failed (%d)\n", __FUNCTION__, psDevInfo->uiFBDevID, eError);
		return eError;
	}

#ifdef CONFIG_HAS_EARLYSUSPEND
	psDevInfo->sEarlySuspend.suspend = EMXXLFBEarlySuspendHandler;
	psDevInfo->sEarlySuspend.resume = EMXXLFBEarlyResumeHandler;
	psDevInfo->sEarlySuspend.level = EARLY_SUSPEND_LEVEL_BLANK_SCREEN;
	register_early_suspend(&psDevInfo->sEarlySuspend);
#endif

	return (EMXXLFB_OK);
}

EMXXLFB_ERROR EMXXLFBDisableLFBEventNotification(EMXXLFB_DEVINFO *psDevInfo)
{
	int res;

#ifdef CONFIG_HAS_EARLYSUSPEND
	unregister_early_suspend(&psDevInfo->sEarlySuspend);
#endif

	
	res = fb_unregister_client(&psDevInfo->sLINNotifBlock);
	if (res != 0)
	{
		printk(KERN_WARNING DRIVER_PREFIX
			": %s: Device %u: fb_unregister_client failed (%d)\n", __FUNCTION__, psDevInfo->uiFBDevID, res);
		return (EMXXLFB_ERROR_GENERIC);
	}

	EMXXLFBAtomicBoolSet(&psDevInfo->sBlanked, EMXXLFB_FALSE);

	return (EMXXLFB_OK);
}

#if defined(SUPPORT_DRI_DRM) && defined(PVR_DISPLAY_CONTROLLER_DRM_IOCTL)
static EMXXLFB_DEVINFO *EMXXLFBPVRDevIDToDevInfo(unsigned uiPVRDevID)
{
	unsigned uiMaxFBDevIDPlusOne = EMXXLFBMaxFBDevIDPlusOne();
	unsigned i;

	for (i=0; i < uiMaxFBDevIDPlusOne; i++)
	{
		EMXXLFB_DEVINFO *psDevInfo = EMXXLFBGetDevInfoPtr(i);

		if (psDevInfo->uiPVRDevID == uiPVRDevID)
		{
			return psDevInfo;
		}
	}

	printk(KERN_WARNING DRIVER_PREFIX
		": %s: PVR Device %u: Couldn't find device\n", __FUNCTION__, uiPVRDevID);

	return NULL;
}

int PVR_DRM_MAKENAME(DISPLAY_CONTROLLER, _Ioctl)(struct drm_device unref__ *dev, void *arg, struct drm_file unref__ *pFile)
{
	uint32_t *puiArgs;
	uint32_t uiCmd;
	unsigned uiPVRDevID;
	int ret = 0;
	EMXXLFB_DEVINFO *psDevInfo;

	if (arg == NULL)
	{
		return -EFAULT;
	}

	puiArgs = (uint32_t *)arg;
	uiCmd = puiArgs[PVR_DRM_DISP_ARG_CMD];
	uiPVRDevID = puiArgs[PVR_DRM_DISP_ARG_DEV];

	psDevInfo = EMXXLFBPVRDevIDToDevInfo(uiPVRDevID);
	if (psDevInfo == NULL)
	{
		return -EINVAL;
	}


	switch (uiCmd)
	{
		case PVR_DRM_DISP_CMD_LEAVE_VT:
		case PVR_DRM_DISP_CMD_ENTER_VT:
		{
			EMXXLFB_BOOL bLeaveVT = (uiCmd == PVR_DRM_DISP_CMD_LEAVE_VT);
			DEBUG_PRINTK((KERN_WARNING DRIVER_PREFIX ": %s: PVR Device %u: %s\n",
				__FUNCTION__, uiPVRDevID,
				bLeaveVT ? "Leave VT" : "Enter VT"));

			EMXXLFBCreateSwapChainLock(psDevInfo);
			
			EMXXLFBAtomicBoolSet(&psDevInfo->sLeaveVT, bLeaveVT);
			if (psDevInfo->psSwapChain != NULL)
			{
				flush_workqueue(psDevInfo->psSwapChain->psWorkQueue);

				if (bLeaveVT)
				{
					EMXXLFBFlip(psDevInfo, &psDevInfo->sSystemBuffer);
					(void) EMXXLFBCheckModeAndSync(psDevInfo);
				}
			}

			EMXXLFBCreateSwapChainUnLock(psDevInfo);
			(void) EMXXLFBUnblankDisplay(psDevInfo);
			break;
		}
		case PVR_DRM_DISP_CMD_ON:
		case PVR_DRM_DISP_CMD_STANDBY:
		case PVR_DRM_DISP_CMD_SUSPEND:
		case PVR_DRM_DISP_CMD_OFF:
		{
			int iFBMode;
#if defined(DEBUG)
			{
				const char *pszMode;
				switch(uiCmd)
				{
					case PVR_DRM_DISP_CMD_ON:
						pszMode = "On";
						break;
					case PVR_DRM_DISP_CMD_STANDBY:
						pszMode = "Standby";
						break;
					case PVR_DRM_DISP_CMD_SUSPEND:
						pszMode = "Suspend";
						break;
					case PVR_DRM_DISP_CMD_OFF:
						pszMode = "Off";
						break;
					default:
						pszMode = "(Unknown Mode)";
						break;
				}
				printk (KERN_WARNING DRIVER_PREFIX ": %s: PVR Device %u: Display %s\n",
				__FUNCTION__, uiPVRDevID, pszMode);
			}
#endif
			switch(uiCmd)
			{
				case PVR_DRM_DISP_CMD_ON:
					iFBMode = FB_BLANK_UNBLANK;
					break;
				case PVR_DRM_DISP_CMD_STANDBY:
					iFBMode = FB_BLANK_HSYNC_SUSPEND;
					break;
				case PVR_DRM_DISP_CMD_SUSPEND:
					iFBMode = FB_BLANK_VSYNC_SUSPEND;
					break;
				case PVR_DRM_DISP_CMD_OFF:
					iFBMode = FB_BLANK_POWERDOWN;
					break;
				default:
					return -EINVAL;
			}

			EMXXLFBCreateSwapChainLock(psDevInfo);

			if (psDevInfo->psSwapChain != NULL)
			{
				flush_workqueue(psDevInfo->psSwapChain->psWorkQueue);
			}

			acquire_console_sem();
			ret = fb_blank(psDevInfo->psLINFBInfo, iFBMode);
			release_console_sem();

			EMXXLFBCreateSwapChainUnLock(psDevInfo);

			break;
		}
		default:
		{
			ret = -EINVAL;
			break;
		}
	}

	return ret;
}
#endif

#if defined(SUPPORT_DRI_DRM)
int PVR_DRM_MAKENAME(DISPLAY_CONTROLLER, _Init)(struct drm_device unref__ *dev)
#else
static int __init EMXXLFB_Init(void)
#endif
{

	if(EMXXLFBInit() != EMXXLFB_OK)
	{
		printk(KERN_WARNING DRIVER_PREFIX ": %s: EMXXLFBInit failed\n", __FUNCTION__);
		return -ENODEV;
	}

	return 0;

}

#if defined(SUPPORT_DRI_DRM)
void PVR_DRM_MAKENAME(DISPLAY_CONTROLLER, _Cleanup)(struct drm_device unref__ *dev)
#else
static void __exit EMXXLFB_Cleanup(void)
#endif
{    
	if(EMXXLFBDeInit() != EMXXLFB_OK)
	{
		printk(KERN_WARNING DRIVER_PREFIX ": %s: EMXXLFBDeInit failed\n", __FUNCTION__);
	}
}

#if !defined(SUPPORT_DRI_DRM)
late_initcall(EMXXLFB_Init);
module_exit(EMXXLFB_Cleanup);
#endif
