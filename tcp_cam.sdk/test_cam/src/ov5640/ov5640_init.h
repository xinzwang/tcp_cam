//****************************************Copyright (c)***********************************//
//ԭ�Ӹ����߽�ѧƽ̨��www.yuanzige.com
//����֧�֣�www.openedv.com
//�Ա����̣�http://openedv.taobao.com
//��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡZYNQ & FPGA & STM32 & LINUX���ϡ�
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2018-2028
//All rights reserved
//----------------------------------------------------------------------------------------
// File name:           ov5640_init.h
// Last modified Date:  2019/07/01 15:59:46
// Last Version:        V1.0
// Descriptions:        ov5640����
//----------------------------------------------------------------------------------------
// Created by:          ����ԭ��
// Created date:        2019/07/01 15:59:52
// Version:             V1.0
// Descriptions:        The original version
//
//----------------------------------------------------------------------------------------
//****************************************************************************************//


#include "xil_types.h"
#include"sleep.h"

#ifndef OV5640_INIT_H_
#define OV5640_INIT_H_


u8 ov5640_init( u16 cmos_h_pixel, u16 cmos_v_pixel, u16 total_h_pixel, u16 total_v_pixel );


#endif /* OV5640_INIT_H_ */
