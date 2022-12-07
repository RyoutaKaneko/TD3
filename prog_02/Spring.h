#pragma once
#include "Struct.h"
#include "DxLib.h"

class Spring {
public:
	Transform transform;
	float vx, vy;
	float gravity;
	float mass;
	float stiffness;
	float damping;
	float forceX;
	float ax;
	float forceY;
	float ay ;

public:
	Spring();
	Spring(float _x,float _y,float _mass,float _gravity);
	~Spring();
	void Update(int targetX, int targetY, float alpha);
	void Draw(float nx, float ny);
};