
#include <DHT22.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
#include <stdio.h>
#define DHT22_PIN1 11
#define DHT22_PIN2 12
#define DHT22_PIN3 13
DHT22 myDHT1(DHT22_PIN1);
DHT22 myDHT2(DHT22_PIN2);
DHT22 myDHT3(DHT22_PIN3);
int temp1=0,humi1=0,temp2=0,humi2=0,temp3=0,humi3=0;

int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

int heater=3,water=2,i=0;

void setup()
{
 Serial.begin(9600);  lcd.begin(16, 2);  
 pinMode(heater, OUTPUT); pinMode(water, OUTPUT); 
 lcd.setCursor(0,0);
 lcd.print("  Mushroom War  "); 
 delay(2000);
}
 
void loop()
{
  dht();
  
 
}

void check()
{
    if(humi1 != humi2)
  {
    i=1;Serial.println(" Begin !!!");delay(1000);
  }
  
  while(i == 1)
  {
    dht();
    if(temp3<= 30 )
    {digitalWrite(heater, HIGH);}
    if(temp3 > 31)
    {digitalWrite(heater, LOW);}
    if(humi3<=80)
    {digitalWrite(water, HIGH);}
    if(humi3>81)
    {digitalWrite(water, LOW);}
    if(temp3>31 || humi3 >81)
    {Serial.print(" END !!!");digitalWrite(heater, LOW);digitalWrite(water, LOW); i=0; }
  }  
}

void dht()
{ 
  DHT22_ERROR_t errorCode;
  errorCode = myDHT1.readData();
  errorCode = myDHT2.readData();
  errorCode = myDHT3.readData();
  temp1 = myDHT1.getTemperatureC();humi1 = myDHT1.getHumidity();
  temp2 = myDHT2.getTemperatureC();humi2 = myDHT2.getHumidity();
  temp3 = myDHT3.getTemperatureC();humi3 = myDHT3.getHumidity();
  lcd.setCursor(0,1);
  lcd.print(temp1);lcd.print("C");lcd.print(humi1);lcd.print("%");
  lcd.setCursor(10,1);
  lcd.print(temp2);lcd.print("C");lcd.print(humi2);lcd.print("%");
  Serial.print(temp1);Serial.print(" / ");Serial.print(humi1);Serial.print("   ");
  Serial.print(temp2);Serial.print(" / ");Serial.print(humi2);Serial.print("   ");
  Serial.print(temp3);Serial.print(" / ");Serial.println(humi3);
}

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
void key()
{
  lcd.setCursor(0,1);            
  lcd_key = read_LCD_buttons();  
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
}


