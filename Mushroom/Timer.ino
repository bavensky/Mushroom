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
