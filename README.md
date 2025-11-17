🕒 Digital Animated Clock Using ESP32 & OLED SSD1306

A simple and stylish digital animated clock built using ESP32, SSD1306 OLED display, and optional DHT11/DHT22 sensor for showing temperature & humidity.
Includes smooth animations, clean UI, and efficient code for embedded projects.

✨ Features

*Real-time digital clock display
*Smooth animations on SSD1306 OLED
*Runs on ESP32
*Uses I2C OLED (128×64) – SSD1306
*Easy to modify and extend for your own projects

🧰 Hardware Required

ESP32 Development Board

SSD1306 128×64 OLED Display (I2C)

Jumper wires

Breadboard

🔌 Wiring Diagram
ESP32 → SSD1306 OLED
OLED Pin	ESP32 Pin
VCC	3.3V
GND	GND
SCL	GPIO 22
SDA	GPIO 21

📦 Required Arduino Libraries

Install these libraries from Arduino IDE → Library Manager:

SSD1306 Display Libraries

Adafruit SSD1306

Adafruit GFX Library


Clone this repository:

git clone [https://github.com/yourusername/digital-animated-clock.git](https://github.com/electr0pi/Digital-Clock-OLED_WSM.git)

Uploading the Code

Open the project in Arduino IDE
Install required libraries
Select ESP32 Dev Module
Upload the code
