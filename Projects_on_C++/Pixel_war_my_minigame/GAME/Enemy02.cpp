#include "Enemy02.h"

#include <iostream>

void Enemy02::initTexture()
{
	//Load a texture from file
	if (!this->texture.loadFromFile("Textures/enemy.png"))
	{
		std::cout << "ERROR::ENEMY::INITTEXTURE::Could not load texture file." << "\n";
	}
}

void Enemy02::initSprite()
{
	//Set the texture to the sprite
	
	this->sprite.setTexture(this->texture);

	int sizeType = rand() % 3 + 1;
	//Resize the sprite 
	switch (sizeType)
	{
	case 1:
		this->sprite.scale(0.05f, 0.05f);
		break;
	case 2:
		this->sprite.scale(0.09f, 0.09f);
		break;
	case 3:
		this->sprite.scale(0.15f, 0.15f);
		break;
	}
}

void Enemy02::initVariables()
{
	this->pointCount = rand() % 8 + 3; //min = 3 max = 10
	this->speed = static_cast<float>(this->pointCount / 3);
	this->hpMax = static_cast<int>(this->pointCount);
	this->hp = this->hpMax;
	this->damage = this->pointCount;
	this->points = this->pointCount;

}
Enemy02::Enemy02(float pos_x, float pos_y)
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->sprite.setPosition(pos_x, pos_y);
}

Enemy02::~Enemy02()
{

}

//Accessors
const sf::FloatRect Enemy02::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Enemy02::getPoints() const
{
	return this->points;
}

const int& Enemy02::getDamage() const
{
	return this->damage;
}

//Functions
void Enemy02::update()
{
	this->sprite.move(0.f, this->speed);
} 

void Enemy02::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}