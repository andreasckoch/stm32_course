#include <stdio.h>
#include <stdint.h>

#include "stm32f4xx.h"
#include "adxl345.h"
#include "uart.h"

int16_t x,y,z;  // 2 bytes per axis
float xg, yg, zg;

extern uint8_t data_rec[6];

int main(void)
{
	uart2_tx_init();
	adxl_init();

	while(1)
	{
		adxl_read_values(DATA_START_ADDR);

		x = ((data_rec[1]<<8) | data_rec[0]);
		y = ((data_rec[3]<<8) | data_rec[2]);
		z = ((data_rec[5]<<8) | data_rec[4]);

		xg = (x * 0.0078);
		yg = (y * 0.0078);
		zg = (z * 0.0078);
	}

}



