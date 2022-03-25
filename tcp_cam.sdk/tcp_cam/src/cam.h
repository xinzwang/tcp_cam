/*
 * cam.h
 *
 *  Created on: 2022��3��10��
 *      Author: ������
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

//ȫ�ֱ���
//frame buffer����ʼ��ַ
static unsigned int const frame_buffer_addr = (XPAR_PS7_DDR_0_S_AXI_BASEADDR + 0x1000000);

// ץ��ͼ��Ļ����ַ
static unsigned int const tcp_addr = (XPAR_PS7_DDR_0_S_AXI_BASEADDR + 0x11000000);

XAxiVdma     vdma;
DisplayCtrl  dispCtrl;
XGpio        axi_gpio_inst;   //PL�� AXI GPIO ����ʵ��
VideoMode    vd_mode;
unsigned int lcd_id;



# endif