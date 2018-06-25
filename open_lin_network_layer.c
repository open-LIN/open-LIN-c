/*
 * open_lin_slave_network_layer.c
 *
 *  Created on: 29.01.2018
 *      Author: ay7vi2
 */

#include "open_lin_network_layer.h"
#include "open_lin_hw.h"

static open_lin_frame_slot_t *slot_array;
static l_u8 slot_array_len;


void open_lin_net_init(open_lin_frame_slot_t *a_slot_array, l_u8 a_slot_array_len)
{
	slot_array = a_slot_array;
	slot_array_len = a_slot_array_len;
	open_lin_set_rx_enabled(true);
}

#ifdef OPEN_LIN_DYNAMIC_IDS
	extern open_lin_id_translation_item_t open_lin_id_translation_tab[];
#endif

open_lin_frame_slot_t* open_lin_net_get_slot(open_lin_pid_t pid)
{
	open_lin_frame_slot_t *result = OPEN_LIN_NET_SLOT_EMPTY;
	uint8_t i = 0;
#ifdef OPEN_LIN_DYNAMIC_IDS
	for(i = 0; i < (slot_array_len); i++)
	{
		if (open_lin_id_translation_tab[i].input_id == pid)
		{
			pid = open_lin_id_translation_tab[i].id_in_lin_table;
			break;
		} else
		{
			/* do nothing */
		}
	}
#endif
	for(i = 0; i < (slot_array_len); i++)
	{
		if (slot_array[i].pid == pid){
			result = &slot_array[i];
			break;
		} else
		{
			/* do nothing */
		}
	}

	return result;
};

void open_lin_net_rx_handler(open_lin_pid_t pid) {
	open_lin_frame_slot_t* slot = open_lin_net_get_slot(pid);
	open_lin_on_rx_frame(slot);
};
