//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "DO_NOT_MODIFY\OpenGLInterface.h"
#include "Framework.h"

#include "ParticleEmitter.h"
#include "Settings.h"

extern PerformanceTimer GlobalTimer;

static const unsigned char squareColors[] =
{
	// ----------------------------
	//  point is actually a quad   
	//  set color on each vertex   
	// ----------------------------
	//    Vert A = Yellow  
	//    Vert B = Yellow  
	//    Vert C = Yellow  
	//    Vert D = Yellow  
	// ----------------------------

	200,  200,  0,  255,
	200,  200,  0,  255,
	200,  200,  0,  255,
	200,  200,  0,  255,
};

static const float squareVertices[] =
{
	// --------------------
	//   Vert A = (x,y,z)
	//   Vert B = (x,y,z)
	//   Vert C = (x,y,z)
	//   Vert D = (x,y,z)
	// --------------------

	-0.015f,  -0.015f, 0.0, // Size of Triangle
	 0.015f,  -0.015f, 0.0, // Size of Triangle
	-0.015f,   0.015f, 0.0, // Size of Triangle
	 0.015f,   0.015f, 0.0, // Size of Triangle
};

ParticleEmitter::ParticleEmitter()
	: start_position(0.0f, 0.0f, 0.0f),
	start_velocity(0.0f, 1.0f, 0.0f),
	vel_variance(1.0f, 4.0f, 0.4f),
	pos_variance(1.0f, 1.0f, 1.0f),
	max_life(MAX_LIFE),
	max_particles(NUM_PARTICLES),
	last_active_particle(-1),
	spawn_frequency(0.0000001f),
	headParticle(nullptr),
	headUnused(nullptr),
	scale_variance(2.5f)
{
	GlobalTimer.Toc();

	last_spawn = GlobalTimer.TimeInSeconds();
	last_loop = GlobalTimer.TimeInSeconds();

	//create all particles now as "unused"
	for (int i = 0; i < NUM_PARTICLES; i++)
	{
		PLACEMENT_NEW_BEGIN
		#undef new
			Particle *unusedParticle = new(particleBuffer + i) Particle();

		PLACEMENT_NEW_END

		unusedParticle->next = headUnused;
		if (headUnused != nullptr) headUnused->prev = unusedParticle;
		headUnused = unusedParticle;
	}
}

ParticleEmitter::~ParticleEmitter()
{
}

void ParticleEmitter::SpawnParticle()
{
	// create another particle if there are ones free
	if (last_active_particle < max_particles - 1)
	{
		// create new particle
		Particle *newParticle = getUnusedParticle();

		// initialize the particle
		newParticle->life = 0.0f;
		newParticle->position = start_position;
		newParticle->velocity = start_velocity;
		newParticle->scale = Vect4D(2.0, 2.0, 2.0, 1.0);

		// apply the variance
		this->Execute(newParticle->position, newParticle->velocity, newParticle->scale);

		// increment count
		last_active_particle++;

		// add to list
		this->addParticle(newParticle);

	}
}

void ParticleEmitter::update()
{
	// get current time
	GlobalTimer.Toc();
	float current_time = GlobalTimer.TimeInSeconds();

	// spawn particles
	float time_elapsed = current_time - last_spawn;

	// update
	while (spawn_frequency < time_elapsed)
	{
		// spawn a particle
		this->SpawnParticle();
		// adjust time
		time_elapsed -= spawn_frequency;
		// last time
		last_spawn = current_time;
	}

	// total elapsed
	time_elapsed = current_time - last_loop;

	Particle *p = this->headParticle;

	// walk the active particles
	while (p != 0)
	{
		// call every particle and update its position 
		p->Update(time_elapsed);

		// if it's live is greater that the max_life 
		// and there is some on the list 
		// remove node
		if ((p->life > max_life) && (last_active_particle > 0))
		{
			// particle to remove
			Particle *s = p;

			// need to squirrel it away.
			p = p->next;

			// remove last node
			this->removeParticle(s);

			// update the number of particles
			last_active_particle--;
		}
		else
		{
			// increment to next point
			p = p->next;
		}
	}

	last_loop = current_time;
}

void ParticleEmitter::addParticle(Particle *p)
{
	assert(p);
	if (this->headParticle == 0)
	{ // first on list
		this->headParticle = p;
		p->next = 0;
		p->prev = 0;
	}
	else
	{ // add to front of list
		headParticle->prev = p;
		p->next = headParticle;
		p->prev = 0;
		headParticle = p;
	}
}

void ParticleEmitter::removeParticle(Particle *p)
{
	// make sure we are not screwed with a null pointer
	assert(p);

	bool prevExists = p->prev != nullptr;
	bool nextExists = p->next != nullptr;
	if (prevExists)
	{ 
		if (nextExists)
		{
			// middle of the list
			p->prev->next = p->next;
			p->next->prev = p->prev;
		}
		else p->prev->next = nullptr; // last on the list 
	}
	else
	{
		if (nextExists)
		{
			// first on the list
			p->next->prev = nullptr;
			this->headParticle = p->next;
		}
		else this->headParticle = nullptr; // only one on the list 
	}

	//reset its stats
	p->life = 0.0f;
	p->position.set(0.0f, 0.0f, 0.0f);
	p->velocity.set(0.0f, 0.0f, 0.0f);
	p->scale.set(1.0f, 1.0f, 1.0f);
	p->rotation = 0.0f;
	p->rotation_velocity = -0.5f;

	//add to unused list
	if (this->headUnused == nullptr)
	{ 
		// first on list
		this->headUnused = p;
		p->next = nullptr;
		p->prev = nullptr;
	}
	else
	{ 
		// add to front of list
		headUnused->prev = p;
		p->next = headUnused;
		p->prev = nullptr;
		headUnused = p;
	}
}

void ParticleEmitter::draw()
{
	// OpenGL goo... don't worrry about this
	glVertexPointer(3, GL_FLOAT, 0, squareVertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, squareColors);
	glEnableClientState(GL_COLOR_ARRAY);

	// iterate throught the list of particles
	Particle *p = headParticle;
	while (p != nullptr)
	{
		// set the transformation matrix
		glLoadMatrixf(reinterpret_cast<float*>(&p->drawMatrix));

		// draw the trangle strip
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		p = p->next;
	}
}

void ParticleEmitter::Execute(Vect4D& pos, Vect4D& vel, Vect4D& sc)
{
	// Add some randomness...

	// --------------------------------------------------------------
	//   Ses it's ugly - I didn't write this so don't bitch at me   |
	//   Sometimes code like this is inside real commerical code    |
	//   ( so now you know how it feels )   |
	//---------------------------------------------------------------

	// x - variance
	float var = static_cast<float>(rand() % 1000) * 0.001f; // Var
	float sign = static_cast<float>(rand() % 2);  // Sign 
	float *t_pos = reinterpret_cast<float*>(&pos);
	float *t_var = &pos_variance[x];
	if (sign == 0)
	{
		var *= -1.0;
	}
	*t_pos += *t_var * var;

	// y - variance
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	t_pos++;
	t_var++;
	if (sign == 0)
	{
		var *= -1.0;
	}
	*t_pos += *t_var * var;

	// z - variance  
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	t_pos++;
	t_var++;
	if (sign == 0)
	{
		var *= -1.0;
	}
	*t_pos += *t_var * var;

	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);

	// x  - add velocity
	t_pos = &vel[x];
	t_var = &vel_variance[x];
	if (sign == 0)
	{
		var *= -1.0;
	}
	*t_pos += *t_var * var;

	// y - add velocity    
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	t_pos++;
	t_var++;
	if (sign == 0)
	{
		var *= -1.0;
	}
	*t_pos += *t_var * var;

	// z - add velocity
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	t_pos++;
	t_var++;
	if (sign == 0)
	{
		var *= -1.0;
	}
	*t_pos += *t_var * var;

	// correct the sign
	var = 2.0f * static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);

	if (sign == 0)
	{
		var *= -1.0;
	}
	sc = sc * var;
}


void ParticleEmitter::GoodBye()
{
	/*Particle *pTmp = this->headParticle;
	Particle *pDeadMan = nullptr;
	while (pTmp)
	{
		pDeadMan = pTmp;
		pTmp = pTmp->next;
		delete pDeadMan;
	}*/
}

Particle *ParticleEmitter::getUnusedParticle()
{
	Particle *rtnParticle = this->headUnused;

	if (this->headUnused->next != nullptr) this->headUnused->next->prev = nullptr;
	this->headUnused = headUnused->next;

	return rtnParticle;
}

// End of file
