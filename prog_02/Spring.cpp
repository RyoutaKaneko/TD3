#include "Spring.h"


Spring::Spring(){
	transform.x = 0;
	transform.y = 0;
	stiffness = 0.1f;
	damping = 0.9f;
	gravity = 3.0f;
	mass = 4.0f;
	ax = 0;
	ay = 0;
	forceX = 0;
	forceY = 0;
	vx = 0;
	vy = 0;
}

Spring::~Spring(){}

//çXêV
void Spring::Update(int targetX, int targetY, float alpha) {

	forceX = (targetX - transform.x) * stiffness;
	ax = forceX / mass;
	vx = damping * (vx + ax);
	transform.x += vx;
	forceY = (targetY - transform.y) * stiffness;
	forceY += gravity;
	ay = forceY / mass;
	vy = damping * (vy + ay);
	transform.y += vy;
}

void Spring::Draw(float nx,float ny) {
	DrawCircle(transform.x, transform.y, 15, GetColor(255, 255, 255),true);
	DrawLine(transform.x, transform.y, nx, ny,GetColor(255,255,255),true);
}