#pragma config(Sensor, S1,     rightSensor,    sensorTouch)
#pragma config(Sensor, S2,     leftSensor,     sensorTouch)
#pragma config(Sensor, S3,     sonarSensor,    sensorSONAR)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define leftSensor S1
#define rightSensor S2
#define sonarSensor S3

task main()
{
	while(false) {
		nxtDisplayTextLine(2,"%f",SensorValue(sonarSensor));
	}
	wait10Msec(400);
	int spd = 20;
	motor[motorC] = spd;
	while(true) {
		nxtDisplayTextLine(2,"%f",SensorValue(sonarSensor));
		if (SensorValue(sonarSensor) < 35&& SensorValue(sonarSensor) > 20) {
			motor[motorB] = 100;
			wait10Msec(40);
			motor[motorB] = 0;
		}
		if (SensorValue(rightSensor) != 0 || SensorValue(leftSensor) != 0) {
			spd *= -1;
			motor[motorC] = spd;
			wait10Msec(20);
		}
	}
}
