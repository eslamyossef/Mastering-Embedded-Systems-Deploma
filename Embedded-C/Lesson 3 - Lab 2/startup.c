// Eslam youssef hosny

#include <stdio.h>
extern unsigned int _S_data;
extern unsigned int _E_data;
extern unsigned int _S_bss;
extern unsigned int _E_bss;
extern unsigned int _E_text;
extern unsigned int _stack_top;
extern int main(void);

void reset_handler(void)
{
	unsigned int i;
	
	//Copy data from flash to Sram
	unsigned int data_size = (unsigned char*)&_E_data - (unsigned char*)&_S_data;
	unsigned char * p_src = (unsigned char*)_E_text;
	unsigned char * p_dst = (unsigned char*)_S_data;
	for(i=0 ; i<data_size ;i++)
	{
		*((unsigned char*)p_dst++) = *((unsigned char*)p_src++);
	}
	
	//init Bss
	unsigned int bss_size = (unsigned char*)&_E_bss - (unsigned char*)&_S_bss;
	p_dst = (unsigned char*)_S_bss;
	for(i=0 ; i<bss_size ; i++)
	{
		*((unsigned char*)p_dst++) = (unsigned char)0;
	}
	
	//jump to main
	main();
}

//a Default function to be called instead on interrupt functions if thay are not defined
void default_handler(void)
{
	reset_handler();
}

//Some Interrupt functions Definition 
void NMI_handler(void)__attribute__((weak,alias("default_handler")));;
void H_fault_handler(void)__attribute__((weak,alias("default_handler")));;
void MM_fault_hadler(void)__attribute__((weak,alias("default_handler")));;
void Bus_fault(void)__attribute__((weak,alias("default_handler")));;
void usage_fault_handler(void)__attribute__((weak,alias("default_handler")));;

// Verctors Section Definition
uint32_t vectors[] __attribute__((section(".vectors"))) ={
	(uint32_t) &_stack_top,
	(uint32_t) &reset_handler,
	(uint32_t) &NMI_handler,
	(uint32_t) &H_fault_handler,
	(uint32_t) &MM_fault_hadler,
	(uint32_t) &Bus_fault,
	(uint32_t) &usage_fault_handler,
};

