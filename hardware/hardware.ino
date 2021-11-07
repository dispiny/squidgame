#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Stepper.h>
#include <Servo.h>

#define SPEAK_BTN 8
#define P1_BTN 2
#define P2_BTN 3
#define P3_BTN 4
#define P4_BTN 5
#define P1_MOTOR 2                                          
#define P2_MOTOR 6
#define P3_MOTOR 10
#define P4_MOTOR 12
#define SERVO_PIN 9

Servo servo;

void LCD_PRINT_TIME();

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);


int min=2, sec=10;
int sig = 0;
int playSpeak = 0;
int angle = 0;

long rate;

const int ledPin = 11;

char ch = ':';

volatile boolean ledState = true;

unsigned long previousMillis = 0;
unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;


void setup() {
  pinMode(ledPin, OUTPUT);
  
  pinMode(P1_BTN, INPUT);
  pinMode(P2_BTN, INPUT);
  pinMode(P3_BTN, INPUT);
  pinMode(P4_BTN, INPUT);

  Serial.begin(9600); // 시리얼 통신 시작
  
  lcd.begin();
  lcd.backlight();

  servo.attach(SERVO_PIN);
  servo.write(0); 

  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("WARMING UP");
  delay(9000);
  lcd.clear();

  randomSeed(analogRead(0));
}


void loop()
{
 
  unsigned long currentMillis = millis();
  rate = random(2, 5);
  
  if (currentMillis - previousMillis >= 1000) {
    previousMillis = currentMillis;
    if (sec == 0 && min == 0){
      LCD_TIME_OUT();
      exit(0);
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
  PLAYER_BTN_EVENT(rate);
}

void SPEAK(int rate) {

    
}

void PLAYER_BTN_EVENT(int rate) {
  int speakValue;

  int speakValue_p1_fail = 0;
  int speakValue_p2_fail = 0;
  int speakValue_p3_fail = 0;
  int speakValue_p4_fail = 0;
  
  unsigned long currentMillis = millis();
  unsigned long currentMillis1 = millis();
  unsigned long currentMillis2 = millis();

  if (currentMillis - previousMillis1 >= 10000) {
    previousMillis1 = currentMillis;  

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
    
    servo.write(180); 
    Serial.print("MOTOR");
    Serial.print(" angle180");
    Serial.println();

  }
    
  int p1_readValue = digitalRead(P1_BTN);
  if (p1_readValue == HIGH && speakValue == 1) {
    Serial.println("FAILEP1");
    delay(500);
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
    digitalWrite(P1_MOTOR, LOW);
    speakValue_p1_fail = 1;
    LCD_PRINT_FAILE_PLAYER(1);
  } else {
    digitalWrite(P1_MOTOR, HIGH);
  }

  int p2_readValue = digitalRead(P2_BTN);
  if (p2_readValue == HIGH && speakValue == 1) {
    Serial.println("FAILEP2");
    delay(500);
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
    speakValue_p2_fail = 1;
    LCD_PRINT_FAILE_PLAYER(2);
  }
  
  int p3_readValue = digitalRead(P3_BTN);
    if (p3_readValue == HIGH && speakValue == 1) {
    Serial.println("FAILEP3");
    delay(500);
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
    speakValue_p3_fail = 1;
    LCD_PRINT_FAILE_PLAYER(3);
  }
  
  int p4_readValue = digitalRead(P4_BTN);
  if (p4_readValue == HIGH && speakValue == 1) {
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
