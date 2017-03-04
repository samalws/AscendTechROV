#include <Servo.h>
#include <Metro.h>
#include <FlexCAN.h>

Servo grab;
Metro sysTimer = Metro(1);// milliseconds

int laser = 4, valve = 5;
int clawStuff [2] = {12, 13}; //valve + servo for grabbing

FlexCAN CANbus(125000); //change baud rate later
static CAN_message_t msg,rxmsg;
unsigned int txTimer,rxTimer;

void setup() {
  //CAN BUS SETUP
  CANbus.begin();
  sysTimer.reset();
  
  //LASER SETUP
  pinMode(laser, OUTPUT);
  digitalWrite(laser, LOW);
    
  //SERVO SETUP
  grab.attach(23); //revise pin number later
}

typedef struct{
  byte msg [8];
} message;

void getMessage(void) {  
  message rx = {CANbus.read(rxmsg)};
}
byte sendMessage(void) {
  message txmsg;
  return 0;
}


void claw(int motor, int value) {
    analogWrite(clawStuff[motor], value);    
}

//PROCESS TLC INPUT
void processMotor(){ 
  byte motor = 2*Serial3.read();
  char value = map(Serial3.read(),0,255,-128,127);
  int a, b;
  if (value < 0) {
    a = map(-long(value), 0, 128, 0, 4095);
    b = 0;
  } else {
    a = 0;
    b = map(long(value), 0, 127, 0, 4095);
  }

//  Tlc.set(motor,a);
//  Tlc.set(motor+1,b);
}

void shineLaser() {  
  digitalWrite(laser, HIGH);
}
void servoSet(){
//  byte servIndex = getMessage();
//  byte servValue = map(servIndex, 0, 255, 0, 180);
//  switch (servIndex){
//    case 0: grab.write(servValue); break;
//  }
}

void tetherProcess(){
  switch(Serial3.read()){		//PROCESS COMMAND
    case 0: processMotor();break;				//TLC INPUT
    case 4: servoSet();break;					//SET SERVO INPUTS
  }
}

void loop(){ 
  if(Serial3.available()>0){tetherProcess();}
}
