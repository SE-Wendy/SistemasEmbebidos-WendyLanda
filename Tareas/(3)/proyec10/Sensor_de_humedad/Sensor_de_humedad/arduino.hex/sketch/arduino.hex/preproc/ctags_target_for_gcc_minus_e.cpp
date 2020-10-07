# 1 "C:\\Users\\jesus\\Desktop\\Sensor_de_humedad\\Sensor_de_humedad\\Sensor_de_humedad.ino"
# 1 "C:\\Users\\jesus\\Desktop\\Sensor_de_humedad\\Sensor_de_humedad\\Sensor_de_humedad.ino"


# 4 "C:\\Users\\jesus\\Desktop\\Sensor_de_humedad\\Sensor_de_humedad\\Sensor_de_humedad.ino" 2

LiquidCrystal_I2C lcd(0x20, 20, 4);
const int LED_ROJO =10;
const int LED_VERDE =11;
const int RELE =12;

const int BOTON_ARRIBA=3;
const int BOTON_ABAJO =2;
int SetPoint =30;
/////////////////////////////////////////////////////////////////////////////////////
void setup (){
pinMode ( LED_ROJO , 0x1 );
pinMode ( LED_VERDE , 0x1 );
pinMode ( RELE , 0x1 );
pinMode ( BOTON_ARRIBA , 0x0 );
pinMode ( BOTON_ABAJO , 0x0 );

digitalWrite ( BOTON_ARRIBA , 0x1 );
digitalWrite ( BOTON_ABAJO , 0x1 );

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

digitalWrite ( LED_VERDE , 0x1 );
digitalWrite ( LED_ROJO , 0x0 );
digitalWrite ( RELE , 0x0 );
delay (2000);
}
/////////////////////////////////////////////////////////////////////////////
void loop (){
 double HUMEDAD = ((100.0/1024.0) * analogRead ( A0 ));
lcd . setCursor (0,2);
lcd . print ("Humedad:");
lcd . print ( HUMEDAD );
lcd . print ("% ");

 if( digitalRead ( BOTON_ABAJO )== 0x0 )
 {
 if( SetPoint >0)
 {
 SetPoint --;
 }
 }
 if( digitalRead ( BOTON_ARRIBA )== 0x0 )
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
digitalWrite ( RELE , 0x0 );
digitalWrite ( LED_ROJO , 0x1 );
digitalWrite ( LED_VERDE , 0x0 );
}
else
{
digitalWrite ( RELE , 0x1 );
digitalWrite ( LED_VERDE , 0x1 );
digitalWrite ( LED_ROJO , 0x0 );
}
delay (1000);
}
