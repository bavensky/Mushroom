  /*******************************************************************************
  * ลูปย่อยเริ่มการทำงานตัวตรวจรู้                                                      *
  *******************************************************************************/
  void dht()
  { 
    DHT22_ERROR_t errorCode;
    errorCode = myDHT1.readData();
    errorCode = myDHT2.readData();
    errorCode = myDHT3.readData();
    temp1 = myDHT1.getTemperatureC();  humi1 = myDHT1.getHumidity();
    temp2 = myDHT2.getTemperatureC();  humi2 = myDHT2.getHumidity();
    temp3 = myDHT3.getTemperatureC();  humi3 = myDHT3.getHumidity();
  }
