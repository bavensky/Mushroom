#include <DHT22.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
#include <stdio.h>
#define DHT22_PIN 2
DHT22 myDHT22(DHT22_PIN);
int temp=0,humi=0;

int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

void setup()
{
 Serial.begin(9600);
 lcd.begin(16, 2);              // start the library
 lcd.setCursor(0,0);
 lcd.print("  Mushroom War  "); // print a simple message
 delay(2000);
}
 
void loop()
{

 lcd.setCursor(0,1);            // move to the begining of the second line
 lcd_key = read_LCD_buttons();  // read the buttons
  if( lcd_key==btnRIGHT)
  {lcd.print("RIGHT ");}
  if( lcd_key==btnLEFT)
  {lcd.print("LEFT  ");}
  if( lcd_key==btnUP)
  {lcd.print("UP    ");}
  if( lcd_key==btnDOWN)
  {lcd.print("DOWN  ");}
  if( lcd_key==btnSELECT)
  {lcd.print("SELECT");}
  if( lcd_key==btnNONE)
  {lcd.print("NONE  ");}
  dht();
}

void dht()
{ 
  DHT22_ERROR_t errorCode;
  errorCode = myDHT22.readData();
  temp = myDHT22.getTemperatureC();humi = myDHT22.getHumidity();
  lcd.setCursor(6,1);
  lcd.print(temp);lcd.print("C ");lcd.print(humi);lcd.print("%");
}

int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor 
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 195)  return btnUP; 
 if (adc_key_in < 380)  return btnDOWN; 
 if (adc_key_in < 555)  return btnLEFT; 
 if (adc_key_in < 790)  return btnSELECT;   
 return btnNONE;  // when all others fail, return this...
}


