//****************************************Copyright (c)***********************************//
//ԭ�Ӹ����߽�ѧƽ̨��www.yuanzige.com
//����֧�֣�www.openedv.com
//�Ա����̣�http://openedv.taobao.com
//��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡZYNQ & FPGA & STM32 & LINUX���ϡ�
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2018-2028
//All rights reserved
//----------------------------------------------------------------------------------------
// File name:           main.c
// Last modified Date:  2019/07/01 15:59:46
// Last Version:        V1.0
// Descriptions:        OV5640����ͷ����LCDʾ��
//----------------------------------------------------------------------------------------
// Created by:          ����ԭ��
// Created date:        2019/07/01 15:59:52
// Version:             V1.0
// Descriptions:        The original version
//
//----------------------------------------------------------------------------------------
//****************************************************************************************//

/***************************** Include Files *********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xil_types.h"
#include "xil_cache.h"
#include "xparameters.h"
#include "xgpio.h"
#include "xaxivdma.h"
#include "xaxivdma_i.h"
#include "display_ctrl/display_ctrl.h"
#include "vdma_api/vdma_api.h"
#include "emio_sccb_cfg/emio_sccb_cfg.h"
#include "ov5640/ov5640_init.h"

//�궨��
#define BYTES_PIXEL        3                           //�����ֽ�����RGB888ռ3���ֽ�
#define FRAME_BUFFER_NUM   3                           //֡�������3
#define DYNCLK_BASEADDR    XPAR_AXI_DYNCLK_0_BASEADDR  //��̬ʱ�ӻ���ַ
#define VDMA_ID            XPAR_AXIVDMA_0_DEVICE_ID    //VDMA����ID
#define DISP_VTC_ID        XPAR_VTC_0_DEVICE_ID        //VTC����ID
//PL��  AXI GPIO 0(lcd_id)���� ID
#define AXI_GPIO_0_ID      XPAR_AXI_GPIO_0_DEVICE_ID   
//ʹ��AXI GPIO(lcd_id)ͨ��1
#define AXI_GPIO_0_CHANEL  1                           

//ȫ�ֱ���
//frame buffer����ʼ��ַ
unsigned int const frame_buffer_addr = (XPAR_PS7_DDR_0_S_AXI_BASEADDR
										+ 0x1000000);
XAxiVdma     vdma;
DisplayCtrl  dispCtrl;
XGpio        axi_gpio_inst;   //PL�� AXI GPIO ����ʵ��
VideoMode    vd_mode;
unsigned int lcd_id;

int main(void)
{
	u32 status;
	u16 cmos_h_pixel;   //ov5640 DVP ���ˮƽ���ص���
	u16 cmos_v_pixel;   //ov5640 DVP �����ֱ���ص���
	u16 total_h_pixel;  //ov5640 ˮƽ�����ش�С
	u16 total_v_pixel;  //ov5640 ��ֱ�����ش�С

	XGpio_Initialize(&axi_gpio_inst,AXI_GPIO_0_ID);                //GPIO��ʼ��
	XGpio_SetDataDirection(&axi_gpio_inst,AXI_GPIO_0_CHANEL,0x07); //����AXI GPIOΪ����
	lcd_id = LTDC_PanelID_Read(&axi_gpio_inst,AXI_GPIO_0_CHANEL);  //��ȡLCD��ID
	XGpio_SetDataDirection(&axi_gpio_inst,AXI_GPIO_0_CHANEL,0x00); //����AXI GPIOΪ���
	xil_printf("LCD ID: %x\r\n",lcd_id);

	//���ݻ�ȡ��LCD��ID��������ov5640��ʾ�ֱ��ʲ�����ѡ��
	switch(lcd_id){
		case 0x4342 :  //4.3����,480*272�ֱ���
			cmos_h_pixel = 480;
			cmos_v_pixel = 272;
			total_h_pixel = 1800;
			total_v_pixel = 1000;
			break;
		case 0x4384 :  //4.3����,800*480�ֱ���
			cmos_h_pixel = 800;
			cmos_v_pixel = 480;
			total_h_pixel = 1800;
			total_v_pixel = 1000;
			break;
		case 0x7084 :  //7����,800*480�ֱ���
			cmos_h_pixel = 800;
			cmos_v_pixel = 480;
			total_h_pixel = 1800;
			total_v_pixel = 1000;
			break;
		case 0x7016 :  //7����,1024*600�ֱ���
			cmos_h_pixel = 1024;
			cmos_v_pixel = 600;
			total_h_pixel = 2200;
			total_v_pixel = 1000;
			break;
		case 0x1018 :  //10.1����,1280*800�ֱ���
			cmos_h_pixel = 1280;
			cmos_v_pixel = 800;
			total_h_pixel = 2570;
			total_v_pixel = 980;
			break;
		default :
			cmos_h_pixel = 480;
			cmos_v_pixel = 272;
			total_h_pixel = 1800;
			total_v_pixel = 1000;
			break;
	}

	emio_init();                         //��ʼ��EMIO
	status = ov5640_init( cmos_h_pixel,  //��ʼ��ov5640
						  cmos_v_pixel,
						 total_h_pixel,
						 total_v_pixel);
	if(status == 0)
		xil_printf("OV5640 detected successful!\r\n");
	else
		xil_printf("OV5640 detected failed!\r\n");

	//���ݻ�ȡ��LCD��ID��������video������ѡ��
	switch(lcd_id){
		case 0x4342 : vd_mode = VMODE_480x272;  break;  //4.3����,480*272�ֱ���
		case 0x4384 : vd_mode = VMODE_800x480;  break;  //4.3����,800*480�ֱ���
		case 0x7084 : vd_mode = VMODE_800x480;  break;  //7����,800*480�ֱ���
		case 0x7016 : vd_mode = VMODE_1024x600; break;  //7����,1024*600�ֱ���
		case 0x1018 : vd_mode = VMODE_1280x800; break;  //10.1����,1280*800�ֱ���
		default : vd_mode = VMODE_800x480; break;
	}

	//����VDMA
	run_vdma_frame_buffer(&vdma, VDMA_ID, vd_mode.width, vd_mode.height,
							frame_buffer_addr,0,0,BOTH);
	//��ʼ��Display controller
	DisplayInitialize(&dispCtrl, DISP_VTC_ID, DYNCLK_BASEADDR);
    //����VideoMode
	DisplaySetMode(&dispCtrl, &vd_mode);
	DisplayStart(&dispCtrl);

    return 0;
}

