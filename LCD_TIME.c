#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int min=2, sec=0;
char ch = ':';

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 1);
  lcd.print("001 Failed");
}

void loop() {    
  if (sec == 0 && min == 0){
    lcd.setCursor(4, 0);
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
    lcd.setCursor(4, 0);
    lcd.print("Time ");
    lcd.print(min);
    lcd.print(ch);
    lcd.print(sec);
    sec--;
    delay(1000);
  }
}
 