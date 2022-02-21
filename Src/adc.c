#include "stm32f4xx.h"
#include "adc.h"

#define GPIOAEN			(1U<<0)
#define ADC1EN			(1U<<8)
#define ADC_CH1			(1U<<0)
#define ADC_SEQ_LEN1	0x00
#define CR2_ADON		(1U<<0)
#define CR2_SWSTART		(1U<<30)
#define CR2_CONT		(1U<<1)
#define SR_EOC			(1U<<1)


void pal_acc_init(void)
{
	/*** Configure the ADC GPIO pin ***/

	/* Enable clock access to PGIOA */
	RCC->AHB1ENR |= GPIOAEN;

	/* Set the mode of PA1 to analog */
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);

	/*** Configure the ADC module ***/
	/* Enable clock access to ADC */
	RCC->APB2ENR |= ADC1EN;

	/*
	 * For all ADC channels to be used, write their desired order in binary form
	 * to the sequence registers
	 * ch2, ch3, ch5
	 * first = ch5 --> SQ1[4:0] = 00101
	 * second = ch3 --> SQ2[4:0] = 00011
	 * third = ch2 ---> SQ3[4:0] = 00010
	 */
	/* Conversion sequence start */
	ADC1->SQR3 = ADC_CH1;

	/* Conversion sequence length */
	ADC1->SQR1 = ADC_SEQ_LEN1;

	/* Enale ADC module */
	ADC1->CR2 |= CR2_ADON;
}


void start_conversion(void)
{
	/* Enable continuous conversion */
	ADC1->CR2 |= CR2_CONT;

	/* Start ADC conversion */
	ADC1->CR2 |= CR2_SWSTART;
}


uint32_t adc_read(void)
{
	/* Wait for conversion to be complete */
	while(!(ADC1->SR & SR_EOC)){}

	/* Read converted result */
	return (ADC1->DR);
}


