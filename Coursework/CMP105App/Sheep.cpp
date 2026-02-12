#include "Sheep.h"
#include <iostream>;
Sheep::Sheep()
{
	// initialise animations
	for (int i = 0; i < 4; i++)
		m_walkDown.addFrame({ { 64 * i, 0 }, { 64, 64 } });
	m_walkDown.setLooping(true);
	m_walkDown.setFrameSpeed(0.25f);

	for (int i = 0; i < 4; i++)
		m_walkUp.addFrame({ { (64 * (i + 4)), 0 }, { 64, 64 } });
	m_walkUp.setLooping(true);
	m_walkUp.setFrameSpeed(0.25f);

	for (int i = 0; i < 4; i++)
		m_walkUpRight.addFrame({ { 64 * i, 64 }, { 64, 64 } });
	m_walkUpRight.setLooping(true);
	m_walkUpRight.setFrameSpeed(0.25f);

	for (int i = 0; i < 4; i++)
		m_walkRight.addFrame({ { (64 * (i + 4)), 64 }, { 64, 64 } });
	m_walkRight.setLooping(true);
	m_walkRight.setFrameSpeed(0.25f);

	for (int i = 0; i < 4; i++)
		m_walkDownRight.addFrame({ { 64 * i, 128 }, { 64, 64 } });
	m_walkDownRight.setLooping(true);
	m_walkDownRight.setFrameSpeed(0.25f);

	// the next 4 animations go clockwise from Up through Right to Down.

	m_currentAnimation = &m_walkDown;
	setTextureRect(m_currentAnimation->getCurrentFrame());
}

Sheep::~Sheep()
{
}

void Sheep::handleInput(float dt)
{
	sf::Vector2f inputDir = {0,0};

	if (m_input->isKeyDown(sf::Keyboard::Scancode::W)) 
	{
		inputDir += {0, -1};
	}
	if (m_input->isKeyDown(sf::Keyboard::Scancode::S)) 
	{
		inputDir += {0, 1};
	}
	if (m_input->isKeyDown(sf::Keyboard::Scancode::D)) 
	{
		inputDir += {1,0};
	}
	if (m_input->isKeyDown(sf::Keyboard::Scancode::A))
	{
		inputDir += {-1, 0};
	}
	
	m_acceleration = inputDir * acceleration;
}

void Sheep::update(float dt)
{
	m_velocity += (m_acceleration * dt) * m_drag;

	move(m_velocity);

	checkWallAndBounce();
}

void Sheep::checkWallAndBounce()
{
	sf::Vector2f pos = getPosition();
	sf::Vector2f size = getSize();
	if(m_velocity.x < 0 && pos.x < 0 || m_velocity.x > 0 && pos.x + size.x > m_worldSize.x)
	{
		m_velocity *= -COEFF_OF_RESTITUTION;
	}
	if(m_velocity.y < 0 && pos.y < 0 || m_velocity.y > 0&& pos.y + size.y > m_worldSize.y)
	{
		m_velocity *= -COEFF_OF_RESTITUTION;
	}

}

void Sheep::collisionResponse(GameObject& collider)
{
	m_velocity *= -COEFF_OF_RESTITUTION;
}