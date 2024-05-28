//Where is the led connected?
//Port:A, B
//Pin:5,13
#include <stdint.h>
#define PERIPH_BASE		    0x40000000UL
#define AHB1PERIPH_OFFSET   0x00020000UL
#define AHB1PERIPH_BASE     (PERIPH_BASE+AHB1PERIPH_OFFSET)
#define GPIOA_OFFSET		(0x0000UL)
#define GPIOA_BASE			(AHB1PERIPH_BASE+GPIOA_OFFSET)
#define RCC_OFFSET			(0x00023800UL)
#define RCC_BASE      		(PERIPH_BASE+RCC_OFFSET)
#define AHB1EN_R_OFFSET		(0x30UL)
#define RCC_AHB1EN_R		(*(volatile unsigned int*)(RCC_BASE+AHB1EN_R_OFFSET))

#define GPIOAEN				(1U<<0)//shift left 1 to position 0
#define MODE_R_OFFSET		(0x00U)
#define GPIOA_MODE_R		(*(volatile unsigned int*)(GPIOA_BASE+MODE_R_OFFSET))
#define OD_R_OFFSET			(0x14UL)
#define GPIOA_OD_R			(*(volatile unsigned int*)(GPIOA_BASE+OD_R_OFFSET))
#define PIN5				(1U<<5)
#define LED_PIN				PIN5

typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t PLLCFGR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t AHB1RFTR;
	volatile uint32_t AHB2RFTR;
	volatile uint32_t APB1RFTR;
	volatile uint32_t APB2RFTR;
	volatile uint32_t AHB1ENR;
	volatile uint32_t AHB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t AHB1LPENR;
	volatile uint32_t AHB2LPENR;
	volatile uint32_t APB1LPENR;
	volatile uint32_t AP2LPENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t SSCGR;
	volatile uint32_t PLLI2SCFGR;
	volatile uint32_t DCKCFGR;
}RCC_TypeDef;

typedef struct
{
	volatile uint32_t MODER;//Address offset is 0x00
	volatile uint32_t OTYPER;//Address offset is 0x04 more than 4bytes
	volatile uint32_t OSPEEDR;//...0x08
	volatile uint32_t PUPDR;//0x12
	volatile uint32_t IDR;//0x16
	volatile uint32_t ODR;
}GPIO_TypeDef;

#define RCC    ((RCC_TypeDef*)RCC_BASE)
#define GPIOA  ((GPIO_TypeDef*)GPIOA_BASE)

int main(void)
{
	//ENABLE CLOCK ACCESS TO GPIOA
	RCC->APB1ENR|= GPIOAEN;
	//SET PINA5 AS OUTPUT PIN bit (1u<<10), &=~(1u<<11)
	GPIOA ->MODER |=(1U<<10);
	GPIOA->MODER&=~(1U<<11);
	while(1)
	{
		//set pina5 high
		//GPIOA_OD_R |=LED_PIN;
		//toggle PA5
		GPIOA->ODR|=LED_PIN;
		for(int i=0;i<100000;i++){}

	}
}




