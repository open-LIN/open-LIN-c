#include "../../open_lin_cfg.h"
#include "../../open_lin_data_layer.h"
#include "../../open_lin_hw.h"
#include "../../open_lin_network_layer.h"
#include "../../open_lin_slave_data_layer.h"

#include <stdio.h>

l_u8 dataBuffer1[] = {0,0};
l_u8 dataBuffer2[] = {0,1,2,3,4,5,6,7};


int cport_nr=3;        /* /dev/ (COM4 on windows) */


open_lin_frame_slot_t slot_array[] =
{
		{0x12,OPEN_LIN_FRAME_TYPE_RECEIVE,sizeof(dataBuffer1),dataBuffer1},
		{0x01,OPEN_LIN_FRAME_TYPE_TRANSMIT,sizeof(dataBuffer2),dataBuffer2}
};

const l_u8 lenght_of_slot_array = sizeof( slot_array ) / sizeof( open_lin_frame_slot_t );

void open_lin_master_dl_rx_callback(open_lin_frame_slot_t* slot){

}

void open_lin_on_rx_frame(open_lin_frame_slot_t *slot){
	printf("frame received \n");
}

void rx_byte_handle(uint8_t byte)
{
	printf("L > %d \n",byte);
	open_lin_slave_rx_header(byte);
}

int main()
{
	printf("OPEN_LIN slave start \n");

	open_lin_hw_init();
	open_lin_net_init(slot_array,lenght_of_slot_array);

	while (1)
	{

	}

	return 0;
}
