#----------------------摄像头接口的时钟---------------------------
#72M
create_clock -period 13.888 -name cam_pclk [get_ports cam_pclk_0]
set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets cam_pclk_0_IBUF]
create_clock -period 13.888 -name cam_pclk [get_ports cam_pclk_1]
set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets cam_pclk_1_IBUF]


#----------------------摄像头接口1---------------------------
set_property -dict {PACKAGE_PIN U10 IOSTANDARD LVCMOS33} [get_ports cam_rst_n_0]
set_property -dict {PACKAGE_PIN V11 IOSTANDARD LVCMOS33} [get_ports cam_pwdn_0]
set_property -dict {PACKAGE_PIN T9 IOSTANDARD LVCMOS33} [get_ports {cam_data_0[0]}]
set_property -dict {PACKAGE_PIN W6 IOSTANDARD LVCMOS33} [get_ports {cam_data_0[1]}]
set_property -dict {PACKAGE_PIN V6 IOSTANDARD LVCMOS33} [get_ports {cam_data_0[2]}]
set_property -dict {PACKAGE_PIN Y7 IOSTANDARD LVCMOS33} [get_ports {cam_data_0[3]}]
set_property -dict {PACKAGE_PIN Y6 IOSTANDARD LVCMOS33} [get_ports {cam_data_0[4]}]
set_property -dict {PACKAGE_PIN Y9 IOSTANDARD LVCMOS33} [get_ports {cam_data_0[5]}]
set_property -dict {PACKAGE_PIN Y8 IOSTANDARD LVCMOS33} [get_ports {cam_data_0[6]}]
set_property -dict {PACKAGE_PIN W10 IOSTANDARD LVCMOS33} [get_ports {cam_data_0[7]}]
set_property -dict {PACKAGE_PIN U9 IOSTANDARD LVCMOS33} [get_ports cam_href_0]
set_property -dict {PACKAGE_PIN W9 IOSTANDARD LVCMOS33} [get_ports cam_pclk_0]
set_property -dict {PACKAGE_PIN W8 IOSTANDARD LVCMOS33} [get_ports cam_vsync_0]
#cam_scl:
set_property -dict {PACKAGE_PIN V8 IOSTANDARD LVCMOS33} [get_ports {GPIO_tri_io[2]}]
#cam_sda:
set_property -dict {PACKAGE_PIN U8 IOSTANDARD LVCMOS33} [get_ports {GPIO_tri_io[3]}]
#pull up
set_property PULLUP true [get_ports {GPIO_tri_io[2]}]
set_property PULLUP true [get_ports {GPIO_tri_io[3]}]



