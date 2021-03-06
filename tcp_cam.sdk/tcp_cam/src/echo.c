/*
 * Copyright (C) 2009 - 2018 Xilinx, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 */

#include <stdio.h>
#include <string.h>

#include "lwip/err.h"
#include "lwip/tcp.h"
#if defined (__arm__) || defined (__aarch64__)
#include "xil_printf.h"
#endif

#include "cam.h"

#define TCP_TEST  		0x00
#define TCP_CAM_STOP  	0x01
#define TCP_CAM_START  	0x02
#define TCP_CAM_DATA	0x03
#define TCP_CAM_SIZE	0x04
#define TCP_ISP  		0x05


const u8 TCP_SUCCESS	= 0x00;
const u8 TCP_FAILED		= 0x01;
const u8 TCP_UNKNOWN	= 0x03;



void* rd_fram_addr;
void* pack_addr;
u32 rd_index;
u16 pkg_size = 8192;	// send package size
u16 snd_buf;			// send buf size

int transfer_data() {
	return 0;
}

void print_app_header()
{
#if (LWIP_IPV6==0)
	xil_printf("\n\r\n\r-----lwIP TCP echo server ------\n\r");
#else
	xil_printf("\n\r\n\r-----lwIPv6 TCP echo server ------\n\r");
#endif
	xil_printf("TCP packets sent to port 6001 will be echoed back\n\r");
}


err_t recv_callback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err){
	/* do not read the packet if we are not in ESTABLISHED state */
	if (!p) {
		tcp_close(tpcb);
		tcp_recv(tpcb, NULL);
		return ERR_OK;
	}

	/* disable nagle algorithm */
	tcp_nagle_disable(tpcb);

	/* indicate that the packet has been received */
	tcp_recved(tpcb, p->len);

	/* echo back the payload */
//	if(tcp_sndbuf(tpcb) <= p->len){
//		xil_printf("no space in tcp_sndbuf\n\r");
//		pbuf_free(p);
//		return ERR_OK;
//	}

	/* in this case, we assume that the payload is < TCP_SND_BUF */
#ifdef __DEBUG__
	xil_printf("start  ");
#endif

	u8 rsp[12];
	u8 code = ((u8*)(p->payload))[0];	// req code
	u16 t;
	snd_buf = tcp_sndbuf(tpcb);

	switch(code){
	case TCP_TEST:	// TCP_TEST
#ifdef __DEBUG__
		xil_printf("-- Test request. payload:%s\n",p->payload);
#endif
		err = tcp_write(tpcb, (void*)(&TCP_SUCCESS), 1, 1);
		break;
	case TCP_CAM_STOP:	// TCP_STOP
#ifdef __DEBUG__
		xil_printf("-- Camera stop. payload:%s\n", pack_id,p->payload);
#endif
		rd_index = XAxiVdma_CurrFrameStore(&vdma, XAXIVDMA_READ);
		XAxiVdma_StartParking(&vdma, rd_index, XAXIVDMA_READ);
		rd_fram_addr = frame_buffer_addr + vd_mode.height*vd_mode.width*3*rd_index;
		Xil_DCacheFlush();
		err = tcp_write(tpcb, (void*)(&TCP_SUCCESS), 1, 1);
		pack_addr = rd_fram_addr;
		break;
	case TCP_CAM_START:	// TCP_START
#ifdef __DEBUG__
		xil_printf("-- Camera start. payload:%s\n", pack_id,p->payload);
#endif
		XAxiVdma_StopParking(&vdma, XAXIVDMA_READ);
		err = tcp_write(tpcb, (void*)(&TCP_SUCCESS), 1, 1);
		break;
	case TCP_CAM_SIZE:	// TCP_SIZE
#ifdef __DEBUG__
		xil_printf("-- Camera size. payload:%s\n", pack_id,p->payload);
#endif
		// ???????? ????????????????
		rsp[0] = img_size >> 24;
		rsp[1] = img_size >> 16;
		rsp[2] = img_size >> 8;
		rsp[3] = img_size;
		rsp[4] = img_height >> 24;
		rsp[5] = img_height >> 16;
		rsp[6] = img_height >> 8;
		rsp[7] = img_height;
		rsp[8] = img_width >> 24;
		rsp[9] = img_width >> 16;
		rsp[10] = img_width >> 8;
		rsp[11] = img_width;
		err = tcp_write(tpcb, (void*)rsp, 12 , 1);
		break;
	case TCP_CAM_DATA:
#ifdef __DEBUG__
		xil_printf("-- Camera DATA pack:%d pack_addr:%x payload:%s\n", pack_id,pack_addr,p->payload);
		xil_printf("    sndbuf:%d\n",snd_buf);
#endif
		pkg_size = (snd_buf >= 0xf000) ? ((pkg_size >= 0x2000) ? ((pkg_size <20480)? (pkg_size+64):pkg_size) : (pkg_size<<1)) : ((snd_buf > 0x8000) ? (snd_buf >> 2) : (snd_buf >> 3));	// 9mb/s ????
		err = tcp_write(tpcb,pack_addr,pkg_size,0);
		tcp_output(tpcb);
		pack_addr = pack_addr + pkg_size;
		break;
	case TCP_ISP:
#ifdef __DEBUG__
		xil_printf("-- Update ISP params. payload:%s\n", p->payload);
#endif
		t = (((u8*)(p->payload))[1] <<8) + ((u8*)(p->payload))[2];
		ov5640_setparams(p->payload+3,t);	// set params of ISP
		err = tcp_write(tpcb, (void*)(&TCP_SUCCESS), 1, 1);
		break;
	default:
#ifdef __DEBUG__
		xil_printf("-- Unknown code. payload:%s\n", p->payload);
#endif
		err = tcp_write(tpcb, (void*)(&TCP_UNKNOWN), 1, 1);
		break;
	}

#ifdef __DEBUG__
	xil_printf("finish.  snd_buf:%d  pkg_size:%d\n",snd_buf,pkg_size);
#endif

	/* free the received pbuf */
	pbuf_free(p);
	return ERR_OK;
}

err_t accept_callback(void *arg, struct tcp_pcb *newpcb, err_t err)
{
	static int connection = 1;

	/* set the receive callback for this connection */
	tcp_recv(newpcb, recv_callback);

	/* just use an integer number indicating the connection id as the
	   callback argument */
	tcp_arg(newpcb, (void*)(UINTPTR)connection);

	/* increment for subsequent accepted connections */
	connection++;

	return ERR_OK;
}


int start_application()
{
	struct tcp_pcb *pcb;
	err_t err;
	unsigned port = 7;

	/* create new TCP PCB structure */
	pcb = tcp_new_ip_type(IPADDR_TYPE_ANY);
	if (!pcb) {
		xil_printf("Error creating PCB. Out of Memory\n\r");
		return -1;
	}


	/* bind to specified @port */
	err = tcp_bind(pcb, IP_ANY_TYPE, port);
	if (err != ERR_OK) {
		xil_printf("Unable to bind to port %d: err = %d\n\r", port, err);
		return -2;
	}

	/* we do not need any arguments to callback functions */
	tcp_arg(pcb, NULL);

	/* listen for connections */
	pcb = tcp_listen(pcb);
	if (!pcb) {
		xil_printf("Out of memory while tcp_listen\n\r");
		return -3;
	}

	/* specify callback to use for incoming connections */
	tcp_accept(pcb, accept_callback);

	xil_printf("TCP echo server started @ port %d\n\r", port);

	return 0;
}
