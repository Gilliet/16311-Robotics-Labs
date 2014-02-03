#pragma config(Sensor, S3,     lightSensor,         sensorLightActive)

task main()
{
	wait1Msec(50);                        // The program waits 50 milliseconds to initialize the light sensor.

	int onEdge = 45;
	int allLine = 35; // On the line
	int allOff = 65;  // Off the line
	int turnCount = 0;
	while(true)                           // Infinite loop
	{
		int lightVal = SensorValue[lightSensor];
		//int prop = onEdge - SensorValue[lightSensor];
		if (lightVal <= 35) {
			motor[motorB] = -25-turnCount;
			motor[motorC] = 6+turnCount;
			turnCount++;
		}
		else if(lightVal  <= 38) {
			motor[motorB] = -5-turnCount;
			motor[motorC] = 10+turnCount;
			turnCount++;
		}
		else if (lightVal < 40) {
			motor[motorB] = 5-turnCount;
			motor[motorC] = 20+turnCount;
		  turnCount++;
		}
		else if (lightVal <= 42) {
			motor[motorB] = 10;
			motor[motorC] = 25;
		  turnCount = 0;
		}
		else if (lightVal < 45) {
			motor[motorB] = 27;
			motor[motorC] = 30;
		  turnCount = 0;
		}
		else if (lightVal == 45) {
			motor[motorB] = 25;
			motor[motorC] = 25;
		  turnCount = 0;
		}
		else if (lightVal < 55) {
			motor[motorB] = 30;
			motor[motorC] = 28;
		  turnCount = 0;
		}
		else if (lightVal < 65) {
			motor[motorB] = 40;
			motor[motorC] = 0;
		  turnCount = 0;
		}
		else {
			motor[motorB] = 20;
			motor[motorC] = -30;
			turnCount = 0;
		}
		writeDebugStream("LightSensor is : %d\n", lightVal);
		wait1Msec(10);
	}
}
