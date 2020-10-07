/*
  Control de agua automático - Al tener el tanque de agua Vacío
  el programa lo detecta y activa una bonba para el llenado de 
  este taque, al momento en que este lleno, apaga la bomba y se 
  pone en espera de si se vacia el tanque. Mediante una LCD nos 
  da el estado del sistema.Cuenta con contol manual
  circuits4you.com
*/

//================================================================
#include <LiquidCrystal_I2C.h>// inicializamos la libreria para el control I2C
LiquidCrystal_I2C lcd(0x20, 20, 4);//Declaramos el tipo de LCD y su dirección
const int LED_RED=10; //LED rojo
const int LED_GREEN=11; //LED verde
const int RELAY=12; //Relevador activador de la bomba

//Conexión clave con Arduino
const int on_key=3;//Boton de encendido
const int off_key=2;//Boton de apagado
char Pump=0;//Variable para encendido y apagado de la bomba

//=================================================================
//                  SETUP
//=================================================================
void setup(){
  //Declaración de entradas y salidas
 pinMode(LED_RED,OUTPUT);
 pinMode(LED_GREEN,OUTPUT); 
 pinMode(RELAY,OUTPUT); 
 pinMode(on_key,INPUT);
 pinMode(off_key,INPUT);
 
 //Activación en pulso bajo
 digitalWrite(on_key,HIGH);
 digitalWrite(off_key,HIGH);
 
 //Inicialización de LCD
 lcd.begin(20, 4);
 lcd.init();
 lcd.clear();//Limpiamos la pantalla
 lcd.home(); //Posicion en la LCD 0,0
 lcd.print("Topicos II"); 
 lcd.setCursor(0,1); //Mover el cursor a la segunda ilera
 lcd.print("Cont. Nivel de agua");
 digitalWrite(LED_GREEN,HIGH);  //LED verde Off
 digitalWrite(LED_RED,HIGH);    //LED rojo Off
 digitalWrite(RELAY,LOW);       //Apagar el relevador
 lcd.setCursor(0,3);//Mover el cursor a la cuarta ilera
 lcd.print("Bomba : Apagada ");   
 delay(2000);
}

//=================================================================
//                  LOOP
//================================================================= 
void loop(){
 lcd.setCursor(0,2);//Cursor en ilera 3
 lcd.print("Nivel Agua: ");    //Mostrar claves ingresadas
  if(analogRead(A1)>512)    //Checar nivel de agua
  {
    lcd.print("Lleno  ");
    digitalWrite(LED_GREEN,LOW);  //LED verde On
    Pump=0;  //Apagar Bomba
  }
  
  if(analogRead(A2)<400)    //Checar nivel de agua
  {
    lcd.print("Vacio   ");       
    digitalWrite(LED_GREEN,HIGH);  //Nivel del tanque bajo apagar LED verde
  }
  
  if(analogRead(A0) < 400)  //Depósito inferior vacío
  {
    Pump=0;   
    lcd.setCursor(0,3);//Cursor en ilera 3
    lcd.print("Deposito inf. Vacio");     
    delay(1000);
  }
  
  else
  {
    if(analogRead(A2)<400)//Nivel de agua del tanque superior bajo, encender la bomba
    {
      Pump=1;
    }
  }
  
  if(Pump==1)
    {
      digitalWrite(LED_RED,LOW);//Encender el indicador de la bomba y la bomba
      digitalWrite(RELAY,HIGH);
      lcd.setCursor(0,3);
      lcd.print("Bomba: ON           ");//Mostrar estado de la bomba    
    }
    
  else
    {
      digitalWrite(LED_RED,HIGH);//Apagar indicador de la bomba y la bomba
      digitalWrite(RELAY,LOW);   
      lcd.setCursor(0,3);
      lcd.print("Bomba: OFF          ");     
      delay(1000);
    }
//Obtenga la entrada del usuario para los puntos de ajuste 
  if(digitalRead(on_key)==LOW)//Checar si es presionado el boton ON
  {
    while(digitalRead(on_key)==LOW);  //Esperar nivel bajo del boton
    Pump=1;    //Encender Bomba
  }
  if(digitalRead(off_key)==LOW)//Checar si es presionado el boton OFF
  {
    Pump=0;    //Apagar Bomba
  }
 delay(100); //Actualización cada 100 microsegundos
}
//=================================================================
