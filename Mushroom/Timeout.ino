  /*******************************************************************************
  * ฟังก์ชั่นกำหนดเวลาใช้งานและบันทึกค่าโดยนับถอยหลัง                                         *
  *******************************************************************************/
  
  void timeout(int hi,int mi)
  {
    // time();  // call funtion time
    
    int hc = 0,  mc = 0;    // variable real hour and real minute. 
    int ho = 0,  mo = 0;    // variable hour and minute out function1
    int h  = 0,  m  = 0;    // variable hour and minute out function2
    int function=0;         // variable function
    
    hc = hour0;    mc = minute0;  // import function  time
    ho = hc+hi;    mo = mc+mi;    // real time plus setting
    
      /*** not over ***/
      if(ho < 23 || mo < 59)
      {
        function = 1;  // goto function 1
      }  
       
       /***  over  ***/   
      if(ho > 23 || mo > 59)
      {
        if(ho > 23){ h = ho - 24;} 
        if(mo > 59){ m = mo - 60; h = ho + 1;}
        function = 2;  // goto function 2
      }
    
    // function1
    while(function == 1)
    {
      time();
      lcd.home();
      lcd.print("    Function1   ");
      lcd.setCursor(0,1);
      lcd.print(ho);
      lcd.print(":");
      lcd.print(mo);
      lcd.print("  ");
      lcd.print(hour0);
      lcd.print(":");
      lcd.print(minute0);

      myFile = SD.open("Datalog.csv",FILE_WRITE); 
      if(myFile)
      {
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
      
      if( ho == hour0 && mo == minute0 )
      {
        lcd.clear();
        lcd.home();
        lcd.print(" END of Function ");
        function = 0;  // end function
      }
    }
    
    //function2
    while(function == 2)
    {
      time();
      lcd.home();
      lcd.print("    Function2   ");
      lcd.setCursor(0,1);
      lcd.print(h);
      lcd.print(":");
      lcd.print(m);
      lcd.print("  ");
      lcd.print(hour0);
      lcd.print(":");
      lcd.print(minute0);
      
      myFile = SD.open("Datalog.csv",FILE_WRITE); 
      if(myFile)
      {
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
      
      if( h == hour0 && m == minute0 )
      {
        lcd.clear();
        lcd.home();
        lcd.print(" END of Function ");
        function = 0;  // end function
      }
    }
    
  }  /*-- End --*/
