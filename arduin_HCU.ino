
int potpin=A0; //potentiometer to analog
int tps=A1; //directly comes from engine
int val1;
int val2;
int val3;
int led=13;//led is connected to 13 of the digital side

void setup() {
  TCCR2B=TCCR2B & 0b11111000 | 0x01; //sets PWM to 32KHz
  digitalWrite(led,HIGH);
  Serial.begin(9600);
  }


void loop() {

  val1=analogRead(potpin); //putting the value of pot in val1
  val2=analogRead(tps); //putting the value of tps in val2
  val1= map(val1,1023,0,0,1023); //set pot value from 0 to 1023
  val2= map(val2,862,59,0,1023);// set TPS value from 0 to 1023

  while(val2<val1)//check if POT is ahead of TPS
  {
    if(val2<320)
    {
      analogWrite(9,60);// Writing the PWM signal of 60 to pin3 for the smooth opening of the butterfly valve
    }
    if(val2>339 && val2<680)
    {
      analogWrite(9,90);// Writing PWM signal of 90 to pin 3
    }
    if(val2>679)
    {
      analogWrite(9,120);
    }

    val1=analogRead(potpin); //Read  DAta for Comparasion in while loop
    val2=analogRead(tps); 
    val1= map(val1,1023,0,0,1023);
    val2= map(val2,862,59,0,1023);
    
  }
  while(val2>val1)
  {
    analogWrite(9,90); // Send a 0 to pin 3 to turn off the motor
    val1=analogRead(potpin);//read input for comparasion
    val2=analogRead(tps);
    val1= map(val1,1023,0,0,1023);
    val2= map(val2,862,59,0,1023);
  }

}
