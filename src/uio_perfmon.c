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

#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "uio_common.h"
#include "uio_perfmon.h"
#include "uio_perfmon_hw.h"

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

static uio_info uPMonInfo;

/****************************************************************************/
/**
 *
 * This function sets the Sample Interval Register
 *
 * @param	InstancePtr is a pointer to the XAxiPmon instance.
 * @param	SampleIntervalHigh is the Sample Interval Register higher
 *		32 bits.
 * @param	SampleIntervalLow is the Sample Interval Register lower
 *		32 bits.
 *
 * @return	None
 *
 * @note		None.
 *
 *****************************************************************************/
void XVCUPmon_SetSampleInterval(const uio_handle *InstancePtr,
		u32 SampleInterval) {

	/*
	 * Assert the arguments.
	 */
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	/*
	 * Set Sample Interval
	 */
	XVCUPmon_WriteReg(InstancePtr->Control_bus_BaseAddress,
			APM0_TIMER, SampleInterval);
	XVCUPmon_WriteReg(InstancePtr->Control_bus_BaseAddress,
			APM1_TIMER, SampleInterval);
	XVCUPmon_WriteReg(InstancePtr->Control_bus_BaseAddress,
			APM2_TIMER, SampleInterval);
	XVCUPmon_WriteReg(InstancePtr->Control_bus_BaseAddress,
			APM3_TIMER, SampleInterval);

}

bool XVCUPmon_IsClkRate333MHz() {
	u32 clk_rate = 0;
	FILE *vcu_apm_clk = NULL;

	if ((vcu_apm_clk = fopen("/sys/kernel/debug/clk/vcu_apm_clk/clk_rate", "r")) != NULL) {
		fscanf(vcu_apm_clk, "%d", &clk_rate);
		if (clk_rate == APM_CLK_RATE_333MHz) {
			fclose(vcu_apm_clk);
			return true;
		}
		fclose(vcu_apm_clk);
	}

	return false;
}

void XVCUPmon_SetCfg(const uio_handle *InstancePtr, u32 cfg) {

	/*
	 * Assert the arguments.
	 */
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	/*
	 * Set Sample Interval
	 */
	XVCUPmon_WriteReg(InstancePtr->Control_bus_BaseAddress,
			APM0_CFG, cfg);
	XVCUPmon_WriteReg(InstancePtr->Control_bus_BaseAddress,
			APM1_CFG, cfg);
	XVCUPmon_WriteReg(InstancePtr->Control_bus_BaseAddress,
			APM2_CFG, cfg);
	XVCUPmon_WriteReg(InstancePtr->Control_bus_BaseAddress,
			APM3_CFG, cfg);

	/* Controls APM timing window completion interrupt */
	XVCUPmon_WriteReg(InstancePtr->Control_bus_BaseAddress,
			APM_INT_GBL_CNTL, 0x0);
}

void XVCUPmon_SetTrg(const uio_handle *InstancePtr, u32 mode) {

	/*
	 * Assert the arguments.
	 */
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	/*
	 * Set Sample Interval
	 */
	XVCUPmon_WriteReg(InstancePtr->Control_bus_BaseAddress,
			APM0_TRG, mode);
	XVCUPmon_WriteReg(InstancePtr->Control_bus_BaseAddress,
			APM1_TRG, mode);
	XVCUPmon_WriteReg(InstancePtr->Control_bus_BaseAddress,
			APM2_TRG, mode);
	XVCUPmon_WriteReg(InstancePtr->Control_bus_BaseAddress,
			APM3_TRG, mode);

}

u32 XVCUPmon_GetInterruptStatus(const uio_handle *InstancePtr) {
	/*
	 * Assert the arguments.
	 */
	u32 RegValue;
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
	RegValue = XVCUPmon_ReadReg(InstancePtr->Control_bus_BaseAddress,APM_ISR);
	XVCUPmon_WriteReg(InstancePtr->Control_bus_BaseAddress,APM_ISR, RegValue);
	return RegValue;
}

u32 XVCUPmon_GetSampleCounter(const uio_handle *InstancePtr, u32 apm,
		u32 read_write) {

	/*
	 * Assert the arguments.
	 */
	u32 RegValue;
	int result_offset = 0;
	int offset = 0;
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	if (read_write)
		result_offset = 4;

	offset = APM0_RESULT2 + (APM0_CFG * apm) + result_offset;
	RegValue = XVCUPmon_ReadReg(InstancePtr->Control_bus_BaseAddress,offset);

	return RegValue;
}
/*-------------------------------------- interface-------------------------------*/

u32 uPerfMon_Check_SIC_Overflow_Mask() {
	u32 reg = 0;
	uio_handle pmon_handle;

	assert(uPMonInfo.isInitialized == XIL_COMPONENT_IS_READY);
	uio_get_Handler(&uPMonInfo, &pmon_handle, MAP_CNT);
	assert(pmon_handle.IsReady == XIL_COMPONENT_IS_READY);
	if (XVCUPmon_GetInterruptStatus(&pmon_handle) & 0x1)
		reg = 1;

	uio_release_handle(&uPMonInfo, &pmon_handle, MAP_CNT);
	return reg;

}

unsigned long uPerfMon_getCounterValue(int apm, int read_write) {
	uio_handle pmon_handle;
	unsigned long perfCount = 0;

	assert(uPMonInfo.isInitialized == XIL_COMPONENT_IS_READY);
	uio_get_Handler(&uPMonInfo, &pmon_handle, MAP_CNT);

	perfCount = XVCUPmon_GetSampleCounter(&pmon_handle, apm, read_write);
	uio_release_handle(&uPMonInfo, &pmon_handle, MAP_CNT);
	return perfCount;
}

int uPerfMon_Init() {
	uio_handle pmon_handle;

	int ret = uio_Initialize(&uPMonInfo, APM_INSTANCE_NAME);
	if (ret == XST_DEVICE_NOT_FOUND)
		return ret;

	assert(uPMonInfo.isInitialized == XIL_COMPONENT_IS_READY);
	uio_get_Handler(&uPMonInfo, &pmon_handle, MAP_CNT);
	assert(pmon_handle.IsReady == XIL_COMPONENT_IS_READY);

	bool clk_rate = XVCUPmon_IsClkRate333MHz();
	if (clk_rate) {
		XVCUPmon_SetSampleInterval(&pmon_handle, APM_SAMPLE_VALUE_333MHz); // Equals 1 second
	} else {
		XVCUPmon_SetSampleInterval(&pmon_handle, APM_SAMPLE_VALUE_300MHz); // Equals 1 second
	}

	XVCUPmon_SetCfg(&pmon_handle, APM_MODE);

	uio_release_handle(&uPMonInfo, &pmon_handle, MAP_CNT);

	return ret;
}

void uPerfMon_Enable() {
	uio_handle pmon_handle;

	assert(uPMonInfo.isInitialized == XIL_COMPONENT_IS_READY);
	uio_get_Handler(&uPMonInfo, &pmon_handle, MAP_CNT);
	assert(pmon_handle.IsReady == XIL_COMPONENT_IS_READY);

	XVCUPmon_SetTrg(&pmon_handle, 0x1);
	uio_release_handle(&uPMonInfo, &pmon_handle, MAP_CNT);
}

void uPerfMon_Disable() {
	uio_handle pmon_handle;

	assert(uPMonInfo.isInitialized == XIL_COMPONENT_IS_READY);
	uio_get_Handler(&uPMonInfo, &pmon_handle, MAP_CNT);
	assert(pmon_handle.IsReady == XIL_COMPONENT_IS_READY);
	XVCUPmon_SetTrg(&pmon_handle, 0x0);

	uio_release_handle(&uPMonInfo, &pmon_handle, MAP_CNT);
}
