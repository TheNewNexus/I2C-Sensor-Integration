/*
 * MPU6050.h
 *
 *	Provides functions to interact with 6-dof MPU6050
 *	accelerometer and gyroscope
 *
 *	Datasheet Link: https://cdn.sparkfun.com/datasheets/Sensors/Accelerometers/RM-MPU-6000A.pdf
 *
 * Created on: May 24th, 2023
 *		Author: Jackie Huynh
 *
 */
#ifndef MPU6050_H_ // Include guard to prevent multiple inclusions
#define MPU6050_H_

#include <stdint.h> // Standard integer types
#include "util.h"	// Utility functions and macros

// NOTE: There will be no self-test regs

/*
IMPORTANT: BEFORE FILLING MACROS READ THE COMMENT BELOW

NOT ALL MACROS NEED TO BE FILLED OUT. REFERENCE TCS34727.c
TO FIGURE OUT WHAT'S NECESSARY (Filling it all out will not
incur any penalties but will be a waste of time)
*/

/* List of MPU6050 Register Macros */

// #define USE_HIGH // Uncomment if AD0 is pulled high

/**********************************************************/
#ifndef USE_HIGH
#define MPU6050_ADDR_AD0_LOW (0x68) // I2C address when AD0 is low
#else
#define MPU6050_ADDR_AD0_HIGH (0x69) // I2C address when AD0 is high
#endif

/*************Sampling Rate Register*************/
#define SMPLRT_DIV (0x19)	// Sample rate divider register address
#define SMPLRT_DIV_8 (0x80) // Sample rate divider value for 8

/****************Config Register****************/
#define CONFIG (0x1A)		 // Configuration register address
#define CONFIG_DFPL_0 (0x01) // Digital low pass filter configuration

/*************Gyro Config Register*************/
#define GYRO_CONFIG (0x1B)					 // Gyroscope configuration register address
#define GYRO_FS_SEL_0 (0x08)				 // Gyroscope full-scale range selection
#define GYRO_FS_SEL_1 (GYRO_FS_SEL_0 + 0x08) // Gyroscope full-scale range selection
#define GYRO_FS_SEL_2 (GYRO_FS_SEL_0 + 0x10) // Gyroscope full-scale range selection
#define GYRO_FS_SEL_3 (GYRO_FS_SEL_0 + 0x18) // Gyroscope full-scale range selection

/*************Accel Config Register************/
#define ACCEL_CONFIG (0x1C)						 // Accelerometer configuration register address
#define ACCEL_AFS_SEL_0 (0x08)					 // Accelerometer full-scale range selection
#define ACCEL_AFS_SEL_1 (ACCEL_AFS_SEL_0 + 0x08) // Accelerometer full-scale range selection
#define ACCEL_AFS_SEL_2 (ACCEL_AFS_SEL_0 + 0x10) // Accelerometer full-scale range selection
#define ACCEL_AFS_SEL_3 (ACCEL_AFS_SEL_0 + 0x18) // Accelerometer full-scale range selection
/**********************************************************/

#define MOT_THR (0x1F)		  // Motion threshold register address
#define FIFO_EN (0x23)		  // FIFO enable register address
#define I2C_MST_CTRL (0x24)	  // I2C master control register address
#define I2C_SLV0_ADDR (0x25)  // I2C slave 0 address register
#define I2C_SLV0_REG (0x26)	  // I2C slave 0 register address
#define I2C_SLV0_CTRL (0x27)  // I2C slave 0 control register
#define I2C_SLV1_ADDR (0x28)  // I2C slave 1 address register
#define I2C_SLV1_REG (0x29)	  // I2C slave 1 register address
#define I2C_SLV1_CTRL (0x2A)  // I2C slave 1 control register
#define I2C_SLV2_ADDR (0x2B)  // I2C slave 2 address register
#define I2C_SLV2_REG (0x2C)	  // I2C slave 2 register address
#define I2C_SLV2_CTRL (0x2D)  // I2C slave 2 control register
#define I2C_SLV3_ADDR (0x2E)  // I2C slave 3 address register
#define I2C_SLV3_REG (0x2F)	  // I2C slave 3 register address
#define I2C_SLV3_CTRL (0x30)  // I2C slave 3 control register
#define I2C_SLV4_ADDR (0x31)  // I2C slave 4 address register
#define I2C_SLV4_REG (0x32)	  // I2C slave 4 register address
#define I2C_SLV4_DO (0x33)	  // I2C slave 4 data out register
#define I2C_SLV4_CTRL (0x34)  // I2C slave 4 control register
#define I2C_SLV4_DI (0x35)	  // I2C slave 4 data in register
#define I2C_MST_STATUS (0x36) // I2C master status register
#define INT_PIN_CFG (0x37)	  // Interrupt pin configuration register
#define INT_ENABLE (0x38)	  // Interrupt enable register
#define INT_STATUS (0x3A)	  // Interrupt status register

/**********************************************************/
#define ACCEL_XOUT_H (0x3B) // Accelerometer X-axis high byte
#define ACCEL_XOUT_L (0x3C) // Accelerometer X-axis low byte
#define ACCEL_YOUT_H (0x3D) // Accelerometer Y-axis high byte
#define ACCEL_YOUT_L (0x3E) // Accelerometer Y-axis low byte
#define ACCEL_ZOUT_H (0x3F) // Accelerometer Z-axis high byte
#define ACCEL_ZOUT_L (0x40) // Accelerometer Z-axis low byte
#define GYRO_XOUT_H (0x43)	// Gyroscope X-axis high byte
#define GYRO_XOUT_L (0x44)	// Gyroscope X-axis low byte
#define GYRO_YOUT_H (0x45)	// Gyroscope Y-axis high byte
#define GYRO_YOUT_L (0x46)	// Gyroscope Y-axis low byte
#define GYRO_ZOUT_H (0x47)	// Gyroscope Z-axis high byte
#define GYRO_ZOUT_L (0x48)	// Gyroscope Z-axis low byte
/**********************************************************/

#define EXT_SENS_DATA_00 (0x49)	  // External sensor data register 00
#define EXT_SENS_DATA_01 (0x4A)	  // External sensor data register 01
#define EXT_SENS_DATA_02 (0x4B)	  // External sensor data register 02
#define EXT_SENS_DATA_03 (0x4C)	  // External sensor data register 03
#define EXT_SENS_DATA_04 (0x4D)	  // External sensor data register 04
#define EXT_SENS_DATA_05 (0x4E)	  // External sensor data register 05
#define EXT_SENS_DATA_06 (0x4F)	  // External sensor data register 06
#define EXT_SENS_DATA_07 (0x50)	  // External sensor data register 07
#define EXT_SENS_DATA_08 (0x51)	  // External sensor data register 08
#define EXT_SENS_DATA_09 (0x52)	  // External sensor data register 09
#define EXT_SENS_DATA_10 (0x53)	  // External sensor data register 10
#define EXT_SENS_DATA_11 (0x54)	  // External sensor data register 11
#define EXT_SENS_DATA_12 (0x55)	  // External sensor data register 12
#define EXT_SENS_DATA_13 (0x56)	  // External sensor data register 13
#define EXT_SENS_DATA_14 (0x57)	  // External sensor data register 14
#define EXT_SENS_DATA_15 (0x58)	  // External sensor data register 15
#define EXT_SENS_DATA_16 (0x59)	  // External sensor data register 16
#define EXT_SENS_DATA_17 (0x5A)	  // External sensor data register 17
#define EXT_SENS_DATA_18 (0x5B)	  // External sensor data register 18
#define EXT_SENS_DATA_19 (0x5C)	  // External sensor data register 19
#define EXT_SENS_DATA_20 (0x5D)	  // External sensor data register 20
#define EXT_SENS_DATA_21 (0x5E)	  // External sensor data register 21
#define EXT_SENS_DATA_22 (0x5F)	  // External sensor data register 22
#define EXT_SENS_DATA_23 (0x60)	  // External sensor data register 23
#define I2C_SLV0_DO (0x63)		  // I2C slave 0 data out register
#define I2C_SLV1_DO (0x64)		  // I2C slave 1 data out register
#define I2C_SLV2_DO (0x65)		  // I2C slave 2 data out register
#define I2C_SLV3_DO (0x66)		  // I2C slave 3 data out register
#define I2C_MST_DELAY_CTRL (0x67) // I2C master delay control register
#define SIGNAL_PATH_RESET (0x68)  // Signal path reset register
#define MOT_DETECT_CTRL (0x69)	  // Motion detection control register
#define USER_CTRL (0x6A)		  // User control register

/**********Power Management & ID Register**********/
#define PWR_MGMT_1 (0x6B)			// Power management 1 register
#define PWR_CLK_SEL_INTERNAL (0x01) // Clock source selection: internal
#define PWR_DEVICE_RESET (0x80)		// Device reset bit
#define WHO_AM_I (0x75)				// Who am I register (device ID)
/**********************************************************/

#define PWR_MGMT_2 (0x6C)	 // Power management 2 register
#define PWR_2_STBY_ZG (0x01) // Standby mode for Z-axis gyroscope
#define PWR_2_STBY_YG (0x02) // Standby mode for Y-axis gyroscope
#define PWR_2_STBY_XG (0x04) // Standby mode for X-axis gyroscope
#define PWR_2_STBY_ZA (0x08) // Standby mode for Z-axis accelerometer
#define PWR_2_STBY_YA (0x10) // Standby mode for Y-axis accelerometer
#define PWR_2_STBY_XA (0x20) // Standby mode for X-axis accelerometer
#define PWR_2_WAKE_0 (0x00)	 // Wake-up frequency: 1.25 Hz
#define PWR_2_WAKE_1 (0x40)	 // Wake-up frequency: 5 Hz
#define PWR_2_WAKE_2 (0x80)	 // Wake-up frequency: 20 Hz
#define PWR_2_WAKE_3 (0xC0)	 // Wake-up frequency: 40 Hz

#define FIFO_COUNTH (0x72) // FIFO count high byte
#define FIFO_COUNTL (0x73) // FIFO count low byte
#define FIFO_R_W (0x74)	   // FIFO read/write register

#define RAD_TO_DEGREE_CONV (180.0 / 3.1415) // Conversion factor from radians to degrees

/* Data Struct to store Accelerometer Data*/
typedef struct
{
	int16_t Ax_RAW; // Raw accelerometer data for X-axis
	int16_t Ay_RAW; // Raw accelerometer data for Y-axis
	int16_t Az_RAW; // Raw accelerometer data for Z-axis

	float Ax; // Processed accelerometer data for X-axis
	float Ay; // Processed accelerometer data for Y-axis
	float Az; // Processed accelerometer data for Z-axis

} MPU6050_ACCEL_t;

/* Data Struct to store Gyroscope Data*/
typedef struct
{
	int16_t Gx_RAW; // Raw gyroscope data for X-axis
	int16_t Gy_RAW; // Raw gyroscope data for Y-axis
	int16_t Gz_RAW; // Raw gyroscope data for Z-axis

	float Gx; // Processed gyroscope data for X-axis
	float Gy; // Processed gyroscope data for Y-axis
	float Gz; // Processed gyroscope data for Z-axis

} MPU6050_GYRO_t;

/* Data Struct to store Tilt Angle Data*/
typedef struct
{
	float ArX; // Tilt angle for X-axis
	float ArY; // Tilt angle for Y-axis
	float ArZ; // Tilt angle for Z-axis
} MPU6050_ANGLE_t;

/*
 *	-------------------MPU6050_Init---------------------
 *	Basic Initialization Function for MPU6050 @ default settings
 *	Input: none
 * 	Output: none
 */
void MPU6050_Init(void);

/*
 *	-----------------MPU6050_Get_Accel------------------
 *	Receive Raw Accelerometer Data and store it in the user struct
 *	Input: MPU6050 Accel User Instance Struct
 * 	Output: none
 */
void MPU6050_Get_Accel(MPU6050_ACCEL_t *Accel_Instance);

/*
 *	-----------------MPU6050_Get_Gyro-------------------
 *	Receive Raw Gyroscope Data and store it in the user struct
 *	Input: MPU6050 Gyro User Instance Struct
 * 	Output: none
 */
void MPU6050_Get_Gyro(MPU6050_GYRO_t *Gyro_Instance);

/*
 *	---------------MPU6050_Process_Accel----------------
 *	Process Raw Accelerometer Data into usable data and store
 *	it in the user struct
 *	Input: MPU6050 Accel User Instance Struct
 * 	Output: none
 */
void MPU6050_Process_Accel(MPU6050_ACCEL_t *Accel_Instance);

/*
 *	---------------MPU6050_Process_Gyro----------------
 *	Process Raw Gyroscope Data into usable data and store it in
 *	the user struct
 *	Input: MPU6050 Gyro User Instance Struct
 * 	Output: none
 */
void MPU6050_Process_Gyro(MPU6050_GYRO_t *Gyro_Instance);

/*
 *	-----------------MPU6050_Get_Angle-----------------
 *	Calculate Tilt Angle using processed Accelerometer and
 *	Gyroscope data and store it in the user angle struct
 *	Input: MPU6050 Angle User Instance Struct
 * 	Output: none
 */
void MPU6050_Get_Angle(MPU6050_ACCEL_t *Accel_Instance, MPU6050_GYRO_t *Gyro_Instance, MPU6050_ANGLE_t *Angle_Instance);

/* Used for Debugging Purposes */
uint8_t MPU6050_Read_Reg(uint8_t reg); // Read a register value for debugging

#endif // End of include guard