//PROPERTY OF IGNITE

int leftMotF = 3;// defines pin 5 as connected to the motor
int leftMotB= 4;// defines pin 6 as connected to the motor
int rightMotF = 5;// defines pin 7 as connected to the motor
int rightMotB = 6;// defines pin 8 as connected to the motor

int ENA = A4;
int ENB= A5;
int channel1 = A0;
int channel2 = A1; 
int channel3 = A2;
int channel4 = A3;

int trigPin = 12;      // trig pin of HC-SR04
int echoPin = 13;

const int buzzer = 11;
long duration, distance;


int ValueChannel1 ; // Used to store values
int ValueChannel2 ; // Used to store values
int ValueChannel3 ; // Used to store values
int ValueChannel4 ; // Used to store values
 
int CARSPEED;




void  setup ()
{
  pinMode(trigPin, OUTPUT);         // set trig pin as output
  pinMode(echoPin, INPUT);          //set echo pin as input to capture reflected waves

  pinMode(buzzer, OUTPUT); //buzzer

  
  // initialises the motor pins as outputs
   pinMode (leftMotF, OUTPUT);
   pinMode (leftMotB, OUTPUT);
   pinMode (rightMotF, OUTPUT);
   pinMode (rightMotB, OUTPUT);
   pinMode(ENA, OUTPUT);
   pinMode(ENB, OUTPUT);

   // initialises the channels as inputs
   pinMode (channel1, INPUT);
   pinMode (channel2, INPUT);
   pinMode (channel3, INPUT);
   pinMode (channel4, INPUT);

   // Sets the baud rate to 9600 bps
   Serial.begin (9600); 
}

void  loop ()
{
    // Checks the value of channel1
  ValueChannel1 = (pulseIn (channel1, HIGH)); 
  Serial.print("Channel 1: ");
  Serial.println(ValueChannel1); //Prints the channels value on the serial monitor

  ValueChannel2 = (pulseIn (channel2, HIGH)); // Checks the value of channel1
  Serial.print("Channel 2: ");
  Serial.println (ValueChannel2); //Prints the channels value value on the serial monitor

  // Checks the value of channel3
  ValueChannel3 = (pulseIn (channel3, HIGH)); 
  Serial.print("Channel 3: ");
  Serial.println(ValueChannel3); //Prints the channels value on the serial monitor// Checks the value of channel4
  ValueChannel4 = (pulseIn (channel4, HIGH)); 
  Serial.print("Channel 4: ");
  Serial.println(ValueChannel4); //Prints the channels value on the serial monitor
  
//Setting Car Speed
    CARSPEED = 150;
  if(ValueChannel3>1500){
    if ((ValueChannel2 > 1300 && ValueChannel2 < 1600 ) && (ValueChannel1 > 1300 && ValueChannel1 < 1600 )&&(ValueChannel4 > 1300 && ValueChannel4 < 1600 )) //STOP 
  {
          analogWrite(ENA, 0);
          analogWrite(ENB, 0);
          digitalWrite(leftMotF , LOW);
          digitalWrite(leftMotB , LOW);
          digitalWrite(rightMotF , LOW);
          digitalWrite(rightMotB , LOW);
          Serial.println("Stop");
  }
 
 
  else if (ValueChannel1 > 1600 && ValueChannel1 < 2000) // LEFT
  {
          analogWrite(ENA, CARSPEED);
          analogWrite(ENB, CARSPEED);
          digitalWrite(leftMotF , LOW);
          digitalWrite(leftMotB , HIGH);
          digitalWrite(rightMotF , HIGH);
          digitalWrite(rightMotB , LOW);
          Serial.println("HL");
  }
  else if (ValueChannel1 < 1300 && ValueChannel1 > 1000) // RIGHT
  {
        
        analogWrite(ENA, CARSPEED);
        analogWrite(ENB, CARSPEED);
        digitalWrite(leftMotF , HIGH);
        digitalWrite(leftMotB , LOW);
        digitalWrite(rightMotF , LOW);
        digitalWrite(rightMotB , HIGH);
        Serial.println("HR"); 
  }
 
  else if (ValueChannel2 < 1300 && ValueChannel2 > 1000) // BACKWARD
  {
          
      analogWrite(ENA, CARSPEED);
      analogWrite(ENB, CARSPEED);
      digitalWrite(leftMotF , LOW);
      digitalWrite(leftMotB , HIGH);
      digitalWrite(rightMotF , LOW);
      digitalWrite(rightMotB , HIGH);
      Serial.println("B");
  }
  else if (ValueChannel2 > 1600 && ValueChannel2 < 2000) // FORWARD
  {
          analogWrite(ENA, CARSPEED);
          analogWrite(ENB, CARSPEED);
          digitalWrite(leftMotF , HIGH);
          digitalWrite(leftMotB , LOW);
          digitalWrite(rightMotF , HIGH);
          digitalWrite(rightMotB , LOW);
          Serial.println("F");
  }
    }
  else if (ValueChannel3< 1500)  //Autonomous
  {
    
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);   
  digitalWrite(trigPin, HIGH);     // send waves for 10 us
  delayMicroseconds(10);
  duration = pulseIn(echoPin, HIGH); // receive reflected waves
  distance = duration / 58.2;   // convert to distance
  delay(10);
    
  if (distance >=18)            
  {
    // move forward
          analogWrite(ENA, CARSPEED);
          analogWrite(ENB, CARSPEED);
          digitalWrite(leftMotF , HIGH);
          digitalWrite(leftMotB , LOW);
          digitalWrite(rightMotF , HIGH);
          digitalWrite(rightMotB , LOW);
          Serial.println("F");  
          delay(100);   
          //Stop 
      analogWrite(ENA, 0);
      analogWrite(ENB, 0);
      digitalWrite(leftMotF , LOW);
      digitalWrite(leftMotB , LOW);
      digitalWrite(rightMotF , LOW);
      digitalWrite(rightMotB , LOW);
      delay(500);   
                                                            
  }

 else if (distance < 18)
  {
    //Stop 
      analogWrite(ENA, 0);
      analogWrite(ENB, 0);
      digitalWrite(leftMotF , LOW);
      digitalWrite(leftMotB , LOW);
      digitalWrite(rightMotF , LOW);
      digitalWrite(rightMotB , LOW);
      delay(500);
    
    //movebackword  
      analogWrite(ENA, CARSPEED);
      analogWrite(ENB, CARSPEED);
      digitalWrite(leftMotF , LOW);
      digitalWrite(leftMotB , HIGH);
      digitalWrite(rightMotF , LOW);
      digitalWrite(rightMotB , HIGH);
      Serial.println("B");
      delay(200);
    

     
      //left
      analogWrite(ENA, CARSPEED);
          analogWrite(ENB, CARSPEED);
          digitalWrite(leftMotF , LOW);
          digitalWrite(leftMotB , HIGH);
          digitalWrite(rightMotF , HIGH);
          digitalWrite(rightMotB , LOW);
          Serial.println("HL");
          delay(200);
          
      
  }
 }
 else{//Stop
    digitalWrite(leftMotF , LOW);
      digitalWrite(leftMotB , LOW);
      digitalWrite(rightMotF , LOW);
      digitalWrite(rightMotB , LOW);
      Serial.println("Stop"); 
  }

 if(ValueChannel4>1600){
  //Buzzer
    tone(buzzer, 1000); // Send 1KHz sound signal...
   }
   else{
      noTone(buzzer);     // Stop sound
    }
Serial.println(CARSPEED);
  
  
 //delay(1000);
}
