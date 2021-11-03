#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define P1_BTN 8

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

int min=2, sec=00;
int sig = 0;
int playSound = 0;
char ch = ':';

void setup()
{
  // initialize the LCD
  lcd.begin();
  lcd.backlight();
  
  Serial.begin(9600); // 시리얼 통신 시작

}

void loop()
{
  int p1_readValue = digitalRead(P1_BTN);
  
  if (p1_readValue == HIGH) {
    playSound += 1;
  }

  if (playSound == 1){
      Serial.print("SOUND");
      Serial.print("1");
      Serial.println();
  }
}

void LCD_PRINT_TIME() {
  if (sec == 0 && min == 0){
    lcd.setCursor(4, 0);      // 1번째줄, 0번째열로 커서 이동
    lcd.print("FINISHED");
  } else {
    if(sec == 0)
    { 
      sec = 59;
      min = min - 1;
    }
    if(min == 0)
    {
      min = 0;
    }
    lcd.setCursor(4, 0);      // 1번째줄, 0번째열로 커서 이동
    lcd.print("Time ");
    lcd.print(min);  // 분
    lcd.print(ch);
    lcd.print(sec);  // 초
    sec--;
    delay(1000);
    lcd.clear();
  }  
}

void LCD_PRINT_FAILE_PLAYER(int number) {  
    lcd.setCursor(4, 1);
    lcd.print(number);
    lcd.setCursor(6, 1);
    lcd.print("FAILED");
}
