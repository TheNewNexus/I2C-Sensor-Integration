# I²C Sensor Integration

This embedded system integrates multiple I²C devices-a TCS34725 color sensor, MPU6050 gyroscope/accelerometer, and a 16x2 I²C LCD display-alongside a PWM-controlled servo and an RGB LED. The TCS34725 detects colors from a servo-mounted paper, and the detected color is mirrored on the RGB LED. The LCD provides real-time feedback of sensor readings and system status. The servo's position is dynamically adjusted via PWM, enabling the system to scan or present different colored areas.

---

## Key Components and Communication

- **MPU6050 (Gyroscope/Accelerometer)**
  - Communicates via I²C (0x68/0x69).
  - Provides orientation and acceleration data.

- **TCS34725 (Color Sensor)**
  - Communicates via I²C (0x29).
  - Reads RGB values from the paper.

- **16x2 LCD Display (I²C Interface)**
  - Communicates via I²C (commonly 0x27 or 0x3F).
  - Displays detected color values, servo position, and system information.
  - Reduces MCU pin usage to just SDA/SCL for display control[2][4][6].

- **Servo Motor**
  - Controlled via PWM.
  - Adjusts position to present various colors to the TCS34725.

- **RGB LED**
  - Driven by GPIO/PWM.
  - Mirrors the detected color from the TCS34725.

---

## System Workflow

1. **Servo Positioning:**  
   The microcontroller sets the servo position using PWM, presenting a specific colored area to the TCS34725.

2. **Color Detection:**  
   The TCS34725 reads color data from the paper and sends RGB values to the MCU via I²C.

3. **Display and Mirroring:**  
   - The MCU updates the RGB LED to match the detected color.
   - The LCD displays the current RGB values, servo angle, and optional gyro data for user feedback[2][4][6].

4. **Gyro Feedback (Optional):**  
   The MPU6050 provides orientation data, which can be displayed on the LCD or used for advanced features.

---

## Example I²C Device Connections

| Device      | I²C Address | Function                |
|-------------|-------------|-------------------------|
| MPU6050     | 0x68/0x69   | Orientation sensor      |
| TCS34725    | 0x29        | Color detection         |
| LCD 16x2    | 0x27/0x3F   | System status display   |

**All devices share the same SDA/SCL lines, each with a unique address[2][4][6].**

---

## Example LCD Integration (Pseudocode)

```c
#include "I2C.h"
#include "TCS34725.h"
#include "MPU6050.h"
#include "LCD.h"
#include "Servo.h"
#include "RGB_LED.h"

int main(void) {
    I2C_Init();
    TCS34725_Init();
    MPU6050_Init();
    LCD_Init();
    Servo_Init();
    RGB_LED_Init();

    while (1) {
        Servo_SetPosition(angle);
        TCS34725_ReadRGB(&r, &g, &b);
        RGB_LED_SetColor(r, g, b);
        LCD_SetCursor(0, 0);
        LCD_Printf("R:%d G:%d B:%d", r, g, b);
        LCD_SetCursor(0, 1);
        LCD_Printf("Servo:%d deg", angle);
        // Optionally display gyro data as well
    }
}
```

---

## Notes

- The I²C LCD display enables efficient use of MCU pins and provides a clear interface for real-time feedback[2][4][6].
- All I²C devices must have unique addresses; use an I²C scanner to confirm addresses if needed.
- The system can be expanded with additional I²C peripherals as required.

---

This architecture enables real-time color detection, mirroring on an RGB LED, and user feedback via an I²C LCD, all coordinated through efficient I²C communication.


