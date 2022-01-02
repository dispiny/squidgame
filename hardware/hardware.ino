#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Wire.h>
#include <Stepper.h>

#define SUCCESS_BTN_A 11
#define SUCCESS_BTN_B 10
#define FAILED_BTN_A 13
#define FAILED_BTN_B 12
#define LED1 9
#define LED2 8
#define LED3 7
#define LED4 6
#define LED5 5
#define SERVO_PIN 4

LiquidCrystal_I2C lcd(0x27, 16, 2);   // LCD 주소 설정
Servo servo;

int min = 3, sec = 10;
char ch = ':';

int new_success_a = 1;
int new_success_b = 1;
int new_failed_a = 1;
int new_failed_b = 1;
int old_success_a = 1;
int old_success_b = 1;
int old_failed_a = 1;
int old_failed_b = 1;

long rate;

unsigned long LCDpreviousMillis = 0;   // LCD의 상태가 업데이트된 시간을 기록할 변수
unsigned long ServopreviousMillis = 0;    // 서보모터의 상태가 업데이트된 시간을 기록할 변수

void setup() {
  Serial.begin(9600);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(FAILED_BTN_A, INPUT);
  pinMode(FAILED_BTN_B, INPUT);
  pinMode(SUCCESS_BTN_A, INPUT);
  pinMode(SUCCESS_BTN_B, INPUT);

  servo.attach(SERVO_PIN);
  servo.write(0);

  lcd.begin();
  lcd.backlight();

  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("WARMING UP");
  delay(9000);
  lcd.clear();

  randomSeed(analogRead(0));
}

void loop()
{  
  unsigned long currentMillis = millis();   // mills 함수사용할 때 현재 값 저장
  rate = random(2, 5);    // 영희 소리 배속 (랜덤)

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
  PLAYER_BTN_EVENT(rate);
}

void PLAYER_BTN_EVENT(int rate) {
  unsigned long currentMillis = millis();

  if (currentMillis - ServopreviousMillis >= 10000) {
    ServopreviousMillis = currentMillis;
    
    Serial.print("MOTOR");
    Serial.print(" angle0");
    Serial.println();
    servo.write(0);    
    
    if ((rate * 1000) == 4000) {
      delay(1250);  
    } else if ((rate * 1000) == 3000) {
      delay(1666);
    } else if ((rate * 1000) == 2000) {
      delay(2500);
    }

    Serial.print("SPEAK");
    Serial.print(rate);
    Serial.println();
    
    Serial.print("MOTOR");
    Serial.print(" angle180");
    Serial.println();
    servo.write(180);     // 서보모터 회전
  }
    
  new_success_a = digitalRead(SUCCESS_BTN_A);
  if (old_success_a == 0 && new_success_a == 1) {
    Serial.println("CSUCCESSP4");
  }
  old_success_a = new_success_a;
  
  new_success_b = digitalRead(SUCCESS_BTN_B);
  if (old_success_b == 0 && new_success_b == 1) {
    Serial.println("CSUCCESSP5");
  }
  old_success_b = new_success_b;

  new_failed_a = digitalRead(FAILED_BTN_A);
  if (new_failed_a == 1 && old_failed_a == 0) {
    Serial.println("FAILEP1");
    SUCCESS_LED();
    LCD_PRINT_FAILE_PLAYER(1);
  }
  old_failed_a = new_failed_a;

  new_failed_b = digitalRead(FAILED_BTN_B);
  if (old_failed_b == 0 && new_failed_b == 1) {
    Serial.println("FAILEP2");
    SUCCESS_LED();
    LCD_PRINT_FAILE_PLAYER(2);
  }
  old_failed_b = new_failed_b;
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

void LCD_PRINT_FAILE_PLAYER(int number) {  // 탈락한 플레이어 출력
  lcd.setCursor(4, 1);
  lcd.print(number);
  lcd.setCursor(6, 1);
  lcd.print("FAILED");
}

void SUCCESS_LED() {
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
  digitalWrite(LED5, HIGH);
  delay(100);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  delay(100);
}
