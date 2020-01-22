//************************ Initial ********************

//----------------------- ECG ----------------------
int ECGL0P = 14, ECGL0M = 12, ECGOP = 27;
unsigned long time1,time2;
//----------------------- LM35 Temp ----------------------

int temPin = 34;                   // Temp sensor pin wire connected to analog pin 1
float RawTemp;                        // holds incoming raw temp data
float TEMP;                         // holds temperature in F

//----------------------- MQ150 Gas ----------------------

int sensorPin = 35; 
int sensorValue = 0;

//************************ Setup ********************

void setup() 
{
//----------------------- ECG ----------------------
Serial.begin(9600);
pinMode(ECGL0P, INPUT); // D5pin Setup for leads off detection LO +
pinMode(ECGL0M, INPUT); // D6pin Setup for leads off detection LO -
}

//************************ Loop ********************

void loop() {
ECG ();

LM35();

MQ135 ();

delay (3000);

}

//************************ Function ********************

//----------------------- ECG ----------------------

void ECG()
{
  time1 = millis();
  time2 = time1;

  while ( (time2-time1) < 5000)
  {
if((digitalRead(ECGL0P) == 1)||(digitalRead(ECGL0M) == 1)){
Serial.println('!');
}
else{
// send the value of analog input 0:
Serial.println(analogRead(ECGOP));
}
//Wait for a bit to keep serial data from saturating
delay(1);
time2 = millis();
}
}

//----------------------- LM35 ----------------------

void LM35(){

  //Calculates temperature from lm35

  RawTemp = analogRead(temPin);
  float mv = (RawTemp/1023.0)*5000;
  float celcius = mv/10;
  TEMP = (celcius*9/5) + 32;
  Serial.print("Temperature is   ");
  Serial.println(TEMP);
  delay(200);
 
}

//----------------------- MQ135 ----------------------

void MQ135() 
{ sensorValue = analogRead(sensorPin);
  
  Serial.print("Air Quality = ");
  Serial.print(sensorValue);

  Serial.print("*PPM");
  Serial.println();
  delay(200);
}
