volatile long temp_inner, temp_outer, counter_inner = 0, counter_outer = 0; //This variable will increase or decrease depending on the rotation of encoder
float angle_inner, angle_outer;
void setup() {
  Serial.begin (9600);

  pinMode(2, INPUT_PULLUP); 
  pinMode(3, INPUT_PULLUP); 
  pinMode(6, INPUT_PULLUP); 
  pinMode(5, INPUT_PULLUP);

  attachInterrupt(0, ai0, RISING);
  attachInterrupt(1, ai1, RISING);
  }
   
  void loop() {
  // Send the value of counter
  if( counter_inner != temp_inner ){
  // Serial.print("inner:");
  angle_inner = 0.0867*counter_inner - 0.7223;
  // Serial.println (angle_inner);
  temp_inner = counter_inner;
  }
  if( counter_outer != temp_outer ){
  // Serial.print("outer:");
  angle_outer = -0.1041*counter_outer - 0.2213;
  // double angle_outer = -0.0663*counter_outer - 3.4483;
  // Serial.println (angle_outer);
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

