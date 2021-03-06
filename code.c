#pragma config(Sensor, in1,    upcoming,       sensorLineFollower)
#pragma config(Sensor, in2,    center,         sensorLineFollower)
#pragma config(Sensor, in3,    L,              sensorLineFollower)
#pragma config(Sensor, in4,    R,              sensorLineFollower)
#pragma config(Sensor, in5,    light,          sensorReflection)
#pragma config(Sensor, dgtl1,  begin,          sensorTouch)
#pragma config(Sensor, dgtl2,  greenL,          sensorLEDtoVCC)
#pragma config(Sensor, dgtl3,  redL,            sensorLEDtoVCC)
#pragma config(Motor,  port1,           Flashlight,    tmotorVexFlashlight, openLoop, reversed)
#pragma config(Motor,  port2,           FR,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           BR,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           BL,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           FL,            tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

void pause();
void approach();
void calc();
void turn(int direction);
float threshhold = 0;
float motorspeed = 0;
void calc(){
	// set the threashhold on each run
	float threshhold= (((SensorValue[L]+SensorValue[R])/2)+(SensorValue[center]+SensorValue[upcoming])/2)/2;
}
void approach (){
	if (SensorValue[upcoming]>= threshhold){wait(0.1); motorspeed=motorspeed/2; startMotor (motor[FL], motorspeed); startMotor (motor[BL], motorspeed); startMotor (motor[BR], motorspeed); startMotor (motor[BL], motorspeed);
	}  else{motorspeed=127;}
}
void turn(int direction){
	if (direction == 1)
	{while(SensorValue[L]>=threshhold){startMotor(BL, -motorspeed); startMotor(FL, -motorspeed);}motorspeed=127;}
	else
	{if(direction == -1){while(SensorValue[R]>=threshhold){startMotor(BR, motorspeed); startMotor(FR, motorspeed);}motorspeed=127;}
	}
}
//stop at bar
void pause(){calc();
	wait(0.1);
	if (SensorValue[center]>=threshhold&SensorValue[L]>=threshhold&SensorValue[R]>=threshhold){stopMotor(BL);stopMotor(FL);stopMotor(FR);stopMotor(BR);}
	//wait to be told to resume
	while (SensorValue[begin]!=1){turnLEDOn(redL);}
	turnLEDOff(redL);
	}
task main()
{// waiting to start
	while(SensorValue[begin]==0)
	{
		if(SensorValue[begin]==1)
		{calc(); motorspeed=127; break;}
	}
	// control loop
	while (true){
		if(SensorValue[upcoming]>=threshhold)
		{
			approach();
		}
		if(SensorValue[L]<=threshhold){turn(1);}
		if(SensorValue[R]<=threshhold){turn(-1);}
		startMotor (motor[FL], motorspeed); startMotor (motor[BL], motorspeed); startMotor (motor[BR], motorspeed); startMotor (motor[BL], motorspeed);
		if(SensorValue[light]<=3050){turnFlashlightOn(Flashlight, 20);wait(0.1);calc();}
		if(SensorValue[light]>=3050){turnFlashlightOff(Flashlight);wait(0.1);calc();}
	}pause();
}
