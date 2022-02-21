/*
 * adc.h
 *
 *  Created on: 7 Feb 2022
 *      Author: andreas
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

void pal_acc_init(void);
uint32_t adc_read(void);
void start_conversion(void);

#endif /* ADC_H_ */
