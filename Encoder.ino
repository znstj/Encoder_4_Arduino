
#include "digitalWriteFast.h"


#define c_RightEncoderInterruptA 5
#define c_RightEncoderInterruptB 4
#define c_RightEncoderPinA 18
#define c_RightEncoderPinB 19



#define LeftEncoderIsReversed
//#define RightEncoderIsReversed

volatile bool _RightEncoderBSet;
volatile long _RightEncoderTicks = 0;
volatile long last_RightEncoderTicks = 0;

volatile bool _LeftEncoderBSet;
volatile long _LeftEncoderTicks = 0;
volatile long last_LeftEncoderTicks = 0;	



volatile double Left_speed = 0;
volatile double Right_speed = 0;
volatile float Left_Speed_Cal = 0;
volatile float Right_Speed_Cal = 0;

#define RISING_ 1
#define FALLING_ 0

// Right encoder

#define c_LeftEncoderInterrupt 1
#define c_LeftEncoderPinA 5
#define c_LeftEncoderPinB 8




volatile long RightEncoderStatus;
volatile long Last_RightEncoderStatus;



volatile long right_count = 0;
volatile long left_count = 0;

void SetupEncoders();

void HandleRightMotorInterruptB()
{
	bool tempA = digitalReadFast(c_RightEncoderPinA);
	bool tempB = digitalReadFast(c_RightEncoderPinB);
	if(tempA && ~tempB) 			RightEncoderStatus = 1;     //AB=10
	else if(tempA && tempB) 		RightEncoderStatus = 2;     //AB=11
	else if(~tempA && tempB) 		RightEncoderStatus = 3;     //AB=01
	else if(~tempA && ~tempB) 		RightEncoderStatus = 4;     //AB=00
	switch(RightEncoderStatus - Last_RightEncoderStatus)
	{
		case 1:		right_count++;
					break;
		case 2:		right_count = right_count + 2;
					break;
		case -3:	right_count++;
					break;
		case -1:	right_count--;
					break;
		case -2:	right_count = right_count - 2;
					break;
		case 3:		right_count--;
					break;
		default:
					break;
	}
	Last_RightEncoderStatus = RightEncoderStatus;
	
	
}


void HandleRightMotorInterruptA()
{
	
	bool tempA = digitalReadFast(c_RightEncoderPinA);
	bool tempB = digitalReadFast(c_RightEncoderPinB);
	if(tempA && ~tempB) 			RightEncoderStatus = 1;     //AB=10
	else if(tempA && tempB) 		RightEncoderStatus = 2;     //AB=11
	else if(~tempA && tempB) 		RightEncoderStatus = 3;     //AB=01
	else if(~tempA && ~tempB) 		RightEncoderStatus = 4;     //AB=00
	switch(RightEncoderStatus - Last_RightEncoderStatus)
	{
		case 1:		right_count++;
					break;
		case 2:		right_count = right_count + 2;
					break;
		case -3:	right_count++;
					break;
		case -1:	right_count--;
					break;
		case -2:	right_count = right_count - 2;
					break;
		case 3:		right_count--;
					break;
		default:
					break;
	}
	Last_RightEncoderStatus = RightEncoderStatus;
	
	
}


void SetupEncoders()
{
  // Quadrature encoders
  // Left encoder

  
  pinMode(c_LeftEncoderPinA, INPUT);      // sets pin A as input
  digitalWrite(c_LeftEncoderPinA, LOW);  // turn on pullup resistors
  pinMode(c_LeftEncoderPinB, INPUT);      // sets pin B as input
  digitalWrite(c_LeftEncoderPinB, LOW);  // turn on pullup resistors
 // attachInterrupt(c_LeftEncoderInterrupt, HandleLeftMotorInterruptA, RISING);
  
  // Right encoder
  pinMode(c_RightEncoderPinA, INPUT);      // sets pin A as input
  digitalWrite(c_RightEncoderPinA, LOW);  // turn on pullup resistors
  pinMode(c_RightEncoderPinB, INPUT);      // sets pin B as input
  digitalWrite(c_RightEncoderPinB, LOW);  // turn on pullup resistors
  attachInterrupt(c_RightEncoderInterruptA, HandleRightMotorInterruptA, CHANGE); 
  attachInterrupt(c_RightEncoderInterruptB, HandleRightMotorInterruptB, CHANGE); 

	
}

void setup()
{

	Serial.begin(57600);
	SetupEncoders();
}

void loop() 
{
	Serial.print(left_count);
	Serial.print("   ");
	Serial.println(right_count);
	
}

