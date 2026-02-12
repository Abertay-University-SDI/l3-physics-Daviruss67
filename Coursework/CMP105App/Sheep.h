#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"

class Sheep :
	public GameObject
{

public:
	Sheep();
	~Sheep();
	void SetWorldSize(float right, float bottom) 
	{ 
		m_worldSize = { right, bottom };
	};

	void checkWallAndBounce();
	void collisionResponse(GameObject& collider) override;

	void handleInput(float dt) override;
	void update(float dt) override;

private:
	const float acceleration = 30.f;
	const float m_drag = 0.95f;
	const float COEFF_OF_RESTITUTION = 0.8f;
	sf::Vector2f m_acceleration;
	sf::Vector2f m_worldSize;

	Animation m_walkDown;
	Animation m_walkUp;
	Animation m_walkUpRight;
	Animation m_walkRight;
	Animation m_walkDownRight;

	Animation* m_currentAnimation;
};

