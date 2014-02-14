#include "RobotModel.h"
#include "RobotModel.c"
//#define K .009
#define D -3


int vtop (float v) {
	return (int)((102.313 * v) + 0.000179047);
}


void driveTo(robotModel* rob, float des_x,float des_y)
{

	/* TURN */
	float goalPose = atan2(des_y - rob->y, des_x - rob->x);
	writeDebugStream("Robot x: %f, Robot y: %f, Robot Pose %f\n",rob->x,rob->y,(rob->pose * 180.0) / PI);
	writeDebugStream("Goal x: %f, Goal y: %f, Goal pose: %f\n",des_x,des_y, (goalPose* 180.0) / PI);
	int LM;
	int RM;
	if (goalPose - rob->pose < 0) {
		LM = -5; // Motor C NEGATIVE
		RM = 5; // Motor B POSITIVE
		} else {
		LM = 5; // Motor B NEGATIVE
		RM = -5; // Motor C POSITIVE
	}
	while (abs(((goalPose)) - ((rob->pose))) > 0.1 && abs(((goalPose)) + ((rob->pose))) > 0.1) {
		update(rob);
		motor[motorC] = RM;
		motor[motorB] = LM;
	//	writeDebugStream("Robot x: %f, Robot y: %f, Robot Pose %f\n",rob->x,rob->y,(rob->pose * 180.0) / PI);
	//	writeDebugStream("Goal x: %f, Goal y: %f, Goal pose: %f\n",des_x,des_y, (goalPose * 180.0) / PI);

	}
	float lastex = 0;
	float lastey = 0;
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
		LM = vtop(outvl);
		RM = vtop(outvr);
		/* STRAIGHT LINE */
		motor[motorC] = RM;
		motor[motorB] = LM;
	}
}

task main()
{
	robotModel rob;
	init(&rob);
	driveTo(&rob, (15.24) * 6.5,0);
	driveTo(&rob, 15.24 * 7, 15.24 * 2);
	driveTo(&rob, 15.24 * 9, 15.24 * 3);
	driveTo(&rob, 15.24 * 13, 15.24 * 1);
}
