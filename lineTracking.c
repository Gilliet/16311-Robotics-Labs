#pragma config(Sensor, S3,     lightSensor,         sensorLightActive)

//1/31/2014: change to line following by slight adjustment

/*--------------------------------------------------------------------------------------------------------*\
|*                                                                                                        *|
|*                                           - Line Tracker -                                             *|
|*                                            ROBOTC on NXT                                               *|
|*                                                                                                        *|
|*  This program allows your taskbot to follow a line in reverse.                                         *|
|*                                                                                                        *|
|*                                        ROBOT CONFIGURATION                                             *|
|*    NOTES:                                                                                              *|
|*    1)  The Light Sensor is attached to the back of the robot.                                          *|
|*    2)  Be sure to take readings of your Light Sensor over the light and dark areas.  Once you have     *|
|*        the values, add them and divide by 2 to find your threshold.  Then, use your threshold as a     *|
|*        comparison in your program.                                                                     *|
|*                                                                                                        *|
|*    MOTORS & SENSORS:                                                                                   *|
|*    [I/O Port]              [Name]              [Type]              [Description]                       *|
|*    Port B                  motorB              NXT                 Right motor                         *|
|*    Port C                  motorC              NXT                 Left motor                          *|
|*    Port 3                  lightSensor         Light Sensor        Back mounted                        *|
\*---------------------------------------------------------------------------------------------------4246-*/

#define LEFT_MOTOR motorB;
#define RIGHT_MOTOR motorC;
/*calibrate: returns the average of the measured dark and light values to be used as a threshold.
 *
 */
int calibrate(){
    int darkNum = SensorValue[lightSensor];
    //scoot a little
	motor[motorB] = 60;
	wait1Msec(50);
	motor[motorB] = 0;
	int lightNum = SensorValue[lightSensor];
	//scoot back
	motor[motorB] = -60;
	wait1Msec(50);
	motor[motorB] = 0;
	return (darkNum+lightNum)/2;
}

task main(){
	wait1Msec(50);  //wait 50 milliseconds to initialize the light sensor.
	//int thresh = calibrate();
	int thresh = 45;
	int turnRight = 0;
	while(true){
		if(SensorValue[lightSensor] < thresh){ //dark!
			//go straight-ish with a bit of right
			motor[motorB] = 40;
			motor[motorC] = 25;
			} else {
			while (SensorValue[lightSensor] > 45){
				//turn sharply left
				motor[motorB] = -10;
				motor[motorC] = 20;
			}
		}
		/*
		int waitCtr = 400;
		while(SensorValue[lightSensor] > 45){
		if (turnRight){
		motor[motorB] = 50;
		motor[motorC] = -20;
		turnRight = 0;
		} else {
		motor[motorC] = 50;
		motor[motorB] = -20;
		turnRight = 1;
		}
		int time = 0;
		while (SensorValue[lightSensor] > 45 && time < waitCtr)
		{
		time++;
		wait1Msec(1);
		}
		waitCtr +=700;
		}
		*/
	}
}
