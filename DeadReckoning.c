#define WB 11.5
#define RAD 2.8
task main()
{
	float x = 0;
	float y = 0;
	float pose = 0;
	int lenc = nMotorEncoder[motorB];
	int renc = nMotorEncoder[motorC];
	int looop = 0;
	while (looop < 3) {
		if (looop == 0) {
			motor[motorB] = 10;
			motor[motorC] = 30;
			} else if (looop == 1) {
			motor[motorB] = -50;
			motor[motorC] = -40;
			} else if (looop == 2) {
			motor[motorB] = 30;
			motor[motorC] = 10;
		}
		looop++;
		float vl;
		float vr;
		ClearTimer(T1);
		int time = time1[T1];
		int lasttime = time;
		while (time < 5000)
		{
			wait1Msec(1);
			time = time1[T1];
			int dt = time - lasttime;
			lasttime = time;
			int newl = nMotorEncoder[motorB];
			int newr = nMotorEncoder[motorC];
			vl = RAD * (newl - lenc) * (PI / 180.0);
			vr = RAD * (newr - renc) * (PI / 180.0);
			renc = newr;
			lenc = newl;
			float V = (vr + vl) / 2;
			float w = (vr - vl) / WB;
			float theta = pose + w * dt / 2;
			x = x + V * cos(theta) * dt;
			y = y + V * sin(theta) * dt;
			pose = pose + w;
			nxtDisplayTextLine(2,"%f,",x / 2);
			nxtDisplayTextLine(3,"%f",y / 2);
			nxtDisplayTextLine(4,"%f",(pose * 180.0) / PI);
			writeDebugStream("time:%d, dt:%d\n",time,dt);

		}
		nxtDisplayTextLine(2,"%f,",x / 2);
		nxtDisplayTextLine(3,"%f",y / 2);
		nxtDisplayTextLine(4,"%f",(pose * 180.0) / PI);
		motor[motorB] = 0;
		motor[motorC] = 0;
		wait1Msec(5000);
	}

	while (true) {
		nxtDisplayTextLine(2,"%f,",x/ 2);
		nxtDisplayTextLine(3,"%f",y / 2);
		nxtDisplayTextLine(4,"%f",(pose * 180) / PI);

}
}
