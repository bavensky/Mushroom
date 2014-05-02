  /*******************************************************************************
  * ฟังก์ชั่นย่อยเริ่มการทำงานโมดูลฐานเวลาจริง                                                *
  *******************************************************************************/
  void time()
  {
    // rtc.adjust(DateTime(__DATE__, __TIME__));   // when use for adjust time
    DateTime now = rtc.now(); 
    year0 = now.year(); month0 = now.month();   day0 = now.day();
    hour0 = now.hour(); minute0 = now.minute(); second0 = now.second();
    DateTime future (now.unixtime() + 7 * 86400L + 30); 
  }
