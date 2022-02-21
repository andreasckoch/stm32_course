#include "stm32f4xx.h"

#define SYSTICK_LOAD_VAL		16000	// for 1ms
#define CTRL_ENABLE				(1U<<0)
#define CTRL_CLKSRC				(1U<<2)
#define CTRL_COUNTFLAG			(1U<<16)


/* delay in ms */
void systickDelayMs(int delay)
{

	/* Reload with number of clocks per millisecond */
	SysTick->LOAD = SYSTICK_LOAD_VAL;

	/* Clear systick current value register */
	SysTick->VAL = 0;

	/* Enable systick and select internal clk src */
	SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSRC;

	for(int i=0; i<delay; i++){
		/* wait until the countflag is set (after 1ms passed) */
		while ((SysTick->CTRL & CTRL_COUNTFLAG) == 0){}
	}
	/* Disable systick */
	SysTick->CTRL = 0;
}

