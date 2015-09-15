#include "pch.h"
#include "HPBar.h"
#include "GameManager.h"

USING_NS_CC;

bool HpBar::init()
{
	if(!Node::init())
	{
		return false;
	}
	scheduleUpdate();
	return true;
}

void HpBar::update(float dTime)
{
	if(GET_GAME_MANAGER()->isGamePlaying())
	{
		if(m_Subject == nullptr)
		{
			return;
		}

		float maxHp = m_Subject->getMaxHp();
		float curHp = m_Subject->getCurHp();

		if(maxHp < 0.001f || maxHp < curHp)
		{
			return;
		}

		m_Percent = curHp / maxHp * 100.f;
		m_ProgressBar->setPercentage(m_Percent);
	}
}


bool KillerHpBar::init()
{
	if(!HpBar::init())
	{
		return false;
	}

	m_BarBody = Sprite::createWithSpriteFrameName("barX.png");
	m_BarBody->setAnchorPoint(Vec2::ZERO);
	addChild(m_BarBody);

	m_ProgressBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("SpoonBar.png"));
	m_ProgressBar->setType(ProgressTimer::Type::BAR);
	m_ProgressBar->setAnchorPoint(Vec2::ZERO);
	m_ProgressBar->setMidpoint(Vec2(0, 0));
	m_ProgressBar->setBarChangeRate(Vec2(1, 0));
	m_ProgressBar->setPercentage(100.f);

	m_BarBody->addChild(m_ProgressBar, -1);

	return true;
}


bool RunnerHpBar::init()
{
	if(!HpBar::init())
	{
		return false;
	}

	m_BarBody = Sprite::createWithSpriteFrameName("barX.png");
	m_BarBody->setAnchorPoint(Vec2::ZERO);
	addChild(m_BarBody);
	
	m_ProgressBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("HPBar.png"));
	m_ProgressBar->setType(ProgressTimer::Type::BAR);
	m_ProgressBar->setBarChangeRate(Vec2(1, 0));
	m_ProgressBar->setMidpoint(Vec2(1, 0));
	m_ProgressBar->setAnchorPoint(Vec2::ZERO);
	m_ProgressBar->setPercentage(100.f);

	m_BarBody->addChild(m_ProgressBar, -1);
	m_BarBody->setScaleX(-1.f);

	return true;
}
