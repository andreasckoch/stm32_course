
#include "stm32f4xx.h"


#define TIM1EN			(1U<<0)
#define TIM2EN			(1U<<0)
#define TIM4EN			(1U<<2)
#define CR1_CEN			(1U<<0)
#define OC_TOGGLE_CH2	((1U<<12) | (1U<<13))
#define CCER_CC2E		(1U<<4)

#define GPIOAEN			(1U<<0)
#define AFR9_TIM		(1U<<4)

#define GPIODEN			(1U<<3)
#define AFR12_TIM		(1U<<17)
#define OC_TOGGLE_CH1	((1U<<4) | (1U<<5))
#define CCER_CC1E		(1U<<0)


void tim2_1hz_init(void)
{
	/* Enable clock access */
	RCC->APB1ENR |= TIM2EN;

	/* Set prescaler value */
	TIM2->PSC = 1600 - 1;		// 16 000 000 / 1600 = 10000

	/* Set autoreload value */
	TIM2->ARR = 10000 - 1;		// 10000 / 10000 = 1

	/* Clear counter */
	TIM2->CNT = 0;

	/* Enable timer */
	TIM2->CR1 |= CR1_CEN;
}

void tim1_pa9_output_compare(void) // toggling LD7 in alternate function mode doesn't work --> LD4 works
{
	/* Enable clock access to GPIOA */
	RCC->AHB1ENR |= GPIOAEN;

	/* Set PA9 mode to alternate function */
	GPIOA->MODER &=~(1U<<18);
	GPIOA->MODER |= (1U<<19);

	/* Set PA9 alternate function type to TIM1_CH2 (AF01) */
	GPIOA->AFR[1] |= AFR9_TIM;
	GPIOA->AFR[1] &=~(1U<<5);
	GPIOA->AFR[1] &=~(1U<<6);
	GPIOA->AFR[1] &=~(1U<<7);

	/* Enable clock access to tim1 */
	RCC->APB2ENR |= TIM1EN;

	/* Set prescaler value */
	TIM1->PSC = 1600 - 1;		// 16 000 000 / 1600 = 10000

	/* Set autoreload value */
	TIM1->ARR = 10000 - 1;		// 10000 / 10000 = 1

	/* Set output compare toggle mode */
	TIM1->CCMR1 |= OC_TOGGLE_CH2;

	/* Enable tim1 ch2 in compare mode */
	TIM1->CCER |= CCER_CC2E;

	/* Clear counter */
	TIM1->CNT = 0;

	/* Enable timer */
	TIM1->CR1 |= CR1_CEN;
}

void tim4_pd12_output_compare(void)
{
	/* Enable clock access to GPIOD */
	RCC->AHB1ENR |= GPIODEN;

	/* Set PD12 mode to alternate function (LD4 at PD12) */
	GPIOD->MODER &=~(1U<<24);
	GPIOD->MODER |= (1U<<25);

	/* Set PA9 alternate function type to TIM4_CH1 (AF02) */
	GPIOD->AFR[1] |= AFR12_TIM;

	/* Enable clock access to tim4 */
	RCC->APB1ENR |= TIM4EN;

	/* Set prescaler value */
	TIM4->PSC = 1600 - 1;		// 16 000 000 / 1600 = 10000

	/* Set autoreload value */
	TIM4->ARR = 10000 - 1;		// 10000 / 10000 = 1

	/* Set output compare toggle mode */
	TIM4->CCMR1 |= OC_TOGGLE_CH1;

	/* Enable tim1 ch2 in compare mode */
	TIM4->CCER |= CCER_CC1E;

	/* Clear counter */
	TIM4->CNT = 0;

	/* Enable timer */
	TIM4->CR1 |= CR1_CEN;
}
