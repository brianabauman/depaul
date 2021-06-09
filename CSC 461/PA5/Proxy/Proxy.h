//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#ifndef PROXY_H
#define PROXY_H

// Modify This File

class Vect2D
{
public:
	Vect2D(const Vect2D &tmp) { Trace::out("contructor\n"); };
	Vect2D &operator =(const Vect2D &tmp) P ;
	Vect2D() = default;
	~Vect2D() = default;

	Vect2D(const float inX, const float inY);

	void setX(const float inX);
	void setY(const float inY);
	void set(const float inX, const float inY);

	float getX() const;
	float getY() const;

	//-----------------------------------------------
	// Rules   this function cannot be inlined 
	//         or implemented directly
	//-----------------------------------------------
	//  Vect2D operator + (const Vect2D &tmp) const;
	//-----------------------------------------------

private:
	float x;
	float y;

	//-----------------------------------------------
	// Add friends here... if you want (hint)
	//-----------------------------------------------
	friend struct Vadd2;
	friend struct Vadd3;
	friend struct Vadd4;
	friend struct Vadd5;
	friend struct Vadd6;
	friend struct Vadd7;
	friend struct Vadd7;
	friend struct Vadd8;
	friend struct Vadd9;
	friend struct Vadd10;
};

struct Vadd2
{
public:
	Vadd2() = delete;
	~Vadd2() = default;
	Vadd2(const Vadd2 &) = default;
	Vadd2 operator = (const Vadd2 &) = delete;

	Vadd2(const Vect2D &v1, const Vect2D &v2)
		: v1(v1), v2(v2)
	{

	};

	operator Vect2D()
	{
		return Vect2D(this->v1.x + this->v2.x, this->v1.y + this->v2.y);
	};

private:
	const Vect2D v1;
	const Vect2D v2;

	friend struct Vadd3;
};

inline Vadd2 operator + (const Vect2D &v1, const Vect2D &v2)
{
	return Vadd2(v1, v2);
};

struct Vadd3
{
public:
	Vadd3() = delete;
	~Vadd3() = default;
	Vadd3(const Vadd3 &) = default;
	Vadd3 operator = (const Vadd3 &) = delete;

	Vadd3(const Vadd2 &vv1, const Vect2D &v3)
		: v1(vv1.v1), v2(vv1.v2), v3(v3)
	{

	};

	operator Vect2D()
	{
		return Vect2D(this->v1.x + this->v2.x + this->v3.x, this->v1.y + this->v2.y + this->v3.y);
	};

private:
	const Vect2D v1;
	const Vect2D v2;
	const Vect2D v3;

	friend struct Vadd4;
};

inline Vadd3 operator + (const Vadd2 &vv1, const Vect2D &v2)
{
	return Vadd3(vv1, v2);
};

struct Vadd4
{
public:
	Vadd4() = delete;
	~Vadd4() = default;
	Vadd4(const Vadd4 &) = default;
	Vadd4 operator = (const Vadd4 &) = delete;

	Vadd4(const Vadd3 &vvv1, const Vect2D &v4)
		: v1(vvv1.v1), v2(vvv1.v2), v3(vvv1.v3), v4(v4)
	{

	};

	operator Vect2D()
	{
		return Vect2D(this->v1.x + this->v2.x + this->v3.x + this->v4.x, this->v1.y + this->v2.y + this->v3.y + this->v4.y);
	};

private:
	const Vect2D v1;
	const Vect2D v2;
	const Vect2D v3;
	const Vect2D v4;

	friend struct Vadd5;
};

inline Vadd4 operator + (const Vadd3 &vvv1, const Vect2D &v4)
{
	return Vadd4(vvv1, v4);
};

struct Vadd5
{
public:
	Vadd5() = delete;
	~Vadd5() = default;
	Vadd5(const Vadd5 &) = default;
	Vadd5 operator = (const Vadd5 &) = delete;

	Vadd5(const Vadd4 &vvvv1, const Vect2D &v5)
		: v1(vvvv1.v1), v2(vvvv1.v2), v3(vvvv1.v3), v4(vvvv1.v4), v5(v5)
	{

	};

	operator Vect2D()
	{
		return Vect2D(this->v1.x + this->v2.x + this->v3.x + this->v4.x + this->v5.x, this->v1.y + this->v2.y + this->v3.y + this->v4.y + this->v5.y);
	};

private:
	const Vect2D v1;
	const Vect2D v2;
	const Vect2D v3;
	const Vect2D v4;
	const Vect2D v5;

	friend struct Vadd6;
};

inline Vadd5 operator + (const Vadd4 &vvvv1, const Vect2D &v5)
{
	return Vadd5(vvvv1, v5);
};

struct Vadd6
{
public:
	Vadd6() = delete;
	~Vadd6() = default;
	Vadd6(const Vadd6 &) = default;
	Vadd6 operator = (const Vadd6 &) = delete;

	Vadd6(const Vadd5 &vvvvv1, const Vect2D &v6)
		: v1(vvvvv1.v1), v2(vvvvv1.v2), v3(vvvvv1.v3), v4(vvvvv1.v4), v5(vvvvv1.v5), v6(v6)
	{

	};

	operator Vect2D()
	{
		return Vect2D(this->v1.x + this->v2.x + this->v3.x + this->v4.x + this->v5.x + this->v6.x, this->v1.y + this->v2.y + this->v3.y + this->v4.y + this->v5.y + this->v6.y);
	};

private:
	const Vect2D v1;
	const Vect2D v2;
	const Vect2D v3;
	const Vect2D v4;
	const Vect2D v5;
	const Vect2D v6;
	
	friend struct Vadd7;
};

inline Vadd6 operator + (const Vadd5 &vvvvv1, const Vect2D &v6)
{
	return Vadd6(vvvvv1, v6);
};

struct Vadd7
{
public:
	Vadd7() = delete;
	~Vadd7() = default;
	Vadd7(const Vadd7 &) = default;
	Vadd7 operator = (const Vadd7 &) = delete;

	Vadd7(const Vadd6 &vvvvvv1, const Vect2D &v7)
		: v1(vvvvvv1.v1), v2(vvvvvv1.v2), v3(vvvvvv1.v3), v4(vvvvvv1.v4), v5(vvvvvv1.v5), v6(vvvvvv1.v6), v7(v7)
	{

	};

	operator Vect2D()
	{
		return Vect2D(this->v1.x + this->v2.x + this->v3.x + this->v4.x + this->v5.x + this->v6.x + this->v7.x, this->v1.y + this->v2.y + this->v3.y + this->v4.y + this->v5.y + this->v6.y + this->v7.y);
	};

private:
	const Vect2D v1;
	const Vect2D v2;
	const Vect2D v3;
	const Vect2D v4;
	const Vect2D v5;
	const Vect2D v6;
	const Vect2D v7;

	friend struct Vadd8;
};

inline Vadd7 operator + (const Vadd6 &vvvvvv1, const Vect2D &v7)
{
	return Vadd7(vvvvvv1, v7);
};

struct Vadd8
{
public:
	Vadd8() = delete;
	~Vadd8() = default;
	Vadd8(const Vadd8 &) = default;
	Vadd8 operator = (const Vadd8 &) = delete;

	Vadd8(const Vadd7 &vvvvvvv1, const Vect2D &v8)
		: v1(vvvvvvv1.v1), v2(vvvvvvv1.v2), v3(vvvvvvv1.v3), v4(vvvvvvv1.v4), v5(vvvvvvv1.v5), v6(vvvvvvv1.v6), v7(vvvvvvv1.v7), v8(v8)
	{

	};

	operator Vect2D()
	{
		return Vect2D(this->v1.x + this->v2.x + this->v3.x + this->v4.x + this->v5.x + this->v6.x + this->v7.x + this->v8.x, this->v1.y + this->v2.y + this->v3.y + this->v4.y + this->v5.y + this->v6.y + this->v7.y + this->v8.y);
	};

private:
	const Vect2D v1;
	const Vect2D v2;
	const Vect2D v3;
	const Vect2D v4;
	const Vect2D v5;
	const Vect2D v6;
	const Vect2D v7;
	const Vect2D v8;

	friend struct Vadd9;
};

inline Vadd8 operator + (const Vadd7 &vvvvvvv1, const Vect2D &v8)
{
	return Vadd8(vvvvvvv1, v8);
};

struct Vadd9
{
public:
	Vadd9() = delete;
	~Vadd9() = default;
	Vadd9(const Vadd9 &) = default;
	Vadd9 operator = (const Vadd9 &) = delete;

	Vadd9(const Vadd8 &vvvvvvvv1, const Vect2D &v9)
		: v1(vvvvvvvv1.v1), v2(vvvvvvvv1.v2), v3(vvvvvvvv1.v3), v4(vvvvvvvv1.v4), v5(vvvvvvvv1.v5), v6(vvvvvvvv1.v6), v7(vvvvvvvv1.v7), v8(vvvvvvvv1.v8), v9(v9)
	{

	};

	operator Vect2D()
	{
		return Vect2D(this->v1.x + this->v2.x + this->v3.x + this->v4.x + this->v5.x + this->v6.x + this->v7.x + this->v8.x + this->v9.x, this->v1.y + this->v2.y + this->v3.y + this->v4.y + this->v5.y + this->v6.y + this->v7.y + this->v8.y + this->v9.y);
	};

private:
	const Vect2D v1;
	const Vect2D v2;
	const Vect2D v3;
	const Vect2D v4;
	const Vect2D v5;
	const Vect2D v6;
	const Vect2D v7;
	const Vect2D v8;
	const Vect2D v9;

	friend struct Vadd10;
};

inline Vadd9 operator + (const Vadd8 &vvvvvvv1, const Vect2D &v9)
{
	return Vadd9(vvvvvvv1, v9);
};

struct Vadd10
{
public:
	Vadd10() = delete;
	~Vadd10() = default;
	Vadd10(const Vadd10 &) = default;
	Vadd10 operator = (const Vadd10 &) = delete;

	Vadd10(const Vadd9 &vvvvvvvvv1, const Vect2D &v10)
		: v1(vvvvvvvvv1.v1), v2(vvvvvvvvv1.v2), v3(vvvvvvvvv1.v3), v4(vvvvvvvvv1.v4), v5(vvvvvvvvv1.v5), v6(vvvvvvvvv1.v6), v7(vvvvvvvvv1.v7), v8(vvvvvvvvv1.v8), v9(vvvvvvvvv1.v9), v10(v10)
	{

	};

	operator Vect2D()
	{
		return Vect2D(this->v1.x + this->v2.x + this->v3.x + this->v4.x + this->v5.x + this->v6.x + this->v7.x + this->v8.x + this->v9.x + this->v10.x, this->v1.y + this->v2.y + this->v3.y + this->v4.y + this->v5.y + this->v6.y + this->v7.y + this->v8.y + this->v9.y + this->v10.y);
	};

private:
	const Vect2D v1;
	const Vect2D v2;
	const Vect2D v3;
	const Vect2D v4;
	const Vect2D v5;
	const Vect2D v6;
	const Vect2D v7;
	const Vect2D v8;
	const Vect2D v9;
	const Vect2D v10;
};

inline Vadd10 operator + (const Vadd9 &vvvvvvvv1, const Vect2D &v10)
{
	return Vadd10(vvvvvvvv1, v10);
};

#endif

// ---  End of File ---------------