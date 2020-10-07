#include <Arduino.h>
#line 1 "C:\\Users\\jesus\\Desktop\\Sensor_de_humedad\\Sensor_de_humedad\\Sensor_de_humedad.ino"
#line 1 "C:\\Users\\jesus\\Desktop\\Sensor_de_humedad\\Sensor_de_humedad\\Sensor_de_humedad.ino"


#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20, 20, 4);
const int LED_ROJO =10; 
const int LED_VERDE =11; 
const int RELE =12; 

const int BOTON_ARRIBA=3;
const int BOTON_ABAJO =2;
int SetPoint =30;
/////////////////////////////////////////////////////////////////////////////////////
#line 14 "C:\\Users\\jesus\\Desktop\\Sensor_de_humedad\\Sensor_de_humedad\\Sensor_de_humedad.ino"
void setup();
#line 42 "C:\\Users\\jesus\\Desktop\\Sensor_de_humedad\\Sensor_de_humedad\\Sensor_de_humedad.ino"
void loop();
#line 14 "C:\\Users\\jesus\\Desktop\\Sensor_de_humedad\\Sensor_de_humedad\\Sensor_de_humedad.ino"
void setup (){
pinMode ( LED_ROJO , OUTPUT );
pinMode ( LED_VERDE , OUTPUT );
pinMode ( RELE , OUTPUT );
pinMode ( BOTON_ARRIBA , INPUT );
pinMode ( BOTON_ABAJO , INPUT );
 
digitalWrite ( BOTON_ARRIBA , HIGH );
digitalWrite ( BOTON_ABAJO , HIGH );
 
lcd . begin (20, 4);
lcd.init();
lcd.clear();
lcd.home();
 
lcd . print ("PROYECTO 10");
lcd . setCursor (0,1); 
lcd . print (" SISTEMA DE RIEGO");
lcd . setCursor (0,2);
lcd . print (" EQUIPO 5 ");
delay (1000);

digitalWrite ( LED_VERDE , HIGH ); 
digitalWrite ( LED_ROJO , LOW ); 
digitalWrite ( RELE , LOW ); 
delay (2000);
}
/////////////////////////////////////////////////////////////////////////////
void loop (){
 double HUMEDAD = ((100.0/1024.0) * analogRead ( A0 )); 
lcd . setCursor (0,2);
lcd . print ("Humedad:"); 
lcd . print ( HUMEDAD );
lcd . print ("% ");

 if( digitalRead ( BOTON_ABAJO )== LOW )
 {
 if( SetPoint >0) 
 {
 SetPoint --;
 }
 }
 if( digitalRead ( BOTON_ARRIBA )== LOW )
 {
 if( SetPoint <99) 
 {
 SetPoint ++;
 }
 }

lcd . setCursor (0,3);
lcd . print ("Set Point:");
lcd . print ( SetPoint );
lcd . print ("% ");

if( HUMEDAD > SetPoint )
{
digitalWrite ( RELE , LOW ); 
digitalWrite ( LED_ROJO , HIGH );
digitalWrite ( LED_VERDE , LOW ); 
}
else
{
digitalWrite ( RELE , HIGH );
digitalWrite ( LED_VERDE , HIGH );
digitalWrite ( LED_ROJO , LOW ); 
}
delay (1000); 
}

