/*
 * cam.h
 *
 *  Created on: 2022年3月10日
 *      Author: 王欣哲
 */
#ifndef _CAM_H_
#define _CAM_H_
// axi vdma
#include "xaxivdma.h"
#include "xaxivdma_i.h"
// camera sscb display vdma
#include "display_ctrl/display_ctrl.h"
#include "vdma_api/vdma_api.h"
#include "emio_sccb_cfg/emio_sccb_cfg.h"
#include "ov5640/ov5640_init.h"

//#define __DEBUG__

static u32 img_width = 800;
static u32 img_height = 480;
static u32 img_size = 1152000;

//全局变量
//frame buffer的起始地址
static unsigned int const frame_buffer_addr = (XPAR_PS7_DDR_0_S_AXI_BASEADDR + 0x1000000);

// 抓拍图像的缓存地址
static unsigned int const tcp_addr = (XPAR_PS7_DDR_0_S_AXI_BASEADDR + 0x11000000);

XAxiVdma     vdma;
DisplayCtrl  dispCtrl;
XGpio        axi_gpio_inst;   //PL端 AXI GPIO 驱动实例
VideoMode    vd_mode;
unsigned int lcd_id;



# endif
