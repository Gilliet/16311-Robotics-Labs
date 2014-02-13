#define WB 11.27
#define RAD 2.8

float trajx (float t) {
	return (0.5 * cos(t / 10.0) * sin(t / 10.0));
}
float trajy (float t) {
	return (0.2 * sin(t / 10.0) * sin(t / 5.0));
}

/****numbered functions***/

float onex (float t) {
	return (0.5 * cos(t / 10.0) * sin(t / 10.0));
}
float oney (float t) {
	return (0.2 * sin(t / 10.0) * sin(t / 5.0));
}

float twox (float t) {
	return (0.2 * sin((3.0*t) / 5.0));
}
float twoy (float t) {
	return (0.2 * cos(2.0*(t/5.0+PI/4.0)));
}

float threex (float t) {
	return (0.2 * cos(t/10.0)*cos(t/5.0))-0.2;
}
float threey (float t) {
	return (0.2 * cos((3.0*t)/10.0)*sin(t/10.0));
}

float fourx (float t) {
	return (0.2 * (0.5*cos((3.0*t)/10.0)-0.75*cos(t/5.0)) + 0.05);
}
float foury (float t) {
	return (0.2 * (-0.75*sin(t/5.0)-0.5*sin((3.0*t)/10.0)));
}

float fivex (float t) {
	return (0.1*(-2.0*(pow(cos(t/5.0),2.0))-(sin(t/10.0))+1.0)*(sin(t/5.0)));
}

float fivey (float t) {
	return (0.1*(cos(t/5.0))*(-2.0*(pow(cos(t/5.0),3.0))-(sin(t/10.0))+1.0)) + 0.1; //+0.1 is for offset
}

float sixx (float t) {
	return 0.1 * (2.0 * (pow(cos(t / 12.0),3.0)) + 1) * (sin(t / 4.0));
}
float sixy (float t) {
	return 0.1 * (cos(t / 4.0)) * (1 - 2 * (pow(sin(t / 4.0),4.0))) - 0.1;
}

/****end numbered functions***/

int vtop (float v) {
	return (int)((102.313 * v) + 0.000179047);
}

float crazyx (float t) {
	return 0.02 * (5.0 * cos(9.0 * t / 20.0) - 4 * cos(t / 4.0));
}
float crazyy (float t) {
	return 0.02 * (-4.0 * sin(t / 4.0) - 5.0 * sin(9.0 * t / 20.0));
}

float r (float t) {
	return 1 + (((abs(cos(t * 3))) + (0.25 - (abs(cos(t * 3 + PI/2.0)))) * 2.0) / (2.0 + abs(cos(t * 6.0 + PI / 2.0)) * 8));
}

float lotusx (float t) {
	return .5 * r(t) * cos(t);
}
float lotusy (float t) {
	return .5 * r(t) * sin(t);
}


float ninex (float t) {
	if (t < 10) {
		return t * 1.5;
		} else if (10 < t < 20) {
		return (t - 10);
		} else {
		return 10;
	}
}
float niney (float t) {
	if (t < 5) {
		return 0;
		} else  if (5 < t < 15) {
		return -(t-5) * .5;
		} else {
		return 5;
	}
}


task main()
{

	ClearTimer(T2);
	float t = 0;
	float lastt = time10[T2];
	float des_x;
	float des_y;
	float K = .02; // GAIN
	float D = -5;
	float x = 0.0;
	float y = 0;
	float vl;
	float vr;
	float pose = 0;
	int lenc = nMotorEncoder[motorB];
	int renc = nMotorEncoder[motorC];
	float lastex = 0;
	float lastey = 0;
	while (t < 32)
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
		des_x = twox(t) * 100;
		des_y = twoy(t) * 100;
		//		writeDebugStream("%f",des_y);
		// END TRAJECTORY

		float dx = K * (des_x - x); // ERROR
		float dy = K * (des_y - y); // PROPORTIONAL GAIN
		float vx = D * ((dx - lastex) / (t - lastt)); // DIFFERENTIAL GAIN
		float vy = D * ((dy - lastey) / (t - lastt));
		nxtDisplayTextLine(2,"%f,", x);
		nxtDisplayTextLine(3,"%f",y);
		nxtDisplayTextLine(4,"%f",(pose*180.0)/PI);
		lastex = dx;
		lastey = dy;

		writeDebugStream("x:%f,y:%f\n",sixx(0),sixy(0));
		float outV = cos(pose) * (dx + vx) + sin(pose) * (dy + vy);
		float outw = cos(pose) * (dy + vy) - sin(pose) * (dx + vx);
		float outvl = outV + WB * outw / 2;
		float outvr = outV - WB * outw / 2;
		int LM = vtop(outvl);
		int RM = vtop(outvr);
		motor[motorC] = LM;
		motor[motorB] = RM;
	}
	motor[motorC] = 0;
	motor[motorB] = 0;
	while (true) {
		nxtDisplayTextLine(2,"%f,",x);
		nxtDisplayTextLine(3,"%f",y );
		nxtDisplayTextLine(4, "%f", (pose * 180.0) / PI);
	}
}
