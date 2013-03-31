#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     LightLeft,      sensorLightActive)
#pragma config(Sensor, S3,     LightRight,     sensorLightActive)
#pragma config(Sensor, S4,     IRSeeker,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     motorL,        tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorY,        tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorR,        tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motorT,        tmotorTetrix, openLoop, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include<JoystickDriver.c>

int Temp1 = 0;

void MotorEncoderTarget (int vform, int vleft, int vright, int vpower , int vtime)
{
	nMotorEncoder[motorL] = 0;
	nMotorEncoder[motorR] = 0;

	switch (vform)
	{
		case 1:
			nMotorEncoderTarget[motorL] = vleft;
			nMotorEncoderTarget[motorR] = vright;
			break;
		case 2:
			nMotorEncoderTarget[motorL] = vleft * 115;
			nMotorEncoderTarget[motorR] = vright * 115;
			break;
	}

	if (vleft > 0)
		motor[motorL] = vpower;
	else
		motor[motorL] = -vpower;
	if (vright > 0)
		motor[motorR] = vpower;
	else
		motor[motorR] = -vpower;

	while (nMotorRunState[motorL] != runStateIdle || nMotorRunState[motorR] != runStateIdle)
	{
		nxtDisplayCenteredTextLine(3, "%d", nMotorEncoder[motorL]);
		nxtDisplayCenteredTextLine(4, "%d", nMotorEncoder[motorR]);
		nxtDisplayCenteredTextLine(5, "%d", SensorValue[IRSeeker]);
	}

	motor[motorL] = 0;
	motor[motorR] = 0;
	wait10Msec(vtime);

}

void MoveLift (int vdir, int vdist, int vpower)
{
	switch (vdir)
	{
		case 0:
			break;
		case 1: // Y up
			nMotorEncoder[motorY] = 0;
			nMotorEncoderTarget[motorY] = vdist;
			motor[motorY] = vpower;
			while(nMotorRunState[motorY] != runStateIdle)
				{}
			motor[motorY] = 0;
			break;
		case 2: // Y down
			nMotorEncoder[motorY] = 0;
			nMotorEncoderTarget[motorY] = -vdist;
			motor[motorY] = -vpower;
			while(nMotorRunState[motorY] != runStateIdle)
				{}
			motor[motorY] = 0;
			break;
		case 3: // X up
			break;
		case 4: // X down
			break;
		case 5: // T up
			motor[motorT] = vpower;
			wait1Msec(vdist);
			motor[motorT] = 0;
			break;
		case 6: // T down
			motor[motorT] = -vpower;
			wait1Msec(vdist);
			motor[motorT] = 0;
			break;
	}

	wait10Msec(100);

}

void LineCheck(int vdist)
{
	nMotorEncoder[motorL] = 0;
	nMotorEncoder[motorR] = 0;
	switch(Temp1)
	{
		case 0:
			while (SensorValue[LightLeft] < 40 && (nMotorEncoder[motorL] <= 1000))
			{
				motor[motorL] = 30;
				motor[motorR] = -30;
			}
				motor[motorL] = 0;
				motor[motorR] = 0;
			if(SensorValue[LightLeft] >= 40)
			{
				break;
			}
			while (SensorValue[LightRight] < 40 && (nMotorEncoder[motorR] <= 1000))
			{
				motor[motorL] = -30;
				motor[motorR] = 30;
			}
				motor[motorL] = 0;
				motor[motorR] = 0;
			break;
		case 1:
			while (SensorValue[LightLeft] < 40 && (nMotorEncoder[motorL] <= 1000))
			{
				motor[motorL] = 30;
				motor[motorR] = -30;
			}
				motor[motorL] = 0;
				motor[motorR] = 0;
			if(SensorValue[LightLeft] >= 40)
			{
				break;
			}
			while (SensorValue[LightRight] < 40 && (nMotorEncoder[motorR] <= 1000))
			{
				motor[motorL] = -30;
				motor[motorR] = 30;
			}
				motor[motorL] = 0;
				motor[motorR] = 0;
			break;
		case 2:
			while (SensorValue[LightRight] < 40 && (nMotorEncoder[motorR] <= 1000))
			{
				motor[motorL] = -30;
				motor[motorR] = 30;
			}
				motor[motorL] = 0;
				motor[motorR] = 0;
			if(SensorValue[LightRight] >= 40)
			{
				break;
			}
			while (SensorValue[LightLeft] < 40 && (nMotorEncoder[motorL] <= 1000))
			{
				motor[motorL] = 30;
				motor[motorR] = -30;
			}
				motor[motorL] = 0;
				motor[motorR] = 0;
			break;
		}


	motor[motorL] = 0;
	motor[motorR] = 0;

	wait1Msec(100);

	nMotorEncoder[motorL] = 0;
	nMotorEncoder[motorR] = 0;

	while(nMotorEncoder[motorL] +	nMotorEncoder[motorR] <= vdist * 2)
   {
      if(SensorValue[LightLeft] >= 40)  // If the Light Sensor reads a value less than 45:
      {
        motor[motorL] = 5;                  // Motor B is run at a 60 power level.
				motor[motorR] = 40;                  // Motor C is run at a 20 power level.
      }
      else                               // If the Light Sensor reads a value greater than or equal to 45:
      {
      	if (SensorValue[LightRight] >= 40)
      	{
        	motor[motorL] = 40;                  // Motor B is run at a 20 power level.
					motor[motorR] = 5;   							// Motor C is run at a 60 power level.
				}
				else //commented out b/c it would go straight even if the line isn't found
				{
					motor[motorL] = 30;
					motor[motorR] = 30;
				}
      }
   }
}



task main()
{
	waitForStart();

	wait1Msec(1450);

	MotorEncoderTarget(2, 15, 15, 75, 10);

	if (SensorValue[IRSeeker] < 8)
	{
		MotorEncoderTarget(2, 20.5, 20.5, 75, 10);

		Temp1++;

		if (SensorValue[IRSeeker] < 8)
		{
			MotorEncoderTarget(2, 20.5, 20.5, 75, 10);

			Temp1++;
		}

	}

	wait10Msec(20);
	MotorEncoderTarget(1, 2100, -2100, 60, 30);
	//MotorEncoderTarget(1, (2000 + Temp1*100), (-2000 - Temp1*100), 60, 30);

	if(Temp1 == 1)
	{
		MoveLift(1, 3000, 30);
	}
	else
	{
		MoveLift(1, 600, 30);
	}

	MotorEncoderTarget(2, 28, 28, 70, 30);
	LineCheck(7 * 115);
	motor[motorL] = 0;
	motor[motorR] = 0;

	if(Temp1 == 1)
	{
		MoveLift(2, 1200, 30);
	}
	else
	{
		MoveLift(2, 550, 30);
	}

	MotorEncoderTarget(2, -39, -39, 80, 10);

	MotorEncoderTarget(1, -2100, 2100, 80, 10);

	switch (Temp1)
	{
		case 0:
			MotorEncoderTarget(2, -10, -10, 80, 10);
			break;
		case 1:
			MotorEncoderTarget(2, -30, -30, 80, 10);
			break;
		case 2:
			MotorEncoderTarget(2, -55, -55, 80, 10);
			break;
	}

}
