#pragma config(Sensor, S3,     lightSensor,         sensorLightActive)

task main()
{
	wait1Msec(50);                        // The program waits 50 milliseconds to initialize the light sensor.

	int onEdge = 45;
	int allLine = 35; // On the line
	int allOff = 65;  // Off the line
	while(true)                           // Infinite loop
	{
		int lightVal = SensorValue[lightSensor];
		//int prop = onEdge - SensorValue[lightSensor];
		if (lightVal <= 35) {
			motor[motorB] = -25;
			motor[motorC] = 6;
		}
		else if(lightVal <= 38) {
			motor[motorB] = -5;
			motor[motorC] = 10;
		}
		else if (lightVal < 40) {
			motor[motorB] = 5;
			motor[motorC] = 20;
		}
		else if (lightVal <= 42) {
			motor[motorB] = 5;
			motor[motorC] = 20;
		}
		else if (lightVal < 45) {
			motor[motorB] = 22;
			motor[motorC] = 25;
		}
		else if (lightVal == 45) {
			motor[motorB] = 20;
			motor[motorC] = 20;
		}
		else if (lightVal < 55) {
			motor[motorB] = 30;
			motor[motorC] = 28;
		}
		else if (lightVal < 65) {
			motor[motorB] = 40;
			motor[motorC] = 0;
		}
		else {
			motor[motorB] = 20;
			motor[motorC] = -30;
		}
		writeDebugStream("LightSensor is : %d\n", lightVal);
		wait1Msec(10);
	}
}
