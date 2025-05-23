/*
 * Servo.h
 *
 *	Provides functions to interact with a standard angular Servo Motor
 *
 * Created on: June 11th, 2023
 *		Author: Jackie Huynh
 *
 */

#ifndef SERVO_H_
#define SERVO_H_

#include <stdint.h>
#include "util.h"

// Use hardware PWM module 0, generator 0, channel 0, pin PB6.

/* List of macros */
#define EN_PWM0_GPIOB_CLOCK (0x00000002)
#define PWM0_PIN (0x00000040)
#define CLEAR_ALT_FUNCTION (0x0F000000)
#define PWM0_ALT_FUNCTION (0x04000000)
#define EN_PWM0_CLOCK (0x01)
#define EN_USE_PWM_DIV (0x00100000)
#define CLEAR_PWM_DIV (0x000E0000)
#define PWM0_DIV_VALUE (0x00040000)
#define PWM0_DEFAULT_CONFIG (0x00)
#define PWM0_GEN_CONFIG (0xC8) // 1100 1000
#define PWM0_COUNTER (40000)
#define PWM0_START (0x00000001)
#define EN_PWM0_FUNCTION (0x00000001)

/* 0.5ms (2.5%) - 2.5ms (12.5%) Duty Cycle */
#define SERVO_MIN_CNT (40000 * 0.025)
#define SERVO_MAX_CNT (40000 * 0.125)

/* Max Range of Either -90 to 90 or 0 to 180 */
#define SERVO_MIN_ANGLE (-90)
#define SERVO_MAX_ANGLE (90)

/*
 *	-------------------Servo_Init------------------
 *	Basic Servo Initialization function for PWM Generation
 *	Input: None
 *	Output: None
 */
void Servo_Init(void);

/*
 *	-------------------Drive_Servo------------------
 *	Drives the Servo Motor to a specified angle
 *	Input: Desired Angle
 *	Output: None
 */
void Drive_Servo(int16_t angle);

#endif