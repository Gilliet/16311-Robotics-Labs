#define WB 11.5
#define RAD 2.8
task main()
{
	float x = 0;
	float y = 0;
	float pose = 0;
	int time = 0;
	int lenc = nMotorEncoder[motorB];
	int renc = nMotorEncoder[motorC];
	motor[motorB] = 100;
	motor[motorC] = 100;
	float vl;
	float vr;
	while (time < 1000)
	{
		wait1Msec(1);
		time++;
		int newl = nMotorEncoder[motorB];
		int newr = nMotorEncoder[motorC];
		vl = RAD * (newl - lenc) * (PI / 180.0);
		vr = RAD * (newr - renc) * (PI / 180.0);
		renc = newr;
		lenc = newl;
		writeDebugStream("vl:%f,vr:%f, pose:%f\n",x,y,pose);
		float V = (vr + vl) / 2;
		float w = (vr - vl) / WB;
		pose = pose + w / 2;
		x = x + V * cos(pose);
		y = y + V * sin(pose);
		pose = pose + w / 2;
	nxtDisplayTextLine(2,"%f,",x);
	nxtDisplayTextLine(3,"%f",y);
	nxtDisplayTextLine(4,"%f",pose);
	}
	motor[motorB] = 0;
	motor[motorC] = 0;
	while (true) {
	nxtDisplayTextLine(2,"%f,",x);
	nxtDisplayTextLine(3,"%f",y);
	nxtDisplayTextLine(4,"%f",pose);
}
}
