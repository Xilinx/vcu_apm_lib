/*********************************************************************
 * Copyright (C) 2017-2022 Xilinx, Inc.
 * Copyright (C) 2022-2024 Advanced Micro Devices, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 ********************************************************************/

#ifndef UPERFMON_H_
#define UPERFMON_H_

#include "uio_common.h"

#define APM_INSTANCE_NAME		       "apm"
#define APM_SAMPLE_VALUE_300MHz                0x137D9FC0 //1 second
#define APM_SAMPLE_VALUE_333MHz                0x13DE4355 //1 second
#define APM_CLK_RATE_333MHz                    333000000
#define MAP_CNT				       0x1
#define APM_MODE                               0x6 //Burst Timing Mode
#define POLL_INTERVAL                          (1000*100)

#define XVCUPmon_ReadReg HW_READ
#define XVCUPmon_WriteReg HW_WRITE

int uPerfMon_Init();
void uPerfMon_Enable();
void uPerfMon_Disable();
u32 uPerfMon_Check_SIC_Overflow_Mask();
void uPerfMon_RestartCounters();
int uPerfMon_Wait_for_counter_overflow();
unsigned long uPerfMon_getCounterValue(int apm, int read_write);

#endif /* UPERFMON_H_ */
