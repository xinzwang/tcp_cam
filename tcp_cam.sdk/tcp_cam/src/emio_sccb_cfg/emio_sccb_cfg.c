//****************************************Copyright (c)***********************************//
//ԭ�Ӹ����߽�ѧƽ̨��www.yuanzige.com
//����֧�֣�www.openedv.com
//�Ա����̣�http://openedv.taobao.com
//��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡZYNQ & FPGA & STM32 & LINUX���ϡ�
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2018-2028
//All rights reserved
//----------------------------------------------------------------------------------------
// File name:           emio_sccb_cfg.c
// Last modified Date:  2019/06/30 15:59:46
// Last Version:        V1.0
// Descriptions:        SCCB����
//----------------------------------------------------------------------------------------
// Created by:          ����ԭ��
// Created date:        2019/06/30 15:59:52
// Version:             V1.0
// Descriptions:        The original version
//
//----------------------------------------------------------------------------------------
//****************************************************************************************//

#include"emio_sccb_cfg.h"

#define  GPIOPS_ID  XPAR_XGPIOPS_0_DEVICE_ID  //PS �� GPIO ���� ID

static  XGpioPs  gpiops_inst; //PS �� GPIO ����ʵ��

//EMIO��ʼ��
void emio_init(void)
{

	XGpioPs_Config *gpiops_cfg_ptr; //PS �� GPIO ������Ϣ

	//�������� ID ����������Ϣ
	gpiops_cfg_ptr = XGpioPs_LookupConfig(GPIOPS_ID);
	//��ʼ����������
	XGpioPs_CfgInitialize(&gpiops_inst, gpiops_cfg_ptr, gpiops_cfg_ptr->BaseAddr);

	//���� sccb�˿� Ϊ���
	XGpioPs_SetDirectionPin(&gpiops_inst, EMIO_SCL_NUM, 1);
	XGpioPs_SetDirectionPin(&gpiops_inst, EMIO_SDA_NUM, 1);

	//ʹ��sccb�˿� ���
	XGpioPs_SetOutputEnablePin(&gpiops_inst, EMIO_SCL_NUM, 1);
	XGpioPs_SetOutputEnablePin(&gpiops_inst, EMIO_SDA_NUM, 1);

	//��sccb��SCLK��SDA������
	XGpioPs_WritePin(&gpiops_inst, EMIO_SCL_NUM, 1);
	XGpioPs_WritePin(&gpiops_inst, EMIO_SDA_NUM, 1);
}

//����sccb��ʼ�ź�
void sccb_start(void)
{
	XGpioPs_WritePin(&gpiops_inst, EMIO_SCL_NUM, 1);
	XGpioPs_WritePin(&gpiops_inst, EMIO_SDA_NUM, 1);

	usleep(4);

 	XGpioPs_WritePin(&gpiops_inst, EMIO_SDA_NUM, 0);  //START:when CLK is high,DATA change form high to low

 	usleep(4);

 	XGpioPs_WritePin(&gpiops_inst, EMIO_SCL_NUM, 0);  //ǯסI2C���ߣ�׼�����ͻ��������

}

//����sccbֹͣ�ź�
void sccb_stop(void)
{

	XGpioPs_WritePin(&gpiops_inst, EMIO_SCL_NUM, 0);

	XGpioPs_WritePin(&gpiops_inst,EMIO_SDA_NUM, 0);  //STOP:when CLK is high DATA change form low to high

 	usleep(4);

	XGpioPs_WritePin(&gpiops_inst, EMIO_SCL_NUM, 1);

	usleep(4);

	XGpioPs_WritePin(&gpiops_inst, EMIO_SDA_NUM, 1);  //����I2C���߽����ź�

}

//sccb����һ���ֽ�
void sccb_send_byte(u8 txd)
{
    u8 t;

    XGpioPs_WritePin(&gpiops_inst, EMIO_SCL_NUM, 0);  //����ʱ�ӿ�ʼ���ݴ���

    for(t=0; t<8; t++)
    {
        XGpioPs_WritePin(&gpiops_inst, EMIO_SDA_NUM, (txd&0x80)>>7);

        txd<<=1;

        usleep(4);

        XGpioPs_WritePin(&gpiops_inst, EMIO_SCL_NUM, 1);

        usleep(4);

        XGpioPs_WritePin(&gpiops_inst, EMIO_SCL_NUM, 0);

        usleep(4);
    }
}

//SCCB����һ���ֽ�
u8  sccb_rece_byte(void)
{
	unsigned char i=0 , rxd=0;

	XGpioPs_SetOutputEnablePin(&gpiops_inst, EMIO_SDA_NUM, 0);
	XGpioPs_SetDirectionPin(&gpiops_inst, EMIO_SDA_NUM, 0);

	XGpioPs_WritePin(&gpiops_inst, EMIO_SCL_NUM, 0);
	usleep(4);

	for(i=0;i<8;i++ )
	{
        XGpioPs_WritePin(&gpiops_inst, EMIO_SCL_NUM, 1);
        usleep(2);

        rxd <<= 1;
        if( XGpioPs_ReadPin(&gpiops_inst, EMIO_SDA_NUM) ) {
        	rxd = rxd | 0x01;
        }
		usleep(2);

		XGpioPs_WritePin(&gpiops_inst, EMIO_SCL_NUM, 0);
		usleep(4);
    }

	XGpioPs_SetDirectionPin(&gpiops_inst, EMIO_SDA_NUM, 1);  //SDA����Ϊ���
	XGpioPs_SetOutputEnablePin(&gpiops_inst, EMIO_SDA_NUM, 1);

    return rxd;

}

//����ACKӦ��
void sccb_ack(void)
{
	XGpioPs_WritePin(&gpiops_inst, EMIO_SCL_NUM, 0);
	XGpioPs_WritePin(&gpiops_inst, EMIO_SDA_NUM, 0);

	usleep(4);

	XGpioPs_WritePin(&gpiops_inst, EMIO_SCL_NUM, 1);

	usleep(4);

	XGpioPs_WritePin(&gpiops_inst, EMIO_SCL_NUM, 0);

	usleep(4);
}

