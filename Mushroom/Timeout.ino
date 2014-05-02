  /*******************************************************************************
  * ฟังก์ชั่นกำหนดเวลาใช้งานและบันทึกค่าโดยนับถอยหลัง                                         *
  *******************************************************************************/
  
  void timeout(int hi,int mi)
  {
    time();  // call funtion time
    
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
    if(function == 1)
    {
      // someone to active
      if( ho == hour0 && mo == minute0 )
      {
        function = 0;  // end function
      }
    }
    //function2
    if(function == 2)
    {
      // someone to active
      if( h == hour0 && m == minute0 )
      {
        function = 0;  // end function
      }
    }
    
  }  /*-- End --*/
