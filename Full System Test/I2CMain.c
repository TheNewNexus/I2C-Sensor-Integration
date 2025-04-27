/*
 * I2CTestMain.c
 *
 *	Test the basic functionality of I2C by reading and writing to the 
 *	TCS34727 RGB Sensor and MPU6050 6-dof IMU, as well as controlling
 *	a Servo Motor and a 16x2 LCD 
 *
 * Created on: May 24th, 2023
 *		Author: Jackie Huynh
 *
 */
 
#include "tm4c123gh6pm.h"
#include "I2C.h"
#include "UART0.h"
#include "TCS34727.h"
#include "MPU6050.h"
#include "ButtonLED.h"
#include "util.h"
#include "Servo.h"
#include "LCD.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "ModuleTest.h"

/* List of Predefined Macros for individual Peripheral Testing */
#define DELAY
#define UART
#define I2C
#define TCS34727
#define MPU6050
#define SERVO
#define LCD
#define FULL_SYSTEM

volatile uint8_t mode = FULL_SYSTEM_TEST;
bool firstRun = false;

int main(void){
	
	/* Peripheral Initialization */
	UART0_Init();
	LED_Init();
	BTN_Init();
	
	#if defined(DELAY) || defined(TCS34727) || defined(MPU6050) || defined(LCD) || defined(FULL_SYSTEM)	
	WTIMER0_Init();
	#endif
	
	#if defined (I2C) || defined(TCS34727) || defined(MPU6050) || defined(LCD) || defined(FULL_SYSTEM)
	I2C0_Init();
	#endif
	
	#if defined(TCS34727) || defined(FULL_SYSTEM)
	/* Color Sensor Initialization */
	TCS34727_Init();
	#endif
	
	#if defined(MPU6050) || defined(FULL_SYSTEM)
	/* MPU6050 Initialization */
	MPU6050_Init();
	#endif
	
	#if defined(SERVO) || defined(FULL_SYSTEM)
	/* Servo Initialization */
	Servo_Init();
	#endif
	
	#if defined(LCD) || defined(FULL_SYSTEM)
	/* LCD Initialization */
	LCD_Init();
	#endif
	
	UART0_OutCRLF();
	while(1){		
		
		if(mode == DELAY_TEST){
		#ifdef DELAY
		if(!firstRun){
		UART0_OutString("\nEnter Modeing 1: DELAY TEST	\r\n");
		firstRun = true;
		}		
		Module_Test(DELAY_TEST);		
		#endif	
		}
		
		if(mode == UART_TEST){
		#ifdef UART
		if(!firstRun){
		UART0_OutString("\nEntering Mode 2: UART TEST	\r\n");
		firstRun = true;
		}
		Module_Test(UART_TEST);
		#endif
		}
			
		if(mode == I2C_TEST){
		#ifdef I2C
		if(!firstRun){
		UART0_OutString("\nEntering Mode 3: I2C TEST	\r\n");
		firstRun = true;
		}
		Module_Test(I2C_TEST);
		#endif
		}
		
		if(mode == MPU6050_TEST){
		#ifdef MPU6050
		if(!firstRun){
		UART0_OutString("\nEntering Mode 5: GYRO TEST	\r\n");
		firstRun = true;
		}
		Module_Test(MPU6050_TEST);
		#endif
		}
		
		if(mode == TCS34727_TEST){
		#ifdef TCS34727
		if(!firstRun){
		UART0_OutString("\nEntering Mode 4: COLOR SENSOR TEST	\r\n");
		firstRun = true;
		}
		Module_Test(TCS34727_TEST);
		#endif
		}
			
		if(mode == SERVO_TEST){
		#ifdef SERVO
		if(!firstRun){
		UART0_OutString("\nEntering Mode 6: SERVO TEST \r\n");
		firstRun = true;
		}
		Module_Test(SERVO_TEST);
		#endif
		}
		
		if(mode == LCD_TEST){
		#ifdef LCD
		if(!firstRun){
		UART0_OutString("\nEntering Mode 7: LCD TEST \r\n");
		firstRun = true;
		}
		Module_Test(LCD_TEST);
		#endif
		}
		
		if(mode == FULL_SYSTEM_TEST){
		#ifdef FULL_SYSTEM
		if(!firstRun){
		UART0_OutString("\nEntering Mode 8: FULL SYSTEM TEST \r\n");
		firstRun = true;
		}
		Module_Test(FULL_SYSTEM_TEST);
		#endif
		}
	}
	
	return 0;
}
