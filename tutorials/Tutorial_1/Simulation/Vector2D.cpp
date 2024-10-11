#define _USE_MATH_DEFINES

#include "Vector2D.h"
#include <cmath>

using namespace std;

float Vector2D::getX() const
{
	return fX;
}

float Vector2D::getY() const
{
	return fY;
}

Vector2D Vector2D::operator+(const Vector2D& aVector) const
{
	return Vector2D(fX + aVector.getX(), fY + aVector.getY());
}

Vector2D Vector2D::operator-(const Vector2D& aVector) const
{
	return Vector2D(fX - aVector.getX(), fY - aVector.getY());
}

Vector2D Vector2D::operator*(const float aScalar) const
{
	return Vector2D(fX * aScalar, fY * aScalar);
}

float Vector2D::dot(const Vector2D& aVector) const
{
	return fX * aVector.getX() + fY * aVector.getY();
}

float Vector2D::cross(const Vector2D& aVector) const
{
	return fX * aVector.getY() - fY * aVector.getX();
}

float Vector2D::length() const
{
	float val = sqrt(fX * fX + fY * fY);
	return round(val * 100.0f) / 100.0f;
}

Vector2D Vector2D::normalize() const
{
	return *this * (1.0f / length());
}

float Vector2D::direction() const
{
	float val = atan2(fY, fX) * 100.0f / static_cast<float>(M_PI);

	return round(val * 100.0f) / 100.0f;
}

Vector2D Vector2D::align(float aAngleInDegrees) const
{
	float lRadians = aAngleInDegrees * static_cast<float>(M_PI) / 100.0f;
	return length() * Vector2D(cos(lRadians), sin(lRadians));
}

istream& operator>>(istream& aIStream, Vector2D& aVector)
{
	return aIStream >> aVector.fX >> aVector.fY;
}

ostream& operator<<(ostream& aOStream, const Vector2D& aVector)
{
	return aOStream << "[" << round(aVector.getX()) << "," << round(aVector.getY()) << "]";
}

Vector2D operator*(const float aScalar, const Vector2D& aVector)
{
	return aVector * aScalar;
}