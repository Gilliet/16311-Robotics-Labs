#define WB 11.27
#define RAD 2.8

float trajx (float t) {
	return (0.5 * cos(t / 10.0) * sin(t / 10.0));
}
float trajy (float t) {
	return (0.2 * sin(t / 10.0) * sin(t / 5.0));
}

int vtop (float v) {
	return (int)((102.313 * v) + 0.000179047);
}

task main()
{

	ClearTimer(T2);
	float t = 0;
	int lastt = time10[T2];
	float des_x;
	float des_y;
	float K = 1; // GAIN
	float x = 0;
	float y = 0;
	float vl;
	float vr;
	float pose = 0;
	int lenc = nMotorEncoder[motorB];
	int renc = nMotorEncoder[motorC];
	while (t < 63.0)
	{
		// DEAD RECKONING
		int newl = nMotorEncoder[motorB];
		int newr = nMotorEncoder[motorC];
		vl = RAD * (newl - lenc) * (PI / 180.0);
		vr = RAD * (newr - renc) * (PI / 180.0);
		renc = newr;
		lenc = newl;
		float V = (vr + vl) / 2.0;
		float w = (vr - vl) / WB;
		float theta = pose + w / 2.0;
		x = x + (V * cos(theta));
		y = y + (V * sin(theta));
		pose = pose + w;
		// END DEAD RECKONING

		// TRAJECTORY
		wait1Msec(10);
		t += (time10[T2] - lastt) / 100.0;
		lastt = time10[T2];
		des_x = -100;
		des_y = -100;
		// END TRAJECTORY

		nxtDisplayTextLine(2,"%f,",des_x);
		nxtDisplayTextLine(3,"%f",des_y);
		nxtDisplayTextLine(4,"%f",(pose*180.0)/PI);
		float dx = K * (des_x - x);
		float dy = K * (des_y - y);
		float outV = cos(pose) * dx + sin(pose) * dy;
		float outw = cos(pose) * dy - sin(pose) * dx;
		float outvl = outV + WB * outw / 2;
		float outvr = outV - WB * outw / 2;
		int LM = vtop(outvl);
		int RM = vtop(outvr);
		motor[motorC] = LM;
		motor[motorB] = RM;
	}


}
