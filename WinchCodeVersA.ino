
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

float current = 0;

s_pull=0;

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



//My aruduino is 10-bit, resolution of ADC is 1024,system voltage is 
//5V, val is the analog value read by the pin. Multiplying the read value by 
// 5/1024 cnverts what that pin reads to voltage we can read
float convert_current(int val){
  return val*5.0/1024.0;
}

void setup(){
  
  // put your setup code here, to run once:
// set pins as outputs
pinMode(M2D1PWM, OUTPUT);
pinMode(M2D2PWM, OUTPUT);
pinMode(M2IN1, OUTPUT);
pinMode(M2IN2, OUTPUT);
pinMode(M1IN1, OUTPUT);
pinMode(M1IN2, OUTPUT);
//Call in encoder pins
pinMode(CoderA, INPUT_PULLUP);
pinMode(CoderB, INPUT_PULLUP);

attachInterrupt(digitalPinToInterrupt(3), encoderp, RISING);
attachInterrupt(digitalPinToInterrupt(2), button , RISING);

Serial.begin(9600);
}

void loop(){

 // read current sensor and wait for the flag, 
 //flag goes off:
 //1) pull winch for x amount fo time
 //2) wait 1 second
 //3) release winch for y ticks
 
current_sensed= analogRead(current_pin);
current= convert_current(current_sensed);
Serial.println(current);

if(button_pressed){

  if(s-pull){
    s_time= millis();
    s_pull = 0;
    w_pull = 1;
  }else if(w_pull){
    w_pull();

    timer = millis();
    if(timer-s_time >=5000){
    s_time = millis();
    w_stop();
    w_pull = 0;
    wait_winch =1;  
    
    }
  }else if(wait_winch){
    timer = millis();
    if(timer-s_time >= 5000){
      wait_winch = 0;
      r_winch = 1;
      
    }
  }else if(r_winch){
    r_winch();

    if (encoderp <= 0){
      w_stop();
      r_winch = 0;
    }
  }
 }
}

void tick_count(){
  if(digitalRead(CoderB) == 1){
    encoderp++;
  }else{
    encoderp--;
  }
}

void button(){
  s_pull = 1;
}


//Error








/Users/garthwestcott/Documents/Arduino/WinchCodeVersA/WinchCodeVersA.ino: In function 'void tick_count()':
WinchCodeVersA:63:3: error: expected initializer before 's_pull'
   s_pull = 1;
   ^~~~~~
/Users/garthwestcott/Documents/Arduino/WinchCodeVersA/WinchCodeVersA.ino: In function 'float current(int)':
WinchCodeVersA:75:3: error: expected initializer before 'val'
   val*5.0/1024.0;
   ^~~
/Users/garthwestcott/Documents/Arduino/WinchCodeVersA/WinchCodeVersA.ino: At global scope:
WinchCodeVersA:86:1: error: expected initializer before 'pinMode'
 pinMode(M2D1PWM, OUTPUT);
 ^~~~~~~
WinchCodeVersA:87:8: error: expected constructor, destructor, or type conversion before '(' token
 pinMode(M2D2PWM, OUTPUT);
        ^
WinchCodeVersA:88:8: error: expected constructor, destructor, or type conversion before '(' token
 pinMode(M2IN1, OUTPUT);
        ^
WinchCodeVersA:89:8: error: expected constructor, destructor, or type conversion before '(' token
 pinMode(M2IN2, OUTPUT);
        ^
WinchCodeVersA:90:8: error: expected constructor, destructor, or type conversion before '(' token
 pinMode(M1IN1, OUTPUT);
        ^
WinchCodeVersA:91:8: error: expected constructor, destructor, or type conversion before '(' token
 pinMode(M1IN2, OUTPUT);
        ^
WinchCodeVersA:93:8: error: expected constructor, destructor, or type conversion before '(' token
 pinMode(CoderA, INPUT_PULLUP);
        ^
WinchCodeVersA:94:8: error: expected constructor, destructor, or type conversion before '(' token
 pinMode(CoderB, INPUT_PULLUP);
        ^
WinchCodeVersA:96:16: error: expected constructor, destructor, or type conversion before '(' token
 attachInterrupt(digitalPinToInterrupt(3), encoderp, RISING);
                ^
WinchCodeVersA:97:16: error: expected constructor, destructor, or type conversion before '(' token
 attachInterrupt(digitalPinToInterrupt(2), button , RISING);
                ^
WinchCodeVersA:99:1: error: 'Serial' does not name a type
 Serial.begin(9600);
 ^~~~~~
WinchCodeVersA:100:1: error: expected declaration before '}' token
 }
 ^
exit status 1
expected initializer before 's_pull'
