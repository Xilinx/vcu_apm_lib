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

#ifndef PERFMON_H
#define PERFMON_H

#ifdef __cplusplus
extern "C"
{
#endif


#define EXIT_SUCCESS 0
#define EXIT_FAIL -1


enum Perf_Operation {
	E_READ_BYTE_CNT,
	E_WRITE_BYTE_CNT
};

enum Perf_APM {
	E_APM0,
	E_APM1,
	E_APM2,
	E_APM3
};

int perf_monitor_init(void);
int perf_monitor_deinit(void);
unsigned long perf_monitor_get_rd_wr_cnt(enum Perf_APM instance);

#ifdef __cplusplus
}
#endif

#endif
