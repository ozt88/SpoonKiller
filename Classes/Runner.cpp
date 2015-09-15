#include "pch.h"
#include "Runner.h"
#include "UtilSpace.h"
#include "Killer.h"
#include "GameManager.h"

USING_NS_CC;

bool Runner::init()
{
	if(!Character::init())
	{
		return false;
	}
	initAnimations();
	setScale(2.f);

	setMaxHp(100.f);
	setCurHp(100.f);

	changeState(RUNNER_MOVING);
	UtilSpace::listenEvent("Hit", CC_CALLBACK_1(Runner::onHit, this), this);

	return true;
}

void Runner::update(float dTime)
{
	if(m_CurHp < 0.001f)
	{
		return changeLevel();
	}
	float tickHot = m_Hot * dTime;
	setCurHp(getCurHp() + tickHot);
}

void Runner::onAnimationEnd()
{
	switch(m_State)
	{
		case RUNNER_HITTED:
		{
			m_Velocity += 5.f;
			changeState(RUNNER_MOVING);
			break;
		}
		default:
		break;
	}
}

void Runner::initAnimations()
{
	for(int i = 0; i < LEVEL_MAX; ++i)
	{
		char movingName[128] = {0, };
		char runningName[128] = {0, };

		sprintf(movingName, "Runner%dRun", i + 1);
		sprintf(runningName, "Runner%dHit", i + 1);

		auto moveAni = UtilSpace::makeAnimation(movingName, 0, 5, 0.1f);
		moveAni->retain();
		m_Animations[i].push_back(StateAnimation {RUNNER_MOVING, moveAni});

		auto hitAni = UtilSpace::makeAnimation(runningName, 0, 5, 0.1f);
		hitAni->retain();
		m_Animations[i].push_back(StateAnimation {RUNNER_HITTED, hitAni});
	}
}


void Runner::onHit(cocos2d::EventCustom* event)
{
	auto killer = (Killer*)(event->getUserData());
	setCurHp(getCurHp() - killer->getPower());
	changeState(RUNNER_HITTED);

	auto manager = GET_GAME_MANAGER();
	manager->setScore(manager->getScore() + m_Score);
}

void Runner::changeState(int state)
{
	if(m_State == state)
	{
		return;
	}
	m_State = state;
	m_Sprite->stopAllActions();

	auto stateAnimation = std::find_if(m_Animations[m_CurrentLevel].begin(), m_Animations[m_CurrentLevel].end(), [state](const StateAnimation& value)
	{
		return value.first == state;
	})->second;

	m_Width = stateAnimation->getFrames().at(0)->getSpriteFrame()->getOriginalSize().width;

	auto animate = Animate::create(stateAnimation);
	auto callfunc = CallFuncN::create(CC_CALLBACK_0(Runner::onAnimationEnd, this));
	auto sequence = Sequence::create(animate, callfunc, NULL);

	m_Sprite->runAction(RepeatForever::create(sequence));
}

void Runner::changeLevel()
{
	if(m_CurrentLevel == LEVEL_MAX - 1)
	{
		return GET_GAME_MANAGER()->changeScene(SceneType::TITLE_SCENE);
	}

	m_MaxHp *= 2;
	m_Hot *= 2;

	m_Score += 50.f;
	m_CurHp = m_MaxHp;

	m_Sprite->stopAllActions();
	int state = m_State;
	auto stateAnimation = std::find_if(m_Animations[++m_CurrentLevel].begin(), m_Animations[m_CurrentLevel].end(), [state](const StateAnimation& value)
	{
		return value.first == state;
	})->second;

	m_Width = m_Width = stateAnimation->getFrames().at(0)->getSpriteFrame()->getOriginalSize().width;

	auto animate = Animate::create(stateAnimation);
	auto callfunc = CallFuncN::create(CC_CALLBACK_0(Runner::onAnimationEnd, this));
	auto sequence = Sequence::create(animate, callfunc, NULL);

	m_Sprite->runAction(RepeatForever::create(sequence));
}
