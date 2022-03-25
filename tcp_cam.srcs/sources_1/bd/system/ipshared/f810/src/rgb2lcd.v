//****************************************Copyright (c)***********************************//
//原子哥在线教学平台：www.yuanzige.com
//技术支持：www.openedv.com
//淘宝店铺：http://openedv.taobao.com
//关注微信公众平台微信号："正点原子"，免费获取ZYNQ & FPGA & STM32 & LINUX资料。
//版权所有，盗版必究。
//Copyright(C) 正点原子 2018-2028
//All rights reserved
//----------------------------------------------------------------------------------------
// File name:           rgb2lcd
// Last modified Date:  2021/6/18 09:48:25
// Last Version:        V1.1
// Descriptions:        RGB格式转LCD格式
//----------------------------------------------------------------------------------------
// Created by:          正点原子
// Created date:        2019/10/8 17:25:36
// Version:             V1.0
// Descriptions:        The original version
//
//----------------------------------------------------------------------------------------
//****************************************************************************************//

module rgb2lcd #(
    //parameter define
    parameter    VID_DATA_WIDTH = 24
)(
    //VID_OUT
    input  [VID_DATA_WIDTH-1:0]   rgb_data ,
    input                         rgb_vde  ,
    input                         rgb_hsync,
    input                         rgb_vsync,

    input                         pixel_clk,
   
    //RGB LCD
    output                        lcd_pclk ,
    output                        lcd_rst  ,
    output                        lcd_hs   ,
    output                        lcd_vs   ,
    output                        lcd_de   ,
    output                        lcd_bl   ,
   
    //AXI GPIO(LCD ID)
    input  [2:0]                  lcd_id_i, 
    input  [2:0]                  lcd_id_t,
    output [2:0]                  lcd_id_o,
    
    //LCD数据引脚为双向引脚,改成三态引脚的形式  
    input  [VID_DATA_WIDTH-1:0]   lcd_rgb_i,
    output [VID_DATA_WIDTH-1:0]   lcd_rgb_o,
    output [VID_DATA_WIDTH-1:0]   lcd_rgb_t
);

//*****************************************************
//**                  main code
//*****************************************************

//LCD信号赋值
assign lcd_pclk = pixel_clk;
assign lcd_de = rgb_vde  ;
assign lcd_hs = rgb_hsync;
assign lcd_vs = rgb_vsync;
assign lcd_bl = 1'b1;
assign lcd_rst = 1'b1;

//读取LCD ID
assign lcd_id_o[0] = (lcd_id_t[0]==1'b1) ? lcd_rgb_i[23] : 1'bz;  //R7:M0
assign lcd_id_o[1] = (lcd_id_t[1]==1'b1) ? lcd_rgb_i[15] : 1'bz;  //G7:M1
assign lcd_id_o[2] = (lcd_id_t[2]==1'b1) ? lcd_rgb_i[7] : 1'bz;   //B7:M2

assign lcd_rgb_o  = (lcd_id_t[0]==1'b1) ? {VID_DATA_WIDTH{1'bz}} :
                                           rgb_data[VID_DATA_WIDTH-1:0];
assign lcd_rgb_t  = {VID_DATA_WIDTH{lcd_id_t[0]}};

endmodule
