//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#ifndef RVO_H
#define RVO_H

// Modify This File

class Vect2D
{
public:
	Vect2D();
	~Vect2D() = default;
	Vect2D(const Vect2D &) = default;
	Vect2D & operator = (const Vect2D &) = default;

	Vect2D(const float inX, const float inY);

	void setX(const float inX);
	void setY(const float inY);

	float getX() const;
	float getY() const;

	//*********************************************************************
	// Convert these methods to Return Value Optimization
	//*********************************************************************

	const Vect2D operator + (const Vect2D &tmp) const;
	const Vect2D operator - (const Vect2D &tmp) const;
	const Vect2D operator * (const float scale) const;
	const Vect2D operator / (const float scale) const;

private:
	float x;
	float y;

};

#endif

// ---  End of File ---------------
