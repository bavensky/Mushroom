  void mode2()
  {
    lcd.setCursor(0,1);lcd.print(" Mode 2 Working ");delay(2000);
    lcd.setCursor(0,0);lcd.print("Mode2 Working   ");
    lcd.setCursor(0,1);lcd.print("CheckTemperature");delay(2000);
    s=1;
    while(s==1)
    {
      dht();
      lcd.setCursor(0,0);lcd.print("TempL:");lcd.print(temp2);lcd.print("C ");lcd.print(humi2);lcd.print("%RH ");
      lcd.setCursor(0,1);lcd.print("TempR:");lcd.print(temp3);lcd.print("C ");lcd.print(humi3);lcd.print("%RH ");
      lcd_key = read_LCD_buttons(); 
      if(lcd_key==btnSELECT)
      {delay(200);s=0;i=0;}                  
      if(temp2 != temp3 || humi2 != humi3)
      {
        delay(2000);
        lcd.setCursor(0,0);lcd.print("     Working    ");
        i=1;
        while(i==1)
        {  
          dht();
          lcd.setCursor(0,1);lcd.print("Temp:");lcd.print(temp3);lcd.print("C ");lcd.print(humi3);lcd.print("%RH ");
          if(temp3 <= 30 )
          {digitalWrite(heater, HIGH);}
          if(temp3 >= 31)
          {digitalWrite(heater, LOW);}
          if(humi3 <= 80)
          {digitalWrite(water, HIGH);digitalWrite(fan, LOW);}
          if(humi3 >= 81)
          {digitalWrite(water, LOW);digitalWrite(fan, HIGH);}
          if(temp2 == temp3 && humi2 == humi3)
          {
            lcd.setCursor(0,1);lcd.print(" Mode 2 END work ");
            digitalWrite(heater, LOW);digitalWrite(water, LOW);digitalWrite(fan, LOW);s=0;i=0; 
          }
          
          lcd_key = read_LCD_buttons(); 
          if(lcd_key==btnSELECT)
          {delay(200);digitalWrite(heater, LOW);digitalWrite(water, LOW);digitalWrite(fan, LOW);s=0;i=0;}   
        }
      }
    }
  }
