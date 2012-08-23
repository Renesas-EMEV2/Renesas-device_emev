#
# Copyright (C) Imagination Technologies Ltd. All rights reserved.
# 
# This program is free software; you can redistribute it and/or modify it
# under the terms and conditions of the GNU General Public License,
# version 2, as published by the Free Software Foundation.
# 
# This program is distributed in the hope it will be useful but, except 
# as otherwise stated in writing, without any warranty; without even the 
# implied warranty of merchantability or fitness for a particular purpose. 
# See the GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License along with
# this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
# 
# The full GNU General Public License is included in this distribution in
# the file called "COPYING".
#
# Contact Information:
# Imagination Technologies Ltd. <gpl-support@imgtec.com>
# Home Park Estate, Kings Langley, Herts, WD4 8LZ, UK 
# 
#

TARGET_PRODUCT ?= mickxx

SGXCORE := 540
SGX_CORE_REV := 120

SGX_FEATURE_SYSTEM_CACHE := 1
SGX_BYPASS_SYSTEM_CACHE := 0

SGX_DYNAMIC_TIMING_INFO := 1
SYS_SGX_ACTIVE_POWER_LATENCY_MS := 100

SUPPORT_LINUX_USING_WORKQUEUES := 1

DISPLAY_CONTROLLER := shmobilelfb

PVR_SYSTEM := upd77660
HAL_VARIANT := mickxx

include ../common/android/paths.mk
include ../common/android/armv7-a.mk
include ../common/android/features.mk

ifneq ($(strip $(KERNELDIR)),)
include ../kernel_version.mk
KERNEL_AT_LEAST_2_6_35 := \
 $(shell test $(KERNEL_VERSION)    -ge 2 -a \
			  $(KERNEL_PATCHLEVEL) -ge 6 -a \
			  $(KERNEL_SUBLEVEL)   -ge 35 && echo 1 || echo 0)
ifeq ($(KERNEL_AT_LEAST_2_6_35),1)
PVR_NO_FULL_CACHE_OPS := 1
endif
endif

DISPLAY_CONTROLLER_COMPONENT := dc_shmobilefb_linux
KERNEL_COMPONENTS += $(DISPLAY_CONTROLLER_COMPONENT)

PDUMP := 0
NO_HARDWARE := 0

SUPPORT_LINUX_X86_PAT := 0
SUPPORT_LINUX_X86_WRITECOMBINE := 0

include ../config/core.mk
include ../common/android/extra_config.mk
include ../common/dridrm.mk
include ../common/opencl.mk
include ../common/upd77660.mk
