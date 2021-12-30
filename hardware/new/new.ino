#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Stepper.h>
#include <Servo.h>

#define P1_BTN 8
#define P2_BTN 9
#define ledPin 13
#define P1_MOTOR_A 2
#define P1_MOTOR_ENA 3
#define P1_MOTOR_B 4
#define P2_MOTOR_A 5
#define P2_MOTOR_ENA 6
#define P2_MOTOR_B 7
#define P1_REVERSE 10
#define P2_REVERSE 11
#define SERVO_PIN 12

int min = 3, sec = 10; // LCD 타이머 기본 시간
char ch = ':';

void LCD_TIME_OUT();
void LCD_PRINT_TIME(int sec, int min);

void setup() {
  Serial.begin(9600); // 시리얼 통신 시작

  lcd.begin();    // LCD의 크기를 설정한다.
  lcd.backlight();
  
  lcd.clear();    // LCD 화면 클리어
  lcd.setCursor(3, 0);
  lcd.print("WARMING UP");    // 게임 준비 화며
//  delay(9000);    // 9초 대기
  lcd.clear();

  randomSeed(analogRead(0));

}

void loop() {
  unsigned long currentMillis = millis();   // mills 함수사용할 때 현재 값 저장
  if (currentMillis - LCDpreviousMillis >= 1000) {    // LCD 타이머
    LCDpreviousMillis = currentMillis;
    if (sec == 0 && min == 0) {
      LCD_TIME_OUT();
      exit(0);    // 시간 초과시 프로그램 종료
    } else {
      if (sec == 0) {
        sec = 59;
        min = min - 1;
      }
      if (min == 0) {
        min = 0;
      }
      sec--;
      LCD_PRINT_TIME(sec, min);
    }
  }
}


void LCD_PRINT_TIME(int sec, int min) {
  lcd.setCursor(4, 0);
  lcd.print("Time");
  lcd.setCursor(9, 0);      // 1번째줄, 0번째열로 커서 이동
  lcd.print(min);  // 분
  lcd.print(ch);
  lcd.print(sec);  // 초
}

void LCD_TIME_OUT() {   // 타이머 종료시 LCD 에 출력
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("FINISHED");
}
