#include <AFMotor.h>
#include <Servo.h>
Servo servo;

AF_DCMotor LF(1);
AF_DCMotor LB(2);
AF_DCMotor RF(4);
AF_DCMotor RB(3);
#define trigPin  A0
#define echoPin  A1

void setup()
  {
    servo.attach(10);
    pinMode(trigPin, OUTPUT);          // Declare "trigPin" as "Output Pin". 
    pinMode(echoPin, INPUT);           // Declare "echoPin" as "Input Pin". 
    LF.setSpeed(200);
    LB.setSpeed(200);
    RF.setSpeed(200);
    RB.setSpeed(200);
  }

void loop()
  {
    float distance = 0.00;
    float RightDistance = 0.00;
    float LeftDistance = 0.00;    
    distance = search();  
        
    if(distance <= 30) // If obstracle found in 40 CM.
      {
          RobotStop(); //Robot Stop
          delay(100);
          servo.write(5);
          delay(300);
          RightDistance = search();
          delay(100);
          servo.write(180);
          delay(300);
          LeftDistance = search();
          delay(100);
          servo.write(90);
          delay(300);
         if(LeftDistance > RightDistance)
           { 
              RobotBackward();
              delay(100);
              RobotStop();
              delay(100);
              RobotLeft();
              delay(500);
              RobotStop();
              delay(100);  
           }
          else 
            {
              RobotBackward();
              delay(100);
              RobotStop();
              delay(100);
              RobotRight();
              delay(500); 
              RobotStop();
              delay(100);             
            }
      }
   else
   {
     RobotForward();
   }
}


float search(void)
  {
    float duration = 0.00;             // Float type variable declaration 
    float CM = 0.00;      
    digitalWrite(trigPin, LOW);        // Trig_pin output as OV (Logic Low-Level) 
    delayMicroseconds(2);              // Delay for 2 us    
    //Send 10us High Pulse to Ultra-Sonic Sonar Sensor "trigPin" 
    digitalWrite(trigPin, HIGH);       // Trig_pin output as 5V (Logic High-Level)
    delayMicroseconds(10);             // Delay for 10 us     
    digitalWrite(trigPin, LOW);        // Trig_pin output as OV (Logic Low-Level)    
    duration = pulseIn(echoPin, HIGH); // Start counting time, upto again "echoPin" back to Logical "High-Level" and puting the "time" into a variable called "duration" 
    CM = (duration / 58.82); //Convert distance into CM.     
    return CM;
  }

void RobotForward()
{
  LF.run(FORWARD);
  RF.run(FORWARD);
  LB.run(FORWARD);
  RB.run(FORWARD);
}
void RobotBackward()
{
  LF.run(BACKWARD);
  LB.run(BACKWARD);
  RF.run(BACKWARD);
  RB.run(BACKWARD);
}
void RobotLeft()
{
  LF.run(BACKWARD);
  LB.run(BACKWARD);
  RF.run(FORWARD);
  RB.run(FORWARD);
}
void RobotRight()
{
  LF.run(FORWARD);
  LB.run(FORWARD);
  RF.run(BACKWARD);
  RB.run(BACKWARD);
}
void RobotStop()
{
  LF.run(RELEASE);
  LB.run(RELEASE);
  RF.run(RELEASE);
  RB.run(RELEASE);
}

  
