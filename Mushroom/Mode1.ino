  /*******************************************************************************
  * ฟังก์ชั่นย่อยเริ่มการทำงานโหมดที่ ๑ โหมดฆ่าเชื้อ                                                    *
  *******************************************************************************/
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
