/*******************************************************************************
 * Project  : Mushroom                                                         *
 * Compiler : Arduino 1.0.2                                                    *
 * Board    : Arduino UNO                                                      *
 * Shield   : [DFROBOT] Arduino LCD Keypad Shield                              *
 * Module   : Temperature and Humidity Sensor Module (DHT22x4)                 *
 *          : RealTimeClock Module                                             *
 *          : SD card Module                                                   *
 *          :                                                                  *
 * Author   : Bavensky :3                                                      *
 * E-Mail   : Aphirak_Sang-ngenchai@hotmail.com                                *
 * Date     : 19/03/2014 [dd/mm/yyyy]                                          *
 *******************************************************************************/
/*******************************************************************************
 * เรียกใช้งานไลบรารี่ต่างๆ                                                          *
 *******************************************************************************/
#include <Wire.h>
#include "RTClib.h"
#include <DHT22.h>
#include <LiquidCrystal.h>
#include <stdio.h>
/*******************************************************************************
 * จอผลึกเหลว ใช้งานขาดิจิตอล 8,9,4,5,6และ7                                        *
 *******************************************************************************/
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
/*******************************************************************************
 * ตัวตรวจรู้อุณหภูมิและความชื้น ใช้งานขาอนาล็อก A1,A2และA3                             *
 *******************************************************************************/
#define DHT22_PIN1 A1
#define DHT22_PIN2 A2
#define DHT22_PIN3 A3
DHT22 myDHT1(DHT22_PIN1);
DHT22 myDHT2(DHT22_PIN2);
DHT22 myDHT3(DHT22_PIN3);
/*******************************************************************************
 * โมดูลฐานเวลาจริง ใช้งานขาอนาล็อก A4และA5                                         *
 *******************************************************************************/
RTC_DS1307 rtc;
/*******************************************************************************
 * กำหนดใช้งานคีย์แพตในโมดูล DFRobot                                              *
 *******************************************************************************/
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
/*******************************************************************************
 * กำหนดตำแปรต่างในการเก็บค่า                                                     *
 *******************************************************************************/
int year0; int month0; int day0; int hour0; int minute0; int second0; // ตัวแปรฐานเวลา
int temp1=0,humi1=0,temp2=0,humi2=0,temp3=0,humi3=0;                  // ตัวแปรเซ็นเซอร์
int heater=2,water=1,fan=0;                                           // ตัวแปรเอาต์พุต
int three,minutes,threehour=3,minutemode=0,i=0,s=0,t=0,m=0;           // ตัวแปรทั่วไป

void setup()
{
 lcd.begin(16, 2);  Wire.begin();  rtc.begin();                          // เริ่มการทำงาน                                    
 pinMode(heater, OUTPUT); pinMode(water, OUTPUT); pinMode(fan, OUTPUT);  // เอาต์พุต
/*******************************************************************************
* แสดงผลหน้าจอครั้งแรก                                                           *
*******************************************************************************/
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
  i=5;
  key();
}

void key()
{   
   while(i==5) 
   {
     i=1;
    while(i==1)
    {
      lcd.setCursor(0,1);lcd.print(">Mode1    Mode2 ");  
      lcd_key = read_LCD_buttons();   
      if( lcd_key==btnSELECT)
      {delay(200);s=5;i=0;}
      if(lcd_key==btnRIGHT)
      {delay(200);i=2;}
    }
    while(i==2)
    {
      lcd.setCursor(0,1);lcd.print(" Mode1   >Mode2 "); 
      lcd_key = read_LCD_buttons();   
      if(lcd_key==btnSELECT)
      {mode2();i=0;}
      if(lcd_key==btnLEFT)
      {i=5;}
    }
   }
   
  while(s==5)
  {
    s=1;
  while(s==1)
    {
      lcd.setCursor(0,1);lcd.print(">Start   SetTime");  
      lcd_key = read_LCD_buttons();   
      if( lcd_key==btnSELECT)
      {delay(200);mode1();}
      if(lcd_key==btnRIGHT)
      {delay(200);s=2;}
    }
    while(s==2)
    {                              
      lcd.setCursor(0,1);lcd.print(" Start  >SetTime"); 
      lcd_key = read_LCD_buttons();   
      if(lcd_key==btnSELECT)
      {delay(200);t=5;s=0;}
      if(lcd_key==btnLEFT)
      {delay(200);s=5;}
    }
  }
  
  while(t==5)
  {
    threehour=0;
    lcd.setCursor(0,0);lcd.print("Set Time        ");
    lcd.setCursor(0,1);lcd.print("  Time end: ");lcd.print(minutemode);lcd.print("m  ");
    lcd_key = read_LCD_buttons();
    if(lcd_key==btnUP)
    {
      delay(200);minutemode = minutemode+1;
    }
    if(lcd_key==btnDOWN)
    {
      delay(200);minutemode = minutemode-1;
    }
    if(lcd_key==btnSELECT)
    {delay(200);t=0;i=0;s=0;;}
  }    
}

void mode1()
{   
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
    {delay(200);s=0;i=0;delay(1500);}
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
/*******************************************************************************
* ลูปย่อยเริ่มการทำงานโมดูลฐานเวลาจริง                                                *
*******************************************************************************/
void time()
{
  DateTime now = rtc.now(); 
  year0 = now.year(); month0 = now.month();   day0 = now.day();
  hour0 = now.hour(); minute0 = now.minute(); second0 = now.second();
  DateTime future (now.unixtime() + 7 * 86400L + 30); 
}
/*******************************************************************************
* ลูปย่อยเริ่มการทำงานตัวตรวจรู้                                                      *
*******************************************************************************/
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
/*******************************************************************************
* ลูปย่อยเริ่มการทำงานปุ่มกดบนโมดูล DFRobot                                          *
*******************************************************************************/
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
/*******************************************************************************
* คำสั่งใช้งานปุ่มกดบนโมดูล DFRobot                                                 
* lcd_key = read_LCD_buttons();         // อ่านค่าแรงดันที่ขาอนาล็อก A0             
* lcd_key==btnRIGHT                     // ปุ่มขวา                               
* lcd_key==btnLEFT                      // ปุ่มซ้าย                               
* lcd_key==btnUP                        // ปุ่มบน                                
* lcd_key==btnDOWN                      // ปุ่มล่าง                                
* lcd_key==btnSELECT                    // ปุ่มเลือก                               
* lcd_key==btnNONE                      // ไม่มีการกดปุ่ม                            
********************************************************************************/




