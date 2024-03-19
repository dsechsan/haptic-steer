volatile long temp_inner, temp_outer, counter_inner = 0, counter_outer = 0; //This variable will increase or decrease depending on the rotation of encoder
float angle_inner, angle_outer;
float force1 = 0, force2 = 0;
// X = 1, Z = 2
const float K_2 = -20.0, K_1 = -10.0;

// Motor 1 - Inner
int pwmPin1 = 9; 
int dirPin1 = 8;

double Tp1 = 0;                    
double duty1 = 0; 

// Motor 2 - Outer
int pwmPin2 = 10;
int dirPin2 = 12;

double Tp2 = 0;                    
double duty2 = 0;   

unsigned int output1 = 0;  
unsigned int output2 = 0;  

void setup() {
  Serial.begin (115200);

  pinMode(2, INPUT_PULLUP); 
  pinMode(3, INPUT_PULLUP); 
  pinMode(6, INPUT_PULLUP); 
  pinMode(5, INPUT_PULLUP);

  attachInterrupt(0, ai0, RISING);
  attachInterrupt(1, ai1, RISING);


  setPwmFrequency(pwmPin1, 1);
  setPwmFrequency(pwmPin2, 1);

  // Output pins
  pinMode(pwmPin1, OUTPUT);  // PWM pin for motor 1
  pinMode(dirPin1, OUTPUT);  // dir pin for motor 1
  
  pinMode(pwmPin2, OUTPUT);  // PWM pin for motor 2
  pinMode(dirPin2, OUTPUT);  // dir pin for motor 2

  // Initialize motor
  analogWrite(pwmPin1, 0);     // set to not be spinning (0/255)
  digitalWrite(dirPin1, LOW);  // set direction

  analogWrite(pwmPin2, 0);     // set to not be spinning (0/255)
  digitalWrite(dirPin2, LOW);  // set direction

  }
   
  void loop() {
    // Sending Angle data
    encoderCounts();
    // Reading from Unity
    if(Serial.available() > 0){
      String msg = Serial.readStringUntil('\n');    

      float xValue = msg.substring(0, msg.indexOf(',')).toFloat();
      msg = msg.substring(msg.indexOf(',') + 1);
      float yValue = msg.substring(0, msg.indexOf(',')).toFloat();
      float zValue = msg.substring(msg.indexOf(',') + 1).toFloat();
      force2= K_2 * zValue;
      force1 = K_1 * xValue; 
      // Serial.println(xValue);
  }
    // else{
    //   force2 = 0;
    //   force1 = 0;
    // }
    // Serial.print("force1: ");
    // Serial.println(force1);
    // Serial.print("force2: ");
    // Serial.println(force2);
    
    //*************************************************************
    //********************** Force output *************************
    //*************************************************************
    Tp1 = force1 * 0.175/5;
    Tp2 = force2 * 0.13/5;

    // Determine correct direction for motor torque
    if (force1 > 0) {
      digitalWrite(dirPin1, HIGH);
    } else {
      digitalWrite(dirPin1, LOW);
    }

    if (force2 > 0) {
      digitalWrite(dirPin2, HIGH);
    } else {
      digitalWrite(dirPin2, LOW);
    }

    // Compute the duty cycle required to generate Tp (torque at the motor pulley)
    duty1= sqrt(abs(Tp1) / 2);
    duty2 = sqrt(abs(Tp2) / 2);
    
    // Serial.print("duty1: ");
    // Serial.println(duty1);
    // Serial.print("duty2: ");
    // Serial.println(duty2);

    // Make sure the duty cycle is between 0 and 100%
    if (duty1 > 1) {
      duty1 = 1;
    } else if (duty1 < 0) {
      duty1 = 0;
    }
    output1 = (int)(duty1 * 255);  // convert duty cycle to output signal
    analogWrite(pwmPin1, output1); // output the signal

    if (duty2 > 1) {
      duty2 = 1;
    } else if (duty2 < 0) {
      duty2 = 0;
    }
    output2= (int)(duty2 * 255);  // convert duty cycle to output signal
    analogWrite(pwmPin2, output2);

    // Serial.print("Tp1: ");
    // Serial.println(Tp1);
    // Serial.print("Tp2: ");
    // Serial.println(Tp2);

  }


// Interrupt Handlers 

void ai0() {
// ai0 is activated if DigitalPin nr 2 is going from LOW to HIGH
// Check pin 3 to determine the direction
  if(digitalRead(6)==LOW) {
  counter_inner--;
  }else{
  counter_inner++;
  }
}
   
void ai1() {
// ai0 is activated if DigitalPin nr 3 is going from LOW to HIGH
// Check with pin 2 to determine the direction
  if(digitalRead(5)==LOW) {
  counter_outer--;
  }else{
  counter_outer++;
  }
}
  
// Transmission to Unity
void encoderCounts(){
  if( counter_inner != temp_inner ){
  angle_inner = 0.0867*counter_inner - 0.7223;
  temp_inner = counter_inner;
  }
  if( counter_outer != temp_outer ){
  angle_outer = -0.1041*counter_outer - 0.2213;
  temp_outer = counter_outer;
  }
  char buffer1[32];
  char buffer2[32];

  dtostrf(angle_inner, 6, 2, buffer1);  
  strcat(buffer1, ", ");
  dtostrf(angle_outer, 6, 2, buffer2);
  strcat(buffer1,buffer2);
  Serial.println(buffer1);
  delay(10);

}


 


// --------------------------------------------------------------
// Function to set PWM Freq -- DO NOT EDIT
// --------------------------------------------------------------
void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if (pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch (divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if (pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if (pin == 3 || pin == 11) {
    switch (divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x7; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}

