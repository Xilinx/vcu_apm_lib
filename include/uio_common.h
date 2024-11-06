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

#ifndef UIO_COMMON_H_
#define UIO_COMMON_H_

#include <stdint.h>
/***************** Macros (Inline Functions) Definitions *********************/
#define MAX_UIO_PATH_SIZE       256
#define MAX_UIO_NAME_SIZE       64
#define MAX_UIO_MAPS            5
#define UIO_INVALID_ADDR        0
#define XIL_COMPONENT_IS_READY  1
#define XIL_COMPONENT_NOT_READY 0
#define HW_WRITE(addr, off, val) *((volatile uint32_t *) ( ((uint8_t*)addr)+ off )) = (val)
#define HW_READ(addr,off) *((volatile uint32_t *) ( ((uint8_t*)addr) + off ));

/**************************** Type Definitions ******************************/
typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short int u16;

typedef struct {
	u32 addr;
	u32 size;
} uio_map;

typedef struct {
	int isInitialized;
	int  uio_fd;
	int  uio_num;
	char name[ MAX_UIO_NAME_SIZE ];
	char version[ MAX_UIO_NAME_SIZE ];
	uio_map maps[ MAX_UIO_MAPS ];
} uio_info;

typedef struct {
	void *Control_bus_BaseAddress; /* Base address of VCU APM */
	void *params[MAX_UIO_MAPS];
	u32 IsReady;
} uio_handle;

enum err_code {
	XST_SUCCESS,
	XST_DEVICE_NOT_FOUND,
	XST_OPEN_DEVICE_FAILED,
	XST_ERR_TIMEOUT
};

int uio_Initialize(uio_info *InfoPtr, const char* InstanceName);
int uio_get_Handler(uio_info *InfoPtr, uio_handle *handle, int map_count);
int uio_release_handle(uio_info *InfoPtr, uio_handle *handle, int map_count);

#endif /* UIO_COMMON_H_ */
