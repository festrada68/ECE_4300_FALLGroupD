/*
 * main.cpp
 *
 *  Created on: Nov 10, 2020
 *      Authors: Jeffrey Hymas, John Wilson, Raymond Banda, Kyle Gerfen, Freddy Estrada
 */

#include "Xparameters.h"
#include "xil_printf.h"
#include "xil_io.h"
#include "xbasic_types.h"
#include <stdio.h>
#include "xtmrctr.h" // header file for AXI timer
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



int main()
{
	XGpio LEDS;

	// initialize the GPIO
	XGpio_Initialize(&LEDS,XPAR_GPIO_0_DEVICE_ID); // initialize the GPIO
	XGpio_SetDataDirection(&LEDS,1,0); // set the GPIO as input, since we are using the DIP switches from board
	XGpio_DiscreteWrite(&LEDS,1,0xFFFF);


	uint32_t key_reg0;
	uint32_t key_reg1 ;
	uint32_t key_reg2 ;
	uint32_t key_reg3;

// Initializing the AXI Timer
	 XTmrCtr TimerCounter;
	    int Status = XTmrCtr_Initialize(&TimerCounter,TMRCTR_DEVICE_ID);
	    if(Status != XST_SUCCESS)
	    {
	    	return XST_FAILURE;
	    }

	    //setting up the timer
	    XTmrCtr_SetOptions(&TimerCounter,0,XTC_AUTO_RELOAD_OPTION);
	    XTmrCtr_Reset(&TimerCounter,0);

	xil_printf("Starting Encryption...\n\n");
	printf("Input Key: 0x00000000000000000000000000000000\n");
	printf("Input Plain-Text: 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF\n");
	//Expected output 0x3f5b8cc9ea855a0afa7347d23e8d664e
	printf("Expected Output: 0x3f5b8cc9ea855a0afa7347d23e8d664e\n");

	uint32_t counter = 0;
	XGpio_DiscreteWrite(&LEDS,1,0x0000);

	unsigned long time0 = XTmrCtr_GetValue(&TimerCounter,0); // start Timer

	XTmrCtr_Start(&TimerCounter,0); // Timer Counter has started

	// INPUT KEY REGISTER
	Xil_Out32(AES_BASEADDR,0x00000000);
	Xil_Out32(AES_BASEADDR+4,0x00000000);
	Xil_Out32(AES_BASEADDR+8,0x00000000);
	Xil_Out32(AES_BASEADDR+12,0x00000000);
	//178 cycles
// *** 1 instruction



//while(counter < 6250000) // 100 MB
//{

// INPUT PLAIN TEXT REGISTER
	Xil_Out32(INPUT_REG,0xFFFFFFFF);
	Xil_Out32(INPUT_REG+4,0xFFFFFFFF);
	Xil_Out32(INPUT_REG+8,0xFFFFFFFF);
	Xil_Out32(INPUT_REG+12,0xFFFFFFFF);
// ***** 1 instruction // 136 cycles



//Start Decrypting....
// LOAD
	Xil_Out32(LOAD_REG,0x00000001);
// **** 1 instruction


//Set Load LOW
	Xil_Out32(LOAD_REG,0x00000000);
// **** 1 instruction


//Get the encrypted 128-bit cypher text

	 key_reg0 = Xil_In32(CYPHER_REG);
	 key_reg1 = Xil_In32(CYPHER_REG+4);
	 key_reg2 = Xil_In32(CYPHER_REG+8);
	 key_reg3 = Xil_In32(CYPHER_REG+12);
// *** 1 instruction

//	counter++;
//}
	 //unsigned long time1 = XTmrCtr_GetValue(&TimerCounter,0);
	unsigned long time1 = XTmrCtr_GetValue(&TimerCounter,0);
	XGpio_DiscreteWrite(&LEDS,1,0xFFFF);

	printf("Encyrpted Output: 0x%x%x%x%x\n",key_reg3,key_reg2,key_reg1,key_reg0);
	printf("Encryption Done.\nMeasured %d clock cycles.\nExecution time: %f seconds. \n",(time1-time0),((double)(time1-time0))/(TIMER_FREQ*1000000));

}

