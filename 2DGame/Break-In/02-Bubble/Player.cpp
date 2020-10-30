#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"

#define ESCALAT 2.f

enum PlayerAnims
{
	LOOK_FRONT, LOOK_RIGHT, LOOK_LEFT, LOOK_TOP, LOOK_BOTTOM, LOOK_TOPRIGHT, LOOK_TOPLEFT, LOOK_BOTRIGHT, LOOK_BOTLEFT, DEAD
};


void Player::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, TileMap* tileMap)
{
	playerSize = glm::ivec2(38 * ESCALAT, 64 * ESCALAT);
	spritesheet.loadFromFile("images/player.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64 * ESCALAT, 64 * ESCALAT), glm::vec2(0.2, 0.33), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(10);

	sprite->setAnimationSpeed(LOOK_FRONT, 8);
	sprite->addKeyframe(LOOK_FRONT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(LOOK_RIGHT, 8);
	sprite->addKeyframe(LOOK_RIGHT, glm::vec2(0.f, 0.33f));

	sprite->setAnimationSpeed(LOOK_LEFT, 8);
	sprite->addKeyframe(LOOK_LEFT, glm::vec2(0.2f, 0.33f));

	sprite->setAnimationSpeed(LOOK_TOP, 8);
	sprite->addKeyframe(LOOK_TOP, glm::vec2(0.4f, 0.33f));

	sprite->setAnimationSpeed(LOOK_BOTTOM, 8);
	sprite->addKeyframe(LOOK_BOTTOM, glm::vec2(0.6f, 0.33f));

	sprite->setAnimationSpeed(LOOK_TOPRIGHT, 8);
	sprite->addKeyframe(LOOK_TOPRIGHT, glm::vec2(0.8f, 0.33f));

	sprite->setAnimationSpeed(LOOK_TOPLEFT, 8);
	sprite->addKeyframe(LOOK_TOPLEFT, glm::vec2(0.f, 0.66f));

	sprite->setAnimationSpeed(LOOK_BOTRIGHT, 8);
	sprite->addKeyframe(LOOK_BOTRIGHT, glm::vec2(0.2f, 0.66f));

	sprite->setAnimationSpeed(LOOK_BOTLEFT, 8);
	sprite->addKeyframe(LOOK_BOTLEFT, glm::vec2(0.4f, 0.66f));

	sprite->setAnimationSpeed(DEAD, 4);
	sprite->addKeyframe(DEAD, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(DEAD, glm::vec2(0.2f, 0.f));
	sprite->addKeyframe(DEAD, glm::vec2(0.4f, 0.f));
	sprite->addKeyframe(DEAD, glm::vec2(0.6f, 0.f));
	sprite->addKeyframe(DEAD, glm::vec2(0.8f, 0.f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

	map = tileMap;
	visible = true;
}

void Player::update(int deltaTime)
{
	int minx = map->getPlayableArea().minx;
	int miny = map->getPlayableArea().miny;
	int maxx = map->getPlayableArea().maxx;
	int maxy = map->getPlayableArea().maxy;
	sprite->update(deltaTime);
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		/*if(sprite->animation() != DEAD)
			sprite->changeAnimation(DEAD);*/
		posPlayer.x -= 4;
		if (posPlayer.x < minx)
		{
			posPlayer.x += 4;
		}
	}
	if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		/*if(sprite->animation() != LOOK_RIGHT)
			sprite->changeAnimation(LOOK_RIGHT);*/
		posPlayer.x += 4;
		if (posPlayer.x > maxx)
		{
			posPlayer.x -= 4;
		}
	}
	if (Game::instance().getSpecialKey(GLUT_KEY_UP))
	{
		/*if (sprite->animation() != LOOK_TOP)
			sprite->changeAnimation(LOOK_TOP);*/
		posPlayer.y -= 4;
		if (posPlayer.y < miny)
		{
			posPlayer.y += 4;
		}
	}
	if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))
	{
		/*if (sprite->animation() != LOOK_BOTTOM)
			sprite->changeAnimation(LOOK_BOTTOM);*/
		posPlayer.y += 4;
		if (posPlayer.y > maxy)
		{
			posPlayer.y -= 4;
		}
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	if (visible) sprite->render();
}

void Player::setPosition(const glm::vec2& pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::setVisibility(bool vis)
{
	visible = vis;
}
