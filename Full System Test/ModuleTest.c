/*
 * ModuleTest.c
 *
 *	Provides the testing functions all of individual peripheral testing
 *	and full system testing
 *
 * Created on: September 3rd, 2023
 *		Author: Jackie Huynh
 *
 */

#include "ModuleTest.h"
#include "TCS34727.h"
#include "MPU6050.h"
#include "UART0.h"
#include "Servo.h"
#include "LCD.h"
#include "I2C.h"
#include "util.h"
#include "ButtonLED.h"
#include "tm4c123gh6pm.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

/* Servo state*/
typedef enum {
    SERVO_STATE_0,
    SERVO_STATE_NEG_45,
    SERVO_STATE_0_AGAIN,
    SERVO_STATE_45,
    SERVO_STATE_0_AGAIN_2,
    SERVO_STATE_NEG_90,
    SERVO_STATE_0_AGAIN_3,
    SERVO_STATE_90,
    SERVO_STATE_DONE
} SERVO_STATE;

static SERVO_STATE servo_state = SERVO_STATE_0;
static char printBuf[100];
static char angleBuf[LCD_ROW_SIZE];
static char colorBuf[LCD_ROW_SIZE];
static char colorString[6];
const uint8_t color_wheel[] = {RED, GREEN, BLUE, YELLOW, CYAN, PURPLE, WHITE, DARK};
const int color_wheel_size = 8; // Number of colors in the color wheel
uint8_t ledColorIndex = 0;
unsigned volatile long currentColor = RED; // Current LED color
extern volatile uint8_t mode;
extern volatile bool firstRun;

/* RGB Color Struct Instance */
RGB_COLOR_HANDLE_t RGB_COLOR;

/* MPU6050 Struct Instance */
MPU6050_ACCEL_t Accel_Instance;
MPU6050_GYRO_t Gyro_Instance;
MPU6050_ANGLE_t Angle_Instance;

static void Test_Delay(void)
{
	LEDs ^= currentColor; // Toggle Red Led
	DELAY_1MS(500);		  // Delay for 0.5s using millisecond delay
}

static void Test_UART(void)
{
	int val = 123;
	double val2 = 3.14;
	sprintf(printBuf, "Test String: letters=%s, number=%d, float=%0.2f", "ABC", val, val2); //
	UART0_OutString(printBuf);
	UART0_OutCRLF();
	DELAY_1MS(1000); // 1 second delay
}

static void Test_I2C(void)
{

	// Command byte should be: Command bit (0x80) | Register address (0x12)
	uint8_t sensorId = I2C0_Receive(TCS34727_ADDR, TCS34727_CMD | TCS34727_ID_R_ADDR);

	sprintf(printBuf, " Sensor ID: 0x%x\r\n", sensorId);
	UART0_OutString(printBuf);

	DELAY_1MS(1000);
}

static void Test_MPU6050(void)
{
	/* Grab Accelerometer and Gyroscope Raw Data*/
	MPU6050_Get_Accel(&Accel_Instance);
	MPU6050_Get_Gyro(&Gyro_Instance);

	/* Process Raw Accelerometer and Gyroscope Data */
	MPU6050_Process_Accel(&Accel_Instance);
	MPU6050_Process_Gyro(&Gyro_Instance);

	/* Calculate Tilt Angle */
	MPU6050_Get_Angle(&Accel_Instance, &Gyro_Instance, &Angle_Instance);

	/* Format buffer to print data and angle */
	sprintf(printBuf, "Ax: %0.2f Ay: %0.2f Az: %0.2f", Accel_Instance.Ax, Accel_Instance.Ay, Accel_Instance.Az);
	UART0_OutString(printBuf);
	sprintf(printBuf, " Gx: %0.2f Gy: %0.2f Gz: %0.2f", Gyro_Instance.Gx, Gyro_Instance.Gy, Gyro_Instance.Gz);
	UART0_OutString(printBuf);
	UART0_OutCRLF();

	sprintf(printBuf, "X Angle: %0.2f Y Angle: %0.2f Z Angle: %0.2f", Angle_Instance.ArX, Angle_Instance.ArY, Angle_Instance.ArZ);
	UART0_OutString(printBuf);
	UART0_OutCRLF();

	DELAY_1MS(250);
}

static void Test_TCS34727(void)
{

	/* Grab Raw Color Data From Sensor */
	RGB_COLOR.R_RAW = TCS34727_GET_RAW_RED();
	RGB_COLOR.B_RAW = TCS34727_GET_RAW_BLUE();
	RGB_COLOR.G_RAW = TCS34727_GET_RAW_GREEN();
	RGB_COLOR.C_RAW = TCS34727_GET_RAW_CLEAR();

	/* Process Raw Color Data to RGB Value */
	TCS34727_GET_RGB(&RGB_COLOR);

	/* Change Onboard RGB LED Color to Detected Color */
	switch (Detect_Color(&RGB_COLOR))
	{
	case RED_DETECT:
		LEDs = RED;
		break;
	case GREEN_DETECT:
		LEDs = GREEN;
		break;
	case BLUE_DETECT:
		LEDs = BLUE;
		break;
	case NOTHING_DETECT:
		LEDs = DARK;
		break;
	}
	/* Format String to Print RGB value*/
	sprintf(printBuf, "R: %0.2f G: %0.2f B: %0.2f", (float)RGB_COLOR.R, (float)RGB_COLOR.G, (float)RGB_COLOR.B);
	UART0_OutString(printBuf);
	UART0_OutCRLF();

	DELAY_1MS(250);
}

static void Test_Servo(void)
{
    if (mode != SERVO_TEST) {
        // Reset state if not in servo test mode
        servo_state = SERVO_STATE_0;
        return;
    }

    switch (servo_state) {
        case SERVO_STATE_0:
            Drive_Servo(0);
            servo_state = SERVO_STATE_NEG_45;
            break;
        case SERVO_STATE_NEG_45:
            Drive_Servo(-45);
            servo_state = SERVO_STATE_0_AGAIN;
            break;
        case SERVO_STATE_0_AGAIN:
            Drive_Servo(0);
            servo_state = SERVO_STATE_45;
            break;
        case SERVO_STATE_45:
            Drive_Servo(45);
            servo_state = SERVO_STATE_0_AGAIN_2;
            break;
        case SERVO_STATE_0_AGAIN_2:
            Drive_Servo(0);
            servo_state = SERVO_STATE_NEG_90;
            break;
        case SERVO_STATE_NEG_90:
            Drive_Servo(-90);
            servo_state = SERVO_STATE_0_AGAIN_3;
            break;
        case SERVO_STATE_0_AGAIN_3:
            Drive_Servo(0);
            servo_state = SERVO_STATE_90;
            break;
        case SERVO_STATE_90:
            Drive_Servo(90);
            servo_state = SERVO_STATE_DONE;
            break;
        case SERVO_STATE_DONE:
            // Test completed, reset state
            servo_state = SERVO_STATE_0;
            break;
    }

    DELAY_1MS(1000); // 1 second delay between steps
}

static void Test_LCD(void) {
    const char* text = "Group 7";
    uint8_t text_length = strlen(text);
    uint8_t center = (LCD_ROW_SIZE - text_length) / 2;  // Calculate center position
    
    /* Print Name to LCD at Center Location */
    LCD_Clear();
    DELAY_1MS(30);
    LCD_Set_Cursor(ROW2, center);
    DELAY_1MS(30);
    LCD_Print_Str((uint8_t *)text);
    
    DELAY_1MS(2000);
}


static void Test_Full_System(void)
{
    // Step 1: Grab Accelerometer and Gyroscope Raw Data
    MPU6050_Get_Accel(&Accel_Instance);
    MPU6050_Get_Gyro(&Gyro_Instance);

    // Step 2: Process Raw Accelerometer and Gyroscope Data
    MPU6050_Process_Accel(&Accel_Instance);
    MPU6050_Process_Gyro(&Gyro_Instance);

    // Step 3: Calculate Tilt Angle
    MPU6050_Get_Angle(&Accel_Instance, &Gyro_Instance, &Angle_Instance);

    // Step 4: Drive Servo Accordingly to Tilt Angle on X-Axis
    Drive_Servo((int16_t)Angle_Instance.ArX);

    // Step 5: Grab Raw Color Data From Sensor
    RGB_COLOR.R_RAW = TCS34727_GET_RAW_RED();
    RGB_COLOR.G_RAW = TCS34727_GET_RAW_GREEN();
    RGB_COLOR.B_RAW = TCS34727_GET_RAW_BLUE();
    RGB_COLOR.C_RAW = TCS34727_GET_RAW_CLEAR();

    // Step 6: Process Raw Color Data to RGB Value
    TCS34727_GET_RGB(&RGB_COLOR);

    // Step 7: Change Onboard RGB LED Color to Detected Color
    int detectedColor = Detect_Color(&RGB_COLOR);
    switch (detectedColor)
    {
    case RED_DETECT:
        LEDs = RED;
        strcpy(colorString, "RED");
        break;
    case GREEN_DETECT:
        LEDs = GREEN;
        strcpy(colorString, "GREEN");
        break;
    case BLUE_DETECT:
        LEDs = BLUE;
        strcpy(colorString, "BLUE");
        break;
    case NOTHING_DETECT:
        LEDs = DARK;
        strcpy(colorString, "NA");
        break;
    }

    // Step 8: Format String to Print RGB value
    sprintf(printBuf, "R: %0.2f G: %0.2f B: %0.2f", (float)RGB_COLOR.R, (float)RGB_COLOR.G, (float)RGB_COLOR.B);
    UART0_OutString(printBuf);
    UART0_OutCRLF();

    // Step 9: Print String to Terminal through USB
    sprintf(printBuf, "Angle: %0.2f Color: %s", Angle_Instance.ArX, colorString);
    UART0_OutString(printBuf);
    UART0_OutCRLF();

    // Step 10: Update LCD With Current Angle and Color Detected
    sprintf(angleBuf, "Angle:%0.2f", Angle_Instance.ArX); // Format String to print angle to 2 Decimal Place
    sprintf(colorBuf, "Color:%s", colorString);           // Format String to print color detected

    LCD_Clear(); // Clear LCD
    DELAY_1MS(2); // Safety Delay of 2ms
    LCD_Set_Cursor(ROW1, 0); // Set Cursor to Row 1 Column 0
    LCD_Print_Str((uint8_t *)angleBuf); // Print angleBuf String on LCD
    DELAY_1MS(2); // Safety Delay of 2ms
    LCD_Set_Cursor(ROW2, 1); // Set Cursor to Row 2 Column 1
    LCD_Print_Str((uint8_t *)colorBuf); // Print colorBuf String on LCD

    DELAY_1MS(20);
}

void Module_Test(MODULE_TEST_NAME test)
{

	switch (test)
	{
	case DELAY_TEST:
		Test_Delay();
		break;

	case UART_TEST:
		Test_UART();
		break;

	case I2C_TEST:
		Test_I2C();
		break;

	case MPU6050_TEST:
		Test_MPU6050();
		break;

	case TCS34727_TEST:
		Test_TCS34727();
		break;

	case SERVO_TEST:
		Test_Servo();
		break;

	case LCD_TEST:
		Test_LCD();
		break;

	case FULL_SYSTEM_TEST:
		Test_Full_System();
		break;

	default:
		break;
	}
}

void GPIOPortF_Handler(void)
{
	DELAY_1MS(50); // 75ms debounce

	// SW 1 Button Press: Mode Switch
	if (SW1_FLAG)
	{
		// mode uart or led
		PORTF_FLAGS |= SW1_PIN; // Clear interrupt flag
		if (mode == DELAY_TEST)
		{
			GPIO_PORTF_IM_R &= ~SW2_PIN; // disarm interrupt on PF4
			mode = UART_TEST; // uart
			firstRun = false;
			
			LEDs = DARK;
		}
		else if (mode == UART_TEST)
		{
			mode = I2C_TEST; // i2c		
			firstRun = false;	
		}
		else if (mode == I2C_TEST)
		{
			mode = TCS34727_TEST; // color sensor
			firstRun = false;
			
		}
		else if (mode == TCS34727_TEST)
		{
			mode = MPU6050_TEST;	//gyro	
			firstRun = false;
		}
		else if (mode == MPU6050_TEST)
		{
			mode = SERVO_TEST; // servo
			PWM0_ENABLE_R |= EN_PWM0_FUNCTION; // start pwm for servo
			firstRun = false;
		}
		else if (mode == SERVO_TEST)
		{
			mode = LCD_TEST; // lcd
			firstRun = false;
			PWM0_ENABLE_R &= ~EN_PWM0_FUNCTION; // stop pwm for servo
		}
		else if (mode == LCD_TEST){
			mode = FULL_SYSTEM_TEST; // full system
			firstRun = false;
			PWM0_ENABLE_R |= EN_PWM0_FUNCTION; // start pwm for servo
		}		
		else if (mode == FULL_SYSTEM_TEST)
		{
			GPIO_PORTF_IM_R |= SW2_PIN; // arm interrupt on PF4
			PWM0_ENABLE_R &= ~EN_PWM0_FUNCTION; // stop pwm for servo
			mode = DELAY_TEST; // delay
			firstRun = false;
			
		}
	}

	// SW 2 Button Press: LED COLOR WHEEL
	if (SW2_FLAG)
	{
		if (mode == DELAY_TEST)
		{
			// mode uart or led
			ledColorIndex = (ledColorIndex + 1) % color_wheel_size;
			currentColor = color_wheel[ledColorIndex];
			LEDs = currentColor;
		}
		PORTF_FLAGS |= SW2_PIN; // Clear interrupt flag
	}
}
