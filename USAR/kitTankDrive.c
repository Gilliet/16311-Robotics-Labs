
/*--------------------------------------------------------------------------------------------------------*\
|*                                                                                                        *|
|*                                      - NXT Smooth Tank Drive -                                         *|
|*                                            ROBOTC on NXT                                               *|
|*                                                                                                        *|
|*  This program allows you to drive a robot via remote control using the ROBOTC Debugger.                *|
|*  This particular method uses "Tank Drive" where each side is controlled individually like a tank.      *|
|*  This program also ignores low values that would cause your robot to move when the joysticks fail to   *|
|*  return back to exact center.  You may need to play with the 'threshold' value to get it just right.   *|
|*                                                                                                        *|
|*                                        ROBOT CONFIGURATION                                             *|
|*    NOTES:                                                                                              *|
|*                                                                                                        *|
|*    MOTORS & SENSORS:                                                                                   *|
|*    [I/O Port]              [Name]              [Type]              [Description]                       *|
|*    Port A                  motorA              NXT                 Camera motor                        *|
|*    Port B                  motorB              NXT                 Right motor                         *|
|*    Port C                  motorC              NXT                 Left motor                          *|
\*---------------------------------------------------------------------------------------------------4246-*/

#include "JoystickDriver.c"

task main()
{
  int driveThresh = 18;             /* threshold lets us ignore noisy low readings */
  int camEnc = nMotorEncoder[motorA]; //360 counts per rotation
  int cfThresh = camEnc;
  int cbThresh = camEnc + 180; //put tolerances in these guys
	while(true)
	{
		getJoystickSettings(joystick);

		//Driving!
		if(abs(joystick.joy1_y2) > driveThresh){
			motor[motorB] = -joystick.joy1_y2;         // Motor B is assigned a power level equal to the right analog stick's Y-axis reading.
			}else{
			motor[motorB] = 0;                        // Motor B is stopped with a power level of 0.
		}


		if(abs(joystick.joy1_y1) > driveThresh){
			motor[motorC] = -joystick.joy1_y1;         // Motor C is assigned a power lev;el equal to the left analog stick's Y-axis reading.
		}else{
			motor[motorC] = 0;                        // Motor C is stopped with a power level of 0.
		}

		//Camera!
	  if (joy1Btn(1)!=0 && joy1Btn(2) == 0){
	  	//the number here tells us which button. no idea of the mapping.
	  	//go forward
	  	int newcam = nMotorEncoder[motorA];
	  			motor[motorA] = 10;

		}

		else if (joy1Btn(1)==0 && joy1Btn(2) != 0){
	  	//go backward
	  	int newcam = nMotorEncoder[motorA];
	  		motor[motorA] = -10;

		} else {
			motor[motorA] = 0;
		}

  }
}
