#include <Wire.h>
#include "RTClib.h"
#include <DHT22.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
#include <stdio.h>
#define DHT22_PIN1 A1
#define DHT22_PIN2 A2
#define DHT22_PIN3 A3
DHT22 myDHT1(DHT22_PIN1);
DHT22 myDHT2(DHT22_PIN2);
DHT22 myDHT3(DHT22_PIN3);

RTC_DS1307 rtc;
int year0; int month0; int day0; int hour0; int minute0; int second0;

int temp1=0,humi1=0,temp2=0,humi2=0,temp3=0,humi3=0;

int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

int heater=2,water=1,fan=0,i=0,s=0;

int three,threehour,minutemode,minutes,m=0;

void setup()
{
 lcd.begin(16, 2);  
 Wire.begin();rtc.begin();
 pinMode(heater, OUTPUT); pinMode(water, OUTPUT); pinMode(fan, OUTPUT); 
 
 lcd.setCursor(0,0);
 lcd.print("RMUTL Electronic");delay(2000);
 lcd.setCursor(0,0);
 lcd.print("    Mushroom    ");
 delay(1000);
 
}
 
void loop()
{
  lcd.setCursor(0,0);
  lcd.print("    Mushroom    ");
  i=0;
  time();
  key();
  choose();
}
void choose()
{
  while(s==3)
  {
    s=1;
    while(s==1)
    {
      lcd.setCursor(0,1);lcd.print(">Start    Time  ");  
      lcd_key = read_LCD_buttons();   
      if( lcd_key==btnSELECT)
      {mode1();}
      if(lcd_key==btnRIGHT)
      {s=2;}
    }
    while(s==2)
    {                              
      lcd.setCursor(0,1);lcd.print(" Start   >Time  "); 
      lcd_key = read_LCD_buttons();   
      if(lcd_key==btnSELECT)
      {lcd.setCursor(0,1);lcd.print("      TIME     ");}
      if(lcd_key==btnLEFT)
      {s=1;}
    } 
  }
}
void mode1()
{      
  while(i=6)
  {
  three=0;threehour=0;minutemode=0;minutes=0;
  threehour = 0;
  minutemode = 5;
  lcd.setCursor(0,1);lcd.print("Mode 1 Disinfect");delay(2000);
  time();threehour = threehour+hour0;minutemode = minutemode+minute0;
  if(threehour < 23|| minutemode < 59){i=8;}
  if(threehour > 23 || minutemode > 59)
      {
        if(threehour > 23){ three = threehour - 24;} 
        if(minutemode > 59){ minutes = minutemode - 60; three = threehour + 1;}
        i=9;
      }
  
  while(i==8)
  {
    dht();time();
    lcd.setCursor(0,0);lcd.print("Mode 1 Disinfect");
    lcd.setCursor(0,1);lcd.print("Temp:");lcd.print(temp1);lcd.print("C  ");lcd.print(threehour);lcd.print(":");lcd.print(minutemode);lcd.print("m");
    
    if(temp1 <= 80 )
    {  digitalWrite(heater ,HIGH);  }
    if(temp1 >= 81 )
    {  digitalWrite(heater ,LOW);  }
    if(threehour == hour0 && minutemode == minute0)
    { digitalWrite(heater ,LOW);digitalWrite(water ,LOW);digitalWrite(fan ,LOW); 
      lcd.setCursor(0,1);lcd.print("  End Disinfect ");delay(2000);i=7;}
  }
  
  while(i==9)
  {
    dht();time();
    lcd.setCursor(0,0);lcd.print("Mode 1  Disinfect");
    lcd.setCursor(0,1);lcd.print("Temp:");lcd.print(temp1);lcd.print("C  ");lcd.print(three);lcd.print(":");lcd.print(minutes);lcd.print("m");
    
    if(temp1 <= 80 )
    {  digitalWrite(heater ,HIGH);  }
    if(temp1 >= 81 )
    {  digitalWrite(heater ,LOW);  }
    if(three == hour0 && minutes == minute0)
    { digitalWrite(heater ,LOW);digitalWrite(water ,LOW);digitalWrite(fan ,LOW); 
      lcd.setCursor(0,1);lcd.print(" End Disinfect  ");delay(2000);i=7;}
  }
  
  while(i==7)
  {
    dht();
    lcd.setCursor(0,0);lcd.print("Mode1  Disinfect");
    lcd.setCursor(0,1);lcd.print("   TEMP :");lcd.print(temp1);lcd.print("C    ");
    lcd_key = read_LCD_buttons(); 
    if(lcd_key==btnSELECT)
    {i=0;delay(2000);}
  }
  }
  
}

void mode2()
{
  lcd.setCursor(0,1);lcd.print(" Mode 2 Working ");delay(2000);i=0;
  /*if(humi1 != humi2)
  {
    i=1;Serial.println(" Begin !!!");delay(1000);
  }
  while(i == 1)
  {
    dht();
    if(temp3<= 30 )
    {digitalWrite(heater, HIGH);}
    if(temp3 > 31)
    {digitalWrite(heater, LOW);}
    if(humi3<=80)
    {digitalWrite(water, HIGH);}
    if(humi3>81)
    {digitalWrite(water, LOW);}
    if(temp3>31 || humi3 >81)
    {Serial.print(" END !!!");digitalWrite(heater, LOW);digitalWrite(water, LOW); i=0; }
  } 
  */
}
void time()
{
  DateTime now = rtc.now(); 
  year0 = now.year(); month0 = now.month();   day0 = now.day();
  hour0 = now.hour(); minute0 = now.minute(); second0 = now.second();
  DateTime future (now.unixtime() + 7 * 86400L + 30);
  
}
void dht()
{ 
  DHT22_ERROR_t errorCode;
  errorCode = myDHT1.readData();
  errorCode = myDHT2.readData();
  errorCode = myDHT3.readData();
  temp1 = myDHT1.getTemperatureC();humi1 = myDHT1.getHumidity();
  temp2 = myDHT2.getTemperatureC();humi2 = myDHT2.getHumidity();
  temp3 = myDHT3.getTemperatureC();humi3 = myDHT3.getHumidity();
}

int read_LCD_buttons()
{
 adc_key_in = analogRead(0);     
 if (adc_key_in > 1000) return btnNONE;
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 195)  return btnUP; 
 if (adc_key_in < 380)  return btnDOWN; 
 if (adc_key_in < 555)  return btnLEFT; 
 if (adc_key_in < 790)  return btnSELECT;   
 return btnNONE; 
}
void key()
{ 
    i=1;
    while(i==1)
    {
      lcd.setCursor(0,1);lcd.print(">Mode1    Mode2 ");  
      lcd_key = read_LCD_buttons();   
      if( lcd_key==btnSELECT)
      {s=3;choose();i=0;}
      if(lcd_key==btnRIGHT)
      {i=2;}
    }
    while(i==2)
    {
      lcd.setCursor(0,1);lcd.print(" Mode1   >Mode2 "); 
      lcd_key = read_LCD_buttons();   
      if(lcd_key==btnSELECT)
      {mode2();i=0;}
      if(lcd_key==btnLEFT)
      {i=1;}
    }
}
  
  /*
  if( lcd_key==btnRIGHT)
  {lcd.print("RIGHT ");}
  if( lcd_key==btnLEFT)
  {lcd.print("LEFT  ");}
  if( lcd_key==btnUP)
  {lcd.print("UP    ");}
  if( lcd_key==btnDOWN)
  {lcd.print("DOWN  ");}
  if( lcd_key==btnSELECT)
  {lcd.print("SELECT");}
  if( lcd_key==btnNONE)
  {lcd.print("NONE  ");}
  */



