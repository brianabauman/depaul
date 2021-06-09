//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#include "RVO.h"

// Modify This File

Vect2D::Vect2D()
	: x(0.0f), y(0.0f)
{
};

Vect2D::Vect2D(const float inX, const float inY)
	: x(inX), y(inY)
{
};

void Vect2D::setX(const float inX)
{
	this->x = inX;
};

void Vect2D::setY(const float inY)
{
	this->y = inY;
};

float Vect2D::getX() const
{
	return this->x;
};

float Vect2D::getY() const
{
	return this->y;
};

const Vect2D Vect2D::operator + (const Vect2D &tmp) const
{
	return Vect2D(x + tmp.x, y + tmp.y);
};

const Vect2D Vect2D::operator - (const Vect2D &tmp) const
{
	return Vect2D(x - tmp.x, y - tmp.y);
};

const Vect2D Vect2D::operator * (const float scale) const
{
	return Vect2D(x * scale, y * scale);
};

// Assume scale != 0.0f
const Vect2D Vect2D::operator / (const float scale) const
{
	return Vect2D(x / scale, y / scale);
};

// ---  End of File ---------------
