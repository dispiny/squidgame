#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Stepper.h>
#include <Servo.h>

#define P1_BTN 2
#define P2_BTN 3
#define P3_BTN 4
#define P4_BTN 5
#define P1_MOTOR 2                                          
#define P2_MOTOR 6
#define P3_MOTOR 10
#define P4_MOTOR 12
#define SERVO_PIN 9

Servo servo;      // Servo 클래스로 servo라는 Object 생성

void LCD_PRINT_TIME();

LiquidCrystal_I2C lcd(0x27, 16, 2);   // LCD 주소 설정


int min=3, sec=10;    // LCD 타이머 기본 시간
int playSpeak = 0;    // 영희 소리 신호 (0 재생 X, 1 재생 O) 
int angle = 0;          // 서보모터 각도 

long rate;

const int ledPin = 11;

char ch = ':';

////////////////////////////////////////
unsigned long LCDpreviousMillis = 0;   // LCD의 상태가 업데이트된 시간을 기록할 변수  
unsigned long ServopreviousMillis = 0;    // 서보모터의 상태가 업데이트된 시간을 기록할 변수  
////////////////////////////////////////

void setup() {
  pinMode(ledPin, OUTPUT);
  
  pinMode(P1_BTN, INPUT);     // 2번 핀 입력모드
  pinMode(P2_BTN, INPUT);     // 3번 핀 입력모드
  pinMode(P3_BTN, INPUT);     // 4번 핀 입력모드
  pinMode(P4_BTN, INPUT);     // 5번 핀 입력모드

  Serial.begin(9600); // 시리얼 통신 시작
  
  lcd.begin();    // LCD의 크기를 설정한다.
  lcd.backlight();

  servo.attach(SERVO_PIN);    // 서보모터 사용
  servo.write(0);   // 서보모터 위치 초기화

  lcd.clear();    // LCD 화면 클리어
  lcd.setCursor(3, 0);
  lcd.print("WARMING UP");    // 게임 준비 화며 
  delay(9000);    // 9초 대기 
  lcd.clear();

  randomSeed(analogRead(0));
}


void loop()
{
 
  unsigned long currentMillis = millis();   // ㅅmills 함수사용할 때 현재 값 저장
  rate = random(2, 5);    // 영희 소리 배속 (랜덤)
  
  if (currentMillis - LCDpreviousMillis >= 1000) {    // LCD 타이머 
    LCDpreviousMillis = currentMillis;
    if (sec == 0 && min == 0){
      LCD_TIME_OUT();
      exit(0);    // 시간 초과시 프로그램 종료
    } else {
      if(sec == 0) { 
        sec = 59;
        min = min - 1;
      }
      if(min == 0) {
        min = 0;
      }
      sec--;
      LCD_PRINT_TIME(sec, min);
    }
  }
  PLAYER_BTN_EVENT(rate);   // 플레이어의 이동 동작
}

void SPEAK(int rate) {

    
}

void PLAYER_BTN_EVENT(int rate) {
  int speakValue;

  int speakValue_p1_fail = 0;   // Player 1~4 생존여부
  int speakValue_p2_fail = 0;
  int speakValue_p3_fail = 0;
  int speakValue_p4_fail = 0;
  
  unsigned long currentMillis = millis();

  if (currentMillis - ServopreviousMillis >= 10000) {
    ServopreviousMillis = currentMillis;  

    speakValue = 1;
    
    Serial.print("MOTOR");
    servo.write(0); 
    Serial.print(" angle0");
    Serial.println();  
    
    Serial.print("SPEAK");
    Serial.print(rate);
    Serial.println();   

    if ((rate * 1000) == 4000) {
      delay(1250);  
    } else if ((rate * 1000) == 3000) {
      delay(1666);
    } else if ((rate * 1000) == 2000) {
      delay(2500);
    }
    
    servo.write(180);     // 서보모터 회전
    Serial.print("MOTOR");
    Serial.print(" angle180");
    Serial.println();

  }
    
  int p1_readValue = digitalRead(P1_BTN);
  if (p1_readValue == HIGH && speakValue == 1) { // 1번 선수 탈락시 동작 
    Serial.println("FAILEP1");    // Serial에 출력
    delay(500);
    digitalWrite(ledPin, HIGH);   // LED 켜고 1초뒤 종료
    delay(1000);
    digitalWrite(ledPin, LOW);
    digitalWrite(P1_MOTOR, LOW);
    speakValue_p1_fail = 1;
    LCD_PRINT_FAILE_PLAYER(1);
  } else {
    digitalWrite(P1_MOTOR, HIGH);
  }

  int p2_readValue = digitalRead(P2_BTN);
  if (p2_readValue == HIGH && speakValue == 1) {    // 2번 선수 탈락시 동작
    Serial.println("FAILEP2");
    delay(500);
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
    speakValue_p2_fail = 1;
    LCD_PRINT_FAILE_PLAYER(2);
  }
  
  int p3_readValue = digitalRead(P3_BTN);
    if (p3_readValue == HIGH && speakValue == 1) {    // 3번 선수 탈락시 동작
    Serial.println("FAILEP3");
    delay(500);
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
    speakValue_p3_fail = 1;
    LCD_PRINT_FAILE_PLAYER(3);
  }
  
  int p4_readValue = digitalRead(P4_BTN);
  if (p4_readValue == HIGH && speakValue == 1) {    // 4번 선수 탈락시 동작
    Serial.println("FAILEP4");
    delay(500);
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
    speakValue_p4_fail = 1;
    LCD_PRINT_FAILE_PLAYER(4);
  } 

  speakValue = 0;
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
