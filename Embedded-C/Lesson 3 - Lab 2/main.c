//Eslam youssef

typedef volatile unsigned int vuint32_t;
#include <stdint.h>
/*********************** Adresses Definition ******************************/
#define RCC_BASE	0x40021000
#define GPIOA_BASE	0x40010800
#define RCC_APB2ENR *(volatile uint32_t *)(RCC_BASE   + 0x18) 
#define GPIOA_CHR   *(volatile uint32_t *)(GPIOA_BASE + 0x04) 
#define GPIOA_ODR   *(volatile uint32_t *)(GPIOA_BASE + 0x0C) 
/*****************************************************/
#define RCC_IOPAEN (1<<2)
#define GPIOA13    (1UL<<13)
/*********************** pointer to data reg ****************************/
typedef union 
{
	vuint32_t all_fields;
	struct{
		vuint32_t reserved:13;
		vuint32_t p_13:1;
	}pin;
}R_ODR_t;

//volatile R_ODR_t* R_ODR = (volatile R_ODR_t*)(GPIOA_BASE + 0x0C);
#define R_ODR ((volatile R_ODR_t*)(GPIOA_BASE + 0x0C))

/*****************************************************/
unsigned char g_arr[3]={1,2,3};
unsigned char const const_arr[3]={1,2,3};
/*****************************************************/

int main(void)
{
	
	int i=0;
	RCC_APB2ENR |= RCC_IOPAEN;
	GPIOA_CHR   &= 0xFF0FFFFF;
	GPIOA_CHR   |= 0x00200000;
	
	while(1)
	{
		//GPIOA_ODR |= 1<<13;
		(R_ODR->pin.p_13) = 1;
		for(i=0 ; i<5000 ; i++);
		
		//GPIOA_ODR &= (~(1<<13));
		(R_ODR->pin.p_13) = 0;
		for(i=0 ; i<5000 ; i++);	
	}
}

extern void NMI_handler(void)
{
	
}