#include "Application.h"
#include "Components.hpp"
#include "LevelBuilder.h"
#include "GameStates.hpp"

#include <sstream>
#include <iostream>
#include <algorithm>

DefaultGameState::DefaultGameState(Application & app, LevelSchema blueprint)
	: BaseGameState::BaseGameState(app)
{
	m_border = app.GetFrame();
	float offsetY = m_border.width - m_border.height;
	m_collisionHandler = new CollisionHandler(4, sf::FloatRect(0, -(offsetY*0.5f), m_border.width, m_border.width));

	lives = new UILable();
	lives->SetPosition(sf::Vector2f(m_border.left + 100, m_border.height - 50));

	std::stringstream ss;
	ss << "Lives: " << m_lives;
	lives->SetText(ss.str());

	m_UIHandler.AddUIElement(lives);

	Construct(blueprint);
}

void DefaultGameState::Update(sf::Time & deltaTime)
{
	BaseGameState::Update(deltaTime);

	if (m_initial && !m_run)
	{
		PhysicsBody & ballPhysics = *m_ball->GetComponent<PhysicsBody>();
		float x = m_paddle->GetPosition().x;
		float y = m_paddle->GetPosition().y - 32;
	
		m_ball->SetPosition(sf::Vector2f(x, y));
		ballPhysics.SetVelocity(sf::Vector2f());
	
		if (InputHandler::IsKeyDown(sf::Keyboard::Space))
		{
			PhysicsBody & paddlePhysics = *m_paddle->GetComponent<PhysicsBody>();
			
			float x = std::cosf(45) * 500.0f;
			float y = std::sinf(45) * 500.0f;
			if (sf::getNormalized(paddlePhysics.GetVelocity()).x < 0)
				x *= -1;
								   
			ballPhysics.AddVelocity(sf::Vector2f(x, -y));
			m_initial = false;
			m_run = true;
		}
	}
	
	if (bricks.size() == 0 || (m_lives <= 0))
	{
		bool winState = false;

		if (bricks.size() == 0)
			winState = true;
		
		m_gameStateManager.ReplaceState(new FinishState(m_application, winState));
		return;
	}
	
	if (InputHandler::IsKeyDown(sf::Keyboard::Key::A))
		m_paddle->Move(-25);
	if (InputHandler::IsKeyDown(sf::Keyboard::Key::D))
		m_paddle->Move(25);


	m_ball->Update(deltaTime);

	m_paddle->Update(deltaTime);

	for (int i = 0; i < bricks.size(); i++)
	{
		bricks[i]->Update(deltaTime);
		// if brick is dead
		if (bricks[i]->GetHitPoints() <= 0)
		{
			// deallocate brick
			Brick * brick = bricks[i];

			delete brick;
			brick = nullptr;

			// remove null element
			bricks.erase(bricks.begin() + i);
		}
	}

	DetectCollisions(deltaTime);
}

void DefaultGameState::DetectCollisions(sf::Time & deltaTime)
{
	Collider pad = *m_paddle->GetComponent<Collider>();
	sf::Vector2f padPos = m_paddle->GetPosition();
	PhysicsBody & padBody = *m_paddle->GetComponent<PhysicsBody>();


	// handle ball->vertical-wall collisions
	if (padPos.x - 52 < m_border.left || padPos.x + 52 > m_border.width)
	{
		padBody.SetVelocity(sf::Vector2f());
		padBody.SetAcceleration(sf::Vector2f());

		if ((padPos.x - 52) < m_border.left)
			m_paddle->SetPosition(sf::Vector2f(m_border.left + 52, padPos.y));
		else if ((padPos.x + 52) > m_border.left + m_border.width)
			m_paddle->SetPosition(sf::Vector2f(m_border.width - 52, padPos.y));
	}
			
	// get collision specific properties from ball
	PhysicsBody& body = *m_ball->GetComponent<PhysicsBody>();
	Collider col = *m_ball->GetComponent<Collider>();
	sf::FloatRect bounds = col.GetBounds();
	sf::Vector2f velocity = body.GetVelocity();
	sf::Vector2f position = m_ball->GetPosition();
	
	// handle ball->vertical-wall collisions
	if (position.x <= m_border.left || position.x >= m_border.width)
	{
		if (position.x <= m_border.left)
			m_ball->SetPosition(sf::Vector2f(m_border.left + 10, position.y));
		else if (position.x >= m_border.left + m_border.width)
			m_ball->SetPosition(sf::Vector2f(m_border.width - 10, position.y));

		velocity.x = -velocity.x;
		body.SetVelocity(velocity);
	}
	// handle side wall collisions
	else if (position.y <= m_border.top || position.y >= m_border.height)
	{
		if (position.y <= m_border.top)
			m_ball->SetPosition(sf::Vector2f(position.x, m_border.top));
		else if (position.y >= m_border.height)
		{
			// lose a life
			m_lives -= 1;

			std::stringstream ss;
			ss << "Lives: " << m_lives;
			lives->SetText(ss.str());

			m_initial = true;
			m_run = false;

			// reset ball position
			m_ball->SetPosition(sf::Vector2f(m_paddle->GetPosition() - sf::Vector2f(0, 64)));
		}
		// revert velocity
		velocity.y = -velocity.y;
		body.SetVelocity(velocity);
	}

	std::vector<Collider*> potentialCollisions;
	// add walls 
	potentialCollisions.push_back(&pad);

	m_collisionHandler->Query(col.GetBounds(), potentialCollisions);
	m_collisionHandler->Broadphase(m_ball->GetComponent<Collider>(), potentialCollisions);
	m_collisionHandler->NarrowPhase();

	potentialCollisions.clear();
}

void DefaultGameState::Draw(sf::RenderWindow & renderer)
{
	BaseGameState::Draw(renderer);

	for (auto & brick : bricks)
		brick->Draw(renderer);

	m_ball->Draw(renderer);
	m_paddle->Draw(renderer);
	m_collisionHandler->Draw(renderer);
}

void DefaultGameState::CleanUp()
{
	BaseGameState::CleanUp();
	
	m_paddle->CleanUp();
	delete m_paddle;
	m_paddle = nullptr;

	while (bricks.size() > 0)
	{
		Brick * brick = bricks.back();
		bricks.pop_back();

		brick->CleanUp();		
		delete brick;
		brick = nullptr;
	}

	m_collisionHandler->CleanUp();
	delete m_collisionHandler;
	m_collisionHandler = nullptr;

	m_ball->CleanUp();
	delete m_ball;
	m_ball = nullptr;
}

void DefaultGameState::Construct(LevelSchema blueprint)
{
	sf::Texture & brickTex = m_contentManager.GetTexture("brick_glossy");
	sf::Texture & ballTex = m_contentManager.GetTexture("ball_grey");
	sf::Texture & paddleTex = m_contentManager.GetTexture("paddle");
	
	// setup game objects //
	// set up ball
	m_ball = new Ball(sf::Vector2f(512, 704), 11, 8);


	AudioSource & source = *m_ball->GetComponent<AudioSource>();
	//source.LoadBuffer(bounce);
	//source.SetVolume(0, 10);
	
	SpriteRenderer & ballRenderer = *m_ball->GetComponent<SpriteRenderer>();
	sf::Sprite ballSprite;
	ballSprite.setTexture(ballTex);
	ballRenderer.LoadSprite(ballSprite);
	
	// set up paddle
	m_paddle = new Paddle(sf::Vector2f(512, 736), sf::Vector2f(104, 24));
	SpriteRenderer & paddleRenderer = *m_paddle->GetComponent<SpriteRenderer>();
	sf::Sprite sprite;
	sprite.setTexture(paddleTex);
	paddleRenderer.LoadSprite(sprite);

	// set up bricks
	sf::Vector2f brickSize = sf::Vector2f(64, 32);
	for (int y = 0; y < blueprint.Cells.y; y++)
	{
		for (int x = 0; x < blueprint.Cells.x; x++)
		{
			sf::Vector2f position;
			position.x = (brickSize.x * x) + (brickSize.x * 0.5f);
			position.y = (brickSize.y * y) + (brickSize.y * 0.5f);

			int hp = 0;
			sf::Color color;

			switch (blueprint.ObjectIDs[x + y * blueprint.Cells.x])
			{
			case 'L':
				hp = 1;
				color = sf::Color::Yellow;
				break;
			case 'M':
				hp = 2;
				color = sf::Color(255, 165, 0);
				break;
			case 'H':
				hp = 3;
				color = sf::Color::Red;
				break;
			case 'x':
				continue;
			case '\t':
				continue;
			}

			Brick* brick = new Brick(brickSize, position);

			brick->SetPosition(position);
			brick->SetColor(color);
			brick->SetHitPoints(hp);

			SpriteRenderer & brickRenderer = *brick->GetComponent<SpriteRenderer>();
			sf::Sprite brickSprite;
			brickSprite.setTexture(brickTex);
			brickRenderer.LoadSprite(brickSprite);
			brickRenderer.SetColor(color);
			
			bricks.push_back(brick);

			m_collisionHandler->Insert(brick->GetPosition(), *brick->GetComponent<Collider>());
		}
	}
}
