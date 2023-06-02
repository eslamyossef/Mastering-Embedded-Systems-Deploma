// Eslam youssef hosny

#include <stdint.h>
void reset_handler(void);
extern int main(void);

void default_handler(void)
{
	reset_handler();
}
//Some Interrupt functions Definition 
void NMI_handler(void)__attribute__((weak,alias("default_handler")));;
void H_fault_handler(void)__attribute__((weak,alias("default_handler")));;

static unsigned long stack_top[256]; //1024 byte

// Verctors Section Definition

void ( * const g_p_fn_vectors[])()__attribute__((section(".vectors"))) =
{
(void(*)()) ((unsigned long)stack_top + sizeof(stack_top)),	//address of stack_top casted as pointer to function
	&reset_handler,
	&NMI_handler,
	&H_fault_handler
};


extern unsigned int _S_data;
extern unsigned int _E_data;
extern unsigned int _S_bss;
extern unsigned int _E_bss;
extern unsigned int _E_text;

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






