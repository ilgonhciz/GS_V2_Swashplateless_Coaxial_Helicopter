// This script test the rpm of the brushless motor and performs a test on the swashplateless prototyp design.   

#include <AS5047P.h>
#include <PulsePosition.h>
#include<math.h>

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// Pin declaration for Teensy (9 by Arduino Uno)
#define AS5047P_CHIP_SELECT_PORT 10  
#define AS5047P_CUSTOM_SPI_BUS_SPEED 100000

#define CHANNEL_1_PIN 3
#define CHANNEL_2_PIN 4
#define CHANNEL_3_PIN 5
#define CHANNEL_4_PIN 6


// initialize a new AS5047P sensor object.
AS5047P as5047p(AS5047P_CHIP_SELECT_PORT, AS5047P_CUSTOM_SPI_BUS_SPEED);
Adafruit_MPU6050 mpu;

byte PWM_PIN = 23; // 3;
byte PWM_PIN_2 = 22;
int pwmValue_motor_1 =118;
int pwmValue_motor_2 = 115;
int moduelate_pwmValue =125;

unsigned long pretime, current_time;
unsigned long time_diff;
float motorAngle;
float previousMotorAngle;
int counter=0;
float rpm;

unsigned long timer = 0;
unsigned long timer_1 = 0;
unsigned long timer_2 = 0;
int angle_offset = 10;
int modulation_offset = 0;
int main_loop_duration;
double controlAngle;
PulsePositionInput myIn;
float ppmValues[8];
float throttle_motor_1, throttle_motor_2, pitch, roll, yaw;
sensors_event_t a, g, temp;
volatile unsigned long timer_start1;
volatile int last_interrupt_time1;
volatile unsigned long timer_start2;
volatile int last_interrupt_time2;
volatile unsigned long timer_start3;
volatile int last_interrupt_time3;
volatile unsigned long timer_start4;
volatile int last_interrupt_time4;

long channel_1_pulse_time = 0;
long channel_2_pulse_time = 0;
long channel_3_pulse_time = 0;
long channel_4_pulse_time = 0;
boolean OmnibusAsFC = true; 

// arduino setup routine
void setup() {
  //TCCR2B = TCCR2B & B11111000 | B00000010; // for PWM frequency of 31372.55 Hz
  timer_start1 = 0; 
  timer_start2 = 0; 
  timer_start3 = 0; 
  timer_start4 = 0; 
    
    
  attachInterrupt(CHANNEL_1_PIN, calcSignal1, CHANGE);
  attachInterrupt(CHANNEL_2_PIN, calcSignal2, CHANGE);
  attachInterrupt(CHANNEL_3_PIN, calcSignal3, CHANGE);
  attachInterrupt(CHANNEL_4_PIN, calcSignal4, CHANGE);
  
  analogWriteFrequency(PWM_PIN,4000);
  analogWriteFrequency(PWM_PIN_2,500);
  myIn.begin(15);  
  // initialize the serial bus for the communication with your pc.
  Serial.begin(115200);
  analogWrite(PWM_PIN, pwmValue_motor_1);
  analogWrite(PWM_PIN_2, pwmValue_motor_2); 
  
  // initialize the AS5047P sensor and hold if sensor can't be initialized..
  while (!as5047p.initSPI()) {
    Serial.println(F("Can't connect to the AS5047P sensor! Please check the connection... "));
    delay(5000);
  }
  //if (!mpu.begin()) {
  //Serial.println("Failed to find MPU6050 chip");
  //while (1) {
   // delay(10);
    //}
  //}
}


void loop() {
    mpu.getEvent(&a, &g, &temp);
    timer_2 = micros();
    getReceiverValues();
    if (OmnibusAsFC){
      getTPRY_Omnibus();
      }
    else{
      getTPRY();  
      }
    
    handleSerial();
    motorAngle = as5047p.readAngleDegree();
    if(micros()-timer > 1000){
      computeRPM();
      timer = micros();
      }
    computeControl();
    manipulateSpeed_Sinus();
    //manipulateSpeed_Sinus();
    //getrpm();

    //Set speed for the ESC
    if(micros()-timer_1 > 1000){
      printInfo();
      timer_1 = micros();
      }
    
    analogWrite(PWM_PIN, moduelate_pwmValue);
    analogWrite(PWM_PIN_2, int((pwmValue_motor_2))); 
    main_loop_duration = micros()- timer_2;
}


void getTPRY(){
  throttle_motor_1 = ppmValues[0]; //2,0,1,3 Flysky  --- 0,1,2,3 Frsky  
  throttle_motor_2 = ppmValues[0];
  roll = ppmValues[1];
  pitch = ppmValues[2];
  yaw = ppmValues[3];
  }

void getTPRY_Omnibus(){
  throttle_motor_1 = channel_1_pulse_time; //2,0,1,3 Flysky  --- 0,1,2,3 Frsky 
  throttle_motor_2 = channel_2_pulse_time;
  roll = channel_4_pulse_time;
  pitch = channel_3_pulse_time;
  }  


void computeControl(){
  int minpwmValue = 140;
  pwmValue_motor_1 = 128 + 128 * normalizeThrottle(throttle_motor_1);
  pwmValue_motor_2 = 128 + 128*1.3 * normalizeThrottle(throttle_motor_2);
  
  if (pwmValue_motor_1 > minpwmValue){
    modulation_offset = 0.7*(pwmValue_motor_1-minpwmValue) * sqrt(pow(normalizePRY(pitch),2) + pow(normalizePRY(roll),2) );
  }else{
    modulation_offset = 0;
    }
  controlAngle = atan2(-normalizePRY(pitch), -normalizePRY(roll));  //- for pitch to correct the upside down effect
  
  if (controlAngle > 0 ){
    angle_offset = 180*float(controlAngle)/PI;
  }else{
    angle_offset = 360 + 180*float( controlAngle)/PI;
    }

  }

int calibration_offset = 100;

void manipulateSpeed(){
    //changing speed using the serial inputs 
    if((int(motorAngle)+angle_offset+calibration_offset)%360 > 180){
        moduelate_pwmValue = pwmValue_motor_1 + modulation_offset; 
      }
    else{
        moduelate_pwmValue = pwmValue_motor_1 - modulation_offset; 
      }
  } 
void manipulateSpeed_Sinus(){
    //Serial.println(sin((int(motorAngle)+angle_offset)));
    moduelate_pwmValue = pwmValue_motor_1+int(modulation_offset*sin((motorAngle+angle_offset+calibration_offset)/180 * PI));
  }

void manipulateSpeed_Sinus_V2(){
    //Serial.println(sin((int(motorAngle)+angle_offset)));
    //moduelate_pwmValue = pwmValue+int(modulation_offset*sin(inverse_rotion_pos_func( (int(motorAngle)+angle_offset),rpm )));
  }

  
void getrpm(){
    // An alternative way to determine the rpm
    if (abs(motorAngle-previousMotorAngle) > 300){
        current_time = micros();
        time_diff = current_time - pretime;
        rpm = 10e5/time_diff ;
        pretime = current_time;                       
      }
  }
