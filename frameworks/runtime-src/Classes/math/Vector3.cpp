

#include "Vector3.h"
#include <math.h>

Vector3::Vector3(float a,float b,float c) 
{
	x = a;
	y = b;
	z = c;
}


Vector3 Vector3::operator+(Vector3 &v2)
{
	Vector3 ret(x + v2.x, y + v2.y, z + v2.z);
	return ret;
}

Vector3 Vector3::operator-(Vector3 &v2)
{
	Vector3 ret(x - v2.x, y - v2.y, z - v2.z);
	return ret;
}

float Vector3::operator*(Vector3 &v2)
{
	return x * v2.x+ y * v2.y+ z * v2.z;
}

void Vector3::cross(Vector3 &v2)
{
	cross(*this, v2, *this);
}

void Vector3::cross(Vector3 &v1, Vector3 &v2, Vector3 &dist)
{
	dist.x = v1.y * v2.z - v1.z * v2.y;
	dist.y = v1.z * v2.x - v1.x * v2.z;
	dist.z = v1.x * v2.y - v1.y * v2.x;
}

float Vector3::dot(Vector3 &v2)
{
	return dot(*this, v2);
}

float Vector3::dot(Vector3 &v1, Vector3 &v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

float Vector3::getAngle(Vector3 &v2)
{
	float t = dot(v2);
	t = t / (length()*v2.length());
	return acosf(t);
}

float Vector3::getRotation(Vector3 &v2)
{
	return getAngle(v2)*57.29578049044297;
}

float Vector3::length()
{
	float ret = x * x + y * y + z * z;
	return sqrt(ret);
}

float Vector3::lenghtSq()
{
	float ret = x * x + y * y + z * z;
	return ret;
}
