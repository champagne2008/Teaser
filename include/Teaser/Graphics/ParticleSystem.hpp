//------------------------------------------------------------
// <copyright file="ParticleSystem.hpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#ifndef TEASER_PARTICLESYSTEM_HPP
#define TEASER_PARTICLESYSTEM_HPP

#include <Teaser/Common.hpp>
#include <Teaser/Graphics/Texture.hpp>
#include <vector>
#include <Teaser/Math.hpp>


namespace Teaser
{


struct Particle 
{
	Vector3 position;
	int lifeTime;
	Vector3 velocity;
};

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();

	void init();
	void update();
	void render(const Matrix4& camera, const Matrix4& proj);

	Vector3 position;

private:

	Texture m_texture;
	Vector3 m_particleVelocity;
	std::vector<Particle> m_particles;

	int m_maxParticles;
	int m_numParticles;
	int m_particleLifeTime;

	int m_spawnTime;
	int m_nextSpawn;
	int m_timer;
	int m_lastTimer;


	GLuint m_vao;
};

} // namespace Teaser

#endif // TEASER_PARTICLESYSTEM_HPP