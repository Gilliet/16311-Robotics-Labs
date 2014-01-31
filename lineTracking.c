#pragma config(Sensor, S3,     lightSensor,         sensorLightActive)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

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
|*    Port 1                  lightSensor         Light Sensor        Back mounted                        *|
\*---------------------------------------------------------------------------------------------------4246-*/

/*calibrate: returns the average of the measured dark and light values to be used as a threshold.
 *
 */
int calibrate(){
    int darkNum = SensorValue[lightSensor];
    //scoot a little
    motor[motorB] = 60;
    int lightNum = SensorValue[lightSensor];
    //scoot back
    motor[motorB] = -60;
    return (darkNum+lightNum)/2;

}

task main(){
	wait1Msec(50);                        // The program waits 50 milliseconds to initialize the light sensor.
	thresh = calibrate();
	while(true){
		if(SensorValue[lightSensor] < there){
			motor[motorB] = 60;                  // Motor B is run at a 60 power level.
			motor[motorC] = 20;                  // Motor C is run at a 20 power level.
		} else {
			motor[motorB] = 20;                  // Motor B is run at a 20 power level.
			motor[motorC] = 60;                  // Motor C is run at a 60 power level.
		}
	}
}
