/*
 * I2C.h
 *
 *	Provides the I2C Init, Read, and Write Function
 *
 * Created on: May 24th, 2023
 *		Author: Jackie Huynh
 *
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "util.h"

/* List of Fill In Macros */

//Init Function
#define EN_I2C0_CLOCK       0x00001000  // Enable I2C0 Clock
#define EN_GPIOB_CLOCK      0x00000002  // Enable GPIOB Clock
#define I2C0_PINS           0x0C        // PB2,PB3 for I2C
#define I2C0_ALT_FUNC_MSK   0xFFFF00FF  // Mask to clear bits for PB2,PB3
#define I2C0_ALT_FUNC_SET   0x00003300  // Set PB2,PB3 to function 3 (I2C)
#define I2C0_SDA_PIN        0x08        // PB3 for SDA
#define I2C0_SCL_PIN        0x04        // PB2 for SCL
#define EN_I2C0_MASTER      0x00000010  // Enable I2C0 Master
#define I2C_MTPR_TPR_VALUE  0x07        // For 100kHz @ 16MHz = 7
#define I2C_MTPR_STD_SPEED  0x00        // Standard mode (100kHz)
//Transmit Function
#define I2C0_RW_PIN         0x00000001  // R/W bit for I2C transfer

//Burst Transmit Function
#define RUN_CMD             0x00000001  // Run command bit


/*
 *	-------------------I2C0_Init------------------
 *	Basic I2C Initialization function for master mode @ 100kHz
 *	Input: None
 *	Output: None
 */
void I2C0_Init(void);

/*
 *	-------------------I2C0_Receive------------------
 *	Polls to receive data from specified peripheral
 *	Input: Slave address & Slave Register Address
 *	Output: Returns 8-bit data that has been received
 */
uint8_t I2C0_Receive(uint8_t slave_addr, uint8_t slave_reg_addr);

/*
 *	-------------------I2C0_Transmit------------------
 *	Transmit a byte of data to specified peripheral
 *	Input: Slave address, Slave Register Address, Data to Transmit
 *	Output: Any Errors if detected, otherwise 0
 */
uint8_t I2C0_Transmit(uint8_t slave_addr, uint8_t slave_reg_addr, uint8_t data);

//Has Yet to be Implemented
/*
 *	----------------I2C0_Burst_Receive-----------------
 *	Polls to receive multiple bytes of data from specified
 *  peripheral by incrementing starting slave register address
 *	Input: Slave address, Slave Register Address, Data Buffer
 *	Output: None
 */
void I2C0_Burst_Receive(uint8_t slave_addr, uint8_t slave_reg_addr, uint8_t* data, uint32_t size);

/*
 *	----------------I2C0_Burst_Transmit-----------------
 *	Transmit multiple bytes of data to specified peripheral
 *  by incrementing starting slave address
 *	Input: Slave address, Slave Register Address, Data Buffer to transmit, Size of Transmit
 *	Output: None
 */
uint8_t I2C0_Burst_Transmit(uint8_t slave_addr, uint8_t slave_reg_addr, uint8_t* data, uint32_t size);

#endif //I2C_H_


