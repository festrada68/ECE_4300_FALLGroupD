/*
 * main2.cpp
 *
 *  Created on: Nov 28, 2020
 *      Authors: John Wilson, Raymond Banda
 */



/*

#include "Xparameters.h"
#include "xil_printf.h"
#include "xil_io.h"
#include "xbasic_types.h"
#include <stdio.h>
#include "xtmrctr.h" // header file for AXI timer
#include "xtmrctr_l.h" // header file for AXI timer
#include "XGpio.h" // header file for GPIO


#define AES_BASEADDR XPAR_AES_ENCRYPT_IP_0_S00_AXI_BASEADDR

#define KEY_REG 	AES_BASEADDR

#define INPUT_REG 	AES_BASEADDR+16

#define CYPHER_REG 	AES_BASEADDR+32

#define LOAD_REG	AES_BASEADDR+48

#define DONE_REG	AES_BASEADDR+52


#define TIMER_BASE 0x41c00000
#define TIMER_FREQ 100
#define TMRCTR_DEVICE_ID XPAR_TMRCTR_0_DEVICE_ID


XGpio LEDS;
XTmrCtr TimerCounter;
uint32_t key_reg0;
uint32_t key_reg1 ;
uint32_t key_reg2 ;
uint32_t key_reg3;

int init_system()
{
	//initialize LEDs
	//XGpio LEDS;
	XGpio_Initialize(&LEDS,XPAR_GPIO_0_DEVICE_ID); // initialize the GPIO
	XGpio_SetDataDirection(&LEDS,1,0); // set the GPIO as input, since we are using the DIP switches from board
	//XGpio_DiscreteWrite(&LEDS,1,0xFFFF);

	//initialize timer
	//XTmrCtr TimerCounter;
	   int Status = XTmrCtr_Initialize(&TimerCounter,TMRCTR_DEVICE_ID);
	  if(Status != XST_SUCCESS)
	   {
	   	return XST_FAILURE;
	    }

	    //setting up the timer
	XTmrCtr_SetOptions(&TimerCounter,0,XTC_AUTO_RELOAD_OPTION);
	XTmrCtr_Reset(&TimerCounter,0);
	xil_printf("TESTING UART\n\n");
	return 0;
}

void clear_LEDs()
{
	XGpio_DiscreteWrite(&LEDS,1,0x0000);
}
void set_LEDs()
{
	XGpio_DiscreteWrite(&LEDS,1,0xFFFF);
}

unsigned long start_timer()
{
	//unsigned long time0 = XTmrCtr_GetValue(&TimerCounter,0);
	unsigned long time0 = 0;
	XTmrCtr_Start(&TimerCounter,0); // Timer Counter has started
	return time0;
}

unsigned long stop_timer()
{
	unsigned long time1 = XTmrCtr_GetValue(&TimerCounter,0);
	XTmrCtr_Stop(&TimerCounter,0); // Timer Counter has stopped
	return time1;
}


void input_key()
{
	Xil_Out32(AES_BASEADDR,0x00000000);
	Xil_Out32(AES_BASEADDR+4,0x00000000);
	Xil_Out32(AES_BASEADDR+8,0x00000000);
	Xil_Out32(AES_BASEADDR+12,0x00000000);
}


void input_plaintext()
{
	Xil_Out32(INPUT_REG,0xFFFFFFFF);
	Xil_Out32(INPUT_REG+4,0xFFFFFFFF);
	Xil_Out32(INPUT_REG+8,0xFFFFFFFF);
	Xil_Out32(INPUT_REG+12,0xFFFFFFFF);
}

void start_encryption()
{
	Xil_Out32(LOAD_REG,0x00000001);
}

void set_load_low()
{
	Xil_Out32(LOAD_REG,0x00000000);
}

void read_output_cypher()
{
	 key_reg0 = Xil_In32(CYPHER_REG);
	 key_reg1 = Xil_In32(CYPHER_REG+4);
	 key_reg2 = Xil_In32(CYPHER_REG+8);
	 key_reg3 = Xil_In32(CYPHER_REG+12);
}


int main()
{
	init_system();
	clear_LEDs();

	uint32_t counter = 0;
	unsigned long time0;
	unsigned long time1;

	time0 = start_timer(); // start Timer

	XTmrCtr_Start(&TimerCounter,0); // Timer Counter has started

	// INPUT KEY REGISTER
	input_key();
	while(counter < 6250000)
	{
		input_plaintext();
		start_encryption();
		set_load_low();
		read_output_cypher();
		counter++;
	}

	time1 = stop_timer();
	set_LEDs();
	printf("Measured %d clock cycles == %f seconds \n",(time1-time0),((double)(time1-time0))/(TIMER_FREQ*1000000));

}
*/
