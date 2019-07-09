
#include "SFML\Graphics.hpp"

class Collider;

struct Manifold
{
public:
	Collider* ColliderA = nullptr;

	Collider* ColliderB = nullptr;

	bool Collision = false;

	sf::Vector2f PenetrationDepth;

	sf::Vector2f hitNormal;
};