#include <stdio.h>
#include <apps/shell/tash.h>
#include <tinyara/gpio.h>
#include <tinyara/config.h>

#define GPIO_FUNC_SHIFT	13
#define GPIO_INPUT	(0x0 << GPIO_FUNC_SHIFT)
#define GPIO_OUTPUT	(0x1 << GPIO_FUNC_SHIFT)

#define GPIO_PORT_SHIFT	3
#define GPIO_PORTG1	(0x5 << GPIO_PORT_SHIFT)
#define GPIO_PORTG2 (0X6 << GPIO_PORT_SHIFT)

#define GPIO_PIN_SHIFT	0
#define GPIO_PIN4_1 (0X4 << GPIO_PIN_SHIFT) // R_DIR
#define GPIO_PIN2_1 (0X2 << GPIO_PIN_SHIFT) // R_ENA
#define GPIO_PIN1_1 (0X1 << GPIO_PIN_SHIFT) // R_CLK
#define GPIO_PIN3_1 (0X3 << GPIO_PIN_SHIFT) // HALF/FULL
#define GPIO_PIN0_1 (0x0 << GPIO_PIN_SHIFT) // Reset
//
#define GPIO_PIN1_2 (0x1 << GPIO_PIN_SHIFT)//L_DIR
#define GPIO_PIN2_2 (0x2 << GPIO_PIN_SHIFT)//L_ENA
#define GPIO_PIN3_2 (0x3 << GPIO_PIN_SHIFT)//L_CLK

#define GPIO_PUPD_SHIFT 11
#define GPIO_PULLDOWN	(0X1 << GPIO_PUPD_SHIFT)
#define GPIO_PULLUP		(0X3 << GPIO_PUPD_SHIFT)

/*
void leftMoterControl(){

	uint32_t cfgcon_l_dir_pin;
	uint32_t cfgcon_l_ena_pin;
	uint32_t cfgcon_l_clk_pin;

	uint32_t cfgcon_HF_pin;
	uint32_t cfgcon_reset_pin;
	int i=0;

	printf("motor\n");

	cfgcon_l_dir_pin=GPIO_OUTPUT | GPIO_PORTG2 | GPIO_PIN1_2;
	cfgcon_l_ena_pin=GPIO_OUTPUT | GPIO_PORTG2 | GPIO_PIN2_2;
	cfgcon_l_clk_pin=GPIO_OUTPUT | GPIO_PORTG2 | GPIO_PIN3_2;

	cfgcon_HF_pin	=GPIO_OUTPUT | GPIO_PORTG1 | GPIO_PIN3_1;
	cfgcon_reset_pin=GPIO_OUTPUT | GPIO_PORTG1 | GPIO_PIN0_1;

	s5j_configgpio(cfgcon_l_ena_pin);
	s5j_configgpio(cfgcon_l_dir_pin);
	s5j_configgpio(cfgcon_l_clk_pin);

	s5j_configgpio(cfgcon_HF_pin);
	s5j_configgpio(cfgcon_reset_pin);

	////////////////////////////////////////////////////////////////////////

	s5j_gpiowrite(cfgcon_l_dir_pin, 1);
	s5j_gpiowrite(cfgcon_l_ena_pin, 1);
	s5j_gpiowrite(cfgcon_l_clk_pin, 0);

	s5j_gpiowrite(cfgcon_HF_pin, 0);
	s5j_gpiowrite(cfgcon_reset_pin, 1);

	///////////////////////////////////////////////////////////////////////////

	for(i=0; i<400; i++){
		s5j_gpiowrite(cfgcon_l_clk_pin, 1);
		printf("%d\n", i);
		up_mdelay(10);
		s5j_gpiowrite(cfgcon_l_clk_pin, 0);
		up_mdelay(10);
	}
}

void rightMoterControl(){
	uint32_t cfgcon_r_dir_pin;
	uint32_t cfgcon_r_ena_pin;
	uint32_t cfgcon_r_clk_pin;

	uint32_t cfgcon_HF_pin;
	uint32_t cfgcon_reset_pin;
	int i=0;

	printf("motor\n");
	cfgcon_r_dir_pin=GPIO_OUTPUT | GPIO_PORTG1 | GPIO_PIN4_1;
	cfgcon_r_ena_pin=GPIO_OUTPUT | GPIO_PORTG1 | GPIO_PIN2_1;
	cfgcon_r_clk_pin=GPIO_OUTPUT | GPIO_PORTG1 | GPIO_PIN1_1;

	cfgcon_HF_pin	=GPIO_OUTPUT | GPIO_PORTG1 | GPIO_PIN3_1;
	cfgcon_reset_pin=GPIO_OUTPUT | GPIO_PORTG1 | GPIO_PIN0_1;


	s5j_configgpio(cfgcon_r_ena_pin);
	s5j_configgpio(cfgcon_r_dir_pin);
	s5j_configgpio(cfgcon_r_clk_pin);

	s5j_configgpio(cfgcon_HF_pin);
	s5j_configgpio(cfgcon_reset_pin);

	//////////////////////////////////////////////////////////////////////

	s5j_gpiowrite(cfgcon_r_dir_pin, 1);
	s5j_gpiowrite(cfgcon_r_ena_pin, 1);
	s5j_gpiowrite(cfgcon_r_clk_pin, 0);

	s5j_gpiowrite(cfgcon_HF_pin, 0);
	s5j_gpiowrite(cfgcon_reset_pin, 1);


	//////////////////////////////////////////////////////////////////////
	for(i=0; i<400; i++){
		s5j_gpiowrite(cfgcon_r_clk_pin, 1);
		printf("%d\n", i);
		up_mdelay(10);
		s5j_gpiowrite(cfgcon_r_clk_pin, 0);
		up_mdelay(10);
	}


}
*/


int main(int argc, FAR char * argv[]){

	uint32_t cfgcon_r_dir_pin;
	uint32_t cfgcon_r_ena_pin;
	uint32_t cfgcon_r_clk_pin;

	uint32_t cfgcon_l_dir_pin;
	uint32_t cfgcon_l_ena_pin;
	uint32_t cfgcon_l_clk_pin;

	uint32_t cfgcon_HF_pin;
	uint32_t cfgcon_reset_pin;
	int i=0;

	printf("motor\n");
	cfgcon_r_dir_pin=GPIO_OUTPUT | GPIO_PORTG1 | GPIO_PIN4_1;
	cfgcon_r_ena_pin=GPIO_OUTPUT | GPIO_PORTG1 | GPIO_PIN2_1;
	cfgcon_r_clk_pin=GPIO_OUTPUT | GPIO_PORTG1 | GPIO_PIN1_1;

	cfgcon_l_dir_pin=GPIO_OUTPUT | GPIO_PORTG2 | GPIO_PIN1_2;
	cfgcon_l_ena_pin=GPIO_OUTPUT | GPIO_PORTG2 | GPIO_PIN2_2;
	cfgcon_l_clk_pin=GPIO_OUTPUT | GPIO_PORTG2 | GPIO_PIN3_2;

	cfgcon_HF_pin	=GPIO_OUTPUT | GPIO_PORTG1 | GPIO_PIN3_1;
	cfgcon_reset_pin=GPIO_OUTPUT | GPIO_PORTG1 | GPIO_PIN0_1;


	s5j_configgpio(cfgcon_r_ena_pin);
	s5j_configgpio(cfgcon_r_dir_pin);
	s5j_configgpio(cfgcon_r_clk_pin);

	s5j_configgpio(cfgcon_l_ena_pin);
	s5j_configgpio(cfgcon_l_dir_pin);
	s5j_configgpio(cfgcon_l_clk_pin);


	s5j_configgpio(cfgcon_HF_pin);
	s5j_configgpio(cfgcon_reset_pin);

	s5j_gpiowrite(cfgcon_r_dir_pin, 1);
	s5j_gpiowrite(cfgcon_r_ena_pin, 1);
	s5j_gpiowrite(cfgcon_r_clk_pin, 0);

	s5j_gpiowrite(cfgcon_l_dir_pin, 1);
	s5j_gpiowrite(cfgcon_l_ena_pin, 1);
	s5j_gpiowrite(cfgcon_l_clk_pin, 0);

	s5j_gpiowrite(cfgcon_HF_pin, 0);
	s5j_gpiowrite(cfgcon_reset_pin, 1);



	for(i=0; i<400; i++){
		s5j_gpiowrite(cfgcon_r_clk_pin, 1);
		printf("%d\n", i);
		up_mdelay(10);
		s5j_gpiowrite(cfgcon_r_clk_pin, 0);
		up_mdelay(10);
	}

	for(i=0; i<400; i++){
		s5j_gpiowrite(cfgcon_l_clk_pin, 1);
		printf("%d\n", i);
		up_mdelay(10);
		s5j_gpiowrite(cfgcon_l_clk_pin, 0);
		up_mdelay(10);
	}

	return 0;

}
