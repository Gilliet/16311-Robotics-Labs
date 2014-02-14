#ifndef ROBOTMODEL_H
#define ROBOTMODEL

#define WB 11.27
#define RAD 2.8


typedef struct {
	float x;
	float y;
	float pose;
	float V;
	float w;
	float lenc;
	float renc;
	float t;
	float lastt;
}robotModel;

void init (robotModel* rob);
void update (robotModel* rob);
#endif
