#include "RobotModel.h"

void init (robotModel* rob) {
	rob->x = 0.0;
	rob->y = 0.0;
	rob->pose = 0.0;
	rob->V = 0.0;
	rob->w = 0.0;
	rob->lenc = nMotorEncoder[motorC];
	rob->renc = nMotorEncoder[motorB];
	ClearTimer(T2);
	rob->t = time10[T2];
	rob->lastt = time10[T2];
}

void update (robotModel* rob) {
	int newl = nMotorEncoder[motorC];
	int newr = nMotorEncoder[motorB];
	float vl = RAD * (newl - rob->lenc) * (PI / 180.0);
	float vr = RAD * (newr - rob->renc) * (PI / 180.0);
	rob->lenc = newl;
	rob->renc = newr;
	rob->V = (vr + vl) / 2.0;
	rob->w = (vr - vl) / WB;
//	writeDebugStream("%f\n",rob->w);
	float theta = rob->pose + rob->w / 2.0;
	rob->x += (rob->V * cos(theta));
	rob->y += (rob->V * sin(theta));
	rob->pose += rob->w;
	if (rob->pose > 2*PI) {
		rob->pose -= 2*PI;
	} else if (rob->pose < -2*PI) {
		rob->pose += 2*PI;
	}
	float tcurr = time10[T2];
	rob->t += (tcurr - rob->lastt) / 100.0;
	rob->lastt = tcurr;
	nxtDisplayTextLine(2,"x:%f",rob->x);
	nxtDisplayTextLine(3,"y:%f",rob->y);
	nxtDisplayTextLine(4,"pose:%f",((rob->pose) * 180.0) / PI);
}
