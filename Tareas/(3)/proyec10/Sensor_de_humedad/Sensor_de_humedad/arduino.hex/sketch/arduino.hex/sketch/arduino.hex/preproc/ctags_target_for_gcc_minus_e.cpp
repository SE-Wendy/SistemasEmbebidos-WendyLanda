# 1 "C:\\Users\\jesus\\Desktop\\Sensor_de_humedad\\Sensor_de_humedad\\Sensor_de_humedad.ino"
# 1 "C:\\Users\\jesus\\Desktop\\Sensor_de_humedad\\Sensor_de_humedad\\Sensor_de_humedad.ino"


# 4 "C:\\Users\\jesus\\Desktop\\Sensor_de_humedad\\Sensor_de_humedad\\Sensor_de_humedad.ino" 2
// initialize the library with the numbers of the interface pins
LiquidCrystal_I2C lcd(0x20, 20, 4);//Declaramos el tipo de LCD y su dirección
const int LED_ROJO =10; //Red LED
const int LED_VERDE =11; //Green LED
const int RELE =12; //Lock Relay or motor
//Key connections with arduino
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
 //Pull up for setpoint keys
digitalWrite ( BOTON_ARRIBA , 0x1 );
digitalWrite ( BOTON_ABAJO , 0x1 );
 // set up the LCD's number of columns and rows:
lcd . begin (20, 4);
lcd.init();
lcd.clear();
lcd.home();
 // Print a message to the LCD.
lcd . print ("PROYECTO 10");
lcd . setCursor (0,1); //Move coursor to second Line
lcd . print (" SISTEMA DE RIEGO");
lcd . setCursor (0,2);
lcd . print (" EQUIPO 5 ");
delay (1000);

digitalWrite ( LED_VERDE , 0x1 ); //Green LED Off
digitalWrite ( LED_ROJO , 0x0 ); //Red LED On
digitalWrite ( RELE , 0x0 ); //Turn off Relay
delay (2000);
}
/////////////////////////////////////////////////////////////////////////////
void loop (){
 double HUMEDAD = ((100.0/1024.0) * analogRead ( A0 )); //Map it in
lcd . setCursor (0,2);
lcd . print ("Humedad:"); //Do not display entered keys
lcd . print ( HUMEDAD );
lcd . print ("% ");
//Get user input for setpoints
 if( digitalRead ( BOTON_ABAJO )== 0x0 )
 {
 if( SetPoint >0) //Not less than zero
 {
 SetPoint --;
 }
 }
 if( digitalRead ( BOTON_ARRIBA )== 0x0 )
 {
 if( SetPoint <99) //Not more than 100%
 {
 SetPoint ++;
 }
 }
//Display Set point on LCD
lcd . setCursor (0,3);
lcd . print ("Set Point:");
lcd . print ( SetPoint );
lcd . print ("% ");
//Check Temperature is in limit
if( HUMEDAD > SetPoint )
{
digitalWrite ( RELE , 0x0 ); //Turn off water pump
digitalWrite ( LED_ROJO , 0x1 );
digitalWrite ( LED_VERDE , 0x0 ); //Turn on Green LED
}
else
{
digitalWrite ( RELE , 0x1 ); //Turn on water pump
digitalWrite ( LED_VERDE , 0x1 );
digitalWrite ( LED_ROJO , 0x0 ); //Turn on RED LED
}
delay (1000); //Update at every 100mSeconds
}
