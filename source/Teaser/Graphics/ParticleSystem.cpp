//------------------------------------------------------------
// <copyright file="ParticleSystem.cpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#include <Teaser/Graphics/ParticleSystem.hpp>
#include <Teaser/Resources.hpp>
#include <Teaser/Graphics/Vertex.hpp>

namespace Teaser
{

ParticleSystem::ParticleSystem() {}

ParticleSystem::~ParticleSystem() {}

void ParticleSystem::init() 
{

	g_shaders.insert(ShaderProgram::loadShaderFromFile("data/shaders/particle-shader.vert","data/shaders/particle-shader.frag"), "ParticleShader");

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	std::vector<Vertex> verts;
	
	verts.push_back({ Vector3(-0.5,-0.5,0),Vector3(0.5,0.5,0),Vector2(0,1) });
	verts.push_back({ Vector3(0.5,-0.5,0),Vector3(0.5,0.5,0),Vector2(1,1) });
	verts.push_back({ Vector3(0.5,0.5,0),Vector3(0.5,0.5,0),Vector2(1,0) });
	verts.push_back({ Vector3(-0.5,0.5,0),Vector3(0.5,0.5,0),Vector2(0,0) });

	std::vector<u16> inds;


	inds.push_back(0);
	inds.push_back(1);
	inds.push_back(2);
	inds.push_back(2);
	inds.push_back(3);
	inds.push_back(4);

	u32 ibo;
	u32 vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, verts.size()*sizeof(Vertex), verts.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, inds.size()*sizeof(u16), inds.data(), GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0,
		3,
		GL_FLOAT,
		GL_FALSE,
		Vertex::size(),
		(const void*)Vertex::offsetPosition());
	glVertexAttribPointer(1,
		1,
		GL_FLOAT,
		GL_FALSE,
		Vertex::size(),
		(const void*)Vertex::offsetColor());
	glVertexAttribPointer(2,
		2,
		GL_FLOAT,
		GL_FALSE,
		Vertex::size(),
		(const void*)Vertex::offsetUV());
	glBindVertexArray(0);


	m_texture = g_textures["Cat"];
	m_maxParticles = 100;
	m_particleLifeTime = 10000;
	m_spawnTime = 10;
	m_particleVelocity = Vector3(0, 0, 0.1f);
}

void ParticleSystem::update()
{
	m_timer = SDL_GetTicks();

	if (m_timer > m_nextSpawn)
	{
		// Spawn particle
		if (m_particles.size() < m_maxParticles)
		{
			Particle p;

			p.lifeTime = 0;
			p.position = position;
			p.velocity = m_particleVelocity;

			m_particles.push_back(p);
		}
		m_nextSpawn += m_spawnTime;
	}

	u32 timepast = m_timer - m_lastTimer;
	m_lastTimer = m_timer;
	auto it = m_particles.begin();
	for (; it != m_particles.end(); it++)
	{
		it->lifeTime += timepast;
		it->position += it->velocity; // * deltaTime;

		if (it->lifeTime > m_particleLifeTime)
		{
			m_particles.erase(it);
			break;
		}
	}

}

void ParticleSystem::render(const Matrix4& camera, const Matrix4& proj)
{

	ShaderProgram *shader = &g_shaders["ParticleShader"]
	    .setUniform("u_view", camera)
	    .setUniform("u_proj", proj)
	    .setUniform("u_sprite", 0).use();
	glActiveTexture(GL_TEXTURE0);

	m_texture.bind();

	glBindVertexArray(m_vao);

	auto it = m_particles.begin();
	for (; it != m_particles.end(); it++)
	{
		Matrix4 model = translate(it->position);


		shader->setUniform("u_model", model);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	}
}

} // namespace Teaser