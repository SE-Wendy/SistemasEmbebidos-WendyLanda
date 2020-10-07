# 1 "C:\\Users\\jesus\\Desktop\\Sensor_de_humedad\\Sensor_de_humedad\\Sensor_de_humedad.ino"
# 1 "C:\\Users\\jesus\\Desktop\\Sensor_de_humedad\\Sensor_de_humedad\\Sensor_de_humedad.ino"


# 4 "C:\\Users\\jesus\\Desktop\\Sensor_de_humedad\\Sensor_de_humedad\\Sensor_de_humedad.ino" 2
LiquidCrystal_I2C lcd(0x20, 20, 4); // Se establece la direccion i2c y se indica el tipo de LCD, en este es una 20x4 

const int LED_ROJO =10; // Asignación del led rojo en el pin 10 del Arduino
const int LED_VERDE =11; // Asignación del led verde en el pin 11 del Arduino
const int ACTUADOR =12; // Asignación del actuador en el pin 12 del Arduino

const int BOTON_ARRIBA=3; // Asignación del boton de seleccion hacia arriba en el pin 3 del Arduino
const int BOTON_ABAJO =2; // Asignación del boton de seleccion hacia abajo en el pin 2 del Arduino
int SetPoint =30; // Inicializacion de del Setpoint en un valor de 30

/////////////////////////////////////////////////////////////////////////////////////

void setup (){
pinMode ( LED_ROJO , 0x1 ); // Asignacion del led rojo como salida
pinMode ( LED_VERDE , 0x1 ); // Asignacion del led verde como salida
pinMode ( ACTUADOR , 0x1 ); // Asignacion del actuador como salida
pinMode ( BOTON_ARRIBA , 0x0 ); // Asignacion del boton arriba como entrada
pinMode ( BOTON_ABAJO , 0x0 ); // Asignacion del boton abajo como entrada

digitalWrite ( BOTON_ARRIBA , 0x1 ); // Asignacion del boton arriba en estado bajo
digitalWrite ( BOTON_ABAJO , 0x1 ); // Asignacion del led rojo como salida

lcd . begin (20, 4); // Se indica que la LCD es 20x4
lcd.init(); // Inicialización de la lcd
lcd.clear(); // Se limpia la lcd
lcd.home(); // Se dirige el cursor a la posicion inicial

lcd . print ("PROYECTO 10"); // Mostrar en pantalla el texto dentro del paréntesis
lcd . setCursor (0,1); // Dirigir el cursor a la siguiente fila
lcd . print (" SISTEMA DE RIEGO"); // Mostrar en pantalla el texto dentro del paréntesis
lcd . setCursor (0,2);// Dirigir el cursor a la siguiente fila
lcd . print (" EQUIPO 5 ");// Mostrar en pantalla el texto dentro del paréntesis
delay (1000); //Mantener por 1 segundo

digitalWrite ( LED_VERDE , 0x1 ); // Apagar led verde
digitalWrite ( LED_ROJO , 0x0 ); // Encender ed rojo
digitalWrite ( ACTUADOR , 0x0 ); // Apagar actuador
delay (2000); // Esperar 2 segundos
}

/////////////////////////////////////////////////////////////////////////////

void loop (){
double HUMEDAD = ((100.0/1024.0) * analogRead ( A0 )); // El valor obtenido en el adc se multiplica por el resultado de 100/1024 y eso se asigna en la variable humedad
lcd . setCursor (0,2); // Se posiciona el cursor en la tercera fila
lcd . print ("Humedad:"); // se imprime la palabra humedad
lcd . print ( HUMEDAD );// Se imprime el valor de la variable HUMEDAD
lcd . print ("% "); //Se imprime el signo de porcentaje

 if( digitalRead ( BOTON_ABAJO )== 0x0 )// Condicional que verifica si el boton_abajo es presionado
 {
 if( SetPoint >0) // Si es asi y el setpoint es mayor a cero
 {
 SetPoint --; // Disminuye el valor de uno en uno
 }
 }

 if( digitalRead ( BOTON_ARRIBA )== 0x0 )// Condicional que verifica si el boton_arriba es presionado
 {
 if( SetPoint <99) // Si es asi y el setpoint es menor a 99
 {
 SetPoint ++;// Aumenta el valor de uno en uno
 }
 }

lcd . setCursor (0,3); //Posiciona el cursor en la fila 4
lcd . print ("Set Point:");// Imprime ña palabra setpoint
lcd . print ( SetPoint );//Imprime e valor de la variable Setpoint
lcd . print ("% ");// Imprime el signo de porcentaje

if( HUMEDAD > SetPoint )// Preunta si lel valor de la variable HUMEDAD es mayor al valor de la variable Setpoint y en caso de ser cierto realiza las siguientes acciones
{
digitalWrite ( ACTUADOR , 0x0 ); // Enciende el actuador
digitalWrite ( LED_ROJO , 0x1 ); // Apaga el led rojo
digitalWrite ( LED_VERDE , 0x0 ); // Enciende el led verde
}
else // En caso contrario
{
digitalWrite ( ACTUADOR , 0x1 ); // Apaga el actuador
digitalWrite ( LED_VERDE , 0x1 ); // Apaga el led verde
digitalWrite ( LED_ROJO , 0x0 ); // Enciende el led rojo
}
delay (1000); // Restardo de 1 segundo
}
