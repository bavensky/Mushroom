  /*******************************************************************************
  * ฟังก์ชั่นการทำงานปุ่มกดบนโมดูล DFRobot                                          *
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

