//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#ifndef VECT2D_H
#define VECT2D_H

// DO NOT CHANGE THIS FILE

class Vect2D
{
public:
	Vect2D()
		: x(0.0f), y(0.0f)
	{
	};

	Vect2D( float a, float b)
	: x(a),y(b)
	{
	};

	Vect2D( const Vect2D &tmp)
		: x(tmp.x),y(tmp.y)
	{
	}

	~Vect2D()
	{
	};

	void setX( const float inX )
	{
		this->x = inX;
	};

	void setY( const float inY )
	{
		this->y = inY;
	};

	void set( const float inX, const float inY )
	{
		this->x = inX;
		this->y = inY;
	};

	float getX()
	{
		return this->x;
	};

	float getY()
	{
		return this->y;
	};

	Vect2D operator + ( const Vect2D &tmp ) const;
	Vect2D operator - ( const Vect2D &tmp ) const;
	Vect2D operator * ( const float scale ) const;
	Vect2D operator / ( const float scale ) const;

private:
	float x;
	float y;
};

#endif

// ---  End of File ---------------
