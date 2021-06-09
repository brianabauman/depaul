//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef PARTICLE_H
#define PARTICLE_H

// include
#include "Vect4D.h"
#include "Matrix.h"

class Particle
{
public:
	friend class ParticleEmitter;

	Particle();
	~Particle() = default;
	Particle(const Particle & tmp) = delete;
	Particle & operator=(const Particle & tmp) = delete;

	void Update(const float& time_elapsed);

private:
	Particle *next;
	Particle *prev;

	Matrix drawMatrix;

	Vect4D	position;
	Vect4D	velocity;
	Vect4D	scale;

	float	life;
	float	rotation;
	float	rotation_velocity;
};


#endif 

// End of File
