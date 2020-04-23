# Winch-Code
Arduino based code meant to drive winch motor.

// Make winch pull at constant force, measure current then unwind the winch



//calling pins
const int M2D1PWM = 6;
const int M2D2PWM = 5;
const int M2IN1 = 9;
const int M2IN2 = 11;
const int M1IN1 = 8;
const int M1IN2 = 10;
const int CoderA = 3;
const int CoderB = 2;
const int current_pin = A0;


volatile long encoderp = 0;

const int wspeed = 100;

int current_sensed = 0; // not constant
//float current = 0;

const int button = 3;

//this function stops sending power to pins to reverse direction
void blank(){
  digitalWrite(M1IN1, LOW);
  digitalWrite(M1IN2, LOW);
}

void forward(){
  blank();
  //Having both HIGH will burn out adruino
  digitalWrite(M1IN1, HIGH);
  digitalWrite(M2IN2, LOW);
}

void backward(){
  blank();
  digitalWrite(M1IN1, LOW);
  digitalWrite(M1IN2, HIGH);
}

void w_pull(int speed){
  forward();
  analogWrite(M2D2PWM, wspeed);
}

void w_stop(){
  blank();
  analogWrite(M2D2PWM, 0);
}

void tick_count(){
  if(digitalRead(CoderB) == 1){
    encoderp++;
  }else{
    encoderp--;
  }
  void button(){
  s_pull = 1;
}
}


//My aruduino is 10-bit, resolution of ADC is 1024,system voltage is 
//5V, val is the analog value read by the pin. Multiplying the read value by 
// 5/1024 cnverts what that pin reads to voltage we can read
float current(int val){
  return val*5.0/1024.0;

 void convert_current(int val){
  val*5.0/1024.0;
 } 
 
