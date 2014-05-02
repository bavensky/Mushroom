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
  #include <SD.h>
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
  /******************************************************************************
   * โมดูลบันทึกค่าลง SDCard + IC CD4050                                            *
   * SDCard         Arduino          CD4050                                      *
   *  CS              D3              15 - 14                                    *
   *  MOSI            D11             12 - 11                                    *
   *  SCK             D13             10 - 9                                     *
   *  MISO            D12                -                                       *
   *******************************************************************************/
   File myFile;
   const int chipSelect = 4;
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
  int three,minutes,threehour=0,minutemode=2,i=0,s=0,t=0,m=0;           // ตัวแปรทั่วไป
  
  /*******************************************************************************/
  void setup()
  {
    lcd.begin(16, 2);  Wire.begin();  rtc.begin();                          // เริ่มการทำงาน                                    
    pinMode(heater, OUTPUT); pinMode(water, OUTPUT); pinMode(fan, OUTPUT);  // เอาต์พุต
    pinMode(3, OUTPUT);
    lcd.setCursor(0,0);lcd.print("RMUTL Electronic");delay(2000);
    lcd.setCursor(0,0);lcd.print("    Mushroom    ");delay(1000);
    time(); dht(); 
    
    if (!SD.begin(chipSelect)){return;}
    myFile = SD.open("Datalog.csv", FILE_WRITE);
    if (myFile) 
    {
      myFile.println("Welcome to Temperature and Humidity Control for Mushroom");
      myFile.println("Datalog Temperature and Humidity");
      myFile.print("Data / Time");
      myFile.print(",");
      myFile.print("Temperaturemy");
      myFile.print(",");
      myFile.println("Humidity");
      
      myFile.print(day0);
      myFile.print("/");
      myFile.print(month0);
      myFile.print("/");
      myFile.print(year0);
      myFile.print(" & ");
      myFile.print(hour0);
      myFile.print(":");
      myFile.print(minute0);
      myFile.print(":");
      myFile.print(second0);
      myFile.print(",");
      
      myFile.print(temp1);
      myFile.print("C"); 
      myFile.print(",");
      myFile.print(humi1);
      myFile.println("%RH");
      myFile.close(); 
    }    
  }
   
  void loop()
  {
    lcd.setCursor(0,0);
    lcd.print("    Mushroom    ");
    i=5; // goto Keycommand
    key();
  }
  
  
  

