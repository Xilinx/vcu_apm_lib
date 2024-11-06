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

#ifndef PERFMON_HW_H_
#define PERFMON_HW_H_

#ifdef __cplusplus
extern "C"
{
#endif

/************************** Constant Definitions ****************************/
#define APM0_CFG 0x100
#define APM0_TIMER 0x104
#define APM0_TRG 0x108
#define APM0_RESULT2 0x114
#define APM0_RESULT3 0x118


#define APM1_CFG 0x200
#define APM1_TIMER 0x204
#define APM1_TRG 0x208
#define APM1_RESULT2 0x214
#define APM1_RESULT3 0x218

#define APM2_CFG 0x300
#define APM2_TIMER 0x304
#define APM2_TRG 0x308
#define APM2_RESULT2 0x314
#define APM2_RESULT3 0x318


#define APM3_CFG 0x400
#define APM3_TIMER 0x404
#define APM3_TRG 0x408
#define APM3_RESULT2 0x414
#define APM3_RESULT3 0x418

#define APM_ISR 0x70
#define APM_INT_GBL_CNTL 0x90

#ifdef __cplusplus
}
#endif
#endif /* PERFMON_HW_H_ */
