/*
 * open_lin_frame_st32.c
 *
 *  Created on: 25.01.2018
 *      Author: ay7vi2
 */
#include "../../open_lin_cfg.h"
#include "../../open_lin_data_layer.h"
#include "../../open_lin_hw.h"
#include "../../open_lin_network_layer.h"

#include "rs232.h"
#include <pthread.h>

int cport_nr=4;        /* /dev/ttyS0 (COM5 on windows) */
unsigned char str[512] = {0};
int send_index = 0;
unsigned char gl_buf[4096] = {0};
volatile bool breakFlag = false;
pthread_t tid;

void open_lin_error_handler(t_open_lin_error error_code)
{
	/* no error handling */
}

l_bool open_lin_hw_check_for_break(void)
{
	l_bool result = false;
	result = breakFlag;
	breakFlag = false;
	return result;
}

l_bool open_lin_hw_tx_break(void){

}

void open_lin_frame_set_auto_baud(void)
{

}

l_bool open_lin_hw_tx_byte(l_u8 byte)
{
	RS232_SendByte(cport_nr, byte);
	return true;
}

l_bool open_lin_hw_tx_data(l_u8* data, l_u8 len)
{
	for (int i = 0; i < len; i++)
	{
		open_lin_hw_tx_byte(data[i]);
	}
	return true;
}

void open_lin_hw_reset(void) {
	RS232_flushRXTX(cport_nr);
}

open_lin_frame_slot_t* last_rx_slot;
void open_lin_master_dl_rx_callback(open_lin_frame_slot_t* slot)
{
	last_rx_slot  = slot;
}

void *rxDataThread(void *vargp)
{
	unsigned char buf[64];
	int size = sizeof(buf);

	while (1)
	{
		int out_size = 0;
		if(RS232_WaitForBreak(cport_nr,buf,size,&out_size)){
			breakFlag = true;
		} else{
			breakFlag = false;
		}
		for (int i = 0; i < out_size; i++)
		{
			open_lin_slave_rx_header(buf[i]);
		}
		Sleep(10);
	}
	return NULL;
}


void open_lin_hw_init(void)
{
	int bdrate=19200;

	char mode[]={'8','N','1',0};

	if(RS232_OpenComport(cport_nr, bdrate, mode))
	{
		printf("Can not open comport\n");
	}
	send_index  = 0;
	pthread_create(&tid, NULL, rxDataThread, NULL);
}


