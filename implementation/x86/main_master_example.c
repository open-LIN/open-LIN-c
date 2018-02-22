#include "../../open_lin_cfg.h"
#include "../../open_lin_data_layer.h"
#include "../../open_lin_hw.h"
#include "../../open_lin_network_layer.h"
#include "../../open_lin_master_data_layer.h"

#include <stdio.h>
#include <synchapi.h>


int cport_nr=4;        /* /dev/ttyS0 (COM5 on windows) */


uint8_t master_data_buffer_tx_1[] = {0xAA,0xBB};
uint8_t master_data_buffer_rx_1[8];
const t_master_frame_table_item master_frame_table[] = {
//		{10,0,{0x02,OPEN_LIN_FRAME_TYPE_TRANSMIT,sizeof(master_data_buffer_tx_1),master_data_buffer_tx_1}},
		{100,100,{0x01,OPEN_LIN_FRAME_TYPE_RECEIVE,sizeof(master_data_buffer_rx_1),master_data_buffer_rx_1}}
};
const uint8_t table_size = sizeof(master_frame_table)/sizeof(t_master_frame_table_item);

void open_lin_on_rx_frame(open_lin_frame_slot_t *slot){
	printf("NOT USED IN MASTER SHOULD BE FIXED!");
}

open_lin_frame_slot_t* last_rx_slot;
void open_lin_master_dl_rx_callback(open_lin_frame_slot_t* slot)
{
	last_rx_slot  = slot;
	printf("Open-LIN master rx data");
	for (int i = 0; i < sizeof(master_data_buffer_rx_1); i++)
	{
		printf(" %d ",master_data_buffer_rx_1[i]);
	}
	printf("\n");

}

void rx_byte_handle(uint8_t byte)
{
	open_lin_master_dl_rx(byte);
}

int main()
{
	printf("Open-LIN master example");

	open_lin_hw_init();
	open_lin_master_dl_init((t_master_frame_table_item *)master_frame_table,table_size);

	while (1)
	{
		Sleep(10);
		open_lin_master_dl_handler(1);
	}

	return 1;
}
