#include "RobotModel.h"
#include "RobotModel.c"
#define K .009
#define D -.1

#define SPEED1 20
#define SPEED2 45
#define SPEED3 70
int vtop (float v) {
	return (int)((102.313 * v) + 0.000179047);
}


void driveTo(robotModel* rob, float des_x,float des_y)
{

	/* TURN
	float goalPose = (atan2(des_y - rob->y, des_x - rob->x)); // Goal pose is relative to current pose.
	writeDebugStream("Robot x: %f, Robot y: %f, Robot Pose %f\n",rob->x,rob->y,(rob->pose * 180.0) / PI);
	writeDebugStream("Goal x: %f, Goal y: %f, Goal pose: %f\n",des_x,des_y, (goalPose* 180.0) / PI);
	writeDebugStream ("Delta x: %f, Delta y: %f\n",des_x - rob->x,des_y - rob->y);
	int LM;
	int RM;
	float startPose = rob->pose;
	if (goalPose > 0) {
	writeDebugStream("GOING LEFT\n");
	LM = -10; // Motor C NEGATIVE
	RM = 10; // Motor B POSITIVE
	while (abs((rob->pose - startPose) - goalPose) > 0.1) {
	update(rob);
	motor[motorC] = LM;
	motor[motorB] = RM;
	//	writeDebugStream("Robot x: %f, Robot y: %f, Robot Pose %f\n",rob->x,rob->y,(rob->pose * 180.0) / PI);
	//	writeDebugStream("Goal x: %f, Goal y: %f, Goal pose: %f\n",des_x,des_y, (goalPose * 180.0) / PI);

	}
	} else {
	writeDebugStream("GOING RIGHT\n");
	LM = 10; // Motor B NEGATIVE
	RM = -10; // Motor C POSITIVE
	while (abs((startPose - rob->pose) + goalPose) > 0.1) {
	writeDebugStream("delta Pose: %f\n", rob->pose - startPose);
	update(rob);
	motor[motorC] = LM;
	motor[motorB] = RM;
	//	writeDebugStream("Robot x: %f, Robot y: %f, Robot Pose %f\n",rob->x,rob->y,(rob->pose * 180.0) / PI);
	//	writeDebugStream("Goal x: %f, Goal y: %f, Goal pose: %f\n",des_x,des_y, (goalPose * 180.0) / PI);

	}
	}
	*/
	float lastex = 0;
	float lastey = 0;
	int lastR = 0;
	int lastL = 0;
	float startt = rob->t;
	while (abs(des_x - rob->x) > 2 || abs(des_y - rob->y) > 2) {
		update(rob);
		float dx = K * (des_x - rob->x); // ERROR
		float dy = K * (des_y - rob->y); // PROPORTIONAL GAIN
		float vx = D * ((dx - lastex) / (rob->t - rob->lastt)); // DIFFERENTIAL GAIN
		float vy = D * ((dy - lastey) / (rob->t - rob->lastt));
		lastex = dx;
		lastey = dy;

		float outV = cos(rob->pose) * (dx + vx) + sin(rob->pose) * (dy + vy);
		float outw = cos(rob->pose) * (dy + vy) - sin(rob->pose) * (dx + vx);
		float outvl = outV + WB * outw / 2;
		float outvr = outV - WB * outw / 2;
		int LM = vtop(outvl);
		int RM = vtop(outvr);
		/* STRAIGHT LINE */
		if (rob->t - startt < 2 ) {
			if (RM > SPEED1) RM = SPEED1;
			if (RM < -SPEED1) RM = -SPEED1;
			if (LM > SPEED1) LM = SPEED1;
			if (LM < -SPEED1) LM = -SPEED1;
			if (RM > 0 && RM < SPEED1) RM = SPEED1;
			if (RM < 0 && RM > -SPEED1) RM = -SPEED1;
			if (LM > 0 && LM < SPEED1) LM = SPEED1;
			if (LM < 0 && LM > -SPEED1) LM = -SPEED1;
			} else if (rob->t - startt < 4) {
			if (RM > SPEED2) RM = SPEED2;
			if (RM < -SPEED2) RM = -SPEED2;
			if (LM > SPEED2) LM = SPEED2;
			if (LM < -SPEED2) LM = -SPEED2;
			if (RM > 0 && RM < SPEED2) RM = SPEED2;
			if (RM < 0 && RM > -SPEED2) RM = -SPEED2;
			if (LM > 0 && LM < SPEED2) LM = SPEED2;
			if (LM < 0 && LM > -SPEED2) LM = -SPEED2;
			} else {
			if (RM > SPEED3) RM = SPEED3;
			if (RM < -SPEED3) RM = -SPEED3;
			if (LM > SPEED3) LM = SPEED3;
			if (LM < -SPEED3) LM = -SPEED3;
			if (RM > 0 && RM < SPEED1) RM = SPEED1;
			if (RM < 0 && RM > -SPEED1) RM = -SPEED1;
			if (LM > 0 && LM < SPEED1) LM = SPEED1;
			if (LM < 0 && LM > -SPEED1) LM = -SPEED1;
		}
		motor[motorC] = RM;
		motor[motorB] = LM;
		//	writeDebugStream("RM: %d,LM: %d\n",RM,LM);
	}
}
/*
task main()
{
robotModel rob;
init(&rob);
driveTo(&rob, (15.24) * 6.5,0);
driveTo(&rob, 15.24 * 7, 15.24 * 2);
driveTo(&rob, 15.24 * 9, 15.24 * 3);
driveTo(&rob, 15.24 * 13, 15.24 * 1);
}*/
