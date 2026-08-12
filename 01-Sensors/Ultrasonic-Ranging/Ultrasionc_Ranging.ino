/*
 * 模块：HC-SR04 超声波测距，屏幕显示
 * 功能：通过触发 TRIG 引脚发射声波，测量 ECHO 引脚高电平持续时间，换算为距离
 * 接线：TRIG → D3, ECHO → D2
 * 参考：Waveshare 示例（已重写并理解）
 */

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ----- 屏幕引脚定义
#define OLED_DC    8
#define OLED_RST   9
#define OLED_CS    10
// DOUT -> D11 (MOSI), CLK -> D13 (SCK) 由SPI库默认处理

// 屏幕尺寸：128x64
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// 创建一个屏幕对象
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, OLED_DC, OLED_RST, OLED_CS);

// ----- 超声波引脚定义
#define ECHO   2
#define TRIG   3

int Distance = 0;

int Distance_test() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  
  float Fdistance = pulseIn(ECHO, HIGH);
  Fdistance = Fdistance / 58;
  return (int)Fdistance;
}

void setup() {
  // 1. 初始化屏幕
  display.begin(SSD1306_SWITCHCAPVCC);  // 使用内部升压电路
  display.clearDisplay();
  display.setTextSize(1);               // 文字大小：1号
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Distance:");         // 固定标题
  display.display();

  // 2. 初始化超声波引脚
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);
}

void loop() {
  Distance = Distance_test();           // 测距

  // ----- 把距离显示到屏幕 -----
  display.setTextSize(2);               // 数字放大一点，更醒目
  display.setCursor(0, 20);             // 从第二行开始显示
  display.fillRect(0, 20, 128, 30, SSD1306_BLACK); // 清除上一轮的数字区域（避免叠影）
  display.setCursor(0, 20);
  display.print(Distance);
  display.println(" cm");
  display.display();                    // 真正把内容显示到屏幕上

  delay(250);
}