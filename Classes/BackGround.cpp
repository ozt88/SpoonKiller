#include "pch.h"
#include "BackGround.h"
#include "GameManager.h"

USING_NS_CC;

bool BackGround::init()
{
	if(!Layer::init())
	{
		return false;
	}

	m_BackSprite1 = Sprite::createWithSpriteFrameName("Background1.png");
	m_BackSprite2 = Sprite::createWithSpriteFrameName("Background1.png");

	float width = m_BackSprite1->getContentSize().width;
	float height = m_BackSprite1->getContentSize().height;

	float scale = Director::getInstance()->getWinSize().height / height;
	addChild(m_BackSprite1);
	addChild(m_BackSprite2);

	m_BackSprite1->setAnchorPoint(Vec2::ZERO);
	m_BackSprite2->setAnchorPoint(Vec2::ZERO);

	m_BackSprite1->setScale(scale);
	m_BackSprite2->setScale(scale); 

	auto curPos = m_BackSprite2->getPosition();
	curPos.x += width * scale - 10.f;
	m_BackSprite2->setPosition(curPos);

	scheduleUpdate();
	return true;
}

void BackGround::update(float dTime)
{
	static float distanceSum = 0.f;
	static float backgroundWidth = m_BackSprite1->getContentSize().width * m_BackSprite1->getScale();
	static float windowWidth = Director::getInstance()->getWinSize().width;

	if(GET_GAME_MANAGER()->isGamePlaying())
	{
		if(m_Runner != nullptr)
		{
			m_Velocity = m_Runner->getVelocity() * -10.f;
		}

		float deltaDistance = m_Velocity * dTime;

		distanceSum += deltaDistance;
		auto pos1 = m_BackSprite1->getPosition();
		auto pos2 = m_BackSprite2->getPosition();

		if(abs(distanceSum) > backgroundWidth)
		{
			distanceSum = 0.f;
			pos1.x = 0.f;
			pos2.x = backgroundWidth - 10.f;
		}
		else
		{
			pos1.x += deltaDistance;
			pos2.x += deltaDistance;
		}
		m_BackSprite1->setPosition(pos1);
		m_BackSprite2->setPosition(pos2);
	}
}