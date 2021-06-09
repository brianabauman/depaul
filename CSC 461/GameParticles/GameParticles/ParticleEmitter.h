//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include "Math\Matrix.h"
#include "Math\Vect4D.h"
#include "Particle.h"
#include "Settings.h"

#include <list>

class ParticleEmitter
{
public:
	ParticleEmitter();
	~ParticleEmitter();
	ParticleEmitter(const ParticleEmitter & tmp) = delete;
	ParticleEmitter & operator=(const ParticleEmitter & tmp) = delete;

	void SpawnParticle();
	void update();
	void draw();

	void addParticle(Particle *p);
	void removeParticle(Particle *p);

	void Execute(Vect4D& pos, Vect4D& vel, Vect4D& sc);
	void GoodBye();

private:
	Vect4D	start_position;
	Vect4D	start_velocity;

	Vect4D	vel_variance;
	Vect4D	pos_variance;

	float	max_life;
	int		max_particles;
	int		last_active_particle;
	float	spawn_frequency;
	float	last_spawn;
	float	last_loop;

	// added for speed efficiency
	int bufferCount;
	Particle *headParticle;
	Particle *headUnused;
	float	scale_variance;

	Particle *getUnusedParticle();

private:
	Particle *particleBuffer = new Particle[NUM_PARTICLES];
};

#endif

// End of File
