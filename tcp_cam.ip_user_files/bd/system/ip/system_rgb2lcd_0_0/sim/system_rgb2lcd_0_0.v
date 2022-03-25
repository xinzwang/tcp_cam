// (c) Copyright 1995-2022 Xilinx, Inc. All rights reserved.
// 
// This file contains confidential and proprietary information
// of Xilinx, Inc. and is protected under U.S. and
// international copyright and other intellectual property
// laws.
// 
// DISCLAIMER
// This disclaimer is not a license and does not grant any
// rights to the materials distributed herewith. Except as
// otherwise provided in a valid license issued to you by
// Xilinx, and to the maximum extent permitted by applicable
// law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
// WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
// AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
// BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
// INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
// (2) Xilinx shall not be liable (whether in contract or tort,
// including negligence, or under any other theory of
// liability) for any loss or damage of any kind or nature
// related to, arising under or in connection with these
// materials, including for any direct, or any indirect,
// special, incidental, or consequential loss or damage
// (including loss of data, profits, goodwill, or any type of
// loss or damage suffered as a result of any action brought
// by a third party) even if such damage or loss was
// reasonably foreseeable or Xilinx had been advised of the
// possibility of the same.
// 
// CRITICAL APPLICATIONS
// Xilinx products are not designed or intended to be fail-
// safe, or for use in any application requiring fail-safe
// performance, such as life-support or safety devices or
// systems, Class III medical devices, nuclear facilities,
// applications related to the deployment of airbags, or any
// other applications that could lead to death, personal
// injury, or severe property or environmental damage
// (individually and collectively, "Critical
// Applications"). Customer assumes the sole risk and
// liability of any use of Xilinx products in Critical
// Applications, subject only to applicable laws and
// regulations governing limitations on product liability.
// 
// THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
// PART OF THIS FILE AT ALL TIMES.
// 
// DO NOT MODIFY THIS FILE.


// IP VLNV: www.alientek.com:user:rgb2lcd:1.0
// IP Revision: 3

`timescale 1ns/1ps

(* IP_DEFINITION_SOURCE = "package_project" *)
(* DowngradeIPIdentifiedWarnings = "yes" *)
module system_rgb2lcd_0_0 (
  rgb_data,
  rgb_vde,
  rgb_hsync,
  rgb_vsync,
  pixel_clk,
  lcd_pclk,
  lcd_rst,
  lcd_hs,
  lcd_vs,
  lcd_de,
  lcd_bl,
  lcd_id_i,
  lcd_id_t,
  lcd_id_o,
  lcd_rgb_i,
  lcd_rgb_o,
  lcd_rgb_t
);

(* X_INTERFACE_INFO = "xilinx.com:interface:vid_io:1.0 vid_rgb DATA" *)
input wire [23 : 0] rgb_data;
(* X_INTERFACE_INFO = "xilinx.com:interface:vid_io:1.0 vid_rgb ACTIVE_VIDEO" *)
input wire rgb_vde;
(* X_INTERFACE_INFO = "xilinx.com:interface:vid_io:1.0 vid_rgb HSYNC" *)
input wire rgb_hsync;
(* X_INTERFACE_INFO = "xilinx.com:interface:vid_io:1.0 vid_rgb VSYNC" *)
input wire rgb_vsync;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME pixel_clk, PHASE 0.000, CLK_DOMAIN system_axi_dynclk_0_0_PXL_CLK_O, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 pixel_clk CLK" *)
input wire pixel_clk;
(* X_INTERFACE_INFO = "xilinx.com:user:lcd:1.0 lcd CLK" *)
output wire lcd_pclk;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME lcd_rst, POLARITY ACTIVE_LOW, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 lcd_rst RST" *)
output wire lcd_rst;
(* X_INTERFACE_INFO = "xilinx.com:user:lcd:1.0 lcd HS" *)
output wire lcd_hs;
(* X_INTERFACE_INFO = "xilinx.com:user:lcd:1.0 lcd VS" *)
output wire lcd_vs;
(* X_INTERFACE_INFO = "xilinx.com:user:lcd:1.0 lcd DE" *)
output wire lcd_de;
output wire lcd_bl;
(* X_INTERFACE_INFO = "xilinx.com:interface:gpio:1.0 lcd_id TRI_O" *)
input wire [2 : 0] lcd_id_i;
(* X_INTERFACE_INFO = "xilinx.com:interface:gpio:1.0 lcd_id TRI_T" *)
input wire [2 : 0] lcd_id_t;
(* X_INTERFACE_INFO = "xilinx.com:interface:gpio:1.0 lcd_id TRI_I" *)
output wire [2 : 0] lcd_id_o;
(* X_INTERFACE_INFO = "xilinx.com:interface:gpio:1.0 lcd_rgb TRI_I" *)
input wire [23 : 0] lcd_rgb_i;
(* X_INTERFACE_INFO = "xilinx.com:interface:gpio:1.0 lcd_rgb TRI_O" *)
output wire [23 : 0] lcd_rgb_o;
(* X_INTERFACE_INFO = "xilinx.com:interface:gpio:1.0 lcd_rgb TRI_T" *)
output wire [23 : 0] lcd_rgb_t;

  rgb2lcd #(
    .VID_DATA_WIDTH(24)
  ) inst (
    .rgb_data(rgb_data),
    .rgb_vde(rgb_vde),
    .rgb_hsync(rgb_hsync),
    .rgb_vsync(rgb_vsync),
    .pixel_clk(pixel_clk),
    .lcd_pclk(lcd_pclk),
    .lcd_rst(lcd_rst),
    .lcd_hs(lcd_hs),
    .lcd_vs(lcd_vs),
    .lcd_de(lcd_de),
    .lcd_bl(lcd_bl),
    .lcd_id_i(lcd_id_i),
    .lcd_id_t(lcd_id_t),
    .lcd_id_o(lcd_id_o),
    .lcd_rgb_i(lcd_rgb_i),
    .lcd_rgb_o(lcd_rgb_o),
    .lcd_rgb_t(lcd_rgb_t)
  );
endmodule
