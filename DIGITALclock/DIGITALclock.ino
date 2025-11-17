#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <math.h>

// OLED Display Settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Wi-Fi Credentials
const char* ssid = "ESP32_cam";
const char* password = "esp32cam";

// NTP Client Setup
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 19800, 60000); // IST (UTC+5:30)

// Animation Variables
bool blinkState = true;  // Blinking colon effect
int scrollOffset = 0;    // Date scrolling effect
int ballY = 10, ballDir = 1; // Bouncing Ball
float angle = 0;         // Rotating Dash Angle
int waveOffset = 0;      // Wave movement

// Month Names Array
const char* months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", 
                         "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

// Function to Get Formatted Date
String getFormattedDate(int day, int month, int year) {
    return String(day) + " " + String(months[month - 1]) + " " + String(year);
}

// Function to Draw Rotating Dashes
void drawRotatingDashes(int x, int y, float angle) {
    for (int i = 0; i < 360; i += 45) {
        int x1 = x + cos((i + angle) * PI / 180) * 20;
        int y1 = y + sin((i + angle) * PI / 180) * 10;
        display.drawPixel(x1, y1, SSD1306_WHITE);
    }
}

// Function to Draw a Bouncing Ball
void drawBouncingBall() {
    display.fillCircle(115, ballY, 2, SSD1306_WHITE);
    ballY += ballDir;
    if (ballY >= 50 || ballY <= 10) ballDir *= -1;
}

// Function to Draw a Flowing Wave
void drawWaveLines() {
    for (int x = 0; x < SCREEN_WIDTH; x += 4) {
        int y = 40 + sin((x + waveOffset) * PI / 30) * 5;
        display.drawPixel(x, y, SSD1306_WHITE);
    }
    waveOffset += 2;
}

// Function to Display Animated Clock
void displayClock(int hours, int minutes, int seconds, int day, int month, int year) {
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);

    // Convert 24-hour format to 12-hour format
    String ampm = "AM";
    if (hours >= 12) ampm = "PM";
    if (hours > 12) hours -= 12;
    if (hours == 0) hours = 12;

    // Format Time String
    String timeStr = (hours < 10 ? " " : "") + String(hours) + (blinkState ? ":" : " ") +
                     (minutes < 10 ? "0" : "") + String(minutes);

    // Display Time (Large Font)
    display.setTextSize(3);
    display.setCursor(10, 10);
    display.print(timeStr);

    // Display Seconds in a Smaller Font
    display.setTextSize(1);
    display.setCursor(100, 20);
    display.print((seconds < 10 ? "0" : "") + String(seconds));

    // Display AM/PM
    display.setTextSize(1);
    display.setCursor(110, 40);
    display.print(ampm);

    // Create Date Scrolling Effect
    String dateStr = getFormattedDate(day, month, year);
    display.setTextSize(1);
    display.setCursor(10 - scrollOffset, 50);
    display.print(dateStr);

    // Smooth scrolling effect
    scrollOffset++;
    if (scrollOffset > 40) scrollOffset = 0;

    // Animated Graphics
    drawBouncingBall();
    drawRotatingDashes(64, 50, angle);
    drawWaveLines();

    // Update animation angles
    angle += 5;
    if (angle >= 360) angle = 0;

    // Refresh Display
    display.display();
}

// Setup Function
void setup() {
    Serial.begin(115200);

    // Initialize OLED Display
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }
    
    display.display();
    delay(2000);

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi");

    // Initialize NTP Client
    timeClient.begin();
    timeClient.setTimeOffset(19800);
    timeClient.update();
}

// Loop Function
void loop() {
    timeClient.update();

    int hours = timeClient.getHours();
    int minutes = timeClient.getMinutes();
    int seconds = timeClient.getSeconds();

    // Fake date for now (NTP does not provide date directly)
    int day = 18;
    int month = 3;
    int year = 2025;

    // Toggle blinking colon every second
    blinkState = !blinkState;

    // Display Time and Animated Graphics
    displayClock(hours, minutes, seconds, day, month, year);

    delay(50);
}
