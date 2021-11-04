#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Stepper.h>
#include <Servo.h>

#define SPEAK_BTN 8
#define P1_BTN 2
#define P2_BTN 3
#define P3_BTN 4
#define P4_BTN 5
#define SERVO_PIN 9

Servo servo;

void LCD_PRINT_TIME();

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

int sig = 0;
int playSpeak = 0;
int angle = 0;

const int ledPin = 13;

char ch = ':';

volatile boolean ledState = true;

unsigned long previousMillis = 0;
unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;


void setup() {
  pinMode(ledPin, OUTPUT);
    
  Serial.begin(9600); // 시리얼 통신 시작
  
  lcd.begin();
  lcd.backlight();

  servo.attach(SERVO_PIN);
  servo.write(0); 
}

int min=2, sec=10;

void loop()
{
 
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 1000) {
    previousMillis = currentMillis;
    if (sec == 0 && min == 0){
      LCD_TIME_OUT();
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
  
  PLAYER_BTN_EVENT();
}

void PLAYER_BTN_EVENT() {
  int speakValue_p1 = 0;
  int speakValue_p1_fail = 0;
  
  int speakValue_p2 = 0;
  int speakValue_p2_fail = 0;
  
  int speakValue_p3 = 0;
  int speakValue_p3_fail = 0;
  
  int speakValue_p4 = 0;
  int speakValue_p4_fail = 0;
  
  unsigned long currentMillis = millis();
  unsigned long currentMillis1 = millis();
  unsigned long currentMillis2 = millis();

  if (currentMillis - previousMillis1 >= 4000) {
    previousMillis1 = currentMillis;

    speakValue_p1 = 1;
    speakValue_p2 = 1;
    speakValue_p3 = 1;
    speakValue_p4 = 1;
    
//    Serial.print("SPEAK");
    Serial.print("DDDDD");
    Serial.print("1");
    Serial.println();
    
    servo.write(180); 
    Serial.print("MOTOR");
    Serial.print(" angle180");
    Serial.println();
  }
  
//  if (currentMillis1 - previousMillis2 >= 5000) {
//    previousMillis2 = currentMillis1;
//    Serial.println();
//  }

  if (currentMillis2 - previousMillis3 >= 5000) {
    previousMillis3 = currentMillis2;
    Serial.print("MOTOR");
    servo.write(0); 
    Serial.print(" angle0");
    Serial.println();
  }
  
  int p1_readValue = digitalRead(P1_BTN);
  if (p1_readValue == HIGH&& speakValue_p1_fail == 1 ) {     
    Serial.print("player");
    Serial.println(1);
  }
  
  if (p1_readValue == HIGH && speakValue_p1 == 1) {
    Serial.println("FAILEP1");
    speakValue_p1_fail = 1;
    LCD_PRINT_FAILE_PLAYER(1);
  }

  int p2_readValue = digitalRead(P2_BTN);
  if (p2_readValue == HIGH&& speakValue_p2_fail == 1 ) {     
    Serial.print("player");
    Serial.println(2);
  }
  
  if (p2_readValue == HIGH && speakValue_p2 == 1) {
    Serial.println("FAILEP2");
    speakValue_p2_fail = 1;
    LCD_PRINT_FAILE_PLAYER(2);
  }

  int p3_readValue = digitalRead(P3_BTN);
  if (p3_readValue == HIGH&& speakValue_p3_fail == 1 ) {     
    Serial.print("player");
    Serial.println(3);
  }
  
  if (p3_readValue == HIGH && speakValue_p3 == 1) {
    Serial.println("FAILEP3");
    speakValue_p3_fail = 1;
    LCD_PRINT_FAILE_PLAYER(3);
  }

  int p4_readValue = digitalRead(P4_BTN);
  if (p4_readValue == HIGH&& speakValue_p4_fail == 1 ) {     
    Serial.print("player");
    Serial.println(4);
  }
  
  if (p4_readValue == HIGH && speakValue_p4 == 1) {
    Serial.println("FAILEP4");
    speakValue_p4_fail = 1;
    LCD_PRINT_FAILE_PLAYER(4);
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

void LCD_TIME_OUT() {
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("FINISHED");
}
    
void LCD_PRINT_FAILE_PLAYER(int number) {  
    lcd.setCursor(4, 1);
    lcd.print(number);
    lcd.setCursor(6, 1);
    lcd.print("FAILED");
}
