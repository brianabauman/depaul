//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#include "DO_NOT_MODIFY\OpenGLInterface.h"

#include "Particle.h"
#include "Matrix.h"

Particle::Particle()
	: life(0.0f),
	position(0.0f, 0.0f, 0.0f),
	velocity(0.0f, 0.0f, 0.0f),
	scale(1.0f, 1.0f, 1.0f),
	rotation(0.0f),
	rotation_velocity(-0.5f)
{
}

void Particle::Update(const float& time_elapsed)
{
	// serious math below - magic secret sauce
	life += time_elapsed;
	position = position + (velocity * time_elapsed);
	Vect4D z_axis(0.0f, -0.25f, 1.0f);
	Vect4D v1(3, 4, 0);
	position.Cross(z_axis, v1);
	v1.norm(v1);
	position = position + v1 * 0.05f * life;

	rotation = rotation + rotation_velocity * time_elapsed *2.01f;

	// get the camera matrix from OpenGL
	// need to get the position     
	Matrix cameraMatrix;

	// get the camera matrix from OpenGL
	glGetFloatv(GL_MODELVIEW_MATRIX, reinterpret_cast<float*>(&cameraMatrix));

	float cm12 = cameraMatrix.m12;
	float cm13 = cameraMatrix.m13;
	float cm14 = cameraMatrix.m14;

	float v = cosf(rotation);
	float w = sinf(rotation);

	drawMatrix = Matrix(Vect4D(v * scale.x * scale.x, -1.0f * w * scale.x * scale.y, 0.0f, 0.0f),
		Vect4D(w * scale.y * scale.x, v * scale.y * scale.y, 0.0f, 0.0f),
		Vect4D(0.0f, 0.0f, scale.z * scale.z, 0.0f),
		Vect4D(scale.x * ((v * (cm12 + position.x)) + ((cm13 + position.y) * w)), scale.y * ((((cm13 + position.y) * v) - (w * (cm12 + position.x)))), scale.z * (cm14 + position.z), 1.0f));
}


// End of file
