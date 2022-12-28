#pragma once
#include "structs.h"

struct Vector3f final
{
	Vector3f();
	explicit Vector3f(float x, float y, float z);
	explicit Vector3f(const Point3f& fromPoint, const Point3f& toPoint);
	explicit Vector3f(const Point3f& point);

	Vector3f operator-() const;
	Vector3f operator+() const;
	Vector3f& operator*=(float rhs);
	Vector3f& operator/=(float rhs);
	Vector3f& operator+=(const Vector3f& rhs);
	Vector3f& operator-=(const Vector3f& rhs);
	explicit operator Point3f();

	Point3f ToPoint3f() const;
	bool Equals(const Vector3f& other, float epsilon = 0.001f) const;
	std::string ToString() const;
	float DotProduct(const Vector3f& other) const;
	Vector3f CrossProduct(const Vector3f& other) const;
	float Norm() const;
	float Length() const;
	float SquaredLength() const;
	float AngleWidth(const Vector3f& other) const;
	Vector3f Normalized(float epsilon = 0.001f) const;
	Vector3f Orthogonal() const;
	Vector3f Reflect(const Vector3f& surfaceNormal) const;
	void Set(float newX, float newY, float newZ);

	float x;
	float y;
	float z;
};

Vector3f operator*(float lhs, Vector3f rhs);
Vector3f operator*(Vector3f lhs, float rhs);
Vector3f operator/(Vector3f lhs, float rhs);

Vector3f operator+(Vector3f lhs, const Vector3f& rhs);
Vector3f operator-(Vector3f lhs, const Vector3f& rhs);

bool operator==(const Vector3f& lhs, const Vector3f& rhs);
bool operator!=(const Vector3f& lhs, const Vector3f& rhs);

std::ostream& operator<<(std::ostream& lhs, const Vector3f& rhs);

Point3f& operator+=(Point3f& lhs, const Vector3f& rhs);
Point3f& operator+(Point3f lhs, const Vector3f& rhs);

Point3f& operator-=(Point3f& lhs, const Vector3f& rhs);
Point3f& operator-(Point3f lhs, const Vector3f& rhs);

Vector3f operator-(const Point3f& lhs, const Point3f& rhs);