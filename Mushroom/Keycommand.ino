  /******************************************************************************
  * ฟังก์ชั่นย่อยเลือกโหมดการทำงาน                                                       *
  *******************************************************************************/
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
    }  }

