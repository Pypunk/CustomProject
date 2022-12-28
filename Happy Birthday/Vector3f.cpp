#include "pch.h"
#include <cmath>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "Vector3f.h"

Vector3f::Vector3f()
	:Vector3f{0.f,0.f,0.f}
{
}

Vector3f::Vector3f(float x, float y, float z)
	:x{x}
	,y{y}
	,z{z}
{
}

Vector3f::Vector3f(const Point3f& fromPoint, const Point3f& toPoint)
	:Vector3f{ toPoint.x - fromPoint.x,toPoint.y - fromPoint.y,toPoint.z - fromPoint.z }
{
}

Vector3f::Vector3f(const Point3f& point)
	:Vector3f{Point3f{0.f,0.f,0.f},point}
{
}

Vector3f Vector3f::operator-() const
{
	return Vector3f{ -x,-y,-z };
}

Vector3f Vector3f::operator+() const
{
	return Vector3f{ x,y,z };
}

Vector3f& Vector3f::operator*=(float rhs)
{
	x *= rhs;
	y *= rhs;
	z *= rhs;
	return *this;
}

Vector3f& Vector3f::operator/=(float rhs)
{
	*this *= 1 / rhs;
	return *this;
}

Vector3f& Vector3f::operator+=(const Vector3f& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Vector3f& Vector3f::operator-=(const Vector3f& rhs)
{
	*this += -rhs;
	return *this;
}

Vector3f::operator Point3f()
{
	return Point3f{ x,y,z };
}

Point3f Vector3f::ToPoint3f() const
{
	return Point3f{ x,y,z };
}

bool Vector3f::Equals(const Vector3f& other, float epsilon) const
{
	return (abs(x - other.x) < epsilon) && (abs(y - other.y) < epsilon) && (abs(z - other.z) < epsilon);
}

std::string Vector3f::ToString() const
{
	std::stringstream buffer;
	
	buffer << std::fixed;
	buffer << std::setprecision(2);
	buffer << "Vector3f(" << x << ", " << y << ", " << z << ")";

	return buffer.str();
}

float Vector3f::DotProduct(const Vector3f& other) const
{
	return x * other.x + y * other.y + z * other.z;
}

Vector3f Vector3f::CrossProduct(const Vector3f& other) const
{
	return Vector3f{ y * other.z - z * other.y,z * other.x - x * other.z,x * other.y - y * other.x };
}

float Vector3f::Norm() const
{
	return Length();
}

float Vector3f::Length() const
{
	return sqrt(x * x + y * y + z * z);
}

float Vector3f::SquaredLength() const
{
	return x * x + y * y + z * z;
}

float Vector3f::AngleWidth(const Vector3f& other) const
{
	return atan2(x * other.y - other.x * y, x * other.x + y * other.y);
}

Vector3f Vector3f::Normalized(float epsilon) const
{
	float length{ Length() };
	if (length < epsilon)
	{
		return Vector3f{ 0,0,0 };
	}
	else
	{
		return Vector3f{ x / length,y / length,z / length };
	}
}

Vector3f Vector3f::Orthogonal() const
{
	return Vector3f{ z,-y,-x };
}

Vector3f Vector3f::Reflect(const Vector3f& surfaceNormal) const
{
	return (*this) - 2 * (this->DotProduct(surfaceNormal) * surfaceNormal);
}

void Vector3f::Set(float newX, float newY, float newZ)
{
	x = newX;
	y = newY;
	z = newZ;
}

Vector3f operator*(float lhs, Vector3f rhs)
{
	return rhs *= lhs;
}

Vector3f operator*(Vector3f lhs, float rhs)
{
	return lhs *= rhs;
}

Vector3f operator/(Vector3f lhs, float rhs)
{
	return lhs *= (1 / rhs);
}

Vector3f operator+(Vector3f lhs, const Vector3f& rhs)
{
	return lhs += rhs;
}

Vector3f operator-(Vector3f lhs, const Vector3f& rhs)
{
	return lhs += -rhs;
}

bool operator==(const Vector3f& lhs, const Vector3f& rhs)
{
	return (lhs.Equals(rhs));
}

bool operator!=(const Vector3f& lhs, const Vector3f& rhs)
{
	return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& lhs, const Vector3f& rhs)
{
	lhs << rhs.ToString();
	return lhs;
}

Point3f& operator+=(Point3f& lhs, const Vector3f& rhs)
{
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	lhs.z += lhs.z;
	return lhs;
}

Point3f& operator+(Point3f lhs, const Vector3f& rhs)
{
	lhs += rhs;
	return lhs;
}

Point3f& operator-=(Point3f& lhs, const Vector3f& rhs)
{
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	lhs.z -= rhs.z;
	return lhs;
}

Point3f& operator-(Point3f lhs, const Vector3f& rhs)
{
	lhs -= rhs;
	return lhs;
}

Vector3f operator-(const Point3f& lhs, const Point3f& rhs)
{
	Vector3f v{ lhs.x - rhs.x,lhs.y - rhs.y,lhs.z - rhs.z };
	return v;
}
