
#pragma once

class  Vector3 
{
public:
	
	float x;
	float y;
	float z;

public:
	Vector3(float a = 0, float b = 0, float c = 0);

	Vector3 operator+(Vector3 &v2);
	Vector3 operator-(Vector3 &v2);
	float operator*(Vector3 &v2);

	void cross(Vector3 &v2);
	static void cross(Vector3 &v1, Vector3 &v2, Vector3 &dist);
	float dot(Vector3 &v2);
	static float dot(Vector3 &v1,Vector3 &v2);

	float getAngle(Vector3 &v2);
	float getRotation(Vector3 &v2);

	float length();
	float lenghtSq();
};
