/*
 * tim.h
 *
 *  Created on: 8 Feb 2022
 *      Author: andreas
 */

#ifndef TIM_H_
#define TIM_H_

void tim2_1hz_init(void);
void tim1_pa9_output_compare(void);
void tim4_pd12_output_compare(void);


#define SR_UIF			(1U<<0)

#endif /* TIM_H_ */
