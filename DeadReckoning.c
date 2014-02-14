#define WB 11.27//11.5
#define RAD 2.7//2.8               //1. over 2. over 3. under
#define R1 30 //10 //-10  //30
#define L1 15//30 //-20  //15
#define R2 52//-50 //70  //52
#define L2 59//-40 //40  //59
#define R3 10//30 //25  //10
#define L3 20//10 //25  //20

float displayDegrees(float degIn){
	if (degIn >= 0){
		while(degIn > 360.0){
		  degIn = degIn - 360.0;
		}
	} else {
	  while(degIn < -360.0){
	    degIn = degIn + 360.0;
	  }
  }
  return degIn;
}


task main()
{
	float x = 0;
	float y = 0;
	float pose = 0;
	int lenc = nMotorEncoder[motorB];
	int renc = nMotorEncoder[motorC];
	int looop = 0;
	float currL = L1;
	float currR = R1;
	while (looop < 3) {
		if (looop == 0) {
			motor[motorB] = R1;//-10;//10;              //numbers for dead reckoning!
			motor[motorC] = L1;//-20;//30;
			currL = L1;
			currR = R1;
			} else if (looop == 1) {
			motor[motorB] = R2;//70;//-50;
			motor[motorC] = L2;//40;//-40;
			currL = L2;
			currR = R2;
			} else if (looop == 2) {
			motor[motorB] = R3;//25;//30;
			motor[motorC] = L3;//25;//10;
				currL = L3;
			currR = R3;
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
			vl = RAD * (newl - lenc) * (PI / 180.0); ////* 1.04*(1.0+(currL)/10000.0);
			vr = RAD * (newr - renc) * (PI / 180.0); //* 1.04*(1.0+(currR)/10000.0);
			renc = newr;
			lenc = newl;
			float V = (vr + vl) / 2;
			float w = (vr - vl) / WB;
			float theta = pose + w * dt / 2;
			x = x + (V * cos(theta) * dt);//*(1.0-((currL+currR)-120.0)/500.0);
			y = y + (V * sin(theta) * dt);//*(1.0-((currL+currR)-120.0)/500.0);
			pose = pose + w;
			nxtDisplayTextLine(2,"%f,",x / 2);
			nxtDisplayTextLine(3,"%f",y / 2);
			nxtDisplayTextLine(4,"%f",(pose * 180.0) / PI);
			writeDebugStream("time:%d, dt:%d\n",time,dt);

		}
		nxtDisplayTextLine(2,"%f,",x / 2);
		nxtDisplayTextLine(3,"%f",y / 2);
		nxtDisplayTextLine(4,"%f",displayDegrees((pose * 180.0) / PI));
		motor[motorB] = 0;
		motor[motorC] = 0;
		wait1Msec(5000);
	}

	while (true) {
		nxtDisplayTextLine(2,"%f,",x/ 2);
		nxtDisplayTextLine(3,"%f",y / 2);
		nxtDisplayTextLine(4,"%f",displayDegrees((pose * 180) / PI));

}
}
